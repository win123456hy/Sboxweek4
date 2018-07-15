#include "stdafx.h"
#include "User.h"
#include <iostream>

using namespace std;


int User::getidu() {
	return idu;
}
string User::getMess() {
	return mess;
}


void User::setidu(int ten) {
	idu = ten;
}

void User::setMess(string messs) {
	mess = messs;
}

User::User()
{

}



User::~User()
{
}
