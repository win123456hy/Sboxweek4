#include "Account.h"
#include "Chat.h"
#include<stdio.h>
#include <iostream>
#include <windows.h>
#include<conio.h>
#include <ctime>
using namespace std;


Account::Account(){}
Account::~Account(){}
void Account::SignIn() {
	username = new (char);
	password = new (char);

	cout << "Nhap username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	Chat conn;
	conn.Open();
	if (conn.Select_login(conn.db,username,password)>0) {
		cout << "Successfuly !\n";
		id = conn.Select_login(conn.db, username, password);
		check = true;
		zID = id;
	}
	else {
		cout << "Sign in fail!\n";
		check = false;
	}
	conn.Close();
}
void Account::SingUp() {
	Chat conn;
	conn.Open();
	username = new (char);
	password = new char;
	birth = new char;
	char name[50];
	char address[100];

	cout << "Nhap username: ";
	cin >> username;
	cout << "Nhap password: ";
	cin >> password;
	cout << "Nhap gender: ";
	cin >> gender;
	cout << "Nhap birth: ";
	cin >> birth;
	cin.ignore();
	cout << "Nhap name: ";
	cin.getline(name,50);
	cout << "Nhap place:";
	cin.getline(address, 100);
	
	conn.Insert_Acc(conn.db, username, password,gender,birth,name, address);
	conn.Close();
	conn.Open();
	int idforview=conn.GetIDfromName(name);
	conn.Close();
	conn.Open();
	conn.Insert_Acc_In_View(conn.db, idforview, gender, birth, name, address);
	conn.Close();
}
void Account::SignOut() {
	check = false;
	id = zID = -1;
	cout << "-----Ban da dang xuat.-------\n";
}
void nhaptheodanhsach(int id) {
	Chat conn;
	conn.Open();
	int id2;
	RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x4C);//0x4C is 'L'
	MSG msg = { 0 };
	if (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			//hien thi danh sach ban be
			conn.ShowFriend(conn.db, id);
			conn.Close();
			//cout<<"WM_HOTKEY received\n";
		}
		else
		{
			cout << "abc";
		}
	}
	cout << "Chon nguoi dung: ";
	char *frien;
	frien = new char;
	int inputi;
	cin >> inputi;
	for (list<std::string>::const_iterator it = conn.friendss.begin(); it != conn.friendss.end(); it++)
	{

		advance(it, inputi - 1);
		frien = _strdup((*it).c_str());
		break;

	}
	/*char *frien;
	frien = new char;
	cin >> frien;*/
	conn.Open();
	id2 = conn.Seach_fr(frien);
	conn.Close();
	if (id2 > 0) {
		char *mess, *dt;
		mess = new char;
		dt = new char;
		conn.Open();
		if (conn.CheckBlock(conn.db, id, id2)) {
			cout << "---------You is blocked by her--------\n";
			conn.Close();
		}
		else {
			conn.update_tt(conn.db, id, id2);
			cout << "Nhap Tin nhan: \n";
			cin >> mess;
			time_t hientai = time(0);
			//dt = ctime(&hientai);
			strftime(dt, 20, "%Y-%m-%d %H:%M:%S", localtime(&hientai));
			int tt = 1;
			conn.Close();
			conn.Open();
			conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
			cout << "To:" << frien << endl;
			conn.Close();
			conn.Open();
			conn.ShowMessDetail(conn.db, id, id2,frien);
			conn.Close();
		}
	}
	else cout << "----Tai khoan khong ton tai-----------\n";
}
void nhaptheotennguoidung(int id) {
	Chat conn;
	conn.Open();
	int id2;
	
	cout << "Nhap nguoi dung: ";
	
	
	char frien[50];
	cin.ignore();
	cin.getline(frien,50);

	id2 = conn.Seach_fr(frien);
	conn.Close();
	conn.Open();
	if (id2 > 0) {
		char *mess, *dt;
		mess = new char;
		dt = new char;
		
		if (conn.CheckBlock(conn.db, id, id2)) {
			cout << "---------You is blocked by her--------\n";
			conn.Close();
		}
		else {
			conn.Close();
			conn.Open();
			conn.update_tt(conn.db, id, id2);
			conn.Close();
			cout << "Nhap Tin nhan: \n";
			cin >> mess;
			time_t hientai = time(0);
			//dt = ctime(&hientai);
			strftime(dt, 20, "%Y-%m-%d %H:%M:%S", localtime(&hientai));
			int tt = 1;
			conn.Open();
			conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
			cout << "To:" << frien << endl;
			conn.Close();
			conn.Open();
			conn.ShowMessDetail(conn.db, id, id2,frien);
			conn.Close();
		}
	}
	else cout << "----Tai khoan khong ton tai-----------\n";
	conn.Close();
}
void Account::SendMess(int id) {

	if (check) {
		cout << "Chon phuong thuc ban muon nhap:" << endl;
		cout << "1.Nhap ten nguoi dung." << endl;
		cout << "2.Chon theo danh sach ban be." << endl;
		cout << "Ban chon:";
		int chonn;
		cin >> chonn;
		switch (chonn)
		{
		case 1: nhaptheotennguoidung(id); break;
		case 2:
			cout << "Bam Ctrl+L de hien ra danh sach:";
			nhaptheodanhsach(id); break;

		default:
			break;
		}
	}

	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Account::ShowMess(int ID) {
	if (check) {
		Chat conn;
		cout << "1. Xem tin nhan gui";
		cout << "2. Xem tin nhan den";
		cout << "Ban chon:";
		int chon;
		cin >> chon;
		switch (chon)
		{
		case 1: {
			conn.Open();
			conn.SelectMessTo(conn.db, zID);
			conn.Close();
			cin.get();
			cin.get();

			break; }
		case 2: {
			conn.Open();
			conn.SelectMessFrom(conn.db, zID);
			conn.Close();
			cin.get();
			cin.get();

			break;
		}
		default:
			break;
		}
	
		
		
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Account::ShowMessDetail(int id1) {
	if (check) {
		int id2;
		cout << "Chon nguoi dung: ";
		char frien[50];
		cin.ignore();
		cin.getline(frien, 50);
	Chat conn;
		conn.Open();
		id2 = conn.Seach_fr(frien);
		conn.Close();
		if (id2 > 0) {
			conn.Open();
			conn.ShowMessDetail(conn.db, id1, id2,frien);
			conn.Close();
			conn.Open();
			conn.update_tt(conn.db, id2, id1);
			RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x52);//0x52 is 'R'
			MSG msg = { 0 };
		label:
			conn.Open();
			while (true) {
				cout << "Ctrl+R de gui tin nhan:" << endl;
				if (GetMessage(&msg, NULL, 0, 0) != 0)
				{
					if (msg.message == WM_HOTKEY)
					{
						char *mess, *dt;
						mess = new char;
						dt = new char;
						cout << "Nhap Tin nhan: \n";
						cin >> mess;
						time_t hientai = time(0);
						//dt = ctime(&hientai);
						strftime(dt, 20, "%Y-%m-%d %H:%M:%S", localtime(&hientai));
						int tt = 1;
						conn.WriteToMess(conn.db, id, id2, mess, dt, tt);
						conn.Close();
						cout << "Da gui tin nhan"<<endl;
						cout << "Nhan 1 de quay lai. phim bat ki de tiep tuc." << endl;
						cin.get();
						int c; c=_getch();
						if (c == 1)
							break;
						else
							goto label;
					}

				}
			}
			cin.get();

		}
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Account::ShowFriend(int id) {
	if (check) {
		Chat conn;
		conn.Open();
		conn.ShowFriend(conn.db, id);
		sqlite3_close_v2(conn.db);
		conn.Open();
		cout << "(Ctrl+C) de sap xep ban theo thanh pho." << endl;
		RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x43);//0x43 is 'C'
		MSG msg = { 0 };
		if (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY)
			{
				//hien thi danh sach ban be theo dia chi
				conn.ShowFriendWithAddress(conn.db, id);
				conn.Close();
				conn.Open();
				int id2;
				cout << "Nhap ten nguoi dung can xem thong tin: ";
				char frien[50];
				cin.ignore();
				cin.getline(frien, 50);
				
				id2 = conn.Seach_fr(frien);
				conn.Close();
				conn.Open();
				if (id2 > 0) {
					conn.ShowFriendDetail(conn.db, id2);
					conn.Close();
				}
				cout << "-----------------------------------------------------------------" << endl;
				cout << "Ban co muon gui tin nhan cho nguoi nay?(Y/N):";
				char ch;
				cin >> ch;
				conn.Close();
				conn.Open();
				if (ch == 'y')
				{
					SendMess(id);
				}
				else {}
				//cout<<"WM_HOTKEY received\n";
			}
			
		}
		
	}
	else {
		cout << "----------Ban chua dang nhap.--------\n\n";
	}
}
void Account::AddFriend(int id) {
	if (check) {
		cout << "Nhap ten nguoi ban muon them: ";
		char newfr[50];
		cin.ignore();
		cin.getline(newfr,50);
		Chat conn;
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
void Account::BlockFriend(int id) {
	if (check) {
		cout << "---------Chon nguoi block :(-------- \n";
		char name[50];
		cin.ignore();
		cin.getline(name,50);
		Chat conn;
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
void Account::UpdateFriend(int)
{
	if (check) {
		cout << "Nhap ten nguoi ban muon sua: ";
		char newfr[50];
		cin.ignore();
		cin.getline(newfr, 50);
		Chat conn;
		conn.Open();
		int id2 = conn.Seach_fr(newfr);
		if (id2 > 0) {
				if (!conn.CheckBlock(conn.db, id, id2)) {
					char *birthd = new char;
					char namee[50];
					char addresss[100];
					bool genderr;
					cout << "Nhap gender: ";
					cin >> genderr;
					cout << "Nhap birth: ";
					cin >> birthd;
					cin.ignore();
					cout << "Nhap name: ";
					cin.getline(namee, 50);
					cout << "Nhap place:";
					cin.getline(addresss, 100);
					conn.UpdateInterfaceFriend(conn.db,id2,genderr,namee,birthd,addresss);
					cout << "Sua thanh cong!";
					conn.Close();
				}
				else cout << "------You were blocked by her -------\n\n\n";
			}
		
		else cout << "----Tai khoan khong ton tai-----------\n";
	}
	else cout << "----------Ban chua dang nhap.--------\n\n";
}

