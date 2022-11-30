/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioduwole <ioduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:33:27 by ioduwole          #+#    #+#             */
/*   Updated: 2022/11/27 17:25:00 by ioduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_frame	*init_ppx(int argc, char **argv)
{
	t_frame	*ppx;

	if (argc != 5)
		return (ft_printf("Error argument is less than 5\n"), NULL);
	ppx = (t_frame *)malloc(1 * sizeof(t_frame));
	if (ppx == NULL)
		return (ft_printf("Error failed to initialise\n"), NULL);
	ppx->infile = open(argv[1], O_RDONLY);
	ppx->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (ppx->infile == -1 || ppx->outfile == -1)
	{
		free(ppx);
		return (perror("Error"), NULL);
	}
	if (pipe(ppx->fd) == -1)
	{
		free(ppx);
		return (ft_printf("Error; Pipe Failed"), NULL);
	}
	init_null(ppx);
	return (ppx);
}

void	clear_string(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free (str);
}

int	arr_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	init_null(t_frame *ppx)
{
	ppx->path = NULL;
	ppx->cmd = NULL;
	ppx->env = NULL;
	ppx->pre_env = NULL;
	ppx->pid = -5;
	ppx->pid2 = -5;
}

void	add_path(t_frame *ppx)
{
	int		i;
	char	**dst;

	dst = ft_calloc(arr_len(ppx->cmd) + 2, sizeof(char *));
	dst[0] = ft_strdup(ppx->path);
	i = 1;
	while (ppx->cmd[i])
	{
		dst[i] = ft_strdup(ppx->cmd[i]);
		i++;
	}
	clear_string(ppx->cmd);
	ppx->cmd = dst;
}
