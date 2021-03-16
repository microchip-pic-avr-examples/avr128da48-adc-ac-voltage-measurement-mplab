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


#include "../usart1.h"
#define RECEIVE_ERROR_MASK 0x46

#if defined(__GNUC__)

int USART1_printCHAR(char character, FILE *stream)
{
    while(!(USART1_IsTxReady()));
    USART1_Write(character);
    return 0;
}

FILE USART1_stream = FDEV_SETUP_STREAM(USART1_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART1_Write(outChar);
    return outChar;
}
#endif

static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART1_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART1_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART1_parity_err_cb)(void) = &DefaultParityErrorCallback;

const struct UART_INTERFACE USART1_Interface = {
  .Initialize = USART1_Initialize,
  .Write = USART1_Write,
  .Read = USART1_Read,
  .RxCompleteCallbackRegister = NULL,
  .TxCompleteCallbackRegister = NULL,
  .ErrorCallbackRegister = NULL,
  .FramingErrorCallbackRegister = USART1_FramingErrorCallbackRegister,
  .OverrunErrorCallbackRegister = USART1_OverrunErrorCallbackRegister,
  .ParityErrorCallbackRegister = USART1_ParityErrorCallbackRegister,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = USART1_IsRxReady,
  .IsTxReady = USART1_IsTxReady,
  .IsTxDone = USART1_IsTxDone
};

void USART1_Initialize(void)
{
    //set baud rate register
    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(9600);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 DISABLE; RXCIE disabled; RXSIE disabled; TXCIE disabled; 
    USART1.CTRLA = 0x0;
	
    // MPCM disabled; ODME disabled; RXEN enabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART1.CTRLB = 0xC0;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART1.CTRLC = 0x3;
	
    //DBGCTRL_DBGRUN
    USART1.DBGCTRL = 0x0;
	
    //EVCTRL_IREI
    USART1.EVCTRL = 0x0;
	
    //RXPLCTRL_RXPL
    USART1.RXPLCTRL = 0x0;
	
    //TXPLCTRL_TXPL
    USART1.TXPLCTRL = 0x0;
	

#if defined(__GNUC__)
    stdout = &USART1_stream;
#endif

}

void USART1_FramingErrorCallbackRegister(void* callbackHandler)
{
    USART1_framing_err_cb=callbackHandler;
}

void USART1_OverrunErrorCallbackRegister(void* callbackHandler)
{
    USART1_overrun_err_cb=callbackHandler;
}

void USART1_ParityErrorCallbackRegister(void* callbackHandler)
{
    USART1_parity_err_cb=callbackHandler;
}

static void DefaultFramingErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
   /* Add your interrupt code here or use USART1.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
    /* Add your interrupt code here or use USART1.ParityCallbackRegister function to use Custom ISR */
}

void USART1_Enable(void)
{
    USART1.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART1_EnableRx(void)
{
    USART1.CTRLB |= USART_RXEN_bm;
}

void USART1_EnableTx(void)
{
    USART1.CTRLB |= USART_TXEN_bm;
}

void USART1_Disable(void)
{
    USART1.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART1_GetData(void)
{
    return USART1.RXDATAL;
}

bool USART1_IsTxReady(void)
{
    return (USART1.STATUS & USART_DREIF_bm);
}

bool USART1_IsRxReady(void)
{
    return (USART1.STATUS & USART_RXCIF_bm);
}

bool USART1_IsTxBusy(void)
{
    return (!(USART1.STATUS & USART_TXCIF_bm));
}

bool USART1_IsTxDone(void)
{
    return (USART1.STATUS & USART_TXCIF_bm);
}

void USART1_ErrorCheck(void)
{
    uint8_t errorMask = USART1.RXDATAH;
    if(errorMask & RECEIVE_ERROR_MASK)
    {
        if(errorMask & USART_PERR_bm)
        {
            USART1_parity_err_cb();
        } 
        if(errorMask & USART_FERR_bm)
        {
            USART1_framing_err_cb();
        }
        if(errorMask & USART_BUFOVF_bm)
        {
            USART1_overrun_err_cb();
        }
    }
    
}

uint8_t USART1_Read(void)
{       
    return USART1.RXDATAL;
}

void USART1_Write(const uint8_t data)
{
    USART1.TXDATAL = data;
}