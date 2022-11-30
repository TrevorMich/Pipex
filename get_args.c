/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioduwole <ioduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 23:48:18 by ioduwole          #+#    #+#             */
/*   Updated: 2022/11/27 17:35:55 by ioduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_args(t_frame *ppx, char **argv, char **envp, int process)
{
	if (ppx->pid == 0)
		return (0);
	ppx->i = 0;
	if (process == 1)
	{
		ppx->cmd = ft_split(argv[2], ' ');
		if (access(ppx->cmd[0], X_OK) == 0)
			return (1);
	}
	else if (process == 2)
	{
		ppx->cmd = ft_split(argv[3], ' ');
		if (access(ppx->cmd[0], X_OK) == 0)
			return (1);
	}
	while (envp[ppx->i])
	{
		if (ft_strncmp(envp[ppx->i], "PATH=", 5) == 0)
		{
			ppx->pre_env = ft_split(&envp[ppx->i][5], ':');
		}
		ppx->i++;
	}
	return (get_path(ppx));
}

int	get_path(t_frame *ppx)
{
	ppx->env = ft_calloc(arr_len(ppx->pre_env) + 1, sizeof(char *));
	ppx->i = 0;
	while (ppx->i < arr_len(ppx->pre_env))
	{
		if (ppx->pre_env[ppx->i][ft_strlen(ppx->pre_env[ppx->i]) - 1] != '/')
		{
			ppx->env[ppx->i] = ft_strjoin(ppx->pre_env[ppx->i],
					ppx->tmp = ft_strjoin("/", ppx->cmd[0]));
			free (ppx->tmp);
		}
		else
			ppx->env[ppx->i] = ft_strjoin(ppx->pre_env[ppx->i], ppx->cmd[0]);
		if (access(ppx->env[ppx->i], X_OK) == 0)
		{
			ppx->path = ppx->env[ppx->i];
			break ;
		}
		ppx->i++;
	}
	if (ppx->path)
		return (add_path(ppx), 1);
	return (ft_printf("Sorry, an error occurred in finding path: ->%s<-\n",
			ppx->cmd[0], 0), clear_array(ppx, 3), 0);
}

void	process_1(t_frame *ppx, char **envp)
{
	if (ppx->pid == 0)
	{
		close(ppx->fd[0]);
		dup2(ppx->infile, STDIN_FILENO);
		dup2(ppx->fd[1], STDOUT_FILENO);
		close(ppx->fd[1]);
		if (execve(ppx->cmd[0], ppx->cmd, envp) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}
}

void	process_2(t_frame *ppx, char **envp)
{
	if (ppx->pid2 == 0)
	{
		dup2(ppx->fd[0], STDIN_FILENO);
		close(ppx->fd[1]);
		dup2(ppx->outfile, STDOUT_FILENO);
		close(ppx->fd[0]);
		if (execve(ppx->cmd[0], ppx->cmd, envp) == -1)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
	}
}

void	clear_array(t_frame *ppx, int f)
{
	if (ppx->pid == 0 || ppx->pid2 == 0)
		return ;
	if (f == 1)
	{
		wait(NULL);
		clear_string(ppx->cmd);
		clear_string(ppx->pre_env);
		clear_string(ppx->env);
		ppx->path = NULL;
	}
	else
	{
		close(ppx->fd[0]);
		close(ppx->fd[1]);
		wait(NULL);
		close(ppx->infile);
		close(ppx->outfile);
		clear_string(ppx->cmd);
		clear_string(ppx->pre_env);
		clear_string(ppx->env);
		free(ppx);
	}
}
