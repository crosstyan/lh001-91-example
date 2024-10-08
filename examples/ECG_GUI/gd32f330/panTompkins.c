/**
* ------------------------------------------------------------------------------*
* File: panTompkins.c                                                           *
*-------------------------------------------------------------------------------*
*/

#define WINDOWSIZE 38   // Integrator window size, in samples. Recommended to use 150ms. So, use FS*0.15
#define NOSAMPLE -32000 // An indicator that there are no more samples to read. Use an impossible value for a sample.
#define FS 250          // Sampling frequency.
#define BUFFSIZE 180    // The size of the buffers (in samples). Must fit more than 1.66 times an RR interval, which
// typically could be around 1 second.

#include "panTompkins.h"
#include <stdint.h>
#include <stdio.h>
//#include <stdio.h>      // Remove if not using the standard file functions.


typedef enum {false, true} bool;

//FILE *fin, *fout;       // Remove them if not using files and <stdio.h>.

/*
Use this function for any kind of setup you need before getting samples.
This is a good place to open a file, initialize your hardware and/or open
a serial connection.
Remember to update its parameters on the panTompkins.h file as well.
*/
//void init(char file_in[], char file_out[])
//{
//  fin = fopen(file_in, "r");
//  fout = fopen(file_out, "w+");
//}

/*
Use this function to read and return the next sample (from file, serial,
A/D converter etc) and put it in a suitable, numeric format. Return the
sample, or NOSAMPLE if there are no more samples.
*/
//dataType input()
//{
//  int num = NOSAMPLE;
//  if (!feof(fin))
//    fscanf(fin, "%d", &num);
//  
//  return num;
//}

/*
Use this function to output the information you see fit (last RR-interval,
sample index which triggered a peak detection, whether each sample was a R
peak (1) or not (0) etc), in whatever way you see fit (write on screen, write
on file, blink a LED, call other functions to do other kinds of processing,
such as feature extraction etc). Change its parameters to receive the necessary
information to output.
*/
//void output(int out)
//{
//  fprintf(fout, "%d\n", out);
//}

/*
This is the actual QRS-detecting function. It's a loop that constantly calls the input and output functions
and updates the thresholds and averages until there are no more samples. More details both above and in
shorter comments below.
*/

// The signal array is where the most recent samples are kept. The other arrays are the outputs of each
// filtering module: DC Block, low pass, high pass, integral etc.
dataType signal[BUFFSIZE], dcblock[BUFFSIZE], lowpass[BUFFSIZE], highpass[BUFFSIZE], derivative[BUFFSIZE], squared[BUFFSIZE], integral[BUFFSIZE], temp[BUFFSIZE];

// rr1 holds the last 8 RR intervals. rr2 holds the last 8 RR intervals between rrlow and rrhigh.
// rravg1 is the rr1 average, rr2 is the rravg2. rrlow = 0.92*rravg2, rrhigh = 1.08*rravg2 and rrmiss = 1.16*rravg2.
// rrlow is the lowest RR-interval considered normal for the current heart beat, while rrhigh is the highest.
// rrmiss is the longest that it would be expected until a new QRS is detected. If none is detected for such
// a long interval, the thresholds must be adjusted.
int rr1[8], rr2[8], rravg1, rravg2, rrlow = 0, rrhigh = 0, rrmiss = 0;

// i and j are iterators for loops.
// sample counts how many samples have been read so far.
// lastQRS stores which was the last sample read when the last R sample was triggered.
// lastSlope stores the value of the squared slope when the last R sample was triggered.
// These are all long unsigned int so that very long signals can be read without messing the count.
long unsigned int i, j, sample = 0, lastQRS = 0, lastSlope = 0, currentSlope = 0;

// This variable is used as an index to work with the signal buffers. If the buffers still aren't
// completely filled, it shows the last filled position. Once the buffers are full, it'll always
// show the last position, and new samples will make the buffers shift, discarding the oldest
// sample and storing the newest one on the last position.
int current;
int qrsdelay;
// There are the variables from the original Pan-Tompkins algorithm.
// The ones ending in _i correspond to values from the integrator.
// The ones ending in _f correspond to values from the DC-block/low-pass/high-pass filtered signal.
// The peak variables are peak candidates: signal values above the thresholds.
// The threshold 1 variables are the threshold variables. If a signal sample is higher than this threshold, it's a peak.
// The threshold 2 variables are half the threshold 1 ones. They're used for a back search when no peak is detected for too long.
// The spk and npk variables are, respectively, running estimates of signal and noise peaks.
dataType peak_i = 0, peak_f = 0, threshold_i1 = 0, threshold_i2 = 0, threshold_f1 = 0, threshold_f2 = 0, spk_i = 0, spk_f = 0, npk_i = 0, npk_f = 0;
dataType peak_mid = 0, temp_max, temp_min;
// qrs tells whether there was a detection or not.
// regular tells whether the heart pace is regular or not.
// prevRegular tells whether the heart beat was regular before the newest RR-interval was calculated.
bool qrs, regular = true, prevRegular;

bool pre_qwave, qwave;

// Initializing the RR averages
void panTompkinsInit(void)
{
	int i;
	
	rravg1 = rravg2 = 0;
  rrlow = 0;
  rrhigh = 0;
  rrmiss = 0;
  sample = 0; lastQRS = 0; lastSlope = 0; currentSlope = 0;
  
  peak_i = 0; peak_f = 0; threshold_i1 = 0; threshold_i2 = 0; threshold_f1 = 0; threshold_f2 = 0; spk_i = 0; spk_f = 0; npk_i = 0; npk_f = 0;
  peak_mid = 0;
  temp_max = temp_min = 0;
	qrsdelay = 0;
	
  qwave = false;

  for (i = 0; i < 8; i++)
  {
    rr1[i] = 0;
    rr2[i] = 0;
  }
  for (i = 0; i < BUFFSIZE-1; i++)
  {
		signal[i] = 0;
		dcblock[i] = 0;
		lowpass[i] = 0;
		highpass[i] = 0;
		derivative[i] = 0;
		squared[i] = 0;
		integral[i] = 0;
//    temp[i] = 0;
  }	
}

 int panTompkins( int ecginput, dataType *filtered)
{
  long unsigned int i, j;
  
  char ptbreak = 0;
  unsigned int ecgqrsoutput = 0;
  
  // The main loop where everything proposed in the paper happens. Ends when there are no more signal samples.
  
  // Test if the buffers are full.
  // If they are, shift them, discarding the oldest sample and adding the new one at the end.
  // Else, just put the newest sample in the next free position.
  // Update 'current' so that the program knows where's the newest sample.
  if (sample >= BUFFSIZE)
  {
    for (i = 0; i < BUFFSIZE - 1; i++)
    {
      signal[i] = signal[i+1];
      dcblock[i] = dcblock[i+1];
      lowpass[i] = lowpass[i+1];
      highpass[i] = highpass[i+1];
      derivative[i] = derivative[i+1];
      squared[i] = squared[i+1];
      integral[i] = integral[i+1];
//      temp[i] = integral[i+1];
    }
    current = BUFFSIZE - 1; //424;
    
  }
  else
  {
    current = sample;
  }
  signal[current] = ecginput;//(int)

  sample++; // Update sample counter
  
  qrs = false;
  
  // DC Block filter
  // This was not proposed on the original paper.
  // It is not necessary and can be removed if your sensor or database has no DC noise.
  if (current >= 1)
    dcblock[current] = signal[current] - signal[current-1] + 0.995*dcblock[current-1];
  else
    dcblock[current] = 0;
  
	dcblock[current] = dcblock[current];//>>4
  // Low Pass filter
  // Implemented as proposed by the original paper.
  // y(nT) = 2y(nT - T) - y(nT - 2T) + x(nT) - 2x(nT - 6T) + x(nT - 12T)
  // Can be removed if your signal was previously filtered, or replaced by a different filter.
  lowpass[current] = dcblock[current];
  if (current >= 1)
    lowpass[current] += 2*lowpass[current-1];
  if (current >= 2)
    lowpass[current] -= lowpass[current-2];
  if (current >= 6)
    lowpass[current] -= 2*dcblock[current-6];
  if (current >= 12)
    lowpass[current] += dcblock[current-12];
  
  // High Pass filter
  // Implemented as proposed by the original paper.
  // y(nT) = 32x(nT - 16T) - [y(nT - T) + x(nT) - x(nT - 32T)]
  // Can be removed if your signal was previously filtered, or replaced by a different filter.
  highpass[current] = -lowpass[current];
  if (current >= 1)
    highpass[current] -= highpass[current-1];
  if (current >= 16)
    highpass[current] += 32*lowpass[current-16];
  if (current >= 32)
    highpass[current] += lowpass[current-32];
  
	highpass[current] = highpass[current]>>9;//
	
	*filtered = highpass[current];
	
  // Derivative filter
  // This is an alternative implementation, the central difference method.
  // f'(a) = [f(a+h) - f(a-h)]/2h
  // The original formula used by Pan-Tompkins was:
  // y(nT) = (1/8T)[-x(nT - 2T) - 2x(nT - T) + 2x(nT + T) + x(nT + 2T)]
  derivative[current] = highpass[current];
  if (current > 0)
    derivative[current] -= highpass[current-1];
  
  // This just squares the derivative, to get rid of negative values and emphasize high frequencies.
  // y(nT) = [x(nT)]^2.
  squared[current] = (derivative[current])*(derivative[current]);//>>8
  
  
  
  // Moving-Window Integration
  // Implemented as proposed by the original paper.
  // y(nT) = (1/N)[x(nT - (N - 1)T) + x(nT - (N - 2)T) + ... x(nT)]
  // WINDOWSIZE, in samples, must be defined so that the window is ~150ms.
	integral[current] = 0;
  for (i = 0; i < WINDOWSIZE; i++)
  {
    if (current >= (dataType)i)
      integral[current] = integral[current] + squared[current - i];///100
    else
      break;
  }
  integral[current] /= (dataType)i;//i;
  
  *filtered = integral[current];
  

  for (i = 0; i < BUFFSIZE-1; i++)
  {
		temp[i] = temp[i+1];
	}		
  temp[BUFFSIZE-1] = integral[current];
	
	

//  printf( "$%d %d %d %d %d %d;", /*dcblock[current], lowpass[current]*/temp_max, temp_min, highpass[current], derivative[current],squared[current],integral[current] );
	
	if(sample>500)
	{}
		temp_max=0;
		temp_min=0x7fffff;
		for (i = 0; i < BUFFSIZE; i++)
		{
			if(temp[i]>temp_max)
				temp_max = temp[i];
			if(temp[i]<temp_min)
				temp_min = temp[i];
		}
		peak_mid = (temp_max+temp_min)/2;
	
  pre_qwave = qwave;
  qwave = (temp[current]>peak_mid)?true:false;
		
	qrsdelay++;
		
  if(pre_qwave==false && qwave==true && qrsdelay>FS/3)
  {
    qrs = true;
		qrsdelay = 0;
  }else
  {
    qrs = false;
  }

  // If the current signal is above one of the thresholds (integral or filtered signal), it's a peak candidate.
  if (integral[current] >= threshold_i1 || highpass[current] >= threshold_f1)
  {
    peak_i = integral[current];
    peak_f = highpass[current];
  }
  

    ecgqrsoutput = qrs;

	
  return ecgqrsoutput;
}

