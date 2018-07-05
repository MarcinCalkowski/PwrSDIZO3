#include "stdafx.h"
#include "TSP.h"
using namespace std;

TSP::TSP()
{
	numberOfVertices = 0;
}


TSP::~TSP()
{
	if (numberOfVertices != 0) {
		for (int i = 0; i < numberOfVertices; i++)
			delete vertices[i];
		delete[] this->vertices;
		vertices = NULL;
		numberOfVertices = 0;
	}
}


int TSP::Menu()
{
	char select = 'x';
	while (select != '0')
	{
		cout << "----> Menu <----\n";
		if (numberOfVertices < 1)
			cout << "\nNie wczytano danych\n";
		else
			cout << "Liczba przedmoitow: " << numberOfVertices << endl;
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
			int num;
			cout << "Podaj ilosc wierzcholkow:\n";
			cin >> num;
			this->Generate(num);
			cout << endl;
		} break;

		case '3':
		{
			this->Show();

		} break;

		case '4':
		{
			if (numberOfVertices > 0) {
				this->Show();
				cout << "\n---> Algorytm Bruteforce <---\n";
				do
				{
					cout << "Podaj wierzcholek poczatkowy (od 0 do " << numberOfVertices - 1 << "):\n";
					cin >> startVer;
				} while (startVer < 0 && startVer > numberOfVertices - 1);
				this->Bruteforce(startVer);
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

int TSP::LoadFromFile(string filename) {

	if (numberOfVertices != 0) {
		for (int i = 0; i < numberOfVertices; i++)
			delete vertices[i];
		delete[] this->vertices;
		vertices = NULL;
		numberOfVertices = 0;
	}
	fstream File;
	File.open(filename, ios::in);
	if (!File.good()) {
		cout << "Nie mozna wczytac pliku!\n";
		return 0;
	}
	File >> numberOfVertices;
	vertices = new int*[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		vertices[i] = new int[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) {
		for (int j = 0; j < numberOfVertices; j++) {
			File >> vertices[i][j];
		}
		File.ignore();
	}
	File.close();
	return 0;
}

int TSP::Show() {
	cout << "\nLiczba wierzcholkow: " << numberOfVertices << endl << endl;
	for (int i = 0; i < numberOfVertices; i++)
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			cout << vertices[i][j] << "\t";
		}
		cout << endl;
	}
	return 0;
}

int TSP::Generate(int number) {

	if (numberOfVertices != 0) {
		for (int i = 0; i < numberOfVertices; i++)
			delete vertices[i];
		delete[] this->vertices;
		vertices = NULL;
		numberOfVertices = 0;
	}

	vertices = new int*[number];
	numberOfVertices = number;
	for (int i = 0; i < number; i++)
		vertices[i] = new int[number];

	int temp = 0;
	for (int i = 0; i < number; i++) {
		for (int j = 0; j <= temp; j++) {
			if (i == j) vertices[i][j] = -1;
			else {
				vertices[j][i] = ((rand() % 99) + 1);
				vertices[i][j] = vertices[j][i];
			}
		}
		temp++;
	}
	return 0;
}

int TSP::Bruteforce(int startVer) {
	//inicjowanie zmiennych
	tempLength = 0;
	addedCites = 0;
	bestLength = MAXINT;
	visitedCity = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		visitedCity[i] = false;

	tempPath = new int[numberOfVertices];
	bestPath = new int[numberOfVertices];
	visitedPath = new bool*[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) {
		visitedPath[i] = new bool[numberOfVertices];
		for (int j = 0; j < numberOfVertices; j++)
			visitedPath[i][j] = false;
	}

	for (int i = 0; i<numberOfVertices; i++){ //przygotowanie tablicy wierzcholkow do odwiedzenia
		for (int j = 0; j < numberOfVertices; j++){
			if (i != j){
				visitedPath[i][j] = true;
				visitedPath[j][i] = true;
			}
		}
	}

	std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
	start = std::chrono::system_clock::now();
	//czas start
	BruteforceRecurrence(startVer); //uruchomienie rekurencji

	//czas stop
	end = std::chrono::system_clock::now(); //koniec pomiaru
	std::chrono::duration<double> elapsed_seconds = end - start;
	double czas = elapsed_seconds.count();
	czas = czas * 1000;

	//wyswietlanie wyniku
	cout << "Dlugosc najkrotszej drogi: " << bestLength << "\n\nKolejnosc odwiedzonych miast:\n\n";
	for (int i = 0; i < numberOfVertices - 1; i++)
		cout << bestPath[i] << " -> ";
	cout << bestPath[numberOfVertices - 1] << endl;
	cout << "\nCzas wykonywania: " << czas << " [ms]\n";
	cout << "\n\n";

	delete visitedCity;
	delete visitedPath;
	delete bestPath;
	delete tempPath;
	return 0;
}

int TSP::Test() {

	int num, rep;
	double temp, timeMid = 0;
	cout << "\n----> Testowanie <----\nPodaj ilosc wierzcholkow:\n";
	cin >> num;
	cout << "Podaj liczbe powtorzen testu:\n";
	cin >> rep;

	for (int i = 0; i < rep; i++) {
		this->Generate(num);
		temp = BruteforceTest(0);
		timeMid += (temp / rep);

		if (i % 10 == 0)
			std::cout << "Petla " << i + 1 << std::endl;
	}
	timeMid *= 1000;
	std::cout << "Sredni czas wykonywania: " << timeMid << " [ms]" << std::endl;

	return 0;
}

double TSP::BruteforceTest(int startVer) {
	tempLength = 0;
	addedCites = 0;
	bestLength = MAXINT;
	visitedCity = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		visitedCity[i] = false;

	tempPath = new int[numberOfVertices];
	bestPath = new int[numberOfVertices];
	visitedPath = new bool*[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) {
		visitedPath[i] = new bool[numberOfVertices];
		for (int j = 0; j < numberOfVertices; j++)
			visitedPath[i][j] = false;
	}

	for (int i = 0; i<numberOfVertices; i++) { //przygotowanie tablicy wierzcholkow do odwiedzenia
		for (int j = 0; j < numberOfVertices; j++) {
			if (i != j) {
				visitedPath[i][j] = true;
				visitedPath[j][i] = true;
			}
		}
	}

	std::chrono::time_point<std::chrono::system_clock> start, end; //pomiar czasu
	start = std::chrono::system_clock::now();
	//czas start
	BruteforceRecurrence(startVer); //uruchomienie rekurencji

	//czas stop
	end = std::chrono::system_clock::now(); //koniec pomiaru
	std::chrono::duration<double> elapsed_seconds = end - start;

	delete visitedCity;
	delete visitedPath;
	delete bestPath;
	delete tempPath;
	return elapsed_seconds.count();
}

int TSP::BruteforceRecurrence(int vert) {

	tempPath[addedCites++] = vert; 
	if (addedCites < numberOfVertices) { //sprawdzanie wierzcholkow gdy nie mamy jeszcze cyklu
		visitedCity[vert] = true; //dodajemy wierzcholek do odwiedzonych
		for (int k = 0; k < numberOfVertices; k++) {
			if (visitedPath[vert][k] && !visitedCity[k]) {
				tempLength += vertices[vert][k]; //dodanie ostatniego wierzcholka, i nastepne wykonanie rekurencji dla niego
				BruteforceRecurrence(k);
				tempLength -= vertices[vert][k];
			}
		}
		visitedCity[vert] = false;
	}
	else if (visitedPath[startVer][vert]) { //sprawdzenie drogi dla cyklu, czy jest lepszy od poprzedniej najlepszej drogi
		tempLength += vertices[vert][startVer]; //dodanie drogi od ostatniego wierzcholka do w poczatkowego
		if (tempLength < bestLength) { //gdy jest lepsza, nadpisywanie najlepszej drogi
			bestLength = tempLength;
			for (int i = 0; i < addedCites; i++)
				bestPath[i] = tempPath[i];
		}
		tempLength -= vertices[vert][startVer];
	}
	addedCites--;

	return 0;
}