#pragma once
#include <iostream>
#include <cmath>

typedef struct Contact {
	bool type;//1-entrance / 0-output
	int x, y, number;//number-number of the associated contact / ==INT_MAX - no connection
}Contact;

Contact* new_size(int size_old, int size_new, Contact* arr);//changes the amount of memory allocated for the array

class Plate
{
private:
	int size;//current number of items
	Contact* arr;//elements are added to the end
public:
	Plate();
	Plate(const Plate& origin);//copying constructor
	Plate(Plate&& origin);//moving constructor
	Plate(int x, int y, int type);//a constructor that creates only 1 pin on the board
	Plate(int size, Contact* arr);//the passed array is placed in the class field
	~Plate();
	//methods
	inline Contact* getArr() { return arr; };//returns an array
	inline int getSize() const { return size; };//returns the current size
	inline void setSize(int new_s) { size = new_s; };//sets a new size
	int addContact(int x, int y, int type);//adding a contact
	int deleteContact();//deletes the last contact, if there is one
	void showInfo(std::ostream& out) const;//output of all elements
	int correctness(int number) const;//checking the correctness of communication
	int addLink(int number1, int number2);//adding a link to the correctness check
	void showGroup(bool type, std::ostream& out) const;//output of a certain type of contacts
	double pathLength(int number1, int number2) const;//finding the path length with correctness check

	//унарные
	friend Plate& operator++(Plate& plate);//prefix increment returns an object with an added contact(0,0,0)
	friend Plate operator++(Plate& plate, int i);//the postfix increment is similar to the prefix increment, but returns the old version
	friend Plate& operator--(Plate& plate);//prefix decrement removes an element
	friend Plate operator--(Plate& plate, int i);//the postfix decrement is similar to the prefix one, but returns the old version
	//бинарные
	Plate& operator+=(const int right);//adds N contacts (0,0,0)
	Plate& operator-=( const int right);//deletes the last N contacts, if any
	Plate* operator+(const Plate& right);//creates a new element with the contacts of the terms
	//ввод вывод
	friend std::ostream& operator<<(std::ostream& out, const Plate& plate);//output of all contacts of the class
	friend std::istream& operator>>(std::istream& in, Plate& plate);//a new contact is being entered and added
	//сравнения
	bool operator!=(const Plate& right);//
	bool operator==(const Plate& right);//
	bool operator<(const Plate& right);//
	bool operator<=(const Plate& right);//	compare the number of contacts on the boards
	bool operator>(const Plate& right);//
	bool operator>=(const Plate& right);//

	Plate& operator=(const Plate& right);//the left board is assigned a size and an array of contacts on the right
	Plate& operator=(Plate&& right);//the left board is assigned a size and an array of contacts on the right
	Contact& operator[] (int index);//returns an array element
	const Contact& operator[] (int index) const;
};

bool operator==(const Contact& left, const Contact& right);//checks the possibility of communication between contacts