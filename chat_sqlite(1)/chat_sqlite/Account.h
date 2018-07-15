#pragma once

class Account
{
public:
	int  id;
	char *username;
	char *password;
	bool gender;
	char *birth;
	char *name;
	char *address;
	int zID; // gan ID 
	bool check; // check dang nhap
public:
	Account();
	~Account();
	void SignIn();
	void SingUp();
	void SignOut();
	void ShowMess(int);
	void ShowMessDetail(int);
	void SendMess(int);
	void AddFriend(int);
	void ShowFriend(int);
	void UpdateFriend(int);
	void BlockFriend(int);
};

