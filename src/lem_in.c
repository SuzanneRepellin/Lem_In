/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 14:33:42 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/30 11:25:31 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

void	create_ant_list(t_ant *ants, int nb, t_room *start)
{
	t_ant	*tmp;
	int		i;

	tmp = ants;
	i = 1;
	while (nb)
	{
		tmp->current = start;
		tmp->num = i;
		if (nb > 1)
		{
			tmp->next = (t_ant*)malloc(sizeof(t_ant));
			tmp = tmp->next;
		}
		else
			tmp->next = NULL;
		nb--;
		i++;
	}
}

void	free_t_tube(t_tube *tubes)
{
	t_tube	*tmp;

	while (tubes)
	{
		tmp = tubes->next;
		ft_strdel(&tubes->com);
		free(tubes);
		tubes = tmp;
	}
	tubes = NULL;
}

void	free_all(t_map *map, t_ant *ants)
{
	t_ant	*tmp;

	if (map)
	{
		ft_strdel(&(map->initcom));
		ft_strdel(&(map->finalcom));
		free_t_room(&(map->start));
		if (map->end && map->end->com && ft_strstr(map->end->com, "##end"))
			free_t_room(&(map->end));
		free_t_room(&(map->shortest));
		free_t_tube(map->tube);
		free(map);
		map = NULL;
	}
	while (ants)
	{
		tmp = ants->next;
		free(ants);
		ants = NULL;
		ants = tmp;
	}
}

int		lem_in(t_map *map)
{
	t_ant	*ants;

	map->sort = sort_rooms(map);
	calc_shortest_path(map);
	if (!(ants = (t_ant*)malloc(sizeof(t_ant))))
		return (0);
	ants->current = map->shortest;
	ants->next = NULL;
	create_ant_list(ants, map->fourmtotal, map->shortest);
	if (!map->shortlen)
	{
		free_all(map, ants);
		write(2, "ERROR\n", 6);
		return (-1);
	}
	display_result(map, ants);
	free_all(map, ants);
	return (0);
}
