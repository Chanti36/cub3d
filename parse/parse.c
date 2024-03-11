
#include "../cub.h"

static void	check_name(char *file)
{
	char	*aux;

	aux = file + (ft_strlen(file) - 4);
	if (ft_strncmp(aux, ".cub", 4) != 0)
	{
		printf("Invalid file\n");
		exit(1);
	}
}

static void	free_list(t_gnl *list)
{
	t_gnl	*i;

	while (list)
	{
		i = list->next;
		free(list->content);
		free(list);
		list = i;
	}
}

void	parse(char *file, t_game *game)
{
	t_gnl	*data;

	check_name(file);
	data = get_file(file);
	check_data(data, game);
	check_map(data, game);
	free_list(data);
}
