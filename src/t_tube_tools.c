/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:36:02 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/27 15:02:00 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

void	t_tubeadd(t_tube **alst, t_tube *new)
{
	if (new)
	{
		if (alst == NULL)
			**alst = *new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}

void	t_tube_push_back(t_tube **begin_list, t_tube *end)
{
	t_tube	*tube;

	tube = *begin_list;
	if (tube)
	{
		while (tube->next)
			tube = tube->next;
		tube->next = end;
	}
	else
		*begin_list = end;
}

int		str_in_next(t_room *room, char *name, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (!ft_strcmp(room->links[j]->name, name))
			return (1);
		j++;
	}
	return (0);
}

void	fill_tube_links(t_tube *tubes, t_room *rooms, t_map *map)
{
	int		i;

	i = 0;
	tubes = map->tube;
	while (tubes)
	{
		if (!ft_strcmp(rooms->name, map->end->name))
			break ;
		if (!ft_strcmp(rooms->name, tubes->link1->name) &&
				ft_strcmp(rooms->name, map->end->name))
		{
			if (!str_in_next(rooms, tubes->link2->name, i))
				rooms->links[i++] = tubes->link2;
		}
		else if (!ft_strcmp(rooms->name, tubes->link2->name) &&
				ft_strcmp(rooms->name, map->end->name))
			if (!str_in_next(rooms, tubes->link1->name, i))
				rooms->links[i++] = tubes->link1;
		tubes = tubes->next;
	}
	rooms->links[i] = NULL;
}
