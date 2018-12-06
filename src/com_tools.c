/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_stde.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/24 13:39:13 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 17:54:29 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../lem_in.h"

char	*ft_strjoin_nl(char const *s1, char const *s2)
{
	char	*d;
	int		i;

	i = 0;
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	d = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!d)
		return (NULL);
	ft_strcpy(d, s1);
	ft_strcat(d, "\n");
	ft_strcat(d, s2);
	return (d);
}

int		start_or_end(char **com, t_map *map, char **line)
{
	int		k;

	k = -1;
	if (!ft_strcmp(*line, "##start"))
	{
		while (k == -1)
		{
			get_com(com, line);
			k = find_endofmap(*line, map);
		}
		return (1);
	}
	else if (!ft_strcmp(*line, "##end"))
	{
		while (k == -1)
		{
			get_com(com, line);
			k = find_endofmap(*line, map);
		}
		return (2);
	}
	return (k);
}

int		manage_com(char **com, t_map *map, char **line, int k)
{
	while (k == -1)
	{
		if (!ft_strcmp(*line, "##start") || !ft_strcmp(*line, "##end"))
			return (start_or_end(com, map, line));
		else
		{
			get_com(com, line);
			k = find_endofmap(*line, map);
		}
	}
	return (k);
}

void	end_of_rooms(t_map *map, char *line, char *com)
{
	t_room_push_back(&map->start, map->end);
	if (!is_tube(line, map->start))
	{
		ft_strdel(&line);
		aff_error(map);
	}
	if (is_tube(line, map->start))
		t_tube_push_back(&map->tube, fill_t_tube(line, map, com));
	ft_strdel(&com);
	ft_strdel(&line);
	if (!map->end)
		aff_error(map);
}

void	get_com(char **com, char **line)
{
	char *tmp;

	tmp = NULL;
	tmp = ft_strdup(*com);
	ft_strdel(com);
	*com = ft_strjoin_nl(tmp, *line);
	ft_strdel(&tmp);
	ft_strdel(line);
	get_next_line(0, line);
}
