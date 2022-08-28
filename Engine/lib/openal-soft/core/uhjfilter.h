#ifndef CORE_UHJFILTER_H
#define CORE_UHJFILTER_H

#include <array>

#include "almalloc.h"
#include "alspan.h"
#include "bufferline.h"
#include "resampler_limits.h"


struct DecoderBase {
    virtual ~DecoderBase() = default;

    virtual void decode(const al::span<float*> samples, const size_t samplesToDo,
        const size_t forwardSamples) = 0;

    /**
     * The width factor for Super Stereo processing. Can be changed in between
     * calls to decode, with valid values being between 0...0.7.
     */
    float mWidthControl{0.593f};

    float mCurrentWidth{-1.0f};
};


struct UhjFilterBase {
    /* The filter delay is half it's effective size, so a delay of 128 has a
     * FIR length of 256.
     */
    static constexpr size_t sFilterDelay{128};
};

struct UhjEncoder : public UhjFilterBase {
    /* Delays and processing storage for the unfiltered signal. */
    alignas(16) std::array<float,BufferLineSize+sFilterDelay> mS{};
    alignas(16) std::array<float,BufferLineSize+sFilterDelay> mD{};

    /* History for the FIR filter. */
    alignas(16) std::array<float,sFilterDelay*2 - 1> mWXHistory{};

    alignas(16) std::array<float,BufferLineSize + sFilterDelay*2> mTemp{};

    /**
     * Encodes a 2-channel UHJ (stereo-compatible) signal from a B-Format input
     * signal. The input must use FuMa channel ordering and UHJ scaling (FuMa
     * with an additional +3dB boost).
     */
    void encode(float *LeftOut, float *RightOut, const al::span<const float*const,3> InSamples,
        const size_t SamplesToDo);

    DEF_NEWDEL(UhjEncoder)
};


struct UhjDecoder : public DecoderBase, public UhjFilterBase {
    /* For 2-channel UHJ, shelf filters should use these LF responses. */
    static constexpr float sWLFScale{0.661f};
    static constexpr float sXYLFScale{1.293f};

    alignas(16) std::array<float,BufferLineSize+MaxResamplerEdge+sFilterDelay> mS{};
    alignas(16) std::array<float,BufferLineSize+MaxResamplerEdge+sFilterDelay> mD{};
    alignas(16) std::array<float,BufferLineSize+MaxResamplerEdge+sFilterDelay> mT{};

    alignas(16) std::array<float,sFilterDelay-1> mDTHistory{};
    alignas(16) std::array<float,sFilterDelay-1> mSHistory{};

    alignas(16) std::array<float,BufferLineSize+MaxResamplerEdge + sFilterDelay*2> mTemp{};

    /**
     * Decodes a 3- or 4-channel UHJ signal into a B-Format signal with FuMa
     * channel ordering and UHJ scaling. For 3-channel, the 3rd channel may be
     * attenuated by 'n', where 0 <= n <= 1. So to decode 2-channel UHJ, supply
     * 3 channels with the 3rd channel silent (n=0). The B-Format signal
     * reconstructed from 2-channel UHJ should not be run through a normal
     * B-Format decoder, as it needs different shelf filters.
     */
    void decode(const al::span<float*> samples, const size_t samplesToDo,
        const size_t forwardSamples) override;

    DEF_NEWDEL(UhjDecoder)
};

struct UhjStereoDecoder : public UhjDecoder {
    /**
     * Applies Super Stereo processing on a stereo signal to create a B-Format
     * signal with FuMa channel ordering and UHJ scaling. The samples span
     * should contain 3 channels, the first two being the left and right stereo
     * channels, and the third left empty.
     */
    void decode(const al::span<float*> samples, const size_t samplesToDo,
        const size_t forwardSamples) override;

    DEF_NEWDEL(UhjStereoDecoder)
};

#endif /* CORE_UHJFILTER_H */
