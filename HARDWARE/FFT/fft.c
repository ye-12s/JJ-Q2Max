#include "math.h"
#include "fft.h"
#include "stdlib.h"
#include <stdbool.h>

// 16 point FFT
const unsigned short  N	= 16;
#define PI	3.141
uint8_t  m_rand;
int REX[N];
int IMX[N];
uint16_t MAG[N];
uint8_t led_buf[8];
extern unsigned char g_fft_frame_flag;

extern    volatile unsigned short   g_Combo_Max_value;
extern    volatile unsigned short   g_Combo_count;
extern    volatile uint32_t         g_Combo_num;
extern    volatile uint8_t          prew_ch;
extern    volatile uint8_t          m_combo_mode;
extern    bool                      g_Combo_flag;  
extern    volatile uint8_t          m_combo_buf[2];

uint8_t  fft_buf[9] = {
                                 0xfc,
                                 0x55,
                                 0x00,
                                 0x02,
                                 0x00,
                                 0x01,
                                 0x22,					//32
                                 0x01,
                                 0x5a,
                              };
bool flag_fft_first;

#define PI2 6.28318530717959

void fft(void)
{
	uint8_t nm1 = N - 1;
	uint8_t nd2 = N / 2;
	uint8_t m = log10(N)/log10(2);
	uint8_t j = nd2;
	uint8_t i, k, l;
	uint8_t le, le2;
	float ur, ui, sr, si;
	uint8_t jm1, ip;
	float tr, ti;

	for (i = 0; i <= nm1; i++)
	{
		IMX[i] = 0;
	}

	for (i = 1; i <= N-2; i++)
	{
			if (i >= j) goto a;
		
			tr = REX[j];
			ti = IMX[j];
			REX[j] = REX[i];
			IMX[j] = IMX[i];
			REX[i] = tr;
			IMX[i] = ti;
		
			a:
		
         k = nd2;
		
			b:
		
         if (k > j) goto c;
		
         j -= k;
         k /= 2;
		
         goto b;
			
			c:
			
         j += k;
	}

	for (l = 1; l <= m; l++)
	{
			le = pow(2, l);
			le2 = le / 2;
			ur = 1;
			ui = 0;

			sr = cos(PI/le2);
			si = -sin(PI/le2);

			for (j = 1; j <= le2; j++)
			{
					jm1 = j - 1;

					for (i = jm1; i <= nm1; i += le)
					{
							ip = i + le2;
							tr = REX[ip]*ur - IMX[ip]*ui;
							ti = REX[ip]*ui + IMX[ip]*ur;
							REX[ip] = REX[i] - tr;
							IMX[ip] = IMX[i] - ti;
							REX[i] = REX[i] + tr;
							IMX[i] = IMX[i] + ti;
					}
					tr = ur;
					ur = tr*sr - ui*si;
					ui = tr*si + ui*sr;
			}
	}
}

void mag_to_buf(void)
{
	uint8_t i;

	for (i = 0; i <= N/2; i++)
	{
		MAG[i] = sqrt(REX[i]*REX[i] + IMX[i]*IMX[i]);

	}

}

void FFT_Handle(void)
{
	 if((g_Combo_Max_value > 2)&&(g_Combo_count >70))
	 {
					if( m_combo_mode ==  0)
					{
	              fft_buf[7] = 2;
                m_combo_buf[1] =5;
						    m_combo_mode = 1;
						     g_Combo_Max_value=0;	
					    	 g_Combo_count = 0;
		             g_fft_frame_flag =1;
							    g_Combo_num ++;
						     g_Combo_flag =true;
				}
					else
					{
	             fft_buf[7] = 3;
               m_combo_buf[0] =4;
								m_combo_mode = 0;
						    g_Combo_Max_value=0;	
					    	g_Combo_count = 0;
		            g_fft_frame_flag =1;
						    g_Combo_num ++;
						    g_Combo_flag =true;
					}
		}
	  else 
	  {
				m_rand = rand();
				fft_buf[7]=(m_rand %6 )+1;
			
			  if(fft_buf[7] == prew_ch)
				{
					   fft_buf[7] =  prew_ch%6+1;
				}

		    g_fft_frame_flag =1;
			
			  prew_ch = fft_buf[7]; 
  }
}


