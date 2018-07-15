// chat_sqlite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdc++.h>
#include <windows.h> //  dung cho clrscr
#include "Maccount.h"

using namespace std;
//ham xoa man hinh
void clrscr()
{
	COORD origin = { 0, 0 };
	unsigned long len;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned long size;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(handle, TEXT(' '), size, origin, &len);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, origin, &len);
	SetConsoleCursorPosition(handle, origin);
}
int main()
{
	Maccount us = Maccount();
	while (1) {
		cout << "-------Chon chuc nang: ------\n"
			"1.Dang nhap\n"
			"2.Dang ky\n"
			"3.Hien thi tin nhan\n"
			"4.Hien thi chi tiet tin nhan\n"
			"5.Gui tin nhan\n"
			"6.Them ban be\n"
			"7.Hien thi ban be\n"
			"8.Block\n"
			"9.Dang xuat\n"
			"-----------------------\n";
		cout << "ban chon so: ";
		char choose;
		cin >> choose;
		switch (choose) {
			case '1':
				clrscr();
				us.SignIn();
				break;
			case '2':
				clrscr();
				us.SingUp();
				break;
			case '3':
				clrscr();
				us.ShowMess(us.id);
				break;
			case '4':
				clrscr();
				us.ShowMessDetail(us.id);
				break;
			case '5':
				clrscr();
				us.SendMess(us.id);
				break;
			case '6':
				clrscr();
				us.AddFriend(us.id);
				break;
			case '7':
				clrscr();
				us.ShowFriend(us.id);
				break;
			case '8':
				clrscr();
				us.BlockFriend(us.id);
				break;
			case '9':
				us.SignOut();
				break;
			default:
				cout << "Xin moi nhap lai\n";
				break;
		}
	}
	return 0;
}

