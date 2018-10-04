class Peice{
	protected:
	int pos;
	int side;
	void nc(vector<int>&);
	void sc(vector<int>&);
	void ec(vector<int>&);
	void wc(vector<int>&);
	void ne(vector<int>&);
	void sw(vector<int>&);
	void nw(vector<int>&);
	void se(vector<int>&);
	
	public:
	virtual void moves(vector<int>&)=0;
	void move(int);
	void init(int, int);
	int loc();
};


void Peice::init(int k, int l){
	this->pos = k;
	this->side = l;
	board[k/8][k%8] = l;
}

void Peice::move(int k){
	board[this->pos/8][this->pos%8] = 0;
	this->pos = k;
	board[this->pos/8][this->pos%8] = this->side;
}

int Peice::loc(){
	return this->pos;
}

void Peice::nc(vector<int> &v){
	int t;
	//North Check
	for(int i=1;i<=8;++i){
		t = check_pos(v, this->pos + (i * 8), this->side);
		if(t != 1)
			return ;
	}
}

void Peice::sc(vector<int> &v){
	int t;
	//South Check
	for(int i=1;i<=8;++i){
		t = check_pos(v, this->pos - (i * 8), this->side);
		if(t != 1)
			return ;
	}
}

void Peice::ec(vector<int> &v){
	int t;
	//East Check
	for(int i=1;i<=8;++i){
		if((this->pos/8) != ((this->pos + i)/8))
			break;
		t = check_pos(v, this->pos + i, this->side);
		if(t != 1)
			return ;
	}
}

void Peice::wc(vector<int> &v){
	int t;
	//West Check
	for(int i=1;i<=8;++i){
		if((this->pos/8) != ((this->pos - i)/8))
			break;
		t = check_pos(v, this->pos - i, this->side);
		if(t != 1)
			return ;
	}
}

void Peice::ne(vector<int> &v){
	int t;
	//Diognal Check (north-east)
	for(int i=1;i<=8;++i){
		if((((this->pos + (i * 9))/8) - (this->pos/8)) != i)
			break;
		t = check_pos(v, this->pos + (i * 9), this->side);
		if(t != 1)
			return ;
	}
}

void Peice::sw(vector<int> &v){
	int t;
	//Diognal Check (south-west)
	for(int i=1;i<=8;++i){
		if((((this->pos/8) - (this->pos - (i * 9))/8)) != i)
			break;
		t = check_pos(v, this->pos - (i * 9), this->side);
		if(t != 1)
			return ;
	}
}

void Peice::nw(vector<int> &v){
	int t;
	//Diognal Check (north-west)
	for(int i=1;i<=8;++i){
		if((((this->pos + (i * 7))/8) - (this->pos/8)) != i)
			break;
		t = check_pos(v, this->pos + (i * 7), this->side);
		if(t != 1)
			return ;
	}
}

void Peice::se(vector<int> &v){
	int t;
	//Diognal Check (south-east)
	for(int i=1;i<=8;++i){
		if(((this->pos/8) - ((this->pos - (i * 7))/8)) != i)
			break;
		t = check_pos(v, this->pos - (i * 7), this->side);
		if(t != 1)
			return ;
	}
}

