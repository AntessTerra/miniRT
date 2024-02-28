#include "Minilibx.hpp"

int	key_hook(int key, void* data)
{
	Minilibx* mini = reinterpret_cast<Minilibx*>(data);
	if(key == 41)
		mlx_loop_end(mini->getMlx());
	return 0;
}

int	main(void)
{
	Minilibx mini;

	mini.my_mlx_put_image_to_window(mini.getTexture("main"), 0, 0);
	mini.my_mlx_put_image_to_window(mini.getTexture("emptyscreen"), 0, 0);
	mini.my_mlx_put_image_to_window(mini.getTexture("isaac"), 0, 0);
	mlx_on_event(mini.getMlx(), mini.getWin(), MLX_KEYDOWN, key_hook, reinterpret_cast<void*>(&mini));

	mlx_loop(mini.getMlx());
	// mlx_destroy_image(mini.getMlx(), mini.getMain().getImg());
	// mlx_destroy_image(mini.getMlx(), mini.getTexture("isaac").getImg());
	// mlx_destroy_image(mini.getMlx(), mini.getTexture("emptyscreen").getImg());
	// mlx_destroy_window(mini.getMlx(), mini.getWin());
	// mlx_destroy_display(mini.getMlx());
	return (0);
}
