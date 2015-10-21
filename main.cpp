//g++ -g main.cpp -lSDL -lSDL_image -I/usr/include/SDL
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define RGB 3

#include "Img.cpp"
int main(int argc, char* argv[]){
	/*if(argc < 4){
		printf("Serve il nome del file seguito da altezza e larghezza\n");
		return -1; 
	}
	int h = 0;
	int w = 0;
	sscanf(argv[2], "%d", &h);
	sscanf(argv[3], "%d", &w);
	if(h <= 0| w <= 0){
		printf("ma sei serio???\n");
		return -2;
	}
	Img i(h,w, argv[1], 3);
	int tmp = i.caricaIMG();
	if(tmp < 0){
		return tmp;
	}
	int m[] = {0,-1,0,-1,5,-1,0,-1,0};
	int m1[] = {1,2,1,2,4,2,1,2,1};
	int m2[] = {0,2,0};
	Img* img = i.equalizza();
	img->path="out.data";
	img->salvaIMG();
	delete(img);	
	return 0;*/
	if (argc < 2)
	{
		printf("metti nome file");
		return -1;
	}
	Img i(argv[1]);
	int m1[] = {1,2,1,2,4,2,1,2,1};
	int m[] = {0,-1,0,-1,5,-1,0,-1,0};
	Img* corretta = i.mediana(3,3);
	corretta->salvaBMP("io.bmp");
	corretta->path = "io.data";
	corretta->salvaIMG();
}

