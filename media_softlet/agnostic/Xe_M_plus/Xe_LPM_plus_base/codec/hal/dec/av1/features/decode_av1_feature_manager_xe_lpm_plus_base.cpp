/*
* Copyright (c) 2020-2021, Intel Corporation
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
//! \file     decode_av1_feature_manager_xe_lpm_plus_base.cpp
//! \brief    Defines the common interface for av1 decode feature manager
//! \details  The av1 decode feature manager is further sub-divided by codec type
//!           this file is for the base interface which is shared by all components.
//!

#include "decode_av1_feature_manager_xe_lpm_plus_base.h"
#include "decode_utils.h"
#include "decode_av1_basic_feature_xe_lpm_plus_base.h"

namespace decode
{
    MOS_STATUS DecodeAv1FeatureManagerXe_Lpm_Plus_Base::CreateFeatures(void *codecSettings)
    {
        DECODE_FUNC_CALL()

        DECODE_CHK_STATUS(DecodeFeatureManager::CreateFeatures(codecSettings));

        Av1BasicFeature *decBasic = MOS_New(Av1BasicFeatureXe_Lpm_Plus_Base, m_allocator, m_hwInterface, m_osInterface);
        DECODE_CHK_STATUS(RegisterFeatures(FeatureIDs::basicFeature, decBasic));

        return MOS_STATUS_SUCCESS;
    }
}
