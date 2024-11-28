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
	if (!p)//this should be exit so we dont get double forks
		return ;
	if (pipe(p->pipe) < 0)
		pipe_error();
	p->pid = fork();
	if (p->pid < 0)
		fork_error();
	if (p->pid == 0)
		child_process_new(p);
	dup2(p->pipe[0], STDIN_FILENO);
	close_fds(p->pipe);	
}

	//M - if child was bad stop piping - missing implementation
	//H - Isn't exit_failure in child enough?
void	process_handler(t_pipex *p)//TODO:function too large split between call with pipes and without!
{
	if (p->next == NULL)
	{
		if (is_builtin(p))//and not echo! echo is run in fork();
		{
			/*redir*/
			printf("doing command in parent\n");
			do_out_redir(p);
			do_input_redir(p);//i think i want to reset redirections after command exec so this doesnt impact the next comand
			exec_if_builtin(p);
		}
		else
		{
			printf("doing comand in fork\n");
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
			p->last_child = (p->next == NULL);//this can just be checked dinamicaly
			spawn_child(p);
			p = p->next;
		}
		exit(0);//just for now
/*  		int	p_id = 1;//i think this is a problem
		while (p_id > 0)
			p_id = wait(NULL); */             /*wait not working need to fix!*/
//		waitpid(p->pid, NULL, 0);
	}
}
