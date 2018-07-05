#include "stdafx.h"
#include "menu.h"
#include "Knapsack.h"
#include "TSP.h"
using namespace std;

menu::menu()
{
}

menu::~menu()
{
}

int menu::ShowMenu() //Menu g³ówne programu
{
	char select = 'x';
	while (select != '0')
	{
		cout << "SDIZO Projek 3 - Marcin Calkowski nr. 218191\nWybierz opcje:\n\n1. Dyskretny problem plecakowy\n2. Asymetryczny problem komiwojazera\n0. Wyjscie\n";
		select = _getch();

		switch (select)
		{
			case '1':
			{
				cout << "\n-----------------------------------------\n------ Dyskretny problem plecakowy ------\n-----------------------------------------\n";
				Knapsack knapsack;
				knapsack.Menu();
				knapsack.~Knapsack();
			} break;

			case '2':
			{
				cout << "\n-----------------------------------------\n--- Asymetryczny problem komiwojazera ---\n-----------------------------------------\n\n";
				TSP tsp;
				tsp.Menu();
				tsp.~TSP();
			} break;

		}
		cout <<endl;
	}
	
	return 0;
}
