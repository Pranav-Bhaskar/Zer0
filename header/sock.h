class Sock{
	struct sockaddr_in sin; 
	int sock, valread;
	char *data; 
	char buffer[4]; 
	public:
	Sock();
	void sender();
	void recver();
	void ender();
};

Sock::Sock(){
	this->data = new char[2];
	this->data[0] = '0';
	this->data[1] = '\0';
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	this->sin.sin_family = AF_INET;
	this->sin.sin_port = htons(PORT);
	this->sin.sin_addr.s_addr = INADDR_ANY;
	connect(this->sock, (struct sockaddr *)&(this->sin), sizeof(this->sin));
}

void Sock::sender(){
	send(this->sock, this->data, strlen(data), 0);
}

void Sock::ender(){
	this->data[0] = '1';
	send(this->sock, this->data, strlen(data), 0);
	close(this->sock);
	system("rm -rf ./server.lock");
}

void Sock::recver(){
	valread = recv(this->sock, &buffer, sizeof(buffer), 0);
}
