#include "stm32f10x.h"
#include "Serial.h"
#include "OLED.h"
#include "string.h"
#include "Delay.h"

typedef struct {
	char *BusID;
	char *StartTime;
	uint16_t Ticket;
	char *Statue;
}Bus;

int main(){
	Serial_Init();
	OLED_Init();
	
	Serial_TxPacket[0] = 0xFD;
	Serial_TxPacket[1] = 0x03;
	Serial_TxPacket[2] = 0x2F;
	Serial_TxPacket[3] = 0x3D;
	
	Serial_SendPacket();
	
	Bus bus[4];
	
	//OLED_ShowString(1,1,"Serial End...");
	//OLED_ShowHexNum(2,1,Serial_TxPacket[0],4);
	Serial_SendString("你好 我的爱人");
	Serial_SendString("你好 我的爱人");
	while(1){
		//绘制边框
		//车次 - 0x01
		OLED_ShowCN(1,1,0,1);
		OLED_ShowCN(1,2,1,1);
		//发车时间 - 0x02
		OLED_ShowCN(1,4,2,1);
		OLED_ShowCN(1,5,3,1);
		OLED_ShowCN(1,6,4,1);
		OLED_ShowCN(1,7,5,1);
		
		//发送请求信息
		Serial_SendByte(0x02);
		//等待后端确认
		while (Serial_RxFlag != 1);
		if (strcmp(Serial_RxPacket, "CNT") == 0)
		{
			Serial_SendString("你好 我的爱人");
			Serial_SendString("LED_ON_OK\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "LED_ON_OK");
		}
		else
		{
			Serial_SendString("ERROR_COMMAND\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "ERROR_COMMAND");
		}
		Serial_RxFlag = 0;
		
		//发送请求数量
		Serial_SendString("Cnt:4");
		while (Serial_RxFlag != 1);
		if (strcmp(Serial_RxPacket, "WITCH") == 0)
		{
			Serial_SendString("LED_ON_OK\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "LED_ON_OK");
		}
		else
		{
			Serial_SendString("ERROR_COMMAND\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "ERROR_COMMAND");
		}
		Serial_RxFlag = 0;
		
		//报文格式 : 请求何 数量 请求何 数量
		Serial_TxPacket[0] = 0x01;
		Serial_TxPacket[1] = 0x02;
		Serial_TxPacket[2] = 0x03;
		Serial_TxPacket[3] = 0x04;
	
		Serial_SendPacket();
		//发送回来的数据格式: @(1)-(2)-(3)-(4)/r/n
		
		while (Serial_RxFlag != 1);
		if (strcmp(Serial_RxPacket, "") == 0)
		{
			Serial_SendString("LED_ON_OK\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "LED_ON_OK");
		}
		else
		{
			Serial_SendString("ERROR_COMMAND\r\n");
			OLED_ShowString(2, 1, "                ");
			OLED_ShowString(2, 1, "ERROR_COMMAND");
		}
		Serial_RxFlag = 0;
		
		Delay_s(5);
		
		//绘制边框
		//余票 - 0x03
		OLED_ShowCN(1,1,6,1);
		OLED_ShowCN(1,2,7,1);
		//状态 - 0x04
		OLED_ShowCN(1,4,8,1);
		OLED_ShowCN(1,5,9,1);
		
		
		Delay_s(5);
		
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
