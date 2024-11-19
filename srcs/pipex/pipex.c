/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo-mar <hugo-mar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:03:33 by hugo-mar          #+#    #+#             */
/*   Updated: 2024/11/19 16:36:16 by hugo-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// This is a ring scheme: parent -> child(0) -> ... -> child(n) -> parent 
// The number of pipes is equal of (pick one from above, they are the same):
// - the number of processes (parent + number of childs)
// - number of child processes + 1 (this is the code operationalization)

void	free_pipes(int **pipes, size_t nbr_of_pipes)
{
	size_t	i;

	i = 0;
	if (pipes != NULL)
	{
		while (i < nbr_of_pipes)
		{
			if (pipes[i] != NULL)
				free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}

static int	**allocate_pipes(size_t nbr_of_pipes)
{
	int		**pipes;
	size_t	i;

	pipes = malloc (sizeof(int *) * nbr_of_pipes);
	if (!pipes)
	{
		perror("malloc pipes");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nbr_of_pipes)
	{
		pipes[i] = malloc (sizeof(int) * 2);
		if (!pipes[i])
		{
			free_pipes(pipes, i);
			perror("malloc pipes[i]");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

int	**create_pipes(size_t nbr_of_pipes)
{
	int		**pipes;
	size_t	i;

	pipes = allocate_pipes(nbr_of_pipes);
	i = 0;
	while (i < nbr_of_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			free_pipes(pipes, nbr_of_pipes);
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}

void	child_pipe_setup(int index, t_ppx_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		if (i != index)
			close(data->pipes[i][0]);
		if (i != index + 1)
			close(data->pipes[i][1]);
		i++;
	}
}

void	parent_pipe_setup(t_ppx_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_pipes)
	{
		if (i != data->nbr_pipes - 1)
			close(data->pipes[i][0]);
		if (i != 0)
			close(data->pipes[i][1]);
		i++;
	}
}

void	create_child(int p_index, t_ppx_data *data)
{
	pid_t	p_id;

	p_id = fork();
	if (p_id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (p_id == 0)
	{
		data->p_ids[p_index] = getpid();
		child_pipe_setup(p_index, data);
		
		// Some code execution
		printf("Child %d: %d\n", p_index, data->p_ids[p_index]);

		close(data->pipes[p_index][0]);
		close(data->pipes[p_index + 1][1]);
		free_pipes(data->pipes, data->nbr_pipes);
		free(data->p_ids);
		exit(EXIT_SUCCESS);
	}
}

void	child_spawn(t_ppx_data *data)
{
	int	i;

	data->p_ids = (pid_t *) malloc (sizeof(pid_t) * (data->nbr_pipes - 1));
	if (data->p_ids == NULL)
	{
		perror("malloc p_ids");
		free_pipes(data->pipes, data->nbr_pipes);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_processes)
	{
		create_child(i, data);
		i++;
	}
}

/* ************************************************************************ */ 
/* INFO ON RUNNING THE FOLLOWING MAIN:										*/
/* - The #define PROCESS_NBR 5 is to be substituted with code from the main */
/* - The for loop from main related to enviroment fd's needs to be removed  */
/* ************************************************************************ */ 

/* #define PROCESS_NBR 5
int	main()
{
	t_ppx_data	data;

//	This for loop fix a strange fd leak in my system
//	for (int fd = 3; fd < 1024; fd++)
//   	close(fd);

	data.nbr_processes = PROCESS_NBR;
	data.nbr_pipes = PROCESS_NBR + 1;
	
	data.pipes = create_pipes(data.nbr_pipes);

	child_spawn(&data);

	parent_pipe_setup(&data);

	// Some code execution

	close (data.pipes[0][1]);
	close (data.pipes[data.nbr_pipes - 1][0]);

	int	i;
	i = 0;
	while (i < data.nbr_processes)
	{
		wait(NULL);
		i++;
	}

	free_pipes(data.pipes, data.nbr_pipes);
	free(data.p_ids);

	data.exit_status = 0;
	return (data.exit_status);
} */
