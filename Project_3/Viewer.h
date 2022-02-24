#include <string>
#include <vector>

#include "Board.h"

using namespace std;

class Viewer {
public:
	void homepage();
	void askLoginPassword();
	void askRegUsername();
	void askRegPassword();
	void askRegPasswordAgain();
	void askRegPermission();
	void askBoardName();
	void askBoardIntroduction();
	void askPostTitle();
	void displayPost(Post);
	void askDeleteFloor();
	void askDeleteReason(int);
	void askComment(string);
	void editorForMail(string);
	void showMailContent(string, string, string, string);
	void showMailBox(vector<string>, vector<string>, vector<string>, int);
	void editorForEdit(string title);
	void editor(string title);
	void showBoardList(int, const vector<Board>);
	void game1(int, int, int);
	void game2(int, int, int,int[],int,int,int);
	void game3Init(int, double[]);
	void game3askMoney();
	void game3askTarget();
	void game3Win(vector<int>, int);
	void game3Lose(vector<int>, int);
	void game3Field(int[],int);
	void mailLobby(int);
	void gameLobby(int);
	void askTo();
	void askMailTitle();
	void lobby(int, int);
	void showPostList(int, int, vector<Board>); //index of selected board
	void error(string message);
	void successful(string message);
	void setCursor(short x, short y);
	void clearRow(short x, short y);
	void clearRow(short x, short y,int xCnt);
	void clearRowWhite(short x, short y);
	void askMailSelect();
	void showMailboxList(string currentUserName);
};