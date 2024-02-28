#ifndef __IMAGE_HPP__
# define __IMAGE_HPP__

# include "Minilibx.hpp"

class Minilibx;

class Image
{
protected:
	void*			_img;
	int				_height;
	int				_width;
	std::string		_name;
	const Minilibx*	_mini;
public:
	Image(const Minilibx& mini, int width, int height);
	Image(const Minilibx& mini, std::string path);
	Image(const Image&);
	Image& operator = (const Image&);
	~Image();

	void*			getImg() const {return _img;};
	int				getHeight() const {return _height;};
	int				getWidth() const {return _width;};
	const Minilibx*	getMlx() const {return _mini;};
	std::string		getName() const {return _name;};
};

#endif
