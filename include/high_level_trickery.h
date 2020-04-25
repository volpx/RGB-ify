#ifndef __HIGH_LEVEL_TRICKERY__
#define __HIGH_LEVEL_TRICKERY__

extern "C"{
	#include "low_level_communication.h"
}

#include <cmath>

/*
 * convert from the HSL colorspace to 3 RGB value
 * H is hue 		0 <= H < 2pi
 * S is saturation 	0 <= S <= 1
 * L is luminance 	0 <= L <= 1
 */
void convert_HSL_RGB(const float H, const float S, const float L,
	uint8_t RGB[]);

#endif // __HIGH_LEVEL_TRICKERY__
