/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   2.0.0
*/
/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/


#include "../rtc.h"

/**
 * \brief Initialize rtc interface
 *
 * \return Initialization status.
 */

void (*RTC_OVF_isr_cb)(void) = NULL;
void (*RTC_CMP_isr_cb)(void) = NULL;
void (*RTC_PIT_isr_cb)(void) = NULL;

/**
 * \brief Initialize RTC interface
 */
int8_t RTC_Initialize(void)
{
    while (RTC.STATUS > 0) { /* Wait for all register to be synchronized */
    }
    //Compare 
    RTC.CMP = 0x7FFF;

    //Count
    RTC.CNT = 0x0;

    //Period
    RTC.PER = 0xFFFF;

    //Clock selection
    RTC.CLKSEL = 0x0;

    // CMP disabled; OVF enabled; 
    RTC.INTCTRL = 0x1;

    // CORREN disabled; PRESCALER RTC Clock / 1; RTCEN enabled; RUNSTDBY disabled; 
    RTC.CTRLA = 0x1;


        while (RTC.PITSTATUS > 0) { /* Wait for all register to be synchronized */
    }
    // PI enabled; 
	RTC.PITINTCTRL = 0x1;

    // PERIOD RTC Clock Cycles 16; PITEN enabled; 
    RTC.PITCTRLA = 0x19;

    return 0;
}

void RTC_SetOVFIsrCallback(RTC_cb_t cb)
{
    RTC_OVF_isr_cb = cb;
}

void RTC_SetCMPIsrCallback(RTC_cb_t cb)
{
    RTC_CMP_isr_cb = cb;
}

void RTC_SetPITIsrCallback(RTC_cb_t cb)
{
    RTC_PIT_isr_cb = cb;
}

ISR(RTC_CNT_vect)
{
    if (RTC.INTFLAGS & RTC_OVF_bm )
    {
        if (RTC_OVF_isr_cb != NULL) 
        {
            (*RTC_OVF_isr_cb)();
        } 
    }  
    
    if (RTC.INTFLAGS & RTC_CMP_bm )
    {
        if (RTC_CMP_isr_cb != NULL) 
        {
            (*RTC_CMP_isr_cb)();
        } 
    }  
    RTC.INTFLAGS = (RTC_OVF_bm | RTC_CMP_bm);
}

ISR(RTC_PIT_vect)
{
   if (RTC_PIT_isr_cb != NULL) 
   {
    (*RTC_PIT_isr_cb)();
   } 
   RTC.PITINTFLAGS = RTC_PI_bm;
}

inline void RTC_WriteCounter(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    RTC.CNT = timerVal;
}

inline uint16_t RTC_ReadCounter(void)
{
    return RTC.CNT;
}

inline void RTC_WritePeroid(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_PERBUSY_bm);
    RTC.PER = timerVal;
}

inline uint16_t RTC_ReadPeriod(void)
{
    return RTC.PER;
}

inline void RTC_EnableCMPInterrupt(void)
{
    RTC.INTCTRL |= RTC_CMP_bm;
}

inline void RTC_DisableCMPInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_CMP_bm; 
}

inline void RTC_EnableOVFInterrupt(void)
{
    RTC.INTCTRL |= RTC_OVF_bm; 
}

inline void RTC_DisableOVFInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_OVF_bm; 
}

inline void RTC_EnablePITInterrupt(void)
{
    RTC.PITINTCTRL |= RTC_PI_bm;  
}

inline void RTC_DisablePITInterrupt(void)
{
    RTC.PITINTCTRL &= ~RTC_PI_bm; 
}

inline void RTC_ClearOVFInterruptFlag(void)
{
    RTC.INTFLAGS &= ~RTC_OVF_bm;
}

inline bool RTC_IsOVFInterruptEnabled(void)
{
    return ((RTC.INTCTRL & RTC_OVF_bm) > 0);
}