/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_per.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboonpro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:58:07 by pboonpro          #+#    #+#             */
/*   Updated: 2023/11/22 23:58:07 by pboonpro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "genetic.h"

void crossover(Chromosome *code1, Chromosome *code2)
{
	for (int i = 0; i < PER; i++)
	{
		if (rand() % 2 == 0)
		{
			int temp = code1->colors[i];
			code1->colors[i] = code2->colors[i];
			code2->colors[i] = temp;
		}
	}
}

void mutate(Chromosome *code)
{
	int random_position = rand() % PER;
	int random_color = rand() % COL + 1;

	code->colors[random_position] = random_color;
}

void permute(Chromosome *code)
{
	for (int i = 0; i < PER; i++)
	{
		if (rand() % 2 == 0)
		{
			int random_position_a = rand() % PER;
			int random_position_b = rand() % PER;

			int temp = code->colors[random_position_a];
			code->colors[random_position_a] = code->colors[random_position_b];
			code->colors[random_position_b] = temp;
		}
	}
}

int check_play(Chromosome ai_choice, Chromosome right_choice)
{
	int placeTrue = 0;
	int placeFalse = 0;

	for (int i = 0; i < PER; i++)
	{
		if (ai_choice.colors[i] == right_choice.colors[i])
		{
			placeTrue++;
			right_choice.colors[i] = -1;
			ai_choice.colors[i] = -2;
		}
	}

	for (int i = 0; i < PER; i++)
	{
		if (ai_choice.colors[i] != -2)
		{
			for (int j = 0; j < PER; j++)
			{
				if (right_choice.colors[j] == ai_choice.colors[i])
				{
					placeFalse++;
					right_choice.colors[j] = -1;
					break;
				}
			}
		}
	}
	return (placeTrue + placeFalse);
}

int fitness_score(Chromosome trial, Chromosome code, Chromosome guesses[], int slots)
{
	int	differences[slots][2];
	int	sum_black_pin_differences = 0;
	int	sum_white_pin_differences = 0;

	for (int i = 0; i < slots; i++)
	{
		Chromosome guess = guesses[i];
		int guess_result[2] = check_play(trial, guess);

		differences[i][0] = abs(guess_result[0] - guess.colors[i]);
		differences[i][1] = abs(guess_result[1] - guess.colors[i]);

		sum_black_pin_differences += differences[i][0];
		sum_white_pin_differences += differences[i][1];
	}

	return sum_black_pin_differences + sum_white_pin_differences;
}

void genetic_evolution(int popsize, int generations, int (*fitness_score)(Chromosome, Chromosome, Chromosome[], int), int eliteratio, int slots)
{
	Chromosome population[popsize][PER];
	Chromosome chosen_ones[popsize][PER];

	for (int i = 0; i < popsize; i++)
	{
		for (int j = 0; j < PER; j++)
		{
			population[i][j] = rand() % COL + 1;
		}
	}

	int h = 1;
	int k = 0;

	while (k < popsize && h <= generations)
	{
		Chromosome sons[popsize][PER];

		for (int i = 0; i < popsize; i++)
		{
			// Select two parents for the son
			int parent1 = rand() % popsize;
			int parent2 = rand() % popsize;

			// Cross over the parents
			crossover(population[parent1], population[parent2]);

			// Mutate the son
			mutate(sons[i]);
		}

	// Evaluate the fitness of each son
	int son_fitness[popsize];
	for (int i = 0; i < popsize; i++)
	{
		son_fitness[i] = costfitness(sons[i], code, guesses, slots);
	}

	// Select the elite sons
	for (int i = 0; i < popsize * eliteratio; i++)
	{
		int best_son = 0;
		int best_fitness = 0;

		for (int j = 0; j < popsize; j++)
		{
			if (son_fitness[j] > best_fitness)
			{
				best_son = j;
				best_fitness = son_fitness[j];
			}
		}

		chosen_ones[i] = sons[best_son];
		son_fitness[best_son] = -1; // Prevent selecting the same son again
	}

	// Replace the population with the elite sons and the rest of the sons
	for (int i = popsize * eliteratio; i < popsize; i++)
	{
		chosen_ones[i] = sons[i];
	}

	// Replace the population with the elite sons
	for (int i = 0; i < popsize; i++)
	{
		for (int j = 0; j < PER; j++)
		{
			population[i][j] = chosen_ones[i][j];
		}
	}
	h++;
	k++;
  }
}
