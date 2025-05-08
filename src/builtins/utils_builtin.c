#include"minishell.h"

int var_name_len(char *name)
{
	int count;

	count = 0;
	while (name[count] && name[count] != '=')
		count++;
	if (name[count] == '=')
		count++;
	return(count);
}

void	print_error_msg(char **args, char *msg)
{
	int i;

	printf("usage: ");
	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%s", msg);
}