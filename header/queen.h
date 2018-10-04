class Queen: public Peice{
	public:
	void moves(vector<int>&);
};

void Queen::moves(vector<int> &v){
	this->nc(v);	//North condition
	this->sc(v);	//South Condition
	this->ec(v);	//East Condition
	this->wc(v);	//West Condition
	this->ne(v);	//Diognal Check (north-east)
	this->sw(v);	//Diognal Check (south-west)
	this->nw(v);	//Diognal Check (north-west)
	this->se(v);	//Diognal Check (south-east)
}
