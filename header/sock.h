class Sock{
	struct sockaddr_in address; 
	int sock, valread; 
	struct sockaddr_in serv_addr;
	char *data; 
	char buffer[1024]; 
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
	this->serv_addr.sin_family = AF_INET;
	this->serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &this->serv_addr.sin_addr);
	connect(this->sock, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr));
}

void Sock::sender(){
	send(this->sock, data, strlen(data), 0);
}

void Sock::recver(){
	valread = recv(this->sock, buffer, strlen(buffer), 0);
}
