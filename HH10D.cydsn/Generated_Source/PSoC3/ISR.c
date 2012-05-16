/*******************************************************************************
* File Name: ISR.c  
* Version 1.50
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#include <CYDEVICE.H>
#include <CYDEVICE_TRM.H>
#include <CYLIB.H>
#include <ISR.H>


/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START ISR_intc` */

/* `#END` */


/*******************************************************************************
* Function Name: ISR_Start
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   void.
*
*
* Return:
*   void.
*
*******************************************************************************/
void ISR_Start(void)
{
    /* For all we know the interrupt is active. */
    ISR_Disable();

    /* Set the ISR to point to the ISR Interrupt. */
    ISR_SetVector(ISR_Interrupt);

    /* Set the priority. */
    ISR_SetPriority(ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Enable();
}

/*******************************************************************************
* Function Name: ISR_StartEx
********************************************************************************
* Summary:
*  Set up the interrupt and enable it.
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*******************************************************************************/
void ISR_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    ISR_Disable();

    /* Set the ISR to point to the ISR Interrupt. */
    ISR_SetVector(address);

    /* Set the priority. */
    ISR_SetPriority(ISR_INTC_PRIOR_NUMBER);

    /* Enable it. */
    ISR_Enable();
}

/*******************************************************************************
* Function Name: ISR_Stop
********************************************************************************
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
void ISR_Stop(void) 
{
    /* Disable this interrupt. */
    ISR_Disable();
}

/*******************************************************************************
* Function Name: ISR_Interrupt
********************************************************************************
* Summary:
*   The default Interrupt Service Routine for ISR.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
*
*
* Parameters:  
*
*
* Return:
*   void.
*
*******************************************************************************/
CY_ISR(ISR_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START ISR_Interrupt` */

    /* `#END` */

    /* PSoC3 ES1, ES2 RTC ISR PATCH  */ 
    #if(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3)
        #if((CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2) && (ISR__ES2_PATCH ))      
            ISR_ISR_PATCH();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: ISR_SetVector
********************************************************************************
* Summary:
*   Change the ISR vector for the Interrupt. Note calling ISR_Start
*   will override any effect this method would have had. To set the vector before
*   the component has been started use ISR_StartEx instead.
*
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_SetVector(cyisraddress address) 
{
    CY_SET_REG16(ISR_INTC_VECTOR, (uint16) address);
}

/*******************************************************************************
* Function Name: ISR_GetVector
********************************************************************************
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*
*******************************************************************************/
cyisraddress ISR_GetVector(void) 
{
    return (cyisraddress) CY_GET_REG16(ISR_INTC_VECTOR);
}

/*******************************************************************************
* Function Name: ISR_SetPriority
********************************************************************************
* Summary:
*   Sets the Priority of the Interrupt. Note calling ISR_Start
*   or ISR_StartEx will override any effect this method would have had. 
*	This method should only be called after ISR_Start or 
*	ISR_StartEx has been called. To set the initial
*	priority for the component use the cydwr file in the tool.
*
*
* Parameters:
*   priority: Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_SetPriority(uint8 priority) 
{
    *ISR_INTC_PRIOR = priority << 5;
}

/*******************************************************************************
* Function Name: ISR_GetPriority
********************************************************************************
* Summary:
*   Gets the Priority of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   Priority of the interrupt. 0 - 7, 0 being the highest.
*
*
*******************************************************************************/
uint8 ISR_GetPriority(void) 
{
    uint8 priority;


    priority = *ISR_INTC_PRIOR >> 5;

    return priority;
}

/*******************************************************************************
* Function Name: ISR_Enable
********************************************************************************
* Summary:
*   Enables the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_Enable(void) 
{
    /* Enable the general interrupt. */
    *ISR_INTC_SET_EN = ISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_GetState
********************************************************************************
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   1 if enabled, 0 if disabled.
*
*
*******************************************************************************/
uint8 ISR_GetState(void) 
{
    /* Get the state of the general interrupt. */
    return (*ISR_INTC_SET_EN & ISR__INTC_MASK) ? 1:0;
}

/*******************************************************************************
* Function Name: ISR_Disable
********************************************************************************
* Summary:
*   Disables the Interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_Disable(void) 
{
    /* Disable the general interrupt. */
    *ISR_INTC_CLR_EN = ISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_SetPending
********************************************************************************
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_SetPending(void) 
{
    *ISR_INTC_SET_PD = ISR__INTC_MASK;
}

/*******************************************************************************
* Function Name: ISR_ClearPending
********************************************************************************
* Summary:
*   Clears a pending interrupt.
*
* Parameters:
*   void.
*
*
* Return:
*   void.
*
*
*******************************************************************************/
void ISR_ClearPending(void) 
{
    *ISR_INTC_CLR_PD = ISR__INTC_MASK;
}
