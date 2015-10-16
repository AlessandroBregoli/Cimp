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

