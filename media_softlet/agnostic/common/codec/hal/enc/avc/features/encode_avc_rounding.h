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
//! \file     encode_avc_rounding.h
//! \brief    Defines the common interface for avc encode rounding feature
//!
#ifndef __ENCODE_AVC_ROUNDING_H__
#define __ENCODE_AVC_ROUNDING_H__

#include "media_feature.h"
#include "encode_avc_basic_feature.h"
#include "mhw_vdbox_vdenc_itf.h"
#include "mhw_vdbox_mfx_itf.h"

namespace encode
{

class AvcEncodeRounding : public MediaFeature, public mhw::vdbox::vdenc::Itf::ParSetting, public mhw::vdbox::mfx::Itf::ParSetting
{
public:
    AvcEncodeRounding(MediaFeatureManager *featureManager,
                      EncodeAllocator *allocator,
                      CodechalHwInterfaceNext *hwInterface,
                      void *constSettings);

    virtual ~AvcEncodeRounding() {}

    virtual MOS_STATUS Update(void *params) override;

    //!
    //! \brief    SetRounding params for AVC slice state
    //!
    //! \param    [out] sliceState
    //!           Reference of AVC slice state
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    MOS_STATUS SetRoundingParams(MHW_VDBOX_AVC_SLICE_STATE &sliceState) const;

    MHW_SETPAR_DECL_HDR(VDENC_AVC_SLICE_STATE);

    MHW_SETPAR_DECL_HDR(MFX_AVC_SLICE_STATE);

protected:

    //!
    //! \brief    Get intra/inter rounding value.
    //!
    //! \param    [out] sliceState
    //!           Reference of AVC slice state
    //!
    //! \return   MOS_STATUS
    //!           MOS_STATUS_SUCCESS if success, else fail reason
    //!
    virtual MOS_STATUS GetRounding(MHW_VDBOX_AVC_SLICE_STATE &sliceState) const;

    AvcBasicFeature *m_basicFeature = nullptr;                        //!< EncodeBasicFeature

    PCODECHAL_ENCODE_AVC_ROUNDING_PARAMS m_roundingParams = nullptr;  //!< Pointer to AVC rounding parameter

MEDIA_CLASS_DEFINE_END(encode__AvcEncodeRounding)
};

}  // namespace encode

#endif  // !__ENCODE_AVC_ROUNDING_H__
