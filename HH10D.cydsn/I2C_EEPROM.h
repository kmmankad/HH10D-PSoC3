/* Interfacing 24LC512 with a PSoC3 via I2C
 Author : Kartik Mankad
 Date : 06-Nov-2011
 This code is licensed as CC-BY-SA 3.0
 Description : All Read and Write modes mentioned in the 
 			   Datasheet have been implemented.
 Note:	No need to send CONTROL BYTEs explicity,since they are included 
		in the start functions.
 ****Check Addressing for the EEPROM and comment where marked
 Tested with 24LC512 with 4.7k pullups.

*/

//Read Functions
uint8 EEPROM_RandomRead(uint8 SlaveAddress, int rAddress);
uint8 EEPROM_CurrentRead(uint8 SlaveAddress);
void EEPROM_SeqRead(uint8 SlaveAddress, int rAddress,uint8 *RxData);

//Write Function
uint8 EEPROM_WriteByte(uint8 SlaveAddress, int wAddress, uint8 wData);
uint8 EEPROM_WritePage(uint8 SlaveAddress, int wAddress, uint8 *wData);



uint8 EEPROM_CurrentRead(uint8 SlaveAddress){
	uint8 result;
	
	result=I2C_MasterSendStart(SlaveAddress,I2C_READ_XFER_MODE); //I2C Start,Read mode
	if(result == I2C_MSTR_NO_ERROR) //Check if transfer completed without errors 
	{
		result = I2C_MasterReadByte(I2C_NAK_DATA);// Read the data (NO acknowledge)
		I2C_MasterSendStop();//Send Stop
	}
	return result;
}

uint8 EEPROM_RandomRead(uint8 SlaveAddress, int rAddress) {
	uint8 result;
	
	result=I2C_MasterSendStart(SlaveAddress,I2C_WRITE_XFER_MODE);  //I2C Start,Write mode
	if(result == I2C_MSTR_NO_ERROR) // Check if transfer completed without errors 
	{
		//***Comment out next line for 8bit adressing
       // result=I2C_MasterWriteByte((uint8)(rAddress >> 8));// send Higher address byte 
 	    result=I2C_MasterWriteByte((uint8)(rAddress & 0xFF));// send Lower address byte
		
		result=I2C_MasterSendRestart(SlaveAddress,I2C_READ_XFER_MODE);//Issue Restart,Read Mode
 		result = I2C_MasterReadByte(I2C_NAK_DATA);// Read the data (NO Ack)
		
		I2C_MasterSendStop();//Send Stop
 	}
 	return result;
 }
 
void EEPROM_SeqRead(uint8 SlaveAddress, int rAddress,uint8 *RxData) {
	uint8 i,result;
	
	result=I2C_MasterSendStart(SlaveAddress,I2C_WRITE_XFER_MODE);  //I2C Start,Write mode

	 if(result == I2C_MSTR_NO_ERROR) // Check if transfer completed without errors 
	{
		//***Comment out next line for 8bit adressing
       	//result=I2C_MasterWriteByte((uint8)(rAddress >> 8));// send Higher address byte
 	    result=I2C_MasterWriteByte((uint8)(rAddress & 0xFF));// send Lower address byte
		
		result=I2C_MasterSendRestart(SlaveAddress,I2C_READ_XFER_MODE);//Issue Restart,Read Mode
 		
		for(i=0;i<126;i++){
 		*RxData++ = I2C_MasterReadByte(I2C_ACK_DATA);     // Read the data,with acknowledge
		}
		*RxData=I2C_MasterReadByte(I2C_NAK_DATA); //Read Final Byte,127th without Ack
		I2C_MasterSendStop();//Send Stop
 	}

 }


uint8 EEPROM_WriteByte(uint8 SlaveAddress, int wAddress, uint8 wData) {
	uint8 result;
	
	result=I2C_MasterSendStart(SlaveAddress,I2C_WRITE_XFER_MODE);  //I2C Start signal,Write mode
	if(result == I2C_MSTR_NO_ERROR) /* Check if transfer completed without errors */
	{
		//***Comment out next line for 8bit adressing
       // result=I2C_MasterWriteByte((uint8)(wAddress >> 8));// send Higher address byte
 	    result=I2C_MasterWriteByte((uint8)(wAddress & 0xFF));// send Lower address byte
        result=I2C_MasterWriteByte(wData);// send data to be written
		I2C_MasterSendStop();//Send Stop
    }
	return result;
} 

uint8 EEPROM_WritePage(uint8 SlaveAddress, int wAddress, uint8 *wData){
	uint8 result,i;
	
	result=I2C_MasterSendStart(SlaveAddress,I2C_WRITE_XFER_MODE);  // issue I2C1 start signal,Write mode
	if(result == I2C_MSTR_NO_ERROR)// Check if transfer completed without errors 
	{
		//***Comment out next line for 8bit adressing
        //result=I2C_MasterWriteByte((uint8)(wAddress >> 8));// send Higher address byte
 	    result=I2C_MasterWriteByte((uint8)(wAddress & 0xFF));// send Lower address byte
      
		for(i=0;i<127;i++){//Write Page
		result=I2C_MasterWriteByte(*wData++);
		}
		
		I2C_MasterSendStop();//Send Stop
    }
	return result;
}
