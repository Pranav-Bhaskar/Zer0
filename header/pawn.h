class Pawn : public Peice{
	public:
	void moves(vector<int>&);
	int move(int);
};

int Pawn::move(int k){
	board[this->pos/8][this->pos%8] = 0;
	this->pos = k;
	if(k != -1)
		board[this->pos/8][this->pos%8] = this->side;
	if(((this->pos/8) == 7) || ((this->pos/8) == 0))
		return 1;
	return 0;
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
		 if(touch_pos(this->pos + 9, this->side) == 2)
			check_pos(v, this->pos + 9, this->side);
		 if(touch_pos(this->pos + 7, this->side) == 2)
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
		 if(touch_pos(this->pos - 9, this->side) == 2)
			check_pos(v, this->pos - 9, this->side);
		 if(touch_pos(this->pos - 7, this->side) == 2)
			check_pos(v, this->pos - 7, this->side);
	}
	
}

