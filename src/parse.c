/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/29 18:19:49 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 11:25:45 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

void	aff_error(t_map *map)
{
	free_all(map, NULL);
	write(2, "ERROR\n", 6);
	exit(1);
}

int		check_error(t_map *map, char *line)
{
	t_room	*room;
	t_room	*tmp;
	int		i;

	i = 0;
	if (!map->start)
		return (0);
	tmp = map->start;
	room = fill_t_room(line, 0, NULL);
	while (tmp)
	{
		if ((room->x == tmp->x && room->y == tmp->y)
				|| !ft_strcmp(room->name, tmp->name))
			i = 1;
		tmp = tmp->next;
	}
	if (map->end && !ft_strcmp(room->name, map->end->name))
		i = 1;
	free_t_room(&room);
	return (i);
}

t_map	*fill_t_map(void)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (NULL);
	map->initcom = NULL;
	map->finalcom = NULL;
	map->fourmtotal = 0;
	map->start = NULL;
	map->end = NULL;
	map->tube = NULL;
	map->sort = NULL;
	map->shortest = NULL;
	map->shortlen = 0;
	return (map);
}

void	parse(t_map *map, char *line)
{
	char	*com;

	com = NULL;
	if (get_next_line(0, &line) >= 0)
	{
		if (ft_isnum(line) && ft_atoi(line))
			map->fourmtotal = ft_atoi(line);
		else if (line[0] == '#')
		{
			while (line && line[0] == '#')
				get_com(&com, &line);
			if (ft_isnum(line) && ft_atoi(line))
			{
				map->initcom = ft_strdup(com);
				ft_strdel(&com);
				map->fourmtotal = ft_atoi(line);
			}
		}
		else
		{
			ft_strdel(&line);
			aff_error(map);
		}
		ft_strdel(&line);
	}
}

int		main(void)
{
	t_map	*map;
	char	*line;

	line = NULL;
	map = fill_t_map();
	parse(map, line);
	read_stde_map(map, line);
	read_stde_tubes(map, line);
	lem_in(map);
	return (0);
}
