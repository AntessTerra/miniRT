#include "Minilibx.hpp"

Minilibx::Minilibx(){
	std::cout << "Calling a Minilibx Constructor" << std::endl;
	_mlx = mlx_init();
	_win = mlx_new_window(_mlx, SCREENWIDTH, SCREENHEIGHT, const_cast<char*>("cub3d"));
	_images.push_back(new Image(*this, SCREENWIDTH, SCREENHEIGHT));
	_images.push_back(new Image(*this, "textures/isaac.png"));
	_images.push_back(new Image(*this, "textures/emptyscreen.png"));
}

Minilibx::~Minilibx(){
	std::cout << "Calling a Minilibx Destruuctor" << std::endl;
	for (std::vector<Image*>::iterator it = _images.begin(); it != _images.end(); it++)
		delete (*it);
	mlx_destroy_window(_mlx, _win);
	mlx_destroy_display(_mlx);
}

Image&	Minilibx::getTexture(std::string name){
	for (std::vector<Image*>::iterator it = _images.begin(); it != _images.end(); it++)
		if ((*it)->getName() == name)
			return *(*it);
	return *(*_images.begin());
}

void	Minilibx::my_mlx_put_image_to_window(Image& image, int x, int y){
	mlx_put_image_to_window(_mlx, _win, image.getImg(), x, y);
}


