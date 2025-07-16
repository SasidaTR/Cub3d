/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douzgane <douzgane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:15:00 by douzgane          #+#    #+#             */
/*   Updated: 2025/07/16 18:54:25 by douzgane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	check_extension_validity(char *filename, char *dot_pos, char **argv)
{
	if (!dot_pos)
		return (ft_printf("Error: File has no extension\nUsage: %s "
				"<map_file.cub>\nFile must have .cub extension\n", argv[0]), 0);
	if (strcmp(dot_pos, ".cub") != 0)
		return (ft_printf("Error: Invalid file extension '%s'\nUsage: %s "
				"<map_file.cub>\nFile must have .cub extension\n",
				dot_pos, argv[0]), 0);
	if (dot_pos == filename)
		return (ft_printf("Error: Invalid filename '.cub'\nUsage: %s "
				"<map_file.cub>\nFilename cannot start with '.'\n", argv[0]), 0);
	if (ft_strlen(filename) < 5)
		return (ft_printf("Error: Filename too short\nUsage: %s "
				"<map_file.cub>\nMinimum filename: 'x.cub'\n", argv[0]), 0);
	return (1);
}

static int	validate_filename_format(char *filename, char **argv)
{
	char	*dot_pos;

	if (!filename || ft_strlen(filename) == 0)
		return (ft_printf("Error: Empty filename\nUsage: %s "
				"<map_file.cub>\nPlease provide a valid .cub file\n",
				argv[0]), 0);
	dot_pos = strrchr(filename, '.');
	return (check_extension_validity(filename, dot_pos, argv));
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("Error: Invalid number of arguments\nUsage: %s "
				"<map_file.cub>\nPlease provide exactly one .cub file\n",
				argv[0]), 0);
	return (validate_filename_format(argv[1], argv));
}
