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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/rtc/rtc.h"
#include "math.h"

#define ADC_SAMPLES	  (uint8_t)200               //Number of ADC samples taken
#define ADC_REF_V	  (float)3.33
#define ADC_GAIN	  (float)(ADC_REF_V / 4096)  //ADC digital to analog voltage factor
#define ANALOG_GAIN	  (float)1750                //Hardware gain 
#define ADC_CH_POS	   6                         //AC signal input channel
#define ADC_CH_NEG	   7                         //AC signal reference point input

void ADC_Handler(void);
float Calculate_RMS(void);
void PITInterrupt(void); 

volatile uint8_t SamplesCount = 0;
volatile uint8_t ADCSumReadyFlag = 0;
float VolRMS = 0;

int32_t ADCRes;
int32_t ADCSqr;
int64_t ADCSqrSum;
int64_t ADCSumSave;
float ADCSqrAvg;

void (*RTC_PIT_isr_cb)(void);
/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    printf("System Initialized \n");
    
    /* PIT interrupt handler for every 500usec  */
    RTC_SetPITIsrCallback(*PITInterrupt);
    
    /* Replace with your application code */
    while (1)
    {
        //ADC samples are ready for computation
        if(ADCSumReadyFlag)
		{
			VolRMS = Calculate_RMS();
            //Convert the voltage to integer to print it on terminal
            uint16_t TempVol = (uint16_t)VolRMS;
			printf("%d \n", TempVol);
			ADCSumReadyFlag = 0;
		}
    }   
}

/*******************************************************************************
 * void ADC_Handler(void)
 *
 * API to collect ADC samples and perform squaring and summation of required number of samples. 
 * @param void 
 * @return void
 ******************************************************************************/
void ADC_Handler(void)
{
    //Read ADC differential conversion result
	ADCRes = (int16_t)ADC0_GetConversionResult();
    //Square the result
	ADCSqr = ADCRes * ADCRes;
    //Summation of the squared samples
	ADCSqrSum += ADCSqr;
	
	SamplesCount += 1;
	
    //Required number of samples are collected
	if(SamplesCount >= ADC_SAMPLES)
	{
        //copy the squared and summed samples result
		ADCSumSave = ADCSqrSum;
		ADCSqrSum = 0;
		SamplesCount = 0;
		ADCSumReadyFlag = 1;
	}
}

/*******************************************************************************
 * float calculateVrms(void)
 *
 * API to calculate RMS voltage, this API calculates RMS voltage using the acquired samples. 
 * @param void 
 * @return calculated rms voltage
 ******************************************************************************/
float Calculate_RMS(void)
{
	float rmsval;
    //Averaging the summation of the samples
	ADCSqrAvg = (float)ADCSumSave / ADC_SAMPLES;
    //Take square root for the Averaged result
	rmsval = sqrt(ADCSqrAvg);
    //Multiply ADC gain
	rmsval *= ADC_GAIN;
    //Multiply hardware analog gain
	rmsval *= ANALOG_GAIN;

	return (rmsval);
}

/*******************************************************************************
 * ISR(RTC_PIT_vect)
 *
 * API to generate the periodic interrupt for every 500usec , 
   ADC starts  differential conversion upon interrupt. 
 * @param void 
 * @return calculated rms voltage
 ******************************************************************************/
void PITInterrupt(void) 
{
    ADC0_StartDiffConversion(ADC_CH_POS, ADC_CH_NEG);
}