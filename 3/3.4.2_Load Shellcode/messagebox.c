//该代码主要是在window xp sp3环境下调用messagebox，参考0day软件漏洞。此shellcode比较规范，不容易出现堆栈调用内存错误。
//注意eax和ret指令的使用
#include <stdio.h>  
#include <windows.h>
char shellcode[] = "\x66\x81\xEC\x40\x04"      //sub sp,440 用于抬高栈帧，以保护shellcode，这一点比较重要
                       "\x33\xDB\x53\x68\x77\x65\x73\x74\x68\x66\x61\x69"   //调用messagebox
                       "\x6C\x8B\xC4\x53\x50\x50\x53\xB8\xEA\x07\xD5\x77"
                       "\xFF\xD0\x53\xB8\xA2\xBF\x81\x7C\xFF\xD0";

void main()  
{
	LoadLibrary("user32.dll");             //加载user32.dll，以后续调用messagebox， 程序中不加这一句会报错。
  
 __asm
 {
   lea eax,shellcode
   push	eax
   ret             //ret指令会将push进去的shellcode在栈中的起始地址弹给EIP，让处理器调到栈区去执行shellcode
 }
}


//下面代码即会出现不能弹出messagebox的情况，原因可以参考:https://github.com/hyz1011088/My_Alpha2/blob/master/my_alpha2_shellcode/Ascii_shellcode_messagebox.c
/*#include <stdio.h>  
#include <windows.h>
char shellcode[] = "\x66\x81\xEC\x40\x04"      //sub sp,440 用于抬高栈帧，以保护shellcode，这一点比较重要
                       "\x33\xDB\x53\x68\x77\x65\x73\x74\x68\x66\x61\x69"   //调用messagebox
                       "\x6C\x8B\xC4\x53\x50\x50\x53\xB8\xEA\x07\xD5\x77"
                       "\xFF\xD0\x53\xB8\xA2\xBF\x81\x7C\xFF\xD0";

void main()  
{
	LoadLibrary("user32.dll");             //加载user32.dll，以后续调用messagebox， 程序中不加这一句会报错。
  
 __asm
 {
   lea esp,shellcode
   jum esp
 }
}*/
