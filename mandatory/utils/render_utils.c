/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 13:53:31 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/08 01:40:30 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	pack_color(t_color color)
{
	int	r;
	int	g;
	int	b;

	if (color.r < 0.0)
		color.r = 0.0;
	else if (color.r > 1.0)
		color.r = 1.0;
	if (color.g < 0.0)
		color.g = 0.0;
	else if (color.g > 1.0)
		color.g = 1.0;
	if (color.b < 0.0)
		color.b = 0.0;
	else if (color.b > 1.0)
		color.b = 1.0;
	r = (int)(color.r * 255.0);
	g = (int)(color.g * 255.0);
	b = (int)(color.b * 255.0);
	return ((r * 65536) + (g * 256) + b);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
