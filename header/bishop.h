class Bishop : public Peice{
	public:
	void moves(vector<int>&);
};

void Bishop::moves(vector<int> &v){
	if(this->pos == -1)
		return ;
	this->ne(v);	//Diognal Check (north-east)
	this->sw(v);	//Diognal Check (south-west)
	this->nw(v);	//Diognal Check (north-west)
	this->se(v);	//Diognal Check (south-east)
}
