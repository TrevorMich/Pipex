/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ioduwole <ioduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:33:23 by ioduwole          #+#    #+#             */
/*   Updated: 2022/11/26 21:11:24 by ioduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_frame	*ppx;

	ppx = init_ppx(argc, argv);
	if (ppx == NULL)
		return (1);
	if (!(get_args(ppx, argv, envp, 1)))
		return (2);
	ppx->pid = fork();
	if (ppx->pid == -1)
		return (ft_printf("Error creating child process. Quitting.\n"), 3);
	process_1(ppx, envp);
	clear_array(ppx, 1);
	if (!(get_args(ppx, argv, envp, 2)))
		return (4);
	ppx->pid2 = fork();
	if (ppx->pid2 == -1)
		return (ft_printf("Error creating child process. Quitting.\n"), 5);
	process_2(ppx, envp);
	clear_array(ppx, 2);
	printf("SUCCESS WITH PIPEX CHEERS!!!\n");
	return (0);
}
