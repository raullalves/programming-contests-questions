#include "pch.h"
#include <stdio.h>
#include <cstring>
#pragma warning(disable:4996)
#define REP(i,a,b) for(int i = int(a); i < int(b); i++)
#define MAX 100

int foundValues[MAX];
int qtdfoundValues = 0;

int tempFoundValues[MAX];
int qtdTempFoundValues = 0;

int alreadyVisited[MAX];
int qtdAlreadyVisited = 0;

int dominationMatrix[MAX][MAX][MAX];
int unreachablePaths[MAX];

class Path
{
public:
	void addPath(int path)
	{
		paths[qtd++] = path;
		tempQtd = qtd;
	}

	int* getPaths(int& qtdTemp)
	{
		qtdTemp = qtd;
		return paths;
	}

	void clear()
	{
		qtd = 0;
	}

	void reset()
	{
		qtd = tempQtd;
	}

private:
	int paths[MAX];
	int qtd = 0;
	int tempQtd = 0;
};

class Graph
{
public:
	Graph(int testNumber)
	{
		this->testNumber = testNumber;
	}

	void setNotDomination(int index)
	{
		REP(i, 0, qtdTempFoundValues)
		{
			if(dominationMatrix[testNumber][index][tempFoundValues[i]] != 2) dominationMatrix[testNumber][index][tempFoundValues[i]] = 1;
		}
	}

	void setDomination()
	{
		memset(unreachablePaths, 0, MAX*sizeof(int));
		
		REP(i, 0, qtdfoundValues)
		{
			dominationMatrix[testNumber][foundValues[i]][foundValues[i]] = 2;
			unreachablePaths[foundValues[i]] = 1;
		}

		//Slow. Figure out optimized way to set up unreachable nodes
		REP(i, 0, qtdPaths)
		{
			if (unreachablePaths[i] == 0)
			{
				REP(j, 0, qtdPaths) dominationMatrix[testNumber][j][i] = 1;
			}
		}
	}

	void addPath(Path * path)
	{
		paths[qtdPaths++] = path;
	}

	void determinateDominators(int testNumber)
	{
		dfs_setup(0, true);

		setDomination();
		
		REP(i, 0, qtdfoundValues) REP(j, 0, qtdPaths)
		{
				int qtd;
				int* tempPaths = paths[j]->getPaths(qtd);
				paths[j]->clear();
				dfs_setup(0, false);
				setNotDomination(j);
				paths[j]->reset();
		}
	}

	void printLine()
	{
		printf("+");
		REP(i, 0, 2*qtdPaths-1) printf("-");
		printf("+\n");
	}

	void show(int testNumber)
	{
		printf("Case %d:\n", testNumber);
		REP(i, 0, 2 * qtdPaths)
		{
			if (i % 2 == 0) {
				printLine();
				continue;
			}

			int index = i / 2;
			
			REP(j, 0, qtdPaths)
			{
				int value = dominationMatrix[testNumber - 1][index][j];
				if (value != 1) printf("|Y");
				else printf("|N");
			}
			printf("|\n");
		}
		printLine();
	}

private:
	int testNumber = 0;
	
	Path * paths[MAX];
	int qtdPaths = 0;
	
	void dfs_setup(int value, bool firstVisit)
	{
		memset(alreadyVisited, 0, MAX * sizeof(int));
		qtdAlreadyVisited = 0;

		if (firstVisit)
		{
			memset(foundValues, 0, MAX * sizeof(int));
			qtdfoundValues = 0;
		}
		else 
		{
			memset(tempFoundValues, 0, MAX * sizeof(int));
			qtdTempFoundValues = 0;
		}

		dfs(value, firstVisit);
	}

	void dfs(int value, bool firstVisit)
	{
		if (value >= qtdPaths) return;

		if (alreadyVisited[value] == 1) return;

		if (firstVisit) foundValues[qtdfoundValues++] = value;
		else tempFoundValues[qtdTempFoundValues++] = value;

		alreadyVisited[value] = 1;

		int qtd;
		int* tempPaths = paths[value]->getPaths(qtd);

		REP(i, 0, qtd) dfs(tempPaths[i], firstVisit);
	}
};

Graph * graphs[MAX];

void newGraph(int index)
{
	graphs[index] = new Graph(index);
	
	int numberOfNodes = 0;
	scanf("%d", &numberOfNodes);

	int nodes[MAX][MAX];

	REP(i, 0, numberOfNodes)
	{
		Path * path = new Path();
		REP(j, 0, numberOfNodes)
		{
			scanf("%d", &nodes[i][j]);
			if (nodes[i][j] == 1) path->addPath(j);
		}
		graphs[index]->addPath(path);
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	REP(i, 0, T) newGraph(i);

	REP(i, 0, T)
	{
		graphs[i]->determinateDominators(i+1);
		graphs[i]->show(i+1);
	}
	return 0;
}