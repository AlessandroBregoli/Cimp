#include "Img.h"
#include "Img/io.cpp"
#include "Img/puntuali.cpp"
#include "Img/globali.cpp"
#include "Img/locali.cpp"
#include <stdio.h>
Img::Img(int h, int w, string path, int cn){
	this->h = h;
	this->w = w;
	this->path = path;
	this->cn = cn;
	this->img = new unsigned char[this->h * this->w * this->cn];
}
Img::~Img(){
	delete(this->img);
}
unsigned char* Img::operator()(int y, int x, int cn1){
		return &this->img[y*this->w*this->cn + x * this->cn + cn1];
	}










