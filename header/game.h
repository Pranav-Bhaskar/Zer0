class Game{
	//White Peices
	Peice* Z[16];
	//Black Peices
	Peice* z[16];
	//Vector For Keeping the Possible Moves for White
	vector<int> w_moves;	//All possible locations the white peices can move to
	vector<int> w_in_mov;	//In respect to the w_moves the initial position of any peice
	//Vector For Keeping the Possible Moves for Black
	vector<int> b_moves;
	vector<int> b_in_mov;
	
	vector<int> post;	//contains the peice number of the move respective to w_momes or b_moves (depends on chance)
	
	bool chance;	//A variable to keep track of the turn true->White; false->Black;
	
	int *pos;	//This pointer will be used to point to an array of integers which would have position of all peices in the game
	int lc;
	bool cas[6];
	string peice_char;
	Peice* back_peice[32];
	bool back_draw;
	bool back_cm;
	bool back_sm;
	
	void w_mov_Call(int k = 1);
	void w_mov_Disp();
	void b_mov_Call(int k = 1);
	void b_mov_Disp();
	
	bool draw;
	bool check_mate;	//Check if the Zer0 is in a check mate position	
	bool stale_mate;	//Check if the Zer0 is in a stale mate position	
	void check_checker(vector<int>&, int);	//A function to purify the moves the Zero can make
	
	void mover(int, int, int = 0);
	void get_pos();
	void set_pos();
	
	void disp_g();
	
	void promote(int, int);
	
	bool w_zer0;
	bool w_rok1;	//pos -> 0
	bool w_rok2;	//pos -> 7
	bool b_zer0;
	bool b_rok1;	//pos -> 56
	bool b_rok2;	//pos -> 63

	void castle(bool);	//Adds the feature of castling
	void castle_em(int);	//impliments castling
	
	void enpassent(bool);
	int enpasser;
	
	bool player1;	//player ? pvp : bvp(bot vs player)
	bool player2;
	int p2(bool);	//the bot makes his chice here and returns it 
	
	int last_capture;
	void hell_in_cell();
	
	bool type;
	bool saved;
	int numb;
	void promo(int, int);
	void saver();
	void saviour(int = 0);
	int getter();
	int promp;
	
	Sock* s;
	
	vector<string> dope_noob;
	void noob_dope();
	public:
	Game(bool = false);
	int begin();
	~Game();
};

Game::~Game(){
	if(this->s != NULL)
		system("rm -f server.lock");
}

Game::Game(bool t){		//If flase : for playing (predicting); true : for training;
	//initializing variables
	this->type = t;
	this->s = NULL;
	this->chance = true;
	this->check_mate = false;
	this->stale_mate = false;
	this->draw = false;
	this->w_zer0 = true;
	this->w_rok1 = true;
	this->w_rok2 = true;
	this->b_zer0 = true;
	this->b_rok1 = true;
	this->b_rok2 = true;
	this->pos = new int [32];
	enpass = -1;
	//Creating Peices
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
	
	//Initializing Peices
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
	
	this->dope_noob.clear();
	
	this->last_capture = 0;
	
	this->get_pos();	//making a backup of the current state of the board
	if(this->type){
		this->player1 = this->player2 = false;
		make_server();
	}
	else{
		char ch;
		cout<<"\nPress 1 to make player 1 a bot : ";
		cin>>ch;
		this->player1 = (ch == '1') ? false : true;
		cout<<"\nPress 1 to make player 2 a bot : ";
		cin>>ch;
		this->player2 = (ch == '1') ? false : true;
		if(!(this->player1 && this->player2))
			make_server();
	}
}

void Game::get_pos(){		//To get the currnt state of the board and store it as backup or checkpoint
	for(int i=0;i<16;++i){
		this->back_peice[i] = this->Z[i];
		this->back_peice[i + 16] = this->z[i];
	}
	for(int i=0;i<16;++i){
		this->pos[i] = this->Z[i]->loc();
		this->pos[i + 16] = this->z[i]->loc();
	}
	this->enpasser = enpass;
	this->lc = this->last_capture;
	this->cas[0] = this->w_zer0;
	this->cas[1] = this->w_rok1;
	this->cas[2] = this->w_rok2;
	this->cas[3] = this->b_zer0;
	this->cas[4] = this->b_rok1;
	this->cas[5] = this->b_rok2;
	peice_char = brd;
	this->back_draw = this->draw;
	this->back_cm = this->check_mate;
	this->back_sm = this->stale_mate;
	this->saved = true;
	this->numb = 0;
}

void Game::set_pos(){		//A function to restore the state of the board which was made from using the get_pos() function
	for(int i=0;i<16;++i){
		this->Z[i] = this->back_peice[i];
		this->z[i] = this->back_peice[i + 16];
	}
	for(int i=0;i<16;++i){
		this->Z[i]->move(this->pos[i]);
		this->z[i]->move(this->pos[i + 16]);
	}
	enpass = this->enpasser;
	this->last_capture = this->lc;
	this->w_zer0 = this->cas[0];
	this->w_rok1 = this->cas[1];
	this->w_rok2 = this->cas[2];
	this->b_zer0 = this->cas[3];
	this->b_rok1 = this->cas[4];
	this->b_rok2 = this->cas[5];
	brd = peice_char;
	this->draw = this->back_draw;
	this->check_mate = this->back_cm;
	this->stale_mate = this->back_sm;
	this->saved = true;
}

void Game::check_checker(vector<int> &v, int k){	//a function used to remove all the moves which could lead the Zer0 into check
	int ini;
	if(this->chance){	//enters this if is a white peice
		this->get_pos();	//will make a copy of the current status of the board 
		for(int i=0;i<v.size();++i){
			this->mover(k, v[i]);	//this move the kth element in the white side in the array to position v[i]
			this->b_mov_Call(0);	//will calculate all valid moves the black will be able to make if kth element is moved to position v[i]
			for(int j = 0;j<this->b_moves.size();++j)
				if(this->Z[0]->loc() == this->b_moves[j]){	//will check if moving the kth element to position v[i] lead to the check on the white Zer0
					v.erase(v.begin() + i);			//if it lead to a check then the kth peice will not be allowed to move to position v[i]
					--i;
					break;
				}
			this->set_pos();	//this will reset the whole board the situation it was at the begining of this function 
		}
	}
	else{		//enters this if it is a black peice (similar to whatis happening for the white peice)
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

void Game::enpassent(bool k){		//This function will be called if any pawn moves an enpassent
	if(k){
		for(int i=1;i<9;++i)
			if(this->pos[i + 16] == enpass)
				this->z[i]->move(-1);
		return ;
	}
	for(int i=1;i<9;++i)
		if(this->pos[i] == enpass)
			this->Z[i]->move(-1);
}

void Game::promote(int k, int posi){	//If a pawn reaches the end of the board this function is called to promote it to the peice it wants
	int opt;
	Peice *tem;
	if(!this->type)
		cout<<"\n1.Queen\n2.Rook\n3.Knight\n4.Bishop\nEnter choice : ";
	do{
		if(this->chance)
			opt = (this->player1) ? siner() : p2(false);
		else
			opt = (this->player2) ? siner() : p2(false);
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

void Game::castle_em(int posi){		//This function is called when the casteling move is made
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

void Game::castle(bool f){		//This function is just to check if casteling is possible or not and if it is possible then add it to the moves the Zer0 can make
	vector<int> tem;
	bool f_1, f_2;
	f_1 = true;
	f_2 = true;
	if(f){
		this->b_mov_Call(0);
		for(int j = 0;j<this->b_moves.size();++j){
			if(this->Z[0]->loc() == this->b_moves[j])
				return ;
			if((this->b_moves[j] == 3) || (this->b_moves[j] == 2))
				f_1 = false;
			if((this->b_moves[j] == 5) || (this->b_moves[j] == 6))
				f_2 = false;
		}
		if(this->w_zer0 && this->w_rok1 && f_1){
			this->Z[10]->moves(tem);
			for(int j = 0;j<tem.size();++j)
				if(3 == tem[j]){
					this->w_moves.push_back(2);
					this->w_in_mov.push_back(this->Z[0]->loc());
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
					this->post.push_back(0);
					break;
				}
		}
		return ;
	}
	this->w_mov_Call(0);
	for(int j = 0;j<this->w_moves.size();++j){
		if(this->z[0]->loc() == this->w_moves[j])
			return ;
		if((this->w_moves[j] == 59) || (this->w_moves[j] == 58))
			f_1 = false;
		if((this->w_moves[j] == 61) || (this->w_moves[j] == 62))
			f_2 = false;
	}
	if(this->b_zer0 && this->b_rok1 && f_1){
		this->z[10]->moves(tem);
		for(int j = 0;j<tem.size();++j)
			if(59 == tem[j]){
				this->b_moves.push_back(58);
				this->b_in_mov.push_back(this->z[0]->loc());
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
				this->post.push_back(0);
				break;
			}
	}
}

void Game::mover(int k, int posi, int l){	//This function calles a function Peice::move() of the peice the user decides to move and on the baises of the data returned by the function calls other functions
	int t;
	if(l){
		++this->last_capture;
		if(this->last_capture > 50)
			this->draw = true;
	}
	if(k < 16){
		for(int i=0;i<16;++i)
			if(this->pos[i + 16] == posi){
				this->z[i]->move(-1);
				if(l)
					this->last_capture = 0;
			}
		t = this->Z[k]->move(posi);
		if(!l)
			return ;
		if((k>0)&&(k<9))
			this->last_capture = 0;
		switch(t){
		case 1: if(l == 1)
				this->promote(k, posi);
			else
				this->promo(k, posi);
			break;
		case 2: this->castle_em(posi);
			break;
		case 3: break;
		case 4: enpassent(true);
			break;
		default:enpass = -1;
		}
		return ;
	}
	k -= 16;
	for(int i=0;i<16;++i)
		if(this->pos[i] == posi){
			this->Z[i]->move(-1);
			if(l)
				this->last_capture = 0;
		}
	t = this->z[k]->move(posi);
	if(!l)
		return ;
	if((k>0)&&(k<9))
		this->last_capture = 0;
	switch(t){
	case 1: if(l == 1)
			this->promote(k + 16, posi);
		else
			this->promo(k + 16, posi);
		break;
	case 2: this->castle_em(posi);
		break;
	case 3: break;
	case 4: enpassent(false);
		break;
	default:enpass = -1;
	}
}

void Game::hell_in_cell(){
	int k = 0;
	for(int i=0;i<16;++i){
		if(this->Z[i]->loc() != -1)
			++k;
		if(this->z[i]->loc() != -1)
			++k;
	}
	if(k == 2)
		this->draw = true;
}

void Game::noob_dope(){
	string s;
	s.clear();
	for(int i=0;i<16;++i)
		s += t_string(this->Z[i]->loc());
	for(int i=0;i<16;++i)
		s += t_string(this->z[i]->loc());
	this->dope_noob.push_back(s);
	if(freak_counter(this->dope_noob) > 2)
		this->draw = true;
}

void Game::promo(int k, int posi){
	int opt;
	Peice *tem;
	for(opt=1;opt<=4;++opt){
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
			this->saviour(opt);
			continue ;
		}
		k -= 16;
		this->z[k] = tem;
		this->z[k]->init(posi, 1);
		this->saviour(opt);
		k += 16; 
	}
	++this->numb;
}

void Game::saviour(int opt){
	this->saved = false;
	ofstream f;
	if(opt != 0)
		f.open((def_dir + t_string(this->numb) + "." + t_string((opt * 10) + 9)).c_str(), ios::binary);
	else{
		f.open((def_dir + t_string(this->numb)).c_str(), ios::binary);
		++this->numb;
	}
	f << (this->chance) ? '1' : '0';	//Chance
	f << ",";
	f << (this->w_zer0 && this->w_rok1) ? 1 : 0;	//White long
	f << ",";
	f << (this->w_zer0 && this->w_rok2) ? 1 : 0;	//white short
	f << ",";
	f << (this->b_zer0 && this->b_rok1) ? 1 : 0;	//black long
	f << ",";
	f << (this->b_zer0 && this->b_rok2) ? 1 : 0;	//black short
	f << ",";
	for(int i=0;i<16;++i)
		f << this->Z[i]->loc() << ",";
	for(int i=0;i<16;++i)
		f << this->z[i]->loc() << ",";	//current positions
	f << enpass << ",";	//stores the pos of enpass if possible
	f << this->last_capture << ",";	//stores no of chances left
	f << brd;	//saves the lables of peices
	f.close();
}

void Game::saver(){
	get_pos();
	for(int i=0;i<this->post.size();++i){
		if(this->chance)
			this->mover(this->post[i], this->w_moves[i], 2);
		else
			this->mover(this->post[i], this->b_moves[i], 2);
		if(this->saved)
			this->saviour();
		set_pos();
	}
}

int Game::getter(){
	ifstream f;
	f.open("./CheckPoint/.move", ios::binary);
	double s;
	f>>s;
	int k = s;
	this->promp = (s*10) - (k*10);
	f.close();
	return k;
}

int Game::p2(bool b){		//This function makes moves when you choose to play against a bot. This is a substitute to the bot.
	int t;
	if(b){
		this->saver();
		this->s = new Sock;
		this->s->sender();
		this->s->recver();
		t = getter();
	}
	else
		t = this->promp;
	if(!this->type)
			cout<<endl<<t;
	return t;
}

int Game::begin(){		//This function askes users/bot for their turns and calls the Game::mover() to move the peice the user/bot selects
	int opt;
	while(1){
		this->noob_dope();
		if(!this->type){
			disp_help();
			this->disp_g();
		}
		if(this->chance){
			this->w_mov_Call();
			this->hell_in_cell();
			if(this->check_mate || this->stale_mate || this->draw)
				break;
			if(!this->type)
				this->w_mov_Disp();
			do{
				opt = this->player1 ? siner() : p2(true);
			}while(opt < 0 || opt >= this->post.size());
			this->mover(this->post[opt], this->w_moves[opt], 1);
			switch(this->post[opt]){
			case 0: this->w_zer0 = false;
				break;
			case 10: this->w_rok1 = false;
				break;
			case 11: this->w_rok2 = false;
				break; 
			}
		}
		else{
			this->b_mov_Call();
			this->hell_in_cell();
			if(this->check_mate || this->stale_mate || this->draw)
				break;
			if(!this->type)
				this->b_mov_Disp();
			do{
				opt = this->player2 ? siner() : p2(true);
			}while(opt < 0 || opt >= this->post.size());
			this->mover(this->post[opt] + 16, this->b_moves[opt], 1);
			switch(this->post[opt]){
			case 0: this->b_zer0 = false;
				break;
			case 10: this->b_rok1 = false;
				break;
			case 11: this->b_rok2 = false;
				break; 
			}
		}
		this->chance = !this->chance;
	}
	if(this->check_mate)
		cout<<"\nCheckMate from ";
	if(this->stale_mate){
		cout<<"\nStaleMate";
		return 0;
	}
	if(this->draw){
		cout<<"\nDraw\n";
		return 0;
	}
	if(this->chance){
		cout<<"Black\n";
		return 2;
	}
	cout<<"White\n";
	return 1;
}

void Game::disp_g(){		//This function is used to display the current status of the board 
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

void Game::w_mov_Call(int k){		//It calculates all posible moves the white side can make by calling the Peice::moves() function of every white peice and storing them in a vector (Game::w_moves)
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
				this->check_checker(v, i);	//Gives a call to Game::check_checker() to remove the peices which lead to a check on the Zer0
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
	this->castle(true);
	if(this->post.empty()){
		this->b_mov_Call(0);
		for(int j = 0;j<this->b_moves.size();++j)
			if(this->Z[0]->loc() == this->b_moves[j]){
				this->check_mate = true;
				return ;
			}
		this->stale_mate = true;
	}
}

void Game::w_mov_Disp(){		//Displays all the possible moves the white side can make (gets its data from the vector Game::w_moves)
	cout<<endl<<"Showing all possible white moves"<<endl;
	for(int i=0;i<this->w_moves.size();++i){
		cout<<i<<". "<<this->w_in_mov[i]<<" -> "<<this->w_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}

void Game::b_mov_Call(int k){		//Same as Game::w_mov_call
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
	this->castle(false);
	if(this->post.empty()){
		this->w_mov_Call(0);
		for(int j = 0;j<this->w_moves.size();++j){
			if(this->z[0]->loc() == this->w_moves[j]){
				this->check_mate = true;
				return ;
			}
		}
		this->stale_mate = true;
	}
}

void Game::b_mov_Disp(){		//Same as Game::w_mov_Disp()
	cout<<endl<<"Showing all possible black moves"<<endl;
	for(int i=0;i<this->b_moves.size();++i){
		cout<<i<<". "<<this->b_in_mov[i]<<" -> "<<this->b_moves[i]<<"                     ";
		if(i&1 == 1)
			cout<<endl;
	}
	cout<<endl;
}
