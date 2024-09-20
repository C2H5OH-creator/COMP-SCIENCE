#include <conio.h>
#include <iostream>

enum {
	ESC = 27,

};

union DOUBLE {
	double m_double = 0;
	unsigned char byte[8];

} number;

void PrintBinaryDouble() {
	for (int i = 7; i >= 0; i--) {
		for (int j = 7; j >= 0; j--) {
			bool bite = number.byte[i] & (1 << j);
			std::cout << bite;
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

void PrintBinaryChar(unsigned char t_char) {
	for (int i = 7; i >= 0; --i) {  
		std::cout << ((t_char >> i) & 1);
	}
	std::cout << std::endl;
}


int main() {
	int keyInput;
	unsigned bitAmmount = 1, index = 1;
	bool dataType = 0; // unsigned char = 0, double = 1

	long long int t_char = -1;
	unsigned char unsignedChar = 0;

	do {
		keyInput = _getch();
		std::cout << "Выберите тип данных (unsigned char - 0, double - 1) : ";
		std::cin >> dataType;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if (!dataType) {
			std::cout << "Введите число, соответсвующее типу (unsigned char): ";
			std::cin >> t_char;
			while (t_char > 255 || t_char < 0 || std::cin.fail()) {
				std::cout << "Введите корректное число в диапазоне [0;255]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> t_char;
			}
			unsignedChar = static_cast<unsigned char>(t_char);
			//std::cout << static_cast<int>(unsignedChar) << std::endl;
			PrintBinaryChar(unsignedChar);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cout << "Введите число, соответсвующее типу (double): ";
			std::cin >> number.m_double;
			PrintBinaryDouble();
		}
		std::cout << "Введите номер старшего разрада: ";
		std::cin >> index;
		std::cout << "Введите количество бит: ";
		std::cin >> bitAmmount;
	
	} while (keyInput != ESC);
}