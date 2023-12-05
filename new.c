#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define CODE_LENGTH 4
#define COLORS 6

//MAX_SIZE -> eligible
#define POP_SIZE 150
#define MAX_GEN 100
#define MAX_SIZE 60

#define CROSSOVER 50
#define MUTATION 3
#define PERMUTATION 3
#define INVERSION 2

typedef struct s_individual
{
	int	code[CODE_LENGTH];
	int	fitness;
	int	black, white;
}		Individual;

int	fitness_score[POP_SIZE];

void	randCode(Individual *code)
{
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		code->code[i] = rand() % COLORS;
	}
}

void	swap(int *a, int *b)
{
	int	temp = *a;
	*a = *b;
	*b = temp;
}

void	createPopulation(Individual population[])
{
	for (int i = 0; i < POP_SIZE; i++)
	{
		randCode(&population[i]);
	}
}

Individual	parent_selection(Individual population[])
{
	int	random = rand() % POP_SIZE;
	Individual	parent = population[random];

	return (parent);
}

// //one-point crossover -> parent สุ่มมาทั้งคู่
// void	crossover(Individual parent1[], Individual parent2[])
// {
// 	int chance = rand() % 100;
// 	if(chance < CROSSOVER)
// 	{
// 		int point = rand() % CODE_LENGTH;
// 		for(int i = point; i < CODE_LENGTH; i++)
// 		{
// 			parent1->code[i] = parent2->code[i];
// 		}
// 	}
// }

Individual	crossover(Individual *p1, Individual *p2)
{
	Individual	new;
	int			i;

	i = 0;
	while (i < CODE_LENGTH)
	{
		if (rand() % 100 > CROSSOVER)
			new.code[i] = p1->code[i];
		else
			new.code[i] = p2->code[i];
		i++;
	}
	return (new);
}

void	mutation(Individual *p)
{
	int	i;
	int	v;

	i = rand() % CODE_LENGTH;
	v = rand() % COLORS;
	p->code[i] = v;
}

void	inverseMutation(Individual population)
{
	int chance = rand() % 100;
	if(chance < INVERSION)
	{
		int start = rand() % CODE_LENGTH;
		int end = rand() % CODE_LENGTH;

		if(start > end) swap(&start, &end);
		else if(start == end) return;

		while(start < end)
		{
			swap(&population.code[start], &population.code[end]);
			start++;
			end--;
		}
	}
}

//check black & white peg for each guess
// correct
// check_play() -> duplicate
void	check_BW(Individual guess[], Individual previous[])
{
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		if(guess->code[i] == previous->code[i])
			previous->black++;
		else
		{
			for(int j = 0; j < CODE_LENGTH; j++)
				if(guess->code[i] == previous->code[j])
					previous->white++;
		}
	}
}

// int	*check_BW_return(Individual guess[], Individual previous[])
// {
// 	int	*pegs; //0 = black, 1 = white

// 	pegs = malloc(sizeof(int) * 2);
// 	pegs[0] = 0;
// 	pegs[1] = 0;
// 	for (int i = 0; i < CODE_LENGTH; i++)
// 	{
// 		if(guess->code[i] == previous->code[i])
// 			pegs[0]++;
// 		else
// 		{
// 			for(int j = 0; j < CODE_LENGTH; j++)
// 				if(guess->code[i] == previous->code[j])
// 					pegs[1]++;
// 		}
// 	}
// 	return (pegs);
// }

// int	get_difference(Individual *trial, Individual *guess)
// {
// 	int	guess_result;
// 	int	guess_code;
// 	int	diff;
// 	int	*trial_result;

// 	guess_result = guess[1]; //pegs
// 	guess_code = guess[0]; //all possible code
// 	trial_result = check_BW_return(trial, guess_code);
// }

void	fitnessCal(Individual pop[], Individual previous[], int prev_count)
{
	for(int i = 0; i < POP_SIZE; i++)
	{
		pop[i].fitness = 0;
		for(int j = 0; j < prev_count; j++)
		{
			check_BW(&pop[i], &previous[j]);
			pop[i].fitness += abs(previous[j].black - pop[i].black) + abs(previous[j].white - pop[i].white);
			fitness_score[i] = pop[i].fitness;
		}
	}
}

Individual	addEligible(Individual pop[], Individual eligible[])
{
	int	j = 0;
	for(int i = 0; i < POP_SIZE; i++)
	{
		if(pop[i].fitness == 0)
		{
			eligible[j] = pop[i];
			j++;
		}
	}
}

void	printCode(const Individual *code)
{
	for (int i = 0; i < CODE_LENGTH; i++)
	{
		printf("%d ", code->code[i]);
	}
	printf("\n");
}

void	evolution()
{
	Individual	pop[POP_SIZE];
	Individual	chosen_ones[POP_SIZE];
	int			i;
	int			h;
	int			k;

	i = 0;
	while (i < POP_SIZE)
	{
		randCode(&pop[i]);
		i++;
	}
	h = 1;
	k = 0;
	while (h <= MAX_GEN)
	{
		Individual	sons[POP_SIZE];
		Individual	son;
		i = 0;
		while (i < POP_SIZE)
		{
			if (i == POP_SIZE - 1)
			{
				sons[i] = pop[i];
				break ;
			}
			son = crossover(&pop[i], &pop[i + 1]);
			if (rand() % 100 <= MUTATION)
				mutation(son);
			i++;
		}
		h++;
	}
}

// void	test(void)
// {
// 	Individual	a;
// 	Individual	b;

// 	a.code[0] = 7;
// 	a.code[1] = 2;
// 	a.code[2] = 6;
// 	a.code[3] = 1;

// 	b.code[0] = 4;
// 	b.code[1] = 5;
// 	b.code[2] = 6;
// 	b.code[3] = 7;

// 	check_BW(&b, &a);
// 	printf("black = %d\nwhite = %d\n", a.black, a.white);
// }

int main()
{
	srand(time(NULL));

	//generate secret code
	// int secret_code[CODE_LENGTH];
	// for (int i = 0; i < CODE_LENGTH; i++)
	// {
	// 	secret_code[i] = rand() % COLORS;
	// }

	// Individual population[POP_SIZE];
	// createPopulation(population);
	memset(fitness_score, 0, POP_SIZE);
	//test();
	//print all population
	// for(int i = 0; i < POP_SIZE; i++){
	//    printf("population #%d: ", i+1);
	//    printCode(&population[i]);
	// }

	int g1[CODE_LENGTH];
	int gen = 1;


	return (0);
}
