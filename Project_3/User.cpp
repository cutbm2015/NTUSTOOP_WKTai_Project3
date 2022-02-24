#include "User.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

vector<User> users;

#define MAILBOXPATH "C:/Users/User/Desktop/program_project3/Project_3/mailbox"


User::User() {
	userName = "";
	userPswd = "";
	userPermission = -1;
}

//抓出所有user資料至users中
void getData() {
	users.clear();
	ifstream ifs;

	ifs.open("userData.txt", ios::in);

	if (!ifs)
		cout << "Can't open userData.txt.(ifs)" << endl;
	else {

		User userTmp;
		string tmpS;
		int tmpI;

		while (!ifs.eof()) {
			ifs >> tmpS;
			userTmp.setUserName(tmpS);
			ifs >> tmpS;
			userTmp.setUserPswd(tmpS);
			ifs >> tmpI;
			userTmp.setUserPermission(tmpI);

			users.push_back(userTmp);
		}

	}

	ifs.close();
}

//call 之前要先自己做帳號是否已存在的檢查
User User::createAccount(string username, string password, int permission) {

	User userTmp;

	userTmp.userName = username;
	userTmp.userPswd = password;
	userTmp.userPermission = permission;


	//write into userData.txt
	ofstream ofs;

	ofs.open("userData.txt", ios::app);	//從末尾開始寫入
	if (!ofs)
		cout << "Can't open userData.txt.(ofs)" << endl;
	else {
		ofs << "\n" << username << "\n" << password << "\n" << permission;
	}

	ofs.close();

	//write into userDataList.txt
	ofs.open("userDataList.txt", ios::app);	//從末尾開始寫入
	if (!ofs)
		cout << "Can't open userDataList.txt.(ofs)" << endl;
	else {
		ofs << "\n" << username;
	}

	ofs.close();

	//create mailbox
	/*string path = MAILBOXPATH; 
	ofstream ofs2(path + "/" + username + ".txt");

	if (!ofs2)  //創建失敗	**不該發生
		cout << "create mailbox failed.";
	
	ofs2.close(); 

	//create mailboxList
	ofstream ofs3(path + "/" + username + "List.txt");

	if (!ofs3)  //創建失敗	**不該發生
		cout << "create mailboxList failed.";

	ofs3.close();*/

	//postsID GET
	ifstream ifs;
	int postIndex = 2;
	bool keepRead = true;
	while (keepRead) {
		ifs.open("Post/" + to_string(postIndex) + ".txt", ios::in);
		if (!ifs) {
			keepRead = false;
		}
		else {
			string temp_str;
			vector<string> temp;
			while (!ifs.eof() && temp.size() < 3) {
				getline(ifs, temp_str);
				temp.push_back(temp_str);
			}
			if (temp.size() == 3) {
				if (temp[2] == username) {
					userTmp.postID.push_back(postIndex);
				}
			}
			else {
				keepRead = false;
			}
			postIndex++;
		}
		ifs.close();
	}

	return userTmp;

}

//call 之前要先自己檢查username跟password是否合法(此member function只負責回傳index)
int User::userLogin(string username) {

	getData();

	for (int i = 0; i < users.size(); i++) 
		if (users[i].userName == username) 
			return i;


	cout << "No match";		//不應該發生

}

//不會將資料寫入 userData.txt
User User::guestIn() {
	User userTmp;

	userTmp.userName = "guest";
	userTmp.userPswd = "guest";
	userTmp.userPermission = 0;

	return userTmp;
}

bool User::isUserExist(string nameIn) {

	getData();

	for (int i = 0; i < users.size(); i++) {
		if (nameIn == users[i].userName)
			return true;
	}

	return false;

}
//return false 時 pswd會設為空 ("")
bool User::isUserExist(string nameIn,string &pswd) {

	getData();

	for (int i = 0; i < users.size(); i++) {
		if (nameIn == users[i].userName) {
			pswd = users[i].userPswd;
			return true;
		}
			
	}

	pswd = " ";
	return false;

}

//private data process
void User::setUserName(string s) {
	userName = s;
}
string User::getUserName() {
	return userName;
}
void User::setUserPswd(string s) {
	userPswd = s;
}
string User::getUserPswd() {
	return userPswd;
}
void User::setUserPermission(int i) {
	userPermission = i;
}
int User::getUserPermission() {
	return userPermission;
}/*
bool User::isGuest() {
	if (userPermission == 0)
		return true;
	return false;
}
bool User::isUser() {
	if (userPermission == 1)
		return true;
	return false;
}
bool User::isAdmin() {
	if (userPermission == 2)
		return true;
	return false;
}

*/



//未使用
/*
User User::createAccount() {

	getData();

	User userTmp;
	string tmpS1, tmpS2;
	int tmpI;

	cout << "Enter your username." << endl;
	cin >> tmpS1;

	//check if username has existed
	bool existFlag;
	while (1) {
		existFlag = false;

		for (int i = 0; i < users.size(); i++) {
			if (tmpS1 == users[i].userName) {
				existFlag = true;
				break;
			}
		}

		if (!existFlag) {
			break;
		}
		else {
			cout << "This username has existed.Please enter again." << endl;
			cin >> tmpS1;
		}
	}
	userTmp.userName = tmpS1;

	cout << "Enter your password." << endl;
	cin >> tmpS2;
	userTmp.userPswd = tmpS2;

	cout << "Enter your permission.('1' to be user , '2' to be administration)." << endl;
	while (1) {
		cin >> tmpI;
		if (tmpI != 1 && tmpI != 2)
			cout << "Please enter again." << endl;
		else
			break;
	}
	userTmp.userPermission = tmpI;
	cout << "Create successfully!" << endl;


	//write into txt
	ofstream ofs;

	ofs.open("userData.txt", ios::app);	//從末尾開始寫入
	if (!ofs)
		cout << "Can't open userData.txt.(ifs)" << endl;
	else {
		ofs << "\n" << tmpS1 << "\n" << tmpS2 << "\n" << tmpI;
	}

	ofs.close();



	return userTmp;

}

int User::userLogin() {
	getData();

	string tmpS;
	int tmpI;
	int index;

	cout << "Enter your username." << endl;
	cin >> tmpS;

	bool matchFlag;
	while (1) {
		matchFlag = false;

		for (int i = 0; i < users.size(); i++) {
			if (users[i].userName == tmpS) {
				matchFlag = true;
				index = i;
				break;
			}
		}

		if (matchFlag)
			break;
		else {
			cout << "This account doesn't exist.Please enter again." << endl;
			cin >> tmpS;
		}
	}

	cout << "Enter your password." << endl;
	cin >> tmpS;

	while (1) {

		if (tmpS == users[index].userPswd) {
			cout << "Login successfully!" << endl;
			return index;
		}
		else {
			cout << "The password is incorrect.Please try again." << endl;
			cin >> tmpS;
		}

	}

}*/