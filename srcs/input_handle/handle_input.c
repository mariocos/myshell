#include "../minishell.h"

void	finish_input(char *new_input)
{
	if (!new_input)
		return ;
	add_history(new_input);
	free(new_input);
	mini_call()->input = NULL;
}

void	input_handle(void)
{
	if (!parse_quotes(mini_call()->input))
		syntax_error();
	mini_call()->token = input_split_to_token(special_split(mini_call()->input));
	mini_call()->token = re_tokenize(mini_call()->token);
	expand_vars_loop(mini_call()->token);
	tilde_loop(mini_call()->token);
	if (!first_parse(mini_call()->token))
		syntax_error();
	tokens_to_pipex(mini_call()->token);
	finish_input(mini_call()->input);
}

