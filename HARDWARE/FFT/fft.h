#ifndef _FFT_H
#define _FFT_H
#include "sys.h"

//extern long lBufInArray[];
//extern long lBufOutArray[];
//extern long lBufMagArray[];

//extern void GetPowerMag(void);
//extern void InitBufInArray(void);
void fft(void);
void mag_to_buf(void);
void FFT_Handle(void);

#endif

