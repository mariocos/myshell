#include "../minishell.h"

void	child_process_new(t_pipex	*p)
{
	if (!p)
		return ;
	/* do redirections! */
	do_input_redir(p);
	do_out_redir(p);


	/*catch builtins here*/
	if (is_builtin(p))
		exec_if_builtin(p);
	else
	{
		/* Command execution: */
		// exec_if_builtin(start);
		char *path = path_search(p->cmd[0], mini_call()->env);
		printf("PATH - %s\n", path);
		char **envp = env_to_double_chr_ptr(mini_call()->env);//if theese are neeeded they need to be added to the p struct to be freed
		if (!envp || !envp[0])
		{
    		static char *empty_env[] = {NULL};
    		envp = empty_env; // Um ambiente vazio válido
		}
		printf("execing in fork\n");
		if (execve(path, p->cmd, envp) == -1)
	 		printf ("EXECVE - NOTHING HAPPENED\n");
		// free(path);
		// ft_free(envp);
		perror("execve");
	}
	exit(EXIT_FAILURE);
}