#include "../minishell.h"

void	child_process_new(t_pipex	*p)
{
	if (!p)
		return ;
	if (!p->last_child)//i dont understand this 
		dup2(p->pipe[1], STDOUT_FILENO);
	
	/* do redirections! */
	do_input_redir(p);
	do_out_redir(p);

	/* Command execution: */
		// exec_if_builtin(start);
		// char *path = path_search(start->cmd[0], mini_call()->env);
		// char **envp = env_to_double_chr_ptr(mini_call()->env);
		// if (execve(path, start->cmd, envp)== -1)
		// 		printf ("EXECVE - NOTHING HAPPENED\n");
		// free(path);
		// ft_free(envp);

	close_fds(p->pipe);
	execve(p->path, p->cmd, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}