#include "minishell.h"

/**
 * Frees multiple string pointers
 * Function accepts a variable number of string pointers and frees each one
 * The last argument must be NULL to indicate the end of arguments
 */
void	free_strings(char *str, ...)
{
	va_list	args;
	char	*ptr;

	if (str)
		free(str);
	va_start(args, str);
	while ((ptr = va_arg(args, char *)) != NULL)
		free(ptr);
	va_end(args);
}
void	free_exp_parts(t_exp_parts *parts)
{
	if (!parts)
		return ;
	free(parts->status_str);
	free(parts->prefix);
	free(parts->suffix);
	free(parts->new_value);
	free(parts->final_value);
	*parts = (t_exp_parts){0};
}