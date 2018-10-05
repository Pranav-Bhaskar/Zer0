class Zero : public Peice{
	public:
	void moves(vector<int>&);
};

void Zero::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	check_pos(v, this->pos + 8, this->side);
	check_pos(v, this->pos - 8, this->side);
	if(((pos-1)/8) == (pos/8)){
		check_pos(v, this->pos - 1, this->side);
	 	check_pos(v, this->pos + 9, this->side);
	 	check_pos(v, this->pos - 9, this->side);
	}
	if(((pos+1)/8) == (pos/8)){
	 	check_pos(v, this->pos + 1, this->side);
	 	check_pos(v, this->pos + 7, this->side);
	 	check_pos(v, this->pos - 7, this->side);
	}
}
