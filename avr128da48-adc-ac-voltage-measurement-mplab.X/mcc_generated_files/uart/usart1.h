/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
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

#ifndef USART1_H
#define USART1_H

#include <stdbool.h>
#include <stdio.h>
#include "../system/utils/compiler.h"
#include "../system/utils/atomic.h"
#include "../system/clock.h"
#include "uart_interface.h"

/* Normal Mode, Baud register value */
#define USART1_BAUD_RATE(BAUD_RATE) (((float)4000000 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

extern const struct UART_INTERFACE USART1_Interface;

/**
 * \brief Initialize USART interface
 * If module is configured to disabled state, the clock to the USART is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the USART init was successful
 * \retval 1 the USART init was not successful
 */
void USART1_Initialize(void);

/**
 * \brief Enable RX and TX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX and TX enable-bits in the USART control register
 *
 * \return Nothing
 */
void USART1_Enable(void);

/**
 * \brief Enable RX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the RX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART1_EnableRx(void);

/**
 * \brief Enable TX in USART1
 * 1. If supported by the clock system, enables the clock to the USART
 * 2. Enables the USART module by setting the TX enable-bit in the USART control register
 *
 * \return Nothing
 */
void USART1_EnableTx(void);

/**
 * \brief Disable USART1
 * 1. Disables the USART module by clearing the enable-bit(s) in the USART control register
 * 2. If supported by the clock system, disables the clock to the USART
 *
 * \return Nothing
 */
void USART1_Disable(void);

/**
 * \brief Get recieved data from USART1
 *
 * \return Data register from USART1 module
 */
uint8_t USART1_GetData(void);

/**
 * \brief Check if the usart can accept data to be transmitted
 *
 * \return The status of USART TX data ready check
 * \retval false The USART can not receive data to be transmitted
 * \retval true The USART can receive data to be transmitted
 */
bool USART1_IsTxReady(void);

/**
 * \brief Check if the USART has received data
 *
 * \return The status of USART RX data ready check
 * \retval true The USART has received data
 * \retval false The USART has not received data
 */
bool USART1_IsRxReady(void);

/**
 * \brief Check if USART1 data is transmitted
 *
 * \return Receiver ready status
 * \retval true  Data is not completely shifted out of the shift register
 * \retval false Data completely shifted out if the USART shift register
 */
bool USART1_IsTxBusy(void);


bool USART1_IsTxDone(void);
/**
 * \brief Read one character from USART1
 *
 * Function will block if a character is not available.
 *
 * \return Data read from the USART1 module
 */
uint8_t USART1_Read(void);

/**
 * \brief Write one character to USART1
 *
 * Function will block until a character can be accepted.
 *
 * \param[in] data The character to write to the USART
 *
 * \return Nothing
 */
void USART1_Write(const uint8_t data);

/**
 * \brief ErrorCheck USART interface
 *
 * Checks the Recieve Error for Parity, Framing, OverRun
 *
 * No Return and Arguments associated
 */
void USART1_ErrorCheck(void);

void USART1_FramingErrorCallbackRegister(void* callbackHandler);

void USART1_OverrunErrorCallbackRegister(void* callbackHandler);

void USART1_ParityErrorCallbackRegister(void* callbackHandler);

#endif /* USART1_H */