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
	int	status;
	int	term_signal;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue;
		else
		{
			perror("waitpid");
			mini_call()->exit_status = 1;
			return ;
		}
	}
	if (WIFEXITED(status))
		mini_call()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		term_signal = WTERMSIG(status);
		mini_call()->exit_status = 128 + term_signal;
	}
	else
		mini_call()->exit_status = 1;
}

void	process_handler(t_pipex *p)//TODO:function too large split between call with pipes and without!
{
	if (prep_input_redir(mini_call()->pipex_list) < 0)
		return ;
	if (mini_call()->exit_status != 0 && p->has_doc)//basically if there was a heredoc wich is reset to zero after the comand is done
		return ;
	if (prep_output_redir(mini_call()->pipex_list) < 0)
		return ;
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
