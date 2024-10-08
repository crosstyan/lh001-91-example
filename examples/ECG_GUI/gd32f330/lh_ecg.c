#include "lh_ecg.h"


void lh_ecg_init(void)
{
    LH001_91_ADC_INIT_t adc_init;
    LH001_91_PGA_INIT_t pga_init;
    LH001_91_LEADOFF_t leadoff_init;
    uint8_t val;

    lh001_91_adc_stop();

    leadoff_init.threshold = LH001_91_LEADOFF_DELTA_10;
    leadoff_init.current = LH001_91_LEADOFF_CURRENT_SOURCE_25nA;
    leadoff_init.sink_cfg = LH001_91_LEADOFF_SINK_AIN0_1;
    leadoff_init.source_cfg = LH001_91_LEADOFF_SOURCE_CLOSE;
    leadoff_init.rld_sink_en = 1;
    leadoff_init.ain0_detect_en = 1;
    leadoff_init.ain1_detect_en = 1;
    leadoff_init.rld_detect_en = 1;
    lh001_91_leadoff_init(&leadoff_init);


    lh001_91_rld_init(1,ENUM_LH001_91_RLD_REF_AVDD_DIV2,ENUM_LH001_91_RLD_CHOP_FMOD_DIV32);

    pga_init.gain = ENUM_LH001_91_PGA_PGAGAIN_6;
    pga_init.pga_bypass = 0;
    pga_init.power_mode = ENUM_LH001_91_PGA_POWER_LP;
    pga_init.comm_sense_en = 1;
    pga_init.pga_chop = ENUM_LH001_91_PGA_CHOP_DIV16;
    lh001_91_pga_init(&pga_init);

    adc_init.Fmodclk = ENUM_LH001_91_ADC_FMODCLK_128K;
    adc_init.oversample_rate = ENUM_LH001_91_ADC_DR_DIV512; ; //update rate = Fmodclk/oversample_rate
    adc_init.conv_mode = ENUM_LH001_91_ADC_CONTINOUS;
    adc_init.ref_sel = ENUM_LH001_91_ADC_REF_2V5;
    lh001_91_adc_init(&adc_init);
    //lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_VCM,ENUM_LH001_91_ADCCHN_GND);	//FOR NOISE TEST
	lh001_91_adc_channel(ENUM_LH001_91_ADCCHP_AIN0,ENUM_LH001_91_ADCCHN_AIN1);
	
    lms_filter_init();
	panTompkinsInit();

}



void lh_ecg_start(void)
{
   lh001_91_adc_go();
   lh001_91_rdatac_start(); 
}

void lh_ecg_stop(void)
{
   lh001_91_adc_stop();
   lh001_91_rdatac_stop(); 
}


/*
    Fs = 250Hz
    4-order chebv band-stop filter at frequency [45Hz,55Hz] and [90Hz,110Hz]
*/
//const float b2[41] = {
//  2.41640288e-03, -2.31230100e-03,  1.09808153e-03,  1.35957395e-03,
// -4.15382112e-03,  5.34472002e-03, -3.64315432e-03,  6.26688737e-04,
// -8.15628018e-04,  8.04907323e-03, -2.01611580e-02,  2.69228606e-02,
// -1.51439608e-02, -2.06258740e-02,  6.92693258e-02, -1.04541940e-01,
//  9.89411738e-02, -4.25430329e-02, -4.62158534e-02,  1.27072695e-01,
//  8.38112256e-01,  1.27072695e-01, -4.62158534e-02, -4.25430329e-02,
//  9.89411738e-02, -1.04541940e-01,  6.92693258e-02, -2.06258740e-02,
// -1.51439608e-02,  2.69228606e-02, -2.01611580e-02,  8.04907323e-03,
// -8.15628018e-04,  6.26688737e-04, -3.64315432e-03,  5.34472002e-03,
// -4.15382112e-03,  1.35957395e-03,  1.09808153e-03, -2.31230100e-03,
//  2.41640288e-03
//};

//static float xn2[41] = {0};
//float lh_filter_100Hz(float input)
//{
//    float sum = 0;
//	  float t,b;

//	  t = xn2[0];
//		for(uint32_t i=1; i<41; i++)
//		{
//			b = xn2[i];
//			xn2[i] = t;
//			t = b;
//		}
//		
//		xn2[0] = input;
//		for(uint32_t i=0; i<41; i++){
//      sum += b2[i] * xn2[i];
//    }
//		return sum;
//}
//const float b1[41] = {
//  0.00241684,  0.00088338, -0.00287533, -0.00356005,  0.0015869 ,  0.00534568,
//  0.00139181, -0.00164099,  0.00213573, -0.00307502, -0.02016478, -0.01028547,
//  0.03965453,  0.05400894, -0.02646328, -0.10456073, -0.03779896,  0.11139912,
//  0.12101642, -0.04854617,  0.83826286, -0.04854617,  0.12101642,  0.11139912,
// -0.03779896, -0.10456073, -0.02646328,  0.05400894,  0.03965453, -0.01028547,
// -0.02016478, -0.00307502,  0.00213573, -0.00164099,  0.00139181,  0.00534568,
//  0.0015869 , -0.00356005, -0.00287533,  0.00088338,  0.00241684
//};

//static float xn1[41] = {0};
//float lh_filter_50Hz(float input)
//{
//    float sum = 0;
//	  float sum2 = 0;
//	  float t,b;

//	  t = xn1[0];
//		for(uint32_t i=1; i<41; i++)
//		{
//			b = xn1[i];
//			xn1[i] = t;
//			t = b;
//		}
//		
//		xn1[0] = input;
//		for(uint32_t i=0; i<41; i++){
//      sum += b1[i] * xn1[i];
//    }
//		
//		return sum;
//		//sum2 = lh_filter_100Hz(sum);
//		//return sum2;
//}


//const float hp_b[] = {0.98132818, -1.96257889,  0.98132818};
//const float hp_a[] = {-1.96223021,  0.96300504,0};

const float hp_b[] = {0.99376785, -1.98753492,  0.99376785};
const float hp_a[] = {-1.98749608,  0.98757454,0};

static float hp_xn1[3] = {0};
static float hp_yn1[3] = {0};
float lh_filter_highpass(float input)
{
    float sum = 0;

    sum += hp_b[0] * input;
    for(uint32_t i=3-1; i > 0; i--)
    {
        sum += hp_b[i] * hp_xn1[i-1];
        hp_xn1[i] = hp_xn1[i-1];
        sum -= hp_a[i] * hp_yn1[i];
        hp_yn1[i] = hp_yn1[i-1];
    }
    sum -= hp_a[0]*hp_yn1[0];
    hp_yn1[0] = sum;
    hp_xn1[0] = input;

    return sum;
}


//const float lp_b[40] = {
//  1.30173319e-03, -7.11636762e-04, -1.10706144e-03,  2.51141181e-03,
// -8.78670494e-04, -3.73946761e-03,  5.93851639e-03, -8.54196659e-18,
// -1.03064815e-02,  1.13046374e-02,  4.64835718e-03, -2.32203740e-02,
//  1.75190366e-02,  1.81437408e-02, -4.79364281e-02,  2.29992494e-02,
//  5.77532005e-02, -1.16493839e-01,  2.62092839e-02,  5.36064791e-01,
//  5.36064791e-01,  2.62092839e-02, -1.16493839e-01,  5.77532005e-02,
//  2.29992494e-02, -4.79364281e-02,  1.81437408e-02,  1.75190366e-02,
// -2.32203740e-02,  4.64835718e-03,  1.13046374e-02, -1.03064815e-02,
// -8.54196659e-18,  5.93851639e-03, -3.73946761e-03, -8.78670494e-04,
//  2.51141181e-03, -1.10706144e-03, -7.11636762e-04,  1.30173319e-03
//};//80Hz cut-off
const float lp_b[80] = {
 -1.20660392e-04,  4.28771950e-04,  7.27509629e-04,  5.16551874e-04,
 -1.72993363e-04, -9.35944155e-04, -1.15942222e-03, -4.51847392e-04,
  9.19485935e-04,  1.99498876e-03,  1.71257783e-03, -1.71685115e-04,
 -2.56356410e-03, -3.54132355e-03, -1.78845014e-03,  2.04618182e-03,
  5.30500861e-03,  5.03223149e-03,  4.42154284e-04, -5.79508337e-03,
 -8.88301726e-03, -5.39313648e-03,  3.49136931e-03,  1.17812449e-02,
  1.24485251e-02,  2.98513760e-03, -1.13995411e-02, -2.01139096e-02,
 -1.44619192e-02,  4.81547847e-03,  2.56565875e-02,  3.12594257e-02,
  1.20592054e-02, -2.46338575e-02, -5.48674073e-02, -5.00028375e-02,
  5.60289280e-03,  1.01955145e-01,  2.04629810e-01,  2.70646316e-01,
  2.70646316e-01,  2.04629810e-01,  1.01955145e-01,  5.60289280e-03,
 -5.00028375e-02, -5.48674073e-02, -2.46338575e-02,  1.20592054e-02,
  3.12594257e-02,  2.56565875e-02,  4.81547847e-03, -1.44619192e-02,
 -2.01139096e-02, -1.13995411e-02,  2.98513760e-03,  1.24485251e-02,
  1.17812449e-02,  3.49136931e-03, -5.39313648e-03, -8.88301726e-03,
 -5.79508337e-03,  4.42154284e-04,  5.03223149e-03,  5.30500861e-03,
  2.04618182e-03, -1.78845014e-03, -3.54132355e-03, -2.56356410e-03,
 -1.71685115e-04,  1.71257783e-03,  1.99498876e-03,  9.19485935e-04,
 -4.51847392e-04, -1.15942222e-03, -9.35944155e-04, -1.72993363e-04,
  5.16551874e-04,  7.27509629e-04,  4.28771950e-04, -1.20660392e-04
};//35Hz cut-off
static float lp_xn1[80] = {0};
float lh_filter_lowpass(float input)
{
    float sum = 0;
	  float t,b;

	  t = lp_xn1[0];
		for(uint32_t i=1; i<80; i++)
		{
			b = lp_xn1[i];
			lp_xn1[i] = t;
			t = b;
		}
		
		lp_xn1[0] = input;
		for(uint32_t i=0; i<80; i++){
      sum += lp_b[i] * lp_xn1[i];
    }
		return sum;
}

static float avg_array[8] = {1};
float shift_avergage(float input){
	float avg;

	avg_array[7] = avg_array[6];
	avg_array[6] = avg_array[5];
	avg_array[5] = avg_array[4];
	avg_array[4] = avg_array[3];
	avg_array[3] = avg_array[2];
	avg_array[2] = avg_array[1];
	avg_array[1] = avg_array[0];
	avg_array[0] = input;
	
	avg=0;
	for(uint32_t i=0;i<8;i++)
	{
		avg += avg_array[i];
	}
	return avg/8.0;
	
}


