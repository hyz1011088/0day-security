//该代码主要实现使用编码后的shellcode调用messagebox
////////////////////////////////////////////////////////////////////////////////////////解码函数
char final_sc_44[] = 
"\x83\xC0\x14"          //ADD EAX,14
"\x33\xC9"             //XOR ECX,ECX
"\x8A\x1C\x08"           //MOV BL,BYTE PTR DS:[EAX+ECX]
"\x80\xF3\x44"          //XOR BL,44   //notice 0x44 is taken as temp key to decode !
"\x88\x1C\x08"           //MOV BYTE PTR DS:[EAX+ECX],BL
"\x41"               //INC ECX
"\x80\xFB\x90"          //CMP BL,90
"\x75\xF1"            //JNZ SHORT decoder.00401034
////////////////////////////////////////////////////////////////////////////////////////解码函数的汇编码
/*
void main()
{
_asm
{
  add eax,0x14      //越过decoder（decode为20字节大小），记录shellcode的起始地址
  xor ecx,ecx       //清零ecx，ecx是循环控制变量
decode_loop:
  mov bl,[eax,ecx]   //将内存中shellcode数据取出赋给bl
  xor bl,0x44        //进行异或操作返回真实shellcode值
  mov [eax+ecx],bl   //将bl数据写到shellcode内存中
  inc ecx            //移位
  cmp bl,0xC0        //判断是否到结尾
  jne decode_loop
}
}
*/
////////////////////////////////////////////////////////////////////////////////////////
"\xb8\x2c\x2e\x4e\x7c\x5a\x2c\x27\xcd\x95\x0b\x2c\x76\x30\xd5\x48"
"\xcf\xb0\xc9\x3a\xb0\x77\x9f\xf3\x40\x6f\xa7\x22\xff\x77\x76\x17"
"\x2c\x31\x37\x21\x36\x10\x77\x96\x20\xcf\x1e\x74\xcf\x0f\x48\xcf"
"\x0d\x58\xcf\x4d\xcf\x2d\x4c\xe9\x79\x2e\x4e\x7c\x5a\x31\x41\xd1"
"\xbb\x13\xbc\xd1\x24\xcf\x01\x78\xcf\x08\x41\x3c\x47\x89\xcf\x1d"
"\x64\x47\x99\x77\xbb\x03\xcf\x70\xff\x47\xb1\xdd\x4b\xfa\x42\x7e"
"\x80\x30\x4c\x85\x8e\x43\x47\x94\x02\xaf\xb5\x7f\x10\x60\x58\x31"
"\xa0\xcf\x1d\x60\x47\x99\x22\xcf\x78\x3f\xcf\x1d\x58\x47\x99\x47"
"\x68\xff\xd1\x1b\xef\x13\x25\x79\x2e\x4e\x7c\x5a\x31\xed\x77\x9f"
"\x17\x2c\x33\x21\x37\x30\x2c\x22\x25\x2d\x28\xcf\x80\x17\x14\x14"
"\x17\xbb\x13\xb8\x17\xbb\x13\xbc\xd4";

int main()
{
    __asm
    {
        lea eax, final_sc_44
        push        eax
        ret

    }
    return 0;
}
