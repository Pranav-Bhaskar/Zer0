class Knight : public Peice{
	public:
	void moves(vector<int>&);
};

void Knight::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	if(((this->pos + 15)/8) - (this->pos/8) == 2)
		check_pos(v, this->pos + 15, this->side);
	
	if(((this->pos + 17)/8) - (this->pos/8) == 2)
		check_pos(v, this->pos + 17, this->side);
	
	if(((this->pos + 10)/8) - (this->pos/8) == 1)
		check_pos(v, this->pos + 10, this->side);
	
	if(((this->pos + 6)/8) - (this->pos/8) == 1)
		check_pos(v, this->pos + 6, this->side);
	
	if((this->pos/8) - ((this->pos - 10)/8) == 1)
		check_pos(v, this->pos - 10, this->side);
	
	if((this->pos/8) - ((this->pos - 6)/8) == 1)
		check_pos(v, this->pos - 6, this->side);
		
	if((this->pos/8) - ((this->pos - 15)/8) == 2)
		check_pos(v, this->pos - 15, this->side);
	
	if((this->pos/8) - ((this->pos - 17)/8) == 2)
		check_pos(v, this->pos - 17, this->side);
}
