/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:25:35 by jmeruma           #+#    #+#             */
/*   Updated: 2022/11/22 16:18:19 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fdf.h>

int	main(int argc, char *argv[])
{
	int		fd;
	t_point	**list;

	if (argc != 2)
		return (perror("argc"), 1);
	fd = map_validity(argv);
	if (fd == -1)
		return (perror("map invalid"), 1);
	list = map_creation(fd);
}