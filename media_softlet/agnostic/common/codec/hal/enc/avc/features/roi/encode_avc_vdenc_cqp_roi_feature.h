/*
* Copyright (c) 2020, Intel Corporation
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
//! \file     encode_avc_vdenc_cqp_roi_feature.h
//! \brief    Define implementation of the CQP ROI features of AVC VDENC
//!

#ifndef __CODECHAL_AVC_VDENC_CQP_ROI_FEATURE_H__
#define __CODECHAL_AVC_VDENC_CQP_ROI_FEATURE_H__

#include "encode_avc_vdenc_roi_interface.h"
#include "mhw_vdbox_vdenc_itf.h"

namespace encode
{

//!
//! \class    AvcVdencCqpRoiFeature
//!
//! \brief    AvcVdencCqpRoiFeature is implementation of CQP VDEnc ROI and Dirty ROI features.
//!
//! \detail   This class is an implementation for AVC native and non-native ROI 
//!           in both ForceQP and DeltaQP modes and Dirty ROI.
class AvcVdencCqpRoiFeature : public AvcVdencRoiInterface, public mhw::vdbox::vdenc::Itf::ParSetting
{
public:

    AvcVdencCqpRoiFeature(
        MediaFeatureManager *featureManager,
        EncodeAllocator *allocator,
        CodechalHwInterfaceNext *hwInterface,
        void *constSettings,
        SupportedModes& supportedModes);

    virtual ~AvcVdencCqpRoiFeature() {}

    virtual MOS_STATUS Update(void* params) override;

    MHW_SETPAR_DECL_HDR(VDENC_AVC_IMG_STATE);

protected:

    virtual MOS_STATUS SetupROI() override;

    virtual MOS_STATUS SetupDirtyROI() override;

    virtual MOS_STATUS SetupMBQP() override;

MEDIA_CLASS_DEFINE_END(encode__AvcVdencCqpRoiFeature)
};

}  // namespace encode
#endif  //<! __CODECHAL_AVC_VDENC_CQP_ROI_FEATURE_H__
