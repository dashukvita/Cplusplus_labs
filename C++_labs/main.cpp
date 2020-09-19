// Task_2_C++_Starikov.cpp: определяет точку входа для консольного приложения.
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

#pragma region Проверка BOX

	printf("////////////  Демонстрация работы класса BOX  ////////////\n");
	#pragma region Пункт 1
	// пункт 1
	printf("Демонстрация пункта 1:\n");
	printf("\nСзоздаем коробку без параметров:");
	BOX box;
	printf("\nИнициализируем поля с помощью setters:");
	box.set_length(1);
	box.set_width(2);
	box.set_height(3);
	printf("\nВыводим поля:");
	box.print();
	printf("\n");

	printf("\nСзоздаем куб, выводим его параметры:");
	BOX cube(2);
	cube.print();
	printf("\n");

	printf("\nИспользуем конструктор с 2-мя параметрами:");
	BOX box1(1, 2);
	box1.print();
	printf("\n");

	printf("\nИспользуем конструктор с 3-мя параметрами:");
	BOX box2(1, 2, 3);
	box2.print();
	printf("\n");

	printf("\nКопируем объект:");
	BOX box3 = box2;
	box3.print();
	printf("\n");

	printf("\nУдаляем объект:\n");
	box3.~BOX();
	printf("\n");

	printf("Считаем площадь поверхности без крышки:");
	box2.print();
	printf("\nПлощадь = %d", box2.area());
	printf("\n\n\n");
#pragma endregion

	#pragma region Пункт 2
	// пункт 2
	printf("Демонстрация пункта 2:\n");
	printf("\nСоздали новую коробку, использовали operator =:");
	BOX box21;
	box21.print();
	printf("\n\nСоздали новую коробку, используя префиксный operator ++");
	BOX box22 = ++box21;
	box22.print();
	printf("\n\nА теперь используем постфиксный operator ++");
	box22++;
	box22.print();
	printf("\n\nСоздали новую коробку, используя префиксный operator --");
	BOX box23 = --box22;
	box23.print();
	printf("\n\nА теперь используем постфиксный operator --");
	box23--;
	box23.print();
	printf("\n\nИспользуем функцию-друг operator +");
	printf("\nБудем складывать:");
	box21.print();
	box22.print();
	printf("\nПолучили новую коробку:");
	BOX box24 = box21 + box22;
	box24.print();
	printf("\n\n\n");
#pragma endregion

#pragma region Пункт 4
	printf("Демонстрация пункта 4:\n");
	WBox box41(1, 1, 2, 2, 2);
	box41.print();
	printf("\nСчитаем площадь поверхности без крышки c окошком:");
	printf("\nПлощадь = %d", box41.area());
	printf("\n\n\n");
#pragma endregion

#pragma region Пункт 5
	printf("Демонстрация пункта 5:\n");
	HBox box51(1, 2, 2, 2);
	box51.print();
	printf("\nСчитаем площадь поверхности c крышкой:");
	printf("\nПлощадь = %d", box51.area());
	printf("\n\n\n");
#pragma endregion

#pragma region Пункт 6
	printf("Демонстрация пункта 6:\n");
	WHBox box61(1, 1, 1, 2, 2, 2);
	box61.print();
	printf("\nСчитаем площадь поверхности c крышкой и с окном:");
	printf("\nПлощадь = %d", box61.area());
	printf("\n\n\n");
#pragma endregion

#pragma region Пункт 7
	printf("Демонстрация пункта 7:\n");
	printf("\nХотим создать коробку с отрицательными длинами:\n");
	BOX box71(-2, -2, -2);
	box71.print();
	printf("\nХотим присвоить отрицательную высоту:\n");
	box71.set_height(-7);
	box71.print();
	printf("\nХотим выполнить префиксное уменьшение:\n");
	--box71;
	box71.print();
	printf("\nХотим создать коробку с неверной шириной окна:\n");
	WHBox box72(1, 3, 1, 2, 2, 2);
	box72.print();

	printf("\n\n\n");
#pragma endregion

	// проверка на const коробку
	const BOX box81;
	cout << box81.area();
	
	printf("\n\n");

#pragma endregion

#pragma region Проверка Stack
	printf("////////////  Демонстрация работы класса Stack  ////////////\n");
	printf("Работаем с int:\n");
	printf("Создаем пустой стек:\n");
	Stack<int> stack = Stack<int>();
	printf("Количество элементов пустого стека %d\n", stack.count());
	printf("Пытаемся взять элемент из пустого стека %d\n", stack.pop());
	printf("Заполняем стек числами от 1 до 10:");
	for (int i = 1; i <= 10; i++)
	{
		stack.push(i);
	}
	stack.print();
	printf("Берем элемент %d\n", stack.pop());
	printf("Берем элемент %d\n", stack.pop());
	stack.print();
	printf("\n\n");

	printf("Работаем с double:\n");
	printf("Создаем пустой стек:\n");
	Stack<double> doubleStack = Stack<double>();
	printf("Количество элементов пустого стека %d\n", doubleStack.count());
	printf("Пытаемся взять элемент из пустого стека %.2f\n", doubleStack.pop());
	printf("Заполняем стек числами от 1 до 10:");
	for (int i = 1; i <= 10; i++)
	{
		doubleStack.push(i*10.01);
	}
	doubleStack.print();
	printf("Берем элемент %.2f\n", doubleStack.pop());
	printf("Берем элемент %.2f\n", doubleStack.pop());
	doubleStack.print();
	printf("\n\n");

	printf("Работаем с BOX:\n");
	printf("Создаем пустой стек:\n");
	Stack<BOX> boxStack = Stack<BOX>();
	printf("Количество элементов пустого стека %d\n", boxStack.count());
	printf("Пытались взять элемент из пустого стека\n");
	printf("Заполняем стек 3-мя коробками:");
	BOX box91(1, 1, 1);
	BOX box92(2, 2, 2);
	BOX box93(3, 3, 3);
	boxStack.push(box91);
	boxStack.push(box92);
	boxStack.push(box93);
	printf("Берем элемент: ");
	boxStack.pop().print();
	printf("Берем элемент: ");
	boxStack.pop().print();
	printf("\n\n");
#pragma endregion

	system("pause");
    return 0;
}

