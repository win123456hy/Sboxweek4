#include "Chat.h"
#include <sstream>
using namespace std;
Chat::Chat(){
}
Chat::~Chat(){}
void Chat::Open() {
	rc = sqlite3_open("w3.db", &db);
	if (rc) {
		cout << "Can't open database" << sqlite3_errmsg(db) << endl;
		exit(0);
	}else {}
}
void Chat::Close() {
	sqlite3_close(db);
}
int Chat::Select_login(sqlite3 *db, char *us, char *pa) {
	int id = 0;
	szSQL = "SELECT * FROM  user WHERE username = ? and password = ? ";
	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, us, strlen(us), 0);
		sqlite3_bind_text(stmt, 2, pa, strlen(pa), 0);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}

	return id;
}
void Chat::Insert_Acc(sqlite3 *db, char *fn, char *ln,bool se, char *bir, char *na,char *add) {
	szSQL = "insert into user (username, password,gender,birth,name,address) values (?,?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, fn, strlen(fn), 0);
		sqlite3_bind_text(stmt, 2, ln, strlen(ln), 0);
		sqlite3_bind_int(stmt, 3, se);
		sqlite3_bind_text(stmt, 4, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 5, na, strlen(na), 0);
		sqlite3_bind_text(stmt, 6, add, strlen(add), 0);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::Insert_Acc_In_View(sqlite3 *db, int idforview,bool se, char *bir, char *na, char *add) {
	szSQL = "insert into userinview (id,name,gender,birth,address) values (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, idforview);
		sqlite3_bind_text(stmt, 2, na, strlen(na), 0);
		sqlite3_bind_int(stmt, 3, se);
		sqlite3_bind_text(stmt, 4, bir, strlen(bir), 0);
		sqlite3_bind_text(stmt, 5, add, strlen(add), 0);
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
string Chat::GetNamefromID(int id)
{
	string a;
	szSQL = "select name from userinview where id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, id);
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			a=string((const char *)sqlite3_column_text(stmt, 0));
		}
		sqlite3_finalize(stmt);
		
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return a;
}
void Chat::SelectMessTo(sqlite3 *db, int zID) {
	if (!db)return;
	//szSQL = "select messenger.contend,messenger.idrec from messenger,user where user.id=messenger.idsen and user.id=?";
	szSQL = "select contend,name from (select * from messenger where idsen=?) as A left join userinview on(A.idsen=userinview.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout <<"To:"<< string((const char *)sqlite3_column_text(stmt, 1)) << "\t\t Mess:"<<string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		/*	User u;
			int idd = sqlite3_column_int(stmt, 1);
			u.setidu(idd);
			string mss = std::string(reinterpret_cast<const char*>(
				sqlite3_column_text(stmt, 0)
				));
			u.setMess(mss);
			
			listUser.push_back(u);*/
			//answer.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
			/*string mss = std::string(reinterpret_cast<const char*>(
				sqlite3_column_text(stmt, 0)
				));
			u[i].setMess(mss);
			u[i].setTen(GetNamefromID(sqlite3_column_int(stmt, 1)));
			i++;*/
			
		}
		/*int ii = 1;
		for (list<std::string>::const_iterator nn = answer.begin(); nn != answer.end(); nn++) {
			cout << ii << ". " << *nn << endl;
			ii++;
		}*/
		/*for (int j = 0; j < i; j++)
		{
			listUser.push_front(u[i]);
		}*/
		sqlite3_finalize(stmt);
		/*cout << "-----Danh sach tin nhan-------\n";
		
		list<User>::iterator p = listUser.begin();
		while (p != listUser.end()) {
			cout << p->getTen() << " "<< p->getMess() << endl;
			p++;
		}*/
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::SelectMessFrom(sqlite3 *db, int zID) {
	if (!db)return;
	//szSQL = "select messenger.contend,messenger.idrec from messenger,user where user.id=messenger.idsen and user.id=?";
	szSQL = "select contend,name from (select * from messenger where idrec=?) as A left join userinview on(A.idrec=userinview.id)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_int(stmt, 1, zID);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout << "From:" << string((const char *)sqlite3_column_text(stmt, 1)) << "\t\t Mess:" << string((const char *)sqlite3_column_text(stmt, 0)) << endl;
		
		}
		
		sqlite3_finalize(stmt);
		
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
int Chat::GetIDfromName(char *name) {
	int id2 = -1;
	szSQL = "SELECT id FROM user WHERE name = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id2;
}
int Chat::Seach_fr(char *frien) {
	int id2 = -1;
	szSQL = "SELECT id FROM userinview WHERE name = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		sqlite3_bind_text(stmt, 1, frien, strlen(frien), 0);
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> id2;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return id2;
}
void Chat::ShowMessDetail(sqlite3 *db, int id1, int id2,char *namf) {
	if (!db)return;
	cout << "--------Detail--------\n";
	szSQL = "SELECT * FROM messenger,userinview WHERE(idsen = ? OR idsen = ?) AND(idrec = ? OR idrec = ?) and userinview.id = messenger.idsen";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	// cout << id1 << id2;
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id1);
		sqlite3_bind_int(stmt, 4, id2);
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			if (sqlite3_column_int(stmt, 0) == id1) {

				if (sqlite3_column_int(stmt, 4) == 0) {
					cout << "To:" << namf << "	Mess:" << string((const char *)sqlite3_column_text(stmt, 2)) << " - Thoi gian: ";
					cout << string((const char *)sqlite3_column_text(stmt, 3)) <<"\t Da xem."<< endl;
				}
				else {
					cout << "To:" << namf << "	Mess:" << string((const char *)sqlite3_column_text(stmt, 2)) << " - Thoi gian: ";
					cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
				}
			}else if(sqlite3_column_int(stmt, 1) == id1) {
				cout << "From:" << string((const char *)sqlite3_column_text(stmt, 6)) << "	Mess:" << string((const char *)sqlite3_column_text(stmt, 2)) << " - Thoi gian: ";
				cout << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			}
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
bool Chat::CheckFriend(sqlite3 *db, int id1, int id2) {
	int isFriend = 0;
	szSQL = "SELECT * FROM friend WHERE ( id1 = ? AND id2 = ?) OR ( id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, id2);
		sqlite3_bind_int(stmt, 4, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isFriend;
			if (isFriend != 0) isFriend = 1;
			else isFriend = 0;
			sqlite3_finalize(stmt);
		}
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	return isFriend;
}
bool Chat::CheckBlock(sqlite3 *db, int id1, int id2) {
	int isblock = 0;
	if (!db)return 0;
	szSQL = "SELECT isblock FROM friend WHERE (id1 = ? AND id2 = ?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id2);
		sqlite3_bind_int(stmt, 2, id1);
		// commit
		if (sqlite3_step(stmt) == SQLITE_ROW) {
			stringstream str;
			str << sqlite3_column_text(stmt, 0);
			str >> isblock;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	
	return isblock;
}
void Chat::WriteToFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "INSERT INTO friend VALUES (?,?,?),(?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		int isblock = 0;
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_int(stmt, 3, isblock);
		sqlite3_bind_int(stmt, 4, id2);
		sqlite3_bind_int(stmt, 5, id1);
		sqlite3_bind_int(stmt, 6, isblock);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::ShowFriend(sqlite3 *db, int id1) {
	cout << "-------List Friends-----------\n";
	if (!db)return;
	szSQL = "SELECT DISTINCT userinview.name FROM (SELECT * FROM friend where (id1 = ?) AND isblock = 0) as A LEFT JOIN userinview ON (A.id2 = userinview.id) LEFT JOIN messenger on (A.id2=messenger.idrec) order by datetime(time) desc";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		// commit
		int i = 1;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout <<i<<"."<< string((const char *)sqlite3_column_text(stmt, 0)) << endl;
			friendss.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
			i++;
		}
		sqlite3_finalize(stmt);
		cout << "-------------------------------------\n";
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

void Chat::ShowFriendWithAddress(sqlite3 *db, int id1) {
	cout << "-------List Friends-----------\n";
	if (!db)return;
	szSQL = "SELECT DISTINCT address FROM  userinview";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// commit
		int i = 1;
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			thanhpho.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
			i++;
		}
		sqlite3_finalize(stmt);
		
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
	for (list<std::string>::const_iterator it = thanhpho.begin(); it != thanhpho.end(); it++) {
		

		szSQL = "SELECT DISTINCT userinview.name FROM (SELECT * FROM friend where (id1 = ?) AND isblock = 0) as A LEFT JOIN userinview ON (A.id2 = userinview.id) where address=?";
		rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
		if (rc == SQLITE_OK) {
			// bind the value
			sqlite3_bind_int(stmt, 1, id1);
			sqlite3_bind_text(stmt, 2, _strdup((*it).c_str()),strlen(_strdup((*it).c_str())), 0);
			// commit
			





			list<string> namee;
			while (sqlite3_step(stmt) == SQLITE_ROW) {
				namee.push_back(string((const char *)sqlite3_column_text(stmt, 0)));
			}
			if (!namee.empty()) {
				cout << *it << endl;
				int ii = 1;
				for (list<std::string>::const_iterator nn = namee.begin(); nn != namee.end(); nn++) {
					cout <<ii<<". "<< *nn << endl;
					ii++;
				}
			}
			sqlite3_finalize(stmt);

		}
		else {
			cout << "SQL error: " << zErrMsg << endl;
			sqlite3_free(zErrMsg);
		}
	}
}
void Chat::ShowFriendDetail(sqlite3 * db, int id2)
{
	if (!db)return;
	szSQL = "SELECT * FROM  userinview WHERE id=? ";
	rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt,1, id2);
		
		// commit
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			cout <<"Ten:" <<string((const char *)sqlite3_column_text(stmt, 1)) << endl;
			if(string((const char *)sqlite3_column_blob(stmt, 2))=="1")
			cout << "Gioi tinh: Nu" << endl;
			else
				cout << "Gioi tinh: Nam" << endl;
			cout << "Ngay sinh:" << string((const char *)sqlite3_column_text(stmt, 3)) << endl;
			cout << "Dia chi:" << string((const char *)sqlite3_column_text(stmt, 4)) << endl;
		}
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::BlockFriend(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE friend SET isblock = 1 WHERE id1 = ? AND id2 = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::WriteToMess(sqlite3 *db, int id1, int id2, char *mes, char *time,int tt) {
	szSQL = "INSERT INTO messenger VALUES (?,?,?,?,?)";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		sqlite3_bind_text(stmt, 3, mes, strlen(mes), 0);
		sqlite3_bind_text(stmt, 4, time, strlen(time), 0);
		sqlite3_bind_int(stmt, 5, tt);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}

}
void Chat::update_tt(sqlite3 *db, int id1, int id2) {
	if (!db)return;
	szSQL = "UPDATE messenger SET trangthai = 0 WHERE idsen = ? AND idrec = ?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_int(stmt, 1, id1);
		sqlite3_bind_int(stmt, 2, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}
void Chat::UpdateInterfaceFriend(sqlite3 * db, int id2, bool se, char *name, char *birth, char *address)
{
	if (!db)return;
	szSQL = "UPDATE userinview SET name = ?,gender=?,birth=?,address=? where id=?";
	rc = sqlite3_prepare_v2(db, szSQL, strlen(szSQL), &stmt, &pzTest);
	if (rc == SQLITE_OK) {
		// bind the value
		sqlite3_bind_text(stmt, 1, name, strlen(name), 0);
		sqlite3_bind_int(stmt, 2, se);
		sqlite3_bind_text(stmt, 3, birth, strlen(birth), 0);
		sqlite3_bind_text(stmt, 4, address, strlen(address), 0);
		sqlite3_bind_int(stmt, 5, id2);
		// commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		cout << "SQL error: " << zErrMsg << endl;
		sqlite3_free(zErrMsg);
	}
}

