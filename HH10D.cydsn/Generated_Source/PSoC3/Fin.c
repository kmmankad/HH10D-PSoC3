/*******************************************************************************
* File Name: Fin.c  
* Version 1.60
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "Fin.h"


/*******************************************************************************
* Function Name: Fin_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void Fin_Write(uint8 value) 
{
    uint8 staticBits = Fin_DR & ~Fin_MASK;
    Fin_DR = staticBits | ((value << Fin_SHIFT) & Fin_MASK);
}


/*******************************************************************************
* Function Name: Fin_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void Fin_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Fin_0, mode);
}


/*******************************************************************************
* Function Name: Fin_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Fin_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Fin_Read(void) 
{
    return (Fin_PS & Fin_MASK) >> Fin_SHIFT;
}


/*******************************************************************************
* Function Name: Fin_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Fin_ReadDataReg(void) 
{
    return (Fin_DR & Fin_MASK) >> Fin_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Fin_INTSTAT) 

    /*******************************************************************************
    * Function Name: Fin_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Fin_ClearInterrupt(void) 
    {
        return (Fin_INTSTAT & Fin_MASK) >> Fin_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */ 
