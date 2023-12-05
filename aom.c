//crossover: single
//mutate: 0.02%
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef DYE
# define DYE 6
#endif

#ifndef PEG
# define PEG 4
#endif

#define LIMIT 100
#define POPULATION 150
#define MAX_GEN 100
#define MAX_LIST 60

char	color[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

typedef struct slot
{
	char	seq[PEG];
	int		B, W;
}			SLOT_T;

char	*generateCode(char color[DYE])
{
	char	*code = (char*)calloc(PEG, sizeof(char));
	for(int i = 0; i < PEG; i++)
	{
		code[i] = color[rand() % DYE];
	}
	return (code);
}

void	check(SLOT_T* slot, char code[PEG])
{
	int	codeCheck[PEG], guessCheck[PEG]; //check code
	for(int i = 0; i < PEG; i++)
	{
		codeCheck[i] = guessCheck[i] = 0;
	}

	for(int i = 0; i < PEG; i++)
	{ //ไล่ตาม guess
		if(slot->seq[i] == code[i])
		{
			slot->B++;  guessCheck[i] = codeCheck[i] = 1;
		}
	}

	for(int i = 0; i < PEG; i++)
	{
		for(int j = 0; j < PEG; j++)
		{
			if(slot->seq[i] == code[j] && guessCheck[i] == 0 && codeCheck[j] == 0)
			{
				slot->W++;
				guessCheck[i] = codeCheck[j] = 1;
				break ;
			}
		}
	}
}

void	generatePopulation(char population[POPULATION][PEG])
{
	for(int i = 0; i < POPULATION; i++)
	{
		for(int j = 0; j < PEG; j++)
		{
			population[i][j] = color[rand() % DYE];
		}
	}
}

int	calFitness(SLOT_T history[LIMIT], char guess[PEG], int round)
{
	int	val = 0;

	for(int i = 0; i < round; i++)
	{
		SLOT_T*	temp = calloc(1, sizeof(SLOT_T));
		temp->B = temp->W = 0;

		for(int i = 0; i < PEG; i++)
		{
			temp->seq[i] = guess[i];
		}

		check(temp, history[i].seq);
		val += abs(temp->B - history[i].B) + abs(temp->W - history[i].W);
		free(temp);
	}
	return (val);
}

void choosing(char get[PEG],int fitness[POPULATION], char population[POPULATION][PEG])
{
	int r;

	if (fitness[POPULATION - 1] > 0)
		r = rand() % fitness[POPULATION - 1];
	else
		r = 0;
	for(int i = POPULATION - 1; i >= 0; i--)
	{
		if(r >= fitness[i])
		{
			for(int j = 0; j < PEG; j++)
			{
				get[j] = population[i][j];
			}
			return ;
		}
	}
	get = NULL;
}

void crossing(char p1[PEG], char p2[PEG], char child[PEG])
{
	int r = rand() % PEG;

	for(int i = 0; i < PEG; i++)
	{
		if(i < r)
			child[i] = p1[i];
		else
			child[i] = p2[i];
	}
}

void	mutate(char child[PEG])
{
	int r = rand() % PEG;

	child[r] = color[rand() % DYE];
}

void	generateNewPopulation(char population[POPULATION][PEG], SLOT_T history[LIMIT], char code[PEG], int round)
{
	char	temp[POPULATION][PEG];
	int		val[POPULATION];

	//get fitness value
	int max = 0;
	for(int i = 0; i < POPULATION; i++)
	{
		val[i] = calFitness(history, population[i], round);
		max = (max < val[i]) ? val[i] : max;
	}
	for(int i = 0; i < POPULATION; i++)
	{
		val[i] = max - val[i];
	}
	for(int i = 1; i < POPULATION; i++)
	{
		val[i] += val[i-1];
	}

	//choose and crossover
	for(int i = 0; i < POPULATION; i++)
	{
		char a[PEG], b[PEG], child[PEG];

		//choose a
		choosing(a, val, population);
		//choose b
		choosing(b, val, population);
		//crossover
		crossing(a, b, child);
		//mutate 0.02%
		if(rand() % 10000 <= 2)
			mutate(child);
		for(int j = 0; j < PEG; j++)
		{
			temp[i][j] = child[j];
		}
	}

	for(int i = 0; i < POPULATION; i++)
	{
		for(int j = 0; j < PEG; j++)
		{
			population[i][j] = temp[i][j];
		}
	}
}

int	isDuplicate(char store[MAX_LIST][PEG], int curSize, char guess[PEG])
{
	for(int i = 0; i < curSize; i++)
	{
		//manual check lol
		//if you use strcmp, it not work
		int	check = 0;

		for(int j = 0; j < PEG; j++)
		{
			if(store[i][j] == guess[j])
				check++;
		}
		if(check == PEG)
			return 1;
	}
	return 0;
}

int	main(void)
{
	srand(time(NULL));

	SLOT_T	*history = (SLOT_T*) calloc(LIMIT, sizeof(SLOT_T));
	char	*code = generateCode(color);
	int		round = 0;

	for(int i = 0; i < PEG; i++)
	{
		printf("%c ", code[i]);
	}
	printf("\n");

	history[round].B = history[round].W = 0;
	if (PEG == 4)
	{
		history[0].seq[0] = color[0];
		history[0].seq[1] = color[0];
		history[0].seq[2] = color[1];
		history[0].seq[3] = color[1];
	}
	else if (PEG == 5)
	{
		history[0].seq[0] = color[0];
		history[0].seq[1] = color[0];
		history[0].seq[2] = color[1];
		history[0].seq[3] = color[2];
		history[0].seq[4] = color[3];
	}
	else
	{
		for(int i = 0; i < PEG; i++)
		{
			history[0].seq[i] = color[i];
		}
	}
	check(&history[round], code);
	round++;

	//GA algo
	while(history[round-1].B < 4)
	{
		char store[MAX_LIST][PEG], population[POPULATION][PEG];
		int listSize = 0, gen = 1;
		generatePopulation(population);

		while(gen <= MAX_GEN && listSize <= MAX_LIST)
		{
			generateNewPopulation(population, history, code, round);

			for(int i=0; i<POPULATION; i++)
			{
				if(listSize > MAX_LIST)
					break;

				if(!calFitness(history, population[i], round) && !isDuplicate(store, listSize, population[i]))
				{
					for(int j=0; j<PEG; j++)
					{
						store[listSize][j] = population[i][j];
					}
					listSize++;
				}
			}
			gen++;
		}

		printf("topic %d.\n(%d)\n", round, listSize);
		for(int i = 0; i < listSize; i++)
		{
			for(int j = 0; j < PEG; j++)
			{
				printf("%c ",store[i][j]);
			}
			printf(" . \n");
		}
		printf("\n\n");

		//random choose to history
		int	r;
		if (listSize > 0)
			r = rand() % listSize; //divide by zero
		else
			r = 0;
		for(int i = 0; i < PEG; i++)
		{
			history[round].seq[i] = store[r][i];
		}
		history[round].B = history[round].W = 0;
		check(&history[round], code);

		printf("basket: \n");
		for(int i = 0; i < round + 1; i++)
		{
			for(int j = 0; j < PEG; j++)
			{
				printf("%c ", history[i].seq[j]);
			}
			printf("B:%d W:%d", history[i].B, history[i].W);
			printf("\n");
		}
		printf("\n\n");

		round++;
	}

	printf("OK : %d\n", round);
	//due to futher implement
	return (0);
}
