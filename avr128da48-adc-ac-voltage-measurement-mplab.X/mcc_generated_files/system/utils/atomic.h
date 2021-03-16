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


#ifndef ATOMIC_H
#define ATOMIC_H

/**
 * \defgroup doc_driver_utils_atomic Atomic memory access and critical sections
 * \ingroup doc_driver_utils
 *
 * Atomic memory access and critical sections
 *
 * \{
 */

/* clang-format off */

#if defined(__GNUC__) || defined (__DOXYGEN__)

/**
 * \brief Enter a critical region
 * 
 * Saves the contents of the status register, including the Global 
 * Interrupt Enable bit, so that it can be restored upon leaving the 
 * critical region. Thereafter, clears the Global Interrupt Enable Bit.
 * This macro takes a parameter P that is unused for the GCC compiler,
 * but necessary for code compatibility with the IAR compiler. The IAR
 * compiler declares a variable with the name of the parameter for
 * holding the SREG value. Since a variable is declared in the macro,
 * this variable must have a name that is unique within the scope
 * that the critical region is declared within, otherwise compilation 
 * will fail.
 *
 * \param[in] UNUSED(GCC)/P(IAR) Name of variable storing SREG
 *
 */

#define ENTER_CRITICAL(UNUSED) __asm__ __volatile__ (   \
   "in __tmp_reg__, __SREG__"                    "\n\t" \
   "cli"                                         "\n\t" \
   "push __tmp_reg__"                            "\n\t" \
   ::: "memory"                                         \
   )

/**
 * \brief Exit a critical region
 * 
 * Restores the contents of the status register, including the Global 
 * Interrupt Enable bit, as it was when entering the critical region.
 * This macro takes a parameter P that is unused for the GCC compiler,
 * but necessary for code compatibility with the IAR compiler. The IAR
 * compiler uses this parameter as the name of a variable that holds 
 * the SREG value. The parameter must be identical to the parameter 
 * used in the corresponding ENTER_CRITICAL().
 *
 * \param[in] UNUSED(GCC)/P(IAR) Name of variable storing SREG
 *
 */

#define EXIT_CRITICAL(UNUSED)  __asm__ __volatile__ (   \
   "pop __tmp_reg__"                             "\n\t" \
   "out __SREG__, __tmp_reg__"                   "\n\t" \
   ::: "memory"                                         \
   )

#define DISABLE_INTERRUPTS()        __asm__ __volatile__ ( "cli" ::: "memory")
#define ENABLE_INTERRUPTS()         __asm__ __volatile__ ( "sei" ::: "memory")

#elif defined(__ICCAVR__)

#define ENTER_CRITICAL(P)  unsigned char P = __save_interrupt();__disable_interrupt();
#define EXIT_CRITICAL(P)  __restore_interrupt(P);

#define DISABLE_INTERRUPTS()   __disable_interrupt();
#define ENABLE_INTERRUPTS()    __enable_interrupt();

#else
#  error Unsupported compiler.
#endif

/* clang-format on */

#endif /* ATOMIC_H */