#ifndef EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_H_
#define EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_H_

// This is not yet fully tested on all types - add support for varying Data and Checksum types

#include <stdint.h>

namespace Embedded {
namespace Utility {
namespace Checksum {
namespace Fletcher {

typedef uint8_t  Data;
typedef uint16_t ChecksumType;

// Default to FF for communications (EEPROM uses Zero) - the value is where to "roll over"
enum ZeroValue
{
    Zero = 255, // FF should NEVER appear in the checksum
    FF   = 256  // 0  should NEVER appear in the checksum
};

// Only define constants in specializations - a bad ZeroValue should fail compile
template<ZeroValue zeroValue> class Constants
{
public:
    static const ChecksumType ChecksumLimit;    // lint complains if this line isn't here
};

template <> class Constants<Zero>
{
public:
    static const ChecksumType ChecksumLimit = 255;
    static const ChecksumType ChecksumInit  = 0;
};

template <> class Constants<FF>
{
public:
    static const ChecksumType ChecksumLimit = 256;
    static const ChecksumType ChecksumInit  = 255;
};

template<ZeroValue zeroValue>
void initialize(ChecksumType * checksum1, ChecksumType * checksum2);

template<ZeroValue zeroValue>
void calculate(Data data, ChecksumType * checksum1, ChecksumType * checksum2);

template<ZeroValue zeroValue>
void calculate(const Data * data, uint16_t len, ChecksumType * checkA, ChecksumType * checkB);

// These functions exist until compilers and lint support default template parameters in functions
//   when they do, add default parameters above and delete these
void initialize(ChecksumType * checksum1, ChecksumType * checksum2);
void calculate(Data data, ChecksumType * checksum1, ChecksumType * checksum2);
void calculate(const Data * data, uint16_t len, ChecksumType * checkA, ChecksumType * checkB);


}   // end namespace Checksum::Fletcher
}
}
}

#include <embedded/utility/checksum/fletcher/Fletcher.hpp>

#endif  // EMBEDDED_UTILITY_CHECKSUM_FLETCHER_FLETCHER_H_

