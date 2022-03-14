#include "cub3d.h"

void move(int movX, int movY, t_game *game)
{
	char		**map;
	t_player	*player;

	player = game->player;
	map = game->map;
	if(map[(int) player->posY + movY][(int) player->posX + movX] != '1')
	{
		map[(int) player->posY][(int) player->posX] = '0';
		map[(int) player->posY + movY][(int) player->posX + movX] = 'N';
		game->player->posY = (int) player->posY + movY;
		game->player->posX = (int) player->posX + movX;
	}
	ft_print_map(game->map);
}

int	key_hook(int keycode, t_game *game)
{
    (void) game;
    int	x;
    int	y;

	x = 0;
	y = 0;
	if(keycode == A_KEY)
		x--;
	if(keycode == W_KEY)
		y--;
	if(keycode == S_KEY)
		y++;
	if(keycode == D_KEY)
		x++;
	move(x, y, game);
	//vars->cntmoves += move(keycode, vars);
	return (0);
}