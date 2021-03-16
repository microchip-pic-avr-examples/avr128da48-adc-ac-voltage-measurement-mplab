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


#ifndef ADC0_H_INCLUDED
#define ADC0_H_INCLUDED

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	ADC0_window_disabled,
	ADC0_window_below,
	ADC0_window_above,
	ADC0_window_inside,
	ADC0_window_outside
} ADC0_window_mode_t;

/** Function pointer to callback function called by IRQ.
    NULL=default value: No callback function is to be used.
*/
typedef void (*adc_irq_cb_t)(void);

/** Datatype for the result of the ADC conversion */
typedef uint16_t adc_result_t;
typedef int16_t diff_adc_result_t;

//* Analog channel selection */
typedef ADC_MUXPOS_t adc_0_channel_t;
typedef ADC_MUXNEG_t adc_0_muxneg_channel_t;

/**
 * \brief Initialize ADC interface
 * If module is configured to disabled state, the clock to the ADC is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the ADC init was successful
 * \retval 1 the ADC init was not successful
 */
int8_t ADC0_Initialize(void);

/**
 * \brief Enable ADC0
 * 1. If supported by the clock system, enables the clock to the ADC
 * 2. Enables the ADC module by setting the enable-bit in the ADC control register
 *
 * \return Nothing
 */
void ADC0_Enable(void);

/**
 * \brief Disable ADC0
 * 1. Disables the ADC module by clearing the enable-bit in the ADC control register
 * 2. If supported by the clock system, disables the clock to the ADC
 *
 * \return Nothing
 */
void ADC0_Disable(void);

/**
 * \brief Enable conversion auto-trigger
 *
 * \return Nothing
 */
void ADC0_EnableAutoTrigger(void);

/**
 * \brief Disable conversion auto-trigger
 *
 * \return Nothing
 */
void ADC0_DisableAutoTrigger(void);

/**
 * \brief Set conversion window comparator high threshold
 *
 * \return Nothing
 */
void ADC0_SetWindowHigh(adc_result_t high);

/**
 * \brief Set conversion window comparator low threshold
 *
 * \return Nothing
 */
void ADC0_SetWindowLow(adc_result_t low);

/**
 * \brief Set conversion window mode
 *
 * \return Nothing
 */
void ADC0_SetWindowMode(ADC0_window_mode_t mode);

/**
 * \brief Set ADC channel to be used for windowed conversion mode
 *
 * \param[in] channel The ADC channel to start conversion on
 *
 * \return Nothing
 */
void ADC0_SetWindowChannel(adc_0_channel_t channel);

/**
 * \brief Start a conversion on ADC0
 *
 * \param[in] channel The ADC channel to start conversion on
 *
 * \return Nothing
 */
void ADC0_StartConversion(adc_0_channel_t channel);

/**
 * \brief Start a differential conversion on ADC0
 *
 * \param[in] channel,channel1 The ADC channels to start conversion on
 *
 * \return Nothing
 */
void ADC0_StartDiffConversion(adc_0_channel_t channel, adc_0_muxneg_channel_t channel1);

/**
 * \brief Stop a conversion on ADC0
 *
 * \return Nothing
 */
void ADC0_StopConversion(void);

/**
 * \brief Check if the ADC conversion is done
 *
 * \return The status of ADC converison done check
 * \retval true The ADC conversion is done
 * \retval false The ADC converison is not done
 */
bool ADC0_IsConversionDone(void);

/**
 * \brief Read a conversion result from ADC0
 *
 * \return Conversion result read from the ADC0 ADC module
 */
adc_result_t ADC0_GetConversionResult(void);

/**
 * \brief Read the conversion window result from ADC0
 *
 * \return Returns true when a comparison results in a trigger condition, false otherwise.
 */
bool ADC0_GetWindowResult(void);

/**
 * \brief Start a conversion, wait until ready, and return the conversion result
 *
 * \return Conversion result read from the ADC0 ADC module
 */
adc_result_t ADC0_GetConversion(adc_0_channel_t channel);

/**
 * \brief Start a differential conversion, wait until ready, and return the conversion result
 *
 * \return Conversion result read from the ADC0 ADC module
 */
diff_adc_result_t ADC0_GetDiffConversion(adc_0_channel_t channel, adc_0_muxneg_channel_t channel1);

/**
 * \brief Return the number of bits in the ADC conversion result
 *
 * \return The number of bits in the ADC conversion result
 */
uint8_t ADC0_GetResolution(void);

/**
 * \brief Register a callback function to be called if conversion satisfies window criteria.
 *
 * \param[in] f Pointer to function to be called
 *
 * \return Nothing.
 */
void ADC0_RegisterWindowCallback(adc_irq_cb_t f);

#ifdef __cplusplus
}
#endif

#endif /* ADC0_H_INCLUDED */