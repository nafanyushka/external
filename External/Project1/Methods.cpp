#include "Plate.h"

Plate::Plate() {
	size = 0;
	arr = nullptr;
}

Plate::Plate(const Plate& origin) {
	try {
		arr = new Contact[origin.size];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	size = origin.size;
	Contact* ptr_arr1 = origin.arr;
	Contact* ptr_arr2 = arr;
	Contact* arr_end = ptr_arr1 + size;
	for (; ptr_arr1 != arr_end; ++ptr_arr1, ++ptr_arr2) {
		ptr_arr2->x = ptr_arr1->x;
		ptr_arr2->y = ptr_arr1->y;
		ptr_arr2->type = ptr_arr1->type;
		ptr_arr2->number = ptr_arr1->number;
	}
}

Plate::Plate(Plate&& origin) {
	this->size = origin.size;
	arr = origin.arr;
	origin.arr = nullptr;
}

Plate::Plate(int x, int y, int type) :size(1) {//конструктор, создающий только 1 контакт на плате
	if (type != 0 && type != 1)
		throw std::exception("Incorrect type\n");
	try {
		arr = new Contact[1];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	arr[0].type = type;
	arr[0].x = x;
	arr[0].y = y;
	arr[0].number = INT_MAX;
};

Plate::Plate(int size, Contact* arr) {//переденный массив помещается в поле класса
	if (size < 0)
		throw std::exception("Incorrect size\n");
	this->size = size;
	try {
		this->arr = new Contact[size];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	Contact* ptr_arr1 = arr;
	Contact* ptr_arr2 = this->arr;
	Contact* arr_end = ptr_arr1 + size;
	for (; ptr_arr1 != arr_end; ++ptr_arr1, ++ptr_arr2) {
		ptr_arr2->x = ptr_arr1->x;
		ptr_arr2->y = ptr_arr1->y;
		ptr_arr2->type = ptr_arr1->type;
		ptr_arr2->number = ptr_arr1->number;
	}
}

Plate::~Plate() {
	delete[] arr;
}

int Plate::addContact(int x, int y, int type) {
	if (!(type == 1 || type == 0))
		return -1;
	//a new element is added to the end
	arr = new_size(size, size + 1, arr);
	arr[size].x = x;
	arr[size].y = y;
	arr[size].type = type;
	arr[size].number = INT_MAX;
	//the number of elements occupied in the array increases
	size++;
	return 1;
}

int Plate::deleteContact() {
	if (size == 0)
		return -1;
	arr = new_size(size, size - 1, arr);
	size--;
	return 1;
}

void Plate::showInfo(std::ostream& out) const {
	if (size == 0)
		out << "Plate is empty" << std::endl;
	for (int i = 0; i < size; i++) {
		out << "Number: " << i << "	Type: ";
		if (arr[i].type == 1)
			out << "entrance";
		else
			out << "output";
		out << "	(x,y): " << '(' << arr[i].x << ',' << arr[i].y << ')';
		if (arr[i].number != INT_MAX) {
			out << std::endl;
			if (arr[i].type == 1)
				out << "Related output element: " << arr[i].number;
			else
				out << "Related input element: " << arr[i].number;
		}
		out << std::endl;
	}
}

int Plate::correctness(int number) const {
	//if there is no such contact
	if (number >= size)
		return 3;
	//no connection
	if (arr[number].number == INT_MAX)
		return 2;
	//if the number of the associated element matches the one specified with the structure
	if (arr[number].number != INT_MAX && arr[number].type != arr[arr[number].number].type)
		return 1;
	//incorrect connection
	return -1;
}

int Plate::addLink(int number1, int number2) {
	//checking for the existence of contacts
	if (number1 >= size) {
		std::cout << "Incorrect first contact number" << std::endl;
		return -1;
	}
	if (number2 >= size) {
		std::cout << "Incorrect second contact number" << std::endl;
		return -1;
	}
	//checking for an existing connection
	if (arr[number1].number != INT_MAX) {
		std::cout << "The first element already has a connection" << std::endl;
		return -1;
	}
	if (arr[number2].number != INT_MAX) {
		std::cout << "The second element already has a connection" << std::endl;
		return -1;
	}
	//type matching check
	if (arr[number1].type == 1) {
		std::cout << "The type of the first element is not suitable" << std::endl;
		return -1;
	}
	if (arr[number2].type == 0) {
		std::cout << "The type of the second element is not suitable" << std::endl;
		return -1;
	}
	arr[number1].number = number2;
	arr[number2].number = number1;
	return 1;
}

void Plate::showGroup(bool type, std::ostream& out) const {
	for (int i = 0; i < size; i++) {
		if (arr[i].type == type) {
			out << "Number: " << i << "	Type: ";
			if (arr[i].type == 1)
				out << "entrance";
			else
				out << "output";
			out << "	(x,y): " << '(' << arr[i].x << ',' << arr[i].y << ')';
			out << std::endl;
		}
	}
}

double Plate::pathLength(int number1, int number2) const {
	//checking for the existence of contacts
	if (number1 >= size) {
		std::cout << "Incorrect first contact number" << std::endl;
		return -1;
	}
	if (number2 >= size) {
		std::cout << "Incorrect second contact number" << std::endl;
		return -1;
	}
	//checking for the existence of a connection
	if (arr[number1].number == INT_MAX) {
		std::cout << "The first element is not connected to anything" << std::endl;
		return -1;
	}
	if (arr[number2].number == INT_MAX) {
		std::cout << "The second element is not connected to anything" << std::endl;
		return -1;
	}
	//checking for a connection between these two elements
	if (arr[number1].number != number2 || arr[number2].number != number1) {
		std::cout << "There is no such connection" << std::endl;
		return -1;
	}
	return sqrt(pow(arr[number1].x - arr[number2].x, 2) + pow(arr[number1].y - arr[number2].y, 2));
}

Contact* new_size(int size_old, int size_new, Contact* arr) {
	int min;
	Contact* result = nullptr;
	if (size_new < size_old)
		min = size_new;
	else
		min = size_old;
	try {
		result = new Contact[size_new];
	}
	catch (std::bad_alloc& ba) {
		std::cerr << ba.what() << std::endl;
	}
	for (int i = 0; i < min; i++) {
		result[i].x = arr[i].x;
		result[i].y = arr[i].y;
		result[i].type = arr[i].type;
		result[i].number = arr[i].number;
	}
	delete[] arr;
	return result;
}