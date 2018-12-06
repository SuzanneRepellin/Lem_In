/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_stde.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 13:39:13 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 17:45:46 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

int		is_valid_room(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (0);
	while (line[0] != 'L' && line[i] && line[i] != ' ')
		i++;
	if (i == 0 || line[i] != ' ')
		return (0);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != ' ')
		return (0);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int		find_endofmap(char *line, t_map *map)
{
	static int	s;
	static int	e;

	if ((s && !ft_strcmp(line, "##start")) || (e && !ft_strcmp(line, "##end")))
	{
		ft_strdel(&line);
		aff_error(map);
	}
	if (!ft_strcmp(line, "##start"))
	{
		s++;
		return (-1);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		e++;
		return (-1);
	}
	else if (line[0] == '#')
		return (-1);
	else if (is_valid_room(line))
		return (3);
	return (0);
}

t_room	*fill_t_room(char *data, int fourm, char *com)
{
	t_room	*room;
	char	**tab;

	if (!(tab = ft_strsplit(data, ' ')))
		return (NULL);
	if (!(room = (t_room*)malloc(sizeof(t_room))))
		return (NULL);
	room->com = ft_strdup(com);
	room->ant = fourm;
	room->i = 0;
	room->name = ft_strdup(tab[0]);
	room->x = ft_atoi(tab[1]);
	room->y = ft_atoi(tab[2]);
	room->next = NULL;
	room->prev = NULL;
	room->links = NULL;
	ft_free_word_table(tab);
	return (room);
}

void	fill_rooms(t_map *map, char *line, int j, char *com)
{
	if (j == 3 && !check_error(map, line))
		t_room_push_back(&map->start, fill_t_room(line, 0, com));
	if (j == 1)
	{
		if (is_valid_room(line) && !check_error(map, line))
			t_room_push_front(&map->start,
				fill_t_room(line, map->fourmtotal, com));
		else
			aff_error(map);
	}
	if (j == 2)
	{
		if (is_valid_room(line) && !map->end && !check_error(map, line))
			map->end = fill_t_room(line, 0, com);
		else
			aff_error(map);
	}
	ft_strdel(&line);
}

void	read_stde_map(t_map *map, char *line)
{
	int		k;
	char	*com;

	com = NULL;
	while (get_next_line(0, &line) > 0)
	{
		ft_strdel(&com);
		if ((k = find_endofmap(line, map)))
		{
			if (k != 3)
				k = manage_com(&com, map, &line, k);
			if (k && !check_error(map, line))
				fill_rooms(map, line, k, com);
			else if (k)
				break ;
		}
		if (!k)
		{
			end_of_rooms(map, line, com);
			return ;
		}
	}
	ft_strdel(&com);
	aff_error(map);
}
