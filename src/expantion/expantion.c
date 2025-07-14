#include "minishell.h"

// Function 1: Initialize and handle dollar quotes (combined)
static void setup_expansion(t_token *token, t_exp_state *state)
{
    // Initialize state
    state->i = 0;
    state->in_single = 0;
    state->in_double = 0;
    state->in_dollar_quote = 0;
    
    // Handle token that starts with $" or $'
    if (token->value[0] == '$' && 
        (token->value[1] == '\"' || token->value[1] == '\''))
    {
        // Remove the leading $ by shifting everything left
        ft_memmove(token->value, token->value + 1, 
                  ft_strlen(token->value));
        state->in_dollar_quote = 1;
    }
}

// Function 2: Process quotes and dollar quotes (combined)
static int process_quotes_and_dollars(t_token *token, t_exp_state *state)
{
    // Handle embedded $" patterns not at start
    if (state->i > 0 && token->value[state->i] == '$' && 
        (token->value[state->i + 1] == '\"' || token->value[state->i + 1] == '\'') &&
        !state->in_single && !state->in_double)
    {
        ft_memmove(&token->value[state->i], &token->value[state->i + 1],
                  ft_strlen(&token->value[state->i + 1]) + 1);
        state->in_dollar_quote = 1;
        return (1);
    }
    // Process quotes
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

// Function 3: Process variables (unchanged)
static int handle_variables(t_token *token, t_data *data, t_exp_state *state)
{
    if (!should_expand_variable(&token->value[state->i], state->in_single))
        return (0);

    // Handle special case of $?
    if (token->value[state->i + 1] == '?')
    {
        if (!process_status_var(token, data, &state->i))
            return (-1);
        return (1);
    }
    // Handle regular environment variables
    if (!process_expantion(token, data, &state->i))
        return (-1);
    return (1);
}

// Function 4: Process a single token
static int process_token(t_token *token, t_data *data)
{
    t_exp_state state;
    int result;

    setup_expansion(token, &state);
    while (token->value[state.i])
    {
        // Process quotes and dollar quotes
        if (process_quotes_and_dollars(token, &state))
            continue;

        // Process variables
        result = handle_variables(token, data, &state);
        if (result == -1)
            return (0);
        if (result == 1)
            continue;

        // If no special handling, move forward
        state.i++;
    }
    return (1);
}

// Function 5: Main function (unchanged)
int expand_variables(t_token *tokens, t_data *data)
{
    t_token *current;

    if (!tokens || !data)
        return (1);

    current = tokens;
    while (current)
    {
        // Skip heredoc content and non-expandable types
        if ((!current->prev || current->prev->type != HEREDOC) &&
            (current->type == WORD || current->type == FILE_NAME) && 
            current->value)
        {
            if (!process_token(current, data))
                return (0);
        }
        current = current->next;
    }
    return (1);
}
