#include<stdio.h>
#include<windows.h>

DWORD GetHash(char *fun_name)
{
	DWORD digest=0;
	while(*fun_name)         //挨个字符进行双字节转换循环右移
{
		digest=((digest<<25)|(digest>>7));  //循环右移7位		
    digest+=*fun_name;                  //累加		
    fun_name++;
	}
	return digest;
}

main()
{
	DWORD hash;
	hash=GetHash("MessageBoxA");           //计算API messagebox的摘要digest
  printf("result of hash is %.8x\n",hash);
}
