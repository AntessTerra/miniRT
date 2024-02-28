#ifndef __MINILIBX_HPP__
# define __MINILIBX_HPP__

# include <iostream>
# include <algorithm>
# include <vector>
# include <list>
# include <numeric>
# include "Image.hpp"
# include "MacroLibX/includes/mlx.h"

# define SCREENWIDTH 1280
# define SCREENHEIGHT 720

class Image;

class Minilibx
{
private:
	void*				_mlx;
	void*				_win;
	std::vector<Image*>	_images;
public:
	Minilibx();
	~Minilibx();

	void	my_mlx_put_image_to_window(Image& image, int x, int y);
	void*	getMlx() const {return _mlx;};
	void*	getWin() const {return _win;};
	Image&	getTexture(std::string name);
};

template <typename T>
typename T::value_type easyfind(T& li, typename T::value_type val){
	typename T::iterator found = std::find(li.begin(), li.end(), val);
	return (found != li.end())? *found : throw std::exception();
}

template <typename T>
void print(T& li){
	for (typename T::iterator it = li.begin(); it != li.end(); it++)
			std::cout << *it << std::endl;
}


#endif

