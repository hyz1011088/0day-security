#include <stdio.h>
#include <windows.h>

int main()
{
    HLOCAL h1, h2, h3, h4;
    HANDLE hp;
    hp = HeapCreate(0, 0, 0);
    __asm int 3
    h1 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h2 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    h3 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 16);
    h4 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 24);
    HeapFree(hp, 0, h1);
    HeapFree(hp, 0, h2);
    HeapFree(hp, 0, h3);
    HeapFree(hp, 0, h4);
    h2 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 16);
    HeapFree(hp, 0, h2);
}
