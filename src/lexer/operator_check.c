#include "minishell.h"

void	process_one(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = ' ';
	(*i)++;
}

void	process_two(char *input, char *output, int *i, int *j)
{
	output[(*j)++] = ' ';
	output[(*j)++] = input[*i];
	output[(*j)++] = input[*i + 1];
	output[(*j)++] = ' ';
	(*i) += 2;
}

// void	process_three(char *input, char *output, int *i, int *j)
// {
// 	output[(*j)++] = ' ';
// 	output[(*j)++] = input[*i];
// 	output[(*j)++] = input[*i + 1];
// 	output[(*j)++] = input[*i + 2];
// 	output[(*j)++] = ' ';
// 	(*i) += 3;
// }