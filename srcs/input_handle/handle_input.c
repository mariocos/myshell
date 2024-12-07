#include "../minishell.h"

void	finish_input(char *new_input)
{
	if (!new_input)
		return ;
	add_history(new_input);
	free(new_input);
	mini_call()->input = NULL;
}

int	input_handle(void)
{
	if (!parse_quotes(mini_call()->input))
	{
		syntax_error();
		return (-1);
	}
//	printf("input is [%s]\n", mini_call()->input);
	mini_call()->token = input_split_to_token(special_split(mini_call()->input));
	mini_call()->token = re_tokenize(mini_call()->token);
	expand_vars_loop(mini_call()->token);
	tilde_loop(mini_call()->token);
	if (!first_parse(mini_call()->token))
	{
		syntax_error();
		return (-1);
	}
	tokens_to_pipex(mini_call()->token);
	remove_pipex_quotes(mini_call()->pipex_list);
//	print_pipex_list(mini_call()->pipex_list);
	finish_input(mini_call()->input);
	return (1);
}
