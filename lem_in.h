/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem-in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: srepelli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/19 14:35:58 by srepelli     #+#   ##    ##    #+#       */
/*   Updated: 2018/08/29 17:54:58 by srepelli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft/libft.h"

typedef struct		s_room
{
	int				ant;
	char			*name;
	char			*com;
	int				x;
	int				y;
	struct s_room	*prev;
	struct s_room	*next;
	struct s_room	**links;
	int				i;
}					t_room;

typedef struct		s_tube
{
	t_room			*link1;
	t_room			*link2;
	char			*com;
	struct s_tube	*next;
}					t_tube;

typedef struct		s_map
{
	char			*initcom;
	char			*finalcom;
	int				fourmtotal;
	t_room			*start;
	t_room			*end;
	t_room			*sort;
	t_room			*shortest;
	int				shortlen;
	t_tube			*tube;
}					t_map;

typedef struct		s_ant
{
	t_room			*current;
	struct s_ant	*next;
	int				num;
}					t_ant;

int					lem_in(t_map *map);
void				t_roomadd(t_room **alst, t_room *nw);
void				t_tubeadd(t_tube **alst, t_tube *nw);
void				t_room_push_front(t_room **begin_list, t_room *start);
void				t_tube_push_back(t_tube **begin_list, t_tube *end);
void				t_room_push_back(t_room **begin_list, t_room *end);
t_tube				*fill_t_tube(char *str, t_map *map, char *com);
t_room				*sort_rooms(t_map *map);
void				display_result(t_map *map, t_ant *ants);
void				free_all(t_map *map, t_ant *ants);
void				fill_tube_links(t_tube *tubes, t_room *rooms, t_map *map);
void				read_stde_map(t_map *map, char *line);
void				read_stde_tubes(t_map *map, char *line);
int					is_tube(char *line, t_room *start);
void				free_t_room(t_room **room);
int					find_room_in_path(t_room *room, t_room *pathstart);
t_room				*t_roomcpy(t_room *src);
int					calc_path_lenght(t_room *path);
t_room				*pathcpy(t_room *src);
void				calc_shortest_path(t_map *map);
void				aff_error(t_map *map);
int					check_error(t_map *map, char *line);
t_room				*which_room(t_map *map, char *name);
t_room				*fill_t_room(char *line, int ant, char *com);
char				*ft_strjoin_nl(char const *s1, char const *s2);
void				get_com(char **com, char **line);
int					find_endofmap(char *line, t_map *map);
int					manage_com(char **com, t_map *map, char **line, int k);
void				end_of_rooms(t_map *map, char *line, char *com);

#endif
