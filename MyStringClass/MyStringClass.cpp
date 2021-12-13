#include <iostream>
#include <Windows.h>
using namespace std;

class MyString
{
private:
	char* Str;
	int length;
public:

	// Консуктор
	MyString(const char* data = " ", int len = 0) : length(len)
	{
		Str = new char[length];
		for (int i = 0; i < len; i++)
			Str[i] = data[i];
	}


	// ОПЕРАТОРЫ
	// Ввод
	friend istream& operator>>(istream& in, MyString& str) {
		in >> str.Str;
		str.length = str.FindStringLength();
		return in;
	}
	// Вывод
	friend ostream& operator<<(ostream& out, const MyString& str) {
		out << str.Str;
		return out;
	}

	// Индекс, присваивание, конактенация
	char operator[] (const int index);
	friend MyString operator+(const MyString& str1, const MyString& str2) {
		MyString strres;
		strres.length = str1.length + str2.length;
		strres.Str = new char[strres.length];		
		int i = 0;
		for (int j = 0; i < strres.length; i++)
		{
			if (i < str1.length)
				strres.Str[i] = str1.Str[i];
			else
			{
				strres.Str[i] = str2.Str[j];
				j++;
			}
		}
		strres.Str[strres.length] = '\0';
		return strres;
	}
	MyString& operator= (const MyString& str) {
		Str = new char[str.length];
		int i;
		for (i = 0; i < str.length; ++i)
			Str[i] = str.Str[i];
		Str[i] = '\0';
		return *this;
	}

	// Условные операторы
	friend bool operator== (const MyString& str, const MyString& str2) {
		return (str.length == str2.length);
	}
	friend bool operator!= (const MyString& str, const MyString& str2) {
		return !(str == str2);
	}
	friend bool operator> (const MyString& str, const MyString& str2) {
		return (str.length > str2.length);
	}
	friend bool operator< (const MyString& str, const MyString& str2) {
		return (str.length < str2.length);
	}
	friend bool operator<= (const MyString& str, const MyString& str2) {
		return (str.length <= str2.length);
	}
	friend bool operator>= (const MyString& str, const MyString& str2) {
		return (str.length >= str2.length);
	}

	// МЕТОДЫ
	int FindStringLength()
	{
		int quantity;
		for (quantity = 0; Str[quantity] != '\0'; quantity++) {}
		return quantity;
	}

	MyString CopyThePart(MyString Str, int beginning_of_substr, int lenght_of_substr)
	{
		MyString ResultStr;		
		int d_pos = 0;

		if ((lenght_of_substr > 0) && (beginning_of_substr < Str.FindStringLength() + 1)) {
			if (beginning_of_substr < 0) {
				beginning_of_substr = 0;
			}
			if ((beginning_of_substr + lenght_of_substr) > Str.FindStringLength()) {
				lenght_of_substr = Str.FindStringLength();
			}
			for (d_pos; d_pos < lenght_of_substr; d_pos++)
			{
				ResultStr.Str[d_pos] = Str[beginning_of_substr];
				beginning_of_substr++;
			}
			ResultStr.Str[d_pos] = '\0';
			return ResultStr;
		}
		else
		{
			return Str;
		}
	}

	MyString DelSubstr(MyString Str, int beginning_of_substr, int lenght_of_substr){
		MyString ResultStr;
		int d_pos = 0, d_pos2 = 0;
		if (lenght_of_substr > 0) {
			if (beginning_of_substr < 0) {
				beginning_of_substr = 0;
			}
			if ((beginning_of_substr + lenght_of_substr) > Str.FindStringLength()) {
				lenght_of_substr = Str.FindStringLength();
			}
			d_pos = lenght_of_substr + beginning_of_substr;
			for (int i = beginning_of_substr; i < d_pos; i++) {
				ResultStr.Str[d_pos2++] = Str.Str[i];
			}
			for (; beginning_of_substr < Str.FindStringLength(); beginning_of_substr++) {
				ResultStr.Str[beginning_of_substr] = Str.Str[d_pos++];
			}
			return ResultStr;
		}
		else {	
			return Str;
		}		
	}

	MyString Inserting(MyString Str, int beginning_of_substr, MyString SubStr){
		int lenght_of_substr = FindStringLength();
		int d_pos = 0;
		if (beginning_of_substr < 0) {
			beginning_of_substr = 0;
		}
		if (beginning_of_substr < Str.FindStringLength()) {
			for (int i = Str.FindStringLength() - 1; i >= beginning_of_substr; i--) {
				Str.Str[i + SubStr.FindStringLength()] = Str.Str[i];
			}Str.Str[SubStr.FindStringLength() + Str.FindStringLength()] = '\0';
			for (int i = beginning_of_substr; i < beginning_of_substr + SubStr.FindStringLength(); i++) {
				Str.Str[i] = SubStr.Str[d_pos++];
			}
		}
		else {
			for (int i = Str.FindStringLength(); i < Str.FindStringLength() + SubStr.FindStringLength(); i++) {
				Str.Str[i] = SubStr.Str[d_pos++];
			}
		}
		Str.Str[SubStr.FindStringLength() + Str.FindStringLength()] = '\0';
		return Str;
	}

	int SubstringSearchStart(MyString Str, MyString SubStr)
	{				
		int d_pos = 0;
		int coincidence = 0;
		int first_in = -1;
		for (int i = 0; (coincidence != SubStr.FindStringLength()) && (i < Str.FindStringLength()); i++) {
			if (Str.Str[i] == SubStr.Str[d_pos++]) {
				if (coincidence == 0) {
					first_in = i;
				}
				coincidence++;
			}
			else {
				if (coincidence != 0) {
					i--;
				}
				d_pos = 0;
				coincidence = 0;
				first_in = -1;
			}
		}
		return first_in;
	}

	int SubstringSearchEnd(MyString Str, MyString SubStr)
	{
		int d_pos = SubStr.FindStringLength() - 1;
		int coincidence = 0;
		int first_in = -1;
		for (int i = Str.FindStringLength(); (coincidence != SubStr.FindStringLength()) && (i > 0); i--) {
			if (Str.Str[i] == SubStr.Str[d_pos--]) {
				if (coincidence == 0) {
					first_in = i;
				}
				coincidence++;
			}
			else {
				d_pos = SubStr.FindStringLength() - 1;
				coincidence = 0;
				first_in = -1;
			}
		}
		first_in -= SubStr.FindStringLength() - 1;
		return first_in;
	}

	MyString ReplacingSubstr(MyString Str1, MyString Str2, MyString Str3)
	{		
		int lenght_of_str1 = Str1.FindStringLength();
		int lenght_of_str2 = Str2.FindStringLength();
		int lenght_of_str3 = Str3.FindStringLength();

		int end = (Str3.FindStringLength() - Str2.FindStringLength()) + Str1.FindStringLength();

		int coincidence = 0, d_pos = 0;
		int first_in = -1;

		for (int i = 0; (coincidence != lenght_of_str2) && (i < lenght_of_str1); i++) {
			if (Str1.Str[i] == Str2.Str[d_pos++]) {
				if (coincidence == 0) {
					first_in = i;
				}
				coincidence++;
			}
			else {
				if (coincidence != 0) {
					i--;
				}
				d_pos = 0;
				coincidence = 0;
				first_in = -1;
			}
		}
		d_pos = 0;

		if (first_in != -1) {
			if ((first_in + lenght_of_str2 - 1) < lenght_of_str1) {
				if (lenght_of_str3 >= lenght_of_str2) {
					for (int i = lenght_of_str1 - 1; i > (first_in + lenght_of_str2 - 1); i--) {
						Str1.Str[i + (lenght_of_str3 - lenght_of_str2)] = Str1.Str[i];
					}
				}
				else
				{
					for (int i = first_in + lenght_of_str2; i < lenght_of_str1; i++) {
						Str1.Str[i - (lenght_of_str2 - 1)] = Str1.Str[i];
					}
				}
				for (int i = first_in; i < first_in + lenght_of_str3; i++) {
					Str1.Str[i] = Str3.Str[d_pos++];
				}
			}
			else {
				for (int i = lenght_of_str1; i < lenght_of_str1 + lenght_of_str3; i++) {
					Str1.Str[i] = Str3.Str[d_pos++];
				}
			}
			Str1.Str[end] = '\0';
		}
		return Str1;
	}

	MyString ReplacingAllSubstr(MyString Str1, MyString Str2, MyString Str3)
	{
		int lenght_of_str1 = Str1.FindStringLength();
		int lenght_of_str2 = Str2.FindStringLength();
		int lenght_of_str3 = Str3.FindStringLength();

		int end = (Str3.FindStringLength() - Str2.FindStringLength()) + Str1.FindStringLength();


		int d_pos = 0;
		int memory_pos = 0;
		int coincidence = 0;
		int first_in = 0;
		while (first_in != -1) {
			first_in = -1;
			coincidence = 0;
			d_pos = 0;
			lenght_of_str1 = 0;
			for (lenght_of_str1; Str1.Str[lenght_of_str1] != '\0'; lenght_of_str1++) {}; //Длина первой строки
			for (; (coincidence != lenght_of_str2) && (memory_pos < lenght_of_str1); memory_pos++) {
				if (Str1.Str[memory_pos] == Str2.Str[d_pos++]) {
					if (coincidence == 0) {
						first_in = memory_pos;
					}
					coincidence++;
				}
				else {
					if (coincidence != 0) {
						memory_pos--;
					}
					d_pos = 0;
					coincidence = 0;
					first_in = -1;
				}
			}
			memory_pos = first_in + lenght_of_str3;
			d_pos = 0;

			if (first_in != -1) {
				if ((first_in + lenght_of_str2 - 1) < lenght_of_str1) {
					if (lenght_of_str3 >= lenght_of_str2) {
						for (int i = lenght_of_str1 - 1; i > (first_in + lenght_of_str2 - 1); i--) {
							Str1.Str[i + (lenght_of_str3 - lenght_of_str2)] = Str1.Str[i];
						}
					}
					else
					{
						for (int i = first_in + lenght_of_str2; i < lenght_of_str1; i++) {
							Str1.Str[i - (lenght_of_str2 - 1)] = Str1.Str[i];
						}
					}
					for (int i = first_in; i < first_in + lenght_of_str3; i++) {
						Str1.Str[i] = Str3.Str[d_pos++];
					}
				}
				else {
					for (int i = lenght_of_str1; i < lenght_of_str1 + lenght_of_str3; i++) {
						Str1.Str[i] = Str3.Str[d_pos++];
					}
				}
				Str1.Str[(lenght_of_str3 - lenght_of_str2) + lenght_of_str1] = '\0';
			}
		}
		return Str1;
	}

	//Деструктор
	~MyString()
	{
	}
};
char MyString::operator[] (const int index) {
	return Str[index];
}

int main()
{
	//Для поддержки русского языка
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	MyString Str1, Str2, Str3, StrRes;
	char Choise;

	cout << "Вы хотите посмотреть методы(m) или операторы(o)\n";
	cout << "Выбор: ";
	cin >> Choise;

	if (Choise == 'o')
	{		
		cout << "Введите первую строку: ";
		cin >> Str1;		
		cout << "Ведите вторую строку: ";
		cin >> Str2;
		cout << "Позиция номер 0: " << Str1[0] << endl;
		cout << "Оператор [] проверен!\n";
		Str3 = Str1 + Str2;
		cout << "Str1 + Str3 = " << Str3;
		cout << "\nОператоры '+' и '=' проверены!\n";

		if (Str1 > Str2) {
			cout << "Str1 > Str2\n";
			cout << "Оператор > проверен!\n";
		}

		if (Str1 < Str2) {
			cout << "Str1 < Str2\n";
			cout << "Оператор < проверен!\n";
		}
			
		if (Str1 == Str2) {
			cout << "Str1 == Str2\n";
			cout << "Operators = checked!\n";
		}

		if (Str1 != Str2) {
			cout << "Str1 != Str2\n";
			cout << "Operators != checked!\n";
		}

		if (Str1 <= Str2) {
			cout << "Str1 <= Str2\n";
			cout << "Operators <= checked!\n";
		}

		if (Str1 >= Str2) {
			cout << "Str1 => Str2\n";
			cout << "Operators >= checked!\n";
		}		
	}	
	else if (Choise == 'm')
	{
		int Pos = 0, Start = 0, Len = 0;
		cout << "Выбирете метод для тестирования: \n 1 - FindStringLength \n 2 - Concatenation \n 3 - CopyThePart \n 4 - DelSubstr \n 5 - Inserting \n 6 - SubstringSearchStart \n 7 - SubstringSearchEnd \n 8 - ReplacingSubstr \n 9 - ReplacingAllSubstr ";
		cout << "\nВыбор: ";
		cin >> Choise;
		switch (Choise)
		{
		case '1':
			cout << "Введите строку: ";
			cin >> Str1;
			cout << "Результат: " << Str1.FindStringLength();
			break;
		case'2':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			cout << "Результат: " << Str1 + Str2;
			break;
		case'3':
			cout << "Введите строку: ";
			cin >> Str1;
			cout << "Введите от куда: ";
			cin >> Start;
			cout << "Введите длину: ";
			cin >> Len;
			cout << "Результат: " << StrRes.CopyThePart(Str1, Start, Len);
			break;
		case'4':
			cout << "Введите строку: ";
			cin >> Str1;
			cout << "Введите от куда: ";
			cin >> Start;
			cout << "Введите длину: ";
			cin >> Len;
			cout << "Результат: " << StrRes.DelSubstr(Str1, Start, Len);
			break;
		case'5':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			cout << "Введите от кдуа: ";
			cin >> Start;
			cout << "Результат: " << StrRes.Inserting(Str1, Start, Str2);
			break;
		case'6':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			Start = StrRes.SubstringSearchStart(Str1, Str2);

			cout << "Результат: " << Start;
			break;
		case'7':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			Start = StrRes.SubstringSearchEnd(Str1, Str2);

			cout << "Результат: " << Start;
			break;
		case'8':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			cout << "Введите третью строку: ";
			cin >> Str3;
			cout << "Результат: " << StrRes.ReplacingSubstr(Str1, Str2, Str3);
			break;
		case'9':
			cout << "Введите первую строку: ";
			cin >> Str1;
			cout << "Введите вторую строку: ";
			cin >> Str2;
			cout << "Введите третью строку: ";
			cin >> Str3;
			cout << "Результат: " << StrRes.ReplacingAllSubstr(Str1, Str2, Str3);
			break;
		default:
			cout << "Ошикбка";
		}
	}
	else
	{
		cout << "Ошикбка";
	}
	cout << '\n';
	system("pause");
}