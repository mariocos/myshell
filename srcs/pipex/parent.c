#include "../minishell.h"

/*
the parent proccess should be called with a t_pipex struct wich allows it to execute a comand
*/
void	pipe_error(void)
{
	printf("\n\na critical error has ocurred when creating a pipe\n\n");
	perror("pipe");
	exit(EXIT_FAILURE);
}

void	fork_error(void)
{
	printf("a critical error has occured trying to fork\n");
	perror("fork");
	exit(EXIT_FAILURE);
}

void	close_fds(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

void	spawn_child(t_pipex *p)
{
	if (!p)
		return ;
	if (pipe(p->pipe) < 0)
		pipe_error();
	p->pid = fork();
	if (p->pid < 0)
		fork_error();
	if (p->pid == 0)
		child_process_new(p);
	if (p->previous)
		close(p->previous->pipe[0]);
	close(p->pipe[1]);
}

void	ft_waitpid(int pid)
{
	int		status;
	int		exit_code;
	int		term_signal;

	mini_call()->exit_status = 0;
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (exit_code != 0)
				mini_call()->exit_status = exit_code;
		}
	}
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		mini_call()->exit_status = 128 + term_signal;
	}

}


void	process_handler(t_pipex *p)//TODO:function too large split between call with pipes and without!
{
	prep_input_redir(mini_call()->pipex_list);
	prep_output_redir(mini_call()->pipex_list);
	//missing if statement for if redir prep was a fail!//TODO:
	if (p->next == NULL)
	{
		if (is_builtin(p))//and not echo! echo is run in fork();
		{
			exec_if_builtin(p);
		}
		else
		{
			p->pid = fork();
			if (p->pid == 0)
				child_process_new(p);
			ft_waitpid(p->pid);
		}
	}
	else
	{
		while(p != NULL)
		{
			spawn_child(p);
			p = p->next;
		}
		p = mini_call()->pipex_list;
		while (p)
		{
			ft_waitpid(p->pid);
			p = p->next;
		}
	}
}
