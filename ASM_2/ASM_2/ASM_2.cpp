
#include <iostream>

int main()
{
    char s[1024];
    char str1[] = "test";
    char str2[] = "_13qwer";
    char f[] = "%s";
    _asm
    {
        lea esi, [str1]
        lea edi, [s]

        FOR_1:
        lodsb
            stosb
            cmp al, 0
            jnz FOR_1

            lea esi, [str2]
            dec edi

            FOR_2 :
        lodsb
            stosb
            cmp al, 0
            jnz FOR_2
    }
    std::cout << s;
}
