#include "DataFrame.h"
#include<Windows.h>
#include<string>
using namespace Pandas;
using namespace System;
//int main() {
//	DF f(DF::read_csv("iris.data"));
//	
//	DF ndf = f.select({ "1" });
//	ndf.imprimir();
//
//	cin.get();
//	return 0;
//}
void PP() {

	Console::ForegroundColor = ConsoleColor::Yellow;
	/*Console::SetCursorPosition(10, 5);
	cout << " ________            __          _____                                " << endl;
	Console::SetCursorPosition(10, 6);
	cout << " \______ \ _______ _/  |______ _/ ____\___________    _____   ____	 " << endl;
	Console::SetCursorPosition(10, 7);
	cout << "  |    |  \\__    \\   __\__  \\   __\\_  __ \__  \ /      \_/ __ \	   " << endl;
	Console::SetCursorPosition(10, 8);
	cout << "  |    `   \ / __  \|  |  / __ \|  |   |  | \// __ \|  Y Y  \  ___/ 	   " << endl;
	Console::SetCursorPosition(10, 9);
	cout << " / _______  (_____  /__| (____  / __|  |__|  (____ / __|_|  /\___  >   " << endl;
	Console::SetCursorPosition(10, 10);
	cout <<"	       \/      \/          \/                 \/       \/     \/ 	  " << endl;*/
	Console::SetCursorPosition(10, 10);
	cout << "DataFrame" << endl;
	Console::SetCursorPosition(40, 20);
	Console::ForegroundColor = ConsoleColor::White;
	cout << "Precione cualquier tecla para continuar";
	system("pause>NULL");
	Console::Clear();
	system("cls");
}

void main() {
	Console::SetWindowSize(120, 26);
	Console::CursorVisible = false;


	PP();
	short v;

	system("cls");
	string x;
	vector<DF> df;
	int aux;
	string cols;
	string col1;
	string col2;
	string op1;
	string op2;
	string val1;
	string val2;
	vector<string> col;
	do {
		Console::SetCursorPosition(0, 0);
		cout << "-------------------------MENÚ--------------------------" << endl;
		cout << "|                                                     |" << endl;
		cout << "|1. Ingrese los datos al Dataframe                    |" << endl;
		cout << "|2. Vea los datos ingredos del dataframe              |" << endl;
		cout << "|3. Filtre el dataframe                               |" << endl;
		cout << "|4. Seleccionar                                       |" << endl;
		cout << "|5. Salir                                             |" << endl;
		cout << "-------------------------------------------------------" << endl;

		Console::SetCursorPosition(2, 11);
		cout << "Ingrese su opción: "; cin >> v;
		switch (v) {
		case 1:  system("cls"); cout << "Ingrese txt a leer: " << endl; cin >> x;
			df.push_back(DF::read_csv(x));
			system("pause>NULL");
			system("cls");
			break;
		case 2:system("cls");
			for (auto f : df) {
				f.imprimir();

			}
			cin.get();
			cin.get();
			system("cls");  break;
		case 3:
			cout << "Ingrese nombre de primera columna: ";
			cin >> col1;
			cout << "Ingrese nombre de la segunda columna: ";
			cin >> col2;
			cout << "Ingrese operador 1: (<,>,=,/f,/i)";
			cin >> op1;
			cout << "Ingrese operador 2:";
			cin >> op2;
			cout << "Ingrese valor a filtrar";
			cin >> val1;
			cout << "Ingrese valor a filtrar 2";
			cin >> val2;
			df.push_back(df[0].filter(col1, op1, val1, col2, op2, val2));
			break;
		case 4:
			cout << "Ingrese el nombre de la columna a seleccionar" << endl;
			cin >> cols;
			col.push_back(cols);
			df.push_back(df[0].select(col));
			system("cls");
			//case 4:      break;*/
		default:
			exit;
			break;
		}
	} while (v != 5);
	if (v == 5)exit;

	system("pause");

	cin.get();
	_getch();
}