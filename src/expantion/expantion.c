#include "minishell.h"

static void	setup_expansion(t_token *token, t_exp_state *state)
{
	state->i = 0;
	state->in_single = 0;
	state->in_double = 0;
	state->in_dollar_quote = 0;
	if (token->value[0] == '$' && (token->value[1] == '\"'
			|| token->value[1] == '\''))
	{
		ft_memmove(token->value, token->value + 1, ft_strlen(token->value));
		state->in_dollar_quote = 1;
	}
}

static int	process_quotes_and_dollars(t_token *token, t_exp_state *state)
{
	if (state->i > 0 && token->value[state->i] == '$'
		&& (token->value[state->i + 1] == '\"'
			|| token->value[state->i + 1] == '\'')
		&& !state->in_single && !state->in_double)
	{
		ft_memmove(&token->value[state->i], &token->value[state->i + 1],
			ft_strlen(&token->value[state->i + 1]) + 1);
		state->in_dollar_quote = 1;
		return (1);
	}
	if (token->value[state->i] == '\'' && !state->in_double)
	{
		state->in_single = !state->in_single;
		state->i++;
		return (1);
	}
	else if (token->value[state->i] == '\"' && !state->in_single)
	{
		state->in_double = !state->in_double;
		if (!state->in_double && state->in_dollar_quote)
			state->in_dollar_quote = 0;
		state->i++;
		return (1);
	}
	return (0);
}

static int	handle_variables(t_token *token, t_data *data, t_exp_state *state)
{
	if (!should_expand_variable(&token->value[state->i], state->in_single))
		return (0);
	if (token->value[state->i + 1] == '?')
	{
		if (!process_status_var(token, data, &state->i))
			return (-1);
		return (1);
	}
	if (!process_expantion(token, data, &state->i))
		return (-1);
	return (1);
}

static int	process_token(t_token *token, t_data *data)
{
	t_exp_state	state;
	int			result;

	setup_expansion(token, &state);
	while (token->value[state.i])
	{
		if (process_quotes_and_dollars(token, &state))
			continue ;
		result = handle_variables(token, data, &state);
		if (result == -1)
			return (0);
		if (result == 1)
			continue ;
		state.i++;
	}
	return (1);
}

int	expand_variables(t_token *tokens, t_data *data)
{
	t_token	*current;

	if (!tokens || !data)
		return (1);
	current = tokens;
	while (current)
	{
		if ((!current->prev || current->prev->type != HEREDOC)
			&& (current->type == WORD || current->type == FILE_NAME)
			&& current->value)
		{
			if (!process_token(current, data))
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
