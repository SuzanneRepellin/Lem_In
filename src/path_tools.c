/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 14:33:42 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 14:22:19 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*t_roomcpy(t_room *src)
{
	t_room	*cpy;

	if (!(cpy = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	cpy->name = ft_strdup(src->name);
	cpy->com = ft_strdup(src->com);
	cpy->ant = src->ant;
	cpy->x = src->x;
	cpy->y = src->y;
	cpy->i = src->i;
	cpy->next = NULL;
	cpy->prev = NULL;
	cpy->links = NULL;
	return (cpy);
}

void	free_t_room(t_room **start)
{
	t_room	*tmp;
	t_room	*del;

	del = *start;
	while (del)
	{
		tmp = del->next;
		ft_strdel(&(del->name));
		ft_strdel(&(del->com));
		if (del->links)
			free(del->links);
		del->links = NULL;
		free(del);
		del = tmp;
	}
	del = NULL;
	*start = NULL;
	start = NULL;
}

t_room	*pathcpy(t_room *path)
{
	t_room	*cpy;
	t_room	*start;
	t_room	*src;

	src = path;
	if (!(cpy = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	start = cpy;
	while (src)
	{
		cpy->name = ft_strdup(src->name);
		cpy->com = ft_strdup(src->com);
		cpy->x = src->x;
		cpy->y = src->y;
		cpy->i = 0;
		cpy->links = NULL;
		cpy->next = NULL;
		cpy->prev = NULL;
		src = src->next;
		if (src)
			if (!(cpy->next = (t_room*)malloc(sizeof(t_room))))
				return (NULL);
		cpy = cpy->next;
	}
	return (start);
}

int		calc_path_lenght(t_room *path)
{
	int		i;

	i = 0;
	while (path)
	{
		path = path->next;
		i++;
	}
	return (i);
}

int		find_room_in_path(t_room *room, t_room *pathstart)
{
	t_room	*path;

	path = pathstart;
	while (path)
	{
		if (!ft_strcmp(room->name, path->name))
			return (1);
		path = path->next;
	}
	return (0);
}
