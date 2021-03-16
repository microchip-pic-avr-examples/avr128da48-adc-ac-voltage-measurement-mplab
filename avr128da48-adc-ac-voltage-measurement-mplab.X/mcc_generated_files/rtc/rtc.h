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


#ifndef RTCDRIVER_H
#define RTCDRIVER_H

#include "../system/utils/compiler.h"
#include <stdint.h>
#include <stdbool.h>

/** Datatype used to hold the number of ticks until a timer expires */

typedef void (*RTC_cb_t)(void);
void RTC_SetOVFIsrCallback(RTC_cb_t cb);
void RTC_SetCMPIsrCallback(RTC_cb_t cb);
void RTC_SetPITIsrCallback(RTC_cb_t cb);
int8_t RTC_Initialize(void);
void RTC_WriteCounter(uint16_t timerVal);
void RTC_WritePeroid(uint16_t timerVal);
uint16_t RTC_ReadCounter(void);
uint16_t RTC_ReadPeriod(void);
void RTC_EnableCMPInterrupt(void);
void RTC_DisableCMPInterrupt(void);
void RTC_EnableOVFInterrupt(void);
void RTC_DisableOVFInterrupt(void);
void RTC_EnablePITInterrupt(void);
void RTC_DisablePITInterrupt(void);
void RTC_ClearOVFInterruptFlag(void);
bool RTC_IsOVFInterruptEnabled(void);


#endif /* RTCDRIVER_H */

/** @}*/