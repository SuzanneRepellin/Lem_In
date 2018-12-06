/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstadd.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/14 17:36:02 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 13:01:51 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

void	t_room_push_front(t_room **begin, t_room *start)
{
	if (*begin)
	{
		start->next = *begin;
		*begin = start;
	}
	else
		*begin = start;
}

void	t_room_push_back(t_room **begin_list, t_room *end)
{
	t_room	*room;

	room = *begin_list;
	if (room)
	{
		while (room->next)
			room = room->next;
		room->next = end;
	}
	else
		*begin_list = end;
}

t_room	*find_sort_add(t_room *start, t_room *begin)
{
	t_room	*sorted;

	sorted = begin;
	while (sorted)
	{
		if (!ft_strcmp(sorted->name, start->name))
			return (sorted);
		else
			sorted = sorted->next;
	}
	return (NULL);
}

void	fill_t_room_next(t_map *map, t_room *rooms)
{
	t_room	*start;
	t_tube	*tubes;
	int		i;

	start = map->start;
	while (rooms)
	{
		i = 0;
		tubes = map->tube;
		while (tubes)
		{
			if (!ft_strcmp(rooms->name, map->end->name))
				break ;
			if (!ft_strcmp(rooms->name, tubes->link1->name) ||
					!ft_strcmp(rooms->name, tubes->link2->name))
				i++;
			tubes = tubes->next;
		}
		if (!(rooms->links = (t_room**)malloc(sizeof(t_room*) * (i + 1))))
			return ;
		rooms->links[i] = NULL;
		fill_tube_links(tubes, rooms, map);
		rooms = rooms->next;
	}
	rooms = map->start;
}

t_room	*sort_rooms(t_map *map)
{
	t_room	*rooms;
	t_room	*roomstart;

	if (!map->start->com || !ft_strstr(map->start->com, "##start"))
		aff_error(map);
	rooms = map->start;
	roomstart = rooms;
	fill_t_room_next(map, rooms);
	return (roomstart);
}
