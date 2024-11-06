#include "../minishel.h"

void	input_handle(void)
{
	mini_call()->token = input_split_to_token(special_split(mini_call()->input));
	mini_call()->token = re_tokenize(mini_call()->token);
	tilde_loop(mini_call()->token);
	expand_vars_loop(mini_call()->token);
	first_parse(mini_call()->token);
}