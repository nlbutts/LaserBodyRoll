/**
 * Copyright (c) 2013 Appareo Systems, LLC.
 * 1810 NDSU Research Park Circle North
 * Fargo ND, 58102
 * All rights reserved.
 *
 * This is the confidential and proprietary information of Appareo Systems, LLC. You shall not
 * disclose such confidential information and shall use it only in accordance with the terms
 * of the license agreement you entered into with Appareo.
 *
 * File: CircularBufferManager.h
 * Creator: Kane Iverson
 * Date: 8/1/2013
 *
 * Copyright Version 1.0
 */

#ifndef APPAREO_UTILITY_CIRCULARBUFFERMANAGER_H_
#define APPAREO_UTILITY_CIRCULARBUFFERMANAGER_H_

#include <stdint.h>
#include <limits.h>

namespace Appareo {
namespace Utility {
namespace CircularBuffer {

typedef uint32_t Count;
typedef uint32_t PhysicalAddress;   // physical address of the actual storage medium
typedef uint32_t LogicalAddress;    // starts at zero, ends at size - 1 

class Pointer
{
    public:

    private:
        Pointer(void);
        Pointer(LogicalAddress address);
        LogicalAddress _address;
        friend class Manager;
};

/*
 * This class represents a circular buffer that does contain its storage.
 *
 * _head points to the beginning of the oldest message
 * _tail points to where the next message will be stored
 *
 * If _head == _tail, the buffer is empty
 */

class Manager
{
    public:
        Manager(PhysicalAddress start, Count size); // start is a physical address
        
        Pointer getPointerFromLogicalAddress (LogicalAddress  address) const;
        Pointer getPointerFromPhysicalAddress(PhysicalAddress address) const;

        PhysicalAddress getPhysicalAddressFromPointer(const Pointer & pointer) const;
        LogicalAddress  getLogicalAddressFromPointer(const Pointer & pointer) const;
        LogicalAddress  getLogicalAddressFromHead() const;
        LogicalAddress  getLogicalAddressFromTail() const;

        Pointer getHead() const;
        Pointer getTail() const;
        Count   getSize() const;
        Count   getAvailableSpace() const;

        bool setHead(const Pointer & pointer);
        bool setTail(const Pointer & pointer);
        bool advanceHead(Count number);
        bool advanceTail(Count number);

        bool set(Pointer & toBeSet, const LogicalAddress address) const;
        bool set(Pointer & toBeSet, const Pointer & pointer) const;
        bool advance(Pointer & pointer, Count number) const; 

        Count leadsBy(const Pointer & leader, const Pointer & follower) const; 

        static const uint32_t Error = ULONG_MAX; 

    private:
        PhysicalAddress _start;
        Count   _size;
        Pointer _head;
        Pointer _tail;
};

} //CircularBuffer
} //Utility
} //Appareo

#endif // APPAREO_UTILITY_CIRCULARBUFFERMANAGER_H_
