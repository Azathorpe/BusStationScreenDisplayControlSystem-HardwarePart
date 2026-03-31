#include "stm32f10x.h"
#include "Serial.h"
#include "OLED.h"
#include "string.h"

int main(){
	Serial_Init();
	OLED_Init();
	
	Serial_TxPacket[0] = 0xFD;
	Serial_TxPacket[1] = 0x03;
	Serial_TxPacket[2] = 0x2F;
	Serial_TxPacket[3] = 0x3D;
	
	Serial_SendPacket();
	
	OLED_ShowString(1,1,"Serial End...");
	OLED_ShowHexNum(2,1,Serial_TxPacket[0],4);
	//Serial_SendString("你好 我的爱人");
	while(1){
		if (Serial_RxFlag == 1)
		{
			OLED_ShowString(4, 1, "                ");
			OLED_ShowString(4, 1, Serial_RxPacket);
			
			if (strcmp(Serial_RxPacket, "LED_ON") == 0)
			{
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_ON_OK");
			}
			else if (strcmp(Serial_RxPacket, "LED_OFF") == 0)
			{
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "LED_OFF_OK");
			}
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2, 1, "                ");
				OLED_ShowString(2, 1, "ERROR_COMMAND");
			}
			
			Serial_RxFlag = 0;
		}
	}
}
