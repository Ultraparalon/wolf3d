/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_music.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:47:36 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/13 13:47:37 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	vs_music(void)
{
	int i;

	i = rand() % 6;
	if (!system("pgrep afplay"))
		system("killall afplay");
	if (i == 1)
		system("afplay sound/schism.mp3 &");
	else if (i == 2)
		system("afplay sound/prison.mp3 &");
	else if (i == 3)
		system("afplay sound/stinkfist.mp3 &");
	else if (i == 4)
		system("afplay sound/always.mp3 &");
	else if (i == 5)
		system("afplay sound/takeonme.mp3 &");
	else
		system("afplay sound/little.mp3 &");
}
