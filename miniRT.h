/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 16:35:33 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 16:51:06 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 960
# define HEIGHT 540

# include "42_libft/libft.h"
# include "miniRT_structs.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

void	init_window(t_app *app);
void	free_object(void *content);
void	free_scene(t_scene *scene);
#endif
