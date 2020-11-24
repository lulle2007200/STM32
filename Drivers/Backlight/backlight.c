#include "backlight.h"
#include "is31fl3733.h"


typedef struct vrgb_s{
	vled_t R;
	vled_t G;
	vled_t B;
}vrgb_t;


static const vrgb_t gVLEDMap[LED_MATRIX_HEIGHT][LED_MATRIX_WIDTH] = LED_MAP;

void BacklightLEDSetColor(uint8_t pPosX, uint8_t pPosY, uint32_t pColor){
	Is31fl3733LEDSetBrightness(gVLEDMap[pPosY][pPosX].R.Index,
							   gVLEDMap[pPosY][pPosX].R.CS, 
							   gVLEDMap[pPosY][pPosX].R.SW, 
							   RGB_GET_RED(pColor));
	Is31fl3733LEDSetBrightness(gVLEDMap[pPosY][pPosX].R.Index,
							   gVLEDMap[pPosY][pPosX].G.CS, 
							   gVLEDMap[pPosY][pPosX].G.SW, 
							   RGB_GET_GREEN(pColor));
	Is31fl3733LEDSetBrightness(gVLEDMap[pPosY][pPosX].B.Index,
							   gVLEDMap[pPosY][pPosX].B.CS, 
							   gVLEDMap[pPosY][pPosX].B.SW, 
							   RGB_GET_BLUE(pColor));
}

void BacklightSetColor(uint32_t pColor){
	for(uint8_t Row = 0; Row < LED_MATRIX_HEIGHT; Row++){
		for(uint8_t Col = 0; Col < LED_MATRIX_WIDTH; Col++){
			BacklightLEDSetColor(Col, Row, pColor);
		}
	}
}

void BacklightLEDEnable(uint8_t pPosX, uint8_t pPosY){
	Is31fl3733LEDEnable(gVLEDMap[pPosY][pPosX].R.Index, 
	                    gVLEDMap[pPosY][pPosX].R.CS,
	                    gVLEDMap[pPosY][pPosX].R.SW);
	Is31fl3733LEDEnable(gVLEDMap[pPosY][pPosX].G.Index, 
	                    gVLEDMap[pPosY][pPosX].G.CS,
	                    gVLEDMap[pPosY][pPosX].G.SW);
	Is31fl3733LEDEnable(gVLEDMap[pPosY][pPosX].B.Index, 
	                    gVLEDMap[pPosY][pPosX].B.CS,
	                    gVLEDMap[pPosY][pPosX].B.SW);
}

void BacklightLEDDisable(uint8_t pPosX, uint8_t pPosY){
	Is31fl3733LEDDisable(gVLEDMap[pPosY][pPosX].R.Index, 
	                    gVLEDMap[pPosY][pPosX].R.CS,
	                    gVLEDMap[pPosY][pPosX].R.SW);
	Is31fl3733LEDDisable(gVLEDMap[pPosY][pPosX].R.Index, 
	                    gVLEDMap[pPosY][pPosX].G.CS,
	                    gVLEDMap[pPosY][pPosX].G.SW);
	Is31fl3733LEDDisable(gVLEDMap[pPosY][pPosX].B.Index, 
	                    gVLEDMap[pPosY][pPosX].B.CS,
	                    gVLEDMap[pPosY][pPosX].B.SW);
}

void BacklightLEDToggle(uint8_t pPosX, uint8_t pPosY){
	Is31fl3733LEDToggle(gVLEDMap[pPosY][pPosX].R.Index, 
	                    gVLEDMap[pPosY][pPosX].R.CS,
	                    gVLEDMap[pPosY][pPosX].R.SW);
	Is31fl3733LEDToggle(gVLEDMap[pPosY][pPosX].G.Index, 
	                    gVLEDMap[pPosY][pPosX].G.CS,
	                    gVLEDMap[pPosY][pPosX].G.SW);
	Is31fl3733LEDToggle(gVLEDMap[pPosY][pPosX].B.Index, 
	                    gVLEDMap[pPosY][pPosX].B.CS,
	                    gVLEDMap[pPosY][pPosX].B.SW);
}

void BacklightDisable(){
	for(uint8_t Row = 0; Row < LED_MATRIX_HEIGHT; Row++){
		for(uint8_t Col = 0; Col < LED_MATRIX_WIDTH; Col++){
			BacklightLEDDisable(Col, Row);
		}
	}
}

void BacklightEnable(){
	for(uint8_t Row = 0; Row < LED_MATRIX_HEIGHT; Row++){
		for(uint8_t Col = 0; Col < LED_MATRIX_WIDTH; Col++){
			BacklightLEDEnable(Col, Row);
		}
	}
}

void BacklightToggle(){
	for(uint8_t Row = 0; Row < LED_MATRIX_HEIGHT; Row++){
		for(uint8_t Col = 0; Col < LED_MATRIX_WIDTH; Col++){
			BacklightLEDToggle(Col, Row);
		}
	}
}

void BacklightUpdate(){
	Is31fl3733UpdateMatrix(0);
	Is31fl3733UpdateMatrix(1);
}

void BacklightInit(void){
	Is31fl3733Init();
	Is31fl3733Enable();
}

