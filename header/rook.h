class Rook : public Peice{
	public:
	void moves(vector<int>&);
};

void Rook::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	this->nc(v);	//North condition
	this->sc(v);	//South Condition
	this->ec(v);	//East Condition
	this->wc(v);	//West Condition
}

