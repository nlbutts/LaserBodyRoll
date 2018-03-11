#ifndef DSP_H
#define DSP_H

#include <stdint.h>
#include <array>

#ifdef ARM_MATH_CM4
#include <arm_math.h>
#else
#include <math.h>
#warning "DSP architecture is undefined"
#include <embedded/utility/filter/IIRFilterSOS.h>
// TODO: Add in mock interface
#endif

namespace Embedded {
namespace Micro {
namespace Adapter {
namespace DSP {

/**
 * @brief Perform a dot multiply of two arrays
 * result[x] = a[x]*b[x], where x = [0,n)
 *
 * @param a First input array
 * @param b Second input array
 * @param result Array to put the dot multiply result in
 * @param n Number of elements to multiply
 */
inline void vectorDotMultiply(const float* a, const float* b, float* result, uint32_t n)
{
    #ifdef ARM_MATH_CM4
    arm_mult_f32(const_cast<float*>(a), const_cast<float*>(b), result, n);
    #else
    for(uint32_t i = 0; i < n; ++i, ++a, ++b, ++result)
    {
        *result = (*a)*(*b);
    }
    #endif
}

/**
 * @brief Data structure needed for performing an FFT
 */
#ifdef ARM_MATH_CM4
using RealFFTInstance = arm_rfft_fast_instance_f32;
using IIRFilterInstance = arm_biquad_cascade_df2T_instance_f32;
#else
typedef void* RealFFTInstance;
using IIRFilterInstance = void*;
#endif

/**
 * @brief Initialize a real FFT instance structure
 * @details This must be called on the RealFFTInstance before using it to
 *          compute an FFT
 *
 * @param instance Structure to initialize
 * @param fftLen Length of the FFTs
 */
inline void initializeRealFFT(RealFFTInstance* instance, uint16_t fftLen)
{
    #ifdef ARM_MATH_CM4
    (void) arm_rfft_fast_init_f32(instance, fftLen);
    #else
    #endif
}


/**
 * @brief Perform a real FFT
 *
 * @param instance FFT instance. Must be initialized first with initializeRealFFT()
 * @param data Input data to perform the FFT on
 * @param output Ouput of the FFT process
 * @param inverse ture for an inverse FFT operation, else false for an FFT
 */
inline void computeRealFFT(RealFFTInstance* instance, float* data, float* output, bool inverse)
{
    #ifdef ARM_MATH_CM4
    arm_rfft_fast_f32(instance, data, output, inverse ? 1 : 0);
    #else
    #endif
}

/**
* Calculate the square root of a single value
*
* @param in a float to calculate the square root on
* @return float the return value
*/
inline float sqrt(float in)
{
    #ifdef ARM_MATH_CM4
    float out;
    arm_sqrt_f32(in, &out);
    return out;
    #else
    return sqrt(in);
    #endif
}


/**
 * @brief Take the ABS of a vector
 *
 * @param in Input vector
 * @param out Output vector
 * @param n Number of elements in the vector the take the ABS of
 */
inline void vectorABS(float* in, float* out, uint32_t n)
{
    #ifdef ARM_MATH_CM4
    arm_abs_f32(in, out, n);
    #else
    for(uint32_t i = 0; i < n; ++i)
    {
        out[i] = static_cast<float>(fabs(in[i]));
    }
    #endif
}

/**
* A template function to apply a scaler to a vector
*
* @param scalar the scale to apply to the vector
* @param in the input array
* @param out the output array
*/
template <int N>
inline void scaleVector(float scalar, const std::array<float, N> &in, std::array<float, N> &out)
{
    #ifdef ARM_MATH_CM4
    arm_scale_f32(const_cast<float*>(in.data()), scalar, out.data(), N);
    #else
    for(uint32_t i = 0; i < N; ++i)
    {
        out[i] = in[i] * scalar;
    }
    #endif
}

/**
* Find the max value in a vector
*
* @param in the input array
* @return float the max value
*/
template <int N>
inline float maxValueVector(const std::array<float, N> &in)
{
    float maxValue = 0.0f;
    #ifdef ARM_MATH_CM4
    arm_max_f32(const_cast<float*>(in.data()), N, &maxValue, NULL);
    #else
    for(uint32_t i = 0; i < N; ++i)
    {
        if (in[i] > maxValue)
        {
            maxValue = in[i];
        }
    }
    #endif

    return maxValue;
}

/**
 * @brief Number of coefficents per second or section
 */
static constexpr uint32_t   NUMBER_OF_COEFF_PER_SOS         = 5;
/**
 * @brief Number of state variables per stage
 */
static constexpr uint32_t   NUMBER_OF_STATE_VARS_PER_SOS    = 2;

template<int stages, int blockSize>
class BiquadCascadeDF2T
{
public:
    BiquadCascadeDF2T(const std::array<float, stages * NUMBER_OF_COEFF_PER_SOS> &coeff)
    {
        #ifdef ARM_MATH_CM4
        arm_biquad_cascade_df2T_init_f32(&_instance, stages, const_cast<float*>(coeff.data()), _state.data());
        #else
        Embedded::Utility::Filter::IIRFilterCoefficients c[stages];
        for (int i = 0; i < stages; ++i)
        {
            c[i].gain = 1.0f;
            c[i].b[0] = coeff[stages*i + 0];
            c[i].b[1] = coeff[stages*i + 1];
            c[i].b[2] = coeff[stages*i + 2];
            c[i].a[0] = 1.0f;
            c[i].a[1] = coeff[stages*i + 3];
            c[i].a[2] = coeff[stages*i + 4];
        }

        _instance.configureFilter(stages, c);
        #endif
    }
    ~BiquadCascadeDF2T() {};

    void filter(const std::array<float, blockSize> &src, std::array<float, blockSize> &dst)
    {
        #ifdef ARM_MATH_CM4
        arm_biquad_cascade_df2T_f32(&_instance, const_cast<float*>(src.data()), dst.data(), blockSize);
        #else
        auto srcIT = src.cbegin();
        auto dstIT = dst.begin();
        for(;srcIT != src.cend(); ++srcIT, ++dstIT)
        {
            *dstIT = _instance.filterSample(*srcIT);
        }
        #endif
    }

    void resetFilter()
    {
        #ifdef ARM_MATH_CM4
        for (float &v : _state)
        {
            v = 0.0f;
        }

        #else
        _instance.seedFilter(0, 0.01);
        #endif
    }

private:
    #ifdef ARM_MATH_CM4
    std::array<float, stages * NUMBER_OF_STATE_VARS_PER_SOS>    _state;
    IIRFilterInstance                                           _instance;
    #else
    Appareo::Utility::Filter::IIRFilterSOS                      _instance;
    #endif


};

} // namespace DSP
} // namespace Adapter
} // namespace Micro
} // namespace Embedded

#endif /* DSP_H */