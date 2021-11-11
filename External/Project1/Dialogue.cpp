#include "Dialogue.h"
#include <string>

using std::string;

template <class T>
bool getNum(T& t)
{
	std::cin >> t;
	if (!std::cin.good())
	{
		if (!std::cin.good()) {
		std::cin.clear();
		while (std::cin.get() != '\n');
		return false;
	}
	return true;
	}
}

void addContact(Plate& plate)
{
	int x, y;
	bool type;
	string typeString;
	std::cout << "Input X: " << std::endl;
	std::cin >> x;
	std::cout << "Input Y: " << std::endl;
	std::cin >> y;
	std::cout << "Input type (in, out): " << std::endl;
	std::cin >> typeString;
	if (!std::cin.good())
		throw std::runtime_error("BAD VARIABLES!");
	if (typeString == "out")
		type = false;
	else if (typeString == "in")
		type = true;
	else
	{
		std::cout << "Bad variables" << std::endl;
		return;
	}
	plate.addContact(x, y, type);
	std::cout << "Success" << std::endl;
}

void addLink(Plate& plate)
{
	int firstConnection, secondConnection;
	std::cout << "Input first connection num:" << std::endl;
	std::cin >> firstConnection;
	std::cout << "Input second connection num:" << std::endl;
	std::cin >> secondConnection;
	if (!std::cin.good())
		throw std::runtime_error("BAD VARIABLES!");
	if (plate.addLink(firstConnection, secondConnection) == -1)
		std::cout << "Something went wrong!" << std::endl;
	else
		std::cout << "Success!" << std::endl;
}

void showLength(Plate& plate)
{
	int firstConnection, secondConnection;
	std::cout << "Input first connection num:" << std::endl;
	std::cin >> firstConnection;
	std::cout << "Input second connection num:" << std::endl;
	std::cin >> secondConnection;
	if (!std::cin.good())
		throw std::runtime_error("BAD VARIABLES!");
	int result = plate.pathLength(firstConnection, secondConnection);
	if (result != -1)
		std::cout << "Result = " << result << std::endl;
}

void showGroup(Plate& plate)
{
	bool type;
	string typeString;
	std::cout << "Input type (in, out): " << std::endl;
	std::cin >> typeString;
	if (!std::cin.good())
		throw std::runtime_error("BAD VARIABLES!");
	if (typeString == "out")
		type = false;
	else if (typeString == "in")
		type = true;
	else {
		std::cout << "Bad variables" << std::endl;
		return;
	}
	plate.showGroup(type, std::cout);
}

void dialogue()
{
	Plate& plate = *(new Plate());
	bool connection = true;
	int choise;
	do
	{
		std::cout << "\n\tMENU" << std::endl;
		std::cout << "1. Show info." << std::endl;
		std::cout << "2. Show info by type group." << std::endl;
		std::cout << "3. Add contact." << std::endl;
		std::cout << "4. Add link." << std::endl;
		std::cout << "5. Show length." << std::endl;
		std::cout << "6. Exit." << std::endl;
		getNum(choise);
		switch (choise)
		{
		case 1:
			plate.showInfo(std::cout);
			break;
		case 2:
			showGroup(plate);
			break;
		case 3:
			addContact(plate);
			break;
		case 4:
			addLink(plate);
			break;
		case 5:
			showLength(plate);
			break;
		case 6:
			connection = false;
			break;
		default:
			break;
		}
	} while (connection);
	delete& plate;
}