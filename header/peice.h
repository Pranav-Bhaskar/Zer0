class Peice{
	protected:
	int pos;			//Stores the current position of the peice
	int side;			//Stores the side of the peice
	void nc(vector<int>&);			//North Check
	void sc(vector<int>&);			//South Check
	void ec(vector<int>&);			//East Check
	void wc(vector<int>&);			//West Check
	void ne(vector<int>&);			//North-East Check
	void sw(vector<int>&);			//South-West Check
	void nw(vector<int>&);			//North-West Check
	void se(vector<int>&);			//South-East Check
	
	public:
	virtual void moves(vector<int>&)=0;	//Used to calculate all the moves the peice can make and append it to a vector
	virtual int move(int);			//Used to move the peice from its current position to the given position NOTE : this is overwriden in some derived classes
	void init(int, int);			//Used to initialize the peice
	int loc();				//return the current location of the peice
};


void Peice::init(int k, int l){
	this->pos = k;
	this->side = l;
	board[k/8][k%8] = l;
}

int Peice::move(int k){
	board[this->pos/8][this->pos%8] = 0;
	this->pos = k;
	if(k != -1)
		board[this->pos/8][this->pos%8] = this->side;
	return 0;
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

