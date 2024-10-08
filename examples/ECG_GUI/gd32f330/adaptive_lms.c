#include "adaptive_lms.h"
#include "math.h"

long test_cnt=0;

float m_order = 2;
float niu = 0.5;
float filter_index = 0;

int   SIR ;
float Fs ;
float F1 ;
float F2 ;
float F3 ;
float Fnoise ;

float    w_forward[2], x[2], w[2];
float    d, y, error;

void  lms_filter_init(void)
{
	Fs = 250.0;
	Fnoise = 50.0;
	
	filter_index = 0;
}

float lms_filter(float signal_in)
{
		if(filter_index == 1){
			x[0] = 0;
			x[1] = 0;
			w[0] = 0;
			w[1] = 0;
		}

			d = signal_in;//signalnoise;
			x[0] = sin(2*PI*Fnoise*(filter_index)/Fs);
			x[1] = cos(2*PI*Fnoise*(filter_index)/Fs);
			
			y = x[0]*w[0] + x[1]*w[1];
		
			error = d - y;
		
			w_forward[0] = w[0] + niu * error * x[0];
			w_forward[1] = w[1] + niu * error * x[1];
			

			w[0] = w_forward[0];
			w[1] = w_forward[1];
			
			return error;			
}
