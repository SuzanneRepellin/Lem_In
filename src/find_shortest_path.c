/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 14:33:42 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 15:02:01 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*remove_path_from_map(t_map *map, t_room *path)
{
//	t_map	*newmap;
	t_room	*newrooms;
	t_room	*newstart;
	t_room	*pathstart;

	pathstart = path->next;
	newrooms = t_roomcpy(map->start);
	newstart = newrooms;
//	newmap = mapcopy(map);
	while (newrooms != map->end)
	{
		path = pathstart;
		newrooms->next->prev = newrooms;
		newrooms = newrooms->next;
		while (path != map->end)
		{
			if (newrooms == path)
			{
				newrooms->prev->next = newrooms->next;
				free_t_room(&newrooms);
				break ;
			}
			else
				path = path->next;
		}
	}
	return (newstart);
}

t_room	*backtoprev(t_room **room, t_room **path, int j)
{
	t_room	*tmp;

	(*room)->i = 0;
	tmp = *room;
	*room = (*room)->prev;
	*path = (*path)->prev;
	free_t_room(&((*path)->next));
	(*path)->next = NULL;
	(*room)->i = (*room)->i + j;
	return (tmp);
}

void	getnext(t_room **tmp, t_room **room, t_room **path, t_room *pathstart)
{
	if (!find_room_in_path((*room)->links[(*room)->i], pathstart)
			&& (!*tmp || ft_strcmp((*tmp)->name,
					(*room)->links[(*room)->i]->name)))
	{
		(*path)->next = t_roomcpy((*room)->links[(*room)->i]);
		(*path)->next->prev = *path;
		(*path) = (*path)->next;
		(*path)->i = (*path)->prev->i + 1;
		(*room)->links[(*room)->i]->prev = *room;
		*room = (*room)->links[(*room)->i];
		(*room)->i = 0;
	}
	else
		(*room)->i++;
}

int		chose_backtrack(t_map **map, t_room **room, t_room **tmp, t_room **path)
{
	if ((*room)->prev && (*room)->prev->links[(*room)->prev->i + 1]
			&& (!*tmp ||
				ft_strcmp((*room)->prev->links[(*room)->prev->i + 1]->name,
					(*tmp)->name) || (*room)->i >= (*map)->shortlen))
		*tmp = backtoprev(room, path, 1);
	else if ((*room)->prev && (!*tmp || ft_strcmp((*tmp)->name,
					(*room)->prev->name) || (*room)->i >= (*map)->shortlen))
		*tmp = backtoprev(room, path, 0);
	else
		return (1);
	return (0);
}

void	get_new_shortest(t_map **map, t_room *pathstart)
{
	if (!(*map)->shortlen ||
			calc_path_lenght(pathstart) < (*map)->shortlen)
	{
		free_t_room(&((*map)->shortest));
		(*map)->shortlen = calc_path_lenght(pathstart);
		(*map)->shortest = pathcpy(pathstart);
	}
}

void	calc_shortest_path(t_map *map)
{
	t_room	*room;
	t_room	*path;
	t_room	*pathstart;
	t_room	*tmp;

	room = map->start;
	path = t_roomcpy(room);
	pathstart = path;
	path->i = 0;
	tmp = NULL;
	while (room)
	{
		while (room->links && room->links[room->i] &&
				(!map->shortlen || path->i <= map->shortlen))
			getnext(&tmp, &room, &path, pathstart);
		if (!ft_strcmp(path->name, map->end->name))
			get_new_shortest(&map, pathstart);
		if (chose_backtrack(&map, &room, &tmp, &path))
		{
			free_t_room(&pathstart);
			break ;
		}
	}
}
