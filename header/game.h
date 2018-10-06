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
	void check_checker(vector<int>&, int);	//A function to purify the moves the king can make
	
	void mover(int, int, int = 0);
	void get_pos();
	void set_pos();
	
	void disp_g();
	
	void promote(int, int);
	
	int w_zer0;
	int w_rok1;	//pos -> 0
	int w_rok2;	//pos -> 7
	int b_zer0;
	int b_rok1;	//pos -> 56
	int b_rok2;	//pos -> 63

	void castle(bool, int);	//Adds the feature of castling
	void castle_em(int);	//impliments castling
	public:
	Game();
	void begin();
};

Game::Game(){
	//initializing variables
	this->chance = 1;
	this->check_mate = 0;
	this->stale_mate = 0;
	this->w_zer0 = 1;
	this->w_rok1 = 1;
	this->w_rok2 = 1;
	this->b_zer0 = 1;
	this->b_rok1 = 1;
	this->b_rok2 = 1;
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

void Game::promote(int k, int posi){
	int opt;
	Peice *tem;
	do{
		cout<<"\n1.Queen\n2.Rook\n3.Knight\n4.Bishop\nEnter choice : ";
		cin>>opt;
	}while(opt < 1 || opt > 4);
	switch(opt){
	case 1: tem = new Queen;
		brd[k] = 'Q';
		break;
	case 2: tem = new Rook;
		brd[k] = 'R';
		break;
	case 3: tem = new Knight;
		brd[k] = 'K';
		break;
	case 4: tem = new Bishop;
		brd[k] = 'B';
		break;
	}
	if(k < 16){
		this->Z[k] = tem;
		this->Z[k]->init(posi, 3);
		return ;
	}
	k -= 16;
	this->z[k] = tem;
	this->z[k]->init(posi, 1);
}

void Game::castle_em(int posi){
	switch(posi){
	case 6: this->Z[11]->move(5);
		break;
	case 2: this->Z[10]->move(3);
		break;
	case 58:this->z[10]->move(59);
		break;
	case 62:this->z[11]->move(61);
		break;
	}
}

void Game::castle(bool f, int l){
	vector<int> tem;
	int f_1, f_2;
	f_1 = 1;
	f_2 = 1;
	if(f){
		if((this->chance == 1) && (l == 0))
			return ;
		this->b_mov_Call(0);
		for(int j = 0;j<this->b_moves.size();++j){
			if(this->Z[0]->loc() == this->b_moves[j])
				return ;
			if((this->b_moves[j] == 3) || (this->b_moves[j] == 2))
				f_1 = 0;
			if((this->b_moves[j] == 5) || (this->b_moves[j] == 6))
				f_2 = 0;
		}
		if(this->w_zer0 && this->w_rok1 && f_1){
			this->Z[10]->moves(tem);
			for(int j = 0;j<tem.size();++j)
				if(3 == tem[j]){
					this->w_moves.push_back(2);
					this->w_in_mov.push_back(this->Z[0]->loc());
					if(l)
						this->post.push_back(0);
					break;
				}
					
		}
		if(this->w_zer0 && this->w_rok2 && f_2){
			tem.clear();
			this->Z[11]->moves(tem);
			for(int j = 0;j<tem.size();++j)
				if(5 == tem[j]){
					this->w_moves.push_back(6);
					this->w_in_mov.push_back(this->Z[0]->loc());
					if(l)
						this->post.push_back(0);
					break;
				}
		}
		return ;
	}
	if((this->chance == 0) && (l == 0))
		return ;
	this->w_mov_Call(0);
	for(int j = 0;j<this->w_moves.size();++j){
		if(this->z[0]->loc() == this->w_moves[j])
			return ;
		if((this->w_moves[j] == 59) || (this->w_moves[j] == 58))
			f_1 = 0;
		if((this->w_moves[j] == 61) || (this->w_moves[j] == 62))
			f_2 = 0;
	}
	if(this->b_zer0 && this->b_rok1 && f_1){
		this->z[10]->moves(tem);
		for(int j = 0;j<tem.size();++j)
			if(59 == tem[j]){
				this->b_moves.push_back(58);
				this->b_in_mov.push_back(this->z[0]->loc());
				if(l)
					this->post.push_back(0);
				break;
			}
				
	}
	if(this->b_zer0 && this->b_rok2 && f_2){
		tem.clear();
		this->z[11]->moves(tem);
		for(int j = 0;j<tem.size();++j)
			if(61 == tem[j]){
				this->b_moves.push_back(62);
				this->b_in_mov.push_back(this->z[0]->loc());
				if(l)
					this->post.push_back(0);
				break;
			}
	}
}

void Game::mover(int k, int posi, int l){
	int t;
	if(k < 16){
		for(int i=0;i<16;++i)
			if(this->pos[i + 16] == posi)
				this->z[i]->move(-1);
		t = this->Z[k]->move(posi);
		if(l && (t == 1))
			this->promote(k, posi);
		if(l && (t == 2))
			this->castle_em(posi);
		return ;
	}
	k -= 16;
	for(int i=0;i<16;++i)
		if(this->pos[i] == posi)
			this->Z[i]->move(-1);
	t = this->z[k]->move(posi);
	if(l && (t == 1))
		this->promote(k + 16, posi);
	if(l && (t == 2))
		this->castle_em(posi);
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
			this->mover(this->post[opt], this->w_moves[opt], 1);
			switch(this->post[opt]){
			case 0: this->w_zer0 = 0;
				break;
			case 10: this->w_rok1 = 0;
				break;
			case 11: this->w_rok2 = 0;
				break; 
			}
			this->get_pos();	//XLAR8 you have to give a call to your history function here; When doing so delete this call;
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
			this->mover(this->post[opt] + 16, this->b_moves[opt], 1);
			switch(this->post[opt]){
			case 0: this->b_zer0 = 0;
				break;
			case 10: this->b_rok1 = 0;
				break;
			case 11: this->b_rok2 = 0;
				break; 
			}
			this->get_pos();	//XLAR8 you have to give a call to your history function here; When doing so delete this call;
			this->chance = 1;
		}
	}
	if(this->check_mate)
		cout<<"\nCheckMate\n";
	if(this->stale_mate)
		cout<<"\nStaleMate\n";
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
			board[this->z[i]->loc()/8][this->z[i]->loc()%8] = brd[i + 16] + 32;
	
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
	this->castle(true, k);
	if(this->post.empty()){
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
	this->castle(false, k);
	if(this->post.empty()){
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
