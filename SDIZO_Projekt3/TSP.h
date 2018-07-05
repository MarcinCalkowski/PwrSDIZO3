#pragma once
class TSP
{
	//macierz odleglosci miedzy krawedziami
	int **vertices;
	int numberOfVertices;

	//zmienne pomocne dla algorytmu
	int startVer;
	int addedCites;
	int tempLength;
	int bestLength;
	int *tempPath;
	int *bestPath;
	bool *visitedCity;
	bool **visitedPath;

public:
	TSP();
	~TSP();
	int Menu();
	int LoadFromFile(std::string filename);
	int Show();
	int Generate(int number);
	int Bruteforce(int startEdge);
	int Test();
	double BruteforceTest(int startVer);
	int BruteforceRecurrence(int verticle);
};

