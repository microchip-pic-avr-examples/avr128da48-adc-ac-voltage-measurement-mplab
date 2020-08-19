/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "port.h"

//get/set PD7 aliases
#define PD7_SetHigh() do { PORTD_OUTSET = 0x80; } while(0)
#define PD7_SetLow() do { PORTD_OUTCLR = 0x80; } while(0)
#define PD7_Toggle() do { PORTD_OUTTGL = 0x80; } while(0)
#define PD7_GetValue() (VPORTD.IN & (0x1 << 7))
#define PD7_SetDigitalInput() do { PORTD_DIRCLR = 0x80; } while(0)
#define PD7_SetDigitalOutput() do { PORTD_DIRSET = 0x80; } while(0)
#define PD7_SetPullUp() do { PORTD_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD7_ResetPullUp() do { PORTD_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD7_SetInverted() do { PORTD_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define PD7_ResetInverted() do { PORTD_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD7_DisableInterruptOnChange() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD7_EnableInterruptForBothEdges() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD7_EnableInterruptForRisingEdge() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD7_EnableInterruptForFallingEdge() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD7_DisableDigitalInputBuffer() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD7_EnableInterruptForLowLevelSensing() do { PORTD.PIN7CTRL = (PORTD.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PD6 aliases
#define PD6_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define PD6_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define PD6_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define PD6_GetValue() (VPORTD.IN & (0x1 << 6))
#define PD6_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define PD6_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define PD6_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD6_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD6_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define PD6_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD6_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD6_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD6_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD6_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD6_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD6_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PC0 aliases
#define PC0_SetHigh() do { PORTC_OUTSET = 0x1; } while(0)
#define PC0_SetLow() do { PORTC_OUTCLR = 0x1; } while(0)
#define PC0_Toggle() do { PORTC_OUTTGL = 0x1; } while(0)
#define PC0_GetValue() (VPORTC.IN & (0x1 << 0))
#define PC0_SetDigitalInput() do { PORTC_DIRCLR = 0x1; } while(0)
#define PC0_SetDigitalOutput() do { PORTC_DIRSET = 0x1; } while(0)
#define PC0_SetPullUp() do { PORTC_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PC0_ResetPullUp() do { PORTC_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PC0_SetInverted() do { PORTC_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PC0_ResetInverted() do { PORTC_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PC0_DisableInterruptOnChange() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PC0_EnableInterruptForBothEdges() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PC0_EnableInterruptForRisingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PC0_EnableInterruptForFallingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PC0_DisableDigitalInputBuffer() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PC0_EnableInterruptForLowLevelSensing() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PC1 aliases
#define PC1_SetHigh() do { PORTC_OUTSET = 0x2; } while(0)
#define PC1_SetLow() do { PORTC_OUTCLR = 0x2; } while(0)
#define PC1_Toggle() do { PORTC_OUTTGL = 0x2; } while(0)
#define PC1_GetValue() (VPORTC.IN & (0x1 << 1))
#define PC1_SetDigitalInput() do { PORTC_DIRCLR = 0x2; } while(0)
#define PC1_SetDigitalOutput() do { PORTC_DIRSET = 0x2; } while(0)
#define PC1_SetPullUp() do { PORTC_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PC1_ResetPullUp() do { PORTC_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PC1_SetInverted() do { PORTC_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PC1_ResetInverted() do { PORTC_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PC1_DisableInterruptOnChange() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PC1_EnableInterruptForBothEdges() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PC1_EnableInterruptForRisingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PC1_EnableInterruptForFallingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PC1_DisableDigitalInputBuffer() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PC1_EnableInterruptForLowLevelSensing() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PORTD_PD7_DefaultInterruptHandler(void);
void PORTD_PD7_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_PD6_DefaultInterruptHandler(void);
void PORTD_PD6_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTC_PC0_DefaultInterruptHandler(void);
void PORTC_PC0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTC_PC1_DefaultInterruptHandler(void);
void PORTC_PC1_SetInterruptHandler(void (* interruptHandler)(void)) ;
#endif /* PINS_H_INCLUDED */
