#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "libft/libft.h"

# define BUFFER_SIZE 42
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720

enum
{
	KEY_A		= 0,
	KEY_S		= 1,
	KEY_D		= 2,
	KEY_W		= 13,
	KEY_ESCAPE	= 53,
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126
};

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

typedef struct s_gnl
{
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

typedef struct s_color
{
	int	R;
	int	G;
	int	B;
}	t_color;

//_____________________________________________________________

typedef struct s_player
{
	float	x;
	float	y;
	float	a;
	float	v_a;
	int		mouse_x;
	int		mouse_y;
	float	speed;
	float	v_speed;
	float	max_speed;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*image;


	char		*n_texture;
	char		*s_texture;
	char		*e_texture;
	char		*w_texture;

	t_color		floor_color;
	t_color		celing_color;

	int			max_x;
	int			max_y;
	char		**map;

	t_player	player;
}	t_game;

void	exit_game(t_game *game);

//Parse
void	parse(char *file, t_game *game);
t_gnl	*get_file(char *file);
void	free_strs(char **strs);

void	check_data(t_gnl *str_map, t_game *game);
void	check_map(t_gnl *str_map, t_game *game);
void	check_map_walls(t_game *game);

//Input
int		key_hook(int keycode, t_game *game);
int		mouse_hook(int x, int y, t_game *game);
int		close_win(t_game *game);

//Render
int		render(t_game *game);
void	render_raycast(t_game *game);

//Render Math
t_vec2	find_vector(t_game *game, int player_a);
float	lerp(float a, float b, float f);

//gnl
char	*get_next_line(int fd);
int		ft_find_line(char *buff);
char	*gnl_strjoin(char *s1, char const *s2);

#endif