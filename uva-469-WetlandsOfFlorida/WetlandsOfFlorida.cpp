#include <stdio.h>
#include <cstring>
#pragma warning(disable:4996)
#define REP(i,a,b) for(int i = int(a); i < int(b); i++)

#define MAX_ELEMENTS 100
#define MAX 10000
struct positions
{
	int x;
	int y;
	int value;
	int area;
	bool alreadyVisited;
};
int size[MAX_ELEMENTS][MAX_ELEMENTS];

positions fullArea[MAX_ELEMENTS][MAX_ELEMENTS];
int area[MAX][MAX];

char input[101];
class DisjointSet
{
public:

	DisjointSet(int N)
	{
		this->testNumber = N;
	}

	void initialize(int x, int y, int value)
	{
		fullArea[x][y].x = x;
		fullArea[x][y].y = y;
		fullArea[x][y].value = value;
		fullArea[x][y].alreadyVisited = false;
		fullArea[x][y].area = 0;
		size[x][y] = 1;
	}

	void findRoot(int &x, int &y)
	{
		while (fullArea[x][y].x != x || fullArea[x][y].y != y)
		{
			int tempX = x;
			int tempY = y;
			x = fullArea[fullArea[tempX][tempY].x][fullArea[tempX][tempY].y].x;
			y = fullArea[fullArea[tempX][tempY].x][fullArea[tempX][tempY].y].y;
		}
	}

	bool find(int xA, int yA, int xB, int yB)
	{
		findRoot(xA, yA);  findRoot(xB, yB);
		return xA == xB && yA == yB;
	}

	void unionOfSets(int xA, int yA, int xB, int yB)
	{
		findRoot(xA, yA);
		findRoot(xB, yB);

		if (fullArea[xA][yA].x == xB && fullArea[xA][yA].y == yB) return;

		if (size[xA][yA] < size[xB][yB])
		{
			fullArea[xA][yA].x = xB;
			fullArea[xA][yA].y = yB;
			size[xB][yB] += size[xA][yA];
			return;
		}

		fullArea[xB][yB].x = xA;
		fullArea[xB][yB].y = yA;
		size[xA][yA] += size[xB][yB];
	}

	void recursiveExecution(int i, int j, int iOld, int jOld)
	{
		if (i < 0 || j < 0) return;
		
		if (i >= this->getRows()) return;
		if (j >= this->getColumns()) return;

		if (fullArea[i][j].value == 0) return;
		if (fullArea[i][j].alreadyVisited) return;
		
		fullArea[i][j].alreadyVisited = true;
		
		totalDisjointSets++;
		
		unionOfSets(i, j, iOld, jOld);

		recursiveExecution(i - 1, j - 1, i, j);
		recursiveExecution(i - 1, j, i, j);
		recursiveExecution(i - 1, j + 1, i, j);

		recursiveExecution(i, j - 1, i, j);
		recursiveExecution(i, j + 1, i, j);

		recursiveExecution(i + 1, j - 1, i, j);
		recursiveExecution(i + 1, j, i, j);
		recursiveExecution(i + 1, j + 1, i, j);
	}

	void evaluateAndSave(int t)
	{
		int i;
		int j;
		if (input[1] != ' ')
		{
			int temp = input[0] - '0';
			int temp1 = input[1] - '0';
			
			if (input[4] != '\0') j = ((int)(input[3] - '0')) * 10 + ((int)(input[4] - '0'));
			else j = (int)(input[3] - '0');

			i = temp * 10 + temp1;
		}
		else
		{
			i = input[0] - '0';

			if (input[3] != '\0') j = ((int)(input[2] - '0')) * 10 + ((int)(input[3] - '0'));
			else j = (int)(input[2] - '0');
		}
		
		i--;
		j--;

		if (fullArea[i][j].value == 0)
		{
			setArea(t, 0);
			return;
		}

		totalDisjointSets = 0;

		if (fullArea[i][j].alreadyVisited)
		{
			findRoot(i, j);
			int area = fullArea[i][j].area;
			setArea(t, area);
			return;
		}
		recursiveExecution(i, j, i, j);

		findRoot(i, j);
		fullArea[i][j].area = totalDisjointSets;

		setArea(t, totalDisjointSets);
	}

	void show()
	{
		REP(i, 0, qtdTests)
			printf("%d\n", area[testNumber][i]);
	}

	void setColumns(int columns)
	{
		this->qtdColumns = columns;
	}

	void setRows(int rows)
	{
		this->qtdRows = rows;
	}

	int getColumns()
	{
		return this->qtdColumns;
	}

	int getRows()
	{
		return this->qtdRows;
	}
private:
	int qtd;
	int testNumber;
	int totalDisjointSets;

	int qtdColumns = 0;
	int qtdRows = 0;

	int qtdTests = 0;

	void setArea(int index, int value)
	{
		area[testNumber][index] = value;
		qtdTests++;
	}
};

DisjointSet * sets[MAX];

void newTestCase(int i)
{
	sets[i] = new DisjointSet(i + 1);
	int qtdRows = 0;
	bool oneTimeColumn = false;
	bool oneTimeRow = false;

	int row = 0;
	int column = 0;
	int qtdTestCases = 0;
	int unique = 0;

	while (gets(input))
	{
		if (input[0] == '\0') return;
		if (input[0] == 'L' || input[0] == 'W')
		{
			if (!oneTimeColumn)
			{
				sets[i]->setColumns(strlen(input));
				oneTimeColumn = true;
			}

			REP(j, 0, sets[i]->getColumns())
			{
				int value = input[j] == 'L' ? 0 : ++unique;
				sets[i]->initialize(qtdRows, j, value);
			}

			qtdRows++;
			continue;
		}

		if (!oneTimeRow)
		{
			sets[i]->setRows(qtdRows);
			oneTimeRow = true;
		}

		sets[i]->evaluateAndSave(qtdTestCases++);
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
		newTestCase(i);
	}

	REP(i, 0, N)
	{
		sets[i]->show();
		if (i != N - 1) printf("\n");
	}

	return 0;
}