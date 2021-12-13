#include <iostream>

int main()
{
    char s[256];
    char f[] = "%s";
    char fd[] = "%d\n";
    _asm {
         lea ebx, s
         push ebx
         lea ecx, f
         push ecx
         call scanf
         add esp, 8
         mov ecx, -1  
         dec ebx
         b1 :
         inc ecx
         inc ebx
         mov al, [ebx]
         cmp al, 0
         jnz b1
         push ecx
         lea ebx, fd
         push ebx
         call printf
         add esp, 8
    }
}
