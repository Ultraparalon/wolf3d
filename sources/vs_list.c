/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 09:54:08 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/14 09:54:10 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_pack	*vs_list_pack_new(char *str)
{
	t_pack	*new;

	new = NULL;
	if (!(new = malloc(sizeof(t_pack))))
		ft_error("couldn't allocate memory");
	new->card = ft_strsplit(str, ' ');
	new->next = NULL;
	return (new);
}

void	vs_list_pack_add(t_pack **dest, t_pack *new)
{
	if (new)
	{
		new->next = *dest;
		*dest = new;
	}
}

void	vs_list_pack_del(t_pack **pack)
{
	t_pack *tmp;

	while (*pack)
	{
		tmp = *pack;
		*pack = tmp->next;
		ft_card_destructor((void **)tmp->card);
		free(tmp);
		tmp = NULL;
	}
	pack = NULL;
}
