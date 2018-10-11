class Zero : public Peice{
	public:
	void moves(vector<int>&);
	int move(int);
};

int Zero::move(int k){
	board[this->pos/8][this->pos%8] = 0;
	if(k == -1){
		this->pos = k;
		return 0;
	}
	if((k - this->pos == 2) || (this->pos - k == 2)){
		this->pos = k;
		board[this->pos/8][this->pos%8] = this->side;
		return 2;
	}
	this->pos = k;
	board[this->pos/8][this->pos%8] = this->side;
	return 0;
}

void Zero::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	check_pos(v, this->pos + 8, this->side);
	check_pos(v, this->pos - 8, this->side);
	if((this->pos%8) != 0){
		check_pos(v, this->pos - 1, this->side);
	 	check_pos(v, this->pos + 7, this->side);
	 	check_pos(v, this->pos - 9, this->side);
	}
	if((this->pos%8) != 7){
	 	check_pos(v, this->pos + 1, this->side);
	 	check_pos(v, this->pos + 9, this->side);
	 	check_pos(v, this->pos - 7, this->side);
	}
}
