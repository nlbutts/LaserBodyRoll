#ifndef EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_HPP_
#define EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_HPP_

namespace Embedded {
namespace Utility {
namespace Checksum {
namespace Fletcher {

template<ZeroValue zeroValue>
inline void initialize(ChecksumType * checksum1, ChecksumType * checksum2)
{
    *checksum1 = Constants<zeroValue>::ChecksumInit;
    *checksum2 = Constants<zeroValue>::ChecksumInit;
}

template<ZeroValue zeroValue>
inline void calculate(Data data, ChecksumType * checksum1, ChecksumType * checksum2)
{
    *checksum1 += (data & 0xFF);
    if (*checksum1 >= Constants<zeroValue>::ChecksumLimit)
    {
        *checksum1 -= 255;
    }
    *checksum2 += *checksum1;
    if (*checksum2 >= Constants<zeroValue>::ChecksumLimit)
    {
        *checksum2 -= 255;
    }
}

template<ZeroValue zeroValue>
inline void calculate(const Data * data, uint16_t len, ChecksumType * checkA, ChecksumType * checkB)
{
    ChecksumType sumA = Constants<zeroValue>::ChecksumInit;
    ChecksumType sumB = Constants<zeroValue>::ChecksumInit;

    for (uint16_t x = 0; x < len; ++x)
    {
        calculate<zeroValue>(data[x], &sumA, &sumB);
    }
    *checkA = sumA;
    *checkB = sumB;
}

// These functions exist until compilers and lint support default template parameters in functions.
//   When they do, add default parameters in the header and delete these
inline void initialize(ChecksumType * checksum1, ChecksumType * checksum2)
{
    initialize<FF>(checksum1, checksum2);
}

inline void calculate(Data data, ChecksumType * checksum1, ChecksumType * checksum2)
{
    calculate<FF>(data, checksum1, checksum2);
}

inline void calculate(const Data * data, uint16_t len, ChecksumType * checkA, ChecksumType * checkB)
{
    calculate<FF>(data, len, checkA, checkB);
}

}
}
}
}

#endif // EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_HPP_


