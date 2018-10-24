void disp_help(){
	cout<<endl
	<<"           Board For Reference"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 56 | 57 | 58 | 59 | 60 | 61 | 62 | 63 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 48 | 49 | 50 | 51 | 52 | 53 | 54 | 55 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 40 | 41 | 42 | 43 | 44 | 45 | 46 | 47 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 8  | 9  | 10 | 11 | 12 | 13 | 14 | 15 |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl
	<<"| 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  |"<<endl
	<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
}

int check_pos(vector<int> &v, int pos, int side){
	if(pos < 0 || pos > 63)
		return 0;
	if(board[pos/8][pos%8] == 0){
		v.push_back(pos);
		return 1;
	}
	if(board[pos/8][pos%8] != side){
		v.push_back(pos);
		return 2;
	}
	return 0;
}

int touch_pos(int pos, int side){
	if(pos < 0 || pos > 63)
		return 0;
	if(board[pos/8][pos%8] == 0)
		return 1;
	if(board[pos/8][pos%8] != side)
		return 2;
	return 0;
}

string t_string(int num){
	string s;
	if(num == 0)
		return string("0");
	while(num){
		s.push_back(num%10 + '0');
		num /= 10;
	}
	reverse(s.begin(), s.end());
	return s;
}

void disp_brd(){
	for(int i=7;i >= 0 ;--i){
		cout<<endl<<" ---------------------------------"<<endl<<" |";
		for(int j=0;j<8;++j)
			cout<<" "<<board[i][j]<<" |";
	}
	cout<<endl<<" ---------------------------------"<<endl;
}

int freak_counter(vector<string>& v){
	if(v.size() <= 0)
		return 0;
	map<string, int> fMap;
	int mFreak = 0;
	for (string x : v){
		int f = ++fMap[x];
		if (f > mFreak)
			mFreak = f;
	}
	return mFreak;
}

int siner(){
	int number;
	while(1){
		cin>>number;
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(69, '\n');
			cout << "Invalid input " << endl;
		}
		else
			break;
		cout<<"HINT : Try entering numbers for a change"<<endl;
	}
	return number;
}
