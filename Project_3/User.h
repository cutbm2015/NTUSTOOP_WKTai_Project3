
#include <vector>
#include <iostream>

using namespace std;

class User {

public:

	User();

	User createAccount(string username, string password,int permission);
	User createAccount();
	User guestIn();
	int userLogin(string username);
	int userLogin();

	bool isUserExist(string);
	bool isUserExist(string, string &pswd);

	vector<int> postsID; //req

	//private data process
	void setUserName(string);
	string getUserName();
	void setUserPswd(string);
	string getUserPswd();
	void setUserPermission(int);
	int getUserPermission();


	virtual bool isGuest() { return false; };
	virtual bool isUser() { return false; };
	virtual bool isAdmin() { return false; };

protected:
	string userName;
	string userPswd;
	int userPermission; //req
	vector<int> postID; //req
};
class Adiministrator : public User {
public:
	Adiministrator(string username, string password, int permission) {
		this->userName = username;
		this->userPswd = password;
		this->userPermission = permission;
	}
	bool isAdmin() {
		return true;
	};
};
class Member : public User {
public:
	Member(string username, string password, int permission) {
		this->userName = username;
		this->userPswd = password;
		this->userPermission = permission;
	}
	bool isUser() {
		return true;
	};
};
class Guest : public User {
public:
	Guest(string username, string password, int permission) {
		this->userName = username;
		this->userPswd = password;
		this->userPermission = permission;
	}
	bool isGuest(){
		return true;
	};
};