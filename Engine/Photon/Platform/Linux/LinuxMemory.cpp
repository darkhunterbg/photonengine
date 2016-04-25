#include "../../PE.h"

#if(PLATFORM == LINUX)

#include <stdlib.h>

namespace photon
{
namespace platform
{
    void* AllocateMemory(size_t size, void* baseAddress)
    {
        return malloc(size);
    }

    void* DeallocateMemory(void* address, size_t size)
    {
        free(address);
    }
}
}

#endif