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
//! \file     encode_huc_brc_init_packet.h
//! \brief    Defines the implementation of huc update packet
//!

#ifndef __CODECHAL_AV1_BRC_UPDATE_PACKET_H__
#define __CODECHAL_AV1_BRC_UPDATE_PACKET_H__

#include "media_cmd_packet.h"
#include "encode_huc.h"
#include "media_pipeline.h"
#include "encode_utils.h"
#include "encode_av1_vdenc_pipeline.h"
#include "encode_av1_basic_feature.h"
#include "mhw_vdbox_avp_itf.h"

namespace encode
{
    struct VdencAv1HucBrcUpdateDmem
    {
        int32_t     UPD_TARGET_BUF_FULLNESS;         // passed by the driver
        uint32_t    UPD_FRAMENUM;                    // passed by the driver
        int32_t     UPD_HRD_BUFF_FULLNESS;           // passed by the driver
        int32_t     UPD_HRD_BUFF_FULLNESS_UPPER;     // passed by the driver
        int32_t     UPD_HRD_BUFF_FULLNESS_LOWER;     // passed by the driver
        uint32_t    UPD_UserMaxFrame;                // set by driver to support I frame size
        uint32_t    UPD_TR_TargetSize;               // transport/look ahead controlled target frame size, passed by the driver//TR_BRC
        uint32_t    UPD_LA_TargetFULNESS;            // look ahead controlled target bufferfulness, passed by the driver
        uint32_t    UPD_CDF_BufferSize;              // for Huc to locate the cdf buffer in LUT
        uint32_t    UPD_UserMaxFramePB;              // Checked with Arch, UserMaxFrame size can be changed frame by frame
        uint32_t    RSVD32[14];                      // mbz

        uint16_t    UPD_startGAdjFrame[4];           // start global adjust frame (4 items)
        uint16_t    UPD_CurWidth;                    // current width
        uint16_t    UPD_CurHeight;                   // current height
        uint16_t    UPD_Asyn;
        uint16_t    UPD_SLBBSize;                    // second level batch buffer total size in bytes
        uint16_t    UPD_AVPPiCStateCmdNum;           // 1-2 kinds of AVP pic state cmd(s)
        uint16_t    UPD_AVPSegmentStateOffset;       // Group1
        uint16_t    UPD_AVPInloopFilterStateOffset;  // Group1
        uint16_t    UPD_VDEncCmd1Offset;        // Group2
        uint16_t    UPD_VDEncCmd2Offset;         // Group3
        uint16_t    UPD_AVPPicStateOffset;           // Group4, the 1st tile pic cmd start position in bytes from the begining of slbb

        uint16_t    UPD_MaxBRCLevel;                 // based on BGOPSize in Cmodel
        uint16_t    UPD_AdditionalHrdSizeByteCount;  // For repeated frame. App can have some header bytes not generated by HW, like skipped frame.
        uint16_t    RSVD16[12];                      // mbz

        // BA start
        uint16_t UPD_LoopFilterParamsBitOffset;
        uint16_t UPD_QIndexBitOffset;
        uint16_t UPD_SegmentationBitOffset;          // SegOn flag bit
        uint16_t UPD_CDEFParamsBitOffset;
        uint16_t UPD_CDEFParamsSizeInBits;
        uint16_t UPD_FrameHdrOBUSizeInBits;          // details in DDI Doc
        uint16_t UPD_FrameHdrOBUSizeByteOffset;      // huc will update this field if seg on, fixed 4 bytes
        uint16_t UPD_FrameHdrOBUSizeInBytes;         // PAK Insert object (frame header) size in bytes
        uint16_t RSVD16_1[8];

        uint8_t UPD_FrameType;                       // see macro AV1_KEY_FRAME in cmodel
        uint8_t UPD_ErrorResilientMode;
        uint8_t UPD_IntraOnly;
        uint8_t UPD_PrimaryRefFrame;
        uint8_t UPD_SegOn;                           // flag to turn on segmentation back annotation
        uint8_t UPD_SegMapUpdate;
        uint8_t UPD_SegTemporalUpdate;
        uint8_t UPD_SegUpdateData;
        uint8_t UPD_IsFrameOBU;
        uint8_t UPD_EnableCDEFUpdate;               //flag to turn on CDEF back annotation
        uint8_t UPD_EnableLFUpdate;                 //flag to turn on LoopFilter back annotation
        uint8_t RSVD8_1[21];
        // BA end

        uint8_t     UPD_OverflowFlag;                // passed by the driver
        uint8_t     UPD_MaxNumPAKs;                  // maximum number of PAKs (default set to 2)
        int8_t      UPD_CurrFrameType;               // current frame type (0:P, 1:B, 2:I)
        uint8_t     UPD_QPThreshold[4];              // QP threshold (4 entries)
        uint8_t     UPD_gRateRatioThreshold[6];      // global rate ratio threshold (6 items)
        int8_t      UPD_startGAdjMult[5];            // start global adjust mult (5 items)
        int8_t      UPD_startGAdjDiv[5];             // start global adjust div (5 items)
        int8_t      UPD_gRateRatioThresholdQP[7];    // global rate ratio threshold QP (7 items)
        uint8_t     UPD_DistThreshldI[9];            // (N_DISTORION_THRESHLDS + 1) distortion thresholds for I frames
        uint8_t     UPD_DistThreshldP[9];            // (N_DISTORION_THRESHLDS + 1) distortion thresholds for P frames
        uint8_t     UPD_DistThreshldB[9];            // (N_DISTORION_THRESHLDS + 1) distortion thresholds for B frames; no needed for Vp8 - to clean up
        int8_t      UPD_MaxFrameThreshI[5];          // num qp threshld + 1 of multiplyers
        int8_t      UPD_MaxFrameThreshP[5];          // num qp threshld + 1 of multiplyers
        int8_t      UPD_MaxFrameThreshB[5];          // num qp threshld + 1 of multiplyers; no needed for Vp8 - to clean up
        uint8_t     UPD_PAKPassNum;                  // current pak pass number
        int8_t      UPD_DeltaQPForSadZone0;
        int8_t      UPD_DeltaQPForSadZone1;
        int8_t      UPD_DeltaQPForSadZone2;
        int8_t      UPD_DeltaQPForSadZone3;
        int8_t      UPD_DeltaQPForMvZero;
        int8_t      UPD_DeltaQPForMvZone0;
        int8_t      UPD_DeltaQPForMvZone1;
        int8_t      UPD_DeltaQPForMvZone2;
        int8_t      UPD_DeltaQPForAvgLuminZone0;
        int8_t      UPD_DeltaQPForAvgLuminZone1;
        int8_t      UPD_DeltaQPForAvgLuminZone2;
        int8_t      UPD_DeltaQPForAvgLuminZone3;
        int8_t      UPD_DeltaQPForAvgLuminZone4;
        int8_t      UPD_DeltaQPForAvgLuminZone5;
        int8_t      UPD_DeltaQPForAvgLuminZone6;
        int8_t      UPD_DeltaQPForAvgLuminZone7;
        int8_t      UPD_DeltaQPForAvgLuminZone8;
        int8_t      UPD_DeltaQPForAvgLuminZone9;
        uint8_t     UPD_Temporal_Level;
        uint8_t     UPD_SegMapGenerating;            // Default 0: The app provides segment map, and HuC does not update segmentation state; 1: HuC generates seg map, updating all 8 segmentation states in second level batch buffer
        uint8_t     UPD_Lowdelay;
        uint8_t     UPD_Delta;
        uint8_t     UPD_LALength;
        uint8_t     UPD_DisableCdfUpdate;
        uint8_t     UPD_EnableDMAForCdf;
        uint8_t     UPD_EnableAdaptiveRounding;
        uint8_t     UPD_TCBRC_SCENARIO; // 2: HQ,  1: VC, 0: CG
        uint8_t     UPD_TCBRC_REPEAT;
        uint8_t     UPD_ROM_CURRENT; // ROM average of current frame
        uint8_t     UPD_ROM_ZERO; // ROM zero percentage (255 is 100%)
        uint8_t     UPD_CQMEnabled;
        uint8_t     UPD_TempCurrentlayer;
        uint8_t     UPD_TempScalable;

        uint8_t     RSVD8[62];
    };

    typedef struct _HUC_MODE_COST
    {
        uint8_t RSVD[24];
    } HUC_MODE_COST;

    struct VdencAv1HucBrcConstantData
    {
        HUC_MODE_COST CONST_ModeCosts[52];

        int8_t        CONST_QPAdjTabI[45];       //(N_INST_RATE_THRESHLDS+1)x(N_DEV_THRESHLDS+1) matrix data
        int8_t        CONST_QPAdjTabP[45];       //(N_INST_RATE_THRESHLDS+1)x(N_DEV_THRESHLDS+1) matrix data
        int8_t        CONST_QPAdjTabB[45];       //(N_INST_RATE_THRESHLDS+1)x(N_DEV_THRESHLDS+1) matrix data

        int8_t        CONST_DistQPAdjTabI[81];   //(N_DEV_THRESHLDS+1)x(N_DISTORION_THRESHLDS+1) QP deltas for I frames
        int8_t        CONST_DistQPAdjTabP[81];   //(N_DEV_THRESHLDS+1)x(N_DISTORION_THRESHLDS+1) QP deltas for P frames
        int8_t        CONST_DistQPAdjTabB[81];   //(N_DEV_THRESHLDS+1)x(N_DISTORION_THRESHLDS+1) QP deltas for B frames; no needed for Vp8 - to clean up

        uint8_t       CONST_LoopFilterLevelTabLuma[256];
        uint8_t       CONST_LoopFilterLevelTabChroma[256];
        uint8_t       RSVD[38];                  // mbz
    };

    class Av1BrcUpdatePkt : public EncodeHucPkt
    {
    public:
        Av1BrcUpdatePkt(MediaPipeline* pipeline, MediaTask* task, CodechalHwInterfaceNext* hwInterface) :
            EncodeHucPkt(pipeline, task, hwInterface)
        {
            m_featureManager = m_pipeline->GetPacketLevelFeatureManager(Av1Pipeline::Av1VdencPacket);
        }

        virtual ~Av1BrcUpdatePkt() {}

        virtual MOS_STATUS Init() override;

        MOS_STATUS Submit(MOS_COMMAND_BUFFER *commandBuffer, uint8_t packetPhase = otherPacket) override;

        //!
        //! \brief  Calculate Command Size
        //!
        //! \param  [in, out] commandBufferSize
        //!         requested size
        //! \param  [in, out] requestedPatchListSize
        //!         requested size
        //! \return MOS_STATUS
        //!         status
        //!
        MOS_STATUS CalculateCommandSize(
            uint32_t &commandBufferSize,
            uint32_t &requestedPatchListSize) override;

        //!
        //! \brief  Get Packet Name
        //! \return std::string
        //!
        virtual std::string GetPacketName() override
        {
            return "BRCUPDATE_PASS" + std::to_string((uint32_t)EncodeHucPkt::m_pipeline->GetCurrentPass());
        }

    protected:
        virtual MOS_STATUS AllocateResources() override;

        virtual MOS_STATUS ConstructBatchBufferHuCBRC(PMOS_RESOURCE batchBuffer);
        MOS_STATUS         ConstructPakInsertHucBRC(PMOS_RESOURCE batchBuffer);
        virtual MOS_STATUS AddAvpPicStateBaseOnTile(MOS_COMMAND_BUFFER& cmdBuffer, SlbData &slbbData);
        Av1BasicFeature *m_basicFeature = nullptr;  //!< Av1 Basic Feature used in each frame

        virtual MOS_STATUS SetConstDataHuCBrcUpdate();

        MHW_SETPAR_DECL_HDR(HUC_IMEM_STATE);
        MHW_SETPAR_DECL_HDR(HUC_DMEM_STATE);
        MHW_SETPAR_DECL_HDR(HUC_VIRTUAL_ADDR_STATE);
        MHW_SETPAR_DECL_HDR(AVP_PIC_STATE);
        MHW_SETPAR_DECL_HDR(VD_PIPELINE_FLUSH);

        MOS_STATUS AddAllCmds_AVP_SEGMENT_STATE(PMOS_COMMAND_BUFFER cmdBuffer) const;

        MOS_STATUS AddAllCmds_AVP_PAK_INSERT_OBJECT(PMOS_COMMAND_BUFFER cmdBuffer) const;
#if USE_CODECHAL_DEBUG_TOOL
        virtual MOS_STATUS DumpInput() override;
        virtual MOS_STATUS DumpOutput() override;
#endif

        static constexpr uint32_t               m_vdboxHucAv1BrcUpdateKernelDescriptor = 19;//!< Huc AV1 Brc init kernel descriptor

        // Batch Buffer for VDEnc
        MOS_RESOURCE                            m_vdencReadBatchBuffer[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM][VDENC_BRC_NUM_OF_PASSES];  //!< VDEnc read batch buffer
        MOS_RESOURCE                            m_vdencPakInsertBatchBuffer[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM];                      //!< VDEnc read batch buffer
        MOS_RESOURCE                            m_vdencBrcConstDataBuffer[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM];                         //!< VDEnc brc constant data buffer

        MOS_RESOURCE                            m_dataFromPicsBuffer = {}; //!< Data Buffer of Current and Reference Pictures for Weighted Prediction
        uint32_t                                m_vdenc2ndLevelBatchBufferSize[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM] = { 0 };
        MOS_RESOURCE                            m_vdencBrcUpdateDmemBuffer[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM][VDENC_BRC_NUM_OF_PASSES];  //!< VDEnc BrcUpdate DMEM buffer

        uint32_t                                m_miBatchBufferEndCmdSize = 0;                     //!< Size of MI_BATCH_BUFFER_END cmd
        uint32_t                                m_cmd2StartInBytes = 0;
        uint32_t                                m_vdencBrcUpdateDmemBufferSize = sizeof(VdencAv1HucBrcUpdateDmem);                //!< Offset of BRC update DMEM buffer
        uint32_t                                m_vdencBrcConstDataBufferSize = sizeof(VdencAv1HucBrcConstantData);                 //!< Offset of BRC const data buffer

        std::shared_ptr<MediaFeatureManager::ManagerLite> m_featureManager = nullptr;

        MOS_RESOURCE m_vdencBrcInitDmemBuffer[CODECHAL_ENCODE_RECYCLED_BUFFER_NUM] = {}; //!< VDEnc BrcInit DMEM buffer

    MEDIA_CLASS_DEFINE_END(encode__Av1BrcUpdatePkt)
    };

}  // namespace encode
#endif
