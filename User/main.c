#include "stm32f10x.h"
#include "Serial.h"

int main(){
	
	Serial_Init();
	Serial_SendString("你好 我的爱人");
	while(1){
		
	}
}
