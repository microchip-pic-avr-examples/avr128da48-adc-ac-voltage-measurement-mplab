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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/include/rtc.h"
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
    /* Initializes MCU, drivers and middleware */
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

/**
    End of File
*/
