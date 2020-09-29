#include "stdafx.h"
#include <iostream>
using namespace std;

char c; 

void gc() { cin >> c; } //считываем символ из входной цепочки

bool scan_G() {
	enum state { H, A, B, S, ERR }; //множество состояний
	state CS;
	CS = H;

	do {
		gc();
		switch (CS) {
		case H:
			if (c == '0') {
				CS = H;
			}
			else if (c == '1')
			{
				CS = A;
			}
			else if (c == '^')
			{
				CS = S;
			}
			else {
				CS = ERR;
			}
			break;
		case A:
			if (c == '0') {
				CS = B;
			}
			else if (c == '1')
			{
				CS = A;
			}
			else if (c == '^') {  
				CS = S;
			}
			else {
				CS = ERR;
			}
			break;
		case B:
			if (c == '0') {
				CS = A;
			}
			else if (c == '^') { 
				CS = S;
			}
			else {
				CS = ERR;
			}
			break;
		}
	} while (CS != S && CS != ERR);

	return CS == S;
}

int main()
{
	(scan_G()) ? printf("\ntrue\n") : printf("\nfalse\n");
	system("pause");
	return 0;
}
