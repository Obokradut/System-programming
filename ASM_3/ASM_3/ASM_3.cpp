
#include <iostream>
#include <Windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char str[256];
    char s[256] = "\n";
    int First;
    int Len;
    char EmptyString[] = " ";
    char f[] = "%s";
    char fd[] = "%d";
    std::cout << "Введите строку:\n";
    char outStr1[256] = "Введите начало копирования:\n";
    char outStr2[256] = "Введите длину копирования:\n";

    __asm
    {
        lea esi, str

        push esi

        lea ecx, f

        push ecx

        call scanf

        add esp, 8

        lea ebx, outStr1

        push ebx

        lea ecx, f

        push ecx

        call printf

        add esp, 8

        lea ebx, First

        push ebx

        lea ecx, fd

        push ecx

        call scanf

        add esp, 8

        lea ebx, outStr2

        push ebx

        lea ecx, f

        push ecx

        call printf

        add esp, 8

        lea ebx, Len

        push ebx

        lea ecx, fd

        push ecx

        call scanf

        add esp, 8

        lea ecx, fd
        mov ecx, -1
        dec esi

        push edx
        mov edx, First

        lea ecx, fd
        mov ecx, -1
        dec esi

        lea ebx, str
        push ebx
        dec ebx

        LengthStr :
        inc ecx
            inc ebx
            mov al, [ebx]
            cmp al, 0
            jnz LengthStr
            push ecx

            StartCopy :
        cmp First, 0
            jge LengthCopy

            mov First, 0

            LengthCopy :
            cmp Len, 0
            jl StrNoChange

            FirstBiggerLength :
        cmp First, ecx
            jg StrNoChange

            add edx, Len

            CheckLengthCopy :

        cmp edx, ecx
            jbe Later
            mov edx, ecx

            Later :
        add esp, 8
            mov ecx, -1
            dec esi

            lea esi, [str]
            lea edi, [s]
            push edi
            dec esi

            mov edx, First

            Write :
        inc esi
            inc ecx
            cmp ecx, edx
            jne Write

            add edx, Len

            ContinueWrite :
        inc ecx
            lodsb
            stosb
            cmp ecx, edx
            jne ContinueWrite

            jmp End

            StrNoChange :
        add esp, 8
            mov ecx, -1
            dec esi
            lea esi, [EmptyString]
            lea edi, [s]
            push edi

            ContinueNoChange :
        lodsb
            stosb
            cmp al, 0
            jnz ContinueNoChange

            End :
        pop edi
            pop esi
    }
    std::cout << "Итог: " << s;
}

