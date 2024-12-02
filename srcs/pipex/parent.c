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

void	process_handler(t_pipex *p)//TODO:function too large split between call with pipes and without!
{
	prep_input_redir(mini_call()->pipex_list);
	if (p->next == NULL)
	{
		if (is_builtin(p))//and not echo! echo is run in fork();
		{
			/*redir*/
	//		printf("doing command in parent\n");
			do_out_redir(p);//maybe change so its like prep input redir
			do_input_redir(p);
			exec_if_builtin(p);
		}
		else
		{
	//		printf("doing %s comand in fork\n", p->cmd[0]);
			/*fork and execve*/
			p->pid = fork();
			if (p->pid == 0)
				child_process_new(p);
			waitpid(p->pid, NULL, 0);
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
			waitpid(p->pid, NULL, 0);
			p = p->next;
		}
	}
}
