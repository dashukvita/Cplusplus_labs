// Task_2_C++_Starikov.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include "BOX.h"
#include "WBox.h"
#include "HBox.h"
#include "WHBox.h"
#include "Stack.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

#pragma region �������� BOX

	printf("////////////  ������������ ������ ������ BOX  ////////////\n");
	#pragma region ����� 1
	// ����� 1
	printf("������������ ������ 1:\n");
	printf("\n�������� ������� ��� ����������:");
	BOX box;
	printf("\n�������������� ���� � ������� setters:");
	box.set_length(1);
	box.set_width(2);
	box.set_height(3);
	printf("\n������� ����:");
	box.print();
	printf("\n");

	printf("\n�������� ���, ������� ��� ���������:");
	BOX cube(2);
	cube.print();
	printf("\n");

	printf("\n���������� ����������� � 2-�� �����������:");
	BOX box1(1, 2);
	box1.print();
	printf("\n");

	printf("\n���������� ����������� � 3-�� �����������:");
	BOX box2(1, 2, 3);
	box2.print();
	printf("\n");

	printf("\n�������� ������:");
	BOX box3 = box2;
	box3.print();
	printf("\n");

	printf("\n������� ������:\n");
	box3.~BOX();
	printf("\n");

	printf("������� ������� ����������� ��� ������:");
	box2.print();
	printf("\n������� = %d", box2.area());
	printf("\n\n\n");
#pragma endregion

	#pragma region ����� 2
	// ����� 2
	printf("������������ ������ 2:\n");
	printf("\n������� ����� �������, ������������ operator =:");
	BOX box21;
	box21.print();
	printf("\n\n������� ����� �������, ��������� ���������� operator ++");
	BOX box22 = ++box21;
	box22.print();
	printf("\n\n� ������ ���������� ����������� operator ++");
	box22++;
	box22.print();
	printf("\n\n������� ����� �������, ��������� ���������� operator --");
	BOX box23 = --box22;
	box23.print();
	printf("\n\n� ������ ���������� ����������� operator --");
	box23--;
	box23.print();
	printf("\n\n���������� �������-���� operator +");
	printf("\n����� ����������:");
	box21.print();
	box22.print();
	printf("\n�������� ����� �������:");
	BOX box24 = box21 + box22;
	box24.print();
	printf("\n\n\n");
#pragma endregion

#pragma region ����� 4
	printf("������������ ������ 4:\n");
	WBox box41(1, 1, 2, 2, 2);
	box41.print();
	printf("\n������� ������� ����������� ��� ������ c �������:");
	printf("\n������� = %d", box41.area());
	printf("\n\n\n");
#pragma endregion

#pragma region ����� 5
	printf("������������ ������ 5:\n");
	HBox box51(1, 2, 2, 2);
	box51.print();
	printf("\n������� ������� ����������� c �������:");
	printf("\n������� = %d", box51.area());
	printf("\n\n\n");
#pragma endregion

#pragma region ����� 6
	printf("������������ ������ 6:\n");
	WHBox box61(1, 1, 1, 2, 2, 2);
	box61.print();
	printf("\n������� ������� ����������� c ������� � � �����:");
	printf("\n������� = %d", box61.area());
	printf("\n\n\n");
#pragma endregion

#pragma region ����� 7
	printf("������������ ������ 7:\n");
	printf("\n����� ������� ������� � �������������� �������:\n");
	BOX box71(-2, -2, -2);
	box71.print();
	printf("\n����� ��������� ������������� ������:\n");
	box71.set_height(-7);
	box71.print();
	printf("\n����� ��������� ���������� ����������:\n");
	--box71;
	box71.print();
	printf("\n����� ������� ������� � �������� ������� ����:\n");
	WHBox box72(1, 3, 1, 2, 2, 2);
	box72.print();

	printf("\n\n\n");
#pragma endregion

	// �������� �� const �������
	const BOX box81;
	cout << box81.area();
	
	printf("\n\n");

#pragma endregion

#pragma region �������� Stack
	printf("////////////  ������������ ������ ������ Stack  ////////////\n");
	printf("�������� � int:\n");
	printf("������� ������ ����:\n");
	Stack<int> stack = Stack<int>();
	printf("���������� ��������� ������� ����� %d\n", stack.count());
	printf("�������� ����� ������� �� ������� ����� %d\n", stack.pop());
	printf("��������� ���� ������� �� 1 �� 10:");
	for (int i = 1; i <= 10; i++)
	{
		stack.push(i);
	}
	stack.print();
	printf("����� ������� %d\n", stack.pop());
	printf("����� ������� %d\n", stack.pop());
	stack.print();
	printf("\n\n");

	printf("�������� � double:\n");
	printf("������� ������ ����:\n");
	Stack<double> doubleStack = Stack<double>();
	printf("���������� ��������� ������� ����� %d\n", doubleStack.count());
	printf("�������� ����� ������� �� ������� ����� %.2f\n", doubleStack.pop());
	printf("��������� ���� ������� �� 1 �� 10:");
	for (int i = 1; i <= 10; i++)
	{
		doubleStack.push(i*10.01);
	}
	doubleStack.print();
	printf("����� ������� %.2f\n", doubleStack.pop());
	printf("����� ������� %.2f\n", doubleStack.pop());
	doubleStack.print();
	printf("\n\n");

	printf("�������� � BOX:\n");
	printf("������� ������ ����:\n");
	Stack<BOX> boxStack = Stack<BOX>();
	printf("���������� ��������� ������� ����� %d\n", boxStack.count());
	printf("�������� ����� ������� �� ������� �����\n");
	printf("��������� ���� 3-�� ���������:");
	BOX box91(1, 1, 1);
	BOX box92(2, 2, 2);
	BOX box93(3, 3, 3);
	boxStack.push(box91);
	boxStack.push(box92);
	boxStack.push(box93);
	printf("����� �������: ");
	boxStack.pop().print();
	printf("����� �������: ");
	boxStack.pop().print();
	printf("\n\n");
#pragma endregion

	system("pause");
    return 0;
}

