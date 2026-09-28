/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 16:33:34 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/09/28 16:43:16 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	main(int ac, char **av)
{
	t_app	*app;

	ac = ac + 1;
	(void)av;
	// parse
	app = malloc(sizeof(t_app));
	init_window(app);
	return (0);
}
