class Pawn : public Peice{
	public:
	void moves(vector<int>&);
};

void Pawn::moves(vector<int> &v){
	if(this->side == 3){
		 if(this->pos/8 == 1){
		 	if(check_pos(v, this->pos + 8, this->side) == 1)
		 		check_pos(v, this->pos + 16, this->side);
		 }
		 else{
		 	check_pos(v, this->pos + 8, this->side);
		 }
	}
	else{
		if(this->pos/8 == 6){
		 	if(check_pos(v, this->pos - 8, this->side) == 1)
		 		check_pos(v, this->pos - 16, this->side);
		 }
		 else{
		 	check_pos(v, this->pos - 8, this->side);
		 }
	}
}

