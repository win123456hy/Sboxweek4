#pragma once
class Maccount
{
public:
	int  id;
	char *username;
	char *password;
	bool sex;
	char *birth;
	char *name;
	char *address;
	int zID; // gan ID 
	bool check; // check dang nhap
public:
	Maccount();
	~Maccount();
	void SignIn();
	void SingUp();
	void SignOut();
	void ShowMess(int);
	void ShowMessDetail(int);
	void SendMess(int);
	void AddFriend(int);
	void ShowFriend(int);
	void BlockFriend(int);
};

