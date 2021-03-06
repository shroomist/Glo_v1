/**
 ******************************************************************************
 * File Name          : sinetable.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sinetable_h_
#define __sinetable_h_

#include <math.h>

#define SINETABLE_SIZE 1024
#define _2PI    6.283185307f
#define ALPHA	(SINETABLE_SIZE/_2PI)

extern float_t sinetable[1025];

#endif // __sinetable_h_

