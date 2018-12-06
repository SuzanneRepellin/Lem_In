/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_stde.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 13:39:13 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 14:06:33 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

t_room	*which_room(t_map *map, char *name)
{
	t_room	*tmp;

	tmp = map->start;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_tube	*fill_t_tube(char *str, t_map *map, char *com)
{
	char	**tube;
	t_tube	*link;

	if (!(link = (t_tube*)malloc(sizeof(t_tube))))
		return (NULL);
	if (!(tube = ft_strsplit(str, '-')))
	{
		free(link);
		return (NULL);
	}
	link->com = ft_strdup(com);
	link->link1 = tube[0] ? which_room(map, tube[0]) : NULL;
	link->link2 = tube[1] ? which_room(map, tube[1]) : NULL;
	link->next = NULL;
	ft_free_word_table(tube);
	return (link);
}

int		check_tube_links(char **tube, t_room *tmp, int j)
{
	int		k;

	k = 0;
	while (tmp)
	{
		if (j == 1 || !ft_strcmp(tube[0], tmp->name))
		{
			j = 1;
			if (k == 1 || !ft_strcmp(tube[1], tmp->name))
			{
				ft_free_word_table(tube);
				return (1);
			}
			tmp = tmp->next;
		}
		else if (!ft_strcmp(tube[1], tmp->name))
		{
			k = 1;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int		is_tube(char *line, t_room *room)
{
	char	**tube;
	t_room	*tmp;

	tmp = room;
	if (!(tube = ft_strsplit(line, '-')))
		return (0);
	if (!tube || tube[2] || !tube[0] || !tube[1] ||
			!ft_strcmp(tube[0], tube[1]))
	{
		ft_free_word_table(tube);
		return (0);
	}
	if (check_tube_links(tube, tmp, 0))
		return (1);
	ft_free_word_table(tube);
	return (0);
}

void	read_stde_tubes(t_map *map, char *line)
{
	char	*com;

	com = NULL;
	while (get_next_line(0, &line) > 0)
	{
		while (line && line[0] == '#')
			get_com(&com, &line);
		if (line && is_tube(line, map->start))
		{
			t_tube_push_back(&map->tube, fill_t_tube(line, map, com));
			ft_strdel(&line);
		}
		else
		{
			ft_strdel(&line);
			map->finalcom = ft_strdup(com);
			break ;
		}
		ft_strdel(&com);
	}
	ft_strdel(&com);
	if (!map->start || !map->end || !map->tube)
		aff_error(map);
}
