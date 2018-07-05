#pragma once

class Knapsack
{
	struct Item {
		int weight;
		int value;
	};

	int numberOfItems;
	Item *items;

	int capacity;
	int *itemsInBackpack;

public:
	Knapsack();
	~Knapsack();
	int Knapsack::Menu();
	int LoadFromFile(std::string filename);
	int Generate(int number, int cap);
	int Show();
	int Bruteforce();
	int Test();
	double BruteforceTest();
};

