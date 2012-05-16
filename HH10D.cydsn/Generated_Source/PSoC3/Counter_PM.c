/*******************************************************************************
* File Name: Counter_PM.c  
* Version 2.10
*
*  Description:
*     This file provides the power management source code to API for the
*     Counter.  
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "Counter.h"

static Counter_backupStruct Counter_backup;

/*******************************************************************************
* Function Name: Counter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
* Reentrant:
*    No
*
*******************************************************************************/
void Counter_SaveConfig(void)
{
    #if (!Counter_UsingFixedFunction)
        /* Backup the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (Counter_PSOC3_ES2 || Counter_PSOC5_ES1)
            Counter_backup.CounterUdb = Counter_ReadCounter();
            Counter_backup.CounterPeriod = Counter_ReadPeriod();
            Counter_backup.CompareValue = Counter_ReadCompare();
            Counter_backup.InterruptMaskValue = Counter_STATUS_MASK;
        #endif
        
        #if (Counter_PSOC3_ES3 || Counter_PSOC5_ES2)
            Counter_backup.CounterUdb = Counter_ReadCounter();
            Counter_backup.InterruptMaskValue = Counter_STATUS_MASK;
        #endif
        
        #if(!Counter_ControlRegRemoved)
            Counter_backup.CounterControlRegister = Counter_ReadControlRegister();
        #endif
    #endif
}

/*******************************************************************************
* Function Name: Counter_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_backup:  Variables of this global structure are used to restore 
*  the values of non retention registers on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void Counter_RestoreConfig(void) 
{      
    #if (!Counter_UsingFixedFunction)     
        /* Restore the UDB non-rentention registers for PSoC3 ES2 and PSoC5 ES1*/
        #if (Counter_PSOC3_ES2 || Counter_PSOC5_ES1)
            /* Interrupt State Backup for Critical Region*/
            uint8 Counter_interruptState;
        
            Counter_WriteCounter(Counter_backup.CounterUdb);
            Counter_WritePeriod(Counter_backup.CounterPeriod);
            Counter_WriteCompare(Counter_backup.CompareValue);
            /* Enter Critical Region*/
            Counter_interruptState = CyEnterCriticalSection();
        
            Counter_STATUS_AUX_CTRL |= Counter_STATUS_ACTL_INT_EN_MASK;
            /* Exit Critical Region*/
            CyExitCriticalSection(Counter_interruptState);
            Counter_STATUS_MASK = Counter_backup.InterruptMaskValue;
        #endif
        
        #if (Counter_PSOC3_ES3 || Counter_PSOC5_ES2)
            Counter_WriteCounter(Counter_backup.CounterUdb);
            Counter_STATUS_MASK = Counter_backup.InterruptMaskValue;
        #endif
        
        #if(!Counter_ControlRegRemoved)
            Counter_WriteControlRegister(Counter_backup.CounterControlRegister);
        #endif
    #endif
}


/*******************************************************************************
* Function Name: Counter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_backup.enableState:  Is modified depending on the enable state
*  of the block before entering sleep mode.
*
* Reentrant:
*  No
*
*******************************************************************************/
void Counter_Sleep(void)
{
    #if(!Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(Counter_CTRL_ENABLE == (Counter_CONTROL & Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            Counter_backup.CounterEnableState = 0u;
        }
    #endif
    Counter_Stop();
    Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: Counter_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
* Reentrant:
*  Yes
*
*******************************************************************************/
void Counter_Wakeup(void) 
{
    Counter_RestoreConfig();
    #if(!Counter_ControlRegRemoved)
        if(Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif
    
}


/* [] END OF FILE */
