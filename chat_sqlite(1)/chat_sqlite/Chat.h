#include <iostream>
#include "sqlite3.h"
#include "User.h"
#include<stdio.h>
#include <list>

using namespace std;
class Chat
{
public:
	Chat();
	~Chat();
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	list<string> answer;
	list<string> friendss;
	list<string> thanhpho;
	list<User> listUser;
public:
	void Open();
	void Close();
	int Select_login(sqlite3 *db, char *fn, char *ln);
	void Insert_Acc(sqlite3 *db, char *, char *,bool,char *,char *,char *);
	void Insert_Acc_In_View(sqlite3 *db,int, bool, char *, char *, char *);
	void SelectMessTo(sqlite3 *db, int id);
	void SelectMessFrom(sqlite3 *db, int id);
	int Seach_fr(char *frien);
	void ShowMessDetail(sqlite3 *db, int id1, int id2,char *namef);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ShowFriend(sqlite3 *db, int id1);
	void ShowFriendWithAddress(sqlite3 *db, int id1);
	void ShowFriendDetail(sqlite3 *db, int id2);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time,int tt);
	void update_tt(sqlite3 *db, int id1, int id2);
	int GetIDfromName(char*);
	string GetNamefromID(int id);
	void UpdateInterfaceFriend(sqlite3 *db,int id2,bool,char*, char*,char*);
};

