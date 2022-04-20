#include "../headers/cub3d.h"

t_mini_tile	*ft_new_tile(void)
{
	t_mini_tile	*new;

	new = malloc(sizeof(t_mini_tile));
	new->x = 0;
	new->y = 0;
	new->type = '0';
	new->next = NULL;
	return (new);
}

void	init_prev(t_mini_tile *tiles)
{
	t_mini_tile	*head;
	t_mini_tile	*previous;

	head = tiles;
	previous = NULL;
	while (head)
	{
		head->prev = previous;
		previous = head;
		head = head->next;
	}
}

static t_mini_tile	*ft_lstlast_tile(t_mini_tile *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_tile(t_mini_tile **alst, t_mini_tile *new)
{
	t_mini_tile	*last;

	if (*alst)
	{
		last = ft_lstlast_tile(*alst);
		last->next = new;
	}
	else
		*alst = new;
}

void	load_square(t_mini_tile *head, t_image *buffer, t_game *game)
{
	size_t		i;
	size_t		j;
	int			x;
	int			y;

	i = 0;
	x = (64 - (head->x * 16)) / 16;
	y = (64 - (head->y * 16)) / 16;
	while (i < game->config->caseHeight - 1)
	{
		j = 0;
		while (j < game->config->caseWidth - 1)
		{
			my_mlx_pixel_put(buffer, j + (16 * x), i + (16 * y), head->color);
			j++;
		}
		i++;
	}
}

int in_circle(float x, float y, t_player *player)
{
	float	distance;
	float	radius = 4.0;

	distance = sqrtf(powf(x - player->posX, 2.) + powf(y - player->posY, 2.));
	if (distance <= radius)
	{
		if ((radius - distance) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

void	ft_get_square(t_mini_tile **head, int x, int y, char type)
{
	t_mini_tile	*new;

	new = ft_new_tile();
	new->x = x;
	new->y = y;
	new->type = type;
	if (type == '1')
		new->color = 0x000000ff;
	else if (type == '0')
		new->color = 0x0000ff00;
	else if (type == 'N')
		new->color = 0x00ff0000;
	ft_lstadd_back_tile(head, new);
}

void	render_minimap(t_game *game, char **map, t_image *mm)
{
	int	x;
	int	y;

	game->minimap->tiles = ft_new_tile();
	y = 0;
	while (map[y])
	{
		x = 0;
		game->minimap->x = 0;
		while (map[y][x])
		{
			if (in_circle(x, y, game->player))
				ft_get_square(&game->minimap->tiles, x - game->player->posX, y - game->player->posY, map[y][x]);
			x++;
		}
		y++;
	}
	init_prev(game->minimap->tiles);
	t_mini_tile *head = game->minimap->tiles->next;
	while (head)
	{
		load_square(head, game->minimap->img, game);
		head = head->next;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->minimap->img->img, 20, 20);
	head = game->minimap->tiles;
	t_mini_tile *temp;
	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}
