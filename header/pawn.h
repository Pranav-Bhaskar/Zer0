class Pawn : public Peice{
	public:
	void moves(vector<int>&);
	int move(int);
};

int Pawn::move(int k){
	int t = 0;
	board[this->pos/8][this->pos%8] = 0;
	if(((this->pos%8 - k%8) == 1 || (k%8 - this->pos%8) == 1) && (board[k/8][k%8] == 0))
		t = 4;	//to make an enpass move
	if((this->pos/8 - k/8) == 2 || (k/8 - this->pos/8) == 2){
		enpass = k;
		t = 3;	//to enpass is available
	}
	this->pos = k;
	if(k != -1)
		board[this->pos/8][this->pos%8] = this->side;
	if(((this->pos/8) == 7) || ((this->pos/8) == 0))
		return 1;	//for Promotion
	return t;
}

void Pawn::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	int t;
	if(this->side == 3){
		 if(this->pos/8 == 1){
		 	t = check_pos(v, this->pos + 8, this->side);
		 	if(t == 1){
		 		t = check_pos(v, this->pos + 16, this->side);
		 		if(t == 2)
		 			v.pop_back();
		 	}
		 	else
		 	if(t == 2)
		 		v.pop_back();

		 }
		 else{
		 	t = check_pos(v, this->pos + 8, this->side);
		 	if(t == 2)
		 		v.pop_back();
		 }
		 if((touch_pos(this->pos + 9, this->side) == 2) && (this->pos%8 !=7 ))
			check_pos(v, this->pos + 9, this->side);
		 if((touch_pos(this->pos + 7, this->side) == 2) && (this->pos%8 !=0 ))
			check_pos(v, this->pos + 7, this->side);
	}
	else{
		if(this->pos/8 == 6){
			t = check_pos(v, this->pos - 8, this->side);
		 	if(t == 1){
		 		t = check_pos(v, this->pos - 16, this->side);
		 		if(t == 2)v.pop_back();
		 	}
		 	else
		 	if(t == 2)
		 		v.pop_back();
		 }
		 else{
		 	t = check_pos(v, this->pos - 8, this->side);
		 	if(t == 2)
		 		v.pop_back();
		 }
		 if((touch_pos(this->pos - 9, this->side) == 2) && (this->pos%8 !=0))
			check_pos(v, this->pos - 9, this->side);
		 if((touch_pos(this->pos - 7, this->side) == 2 ) && (this->pos%8 !=7))
			check_pos(v, this->pos - 7, this->side);
	}
	if(enpass != -1){
		if(this->side == 3){
			if((this->pos/8 == (this->pos + 1)/8) && (touch_pos(this->pos + 1, this->side) == 2) && (enpass == this->pos + 1))
				check_pos(v, this->pos + 9, this->side);
			if((this->pos/8 == (this->pos - 1)/8) && (touch_pos(this->pos - 1, this->side) == 2) && (enpass == this->pos - 1))
				check_pos(v, this->pos + 7, this->side);
		}
		else{
			if((this->pos/8 == (this->pos + 1)/8) && (touch_pos(this->pos + 1, this->side) == 2) && (enpass == this->pos + 1))
				check_pos(v, this->pos - 7, this->side);
			if((this->pos/8 == (this->pos - 1)/8) && (touch_pos(this->pos - 1, this->side) == 2) && (enpass == this->pos - 1))
				check_pos(v, this->pos - 9, this->side);
		}
	}
}

