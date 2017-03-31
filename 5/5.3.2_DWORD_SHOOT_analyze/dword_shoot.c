#include <windows.h>

int main()
{
    HLOCAL h1, h2, h3, h4, h5, h6;
    HANDLE hp;
    hp = HeapCreate(0, 0x1000, 0x10000);
    h1 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h2 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h3 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h4 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h5 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h6 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);

    _asm int 3    //used to break the process
    //free the odd blocks to prevent coalesing
    HeapFree(hp, 0, h1); 
    HeapFree(hp, 0, h3); 
    HeapFree(hp, 0, h5); //now freelist[2] got 3 entries

    //will allocate from freelist[2] which means unlink the last entry (h5)
    h1 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8); 

    return 0;
}
