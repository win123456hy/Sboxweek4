#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <windows.h> // clrscr xóa màn hình
#include "Account.h"
#include<string>
using namespace std;
// xoa man hinh
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
void hien() {

}

int main()
{
	
	Account us = Account();
	//clrscr();
	//us.SignIn();
	//int choose = 1;
	//enum { ONE_KEYID = 1, TWO_KEYID = 2 };

	//ShowWindow(hw, SW_HIDE);
	/*HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);*/
	
	while (1) {
		clrscr();
		cout << "-------Chon chuc nang: ------\n"
			"1.Dang nhap\n"
			"2.Dang ky\n"
			"3.Hien thi tin nhan\n"
			"4.Hien thi chi tiet tin nhan\n"
			"5.Gui tin nhan\n"
			"6.Them ban be\n"
			"7.Hien thi ban be\n"
			"8.Sua thong tin ban be\n"
			"9.Block\n"
			"10.Dang xuat\n"
			"-----------------------\n";

		cout << "Ban chon so: ";
		int choose;
		//cin >> choose;
		/*HWND hwnd = GetConsoleWindow();
		ShowWindow(hwnd, SW_HIDE);*/
		//RegisterHotKey(NULL, ONE_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x42); // register 1 key as hotkey
		//RegisterHotKey(NULL, TWO_KEYID, MOD_CONTROL | MOD_NOREPEAT, 0x4E); // register 2 key as hotkey
		//MSG msg;
		//while (GetMessage(&msg, 0, 0, 0))
		//{
		//	PeekMessage(&msg, 0, 0, 0, 0x0001);
		//	switch (msg.message)
		//	{
		//	case WM_HOTKEY:
		//		if (msg.wParam == ONE_KEYID)
		//		{
		//			choose--;
		//			goto play;
		//		}
		//		else if (msg.wParam == TWO_KEYID)
		//		{
		//			choose++;
		//			goto play;
		//		}
		//	}
		//}
		
		
		
		
		
		/*play:*/
		cin >> choose;
		switch (choose) {
			case 1:
				clrscr();
				cout << "Dang nhap"<<endl;
				us.SignIn();
				break;
			case 2:
				clrscr();
				cout << "Dang ky" << endl;
				us.SingUp();
				break;
			case 3:
				clrscr();
				us.ShowMess(us.id);
				break;
			case 4:
				clrscr();
				us.ShowMessDetail(us.id);
				break;
			case 5:
				clrscr();
				us.SendMess(us.id);
				break;
			case 6:
				clrscr();
				us.AddFriend(us.id);
				break;
			case 7:
				clrscr();
				us.ShowFriend(us.id);
				break;
			case 8:
				clrscr();
				us.UpdateFriend(us.id);
				break;
			case 9:
				clrscr();
				us.BlockFriend(us.id);
				break;
			case 10:
				clrscr();
				us.SignOut();
				break;
			default:
				cout << "Fall !! Xin moi nhap lai\n";
				break;
		}
	}
	return 0;
}

