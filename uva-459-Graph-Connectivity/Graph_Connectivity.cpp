#include <stdio.h>
#pragma warning(disable:4996)
#define REP(i,a,b) for(int i = int(a); i < int(b); i++)

#define MAX_ELEMENTS 26
#define MAX 10000

int arrayOfSets[MAX_ELEMENTS];
int size[MAX_ELEMENTS];
char input[10];
int decoded[10];

class Utils
{
public:
	static int char2int(char c)
	{
		return (int)c - 65;
	}

	static void decode()
	{
		decoded[0] = char2int(input[0]);
		decoded[1] = char2int(input[1]);
	}
};

class DisjointSet
{
public:

	DisjointSet(int N)
	{
		this->testNumber = N;
	}

	void initialize(int N)
	{
		this->qtd = N;
		this->totalDisjointSets = N;
		REP(i, 0, qtd)
		{
			arrayOfSets[i] = i;
			size[i] = 1;
		}
	}

	int findRoot(int A)
	{
		while (arrayOfSets[A] != A)
		{
			arrayOfSets[A] = arrayOfSets[arrayOfSets[A]];
			A = arrayOfSets[A];
		}
		return A;
	}

	bool find(int A, int B)
	{
		return findRoot(A) == findRoot(B);
	}

	void unionOfSets(int A, int B)
	{
		int rootA = findRoot(A);
		int rootB = findRoot(B);
		if (arrayOfSets[rootA] == rootB) return;

		totalDisjointSets--;
		if (size[rootA] < size[rootB])
		{
			arrayOfSets[rootA] = rootB;
			size[rootB] += size[rootA];
			return;
		}
				
		arrayOfSets[rootB] = rootA;
		size[rootA] += size[rootB];
	}

	void show()
	{
		printf("%d", totalDisjointSets);
	}
private:
	int qtd;
	int testNumber;
	int totalDisjointSets;
};

DisjointSet * sets[MAX];

void newGraph(int i)
{
	sets[i] = new DisjointSet(i + 1);

	gets(input);
	if (input[0] == '\0') return;

	sets[i]->initialize(Utils::char2int(input[0]) + 1);

	while (gets(input))
	{
		if (input[0] == '\0') break;
		Utils::decode();
		sets[i]->unionOfSets(decoded[0], decoded[1]);
	}
}

int main()
{
	int N;
	scanf("%d", &N);

	getchar();
	getchar();

	REP(i, 0, N)
	{
		newGraph(i);
	}

	REP(i, 0, N)
	{
		sets[i]->show();
		printf("\n");
		if (i != N - 1)printf("\n");
	}

	return 0;
}