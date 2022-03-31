#include "proverki.h"
#include <string>
#include <iostream>
#include <locale>
#include <Windows.h>
#include <fstream>
#include <conio.h>
using namespace std;

int checkInt()
{
	int value, counter = 0;
	char* BufForWriting = new char[256];
	cin.clear();
	cin.getline(BufForWriting, 256, '\n');
	for (int i = 0; BufForWriting[i] != '\0'; i++)
		if (isdigit(BufForWriting[i]))
			counter++;
	if (strlen(BufForWriting) != counter ||
		(BufForWriting[0] == '0' && strlen(BufForWriting) > 1))
		value = -1;
	else value = atoi(BufForWriting);
	delete[] BufForWriting;
	return value;
}
int checkInterval(int min, int max)
{
	int value;
	value = checkInt();
	while (value < min || value > max)
	{
		cout << "Нет такого варианта, попробуйте еще раз: ";
		value = checkInt();
	}
	return value;
}

char encryption(char*& password)
{
	char BufForWriting[256];
	register int i;
	for (i = 0; (BufForWriting[i] = _getch()) != '\r';)
	{
		if (BufForWriting[i] == '\b' && i != 0)
		{
			cout << "\b \b";
			i--;
		}
		else if (BufForWriting[i] != '\b')
		{
			cout << "*";
			i++;
		}
	}
	BufForWriting[i] = '\0';
	delete[] BufForWriting;
}
