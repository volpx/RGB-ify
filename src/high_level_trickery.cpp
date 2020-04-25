#include "high_level_trickery.h"

void convert_HSL_RGB(const float H, const float S, const float L,
	uint8_t RGB[3]){
	// implementation from:
	// https://www.rapidtables.com/convert/color/hsl-to-rgb.html
	memset(RGB,0,3);
	if (H<0 || H>=2*M_PI ||
		S<0 || S > 1 ||
		L<0 || L>1){
		return;
	}
	float C{ (1-std::abs(2*L-1))*S };
	float X{ C*(1-std::abs( static_cast<float>(std::fmod(H/(M_PI/3),2))-1 ) ) };
	float m{ L-C/2 };
	uint8_t h{ static_cast<uint8_t>(H/(M_PI/3)) };
	switch(h){
		case 0:
			RGB[0]=static_cast<uint8_t>((C+m)*255);
			RGB[1]=static_cast<uint8_t>((X+m)*255);
			RGB[2]=static_cast<uint8_t>((0+m)*255);
			break;
		case 1:
			RGB[0]=static_cast<uint8_t>((X+m)*255);
			RGB[1]=static_cast<uint8_t>((C+m)*255);
			RGB[2]=static_cast<uint8_t>((0+m)*255);
			break;
		case 2:
			RGB[0]=static_cast<uint8_t>((0+m)*255);
			RGB[1]=static_cast<uint8_t>((C+m)*255);
			RGB[2]=static_cast<uint8_t>((X+m)*255);
			break;
		case 3:
			RGB[0]=static_cast<uint8_t>((0+m)*255);
			RGB[1]=static_cast<uint8_t>((X+m)*255);
			RGB[2]=static_cast<uint8_t>((C+m)*255);
			break;
		case 4:
			RGB[0]=static_cast<uint8_t>((X+m)*255);
			RGB[1]=static_cast<uint8_t>((0+m)*255);
			RGB[2]=static_cast<uint8_t>((C+m)*255);
			break;
		case 5:
			RGB[0]=static_cast<uint8_t>((C+m)*255);
			RGB[1]=static_cast<uint8_t>((0+m)*255);
			RGB[2]=static_cast<uint8_t>((X+m)*255);
			break;
	}
}
