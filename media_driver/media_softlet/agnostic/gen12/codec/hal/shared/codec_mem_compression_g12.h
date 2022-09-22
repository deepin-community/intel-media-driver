/*
* Copyright (c) 2019-2020, Intel Corporation
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/

//!
//! \file     codec_mem_compression_g12.h
//! \brief    Defines the common interface for codec mmc
//! \details  The codec mmc is to handle mmc operations
//!

#ifndef __MEDIA_CODEC_MEM_COMPRESSION_G12_H__
#define __MEDIA_CODEC_MEM_COMPRESSION_G12_H__

#include "media_context.h"

class CodecMmcAuxTableG12
{
public:
    //!
    //! \brief    Construct
    //!
    CodecMmcAuxTableG12() {};

    //!
    //! \brief    Destructor
    //!
    virtual ~CodecMmcAuxTableG12() {};

    //!
    //! \brief    LoadAuxTableMmio, this is only used by gen12lp
    //!
     MOS_STATUS LoadAuxTableMmio(
        PMOS_INTERFACE    m_osInterface,
        MhwMiInterface    *m_mhwMiInterface,
        PMOS_COMMAND_BUFFER    cmdBuffer,
        bool    bRcsIsUsed);
};

#endif //__MEDIA_CODEC_MEM_COMPRESSION_G12_H__
