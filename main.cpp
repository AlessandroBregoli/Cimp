#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define RGB 3

#include "Img.cpp"
int main(int argc, char* argv[]){
	if(argc < 4){
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
	Img* img = i.scalaGrigi()->applicaMatrice(m,3,3,1);
	img->path="out.data";
	img->salvaIMG();
	delete(img);	
	return 0;
}
