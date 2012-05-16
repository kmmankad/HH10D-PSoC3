/*******************************************************************************
* File Name: Fin.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Fin_H) /* Pins Fin_H */
#define CY_PINS_Fin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Fin_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Fin_Write(uint8 value) ;
void    Fin_SetDriveMode(uint8 mode) ;
uint8   Fin_ReadDataReg(void) ;
uint8   Fin_Read(void) ;
uint8   Fin_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Fin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Fin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Fin_DM_RES_UP          PIN_DM_RES_UP
#define Fin_DM_RES_DWN         PIN_DM_RES_DWN
#define Fin_DM_OD_LO           PIN_DM_OD_LO
#define Fin_DM_OD_HI           PIN_DM_OD_HI
#define Fin_DM_STRONG          PIN_DM_STRONG
#define Fin_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Fin_MASK               Fin__MASK
#define Fin_SHIFT              Fin__SHIFT
#define Fin_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Fin_PS                     (* (reg8 *) Fin__PS)
/* Data Register */
#define Fin_DR                     (* (reg8 *) Fin__DR)
/* Port Number */
#define Fin_PRT_NUM                (* (reg8 *) Fin__PRT) 
/* Connect to Analog Globals */                                                  
#define Fin_AG                     (* (reg8 *) Fin__AG)                       
/* Analog MUX bux enable */
#define Fin_AMUX                   (* (reg8 *) Fin__AMUX) 
/* Bidirectional Enable */                                                        
#define Fin_BIE                    (* (reg8 *) Fin__BIE)
/* Bit-mask for Aliased Register Access */
#define Fin_BIT_MASK               (* (reg8 *) Fin__BIT_MASK)
/* Bypass Enable */
#define Fin_BYP                    (* (reg8 *) Fin__BYP)
/* Port wide control signals */                                                   
#define Fin_CTL                    (* (reg8 *) Fin__CTL)
/* Drive Modes */
#define Fin_DM0                    (* (reg8 *) Fin__DM0) 
#define Fin_DM1                    (* (reg8 *) Fin__DM1)
#define Fin_DM2                    (* (reg8 *) Fin__DM2) 
/* Input Buffer Disable Override */
#define Fin_INP_DIS                (* (reg8 *) Fin__INP_DIS)
/* LCD Common or Segment Drive */
#define Fin_LCD_COM_SEG            (* (reg8 *) Fin__LCD_COM_SEG)
/* Enable Segment LCD */
#define Fin_LCD_EN                 (* (reg8 *) Fin__LCD_EN)
/* Slew Rate Control */
#define Fin_SLW                    (* (reg8 *) Fin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Fin_PRTDSI__CAPS_SEL       (* (reg8 *) Fin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Fin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Fin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Fin_PRTDSI__OE_SEL0        (* (reg8 *) Fin__PRTDSI__OE_SEL0) 
#define Fin_PRTDSI__OE_SEL1        (* (reg8 *) Fin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Fin_PRTDSI__OUT_SEL0       (* (reg8 *) Fin__PRTDSI__OUT_SEL0) 
#define Fin_PRTDSI__OUT_SEL1       (* (reg8 *) Fin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Fin_PRTDSI__SYNC_OUT       (* (reg8 *) Fin__PRTDSI__SYNC_OUT) 


#if defined(Fin__INTSTAT)  /* Interrupt Registers */

    #define Fin_INTSTAT                (* (reg8 *) Fin__INTSTAT)
    #define Fin_SNAP                   (* (reg8 *) Fin__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Fin_H */


/* [] END OF FILE */
