#pragma once
#include <iostream>
#include <sqlite3.h>
#include<stdc++.h>
using namespace std;
class Mchat
{
public:
	Mchat();
	~Mchat();
public:
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	const char *szSQL;
	const char *pzTest;
	sqlite3_stmt *stmt;
	list<string> answer;
public:
	void Open();
	int Select_login(sqlite3 *db, char *fn, char *ln);
	void Insert_Acc(sqlite3 *db, char *, char *,bool,char *,char *,char *);
	void SelectMess(sqlite3 *db, int id);
	int Seach_fr(char *frien);
	void ShowMessDetail(sqlite3 *db, int id1, int id2);
	bool CheckFriend(sqlite3 *db, int id1, int id2);
	bool CheckBlock(sqlite3 *db, int id1, int id2);
	void WriteToFriend(sqlite3 *db, int id1, int id2);
	void ShowFriend(sqlite3 *db, int id1);
	void BlockFriend(sqlite3 *db, int id1, int id2);
	void WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time,int tt);
	void update_tt(sqlite3 *db, int id1, int id2);
};

