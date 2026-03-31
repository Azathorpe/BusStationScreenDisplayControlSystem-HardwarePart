#include "stm32f10x.h"
#include "Serial.h"
#include "OLED.h"

int main(){
	Serial_Init();
	OLED_Init();
	
	OLED_ShowString(1,1,"Hello World");
	Serial_SendString("你好 我的爱人");
	while(1){
		
	}
}
