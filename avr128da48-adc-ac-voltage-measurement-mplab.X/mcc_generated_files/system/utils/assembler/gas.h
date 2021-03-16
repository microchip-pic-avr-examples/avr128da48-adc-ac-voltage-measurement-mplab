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


#ifndef ASSEMBLER_GAS_H_INCLUDED
#define ASSEMBLER_GAS_H_INCLUDED

#ifndef __DOXYGEN__

/* clang-format off */

        /* IAR doesn't accept dots in macro names */
        .macro  ld_addr, reg, sym
        lda.w   \reg, \sym
        .endm

        /* Define a function \a name that is either globally visible or only
         * file-local.
         */
        .macro gas_begin_func name, is_public
                .if \is_public
                .global \name
                .endif
            #ifdef __XC8
                .section .text.\name, code
            #else
                .section .text.\name, "ax", @progbits
            #endif
                .type \name, @function
        \name :
        .endm

        /* Define a function \a name that is either globally visible or only
         * file-local in a given segment.
         */
        .macro gas_begin_func_segm name, is_public, segment
                .if \is_public
                .global \name
                .endif
                .section .\segment, "ax", @progbits
                .type \name, @function
        \name :
        .endm

        /* Define \a name as a weak alias for the function \a strong_name */
        .macro gas_weak_function_alias name, strong_name
        .global \name
        .weak   \name
        .type   \name, @function
        .set    \name, \strong_name
        .endm

        /* Define a weak function called \a name */
        .macro gas_weak_function name
        .weak   \name
        gas_begin_func \name 1
        .endm

#define REPEAT(count)           .rept   count
#define END_REPEAT()            .endr
#define FILL_BYTES(count)       .fill   count
#define SET_LOC(offset)         .org    offset
#define L(name)                 .L##name
#define EXTERN_SYMBOL(name)

#define TEXT_SECTION(name)                              \
        .section name, "ax", @progbits
#define RODATA_SECTION(name)                            \
        .section name, "a", @progbits
#define DATA_SECTION(name)                              \
        .section name, "aw", @progbits
#define BSS_SECTION(name)                               \
        .section name, "aw", @nobits

#define FUNCTION(name) gas_begin_func name 0
#define PUBLIC_FUNCTION(name)   gas_begin_func name 1
#define PUBLIC_FUNCTION_SEGMENT(name, segment)          \
        gas_begin_func_segm name 1 segment
#define WEAK_FUNCTION(name) gas_weak_function name
#define WEAK_FUNCTION_ALIAS(name, strong_name) \
        gas_weak_function_alias name strong_name
#define END_FUNC(name)                                  \
        .size   name, . - name

#define END_FILE()

/* clang-format on */

#endif /* __DOXYGEN__ */

#endif /* ASSEMBLER_GAS_H_INCLUDED */