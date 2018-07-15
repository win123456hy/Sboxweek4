#include "Maccount.h"
#include "Mchat.h"
#include<stdc++.h>
#include <iostream>
#include <windows.h>
#include<conio.h>
using namespace std;

Maccount::Maccount(){}
Maccount::~Maccount(){}
void Maccount::SignIn() {
	username = new (char);
	password = new (char);

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	Mchat conn;
	conn.Open();
	if (conn.Select_login(conn.db,username,password)>0) {
		cout << "Sign in successfuly!\n";
		id = conn.Select_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		cout << "Sign in fail!\n";
		check = false;
	}
}
void Maccount::SingUp() {
	username = new (char);
	password = new char;
	birth = new char;
	name = new char;
	address = new char;

	cout << "Nhap vao username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	cout << "Nhap sex: ";
	cin >> sex;
	cout << "Nhap birth: ";
	cin >> birth;
	cout << "Nhap name: ";
	cin >> name;
	cout << "Nhap address: ";
	cin >> address;
	Mchat conn;
	conn.Open();
	conn.Insert_Acc(conn.db, username, password,sex,birth,name,address);
}
void Maccount::SignOut() {
	check = false;
	cout << "-----Ban da dang xuat.-------\n";
}
void Maccount::SendMess(int id) {
	if (check) {
		int id2;
		RegisterHotKey(NULL, 1, MOD_ALT | MOD_NOREPEAT, 0x42);//0x42 is 'b'
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				cout<<"WM_HOTKEY received\n";
			}
			else
			{
				cout << "abc";
			}
		}
		cout << "Chon nguoi dung: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Mchat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0) {
			char *mess, *dt;
			mess = new char;
			dt = new char;
			if (!conn.CheckBlock(conn.db, id, id2)) {
				cout << "---------You is blocked by her--------\n";
			}
			else {
				conn.update_tt(conn.db, id, id2);
				cout << "Nhap Tin nhan: \n";
				cin >> mess;
				time_t hientai = time(0);
				dt = ctime(&hientai);
				int tt = 1;
				conn.WriteToMess(conn.db, id, id2, mess, dt,tt);
				conn.ShowMessDetail(conn.db, id, id2);
			}
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowMess(int ID) {
	if (check) {
		Mchat conn;
		conn.Open();
		conn.SelectMess(conn.db, zID);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "Chon nguoi dung: ";
		char *frien;
		frien = new char;
		cin >> frien;
		Mchat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		if (id2 > 0)
			conn.ShowMessDetail(conn.db, id1, id2);
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::ShowFriend(int id) {
	if (check) {
		Mchat conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Maccount::AddFriend(int id) {
	if (check) {
		cout << "Nhap ten nguoi ban muon them: ";
		char *newfr;
		newfr = new char;
		cin >> newfr;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
			if (!conn.CheckFriend(conn.db, id, id2)) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					conn.WriteToFriend(conn.db, id, id2);
					ShowFriend(id);
				}
				else cout << "------You were blocked by her -------\n\n\n";
			}
			else cout << "------You was friend ----------\n\n\n";
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
}
void Maccount::BlockFriend(int id) {
	if (check) {
		cout << "---------Chon nguoi block :(-------- \n";
		char *name;
		name = new char;
		cin >> name;
		Mchat conn;
		conn.Open();
		int id2 = conn.Seach_fr(name);
		if (id2 > 0) {
			conn.BlockFriend(conn.db, id, id2);
			cout << "---------Block Successfuly---------\n";
			conn.ShowFriend(conn.db, id);
		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
