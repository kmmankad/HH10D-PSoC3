/*******************************************************************************
* File Name: CountClk.h
* Version 1.60
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_CountClk_H)
#define CY_CLOCK_CountClk_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void CountClk_Start(void) ;
void CountClk_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void CountClk_StopBlock(void) ;
#endif

void CountClk_StandbyPower(uint8 state) ;
void CountClk_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 CountClk_GetDividerRegister(void) ;
void CountClk_SetModeRegister(uint8 modeBitMask) ;
void CountClk_ClearModeRegister(uint8 modeBitMask) ;
uint8 CountClk_GetModeRegister(void) ;
void CountClk_SetSourceRegister(uint8 clkSource) ;
uint8 CountClk_GetSourceRegister(void) ;
#if defined(CountClk__CFG3)
void CountClk_SetPhaseRegister(uint8 clkPhase) ;
uint8 CountClk_GetPhaseRegister(void) ;
#endif

#define CountClk_Enable()                       CountClk_Start()
#define CountClk_Disable()                      CountClk_Stop()
#define CountClk_SetDivider(clkDivider)         CountClk_SetDividerRegister(clkDivider, 1)
#define CountClk_SetDividerValue(clkDivider)    CountClk_SetDividerRegister((clkDivider) - 1, 1)
#define CountClk_SetMode(clkMode)               CountClk_SetModeRegister(clkMode)
#define CountClk_SetSource(clkSource)           CountClk_SetSourceRegister(clkSource)
#if defined(CountClk__CFG3)
#define CountClk_SetPhase(clkPhase)             CountClk_SetPhaseRegister(clkPhase)
#define CountClk_SetPhaseValue(clkPhase)        CountClk_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*           API Constants
***************************************/

/* Constants SetPhase(), clkPhase parameter. Only valid for PSoC 3 ES2 and earlier. See datasheet for details. */
#if CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
   (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 || \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
#define CYCLK_2_5NS             0x01 /* 2.5 ns delay. */
#define CYCLK_3_5NS             0x02 /* 3.5 ns delay. */
#define CYCLK_4_5NS             0x03 /* 4.5 ns delay. */
#define CYCLK_5_5NS             0x04 /* 5.5 ns delay. */
#define CYCLK_6_5NS             0x05 /* 6.5 ns delay. */
#define CYCLK_7_5NS             0x06 /* 7.5 ns delay. */
#define CYCLK_8_5NS             0x07 /* 8.5 ns delay. */
#define CYCLK_9_5NS             0x08 /* 9.5 ns delay. */
#define CYCLK_10_5NS            0x09 /* 10.5 ns delay. */
#define CYCLK_11_5NS            0x0A /* 11.5 ns delay. */
#define CYCLK_12_5NS            0x0B /* 12.5 ns delay. */
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CountClk_CLKEN              (* (reg8 *) CountClk__PM_ACT_CFG)
#define CountClk_CLKEN_PTR          ((reg8 *) CountClk__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CountClk_CLKSTBY            (* (reg8 *) CountClk__PM_STBY_CFG)
#define CountClk_CLKSTBY_PTR        ((reg8 *) CountClk__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CountClk_DIV_LSB            (* (reg8 *) CountClk__CFG0)
#define CountClk_DIV_LSB_PTR        ((reg8 *) CountClk__CFG0)
#define CountClk_DIV_PTR            ((reg16 *) CountClk__CFG0)

/* Clock MSB divider configuration register. */
#define CountClk_DIV_MSB            (* (reg8 *) CountClk__CFG1)
#define CountClk_DIV_MSB_PTR        ((reg8 *) CountClk__CFG1)

/* Mode and source configuration register */
#define CountClk_MOD_SRC            (* (reg8 *) CountClk__CFG2)
#define CountClk_MOD_SRC_PTR        ((reg8 *) CountClk__CFG2)

#if defined(CountClk__CFG3)
/* Analog clock phase configuration register */
#define CountClk_PHASE              (* (reg8 *) CountClk__CFG3)
#define CountClk_PHASE_PTR          ((reg8 *) CountClk__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CountClk_CLKEN_MASK         CountClk__PM_ACT_MSK
#define CountClk_CLKSTBY_MASK       CountClk__PM_STBY_MSK

/* CFG2 field masks */
#define CountClk_SRC_SEL_MSK        CountClk__CFG2_SRC_SEL_MASK
#define CountClk_MODE_MASK          (~(CountClk_SRC_SEL_MSK))

#if defined(CountClk__CFG3)
/* CFG3 phase mask */
#define CountClk_PHASE_MASK         CountClk__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_CountClk_H */


/* [] END OF FILE */
