#include "Img.h"
Img::Img(int h, int w, char* path, int cn){
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

int Img::caricaIMG(){
	FILE* f = fopen(this->path, "rb");
	if(f == NULL){
		printf("L'immagine non può essere aperta: errore %d\n", errno);
		return -3;
	}
	int i,j,k = 0;
	char *buff = new char[this->cn*this->w];
	for(i = 0; i<this->h;i++){
		size_t letti = fread(buff, sizeof(char), this->w * this->cn, f);
		if(letti < this->w * this->cn){
			printf("Mi hai mentito non e' questa la dimensione\n");
			return -4;
		}
		for(j = 0; j<this->w; j++){
			for(k = 0; k<this->cn; k++){
				*((*this)(i,j,k)) = buff[this->cn * j + k];
			}
		}
	}
	free(buff);
	fclose(f);
	return 0;
}


int Img::salvaIMG(){
	FILE* f = fopen(this->path, "wb");
	if(f == NULL){
		printf("L'immagine non può essere aperta: errore %d\n", errno);
		return -3;
	}
	int i,j,k = 0;
	char *buff = new char[this->cn*this->w];
	for(i = 0; i<this->h;i++){		
		for(j = 0; j<this->w; j++){
			for(k = 0; k<this->cn; k++){
				buff[this->cn * j + k] = *((*this)(i,j,k));
			}			
		}
		size_t scritti = fwrite(buff, sizeof(char), this->w * this->cn, f);
		if(scritti < this->w*this->cn){
			printf("Errore nella scrittura dell'immagine\n");
			return -4;
		}
	}
	free(buff);
	fclose(f);
	return 0;
}

Img* Img::scalaGrigi(){
	Img* img = new Img(this->h,this->w,"",this->cn);
	for(int i = 0; i<this->h;i++){		
		for(int j = 0; j<this->w; j++){
			unsigned int tmp = 0;
			for(int k = 0; k<this->cn; k++){
				tmp += *(*this)(i,j,k);
			}
			tmp = tmp / this->cn;
			
			for(int k = 0; k<this->cn; k++){
				*(*img)(i,j,k)= tmp;
			}
		}
	}
	return img;
}

Img* Img::applicaMatrice(int* mtx,int h, int w, int divisore){
	if((h*w)%2 == 0){
		printf("mamama questa matrice non ha un centro :'(\n");
		return NULL;
	}
	Img* img = new Img(this->h,this->w,"",this->cn);
	for(int i = 0; i < this->h; i++){
		for(int j = 0; j < this->w; j++){
			for(int k = 0; k < this->cn; k++){
				int tmp = 0;
				for(int y = 0; y < h; y++){
					for(int x = 0; x < w; x ++){
						int yi = i - (h/2-y);
						int xi = j - (w/2-x);
						yi = yi <0 ? 0 : y >= this->h? this->h -1 : yi;
						xi = xi <0 ? 0 : x >= this->w? this->w -1 : xi;
						tmp += *(*this)(yi,xi,k) * mtx[y*w+x];
					}
				}
				tmp = tmp/divisore;
				*(*img)(i,j,k) = tmp<0?0:tmp>255?255:tmp;
			}
		}
	}
	return img;
}
