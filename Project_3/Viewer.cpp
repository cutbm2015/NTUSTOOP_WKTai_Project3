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
	cout << "�п�J�����ID, �ο�J'!'���}: ";
}
void Viewer::askMailTitle() {
	system("cls");
	cout << "�H����D�H30�r����, �W�X�r�űN�Q�I�_, ����H��r�p��C\n";
	cout << "�п�J�H����D: ";
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
		"�@�@�@�@�@�@�@�@�@�i�i�i��   �i�i�i�� �i�i��   �i�i�� �i�i�i�i�i�i�� �i�i�i�i�i�i�i�i�ߢi�i�i�i�i�i�i�i��" << endl <<
		"�@�@�@�@�@�@�@�@�@�i�i�i�i�� �i�i�i�i�� ��i�i�� �i�i���� �i�i�������i�i���������i�i���������������i�i��������" << endl <<
		"�@�@�@�@�@�@�@�@�@�i�i�ݢi�i�i�i�ݢi�i��  ��i�i�i�i����  �i�i�i�i�i�i����   �i�i��      �i�i��" << endl <<
		"�@�@�@�@�@�@�@�@�@�i�i����i�i����i�i��   ��i�i����   �i�i����������    �i�i��      �i�i��" << endl <<
		"�@�@�@�@�@�@�@�@�@�i�i�� ������ �i�i��    �i�i��    �i�i��        �i�i��      �i�i��" << endl <<
		"�@�@�@�@�@�@�@�@�@������     ������    ������    ������        ������      ������" << endl;
	cout << endl << endl;
	cout << "�@�@�@�@��J�ϥΪ̥N���A�ΥH new ���U�A�ΥH guest ���[ ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@�@�@�@" << endl;

}
void Viewer::askRegUsername() {
	
	resetColor();
	cout << "�п�J�b�� ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@�@�@�@" << endl;
	SetConsoleCursorPosition(hStdout, { 55,12 });
	//resetColor();

}
void Viewer::askRegPassword() {
	SetConsoleCursorPosition(hStdout, { 0,13 });
	resetColor();
	cout << "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�п�J�K�X ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@�@�@�@" << endl;
	SetConsoleCursorPosition(hStdout, { 55,13 });
	//resetColor();
}
void Viewer::askRegPasswordAgain() {
	SetConsoleCursorPosition(hStdout, { 0,14 });
	resetColor();
	cout << "�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�ЦA����J ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@�@�@�@" << endl;
	SetConsoleCursorPosition(hStdout, { 55,14 });
	//resetColor();
}
void Viewer::askRegPermission() {

	resetColor();
	cout << "�п�J�v�� ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@  �@�@" << endl;
	SetConsoleCursorPosition(hStdout, { 55,14 });
}
void Viewer::askLoginPassword() {
	resetColor();
	cout << "�п�J�K�X ";
	changeColor(240);
	cout << "�@�@�@�@�@�@�@�@�@�@" << endl;
	SetConsoleCursorPosition(hStdout, { 55,12 });
	//resetColor();
}
void Viewer::error(string message) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	cout << "\r";		//�M��error���
	cout.flush();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	changeColor(79);
	cout << message;
	resetColor();
	if (message == "This account doesn't exist.Please enter again.") {
		resetColor();
		setCursor(55, 11);
		changeColor(240);
		cout << "�@�@�@�@�@�@�@�@�@�@" << endl;
	}
}
void Viewer::successful(string message) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	cout << "\r";		//�M��error���
	cout.flush();
	SetConsoleCursorPosition(hStdout, { 0,0 });
	changeColor(175);
	cout << message;
	resetColor();
}
void Viewer::setCursor(short x, short y) {
	SetConsoleCursorPosition(hStdout, { x,y });
}
//�M��������|�Ncursor���^�y��(x,y)
void Viewer::clearRow(short x, short y) {
	resetColor();
	SetConsoleCursorPosition(hStdout, { x,y });
	cout << "                                                                                                                                                 ";
	SetConsoleCursorPosition(hStdout, { x,y });
}
//�M��������|�Ncursor���^�y��(x,y)
void Viewer::clearRowWhite(short x, short y) {
	changeColor(240);
	SetConsoleCursorPosition(hStdout, { x,y });
	cout << "�@�@�@�@�@�@�@�@�@�@";
	SetConsoleCursorPosition(hStdout, { x,y });
	//resetColor();
}
//�M��������|�Ncursor���^�y��(x,y)
void Viewer::clearRow(short x, short y, int xCnt) {
	SetConsoleCursorPosition(hStdout, { x,y });
	for (int i = 0; i < xCnt; i++)
		cout << " ";
	SetConsoleCursorPosition(hStdout, { x,y });
}

void Viewer::lobby(int options, int permission) {
	//�i�H��ݪO �H�c �޲z���i�H��ЬݪO
	system("cls");
	cout << endl << endl << "            �D���" << endl << endl;
	cout << "            [��][��]��� [��]�i�J\n\n";
	options = (options < 0 ? -options : options);
	if (permission == 2) {
		options = options % 5;
		for (int i = 0; i <= 4; ++i) {
			//hight light
			if (i == options) {
				cout << "            ��";
			}
			else {
				cout << "            �@";
			}
			//���ƻ�\��
			if (i == 0) {
				cout << "(B)oard  �i�Ҧ��ݪO�j" << endl;
			}
			else if (i == 1) {
				cout << "(M)ail   �i�ڪ��l�c�j" << endl;
			}
			else if (i == 2) {
				cout << "(C)reate �i�ЫجݪO�j" << endl;
			}			
			else if (i == 3) {
				cout << "(G)ame   �i�p�@�C���j" << endl;
			}
			else if (i == 4) {
				cout << "(L)ogout �i�n�@�@�X�j" << endl;
			}
		}
	}
	else if (permission==1) {
		options = options % 4;
		for (int i = 0; i <= 3; ++i) {
			//hight light
			if (i == options) {
				cout << "            ��";
			}
			else {
				cout << "            �@";
			}
			//���ƻ�\��
			if (i == 0) {
				cout << "(B)oard  �i�Ҧ��ݪO�j" << endl;
			}
			else if (i == 1) {
				cout << "(M)ail   �i�ڪ��l�c�j" << endl;
			}			
			else if (i == 2) {
				cout << "(G)ame   �i�p�@�C���j" << endl;
			}
			else if (i == 3) {
				cout << "(L)ogout �i�n�@�@�X�j" << endl;
			}
		}
	}
	else if (permission==0) {
		options = options % 3;
		for (int i = 0; i <= 2; ++i) {
			//hight light
			if (i == options) {
				cout << "            ��";
			}
			else {
				cout << "            �@";
			}
			//���ƻ�\��
			if (i== 0) {
				cout << "(B)oard  �i�Ҧ��ݪO�j" << endl;
			}		
			else if (i == 1) {
				cout << "(G)ame   �i�p�@�C���j" << endl;
			}
			else if (i == 2) {
				cout << "(L)ogout �i�n�@�@�X�j" << endl;
			}
		}
	}
}
void Viewer::mailLobby(int options) {
	system("cls");
	cout << endl << endl << "            �H��t��" << endl << endl;
	cout << "            [��][��]��� [��]��^ [��]�i�J\n\n";
	options = (options < 0 ? -options : options);
	options = options % 2;
	for (int i = 0; i <= 1; ++i) {
		//hight light
		if (i == options) {
			cout << "            ��";
		}
		else {
			cout << "            �@";
		}
		//���ƻ�\��
		if (i == 0) {
			cout << "(M)ail  �i���󧨡j" << endl;
		}
		else if (i == 1) {
			cout << "(S)end  �i�o�H�ϡj" << endl;
		}
	}
}
void Viewer::gameLobby(int options) {
	system("cls");
	cout << endl << endl << "            ��ܹC��" << endl << endl;
	cout << "            [��][��]��� [��]��^ [��]�i�J\n\n";
	options = (options < 0 ? -options : options);
	options = options % 3;
	for (int i = 0; i <= 2; ++i) {
		//hight light
		if (i == options) {
			cout << "            ��";
		}
		else {
			cout << "            �@";
		}
		//���ƻ�\��
		if (i == 0) {
			cout << " �׷��K�X" << endl;
		}
		else if (i == 1) {
			cout << " ��j�p" << endl;
		}
		else if (i == 2) {
			cout << " �ɰ���" << endl;
		}
	
	}
}
void Viewer::game1(int min, int max, int attempt) {
	system("cls");
	cout << endl << endl << "            �׷��K�X(�ϥ���L�i��q��, ��J-1�i���}�C��)" << endl << endl;
	cout << endl << endl << "            ��e�̤p��: " << min << endl << endl;
	cout << endl << endl << "            ��e�̤j��: " << max << endl;
	cout << endl << endl << "            ���զ���: " << attempt << endl;
	cout << endl << endl << "            �z���q��: ";
}
void Viewer::game2(int moneyHave,int type,int moneyBet,int dice[],int winner,int diceGuess1,int diceGuess2) {
	system("cls");
	cout << endl << endl << "            ��j�p(���\�t��)" << endl << endl;
	cout << endl << endl << "            �U�`�����ν߲v: [1]�j:1��1 ; [2]�p:1��1 ; [3]������l:1��5 ; [4]����:1��8 ; [5]���:1��150 ; [6]����:1��24 ; [-1]���}" << endl;
	cout << endl << endl << "            �Ѿl���B: " << moneyHave << endl << endl;
	
	if (type == 1) 
		cout << endl << endl << "            �U�`����: �j" << endl;
	else if (type == 2) 
		cout << endl << endl << "            �U�`����: �p" << endl;
	else if (type == 3) {
		if (diceGuess1 == -1 && diceGuess2 == -1)
			cout << endl << endl << "            �U�`����: ������l        ��l1�I��:        ��l2�I��: " << endl;
		else if (diceGuess1 != -1 && diceGuess2 != -1)
			cout << endl << endl << "            �U�`����: ������l        ��l1�I��: " << diceGuess1 << "        ��l2�I��: " << diceGuess2 << endl;
		else if(diceGuess1 != -1 && diceGuess2 == -1)
			cout << endl << endl << "            �U�`����: ������l        ��l1�I��: " << diceGuess1 << endl;
	}
	else if (type == 4) {
		if (diceGuess1 == -1)
			cout << endl << endl << "            �U�`����: ����        ��l�I��: " << endl;
		else
			cout << endl << endl << "            �U�`����: ����        ��l1�I��: " << diceGuess1 << endl;
	}	
	else if (type == 5) {
		if (diceGuess1 == -1)
			cout << endl << endl << "            �U�`����: ���        ��l�I��: " << endl;
		else
			cout << endl << endl << "            �U�`����: ���        ��l1�I��: " << diceGuess1 << endl;
	}
	else if (type == 6)
		cout << endl << endl << "            �U�`����: ����" << endl;
	else if (type == -1) 
		cout << endl << endl << "            �U�`����: " << endl;
	
		
	if (moneyBet == -1)
		cout << endl << endl << "            �U�`���B: " << endl;
	else
		cout << endl << endl << "            �U�`���B: " << moneyBet << endl;

	if (dice[0] != -1) {
		cout << endl << endl << "            �Y�뵲�G: ";

		for (int i = 0; i <= 2; i++) {
			if (i != 2)
				cout << dice[i] << ',';
			else
				cout << dice[i];
		}	
	}
	else
		cout << endl << endl << "            �Y�뵲�G: ";

	if (winner == -1)
		cout << endl << endl << endl << "            Ĺ�a: ";
	else if (winner == 0)
		cout << endl << endl << endl << "            Ĺ�a: ���a";
	else
		cout << endl << endl << endl << "            Ĺ�a: ���a";

}
//options = ��e��ĴX��?
void Viewer::showBoardList(int options, vector<Board> boards) {
	
	int BOARD_AMOUNT = boards.size();
	int show_cnt = 0; //�w�gshow�F�X�ӬݪO
	int show_idx = (options > BOARD_SHOW_HOW_MANY?options-BOARD_SHOW_HOW_MANY:0); //show index
	//�i�H��ݪO �H�c �޲z���i�H��ЬݪO
	system("cls");
	
	cout <<endl << endl << "            ";
	changeColor(27); 
	cout << "�i�ݪO�C��j";
	resetColor();
	cout << endl << "            [��]�^�W�h [��]�i�J [����]��� [d]�R���ݪO" << endl;
	cout << endl << "            �s��\t�ݪO        \t����ԭz                                   \t�H��\t�\��" << endl  << endl;
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
			cout << "            ��";
		}
		else {
			cout << "              ";
			//cout << "              �@";
		}
		//���ƻ�\��
		int popu_temp = boards[show_idx].getPopularity();
		cout << left << setw(3) << (show_idx + 1) << "\t" << setw(13) << boards[show_idx].getName() << "\t" << setw(40) << boards[show_idx].getIntroduction() << "\t";
		if (popu_temp > POPU_PURPLE) {
			changeColor(13);
			cout << "�z";
		}
		else if (popu_temp > POPU_BLUE) {
			changeColor(11);
			cout << "�z";
		}
		else if (popu_temp > POPU_RED) {
			changeColor(12);
			cout << "�z";
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
	cout << "�ݪO�W�ٶȯ�ϥ� a~z �� A~Z �� 0~9\n";
	cout << "��J ! ���}�Ыصe��\n";
	cout << "�п�J���Ыت��ݪO�W�� ";

}
void Viewer::askBoardIntroduction() {
	cout << endl << endl;
	cout << "�п�J�ݪO��r����(�i��A��JEnter���L) ";

}
void Viewer::askPostTitle() {
	cout << endl;
	cout << "�п�J�峹���D(�ο�J'!'���}�ЫؼҦ�)�G";
}
void Viewer::editorForEdit(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "�i�s��峹�j" << endl;
	resetColor();
	changeColor(27);
	cout << "���D�G" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]�˱�����} [`]�T�{�s��" << endl;
	resetColor();

}
void Viewer::showMailContent(string fromWho, string title, string time, string content) {
	system("cls");
	cout << endl << endl << "�l���T" << endl;
	cout << "==============================================================\n";
	cout << "�H���: " << fromWho << "\n";
	cout << "���D: " << title << "\n";
	cout << "�ɶ�: " << time << "\n";
	cout << "==============================================================\n";
	cout << "�l�󤺮e: " << endl;
	cout << content;
	cout << "\n";
	cout << "==============================================================\n";
	cout << "��J���N�����}\n";
}
void Viewer::showMailBox(vector<string> from, vector<string> time, vector<string> title, int current_select) {
	system("cls");
	cout << endl << endl << "            �H��t��" << endl << endl;
	cout << "            [��][��]��� [��]��^ [��]�s��\n\n";
	cout << "            ";
	cout << setw(13) << right << "    �H���\t";
	cout << setw(30) << left << "      ���D\t";
	cout << "   �ɶ�" << endl << endl;

	
	for (int i = 0; i < from.size(); ++i) {
		//hight light
		if (i == current_select) {
			cout << "            ��";
		}
		else {
			cout << "            �@";
		}
		cout << "" << setw(10) << right << from[i] << "\t" << setw(30) << left << title[i] << "\t" << time[i] << "\n";
	}
}
void Viewer::editorForMail(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "�i���g�l��j" << endl;
	resetColor();
	changeColor(27);
	cout << "���D�G" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]�˱�����} [`]�T�{�o�X" << endl;
	resetColor();
}
void Viewer::editor(string title) {
	system("cls");

	cout << endl << endl << "";
	changeColor(27);
	cout << "�i�Ыؤ峹�j" << endl;
	resetColor();
	changeColor(27);
	cout << "���D�G" << title;
	resetColor();
	cout << endl;
	changeColor(27);
	cout << "[Esc]�˱�����} [`]�o��" << endl;
	resetColor();

}
void Viewer::askComment(string type) {
	cout << "----��J[Enter]����----\n";
	changeColor(31);
	cout << "�п�J " + type + " ���e: ";
	resetColor();
}
void Viewer::askDeleteFloor() {
	changeColor(79);
	cout << "�п�J���R���Ӽh��-1���} ";
	resetColor();
}
void Viewer::askDeleteReason(int floor){
	changeColor(79);
	cout << "�п�J�R�� " + to_string(floor) + "F ���z��(��J[Enter]����)�G";
	resetColor();
}
void Viewer::displayPost(Post myPost) {
	
	system("cls");


	changeColor(121);
	cout << "�i�@�̡j";
	changeColor(23);
	cout << setw(100)  << " " + myPost.getAuthor();
	resetColor();
	cout << "\n";

	changeColor(121);
	cout << "�i���D�j";
	changeColor(23);
	cout << setw(100) << " " + myPost.getTitle();
	resetColor();
	cout << "\n";
		
	changeColor(121);
	cout << "�i�ɶ��j";
	changeColor(23);
	cout << setw(100) << " " + myPost.getTimestamp();
	resetColor();
	cout << "\n";
	cout << "[L]���� [D]�N�� [A]���b�Y [E]�s��K�� [H]�R���d�� \n\n";
	cout << myPost.getContent();
	cout << endl << endl;
	changeColor(2);
	cout << "�� �o�H��: myptt";
	resetColor();
	cout << "\n";
		//--------------comment start----------------------
	//�C6�欰�@��
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
		//6�欰�@��
		int floor = 0;
		string username, status, reason, type, timestamp, content;
		for (int i = 0; (i+5) < rawData.size(); i += 6) {
			//�Ӽh
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
				type = "��";
				color = 15;
			}
			else if (type == "0") {
				type = "�N";
				color = 12;
			}
			else if (type == "2") {
				type = "��";
				color = 12;
			}

			if (status == "1") {
				//�R�����A
				if (reason == "") {
					content = "[���d���w�Q��@�̧R��]";
				}
				else {
					content = "[�R��: " + reason + "]";
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
	//options = �ĴX�Ӥ峹
	//select_board = ������ݪO��index
	//�п�X���windex�ݪO���Ҧ��峹


	int BOARD_AMOUNT = boards.size();
	int show_cnt = 0; //�w�gshow�F�X�Ӥ峹
	int show_idx = (options > POST_SHOW_HOW_MANY ? options - POST_SHOW_HOW_MANY : 0); //show index
	//�i�H��ݪO �H�c �޲z���i�H��ЬݪO
	system("cls");

	cout << endl << endl << "            ";
	changeColor(27);
	cout << "�i�峹�C��j"<< boards[select_board].getIntroduction() << " �ݪO�m" << boards[select_board].getName() << "�n";
	resetColor();
	cout << endl << "            [��]�^�W�h [��]�i�J [����]��� [c]�Ыؤ峹 [d]�R���峹" << endl;
	cout << endl << "            �s��\t���N\t���    \t�@��   \t���D                                   " << endl << endl;

	cout << std::resetiosflags(std::ios::showbase);

	if (boards[select_board].posts.size() == 0) {
		cout << "              �ȵL�峹" << endl;
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
					cout << "            ��";
				}
				else {
					cout << "              ";
					//cout << "              �@";
				}
				//���ƻ�\��
				cout << left << setw(3) << show_cnt+1 << "\t"
					<< setw(3) << (boards[select_board].posts[show_idx].getLike()- boards[select_board].posts[show_idx].getDislike()) << "\t"
					<< setw(3) << boards[select_board].posts[show_idx].getTimestamp().substr(0, 8) << "\t"
					<< setw(7) << boards[select_board].posts[show_idx].getAuthor() << "\t"					
					<< setw(40) << ("[�R��] " + deleteReason) << "\t" << endl;
			}
		}
		else {
			//hight light
			if (show_idx == options) {
				cout << "            ��";
			}
			else {
				cout << "              ";
				//cout << "              �@";
			}
			//���ƻ�\��
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
	cout << "            'S' �H�H,'R'���H�h,'E'�^�W�@��" << endl << endl;

}
void Viewer::game3Init(int money, double rate[8]) {
	system("cls");

	
		cout << endl << endl << "            �ɰ���" << endl << endl;
		cout << endl << endl << "            ��e�������B: " << money << endl << endl;
		cout << "            ���k�M�� [1]�WĹ [2]��m [3]���} "  << endl;
		cout << "            ���k����: [1]�WĹ: �ȲĤ@�W�Ĩ���I�~��� " << endl;
		cout << "            �@�@�@�@  [2]��m: �Z�e�T�W�Ĩ���I����� "  << endl;
		cout << "            �WĹ�߲v" << endl;
		cout << "               ";
		for (int i = 0; i < 8; i++) {
			cout << "" << (i + 1) << " ����\t";
		}
		cout << "\n               ";
		for (int i = 0; i < 8; i++) {
			cout << fixed << setprecision(2)<< rate[i] << " ��\t";
		}
		cout << "\n";
		cout << "            ��m�߲v" << endl;
		cout << "               ";
		for (int i = 0; i < 8; i++) {
			cout << "" << (i + 1) << " ����\t";
		}
		cout << "\n               ";
		for (int i = 0; i < 8; i++) {
			cout << fixed << setprecision(2) << rate[i]*0.333 << " ��\t";
		}
		cout << "\n";
		cout << "            �п�ܪ��k: ";
}
void Viewer::game3askMoney() {
	//system("cls");
	cout << "            �п�J���B: ";
}
void Viewer::game3askTarget() {
	cout << "            �п�J�U�`����: ";
}
void Viewer::game3Field(int progress[], int target) {
	system("cls");
	cout << "\n";
	for (int i = 0; i < 8; i++) {
		if (progress[i] == 100)
			cout << "��";
		else
			cout << "��";
		cout << (i + 1) << " :";
		for (int j = 0; j < progress[i]; j++) {
			cout << "-";
		}
		cout << "\n\n";
	}
	for (int j = 0; j < 100; j++) {
		cout << " ";
	}
	cout << "     ^���I";
}
void Viewer::game3Win(vector<int> winTarget, int target) {
	system("cls");
	cout << endl << endl << "            �ɰ���" << endl << endl;
	cout << endl << endl << "            �e�T�W: ";
	for (int i = 0; i < 3; i++) {
		cout << winTarget[i] << "���� ";
	}
	cout << "\n";
	cout << "            ����W��: \n";
	for (int i = 0; i < 8; i++) {
		cout << "                        �� " << (i+1) << "�W: " << winTarget[i] << "���� \n";
	}
	cout << "            �z��ܪ����� " << target << " ����, ��o�ӧQ\n";
	cout << "            ��J���N�����~��\n";
}
void Viewer::game3Lose(vector<int> winTarget, int target) {
	system("cls");
	cout << endl << endl << "            �ɰ���" << endl << endl;
	cout << endl << endl << "            �e�T�W: ";
	for (int i = 0; i < 3; i++) {
		cout << winTarget[i] << "���� ";
	}
	cout << "\n";
	cout << "            ����W��: \n";
	for (int i = 0; i < 8; i++) {
		cout << "                        �� " << (i + 1) << "�W: " << winTarget[i] << "���� \n";
	}
	cout << "            �ܿ�ѱz��ܪ����� " << target << " ����, �S����o�ӧQ\n";
	cout << "            ��J���N�����~��\n";
}
/*void Viewer::showMailboxList(string currentUserName) {


}*/