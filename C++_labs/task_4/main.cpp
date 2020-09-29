#include "stdafx.h"
#include <iostream>
using namespace std;

char c; 

void S();
void P();
void I();
void A();
void E();
void T();
void F();

void gc() {
	cin >> c; //считать очередной символ
}

void S() {
	//cout << "S" << endl;
	if (c == 'a' || c == 'b') {
		cout << "S" << endl;
		P();
		if (c == ':') {
			gc();
			if (c == '=') {
				gc();
				E();
			}
			else {	throw c; }
		}
		else { throw c; }
	}
	else if (c == 'i') {
		gc();
		if (c == 'f') {
			gc();
			E();
			if (c == 't') {
				gc();
				if (c == 'h') {
					gc();
					if (c == 'e') {
						gc();
						if (c == 'n') {
							gc();
							S();
							A();
						}
						else { throw c; }
					}
					else { throw c; }
				}
				else { throw c; }
			}
			else { throw c; }
		}
		else { throw c; }
	}
	else { throw c; }
}

void A() {
	//cout << "A" << endl;
	if (c == 'e') {
		gc();
		if (c == 'l') {
			gc();
			if (c == 's') {
				gc();
				if (c == 'e') {
					gc();
					S();
				}
				else { throw c; }
			}
			else { throw c; }
		}
		else { throw c; }
	}
}

void P() {
	//cout << "P" << endl;
	if (c == 'a') {
		gc();
		I();
	}
	else if (c == 'b') {
		gc();
		I();
	}
	else { throw c; }
}

void I() {
	//cout << "I" << endl;
	if (c == '(') {
		gc();
		E();
		if (c != ')') {	throw c; }
		else {
			gc();
		}
	}
}

void E() {
	//cout << "E" << endl;
	if (c == 'a' || c == 'b' || c == '(') {
		T();
		while (c == '+')
		{
			gc();
			T();
		}
	}
}

void T() {
	//cout << "T" << endl;
	if (c == 'a' || c == 'b' || c == '(') {
		F();
		while (c == '*')
		{
			gc();
			F();
		}
	}
}

void F() {
	//cout << "F" << endl;
	if (c == 'a' || c == 'b') {
		P();
	}
	else if (c == '(') {
		gc();
		E();
		if (c != ')') {	throw c; }
		gc();
	}
}



int main()
{
	try
	{
		gc();
		S();
		if (c != '^') {
			throw c;
		}
		cout << "TRUE" << endl;
		system("pause");

	}
	catch (char c)
	{
		cout << "FALSE " << endl;
		cout << "Wrong lexeme: " << c << endl;
		system("pause");
	}
}

