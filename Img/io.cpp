
int Img::caricaIMG(){
	FILE* f = fopen(this->path.c_str(), "rb");
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
	delete(buff);
	fclose(f);
	return 0;
}


int Img::salvaIMG(){
	FILE* f = fopen(this->path.c_str(), "wb");
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
	delete(buff);
	fclose(f);
	return 0;
}
