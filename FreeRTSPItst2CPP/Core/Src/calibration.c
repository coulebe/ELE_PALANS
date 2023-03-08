#include "calibration.h"
//#include "freertosi.h"
#include "limits.h"



volatile uint8_t calibration_mode=CALIB_UNCAL;

volatile float target[2]={0};
volatile float target_v[2]={0};

volatile int32_t mycounter[3]={0};
volatile int32_t myvelocity[3]={0};
volatile uint8_t my_limit_status=0;
volatile float   mydt=0.001f;


uint8_t isCalibrating()
{
	return calibration_mode>= CALIB_INIT && calibration_mode <=CALIB_END;
}

uint8_t isCalibratingMode(uint8_t mode)
{
	return mode>= CALIB_INIT && mode <=CALIB_END;
}

void startCalibration()
{
	calibration_mode=CALIB_INIT;
}

void stopCalibration()
{
	if(!isCalibrating())return;

	calibration_mode=CALIB_UNCAL;
}

void startDemo()
{
	calibration_mode = CALIB_DEMO_BEGIN;
}

void stopDemo()
{
	calibration_mode=CALIB_UNCAL;
}

uint8_t isDemo()
{
	return calibration_mode>=CALIB_DEMO_BEGIN && calibration_mode <= CALIB_DEMO_END;
}

float total_error_I=0;

void moveTarget()
{
	float p_x =   ( (float)mycounter[0])*(DISTANCE_PER_TURN_X/PPRX) ;

	if(fabs(target[0]-p_x)<.15f) //only move it if it manages to follow.
	{
		target[0] += target_v[0]*mydt;
		target[1] += target_v[1]*mydt;
	}
	else
	{
		//Mechanical error. Can't follow target.
	}
}

void calibGetTarget(float* rtarget)
{
	rtarget[0] = target[0];
	rtarget[1] = target[1];
}

void calibGetVelocity(float* rvelocity)
{
	float v_x = ((float)myvelocity[0])*PPR_TO_DISTANCE_X/ mydt;
	float v_y = ((float)myvelocity[1])*PPR_TO_DISTANCE_X/ mydt;

	rvelocity[0]=v_x;
	rvelocity[1]=v_y;
}


void calibGetDelta(float* rdelta)
{
	float p_x =  ( (float)mycounter[0])*(DISTANCE_PER_TURN_X/PPRX);
	float p_y =  ( (float)mycounter[1])*(DISTANCE_PER_TURN_Y/PPRY);
	rdelta[0]=target[0] - p_x;
	rdelta[1]=target[1] - p_y;
}

float calibGetDeltaY()
{
	float p_y =  ( (float)mycounter[1])*(DISTANCE_PER_TURN_Y/PPRY);
	return target[1]-p_y;
}

//#define K_P 850.f
//#define K_I 0.f
//#define K_D 9.f

#define K_P 400.f
#define K_I 0.f
#define K_D 4.f

#define K_P_Y 80.f
#define K_I_Y 0.f
#define K_D_Y .6f

uint32_t pdcounter=0;

int8_t somenoise[24]=
{
		 80,
		-83,
		 14,
		 68,
		 49,
		-63,
		 83,
		 -2,

		 -46,
		-98,
		 56,
		 -3,
		 51,
		-44,
		-30,
		 93,

		 73,
		-86,
		 99,
		-80,
		 39,
		 86,
		 17,
		  7
};

void computePD(int32_t* pcounter, int32_t* pvelocity, int32_t* pwm_out)
{
	++pdcounter;
	{
		int8_t noise= somenoise[pdcounter%24];
//		float v_x =  ( (float)(pvelocity[0] ) + (float)noise*.0005f)*( PPR_TO_DISTANCE_X/ mydt ); //counterToVelocityX(pvelocity[0]);// ( (float)myvelocity[0] )/ (dt* PPM_X);

		float velocity_closer_to_zero = (float)pvelocity[0] ;
		if(velocity_closer_to_zero>1.f)velocity_closer_to_zero-=.5f;
		else if(velocity_closer_to_zero<-1.f)velocity_closer_to_zero+=.5f;
		else velocity_closer_to_zero=0;

		float v_x =  ( (float)(velocity_closer_to_zero) )*( PPR_TO_DISTANCE_X/ mydt ); //counterToVelocityX(pvelocity[0]);// ( (float)myvelocity[0] )/ (dt* PPM_X);
		float p_x =   ( (float)(pcounter[0] ))*PPR_TO_DISTANCE_X; //((float)mycounter[0]) / PPM_X;

		float target_p_x = target[0];
		float target_v_x = target_v[0];

		float error_P = target_p_x - p_x;

		float error_acceptable = 0.02f;// + 0.001f*(pdcounter%8);

		if(error_P>error_acceptable)error_P-=error_acceptable;	//Allow 1cm error.
		else if(error_P<-error_acceptable)error_P+=error_acceptable;
		else error_P=0;

		float error_D = target_v_x - v_x;
		//total_error_I += error_P*dt;

		float pwm_output = error_P*(K_P) /* + total_error_I* (K_I)*/ + error_D*(K_D);

		if(pwm_output>1.f)pwm_output=1.f;
		if(pwm_output<-1.f)pwm_output=-1.f;
		int32_t vPWMX_out = (int32_t)(pwm_output*12000);

//		if(vPWMX_out>12000)vPWMX_out=12000;
//		if(vPWMX_out<-12000)vPWMX_out=-12000;

 		pwm_out[0]=vPWMX_out;
	}
	{
		float v_y =  ( (float)pvelocity[1])*( PPR_TO_DISTANCE_Y/ mydt); //counterToVelocityX(pvelocity[0]);// ( (float)myvelocity[0] )/ (dt* PPM_X);
		float p_y =   ( (float)pcounter[1])*PPR_TO_DISTANCE_Y; //((float)mycounter[0]) / PPM_X;

		float target_p_y = target[1];
		float target_v_y = target_v[1];

		float error_P = target_p_y - p_y;
		float error_D = target_v_y - v_y;
		//total_error_I += error_P*dt;

		float pwm_output = error_P*(K_P_Y) /* + total_error_I* (K_I)*/ + error_D*(K_D_Y);

		if(pwm_output>.8f)pwm_output=.8f;
		if(pwm_output<-.8f)pwm_output=-.8f;


		int32_t vPWMY_out = (int32_t)(pwm_output*12000);
//		if(vPWMY_out>8000)vPWMY_out=8000;
//		if(vPWMY_out<-8000)vPWMY_out=-8000;
		pwm_out[1] = vPWMY_out;
	}

}

uint8_t getCalibrationMode()
{
	return calibration_mode;
}

float wait_time=0;
int32_t counter_limit_right=0;
int32_t counter_limit_left=0;
int32_t counter_center=0;

float calib_speed= 0.3f;
float calib_speed_y= 0.2f;

uint8_t calib_failed;


int32_t theta_min=0;
int32_t theta_max=0;

//Feedback loop called on timer callback at current update rate.
void updateCalibration(int32_t* pcounter, int32_t* pvelocity, uint8_t _limit_status,  int32_t* rPWM)
{
	my_limit_status = _limit_status;

	for(int i=0;i<3;++i)
	{
		mycounter[i] = pcounter[i];
		myvelocity[i] = pvelocity[i];
	}

	mydt = getDt();

	if(calibration_mode == CALIB_INIT)
	{
		//Set target to current position.
		target[0]= ( (float)pcounter[0])*PPR_TO_DISTANCE_X;//counterToPositionX(mycounter[0]);
		target[1]= ( (float)pcounter[1])*PPR_TO_DISTANCE_Y;
		target_v[0]= 0;
		target_v[1]= -calib_speed_y;
		calibration_mode = CALIB_MOVE_DOWN;
		wait_time=1.f;

		calib_failed=0;
//		wait_time=1.5f;
//		calibration_mode = CALIB_BEEP;
	}


/*	if( !isCalibrating() )
	{
		return;
	}*/


	switch(calibration_mode)
	{
		case CALIB_MOVE_DOWN:
		{
			wait_time -= mydt;
			if(wait_time<=0)
			{
				target_v[1]=calib_speed_y;
				calibration_mode = CALIB_MOVE_UP;
				wait_time=20;//max 10 seconds up... Who knows, maybe that pulley thing is not connected...
				break;
			}

			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_MOVE_UP:
		{
			wait_time -= mydt;
			if(wait_time<=0 || my_limit_status & LIMIT_Y_UP || fabs(calibGetDeltaY())>.08f )
			{

				if(wait_time<=0)calib_failed=1;

				target_v[0]=-calib_speed;
				target[1]-=.025f;
				target_v[1]=0;
				calibration_mode = CALIB_MOVE_LEFT_IF_NECESSARY;
				wait_time=10.f;
				break;
			}

			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_MOVE_LEFT_IF_NECESSARY:
		{
			wait_time -= mydt;
			if(!( my_limit_status & LIMIT_MAXRIGHT) || wait_time<=0 )
			{
				if(wait_time<=0)calib_failed=1;

				wait_time=10.f;
				target_v[0]= calib_speed;
//				target_v[1]= - calib_speed_y;
				calibration_mode = CALIB_MOVE_RIGHT;
				break;
			}

			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_MOVE_RIGHT:
		{
			wait_time -= mydt;
			if( my_limit_status & LIMIT_MAXRIGHT || wait_time<=0)
			{
				if(wait_time<=0)calib_failed=1;

				wait_time = 10.f;
				target_v[0]=0;//-calib_speed;
				calibration_mode = CALIB_MOVE_LEFT;

				counter_limit_right = pcounter[0];
				break;
			}

			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;


		case CALIB_MOVE_LEFT:
		{
			wait_time -= mydt;
			if( my_limit_status & LIMIT_MAXLEFT || wait_time<=0)
			{
				if(wait_time<=0)calib_failed=1;

				wait_time=10.f;
				target_v[0]=0;//calib_speed;
				calibration_mode = CALIB_MOVE_CENTER;
				counter_limit_left = pcounter[0];
				counter_center = (counter_limit_left+counter_limit_right)/2;
				break;
			}

			moveTarget();
			if(wait_time<9.75f)target_v[0]=-calib_speed;
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_MOVE_CENTER:
		{
			wait_time -= mydt;
			if(pcounter[0]>=counter_center || wait_time<=0)
			{
				if(wait_time<=0)calib_failed=1;


				target_v[0]=0.f;
				target_v[1]=-calib_speed_y;
				calibration_mode = CALIB_MOVE_DOWN_AGAIN;
				resetCounter(0);
				target[0]=0;
//				wait_time=1;
//				wait_time = 1/calib_speed_y; //Go down 1 meter.
				wait_time = LIMIT_Y_UP_VALUE/calib_speed_y; //Go down 1 meter.

				break;
			}

			moveTarget();
			if(wait_time<9.75f)target_v[0]=calib_speed;

			computePD(pcounter, pvelocity, rPWM);
		}break;



		case CALIB_MOVE_DOWN_AGAIN:
		{
			wait_time -= mydt;
			if(wait_time<=0)
			{
				target_v[1]=0;
				calibration_mode = CALIB_MEASURE_THETA;
				wait_time=10;
				resetCounter(1);
				target[1]=0;
//				resetCounter(2);
				wait_time=5.f;	//wait 5 seconds and measure min/max on theta.


				break;
			}

			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_MEASURE_THETA:
		{
			wait_time -= mydt;
			if(wait_time<=0)
			{
				wait_time=1.5f;
				calibration_mode = CALIB_BEEP;
				int32_t middle = (theta_min + theta_max)/2;

				setCounter(2, pcounter[2] - middle);
				break;
			}

			if(wait_time>4.5f)
			{
				theta_min=pcounter[2];
				theta_max=theta_min;
			}
			else
			{
				int32_t theta=pcounter[2];
				if(theta<theta_min)theta_min=theta;
				if(theta>theta_max)theta_max=theta;
			}

			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_BEEP:
		{
			float k_mul = 1/(5000.f*mydt);
			wait_time -= mydt;
			if(wait_time<=0)
			{
				rPWM[0]=0;
				rPWM[1]=0;

				if(calib_failed)
				{
					calibration_mode = CALIB_ERROR;
					rPWM[0]=0;
					rPWM[1]=0;
					break;
				}
				else
				{
					calibration_mode = CALIB_DONE;
					rPWM[0]=0;
					rPWM[1]=0;
					break;
				}
			}

			static uint8_t beep_up=0;
			computePD(pcounter, pvelocity, rPWM);

			if(calib_failed)
			{
				if( (uint16_t)(wait_time*10)%2==0)
				{
					beep_up = (beep_up+1)%6; //Beep 5 times per second

					if(beep_up>=3)
					{
						rPWM[1]+=7000*k_mul;
						rPWM[0]+=7000*k_mul;
					}
					else
					{
						rPWM[1]+=-7000*k_mul;
						rPWM[0]+=-7000*k_mul;
					}
				}
				else
				{
					rPWM[1]=0;
					rPWM[0]=0;
				}
			}
			else
			{
				if(wait_time>1.f)
				{
					beep_up = (beep_up+1)%8;

					if(beep_up>=4)
					{
						rPWM[1]+=7000*k_mul;
						rPWM[0]+=7000*k_mul;
					}
					else
					{
						rPWM[1]+=-7000*k_mul;
						rPWM[0]+=-7000*k_mul;
					}
					break;
				}
				if(wait_time>.5f)
				{
					beep_up = (beep_up+1)%6;

					if(beep_up>=3)
					{
						rPWM[1]+=7000*k_mul;
						rPWM[0]+=7000*k_mul;
					}
					else
					{
						rPWM[1]+=-7000*k_mul;
						rPWM[0]+=-7000*k_mul;
					}
					break;
				}
				else
				{
					beep_up = (beep_up+1)%4;

					if(beep_up>=2)
					{
						rPWM[1]+=7000*k_mul;
						rPWM[0]+=7000*k_mul;
					}
					else
					{
						rPWM[1]+=-7000*k_mul;
						rPWM[0]+=-7000*k_mul;
					}
				}
			}

		}break;


		case CALIB_DEMO_BEGIN:
		{
			target[0]= ( (float)pcounter[0])*PPR_TO_DISTANCE_X;//counterToPositionX(mycounter[0]);
			target[1]= ( (float)pcounter[1])*PPR_TO_DISTANCE_Y;
			target_v[0]=0 ;//-calib_speed*.75f;
			target_v[1]= 0;
			calibration_mode = CALIB_DEMO_RIGHT;
			wait_time=10.f;
		}break;


		case CALIB_DEMO_RIGHT:
		{
			wait_time-=mydt;
		//	if(pcounter[0]> (int32_t)(0.8f*DISTANCE_TO_PPR_X) )
			if(wait_time<0 || my_limit_status & LIMIT_RIGHT)
			{
				target_v[0]=0;//-calib_speed*.75f;
				target_v[1]=0;
				calibration_mode = CALIB_DEMO_DOWN;
				wait_time=2.f;
				break;
			}

			if(wait_time<9.75f)target_v[0]=calib_speed*.75f;
			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_DEMO_DOWN:
		{
			wait_time-=mydt;
		//	if(pcounter[0]> (int32_t)(0.8f*DISTANCE_TO_PPR_X) )
			if(wait_time<0)
			{
				target_v[0]=0;//-calib_speed*.75f;
				target_v[1]=0;
				calibration_mode = CALIB_DEMO_LEFT;
				wait_time=10.f;
				break;
			}

			if(wait_time<1.75f)target_v[1]=-calib_speed_y*.75f;
			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_DEMO_LEFT:
		{
			wait_time-=mydt;

			if(wait_time<0 || my_limit_status &LIMIT_LEFT)
			{
				target_v[0]=0;
				target_v[1]=0;
				calibration_mode = CALIB_DEMO_UP;
				wait_time=2.f;
				break;
			}

			if(wait_time<9.75f)target_v[0]=-calib_speed*.75f;
			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

		case CALIB_DEMO_UP:
		{
			wait_time-=mydt;

			if(wait_time<0 )
			{
				target_v[0]=0;//-calib_speed*.75f;
				target_v[1]=0;
				calibration_mode = CALIB_DEMO_RIGHT;
				wait_time=10.f;
				break;
			}

			if(wait_time<1.75f)target_v[1]=calib_speed_y*.75f;
			moveTarget();
			computePD(pcounter, pvelocity, rPWM);
		}break;

	}

}
