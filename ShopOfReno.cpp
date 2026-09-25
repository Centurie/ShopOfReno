#include <array>
#include <string_view>
#include <iostream>
#include <vector>
#include <limits>
#include "random.h"
#include <string>

template <typename T, std::size_t N>
using PotArray = std::array<T, N>;

void introduce()
{
	std::cout << "Welcome to Roscoe's(RENO) potion emporium!\n";
}

namespace Potion
{	
	enum Type
	{
		healing, mana, speed, invisibility, potions_count
	};
	constexpr PotArray type{healing, mana, speed, invisibility}; // CTAD template type deduction
	constexpr PotArray cost{20, 30, 12, 50};
	constexpr PotArray <std::string_view, potions_count> name
	{"Healing", "Mana", "Speed", "Invisibility"};                 // extra safety with potions_count

	static_assert(type.size() == potions_count);
	static_assert(name.size() == potions_count);
	static_assert(cost.size() == potions_count);
}

static void shop()
{
	std::cout << "\nHere is our selection for today:\n";
	for (const auto& p: Potion::type)
	{
		std::cout << p << ") " 
			<< Potion::name[p] << " costs " << Potion::cost[p] << '\n';
	}
	std::cout << '\n';
}

class Player
{
private:
	std::string p_name{};
	std::array<int, Potion::potions_count> p_inventory{};
	int p_gold{Random::get(80, 120)};

public:
	explicit Player(std::string_view name) : p_name{ name }{ }

	const std::string_view getPlayerName() const { return p_name; }
	void setName(const std::string_view name) { p_name = name; }
	void setInventory(const int index) { p_inventory[index] += 1; }
	const std::array<int, Potion::potions_count>& getInventory() const { return p_inventory; }
	void setGold(int cost) { p_gold -= cost; }
	int getGold() const { return p_gold; }
};

Player registerPlayer()
{
	std::cout << "Enter your first name: ";
	std::string name{};
	std::cin >> name;
	return Player{ name }; // temp object to allocate less memory for initialization
}

void printPlayerName(Player& p)
{
	std::cout << "Hello, " << p.getPlayerName() << ", you have " << p.getGold() << " gold.\n";
}

void resetNPurge()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void ignoreLine()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void run(Player& p)
{
	bool noExtraChar{ false };
	bool invalidInput{ false };
	//shop();
	//std::cout << "Your selection : ";
	char value{};							// key takeaway char and int for value and intValue not same.
	int intValue{};
	while (true)
	{
		if (!invalidInput)
		{
			shop();
			std::cout << "Your selection (Press 'q' to quit) : ";
		}
		invalidInput = false;
		if (std::cin >> value)
		{
			if (value == 'q')
				return;

			// Check for unextracted trailing characters
			if (std::cin.peek() != '\n' || std::cin.peek() != EOF)
			{
				ignoreLine(); // don't think this is needed for string though, for int value it is fine. (char :) )
				noExtraChar = true;
			}
			if ((value - '0') >= 0 && (value - '0') < Potion::potions_count)
			{
				intValue = value - '0';			// key takeaway from this quiz, char and int input handler using - '0'.
				for (const auto& i : Potion::type)
				{
					if (i == intValue)
					{
						if (p.getGold() > Potion::cost[i])
						{
							p.setInventory(i);
							p.setGold(Potion::cost[i]);
							std::cout << "\tCurrent gold: " << p.getGold() << '\n';
							std::cout << "Congrats, you purchased " << Potion::name[i]
								<< " of " << Potion::cost[i] << " gold.\n";
							break;
						}
						else
						{
							std::cout << "Not enough gold.\n";
						}
					}
				}
			}
			else
			{
				std::cout << "Invalid input. Retry: ";
				invalidInput = true;
			}
		}
		// Clear failbit from overflow, mismatch, or trailing characters
		if (!noExtraChar)
			resetNPurge();
	}
}

void printInventory(Player &p)
{
	std::cout << "\nYour inventory contains: \n";
	for (const auto& i : Potion::type)
	{
		if (p.getInventory()[i] != 0)
		{
			std::cout << p.getInventory()[i] << "x potion of " << Potion::name[i] << '\n';
		}
	}
}

void closeMessage()
{
	std::cout << "Thanks for shopping at Roscoe's(RENO) potion emporium!\n";
}

int main()
{
	introduce();
	Player p{ registerPlayer() };
	printPlayerName(p);

	run(p);
	printInventory(p);
	closeMessage();

	return 0;
}	