#include "Viewer.h"
#include "User.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

#define MSGLINE1 51
#define MSGLINE2 52
#define LOBBY_OPTIONS 4
#define BOARD_SHOW_HOW_MANY 20
#define POST_SHOW_HOW_MANY 20

#define POPU_RED 5
#define POPU_BLUE 10
#define POPU_PURPLE 15

HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD originCOORD = { 0,0 };
COORD messageLine1 = { 0, MSGLINE1 };
COORD messageLine2 = { 0, MSGLINE2 };
enum colour { black, blue, green, red, yellow, yellow_darken, white, grey, blue_darken };
void changeColor(int backcolour = black) {
	HANDLE handle;

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
/*/
	switch (backcolour) {
	case black:
		backcolour = BACKGROUND_BLUE & BACKGROUND_GREEN & BACKGROUND_RED;
		break;
	case blue:
		backcolour = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case green:
		backcolour = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case red:
		backcolour = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case yellow:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case yellow_darken:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case white:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case grey:
		backcolour = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case blue_darken:
		backcolour = BACKGROUND_BLUE;
		break;
	}*/
	SetConsoleTextAttribute(handle, backcolour);

};
void Viewer::askTo() {
	system("cls");
	cout << "請輸入收件者ID, 或輸入'!'離開: ";
}
void Viewer::askMailTitle() {
	system("cls");
	cout << "信件標題以30字為限, 超出字符將被截斷, 中文以兩字計算。\n";
	cout << "請輸入信件標題: ";
}
void resetColor() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED |
		FOREGROUND_GREEN |
		FOREGROUND_BLUE |
		FOREGROUND_INTENSITY);
	return;
}
void Viewer::homepage() {
	resetColor();
	system("cls");
	changeColor(15);
	cout << endl << endl << endl <<
		"　　　　　　　　　███╗   ███╗ ██╗   ██╗ ██████╗ ████████╗████████╗" << endl <<
		"　　　　　　　　　████╗ ████║ ╚██╗ ██╔╝ ██╔══██╗╚══██╔══╝╚══██╔══╝" << endl <<
		"　　　　　　　　　██╔████╔██║  ╚████╔╝  ██████╔╝   ██║      ██║" << endl <<
		"　　　　　　　　　██║╚██╔╝██║   ╚██╔╝   ██╔═══╝    ██║      ██║" << endl <<
		"　　　　　　　　　██║ ╚═╝ ██║    ██║    ██║        ██║      ██║" << endl <<
		"　　　　　　　　　╚═╝     ╚═╝    ╚═╝    ╚═╝        ╚═╝      ╚═╝" << endl;
	cout << endl << endl;
	cout << "　　　　輸入使用者代號，或以 new 註冊，或以 guest 參觀 ";
	changeColor(240);
	cout << "　　　　　　　　　　" << endl;

}
void Viewer::askRegUsername() {
	
	resetColor();
	cout << "請輸入帳號 ";
	changeColor(240);
	cout << "　　　　　　　　　　" << endl;
	SetConsoleCursorPosition(hStdout, { 55,12 });
	//resetColor();

}
void Viewer::askRegPassword() {
	SetConsoleCursorPosition(hStdout, { 0,13 });
	resetColor();
	cout << "　　　　　　　　　　　　　　　　　　　　　　請輸入密碼 ";
	changeColor(240);
	cout << "　　　　　　　　　　" << endl;
	SetConsoleCursorPosition(hStdout, { 55,13 });
	//resetColor();
}
void Viewer::askRegPasswordAgain() {
	SetConsoleCursorPosition(hStdout, { 0,14 });
	resetColor();
	cout << "　　　　　　　　　　　　　　　　　　　　　　請再次輸入 ";
	changeColor(240);
	cout << "　　　　　　　　　　" << endl;
	SetConsoleCursorPosition(hStdout, { 55,14 });
	//resetColor();
}
void Viewer::askRegPermission() {

	resetColor();
	cout << "請輸入權限 ";
	changeColor(240);
	cout << "　　　　　　　  　　" << endl;
	SetConsoleCursorPosition(hStdout, { 55,14 });
}
void Viewer::askLoginPassword() {
	resetColor();
	cout << "請輸入密碼 ";
	changeColor(240);
	cout << "　　　　　　　　　　" << endl;
	SetConsoleCursorPosition(hStdout, { 55,12 });
	//resetColor();
}
void Viewer::error(string message) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	cout << "\r";		//清空error欄位
	cout.flush();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	changeColor(79);
	cout << message;
	resetColor();
	if (message == "This account doesn't exist.Please enter again.") {
		resetColor();
		setCursor(55, 11);
		changeColor(240);
		cout << "　　　　　　　　　　" << endl;
	}
}
void Viewer::successful(string message) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	cout << "\r";		//清空error欄位
	cout.flush();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	changeColor(175);
	cout << message;
	resetColor();
}
void Viewer::setCursor(short x, short y) {
	SetConsoleCursorPosition(hStdout, { x,y });
}
//清除完成後會將cursor移回座標(x,y)
void Viewer::clearRow(short x, short y) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { x,y });
	cout << "                                                                                                                                                 ";
	SetConsoleCursorPosition(hStdout, { x,y });
}
//清除完成後會將cursor移回座標(x,y)
void Viewer::clearRowWhite(short x, short y) {
	changeColor(240);
	SetConsoleCursorPosition(hStdout, { x,y });
	cout << "　　　　　　　　　　";
	SetConsoleCursorPosition(hStdout, { x,y });
	//resetColor();
}
//清除完成後會將cursor移回座標(x,y)
void Viewer::clearRow(short x, short y, int xCnt) {
	SetConsoleCursorPosition(hStdout, { x,y });
	for (int i = 0; i < xCnt; i++)
		cout << " ";
	SetConsoleCursorPosition(hStdout, { x,y });
}

void Viewer::lobby(int options, int permission) {
	//可以選看板 信箱 管理員可以選創看板
	system("cls");
	cout << endl << endl << "            主選單" << endl << endl;
	cout << "            [↑][↓]選取 [→]進入\n\n";
	options = (options < 0 ? -options : options);
	if (permission == 2) {
		options = options % 5;
		for (int i = 0; i <= 4; ++i) {
			//hight light
			if (i == options) {
				cout << "            ●";
			}
			else {
				cout << "            　";
			}
			//有甚麼功能
			if (i == 0) {
				cout << "(B)oard  【所有看板】" << endl;
			}
			else if (i == 1) {
				cout << "(M)ail   【我的郵箱】" << endl;
			}
			else if (i == 2) {
				cout << "(C)reate 【創建看板】" << endl;
			}			
			else if (i == 3) {
				cout << "(G)ame   【小　遊戲】" << endl;
			}
			else if (i == 4) {
				cout << "(L)ogout 【登　　出】" << endl;
			}
		}
	}
	else if (permission==1) {
		options = options % 4;
		for (int i = 0; i <= 3; ++i) {
			//hight light
			if (i == options) {
				cout << "            ●";
			}
			else {
				cout << "            　";
			}
			//有甚麼功能
			if (i == 0) {
				cout << "(B)oard  【所有看板】" << endl;
			}
			else if (i == 1) {
				cout << "(M)ail   【我的郵箱】" << endl;
			}			
			else if (i == 2) {
				cout << "(G)ame   【小　遊戲】" << endl;
			}
			else if (i == 3) {
				cout << "(L)ogout 【登　　出】" << endl;
			}
		}
	}
	else if (permission==0) {
		options = options % 3;
		for (int i = 0; i <= 2; ++i) {
			//hight light
			if (i == options) {
				cout << "            ●";
			}
			else {
				cout << "            　";
			}
			//有甚麼功能
			if (i== 0) {
				cout << "(B)oard  【所有看板】" << endl;
			}		
			else if (i == 1) {
				cout << "(G)ame   【小　遊戲】" << endl;
			}
			else if (i == 2) {
				cout << "(L)ogout 【登　　出】" << endl;
			}
		}
	}
}
void Viewer::mailLobby(int options) {
	system("cls");
	cout << endl << endl << "            信件系統" << endl << endl;
	cout << "            [↑][↓]選取 [←]返回 [→]進入\n\n";
	options = (options < 0 ? -options : options);
	options = options % 2;
	for (int i = 0; i <= 1; ++i) {
		//hight light
		if (i == options) {
			cout << "            ●";
		}
		else {
			cout << "            　";
		}
		//有甚麼功能
		if (i == 0) {
			cout << "(M)ail  【收件夾】" << endl;
		}
		else if (i == 1) {
			cout << "(S)end  【發信區】" << endl;
		}
	}
}
void Viewer::gameLobby(int options) {
	system("cls");
	cout << endl << endl << "            選擇遊戲" << endl << endl;
	cout << "            [↑][↓]選取 [←]返回 [→]進入\n\n";
	options = (options < 0 ? -options : options);
	options = options % 3;
	for (int i = 0; i <= 2; ++i) {
		//hight light
		if (i == options) {
			cout << "            ●";
		}
		else {
			cout << "            　";
		}
		//有甚麼功能
		if (i == 0) {
			cout << " 終極密碼" << endl;
		}
		else if (i == 1) {
			cout << " 賭大小" << endl;
		}
		else if (i == 2) {
			cout << " 賽馬場" << endl;
		}
	
	}
}
void Viewer::game1(int min, int max, int attempt) {
	system("cls");
	cout << endl << endl << "            終極密碼(使用鍵盤進行猜測, 輸入-1可離開遊戲)" << endl << endl;
	cout << endl << endl << "            當前最小值: " << min << endl << endl;
	cout << endl << endl << "            當前最大值: " << max << endl;
	cout << endl << endl << "            嘗試次數: " << attempt << endl;
	cout << endl << endl << "            您的猜測: ";
}
void Viewer::game2(int moneyHave,int type,int moneyBet,int dice[],int winner,int diceGuess1,int diceGuess2) {
	system("cls");
	cout << endl << endl << "            賭大小(允許負債)" << endl << endl;
	cout << endl << endl << "            下注類型及賠率: [1]大:1賠1 ; [2]小:1賠1 ; [3]兩顆骰子:1賠5 ; [4]雙骰:1賠8 ; [5]圍骰:1賠150 ; [6]全圍:1賠24 ; [-1]離開" << endl;
	cout << endl << endl << "            剩餘金額: " << moneyHave << endl << endl;
	
	if (type == 1) 
		cout << endl << endl << "            下注類型: 大" << endl;
	else if (type == 2) 
		cout << endl << endl << "            下注類型: 小" << endl;
	else if (type == 3) {
		if (diceGuess1 == -1 && diceGuess2 == -1)
			cout << endl << endl << "            下注類型: 兩顆骰子        骰子1點數:        骰子2點數: " << endl;
		else if (diceGuess1 != -1 && diceGuess2 != -1)
			cout << endl << endl << "            下注類型: 兩顆骰子        骰子1點數: " << diceGuess1 << "        骰子2點數: " << diceGuess2 << endl;
		else if(diceGuess1 != -1 && diceGuess2 == -1)
			cout << endl << endl << "            下注類型: 兩顆骰子        骰子1點數: " << diceGuess1 << endl;
	}
	else if (type == 4) {
		if (diceGuess1 == -1)
			cout << endl << endl << "            下注類型: 雙骰        骰子點數: " << endl;
		else
			cout << endl << endl << "            下注類型: 雙骰        骰子1點數: " << diceGuess1 << endl;
	}	
	else if (type == 5) {
		if (diceGuess1 == -1)
			cout << endl << endl << "            下注類型: 圍骰        骰子點數: " << endl;
		else
			cout << endl << endl << "            下注類型: 圍骰        骰子1點數: " << diceGuess1 << endl;
	}
	else if (type == 6)
		cout << endl << endl << "            下注類型: 全圍" << endl;
	else if (type == -1) 
		cout << endl << endl << "            下注類型: " << endl;
	
		
	if (moneyBet == -1)
		cout << endl << endl << "            下注金額: " << endl;
	else
		cout << endl << endl << "            下注金額: " << moneyBet << endl;

	if (dice[0] != -1) {
		cout << endl << endl << "            擲骰結果: ";

		for (int i = 0; i <= 2; i++) {
			if (i != 2)
				cout << dice[i] << ',';
			else
				cout << dice[i];
		}	
	}
	else
		cout << endl << endl << "            擲骰結果: ";

	if (winner == -1)
		cout << endl << endl << endl << "            贏家: ";
	else if (winner == 0)
		cout << endl << endl << endl << "            贏家: 莊家";
	else
		cout << endl << endl << endl << "            贏家: 閒家";

}
//options = 當前選第幾個?
void Viewer::showBoardList(int options, vector<Board> boards) {
	
	int BOARD_AMOUNT = boards.size();
	int show_cnt = 0; //已經show了幾個看板
	int show_idx = (options > BOARD_SHOW_HOW_MANY?options-BOARD_SHOW_HOW_MANY:0); //show index
	//可以選看板 信箱 管理員可以選創看板
	system("cls");
	
	cout <<endl << endl << "            ";
	changeColor(27); 
	cout << "【看板列表】";
	resetColor();
	cout << endl << "            [←]回上層 [→]進入 [↑↓]選擇 [d]刪除看板" << endl;
	cout << endl << "            編號\t看板        \t中文敘述                                   \t人氣\t閱覽" << endl  << endl;
	cout << std::resetiosflags(std::ios::showbase);

	int boardCnt = 0;
	int boardAmountLimit = boards.size();

	while (show_cnt <= BOARD_SHOW_HOW_MANY) {

		boardCnt++;
		if (boardCnt > boardAmountLimit) {
			break;
		}
		//hight light
		if (show_idx == options) {
			cout << "            ●";
		}
		else {
			cout << "              ";
			//cout << "              　";
		}
		//有甚麼功能
		int popu_temp = boards[show_idx].getPopularity();
		cout << left << setw(3) << (show_idx + 1) << "\t" << setw(13) << boards[show_idx].getName() << "\t" << setw(40) << boards[show_idx].getIntroduction() << "\t";
		if (popu_temp > POPU_PURPLE) {
			changeColor(13);
			cout << "爆";
		}
		else if (popu_temp > POPU_BLUE) {
			changeColor(11);
			cout << "爆";
		}
		else if (popu_temp > POPU_RED) {
			changeColor(12);
			cout << "爆";
		}
		else {

			cout << boards[show_idx].getPopularity();
		}
	
		resetColor();
		cout << "\t";
			cout << boards[show_idx].getViewAmount() << endl;
			
		++show_idx;
		++show_cnt;
		if (show_idx >= boards.size())
			show_idx = 0;
	}
	
}
void Viewer::askBoardName() {
	cout << endl << endl << endl;
	cout << "看板名稱僅能使用 a~z 或 A~Z 或 0~9\n";
	cout << "輸入 ! 離開創建畫面\n";
	cout << "請輸入欲創建的看板名稱 ";

}
void Viewer::askBoardIntroduction() {
	cout << endl << endl;
	cout << "請輸入看板文字介紹(可選，輸入Enter跳過) ";

}
void Viewer::askPostTitle() {
	cout << endl;
	cout << "請輸入文章標題(或輸入'!'離開創建模式)：";
}
void Viewer::editorForEdit(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "【編輯文章】" << endl;
	resetColor();
	changeColor(27);
	cout << "標題：" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]捨棄並離開 [`]確認編輯" << endl;
	resetColor();

}
void Viewer::showMailContent(string fromWho, string title, string time, string content) {
	system("cls");
	cout << endl << endl << "郵件資訊" << endl;
	cout << "==============================================================\n";
	cout << "寄件者: " << fromWho << "\n";
	cout << "標題: " << title << "\n";
	cout << "時間: " << time << "\n";
	cout << "==============================================================\n";
	cout << "郵件內容: " << endl;
	cout << content;
	cout << "\n";
	cout << "==============================================================\n";
	cout << "輸入任意鍵離開\n";
}
void Viewer::showMailBox(vector<string> from, vector<string> time, vector<string> title, int current_select) {
	system("cls");
	cout << endl << endl << "            信件系統" << endl << endl;
	cout << "            [↑][↓]選取 [←]返回 [→]瀏覽\n\n";
	cout << "            ";
	cout << setw(13) << right << "    寄件者\t";
	cout << setw(30) << left << "      標題\t";
	cout << "   時間" << endl << endl;

	
	for (int i = 0; i < from.size(); ++i) {
		//hight light
		if (i == current_select) {
			cout << "            ●";
		}
		else {
			cout << "            　";
		}
		cout << "" << setw(10) << right << from[i] << "\t" << setw(30) << left << title[i] << "\t" << time[i] << "\n";
	}
}
void Viewer::editorForMail(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "【撰寫郵件】" << endl;
	resetColor();
	changeColor(27);
	cout << "標題：" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]捨棄並離開 [`]確認發出" << endl;
	resetColor();
}
void Viewer::editor(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "【創建文章】" << endl;
	resetColor();
	changeColor(27);
	cout << "標題：" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]捨棄並離開 [`]發文" << endl;
	resetColor();

}
void Viewer::askComment(string type) {
	cout << "----鍵入[Enter]取消----\n";
	changeColor(31);
	cout << "請輸入 " + type + " 內容: ";
	resetColor();
}
void Viewer::askDeleteFloor() {
	changeColor(79);
	cout << "請輸入欲刪除樓層或-1離開 ";
	resetColor();
}
void Viewer::askDeleteReason(int floor){
	changeColor(79);
	cout << "請輸入刪除 " + to_string(floor) + "F 的理由(鍵入[Enter]取消)：";
	resetColor();
}
void Viewer::displayPost(Post myPost) {
	
	system("cls");


	changeColor(121);
	cout << "【作者】";
	changeColor(23);
	cout << setw(100)  << " " + myPost.getAuthor();
	resetColor();
	cout << "\n";

	changeColor(121);
	cout << "【標題】";
	changeColor(23);
	cout << setw(100) << " " + myPost.getTitle();
	resetColor();
	cout << "\n";
		
	changeColor(121);
	cout << "【時間】";
	changeColor(23);
	cout << setw(100) << " " + myPost.getTimestamp();
	resetColor();
	cout << "\n";
	cout << "[L]推文 [D]噓文 [A]給箭頭 [E]編輯貼文 [H]刪除留言 \n\n";
	cout << myPost.getContent();
	cout << endl << endl;
	changeColor(2);
	cout << "※ 發信站: myptt";
	resetColor();
	cout << "\n";
		//--------------comment start----------------------
	//每6行為一筆
	vector<string> rawData;
	ifstream ifs("Comment/" + to_string(myPost.getPostID()) + ".txt", ios::in);
	if (!ifs) {
		//failed or no comment yet

	}
	else {
		string temp;
		while (!ifs.eof()) {
			getline(ifs, temp);
			rawData.push_back(temp);
		}
		//6行為一筆
		int floor = 0;
		string username, status, reason, type, timestamp, content;
		for (int i = 0; (i+5) < rawData.size(); i += 6) {
			//樓層
			++floor;
			cout << floor << "F ";
			int color = 0;
			username = rawData[i];
			status = rawData[i+1];
			reason = rawData[i+2];
			type = rawData[i+3];
			timestamp = rawData[i+4];
			content = rawData[i+5];

			if (type == "1") {
				type = "推";
				color = 15;
			}
			else if (type == "0") {
				type = "噓";
				color = 12;
			}
			else if (type == "2") {
				type = "→";
				color = 12;
			}

			if (status == "1") {
				//刪除狀態
				if (reason == "") {
					content = "[此留言已被原作者刪除]";
				}
				else {
					content = "[刪除: " + reason + "]";
				}
				changeColor(color);
				cout << type;
				resetColor;
				cout << " ";
				changeColor(6);
				cout << setw(90);
				cout << username + ": " + content;
				resetColor();
				cout << timestamp;
				cout << endl;

			}
			else {
				changeColor(color);
				cout << type;
				resetColor;
				cout << " ";
				changeColor(6);
				cout << setw(90);
				cout << username + ": " + content;
				resetColor();
				cout << timestamp;
				cout << endl;
			}
	

			
		}


	}

	ifs.close();
	setCursor(0, 0);

}
void Viewer::showPostList(int options, int select_board, vector<Board> boards) {
	//options = 第幾個文章
	//select_board = 選取的看板的index
	//請輸出指定index看板的所有文章


	int BOARD_AMOUNT = boards.size();
	int show_cnt = 0; //已經show了幾個文章
	int show_idx = (options > POST_SHOW_HOW_MANY ? options - POST_SHOW_HOW_MANY : 0); //show index
	//可以選看板 信箱 管理員可以選創看板
	system("cls");

	cout << endl << endl << "            ";
	changeColor(27);
	cout << "【文章列表】"<< boards[select_board].getIntroduction() << " 看板《" << boards[select_board].getName() << "》";
	resetColor();
	cout << endl << "            [←]回上層 [→]進入 [↑↓]選擇 [c]創建文章 [d]刪除文章" << endl;
	cout << endl << "            編號\t推噓\t日期    \t作者   \t標題                                   " << endl << endl;

	cout << std::resetiosflags(std::ios::showbase);

	if (boards[select_board].posts.size() == 0) {
		cout << "              暫無文章" << endl;
		return;
	}
	int postCnt = 0;
	int postAmountLimit = boards[select_board].posts.size();
	while (show_cnt <= POST_SHOW_HOW_MANY) {
		++postCnt;
		if (postCnt > postAmountLimit) {
			break;
		}



		if (boards[select_board].posts[show_idx].isDelete()) {
			string deleteReason = boards[select_board].posts[show_idx].getDeleteReason();
			if (deleteReason == "") {
				++show_idx;
				if (show_idx >= boards[select_board].posts.size())
					show_idx = 0;
				continue;
			}
			else {
				//hight light
				if (show_idx == options) {
					cout << "            ●";
				}
				else {
					cout << "              ";
					//cout << "              　";
				}
				//有甚麼功能
				cout << left << setw(3) << show_cnt+1 << "\t"
					<< setw(3) << (boards[select_board].posts[show_idx].getLike()- boards[select_board].posts[show_idx].getDislike()) << "\t"
					<< setw(3) << boards[select_board].posts[show_idx].getTimestamp().substr(0, 8) << "\t"
					<< setw(7) << boards[select_board].posts[show_idx].getAuthor() << "\t"					
					<< setw(40) << ("[刪除] " + deleteReason) << "\t" << endl;
			}
		}
		else {
			//hight light
			if (show_idx == options) {
				cout << "            ●";
			}
			else {
				cout << "              ";
				//cout << "              　";
			}
			//有甚麼功能
			cout << left << setw(3) << show_cnt+1 << "\t"
				<< setw(3) << (boards[select_board].posts[show_idx].getLike() - boards[select_board].posts[show_idx].getDislike()) << "\t"
				<< setw(3) << boards[select_board].posts[show_idx].getTimestamp().substr(0, 8) << "\t"
				<< setw(7) << boards[select_board].posts[show_idx].getAuthor() << "\t"
				<< setw(40) << boards[select_board].posts[show_idx].getTitle() << "\t" << endl;
		}
		++show_idx;
		++show_cnt;
		if (show_idx >= boards[select_board].posts.size())
			show_idx = 0;
	}

}
void Viewer::askMailSelect() {
	system("cls");
	cout << "            'S' 寄信,'R'收信閘,'E'回上一頁" << endl << endl;

}
void Viewer::game3Init(int money, double rate[8]) {
	system("cls");

	
		cout << endl << endl << "            賽馬場" << endl << endl;
		cout << endl << endl << "            當前持有金額: " << money << endl << endl;
		cout << "            玩法清單 [1]獨贏 [2]位置 [3]離開 "  << endl;
		cout << "            玩法說明: [1]獨贏: 僅第一名衝到終點才獲勝 " << endl;
		cout << "            　　　　  [2]位置: 凡前三名衝到終點皆獲勝 "  << endl;
		cout << "            獨贏賠率" << endl;
		cout << "               ";
		for (int i = 0; i < 8; i++) {
			cout << "" << (i + 1) << " 號馬\t";
		}
		cout << "\n               ";
		for (int i = 0; i < 8; i++) {
			cout << fixed << setprecision(2)<< rate[i] << " 倍\t";
		}
		cout << "\n";
		cout << "            位置賠率" << endl;
		cout << "               ";
		for (int i = 0; i < 8; i++) {
			cout << "" << (i + 1) << " 號馬\t";
		}
		cout << "\n               ";
		for (int i = 0; i < 8; i++) {
			cout << fixed << setprecision(2) << rate[i]*0.333 << " 倍\t";
		}
		cout << "\n";
		cout << "            請選擇玩法: ";
}
void Viewer::game3askMoney() {
	//system("cls");
	cout << "            請輸入金額: ";
}
void Viewer::game3askTarget() {
	cout << "            請輸入下注馬匹: ";
}
void Viewer::game3Field(int progress[], int target) {
	system("cls");
	cout << "\n";
	for (int i = 0; i < 8; i++) {
		if (progress[i] == 100)
			cout << "●";
		else
			cout << "○";
		cout << (i + 1) << " :";
		for (int j = 0; j < progress[i]; j++) {
			cout << "-";
		}
		cout << "\n\n";
	}
	for (int j = 0; j < 100; j++) {
		cout << " ";
	}
	cout << "     ^終點";
}
void Viewer::game3Win(vector<int> winTarget, int target) {
	system("cls");
	cout << endl << endl << "            賽馬場" << endl << endl;
	cout << endl << endl << "            前三名: ";
	for (int i = 0; i < 3; i++) {
		cout << winTarget[i] << "號馬 ";
	}
	cout << "\n";
	cout << "            完整名次: \n";
	for (int i = 0; i < 8; i++) {
		cout << "                        第 " << (i+1) << "名: " << winTarget[i] << "號馬 \n";
	}
	cout << "            您選擇的馬匹 " << target << " 號馬, 獲得勝利\n";
	cout << "            輸入任意按鍵繼續\n";
}
void Viewer::game3Lose(vector<int> winTarget, int target) {
	system("cls");
	cout << endl << endl << "            賽馬場" << endl << endl;
	cout << endl << endl << "            前三名: ";
	for (int i = 0; i < 3; i++) {
		cout << winTarget[i] << "號馬 ";
	}
	cout << "\n";
	cout << "            完整名次: \n";
	for (int i = 0; i < 8; i++) {
		cout << "                        第 " << (i + 1) << "名: " << winTarget[i] << "號馬 \n";
	}
	cout << "            很遺憾您選擇的馬匹 " << target << " 號馬, 沒能取得勝利\n";
	cout << "            輸入任意按鍵繼續\n";
}
/*void Viewer::showMailboxList(string currentUserName) {


}*/