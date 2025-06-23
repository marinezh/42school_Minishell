#include <minishell.h>

// Helper function to process a quoted segment
static int process_quote_segment(char *str, int *j, int *in_quote, char *quote_char)
{
	// Handle quotes: entering or exiting quote mode
	if (!(*in_quote))
	{
		*in_quote = 1;
		*quote_char = str[*j];
	}
	else if (str[*j] == *quote_char)
		*in_quote = 0;
	(*j)++;
	return 0;
}
// Helper function to find the end of a word
static int find_word_end(char *str, char delimiter, int start)
{
	int j = start;
	int in_quote = 0;
	char quote_char = 0;

	while (str[j] && (in_quote || str[j] != delimiter))
	{
		if (str[j] == '\'' || str[j] == '\"')
			process_quote_segment(str, &j, &in_quote, &quote_char);
		else
			j++;
	}
	// Check if quotes were properly closed
	if (in_quote)
	{
		ft_putstr_fd("minishell: quotes are not closed\n", 2);
		//handle_error_arg(data, "syntax error", ": unclosed quotes\n", 2); Think how to use this function
		return -1;
	}
	return j;
}
static int add_word_to_res(char **res, int i, char *word_start, int word_len)
{
	// Safety check
	if (word_len < 0)
	{
		ft_putstr_fd("minishell: internal parse error\n", 2);
		return 0;  // Return 0 (false) for failure
	}
	// Create and add the word
	res[i] = word_dup(word_start, word_len);
	if (!res[i])
		return 0;  // Return 0 (false) for failure
	
	return 1;  // Return 1 (true) for success
}
static char **handle_split_error(char **result, int i)
{
	free_split_result(result, i);
	return NULL;
}
char **quote_safe_split(char *str, char del)
{
	char **res;
	t_split_data pos;

	res = (char **)malloc(sizeof(char *) * (word_count(str, del) + 1));
	pos.i = 0;
	pos.j = 0;
	if (!res)
		return NULL;
	while (str[pos.j])
	{
		while (str[pos.j] && str[pos.j] == del)
			pos.j++;
		if (str[pos.j])
		{
			pos.start = pos.j;
			pos.end = find_word_end(str, del, pos.start);
			if (pos.end == -1)
				return handle_split_error(res, pos.i);
			if (!add_word_to_res(res, pos.i, &str[pos.start], pos.end - pos.start))
				return handle_split_error(res, pos.i);
			pos.j = pos.end;
			pos.i++;
		}
	}
	res[pos.i] = NULL;
	return res;
}

// char **quote_safe_split_2(char *str, char delimiter)
// {
// 	int		words = word_count(str, delimiter);
// 	char	**result = (char **)malloc(sizeof(char *) * (words + 1));
// 	int		i = 0;
// 	int		j = 0;

// 	if (!result)
// 		return NULL;

// 	while (str[j])
// 	{
// 		while (str[j] && str[j] == delimiter)
// 			j++;

// 		if (str[j])
// 		{
// 			int start = j;
// 			int in_quote = 0;
// 			char quote_char = 0;

// 			while (str[j] && (in_quote || str[j] != delimiter))
// 			{
// 				if (str[j] == '\'' || str[j] == '\"')
// 				{
// 					if (!in_quote)
// 					{
// 						in_quote = 1;
// 						quote_char = str[j];
// 					}
// 					else if (str[j] == quote_char)
// 						in_quote = 0;
// 				}
// 				j++;
// 			}

// 			if (in_quote)
// 			{
// 				ft_putstr_fd("minishell: quotes are not closed\n", 2);
// 				free_split_result(result, i);
// 				return NULL;
// 			}

// 			if (j < start) // safety check (should never happen)
// 			{
// 				ft_putstr_fd("minishell: internal parse error\n", 2);
// 				free_split_result(result, i);
// 				return NULL;
// 			}

// 			result[i] = word_dup(&str[start], j - start);
// 			if (!result[i])
// 			{
// 				free_split_result(result, i);
// 				return NULL;
// 			}

// 			// DEBUG: check address of each allocation
// 			// printf("result[%d] = \"%s\" at %p\n", i, result[i], result[i]);

// 			i++;
// 		}
// 	}

// 	result[i] = NULL;
// 	return result;
// }
///////////////////////////////////////////////////////////////////////////
// char **quote_safe_split_1(char *str, char delimiter)
// {
// 	int words = word_count(str, delimiter);
// 	char **result = (char **)malloc(sizeof(char *) * (words + 1));
// 	int i = 0; 
// 	int j = 0;
	
// 	if (!result)
// 		return NULL;
// 	while (str[j])
// 	{
// 		while (str[j] && (str[j] == delimiter))
// 			j++;
// 		if (str[j])
// 		{
// 			int start = j;
// 			if (str[j] == '\'' || str[j] == '\"')
// 			{
// 				while(str[j] == '\'' || str[j] == '\"')
// 				{
// 					if (skip_quoted_seg(str, &j) == -1)
// 					{
// 						free_split_result(result, i);
// 						return NULL;
// 					}
// 				}
// 			}
// 			else 
// 			{
// 				int in_quote = 0;
// 				char quote_char = 0;

// 				while (str[j] && (in_quote || str[j] != delimiter))
// 				{
// 					if ((str[j] == '\'' || str[j] == '\"'))
// 					{
// 						if (!in_quote)
// 						{
// 							in_quote = 1;
// 							quote_char = str[j];
// 						}
// 						else if (str[j] == quote_char)
// 							in_quote = 0;
// 					}
// 					j++;
// 				}
// 				if (in_quote == 1)
// 				{
// 					ft_putstr_fd("minishell: quotes are not closed\n", 2);
// 					free_split_result(result, i);
// 					return NULL;
// 				}
// 			}
// 			if (j < start) // safety check (should never happen)
// 			{
// 				ft_putstr_fd("minishell: internal parse error\n", 2);
// 				free_split_result(result, i);
// 				return NULL;
// 			}
// 			result[i] = word_dup(&str[start], j - start); // Copy the word and store it in the array
// 			if (!result[i])
// 			{
// 				free_split_result(result, i);
// 				return NULL;
// 			}
// 			//printf("result[%d] = \"%s\" at %p\n", i, result[i], result[i]);
// 			i++;
// 		}
// 	}

// 	result[i] = NULL;
// 	return result;
// }

// char **quote_safe_split_2(char *str, char delimiter)
// {
//     int words = word_count(str, delimiter);
//     char **result = (char **)malloc(sizeof(char *) * (words + 1));
//     int i = 0;
//     int j = 0;
	
//     if (!result)
//         return NULL;
//     while (str[j])
//     {
//         while (str[j] && str[j] == delimiter)
//             j++;
//         if (str[j])
//         {
//             int start = j;
//             int word_end = find_word_end(str, delimiter, start);
			
//             if (word_end == -1 || add_word_to_result(result, i, str, start, word_end) == -1)
//             {
//                 free_split_result(result, i);
//                 return NULL;
//             }
			
//             j = word_end;
//             i++;
//         }
//     }
	
//     result[i] = NULL;
//     return result;
// }

