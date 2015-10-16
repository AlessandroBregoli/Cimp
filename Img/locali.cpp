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
