/* Interfacing HH10D with a PSoC3
 Author : Kartik Mankad
 Date : 12-Nov-2011
 This code is licensed as CC-BY-SA 3.0
 Description : Humidity Measurement using HH10D sensor.
 Operation:
 			1.Read Sensitivity and Offset Constants from EEPROM
				-I2C Speed 400kbits/sec,
				-P0[0] - SCL
				-P0[1] - SDA
			2.Measure Frequency using Counter.
				-Counter Set as 16bit,UDB,Up Counter,Reload on Capture,Interrupt on Capture.
				-Freq input at P0[2]
			3.Use the above data to calculate RH using RH=(offset-frequency)*sens/2^12
			4.Display the formatted RH on the LCD.
			
 This code has been tested with:
  Hardware: CY8CKIT-030 with HH10 module from www.sparkfun.com
  Software: PSoC Creator 2.1 with cy_boot 3.0
 Note: 8bit addressing has been enabled in the I2C_EEPROM.h,by commenting out MSByte lines.
*/
#include <device.h>
#include <stdio.h>
#include "I2C_EEPROM.h"//Uses I2C EEPROM Functions to Read.
					  //8bit Addressing.

//Slave Address of the EEPROM,in decimal.
#define SLAVE_ADDR 81 /* 7bit slave address,1010 001. 001 because of A0 high,A1 & A2 low.
					     See Schematic in Datasheet. */

//Global Variable to hold the Period of the Sq. Wave.
uint16 period=0;

//Function to Calculate Humidity from Sensitivity and Offset values.
float GetHum(uint8 sensmsb,uint8 senslsb,uint8 offmsb,uint8 offlsb);

//Interrupt Service Routine for Period Measurement.
CY_ISR(Cap){
    //IMPORTANT To do a ReadStatusRegister call,since that clears interrupt flag.
    Counter_ReadStatusRegister();// This will clear the interrupt if set.
    period=Counter_ReadCapture();//Read the Capture Value.
    /*Capture value will give us the period of the sq. wave.
    in microseconds. */
}


void main(){
	//Variable to hold Calculated Humidity Value.
	float Hum;
	
	/*Variables to hold Sensitivity 
	and Offset MSB,LSB Values read from the EEPROM. */
	uint8 sensmsb,senslsb,offmsb,offlsb;
	
	//Character array to hold the Display Text.
	char displayStr[15] = {'\0'};
	
   /*Disable Interrupts to prevent accidental triggering
   while setting up.*/
   CYGlobalIntDisable;
   
   LCD_Start(); //Start LCD .
   
   LCD_PrintString("HH10D Demo");
   CyDelay(1000);
   LCD_ClearDisplay();
   
   ISR_Start();//Start ISR.
   ISR_SetVector(Cap);//Set ISR Vector to above written function.
   Counter_Start();//Start Counter.
   
   I2C_Start(); //Start I2C.
   
   /*Read Sensitivity and Offset Values 
   Sensitivity is a 2byte value stored at 0x0A
   Offset is a 2byte value stored at 0x0C .*/
   sensmsb=EEPROM_RandomRead(SLAVE_ADDR,0x0A);
   senslsb=EEPROM_RandomRead(SLAVE_ADDR,0x0B);
   offmsb=EEPROM_RandomRead(SLAVE_ADDR,0x0C);
   offlsb=EEPROM_RandomRead(SLAVE_ADDR,0x0D);
   
   CYGlobalIntEnable; //Enable Global Interrupts.
   
   /*We enable it only after setting up,since we
   dont want any interruption in I2C reads.*/
    	
	for(;;){
	LCD_ClearDisplay();//Clear Previously Printed Result
	Hum=GetHum(sensmsb,senslsb,offmsb,offlsb);//Calculate Humidity
	sprintf(displayStr,"RH=%4.2f",Hum);//Format to a RH=XX.XX output
	LCD_PrintString(displayStr);//Display formatted string.
	LCD_PrintString("%");//Print % sign.
	CyDelay(100);//Cool off for a bit.
	}
}

//Function to Calculate Humidity from Sensitivity and Offset values.
float GetHum(uint8 sensmsb,uint8 senslsb,uint8 offmsb,uint8 offlsb){
	//Get Proper 16bit values for Sens and Offset.
	uint16 sens=((uint16)senslsb | (uint16)sensmsb<<8);//Get Sensitivity,was 395 for my module.
	uint16 off=((uint16)offlsb | (uint16)offmsb<<8);//Get offset,was 7728 for my module.
	float freq=(1/((float)period))*1000000;//Get Frequency in Hz,from period in microsec.
	
	float RH=((off-freq)*sens)/4096;//Apply the formula given in the datasheet.
	
	return(RH);
}


