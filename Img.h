#ifndef CIAO
#include <iostream>
#define CIAO 1
using namespace std;
class Img{
	private:
	int h; //altezza
	int w; //larghezza
	int cn; //canali
	unsigned char* img;
	public:
	string path;
	int caricaIMG();	
	int salvaIMG();
	Img(int h, int w, string path, int cn);
	~Img();
	unsigned char* operator()(int y, int x, int cn1);
	Img* applicaMatrice(int* mtx,int h, int w, int divisore);
	Img* scalaGrigi();
	Img* stretch();
	Img* equalizza();
	Img* greyWorld();
};
#endif
