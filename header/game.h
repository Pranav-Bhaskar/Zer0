class Game{
	//White Peices
	Peice* Z[16];
	//Black Peices
	Peice* z[16];
	//Vector For Keeping the Possible Moves for White
	vector<int> w_moves;
	vector<int> w_in_mov;
	//Vector For Keeping the Possible Moves for Black
	vector<int> b_moves;
	vector<int> b_in_mov;
	public:
	Game();
	void disp_g();
	void w_mov_Call();
	void w_mov_Disp();
	void b_mov_Call();
	void b_mov_Disp();
};

Game::Game(){
	cout<<"\nCreating the Peices...";
	//White Peices
	
	this->Z[0] = new Zero;
	this->Z[9] = new Queen;
	this->Z[10] = new Rook;
	this->Z[11] = new Rook;
	this->Z[12] = new Bishop;
	this->Z[13] = new Bishop;
	this->Z[14] = new Knight;
	this->Z[15] = new Knight;
	for(int i=1;i<=8;++i)
		this->Z[i] = new Pawn;
	
		
	//Black Peices
	this->z[0] = new Zero;
	this->z[9] = new Queen;
	this->z[10] = new Rook;
	this->z[11] = new Rook;
	this->z[12] = new Bishop;
	this->z[13] = new Bishop;
	this->z[14] = new Knight;
	this->z[15] = new Knight;
	for(int i=1;i<=8;++i)
		this->z[i] = new Pawn;
	
	
	cout<<"\nInitializing the Peices...";
	//White Peices
	this->Z[0]->init(4, 3);
	this->Z[9]->init(3, 3);
	this->Z[10]->init(0, 3);
	this->Z[11]->init(7, 3);
	this->Z[12]->init(2, 3);
	this->Z[13]->init(5, 3);
	this->Z[14]->init(1, 3);
	this->Z[15]->init(6, 3);
	for(int i=1;i<=8;++i)
		this->Z[i]->init(i+7, 3);
	
	
	//Black Peices
	this->z[0]->init(60, 1);
	this->z[9]->init(59, 1);
	this->z[10]->init(56, 1);
	this->z[11]->init(63, 1);
	this->z[12]->init(58, 1);
	this->z[13]->init(61, 1);
	this->z[14]->init(57, 1);
	this->z[15]->init(62, 1);
	for(int i=1;i<=8;++i)
		this->z[i]->init(i+47, 1);
}

void Game::disp_g(){
	char board[8][8];
	for(int i=0;i<8;++i)
		for(int j=0;j<8;++j)
			board[i][j] = ' ';
	//White Peices
	for(int i=0;i<16;++i)
		if(this->Z[i]->loc() != -1)
			board[this->Z[i]->loc()/8][this->Z[i]->loc()%8] = brd[i];
	
	//Black Pieces
	for(int i=0;i<16;++i)
		if(this->z[i]->loc() != -1)
			board[this->z[i]->loc()/8][this->z[i]->loc()%8] = brd[i] + 32;
	
	for(int i=7;i >= 0 ;--i){
		cout<<endl<<" ---------------------------------"<<endl<<" |";
		for(int j=0;j<8;++j)
			cout<<" "<<board[i][j]<<" |";
	}
	cout<<endl<<" ---------------------------------"<<endl;
}

void Game::w_mov_Call(){
	this->w_moves.clear();
	this->w_in_mov.clear();
	for(int i=0;i<16;++i)
		if(this->Z[i]->loc() != -1){
			this->Z[i]->moves(this->w_moves);
			while(this->w_moves.size() != this->w_in_mov.size())
				this->w_in_mov.push_back(this->Z[i]->loc());
		}
}

void Game::w_mov_Disp(){
	cout<<endl<<"Showing all posiible white moves"<<endl;
	for(int i=0;i<this->w_moves.size();++i){
		cout<<this->w_in_mov[i]<<" -> "<<this->w_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}

void Game::b_mov_Call(){
	this->b_moves.clear();
	this->b_in_mov.clear();
	for(int i=0;i<16;++i)
		if(this->z[i]->loc() != -1){
			this->z[i]->moves(this->b_moves);
			while(this->b_moves.size() != this->b_in_mov.size())
				this->b_in_mov.push_back(this->z[i]->loc());
		}
}

void Game::b_mov_Disp(){
	cout<<endl<<"Showing all posiible black moves"<<endl;
	for(int i=0;i<this->b_moves.size();++i){
		cout<<this->b_in_mov[i]<<" -> "<<this->b_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}
