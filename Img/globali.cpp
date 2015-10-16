
Img* Img::stretch(){
		Img* img = new Img(this->h,this->w,"",this->cn);
		for(int k = 0; k < this->cn; k++){
			int max = 0;
			int min = 255;
			//cerco il massimo e il minimo del canale
			for(int i = 0; i < this->h; i++){
				for(int j = 0; j < this->w; j++){
					if(*(*this)(i,j,k)>max){
						max = *(*this)(i,j,k);
					}
					if(*(*this)(i,j,k)<min){
						min = *(*this)(i,j,k);
					}
				}
			}
			//spalmo i valori del canale tra 0 e 255
			for(int i = 0; i < this->h; i++){
				for(int j = 0; j < this->w; j++){
					unsigned int tmp = *(*this)(i,j,k);
					tmp = (tmp - min) * 255/(max-min);
					*(*img)(i,j,k) = tmp;
				}
			}
		}
		return img;
}


Img* Img::equalizza(){
		Img* img = new Img(this->h,this->w,"",this->cn);
		for(int k = 0; k < this->cn; k++){
			int istogramma[256];
			for(int i = 0; i<256; i++){
				istogramma[i] = 0;
			}
			//creo l'istogramma
			for(int i = 0; i < this->h; i++){
				for(int j = 0; j < this->w; j++){
					istogramma[*(*this)(i,j,k)]++;
				}
			}
			//calcolo l'istogramma cumulato
			for(int i = 1; i < 256; i++){
				istogramma[i] = istogramma[i-1] + istogramma[i];
			}
			for(int i = 0; i<256;i++){
				istogramma[i] = istogramma[i]*255/istogramma[255];
			}
			//rimappo l'immagine con i nuovi colori
			for(int i = 0; i < this->h; i++){
				for(int j = 0; j < this->w; j++){
					*(*img)(i,j,k) = istogramma[*(*this)(i,j,k)];
				}
			}

		}
		return img;
}
