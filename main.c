#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_adc.h"              // Keil::Drivers:ADC
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup


#define ON1  PORT_SetBits (MDR_PORTA, PORT_Pin_7)
#define OFF1 PORT_ResetBits (MDR_PORTA, PORT_Pin_7)

#define ON2  PORT_SetBits (MDR_PORTA, PORT_Pin_4)
#define OFF2 PORT_ResetBits (MDR_PORTA, PORT_Pin_4)

#define ON3  PORT_SetBits (MDR_PORTA, PORT_Pin_5)
#define OFF3 PORT_ResetBits (MDR_PORTA, PORT_Pin_5)

#define ON4  PORT_SetBits (MDR_PORTB, PORT_Pin_0)
#define OFF4 PORT_ResetBits (MDR_PORTB, PORT_Pin_0)

#define ON5  PORT_SetBits (MDR_PORTB, PORT_Pin_2)
#define OFF5 PORT_ResetBits (MDR_PORTB, PORT_Pin_2)

#define ON6  PORT_SetBits (MDR_PORTB, PORT_Pin_1)
#define OFF6 PORT_ResetBits (MDR_PORTB, PORT_Pin_1)

#define ON7  PORT_SetBits (MDR_PORTC, PORT_Pin_0)
#define OFF7 PORT_ResetBits (MDR_PORTC, PORT_Pin_0)

#define ON8  PORT_SetBits (MDR_PORTC, PORT_Pin_1)
#define OFF8 PORT_ResetBits (MDR_PORTC, PORT_Pin_1)

#define ADC_PRESC 227

void Init_LED(void)
{
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
	
	PORT_InitTypeDef PORT_InitStruct;
	PORT_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStruct.PORT_OE = PORT_OE_OUT;
	PORT_InitStruct.PORT_Pin = PORT_Pin_7+PORT_Pin_4+PORT_Pin_5;                //указать пины, доинициализировать порты если надо 
	PORT_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORT_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PORT_Init(MDR_PORTA, &PORT_InitStruct);
	PORT_InitStruct.PORT_Pin = PORT_Pin_0+PORT_Pin_2+PORT_Pin_1;
	PORT_Init(MDR_PORTB, &PORT_InitStruct);
	PORT_InitStruct.PORT_Pin = PORT_Pin_0+PORT_Pin_1;
	PORT_Init(MDR_PORTC, &PORT_InitStruct);
	
}
void Init_ADC()
{
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
	PORT_InitTypeDef PORT_InitStruct;
	PORT_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	//PORT_InitStruct.PORT_FUNC = PORT_FUNC_PORT;   //Нужно ли(не включит ли цифровой режим????7)
	PORT_InitStruct.PORT_MODE = PORT_MODE_ANALOG;
	PORT_InitStruct.PORT_OE = PORT_OE_IN;
	PORT_InitStruct.PORT_Pin = PORT_Pin_7;                
	PORT_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORT_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PORT_Init(MDR_PORTD, &PORT_InitStruct);
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_ADC, ENABLE);
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_SynchronousMode = ADC_SyncMode_Independent;
	ADC_InitStruct.ADC_StartDelay = 0;
	ADC_InitStruct.ADC_TempSensor = ADC_TEMP_SENSOR_AMPLIFIER_Disable;
	ADC_InitStruct.ADC_IntVRefConversion = ADC_VREF_CONVERSION_Disable;
	ADC_InitStruct.ADC_IntVRefTrimming = 1;
	ADC_Init(&ADC_InitStruct);
	
	ADCx_InitTypeDef ADC1_InitStruct;
	ADC1_InitStruct.ADC_ClockSource = ADC_CLOCK_SOURCE_CPU;
	ADC1_InitStruct.ADC_SamplingMode = ADC_SAMPLING_MODE_CICLIC_CONV;
	ADC1_InitStruct.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;
	ADC1_InitStruct.ADC_ChannelNumber = ADC_CH_ADC7; //Точно ли этот канал??
	ADC1_InitStruct.ADC_Channels = 0;
	ADC1_InitStruct.ADC_LevelControl = ADC_LEVEL_CONTROL_Enable;
	ADC1_InitStruct.ADC_LowLevel = 0;
	ADC1_InitStruct.ADC_HighLevel = ADC_VALUE_MAX;
	ADC1_InitStruct.ADC_VRefSource = ADC_VREF_SOURCE_INTERNAL;
	ADC1_InitStruct.ADC_IntVRefSource = ADC_INT_VREF_SOURCE_INEXACT;
	ADC1_InitStruct.ADC_Prescaler = ADC_CLK_div_32768;
	ADC1_InitStruct.ADC_DelayGo = 0xF;
	ADC1_Init(&ADC1_InitStruct);
	
	ADC1_SetChannel(ADC_CH_ADC7);
	ADC1_Cmd(ENABLE);
}



void setLEDs(uint32_t result) {
    // Проверить значение переменной result и включить светодиоды соответственно
		result /= 455;
		OFF1; OFF2; OFF3; OFF4; OFF5; OFF6; OFF7; OFF8;
		//ON1; ON2; ON3; ON4; ON5; ON6; ON7; ON8;
    switch(result)
		{
			///case 8: ON1; ON2; ON3; ON4; ON5; ON6; ON7; ON8;
			case 7: ON6;break;
			case 6: ON6; ON5;break;
			case 5: ON6; ON5; ON4;break;
			case 4: ON6; ON5; ON4; ON3;break;
			case 3: ON6; ON5; ON4; ON3; ON2;break;
			case 2: ON6; ON5; ON4; ON3; ON2;ON1;break;
			case 1: ON6; ON5; ON4; ON3; ON2;ON1;ON8;break;
			case 0: ON6; ON5; ON4; ON3; ON2;ON1;ON8;ON7; break;
		
			
		}
	
}

int main(void)
{
	 
	Init_LED();
	Init_ADC();
	uint32_t data;
	//ON1; ON2; ON3; ON4; ON5; ON6; ON7; ON8;
	//ADC1_Start();
	while(1){
		ADC1_Start();
	while(!ADC_GetFlagStatus(ADC1_FLAG_END_OF_CONVERSION))
			{}
				data = (MDR_ADC -> ADC1_RESULT) & 0x0FFF;
				setLEDs(data);
				//ON1; ON2; ON3; ON4;
			
			
	}
}
