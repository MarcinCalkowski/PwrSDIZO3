#include "stdafx.h"
#include "Knapsack.h"
using namespace std;

Knapsack::Knapsack()
{
	numberOfItems = 0;
	capacity = 0;
}

Knapsack::~Knapsack()
{
	if (numberOfItems != 0) {
		delete[]this->items;
		items = NULL;
		numberOfItems = 0;
		capacity = 0;
	}
}

int Knapsack::Menu()
{
	char select = 'x';
	while (select != '0')
	{
		cout << "----> Menu <----\n";
		if (numberOfItems < 1)
			cout << "\nNie wczytano danych\n";
		else
			cout << "Liczba przedmoitow: "<<numberOfItems<<"\nPojemnosc plecaka: " << capacity << endl;
		cout << "Wybierz opcje:\n\n1. Wczytaj dane z pliku\n2. Wylosuj dane\n3. Pokaz dane\n\n4. Algorytm bruteforce\n7. Testowanie\n\n0. Wyjscie\n";
		select = _getch();

		switch (select)
		{
		case '1':
		{
			cout << "Podaj nazwe pliku:\n";
			string filename;
			cin >> filename;
			if (filename.substr(filename.find_last_of(".") + 1) != "txt") //dodanie do nazwy pliku rozszerzenia .txt gdy go nie ma
			{
				filename += ".txt";
			}
			this->LoadFromFile(filename);
			cout << endl;
		} break;

		case '2':
		{
			int num, cap;
			cout << "Podaj ilosc przedmiotow:\n";
			cin >> num;
			cout << "Podaj pojemnosc plecaka:\n";
			cin >> cap;
			this->Generate(num, cap);
			cout << endl;
		} break;

		case '3':
		{
			this->Show();

		} break;

		case '4':
		{
			if (numberOfItems > 0) {
			this->Show();
			cout << "\n---> Algorytm Bruteforce <---\n";
			this->Bruteforce();
			}
			else cout << "Brak danych!\n";
		} break;

		case '7':
		{
			this->Test();
		} break;
		}
	}
	return 0;
}

//Wczytywanie z pliku
int Knapsack::LoadFromFile(string filename) {
	
	if (numberOfItems != 0) {
		delete []this->items;
		items = NULL;
		numberOfItems = 0;
		capacity = 0;
	}

	fstream File;
	File.open(filename, ios::in);
	if (!File.good()) {
		cout << "Nie mozna wczytac pliku!\n";
		return 0;
	}
	
	File >> capacity;
	File >> numberOfItems;
	items = new Item[numberOfItems];

	for (int i = 0; i < numberOfItems; i++) {
		File >> items[i].weight;
		File >> items[i].value;
	}

	File.close();
	return 0;
}

//generowanie listy przedmoitow
int Knapsack::Generate(int number,int cap) {
	
	if (numberOfItems != 0) {
		delete[]this->items;
		items = NULL;
		numberOfItems = 0;
		capacity = 0;
	}
	numberOfItems = number;
	capacity = cap;

	items = new Item[number];

	for (int i = 0; i < number; i++) {
		items[i].weight = (rand()%(cap/number))+5;
		items[i].value = (rand()%(cap/2))+(cap/10);
	}

	return 0;
}

//Wyswietlenie przedmiotow
int Knapsack::Show() {
	if (numberOfItems < 1) {
		cout << "Brak danych!\n";
		return 0;
	}

	cout << "\nPojemnosc plecaka: " << capacity << endl;
	cout << "Ilosc rzeczy do wyboru: " << numberOfItems << endl;
	for (int i = 0; i < numberOfItems; i++) {
		cout << i << ".\t Waga: " << items[i].weight << "\tWartosc: " << items[i].value << endl;
	}
	cout << endl;
	return 0;
}

int Knapsack::Bruteforce() {
	int bestWeight = 0, bestValue = 0; 
	int *bestSet = new int[numberOfItems]; //najlepszy set przedmiotów
	int *currentSet = new int[numberOfItems]; //aktualny set przedmiotów

	for (int i = 0; i < numberOfItems; i++)
		bestSet[i] = 0;
	for (int i = 0; i < numberOfItems; i++)
		currentSet[i] = 0;

	//czas start
	std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
	start = std::chrono::system_clock::now();

	for (int i = 0; i < pow(2, numberOfItems); i++) { //pêtla do 2^n - wszystkie mo¿liwe kombinacje

		int temp = numberOfItems - 1;
		int tempWeight = 0;
		int tempValue = 0;

		while (currentSet[temp] != 0 && temp >= 0) {
			currentSet[temp] = 0;
			temp--;
		}
		currentSet[temp] = 1;

		for (int k = 0; k < numberOfItems; k++) { //dodawanie wartosci do aktualnego setu
			
			if (currentSet[k] == 1) { //dany przedmiot zostal dodany do rozwiazania
				tempWeight = tempWeight + items[k].weight;
				tempValue = tempValue + items[k].value;
			}

			if (tempWeight <= capacity && tempValue > bestValue) { //jesli znaleziono lepszy set
				bestValue = tempValue;
				bestWeight = tempWeight;
				for (int j = 0; j < numberOfItems; j++)
					bestSet[j] = currentSet[j];
			}
		}
	}
	//czas stop

	end = std::chrono::system_clock::now(); //koniec pomiaru
	std::chrono::duration<double> elapsed_seconds = end - start;
	double czas = elapsed_seconds.count();
	czas = czas * 1000;

	cout << "Waga wybranych przedmiotow: " << bestWeight << endl << "Wartosc wybranych przedmiotow: " << bestValue << "\n\nWybrane przedmioty:\n";
	for (int i = 0; i < numberOfItems; i++) {
		if (bestSet[i] == 1)
			cout << "Waga: " << items[i].weight << "\tWartosc: " << items[i].value << endl;
	}
	cout << "\nCzas wykonywania: " << czas << " [ms]\n";
	cout << "\n\n";
	//koniec 
	//delete bestSet;
	//delete currentSet;
	return 0;
}

int Knapsack::Test() {

	int num, cap, rep;
	double temp, timeMid = 0;
	cout << "\n----> Testowanie <----\nPodaj ilosc przedmiotow:\n";
	cin >> num;
	cout << "Podaj pojemnosc plecaka:\n";
	cin >> cap;
	cout << "Podaj liczbe powtorzen testu:\n";
	cin >> rep;

	for (int i = 0; i < rep; i++) {
		this->Generate(num, cap);
		temp = BruteforceTest();
		timeMid += (temp / rep);

		if (i % 10 == 0)
			std::cout << "Petla " << i + 1 << std::endl;
	}
	timeMid *= 1000;
	std::cout << "Sredni czas wykonywania: " << timeMid << " [ms]" << std::endl;

	return 0;
}

double Knapsack::BruteforceTest() {
	int bestWeight = 0, bestValue = 0;
	int *bestSet = new int[numberOfItems]; //najlepszy set przedmiotów
	int *currentSet = new int[numberOfItems]; //aktualny set przedmiotów

	for (int i = 0; i < numberOfItems; i++)
		bestSet[i] = 0;
	for (int i = 0; i < numberOfItems; i++)
		currentSet[i] = 0;

	//czas start
	std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
	start = std::chrono::system_clock::now();

	for (int i = 0; i < pow(2, numberOfItems); i++) { //pêtla do 2^n - wszystkie mo¿liwe kombinacje

		int temp = numberOfItems - 1;
		int tempWeight = 0;
		int tempValue = 0;

		while (currentSet[temp] != 0 && temp >= 0) {
			currentSet[temp] = 0;
			temp--;
		}
		currentSet[temp] = 1;

		for (int k = 0; k < numberOfItems; k++) { //dodawanie wartosci do aktualnego setu

			if (currentSet[k] == 1) { //dany przedmiot zostal dodany do rozwiazania
				tempWeight = tempWeight + items[k].weight;
				tempValue = tempValue + items[k].value;
			}

			if (tempWeight <= capacity && tempValue > bestValue) { //jesli znaleziono lepszy set
				bestValue = tempValue;
				bestWeight = tempWeight;
				for (int j = 0; j < numberOfItems; j++)
					bestSet[j] = currentSet[j];
			}
		}
	}
	//czas stop

	end = std::chrono::system_clock::now(); //koniec pomiaru
	std::chrono::duration<double> elapsed_seconds = end - start;

	//koniec 
	return elapsed_seconds.count();
}