
#include <iostream>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char str[255];
	char FindString[255];
	char f[] = "%s";
	char fd[] = "%d\n";
	char outStr1[256] = "Введите строку:\n";
	char outStr2[256] = "Введите что нужно найти с конца:\n";
	char outPut[256] = "Итог:\n";

	__asm {

		lea edx, outStr1
		push edx
		lea ecx, f
		push ecx
		call printf
		add esp, 8

		lea eax, str
		push eax
		lea ecx, f
		push ecx
		call scanf
		add esp, 8

		lea edx, outStr2
		push edx
		lea ecx, f
		push ecx
		call printf
		add esp, 8

		lea eax, FindString
		push eax
		lea ecx, f
		push ecx
		call scanf
		add esp, 8

		lea edx, outPut
		push edx
		lea ecx, f
		push ecx
		call printf
		add esp, 8

		lea eax, str
		dec eax
		mov ecx, 0
		dec ecx

		CountLen :
		inc eax
			inc ecx
			cmp[eax], 0
			jnz CountLen

			lea ebx, FindString
			dec ebx
			mov edx, 0
			dec edx

			CountLenSub :
		inc ebx
			inc edx
			cmp[ebx], 0
			jnz CountLenSub


			push edx
			cmp edx, ecx
			jg NoMatch
			cmp edx, 0
			jz NoMatch

			dec eax
			dec ebx

			Cycle :
		cmp edx, 0
			jz OutPutResult
			cmp ecx, 0
			jz NoMatch
			push ecx
			mov ch, [eax]
			mov cl, [ebx]
			cmp ch, cl
			pop ecx
			jz skip
			pop edx
			lea ebx, FindString
			add ebx, edx
			push edx
			dec ebx
			push ecx
			mov ch, [eax]
			mov cl, [ebx]
			cmp ch, cl
			pop ecx
			jz skip
			dec eax
			dec ecx
			jmp Cycle
			skip :
		dec eax
			dec ebx
			dec ecx
			dec edx
			jmp Cycle

			NoMatch :
		mov ecx, -1
			OutPutResult :
			push ecx
			lea ecx, fd
			push ecx
			call printf
			add esp, 12

	}
}