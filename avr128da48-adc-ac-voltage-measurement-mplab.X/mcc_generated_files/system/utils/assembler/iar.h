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


#ifndef ASSEMBLER_IAR_H_INCLUDED
#define ASSEMBLER_IAR_H_INCLUDED

/* clang-format off */

ld_addr MACRO   reg, sym
	mov     reg, LWRD sym
	orh     reg, HWRD sym
	ENDM

call    MACRO   sym
	rcall   sym
	ENDM

iar_begin_func  MACRO   name, sect, is_public, is_weak
	MODULE  name
	RSEG    CODE:CODE:NOROOT(1)
	IF      is_weak == 1
	PUBWEAK name
	ELSEIF  is_public
	PUBLIC  name
	ENDIF
name:
	ENDM

iar_begin_func_segm  MACRO   name, sect, is_public, is_weak, segment
	MODULE  name
	RSEG    segment:CODE:NOROOT(1)
	IF      is_weak == 1
	PUBWEAK name
	ELSEIF  is_public
	PUBLIC  name
	ENDIF
name:
	ENDM

iar_weak_alias  MACRO   name, strong_name
	PUBWEAK name
name:
	rjmp    strong_name
	ENDM

#define lo(x)   LWRD x
#define hi(x)   HWRD x

#define REPEAT(count)           REPT    count
#define END_REPEAT()            ENDR
#define SET_LOC(offset)         ORG     offset
#define END_FILE()              END

#define FILL_BYTES(count)       DS8     count

#define L(name)                 name
#define EXTERN_SYMBOL(name)             EXTERN  name
#define FUNCTION(name)          iar_begin_func name, text_##name, 0, 0
#define PUBLIC_FUNCTION(name)   iar_begin_func name, text_##name, 1, 0
#define PUBLIC_FUNCTION_SEGMENT(name, segment)          \
		iar_begin_func_segm name, text_##name, 1, 0, segment
#define WEAK_FUNCTION(name)     iar_begin_func name, text_##name, 1, 1
#define WEAK_FUNCTION_ALIAS(name, strong_name)          \
		iar_weak_alias  name, strong_name
#define END_FUNC(name)          ENDMOD

#define TEXT_SECTION(name)      RSEG    name:CODE:NOROOT
#define RODATA_SECTION(name)    RSEG    name:CONST:NOROOT
#define DATA_SECTION(name)      RSEG    name:DATA:NOROOT
#define BSS_SECTION(name)       RSEG    name:DATA:NOROOT

/* clang-format on */

#endif /* ASSEMBLER_IAR_H_INCLUDED */