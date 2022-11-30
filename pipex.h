/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioduwole <ioduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:33:35 by ioduwole          #+#    #+#             */
/*   Updated: 2022/11/27 17:22:15 by ioduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_frame
{
	int		i;
	int		fd[2];
	int		pid;
	int		pid2;
	int		wstatus;
	int		statuscode;
	int		infile;
	int		outfile;
	char	**cmd;
	char	**pre_env;
	char	**env;
	char	*tmp;
	char	*path;
}	t_frame;

t_frame	*init_ppx(int argc, char **argv);
void	clear_string(char **str);
int		arr_len(char **arr);
void	init_null(t_frame *ppx);
int		get_path(t_frame *ppx);
int		get_args(t_frame *ppx, char **argv, char **envp, int prcoess);
void	add_path(t_frame *ppx);
void	process_1(t_frame *ppx, char **envp);
void	process_2(t_frame *ppx, char **envp);
void	clear_array(t_frame *ppx, int f);

#endif
