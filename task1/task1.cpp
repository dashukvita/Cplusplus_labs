// Task2C++.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream> 
using namespace std;

class Body { virtual int area() const = 0; };


class Box: public Body
{
private:
	int width, length, height;

public:
#pragma region Getters & Setters
	void setBoxWidth(int _width) {
		try {
			if (_width < 0) {
				throw 1;
				width = 0;
			}
			else width = _width;
		}
		catch (int) {
			cout << endl << "������ ������ 0!" << endl;
		}
	}
	void setBoxLength(int _length) {
		try {
			if (_length < 0) {
				throw 1;
				length = 0;
			}
			else length = _length;
		}
		catch (int) {
			cout << endl << "����� ������ 0!" << endl;
		}
	}
	void setBoxHeight(int _height) {
		try {
			if (_height < 0) {
				throw 1;
				height = 0;
			}
			else height = _height;
		}
		catch (int) {
			cout << endl << "������ ������ 0!" << endl;
		}
	}

	int getBoxLength() const {return length;}
	int getBoxWidth() const {return width;}
	int getBoxHeight() const {return height;}
#pragma endregion

#pragma region ������������ & ����������
	Box(int a = 0, int b = 0, int c = 0) {
		try {
			if (a < 0 || b < 0 || c < 0) {
				length = 0;
				width = 0;
				height = 0;
				throw 1;
			}
			else {
				length = a;
				width = b;
				height = c;
			}
		}
		catch (int) {
			cout << endl << "������������� ����!" << endl;
		}
	 }

	Box(const Box & box)
	{
		width = box.width;
		length = box.length;
		height = box.height;
	}

	~Box()
	{
		cout << "\n��c������� Box ��������!\n";
	}
#pragma endregion

#pragma region ������
	int area() const { return 2 * (width * length + length * height + width * height); }

	void print() {
		printf("\n����� %d", length);
		printf("\n������ %d", width);
		printf("\n������ %d", height);
	}
#pragma endregion

#pragma region ���������� ��������
	Box & operator = (const Box & b)
	{
		width = b.width;
		length = b.length;
		height = b.height;
		return *this;
	}

	Box & operator ++()
	{
		width++;
		length++;
		height++;
		return *this;
	}
	Box operator++(int)
	{
		Box box = *this;
		length++;
		width++;
		height++;
		return box;
	}

	Box & operator--()
	{
		try {
			if (length <= 0 || width <= 0 || height <= 0) {
				throw 1;
			}
			else {
				length--;
				width--;
				height--;
			}
		}
		catch (int) {
			cout << "������ ���������, ������������� �����!" << endl;
		}
		return *this;
	}

	Box operator--(int)
	{
		Box box = *this;
		try
		{
			if (length <= 0 || width <= 0 || height <= 0) {
				throw 1;
			}
			else {
				length--;
				width--;
				height--;
			}
		}
		catch (int)
		{
			cout << "������ ���������, ������������� �����!" << endl;
		}
		return box;
	}

	friend Box operator+(const Box &a, const Box &b)
	{
		Box box1(a.width + b.width, a.length + b.length, a.height + b.height);
		return box1;
	}
#pragma endregion
};

class WBox : public virtual Box
{
private:
	int win_width, win_height;

public:
#pragma region Getters & Setters
	void setWBoxWidth(int w_width) {
		try {
			if (w_width < 0 || w_width > getBoxWidth()) {
				win_width = 0;
				throw 1;
			}
			else win_width = w_width;
		}
		catch (int) {
			cout << endl << "������������ ������ ����." << endl;
		}
	}
	void setWBoxHeight(int w_height) {
		try {
			if (w_height < 0 || w_height > getBoxHeight()) {
				win_width = 0;
				throw 1;
			}
			else win_height = w_height;
		}
		catch (int) {
			cout << endl << "������������ ������ ����." << endl;
		}
	}

	int getWBoxHeight() const { return win_height; }
	int getWBoxWidth() const { return win_width; }
#pragma endregion

#pragma region ������������ � ����������
	WBox(int w = 0, int h = 0, int a = 0, int b = 0, int c = 0) : Box(a, b, c) {
		try {
			if (w < 0 || h < 0 || w > getBoxWidth() || h > getBoxHeight()) {
				win_width = 0;
				win_height = 0;
				throw 1;
			}
			else {
				win_width = w;
				win_height = h;
			}
		}
		catch (int) {
			cout << endl << "������������ �������� ���������� ����!" << endl;
		}
	}

	WBox(WBox & box) : Box(box) {
		win_width = box.win_width;
		win_height = box.win_height;
	}


	~WBox() {
		cout << "�������� ���������� ������ WBox!" << endl;
	}
#pragma endregion

#pragma region ������
	int area() const {
		return Box::area() - win_width * win_height;
	}

	void print() {
		Box::print();
		printf("\n������ ���� %d", win_width);
		printf("\n������ ���� %d", win_height);
	}
#pragma endregion

};

class HBox : public virtual Box
{
private:
	int box_cover;

public:
#pragma region Getters & Setters
	void setHBoxCover(int b_cover) {
		try {
			if (b_cover < 0) {
				box_cover = 0;
				throw 1;
			}
			else box_cover = b_cover;
		}
		catch (int) {
			cout << endl << "������������� �������� ������ �������!" << endl;
		}
	}
	int getHBoxCover() const { return box_cover; }
#pragma endregion

#pragma region ������������ � ����������
	HBox(int hh = 0, int a = 0, int b = 0, int c = 0) : Box(a, b, c) {
		try {
			if (a < 0) {
				box_cover = 0;
				throw 1;
			}
			else box_cover = hh;
		}
		catch (int) {
			cout << endl << "������������� �������� ������ �������!" << endl;
		}
	}

	HBox(HBox & box) : Box(box) {
		box_cover = box.box_cover;
	}

	//����������
	~HBox()
	{
		cout << "\n��c������� ��������!\n";
	}
#pragma endregion

#pragma region ������
	int area() const {
		int l = Box::getBoxLength();
		int w = Box::getBoxWidth();
		return Box::area() + l*w + 2 * (l + w) * box_cover;
	}

	void print() {
		Box::print();
		printf("\n������ ������ %d", box_cover);
	}
#pragma endregion

};

class WHBox : public WBox, public HBox
{
public:
#pragma region ������������ � ����������
	WHBox(int hh = 0, int ww = 0, int wh = 0, int a = 0, int b = 0, int c = 0) : Box(a, b, c) {
		HBox::setBoxHeight(hh);
		WBox::setWBoxHeight(wh);
		WBox::setWBoxWidth(ww);
	}

	WHBox(WHBox & box) : Box(box) {
		HBox::setBoxHeight(box.getBoxHeight());
		WBox::setBoxHeight(box.getWBoxHeight());
		WBox::setBoxWidth(box.getWBoxWidth());
	}

	~WHBox() {
		cout << "���������� ������ WHBox ��������!" << endl;
	}
#pragma endregion

#pragma region ������
	int area() const {
		int h = WBox::getWBoxHeight();
		int w = WBox::getWBoxWidth();
		return HBox::area() + h*w;
	}

	void print() {
		Box::print();
		printf("\n������ ���� %d", WBox::getWBoxWidth());
		printf("\n������ ���� %d", WBox::getWBoxHeight());
		printf("\n������ ������ %d", HBox::getBoxHeight());
	}
#pragma endregion
};

template <class T>
class Stack {
	class Node {
	public:
		T data;
		Node * next;
	};
	Node * head;
public:
	int count() {
		int rez = 0;
		if (head == NULL) return rez;
		Node * pointer = head;
		rez++;
		while (pointer != NULL)
		{
			pointer = pointer->next;
			rez++;
		}
		return rez;
	}

	void push(T elem) {
		Node * node = new Node();
		node->data = elem;
		node->next = head;
		head = node;

	}

	T pop() {
		if (head == NULL) {
			cout << "Stack is Empty!" << endl;
			return NULL;
		}
		T rez = head->data;
		head = head->next;
		return rez;
	}

	void print() {
		Node * pointer = head;
		while (pointer != NULL) {
			cout << pointer->data << endl;
			pointer = pointer->next;
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	const Box box234 (1,1,1);
	cout << box234.area() << endl;
	Box box;
	printf("\n�������������� ���� � ������� setters:");
	box.setBoxHeight(1);
	box.setBoxWidth(2);
	box.setBoxLength(3);
	printf("\n������� ����:");
	box.print();
	printf("\n");

	printf("\n���:");
	Box cube(2);
	cube.print();
	printf("\n");

	printf("\n����������� � 2-�� �����������:");
	Box box1(1, 2);
	box1.print();
	printf("\n");

	printf("\n����������� � 3-�� �����������:");
	Box box2(1, 2, 3);
	box2.print();
	printf("\n");

	printf("\n�������� ������:");
	Box box3 = box2;
	box3.print();
	printf("\n");

	printf("\n������� ������� = %d", box2.area());
	printf("\n\n");

	printf("������� � �������:");
	WBox box_win(2, 3, 4, 5, 6);
	box_win.print();
	printf("\n������� ������� � ������� = %d", box_win.area());
	printf("\n\n");

	printf("������� � �������:");
	HBox box_cov(1, 2, 2, 2);
	box_cov.print();
	printf("\n������� ������� c �������= %d", box_cov.area());
	printf("\n\n");

	printf("������� � �������������� �������:");
	Box box7(-2, -2, -2);

	printf("������� � �������� ������� ����:");
	WHBox box72(1, 3, 1, 2, 2, 2);
	printf("\n\n");

	printf("���� int-��������:\n");
	Stack<int> stack = Stack<int>();
	for (int i = 1; i <= 10; i++)
	{
		stack.push(i);
	}
	stack.print();
	printf("\n����� 1-������� %d\n", stack.pop());
	printf("\n�������� ���������� ����:\n");
	stack.print();

	printf("\n���� double-��������:\n");
	Stack<double> doubleStack = Stack<double>();
	for (int i = 1; i <= 10; i++)
	{
		doubleStack.push(i*10.01);
	}
	doubleStack.print();
	printf("\n����� 1-������� %.2f\n", doubleStack.pop());
	printf("\n�������� ���������� ����:\n");
	doubleStack.print();
	printf("\n\n\n\n\n\n\n\n");
	return 0;
}
