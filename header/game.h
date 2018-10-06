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
	
	vector<int> post;
	
	int chance;	//A variable to keep track of the turn 1->White; 2->Black;
	
	int *pos;
	
	void w_mov_Call(int k = 1);
	void w_mov_Disp();
	void b_mov_Call(int k = 1);
	void b_mov_Disp();
	
	int check_mate;	//Check if the Zer0 is in a check mate position	
	int stale_mate;	//Check if the Zer0 is in a stale mate position	
	void check_checker(vector<int>&, int);	//A function to purify the moves the Zero can make
	
	void mover(int, int);
	void get_pos();
	void set_pos();
	
	public:
	
	void disp_g();
	Game();
	void begin();
};

Game::Game(){
	this->chance = 1;
	this->check_mate = 0;
	this->stale_mate = 0;
	this->pos = new int [32];
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
	this->get_pos();
}

void Game::get_pos(){
	for(int i=0;i<16;++i){
		this->pos[i] = this->Z[i]->loc();
		this->pos[i + 16] = this->z[i]->loc();
	}
}

void Game::set_pos(){
	for(int i=0;i<16;++i){
		this->Z[i]->move(this->pos[i]);
		this->z[i]->move(this->pos[i + 16]);
	}
}

void Game::check_checker(vector<int> &v, int k){
	int ini;
	if(this->chance == 1){
		this->get_pos();
		for(int i=0;i<v.size();++i){
			this->mover(k, v[i]);
			this->b_mov_Call(0);
			for(int j = 0;j<this->b_moves.size();++j)
				if(this->Z[0]->loc() == this->b_moves[j]){
					v.erase(v.begin() + i);
					--i;
					break;
				}
			this->set_pos();
		}
		
	}
	else{
		this->get_pos();
		for(int i=0;i<v.size();++i){
			this->mover(k + 16, v[i]);
			this->w_mov_Call(0);
			for(int j = 0;j<this->w_moves.size();++j)
				if(this->z[0]->loc() == this->w_moves[j]){
					v.erase(v.begin() + i);
					--i;
					break;
				}
			this->set_pos();
		}
	}
}

void Game::mover(int k, int posi){
	if(k < 16){
		for(int i=0;i<16;++i)
			if(this->pos[i + 16] == posi)
				this->z[i]->move(-1);
		this->Z[k]->move(posi);
		return ;
	}
	k -= 16;
	for(int i=0;i<16;++i)
		if(this->pos[i] == posi)
			this->Z[i]->move(-1);
	this->z[k]->move(posi);
}

void Game::begin(){
	int opt;
	while(1){
		disp_help();
		this->disp_g();
		if(this->chance){
			do{
				this->w_mov_Call();
				if((this->check_mate | this->stale_mate) == 1)
					break;
				this->w_mov_Disp();
				cin>>opt;
			}while(opt < 0 || opt >= this->post.size());
			if((this->check_mate | this->stale_mate) == 1)
				break;
			this->mover(this->post[opt], w_moves[opt]);
			this->get_pos();
			this->chance = 0;
		}
		else{
			do{
				this->b_mov_Call();
				if((this->check_mate | this->stale_mate) == 1)
					break;
				this->b_mov_Disp();
				cin>>opt;
			}while(opt < 0 || opt >= this->post.size());
			if((this->check_mate | this->stale_mate) == 1)
				break;
			this->mover(this->post[opt] + 16, b_moves[opt]);
			this->get_pos();
			this->chance = 1;
		}
		
	}
	if(this->check_mate)
		cout<<"\nCheckMate";
	if(this->stale_mate)
		cout<<"\nStaleMate";
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

void Game::w_mov_Call(int k){
	vector<int> v;
	this->w_moves.clear();
	this->w_in_mov.clear();
	if(k)
		this->post.clear();
	for(int i=0;i<16;++i){
		if(this->Z[i]->loc() != -1){
			v.clear();
			this->Z[i]->moves(v);
			if(k == 1)
				this->check_checker(v, i);
			for(int l=0;l<v.size();++l){
				this->w_moves.push_back(v[l]);
				this->w_in_mov.push_back(this->Z[i]->loc());
				if(k)
					this->post.push_back(i);
			}
		}
	}
	if(k == 0)
		return ;
	if(this->w_moves.empty()){
		this->b_mov_Call(0);
		for(int j = 0;j<this->b_moves.size();++j)
			if(this->Z[0]->loc() == this->b_moves[j]){
				this->check_mate = 1;
				return ;
			}
		this->stale_mate = 1;
	}
}

void Game::w_mov_Disp(){
	cout<<endl<<"Showing all possible white moves"<<endl;
	for(int i=0;i<this->w_moves.size();++i){
		cout<<i<<". "<<this->w_in_mov[i]<<" -> "<<this->w_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}

void Game::b_mov_Call(int k){
	vector<int> v;
	this->b_moves.clear();
	this->b_in_mov.clear();
	if(k)
		this->post.clear();
	for(int i=0;i<16;++i){
		if(this->z[i]->loc() != -1){
			v.clear();
			this->z[i]->moves(v);
			if(k == 1)
				this->check_checker(v, i);
			for(int l=0;l<v.size();++l){
				this->b_moves.push_back(v[l]);
				this->b_in_mov.push_back(this->z[i]->loc());
				if(k)
					this->post.push_back(i);
			}
		}
	}
	if(k == 0)
		return ;
	if(this->b_moves.empty()){
		this->w_mov_Call(0);
		for(int j = 0;j<this->w_moves.size();++j){
			if(this->z[0]->loc() == this->w_moves[j]){
				this->check_mate = 1;
				return ;
			}
		}
		this->stale_mate = 1;
	}
}

void Game::b_mov_Disp(){
	cout<<endl<<"Showing all possible black moves"<<endl;
	for(int i=0;i<this->b_moves.size();++i){
		cout<<i<<". "<<this->b_in_mov[i]<<" -> "<<this->b_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}
