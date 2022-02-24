#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include "BoardManager.h"

HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
COORD myScreen = { 0, 0 };



int main() {
	
	srand(time(NULL));

	BoardManager BM;


	BM.startBoard();


	system("pause");

	return 0;

}
