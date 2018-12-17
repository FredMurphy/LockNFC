/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//*****************************************************************************
//
// rom_captivate.h
// This is the top level ROM header file.  It includes the correct device
// specific ROM header file for the application that is being built.
//
//! \version 1.70.00.03
//! Released on July 30, 2018
//
//*****************************************************************************

#ifndef __ROM_CAPTIVATE_H__
#define __ROM_CAPTIVATE_H__
#if 0

//! MSP430FR2633 Device ROM Header File
//
#elif   defined (__MSP430FR2633__)
#include "rom_headers/rom_captivate_msp430fr2633_family.h"

//! MSP430FR2632 Device ROM Header File
//
#elif defined (__MSP430FR2632__)
#include "rom_headers/rom_captivate_msp430fr2633_family.h"

//! MSP430FR2533 Device ROM Header File
//
#elif defined (__MSP430FR2533__)
#include "rom_headers/rom_captivate_msp430fr2633_family.h"

//! MSP430FR2532 Device ROM Header File
//
#elif defined (__MSP430FR2532__)
#include "rom_headers/rom_captivate_msp430fr2633_family.h"

//! MSP430FR2522 Device ROM Header File
//
#elif defined (__MSP430FR2522__)
#include "rom_headers/rom_captivate_msp430fr2522_family.h"

//! MSP430FR2512 Device ROM Header File
//
#elif defined (__MSP430FR2512__)
#include "rom_headers/rom_captivate_msp430fr2522_family.h"

#else
#warning "Failed to match a ROM include file."
#endif

#endif // __ROM_CAPTIVATE_H__


