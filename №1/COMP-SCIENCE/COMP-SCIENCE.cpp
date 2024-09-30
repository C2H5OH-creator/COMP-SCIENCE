#include <conio.h>
#include <iostream>
#include <cstring>

enum {
	ESC = 27,

};

union DOUBLE {
	double m_double = 0;
	unsigned char byte[8];
} number;

void PrintBinaryDouble(const DOUBLE& number) {
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


unsigned char BitSwaper(unsigned char& value, unsigned bitAmmount, unsigned index) {
	unsigned ones = 0, zeros = 0;
	for (unsigned i = index; i < index + bitAmmount; i++) {
		if (value & (1 << i)) ones++;
		else zeros++;
	}

	std::cout << "Количество единиц: " << ones << " Количество нулей: " << zeros << std::endl;
	
	while (ones + zeros > 0) {
		if (ones > 0) {
			value |= (1 << index); // Устанавливаем единицу
			ones--;
		}
		else {
			value &= ~(1 << index); // Устанавливаем ноль
			zeros--;
		}
		index++;
	}
	return value;
}

void BitSwaper(DOUBLE& number, unsigned bitAmmount, unsigned index) {
	unsigned ones = 0, zeros = 0;

	for (unsigned i = index / 8; i <= (index + bitAmmount - 1) / 8; ++i) {
		unsigned startBit = (i == index / 8) ? (index % 8) : 0;
		unsigned endBit = (i == (index + bitAmmount - 1) / 8) ? ((index + bitAmmount) % 8) : 8;

		for (unsigned j = startBit; j < endBit; ++j) {
			if (number.byte[i] & (1 << j)) ones++;
			else zeros++;
		}
	}

	std::cout << "Количество единиц: " << ones << " Количество нулей: " << zeros << std::endl;

	unsigned currentIndex = index;
	for (unsigned i = index / 8; i <= (index + bitAmmount - 1) / 8; ++i) {
		unsigned startBit = (i == index / 8) ? (index % 8) : 0;
		unsigned endBit = (i == (index + bitAmmount - 1) / 8) ? ((index + bitAmmount) % 8) : 8;

		for (unsigned j = startBit; j < endBit; ++j) {
			if (ones > 0) {
				number.byte[i] |= (1 << j); // Устанавливаем единицу
				ones--;
			}
			else if (zeros > 0) {
				number.byte[i] &= ~(1 << j); // Устанавливаем ноль
				zeros--;
			}
		}
	}
}

int main() {
	int keyInput;
	unsigned bitAmmount = 1, index = 1;
	bool dataType = 0; // unsigned char = 0, double = 1

	long long int t_char = -1;
	unsigned char unsignedChar = 0;

	do {
		std::cout << "Нажмите любую клавишу: ";
		keyInput = _getch();
		std::cout << "\nВыберите тип данных (unsigned char - 0, double - 1) : ";
		std::cin >> dataType;
		while (dataType != 1 && dataType != 0 || std::cin.fail()) {
			std::cout << "Введите корректное число. Либо 1, либо 0: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> dataType;
		}
		
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
			PrintBinaryChar(unsignedChar);
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else {
			std::cout << "Введите число, соответсвующее типу (double): ";
			std::cin >> number.m_double;
			PrintBinaryDouble(number);
		}
		std::cout << "Введите номер младшего разряда: ";
		std::cin >> index;
		if (!dataType) {
			while (index >= 8|| index < 0 || std::cin.fail()) {
				std::cout << "Введите корректный индекс в диапазоне [0;7]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> index;
			}
		}
		else {
			while (index >= 64 || index < 0 || std::cin.fail()) {
				std::cout << "Введите корректный индекс в диапазоне [0;63]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> index;
			}
		}
		std::cout << "Введите количество бит: ";
		std::cin >> bitAmmount;
		if (!dataType) {
			while (bitAmmount >= 7 || bitAmmount <= 0 || std::cin.fail()) {
				std::cout << "Введите корректное количество бит в диапазоне [0;7]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> bitAmmount;
			}
			PrintBinaryChar(BitSwaper(unsignedChar, bitAmmount, index));
			std::cout<< "Число после преобразований: " << static_cast<int>(unsignedChar) << std::endl;
		}
		else {
			while (bitAmmount >= 63 || bitAmmount <= 0 || std::cin.fail()) {
				std::cout << "Введите корректное количество бит в диапазоне [0;63]: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> bitAmmount;
			}
			BitSwaper(number, bitAmmount, index);
			PrintBinaryDouble(number);
		}
	} while (keyInput != ESC);
}