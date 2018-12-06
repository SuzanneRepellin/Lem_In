/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/08/18 17:50:36 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 18:11:36 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

void	display_ants_moves(t_ant *ants, t_ant *start, int j)
{
	int		i;

	i = 1;
	while (ants)
	{
		j = j + 1 - i;
		ants = start;
		while (j < i && ants)
		{
			if (ants->current)
				ants->current = ants->current->next;
			if (ants->current)
				ft_printf("L%d-%s ", ants->num, ants->current->name);
			ants = ants->next;
			j++;
		}
		ants = start;
		while (ants && !ants->current)
			ants = ants->next;
		if (ants)
			ft_printf("\n");
		i++;
	}
}

void	aff_ants(t_map *map)
{
	if (map->initcom)
		ft_printf("%s\n", map->initcom);
	ft_printf("%d\n", map->fourmtotal);
	ft_strdel(&(map->initcom));
}

void	aff_finalcom(t_map *map)
{
	if (map->finalcom)
		ft_printf("%s\n", map->finalcom);
	ft_printf("\n");
	ft_strdel(&(map->finalcom));
}

void	display_result(t_map *map, t_ant *ants)
{
	t_tube	*tube;
	t_room	*room;
	t_ant	*start;

	tube = map->tube;
	room = map->sort;
	start = ants;
	aff_ants(map);
	while (room)
	{
		if (room->com)
			ft_printf("%s\n", room->com);
		ft_printf("%s %d %d\n", room->name, room->x, room->y);
		room = room->next;
	}
	while (tube)
	{
		if (tube->com)
			ft_printf("%s\n", tube->com);
		ft_printf("%s-%s\n", tube->link1->name, tube->link2->name);
		tube = tube->next;
	}
	aff_finalcom(map);
	display_ants_moves(ants, start, 0);
}
