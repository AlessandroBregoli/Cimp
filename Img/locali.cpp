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
						yi = yi <0 ? 0 : yi >= this->h? this->h -1 : yi;
						xi = xi <0 ? 0 : xi >= this->w? this->w -1 : xi;
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

int compare(const void *a, const void *b){
	unsigned char a1 = *(unsigned char*)a;
	unsigned char b1 = *(unsigned char*)b;
	return a1<b1?-1:(a1==b1 ? 0 : 1);
}
Img* Img::mediana(int h, int w){
	if(h*w%2!=1){
		printf("la voglio dispari");
		return NULL;
	}
	unsigned char bordo[h*w];
	Img* img = new Img(this->h,this->w,"",this->cn);
	for (unsigned int i = 0; i < this->h; i += 1)
	{
		for (unsigned int j = 0; j < this->w; j += 1)
		{
			for (unsigned int k = 0; k < this->cn; k += 1)
			{
				int ind = 0;
				for(int y = 0; y < h; y++){
					for(int x = 0; x < w; x ++){
						int yi = i - (h/2-y);
						int xi = j - (w/2-x);
						yi = yi <0 ? 0 : yi >= this->h? this->h -1 : yi;
						xi = xi <0 ? 0 : xi >= this->w? this->w -1 : xi;
						bordo[ind] = *(*this)(yi,xi,k);
						ind ++;
					}
				}
				qsort(bordo, h*w, sizeof(char), &compare);
				/*for (unsigned int z = 0; z < h*w; z += 1)
				{
					printf("%d,",bordo[z]);
				}
				printf("\n");*/
				*(*img)(i,j,k) = bordo[h*w/2];
			}
		}
	}
	return img;
}
