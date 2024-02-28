#include "Image.hpp"

Image::Image(const Minilibx& mini, int width, int height){
	std::cout << "Calling a Image Constructor" << std::endl;
	_mini = &mini;
	_img = mlx_new_image(_mini->getMlx(), width, height);
	_width = width;
	_height = height;
	_name = "main";
}

Image::Image(const Minilibx& mini, std::string path){
	std::cout << "Calling a Textured Image Constructor" << std::endl;
	_mini = &mini;
	_img = mlx_png_file_to_image(_mini->getMlx(), const_cast<char*>(path.c_str()), &_width, &_height);
	_name = path.substr(path.find_last_of("/", path.length()) + 1, path.length() - path.find_last_of("/", path.length()) - 5);
	// std::cout << _name << std::endl;
}

Image::Image(const Image& image){
	std::cout << "Copying a image!!" << std::endl;
	this->_img = image.getImg();
	this->_mini = image.getMlx();
	this->_name = image.getName();
	this->_width = image.getWidth();
	this->_height = image.getHeight();
	return ;
}

Image&	Image::operator = (const Image& image){
	std::cout << "Copy & assign a image!!" << std::endl;
	if (this != &image){

	}
	return *this;
}

Image::~Image(){
	std::cout << "Calling a Image Destructor" << std::endl;
	mlx_destroy_image(_mini->getMlx(), _img);
	// mlx_destroy_image(_mini->getMlx(), _img);
}

