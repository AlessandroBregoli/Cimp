#include "Img.h"
#include "Img/io.cpp"
#include "Img/puntuali.cpp"
#include "Img/globali.cpp"
#include "Img/locali.cpp"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
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
Img::Img(string path){
	SDL_Surface* s = IMG_Load(path.c_str());
	if(s == NULL){
		printf("non riesco \n");
		return;
	}
	this->h = s->h;
	this->w = s->w;
	this->path = path;
	this->cn = s->format->BytesPerPixel;
	this->img = new unsigned char[this->h * this->w * this->cn];
	//printf("maschere: %d, %d, %d\n", s->format->Rmask, s->format->Gmask, s->format->Bmask);
	if(s->format->palette == NULL){
		for (unsigned int i = 0; i < this->h; i += 1)
		{
			for (unsigned int j = 0; j < this->w; j += 1)
			{
				for (unsigned int k = 0; k < this->cn; k +=1)
				{
					unsigned char* pixel_addr = (unsigned char*)s->pixels + i * s->pitch + j * this->cn + k;
					*((*this)(i,j,k)) = *pixel_addr;
				}
			}
		}
	} else {
		printf("Che schifo le palette");
		return;
	}
}

void Img::salvaBMP(string path){
	SDL_Surface* s = SDL_CreateRGBSurface(0, this->w, this->h, this->cn*8, 0xff,0xff00,0xff0000, this->cn>3?0xff000000:0);
	int numeroC = this->cn;
	for (unsigned int i = 0; i < this->h; i += 1)
	{
		for (unsigned int j = 0; j < this->w; j += 1)
		{
			for (unsigned int k = 0; k < numeroC; k +=1)
			{
				*((unsigned char*)s->pixels + i * s->pitch + j * this->cn + k) = *((*this)(i,j,k));
			}
		}
	}
	SDL_SaveBMP(s, path.c_str());
}
