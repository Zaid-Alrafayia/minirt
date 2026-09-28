/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 15:02:19 by jalghamd          #+#    #+#             */
/*   Updated: 2026/09/28 21:12:56 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	if (ft_strncmp(&file[len - 3], ".rt", 3) == 0)
		return (1);
	return (0);
}

int	check_fvalidity(char *file)
{
	int		fd;
	char	buff[1];
	int		bytesread;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open the file or the file doesn't exist\n",
			2);
		return (0);
	}
	bytesread = read(fd, buff, 1);
	if (bytesread == 0 || bytesread < 0)
	{
		ft_putstr_fd("Error\nThe file is empty or cannot be read\n", 2);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
