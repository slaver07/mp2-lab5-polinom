#include <iostream>
#include <cstdlib>
#include <string>
#include "polinom.h"

using namespace std;

void printMenu() {
	setlocale(LC_ALL, "Russian");
	cout << "\n=== ������������� �������������� ��������� ===\n";
	cout << "  + : �������� ���� ���������\n";
	cout << "  - : ��������� ���� ���������\n";
	cout << "  * : ��������� ���� ��������� ��� ��������� �������� �� �����\n";
	cout << "  = : ��������� �������� �������� � �����\n";
	cout << "  d : ����� ����������� �� ��������\n";
	cout << "  q : ����� �� ���������\n";
	cout << "=============================================\n";
	cout << "�������� ��������: ";
}

bool isPolynomValid(const string& str) {
	return !str.empty();
}

int main() {
	setlocale(LC_ALL, "Russian");
	char operation;
	Polinom polynom1, polynom2, result;

	cout << "������� ������ �������: ";
	string input1;
	cin >> input1;

	if (!isPolynomValid(input1)) {
		cout << "������������ �������!\n";
		return 1;
	}
	polynom1 = Polinom(input1);

	while (true) {
		printMenu();
		cin >> operation;

		switch (operation) {
		case '+':
			cout << "������� ������ ������� ��� ��������: ";
			cin >> input1;
			if (!isPolynomValid(input1)) {
				cout << "������������ �������!\n";
				break;
			}
			polynom2 = Polinom(input1);
			result = polynom1 + polynom2;
			cout << "���������: " << result << endl;
			break;

		case '-':
			cout << "������� ������ ������� ��� ���������: ";
			cin >> input1;
			if (!isPolynomValid(input1)) {
				cout << "������������ �������!\n";
				break;
			}
			polynom2 = Polinom(input1);
			result = polynom1 - polynom2;
			cout << "���������: " << result << endl;
			break;

		case '*':
			cout << "" << endl;
			cout << "������, ��� ��� ����� ������� ������� ��������� �������� ����� �������� �����������." << endl;
			cout << "����� ������������� ��������� ������������ � ������� (����� ������ �� x^2, � 1x^2) ." << endl;
			cout << "������� ������ ������� ��� �����: ";
			cin >> input1;
			if (isdigit(input1[0]) || input1[0] == '-') {
				double value = stod(input1);
				result = polynom1 * value;
			}
			else if (isPolynomValid(input1)) {
				polynom2 = Polinom(input1);
				result = polynom1 * polynom2;
			}
			else {
				cout << "������������ ����!" << endl;
				break;
			}
			cout << "���������: " << result << endl;
			break;

		case '=':
			double x, y, z;
			cout << "������� �������� ���������� x, y, z ����� ������: ";
			cin >> x >> y >> z;
			cout << "��������� ����������: " << polynom1.evaluate(x, y, z) << endl;
			break;

		case 'd': {
			cout << "�������� ���������� ��� ����������������� (��������, x, y, z): ";
			char var;
			cin >> var;
			cin.ignore();

			cout << "����������, ������� ������� ��� �����������������." << endl;
			cout << "����������� ���������� ������������ � ������� (������ ������ x^2, ����� ������ 1x^2)." << endl;
			cout << "������ �����: 1x^2+2x-3" << endl;
			cout << "������� �������: ";

			string input2;
			getline(cin, input2);

			if (!isPolynomValid(input2)) {
				cout << "������������ �������!\n";
				break;
			}

			Polinom polynomToDerive;
			try {
				polynomToDerive = Polinom(input2);
				result = polynomToDerive.derivative(var);
				cout << "����������� �������� �� ���������� '" << var << "': " << result << endl;
			}
			catch (const invalid_argument & e) {
				cout << e.what() << endl;
			}
			break;
		}

		case 'q':
			cout << "����� �� ���������...\n";
			return 0;

		default:
			cout << "�������� ��������. ���������� �����.\n";
			break;
		}
	}
}

