#define _CRT_SECURE_NO_WARNINGS
#include "BoardManager.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <fstream>
#include<string>

#define LOBBY_OPTIONS 4

using namespace std;

//#define debug

BoardManager::BoardManager() {
	//constructor
	BoardManager::current_user = -1;	//未登入
	BoardManager::state = MENU;
}

void BoardManager::startBoard() {
	getUser();
	getBoard();
	int current_select_mail_index = 0;
	int current_select_board = 0;
	int current_select_post = 0;
	int browsePostCursorY = 30; //用於瀏覽貼文時的cursor
	bool browsePostPreviousCursorIsDown = true;
	while (!cin.eof()) {
		if (state == MENU)
		{

			viewer.setCursor(0, 0);
			viewer.homepage();
			viewer.setCursor(55, 11);

			User user;
			string tmp;
			cin >> tmp;
			if (tmp == "new") {

				string nameS, pswdS;
				int perI;

				//username
				viewer.setCursor(44, 12);
				viewer.askRegUsername();
				viewer.setCursor(55, 12);
				cin >> nameS;
				while (nameS == "guest" || nameS == "new") {
					viewer.error("Username can't be 'guest' or 'new'");
					viewer.clearRow(44, 12);
					viewer.askRegUsername();
					cin >> nameS;
				}
				while (user.isUserExist(nameS)) {	//check if the username has existed
					viewer.error("This username has existed.Please enter again.");
					viewer.clearRow(44, 12);
					viewer.askRegUsername();
					cin >> nameS;
					while (nameS == "guest") {
						viewer.error("Username can't be 'guest'");
						viewer.clearRow(44, 12);
						viewer.askRegUsername();
						cin >> nameS;
					}
				}
			//	viewer.error("Valid username!");	//username合法

				//password
				viewer.askRegPassword();

				//password
				string password = "";
				string passwordVerify = "";
				bool keepEnter = true;
				do {
				
					password = "";

					viewer.askRegPassword();

					//enter password
					char temp;
					while ((temp = _getch()) != '\r')	// 沒有按下'Enter'鍵		 //輸入密碼時不能使用方向鍵
					{
						if (int(temp) == 8) {	//backspace
							if (password.size() > 0)
								password.pop_back();
						}
						else {		//正常輸入密碼
							password.push_back(temp);
						}

						//顯示密碼星號
						viewer.clearRowWhite(55, 13);
						for (int i = 0; i < password.size(); i++)
							cout << "*";
					}
					if (temp == '\r')
						keepEnter = false;
				} while (keepEnter);
				keepEnter = true;
				do {

					passwordVerify = "";

					viewer.askRegPasswordAgain();

					//enter password
					char temp;
					while ((temp = _getch()) != '\r')	// 沒有按下'Enter'鍵		 //輸入密碼時不能使用方向鍵
					{
						if (int(temp) == 8) {	//backspace
							if (passwordVerify.size() > 0)
								passwordVerify.pop_back();
						}
						else {		//正常輸入密碼
							passwordVerify.push_back(temp);
						}

						//顯示密碼星號
						viewer.clearRowWhite(55, 14);
						for (int i = 0; i < passwordVerify.size(); i++)
							cout << "*";
					}
					if (temp == '\r')
						keepEnter = false;
				} while (keepEnter);
				if (password != passwordVerify) {
					viewer.error("密碼與確認密碼不一致 ");
					Sleep(1500);
					state = MENU;
					continue;
				}
				pswdS = password;
				//cin >> pswdS;
			//	viewer.error("Valid password!");	//password合法	(目前無不合法狀態)

				//permission
				viewer.setCursor(44, 14);
				perI = 1;
			/*	viewer.askRegPermission();
				cin >> perI;
				while (perI != 1 && perI != 2) {
					viewer.error("Permission must be '1' or '2'.Please enter again.");
					viewer.clearRow(44, 14);
					viewer.askRegPermission();
					cin >> perI;
				}
				viewer.error("Valid permission!");	//permission合法
				*/
				
				users.push_back(new User(user.createAccount(nameS, pswdS, perI)));
				getUser();
				viewer.successful("註冊完成！請重新登入");
				Sleep(1500);
				state = MENU;
				continue;
			}
			else if (tmp == "guest") {
				if (current_user == -1) {	//目前為登出狀態
				//	users.push_back(new User(user.guestIn()));
					users.push_back(new Guest("","",0));
					current_user = users.size() - 1;
					viewer.error("guest login successfully");
					state = LOBBY;
				}
				else {
					viewer.error("guest login failed");
				}
			}
			else if (tmp != "guest" && tmp != "new") {	//login
				string password = "";
				string correctPswd;
				string username = tmp;

				//username
				while (!user.isUserExist(username, correctPswd)) {

					viewer.setCursor(0, 0);
					viewer.homepage();
					viewer.error("This account doesn't exist.Please enter again.");
					viewer.setCursor(55, 11);

					cin >> username;
					if (username == "guest" || username == "new")
						break;
				}

				if (username == "guest") {
					users.push_back(new Guest("", "", 0));
					current_user = users.size() - 1;
					viewer.error("guest login successfully");
					state = LOBBY;
					continue;
				}
				else if (username == "new") {
					string nameS, pswdS;
					int perI;

					//username
					viewer.setCursor(44, 12);
					viewer.askRegUsername();
					viewer.setCursor(55, 12);
					cin >> nameS;
					while (nameS == "guest") {
						viewer.error("Username can't be 'guest'");
						viewer.clearRow(44, 12);
						viewer.askRegUsername();
						cin >> nameS;
					}
					while (user.isUserExist(nameS)) {	//check if the username has existed
						viewer.error("This username has existed.Please enter again.");
						viewer.clearRow(44, 12);
						viewer.askRegUsername();
						cin >> nameS;
						while (nameS == "guest") {
							viewer.error("Username can't be 'guest'");
							viewer.clearRow(44, 12);
							viewer.askRegUsername();
							cin >> nameS;
						}
					}
					//viewer.error("Valid username!");	//username合法

					//password
					viewer.askRegPassword();
					cin >> pswdS;
				//	viewer.error("Valid password!");	//password合法	(目前無不合法狀態)

					//permission
					viewer.setCursor(44, 14);
					viewer.askRegPermission();
					perI = 1;
				/*	cin >> perI;
					while (perI != 1 && perI != 2) {
						viewer.error("Permission must be '1' or '2'.Please enter again.");
						viewer.clearRow(44, 14);
						viewer.askRegPermission();
						cin >> perI;
					}
					viewer.error("Valid permission!");	//permission合法*/


					users.push_back(new User(user.createAccount(nameS, pswdS, perI)));
					continue;
				}


			//	viewer.error("Valid username!");	//valid username


				//password
				do {
					if (password.size() != 0)	//密碼錯誤
						viewer.error("Incorrect password.Please enter again.");

					password = "";

					viewer.setCursor(44, 12);
					viewer.askLoginPassword();

					//enter password
					char temp;
					while ((temp = _getch()) != '\r')	// 沒有按下'Enter'鍵		 //輸入密碼時不能使用方向鍵
					{
						if (int(temp) == 8) {	//backspace
							if (password.size() > 0)
								password.pop_back();
						}
						else {		//正常輸入密碼
							password.push_back(temp);
						}

						//顯示密碼星號
						viewer.clearRowWhite(55, 12);
						for (int i = 0; i < password.size(); i++)
							cout << "*";
					}
				} while (password != correctPswd);

				
				viewer.successful("Login successfully!");
				Sleep(1000);
				current_user = user.userLogin(username);


				state = LOBBY;

			}



		}
		else if (state == LOBBY)
		{
			// Display & Select next operation
			getBoard();
			int ch1 = 0;
			int ch2 = 0;
			int current_select = 0;

			viewer.lobby(current_select, users[current_user]->getUserPermission());
			while (!cin.eof())
			{
				if (ch1 = _getch())
				{//98 109 99 108
					/*if (ch1 == 'B') {
						current_select = 1;
						viewer.lobby(current_select);
						continue;
					}
					else if (ch1 == 'M') {
						current_select = 2;
						viewer.lobby(current_select);
						continue;
					}
					else if (ch1 == 99) {
						current_select = 3;
						viewer.lobby(current_select);
						continue;
					}
					else if (ch1 == 108) {
						current_select = 4;
						viewer.lobby(current_select);
						continue;
					}*/
					//如果是方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值
					if (ch1 == 224) {
						ch2 = _getch();
						if (ch2 == 72) {
							//up
							current_select--;

						}
						else if (ch2 == 80) {
							//down 往下index增加
							current_select++;

						}
						else if (ch2 == 75) {
							//left

						}
						else if (ch2 == 77) {
							//right
							//enter the page
							if (users[current_user]->isAdmin()) {
								current_select %= 5;
								switch (current_select)
								{
								case 0:
									state = SELECT_BOARD;
									break;
								case 1:
									state = MAIL;
									break;
								case 2:
									state = CREATE_BOARD;
									break;
								case 3:
									state = GAME;
									break;
								case 4:
									current_user = -1;
									state = MENU;
									break;
								default:
									break;
								}
							}
							else if (users[current_user]->isUser()) {
								current_select %= 4;

								switch (current_select)
								{
								case 0:
									state = SELECT_BOARD;
									break;
								case 1:
									state = MAIL;
									break;
								case 2:
									state = GAME;
									break;
								case 3:
									current_user = -1;
									state = MENU;
									break;
								default:
									break;
								}

							}
							else if (users[current_user]->isGuest()) {
								current_select %= 3;

								switch (current_select)
								{
								case 0:
									state = SELECT_BOARD;
									break;
								case 1:
									state = GAME;
									break;
								case 2:
									current_user = -1;
									state = MENU;
									break;
								default:
									break;
								}

							}
							/*if (current_select == 1) {
								state = SELECT_BOARD;
							}
							else if (current_select == 2) {
								state = MAIL;
							}
							else if (current_select == 3) {
								state = CREATE_BOARD;
							}
							else if (current_select == 4) {
								current_user = -1;
								state = MENU;

							}*/
							break;

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));
							continue;
						}


						viewer.lobby(current_select, users[current_user]->getUserPermission());
					}
				}
			}

		}
		else if (state == SELECT_BOARD) {
			// show all board
			if (boards.size() == 0) {

				viewer.error("尚無任何看板可供選擇");
				Sleep(2000);
				state = LOBBY;
				continue;
			}

			int ch1 = 0;
			int ch2 = 0;
			int popu = 0;
			
				for (Post p : boards[current_select_board].posts) {
					if (p.isDelete())
						continue;
					popu += p.getLike();
					popu -= p.getDislike();
				}
				boards[current_select_board].setPopularity(popu);
			
			viewer.showBoardList(current_select_board, boards);
			while (!cin.eof())
			{

				//99=C 100=D
				if (ch1 = _getch()) {
					if (ch1 == 100) {
						if (!users[current_user]->isAdmin()) {
							viewer.error("permission denied");
							continue;
						}
						char yn;
						viewer.error("確認刪除 [y/n]");
						cin >> yn;
						if (yn == 'y') {
							//刪除
							boards[current_select_board].doDelete(boards);
							viewer.successful("delete " + boards[current_select_board].getName() + " successful");
							getBoard();
							Sleep(1000);
						}
						else {
							//不刪除
						}
						int current_select = 0;
						viewer.showBoardList(current_select, boards);
					}
					else {


						//方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值

						ch2 = _getch();
						if (ch2 == 72) {
							//up
							current_select_board--;

						}
						else if (ch2 == 80) {
							//down 往下index增加
							current_select_board++;

						}
						else if (ch2 == 75) {
							//left
							state = LOBBY;
							break;
						}
						else if (ch2 == 77) {
							//right
							//enter the board
							selected_board = current_select_board;
							boards[selected_board].increaseViewAmount();
							state = BOARD;
							break;

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));

						}

						if (current_select_board >= boards.size()) {//超出index
							current_select_board = 0;
						}
						else if (current_select_board < 0) {//超出index
							current_select_board = boards.size();
						}
						viewer.showBoardList(current_select_board, boards);

					}
				}
			}

		
		
		}
		else if (state == BOARD)
		{
			getBoard();
			/*if (boards[current_select_board].posts.size() == 0) {

				viewer.error("尚無任何貼文可供閱覽");
				Sleep(2000);

				state = LOBBY;
				continue;
			}*/
			// Display each post & select post
			
			int ch1 = 0;
			int ch2 = 0;
			 current_select_post = 0;

			for (auto iter = boards[current_select_board].posts.begin(); iter != boards[current_select_board].posts.end(); ++iter) {
				if (iter->getDeleteReason() == "" && iter->isDelete()) {
					boards[current_select_board].posts.erase(iter);
					if (boards[current_select_board].posts.size() == 0) {						
						break;
					}
					iter = boards[current_select_board].posts.begin();
				}
			}

			for (Post p : boards[current_select_board].posts) {
				if (p.isDelete() && p.getDeleteReason() == "") {
					current_select_post++;
				}
				else {
					break;
				}
			}
			viewer.showPostList(current_select_post, selected_board, boards);
			while (!cin.eof())
			{

				//99=C 100=D
				if (ch1 = _getch()) {
					if (ch1 == 99) {
						if (users[current_user]->isGuest()) {
							viewer.error("遊客不可創建貼文, 請先註冊成為會員");
							Sleep(2000);
						//	viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							break;
						}

						state = CREATE_POST;
						break;
					}
					else if (ch1 == 100) {
						if (!users[current_user]->isAdmin() && boards[current_select_board].posts[current_select_post].getAuthor() != users[current_user]->getUserName()) {

							//原作者?

							viewer.error("permission denied");
							continue;
						}
						char yn;
						viewer.error("確認刪除 [y/n]");
						cin >> yn;
						if (yn == 'y') {
							//刪除
							string reason;
							if (boards[current_select_board].posts[current_select_post].getAuthor() == users[current_user]->getUserName()) {
								//作者本人
								reason = "";
							}
							else {
								//管理員刪除
								reason = "";
								viewer.error("請輸入文章刪除理由：");
								cin.get();
								getline(cin, reason);
								while (reason == "") {
									viewer.error("請輸入文章刪除理由：（不得為空！）");
									Sleep(1000);
									viewer.error("請輸入文章刪除理由：");
									getline(cin, reason);
								}
							}
							
							
							boards[current_select_board].posts[current_select_post].doDelete(reason);
							viewer.successful("刪除成功！");
							Sleep(1000);
							break;
						}
						else {
							//不刪除
						}
						int current_select = 0;
						viewer.showBoardList(current_select, boards);
					}
					else {


						//方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值

						ch2 = _getch();
						if (ch2 == 72) {
							//up
							current_select_post--;

							

						}
						else if (ch2 == 80) {
							//down 往下index增加
							current_select_post++;

						}
						else if (ch2 == 75) {
							//left
							state = SELECT_BOARD;
							break;
						}
						else if (ch2 == 77) {
							//right
							//enter the post
							if (boards[current_select_board].posts.size() > 0) {

								if (boards[current_select_board].posts[current_select_post].isDelete()) {
									if (users[current_user]->isAdmin()) {
										viewer.error("此文章已被刪除，是否仍要閱覽？[y/n]");
										char yorn;
										cin >> yorn;
										while (yorn != 'y' && yorn != 'n') {
											cin >> yorn;
										}
										if (yorn == 'y') {
											state = POST;
											break;
										}
										else {
											//don't enter
										}
									}
									else {

										viewer.error("permission denied 貼文已被管理員刪除");

									}
								}
								else {
									//沒被刪除
									state = POST;
									break;
								}

							}

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));

						}

						if (current_select_post >= boards[selected_board].posts.size()) {//超出index
							current_select_post = 0;
						}
						else if (current_select_post < 0) {//超出index
							current_select_post = boards.size();
						}
						viewer.showPostList(current_select_post, selected_board, boards);

					}
				}
			}

		}
		else if (state == POST)
		{
			// Display Post text
			viewer.displayPost(boards[current_select_board].posts[current_select_post]);
			
			int ch1 = 0;
			int ch2 = 0;
			
			while (!cin.eof())
			{

				//99=C 100=D
				if (ch1 = _getch()) {
					//L76/108 D68/100 A65/97 E69/101 H72/104

					//方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值
					//101 = edit編輯文章
					if (ch1 == 'e' || ch1 == 'E') {

						//edit (author)
						if (users[current_user]->isAdmin()  || boards[current_select_board].posts[current_select_post].getAuthor() == users[current_user]->getUserName()) {
							state = EDIT_POST;
							break;
						}
						else {
							viewer.error("非原作者或管理員無法編輯文章");
							Sleep(2000);
							viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							
						}

					}
					else if (ch1 == 'l' || ch1 == 'L' || ch1 == 'd' || ch1 == 'D' || ch1 == 'a' || ch1 == 'A') {
						//
						if (users[current_user]->isGuest()) {
							viewer.error("遊客不可推/噓/給箭頭, 請先註冊成為會員");
							Sleep(2000);
							viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							break;
						}

						string type = "";
						if (ch1 == 'l' || ch1 == 'L') {
							type = "推";
							//檢查重複推噓
							if (!boards[current_select_board].posts[current_select_post].isLikeOrDislikeAvailable(users[current_user]->getUserName())) {
								//不允許
								viewer.error("不可重複 推/噓 建議您使用給箭頭功能 [duplicated]");
								Sleep(2000);
								viewer.displayPost(boards[current_select_board].posts[current_select_post]);
								break;
							}
						}
						else if (ch1 == 'd' || ch1 == 'D') {
							type = "噓";
							//檢查重複推噓
							if (!boards[current_select_board].posts[current_select_post].isLikeOrDislikeAvailable(users[current_user]->getUserName())) {
								//不允許
								viewer.error("不可重複 推/噓 建議您使用給箭頭功能 [duplicated]");
								Sleep(2000);
								viewer.displayPost(boards[current_select_board].posts[current_select_post]);
								break;
							}
						}
						else if (ch1 == 'a' || ch1 == 'A') {
							type = "箭頭";
						}
						viewer.setCursor(0, 25);
						viewer.askComment(type);
						
						string comment = "";
						getline(cin, comment);
						if (comment == "") {
							viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							break;
						}
						else if (comment.length() > 80) {
							viewer.error("留言長度超限 [length exceed]");
							Sleep(2000);
							viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							break;
						}else {							
							if(boards[current_select_board].posts[current_select_post].doComment(users[current_user]->getUserName(), type, comment)){
								//success
							}
							else {
								viewer.error("comment failed");
								Sleep(1000);
							}
						}
						viewer.displayPost(boards[current_select_board].posts[current_select_post]);
						break;

					}
					else if (ch1 == 'h' || ch1 == 'H') {
						//delete comment (author or admin)
						if (users[current_user]->isGuest()) {
							viewer.error("遊客不可刪除留言, 請先註冊成為會員");
							Sleep(2000);
							viewer.displayPost(boards[current_select_board].posts[current_select_post]);
							break;
						}

						int floor;
						viewer.setCursor(0, browsePostCursorY);
						viewer.askDeleteFloor();
						cin >> floor;
						if (floor == -1)
							break;
						if (boards[current_select_board].posts[current_select_post].isCommentAuthor(floor, users[current_user]->getUserName())) {
							//原作者自己刪除
							if(boards[current_select_board].posts[current_select_post].doDeleteComment(floor, "")){
								system("cls");
								viewer.successful("成功刪除 " + to_string(floor) + "F" + " 留言");
								Sleep(2000);
								break;
							}						
						}
						else if(users[current_user]->isAdmin()) {
							//管理員強制刪除
							string reason = "";
							cin.get();
							viewer.askDeleteReason(floor);
							getline(cin, reason);
							if (reason == "")
							{							
								break;
							}

							if (boards[current_select_board].posts[current_select_post].doDeleteComment(floor, reason)) {
								system("cls");
								viewer.setCursor(0, 0);
								viewer.successful("成功刪除 " + to_string(floor) + "F" + " 留言" + ", 原因: " + reason);
								Sleep(2000);
								break;
							}
							else {
								system("cls");
								viewer.setCursor(0, 0);
								viewer.error("不得刪除非法樓層之留言");
								Sleep(2000);
								break;
							}
						}
						else {
							//不是作者也不是管理員
							system("cls");
							viewer.setCursor(0, 0);
							viewer.error("您非管理員, 您僅可刪除自己的留言, 他人的留言無法刪除！");
							Sleep(2000);
							break;
						}
					




					}
					else if (ch1 == 'Z' || ch1 =='z') {
						/*string reason = "";
						cin.get();
						viewer.askDeleteReason(floor);
						getline(cin, reason);
						if (reason == "")
						{
							break;
						}

						if (boards[current_select_board].posts[current_select_post].doDeleteComment(floor, reason)) {
							system("cls");
							viewer.setCursor(0, 0);
							viewer.successful("成功刪除 " + to_string(floor) + "F" + " 留言" + ", 原因: " + reason);
							Sleep(2000);
							break;
						}
						else {
							system("cls");
							viewer.setCursor(0, 0);
							viewer.error("不得刪除非法樓層之留言");
							Sleep(2000);
							break;
						}*/
					}
					else if (ch1 == 224) {
						ch2 = _getch();
						if (ch2 == 72) {
							//up
							if (browsePostPreviousCursorIsDown)
								browsePostCursorY -= 30;
							else
								browsePostCursorY -=1;
							if (browsePostCursorY < 0)
								browsePostCursorY = 0;
							browsePostPreviousCursorIsDown = false;
							viewer.setCursor(0, browsePostCursorY);
						}
						else if (ch2 == 80) {
							//down 
							//browsePostPreviousCursorIsDown = true;
							if (browsePostPreviousCursorIsDown)
								browsePostCursorY += 1;
							else
								browsePostCursorY += 30;
							browsePostPreviousCursorIsDown = true;
							viewer.setCursor(0, browsePostCursorY);
						}
						else if (ch2 == 75) {
							//left
							state = BOARD;
							break;
						}
						else if (ch2 == 77) {
							//right
							//已經最底層
							break;

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));

						}
					}




				}
			}
		}
		else if (state == CREATE_POST) {
		// create post
		string title;
		system("cls");
		viewer.askPostTitle();
		//cin.get();
		getline(cin, title);
		while (title == "") {
			//cin.get();
			getline(cin, title);
		}
		if (title == "!") {
			state = BOARD;
			continue;
		}
		viewer.editor(title);

		string line;
		vector<string> content;

		int ch1 = 0;
		int ch2 = 0;
		int previousX = 0;
		int cursorX = 0;
		int cursorY = 6;
		viewer.setCursor(cursorX, cursorY);
		while (!cin.eof())
		{//59=f1   224->83=del



			int c1;
			fflush(stdin);
			string buffer = "";
			string content;
			bool chineseMove = false;
			auto bufferIter = buffer.end();
			int iterOffset = 0;
			bool functionKey = false;
			while (c1 = _getch()) {

					

				//	cout << "d: " << c1 << "\n";
					if (functionKey) {
						char ctmp;
						if (bufferIter == buffer.begin()) {
							cursorX = 0;
							viewer.setCursor(cursorX, cursorY);
							functionKey = false;
							bufferIter = buffer.end() + iterOffset;
							if(c1 == 75)
								continue;
							else
								ctmp = 0;
						}
						else {
							ctmp = *(bufferIter - 1);
						}
						

						if (c1 == 72) {
							//up


						}
						else if (c1 == 80) {
							//down


						}
						else if (c1 == 75) {
							//left
							cursorX--;
							if (ctmp == '\n')							{
								cursorX = previousX;
								cursorY--;			
								iterOffset--;
						}
							else if (ctmp < 0) {
								cursorX--;

								iterOffset -= 2;
							
							}
							else {		
								iterOffset -= 1;
							}
							if (iterOffset > 0)
								iterOffset = 0;
							bufferIter = buffer.end() + iterOffset;

						}
						else if (c1 == 77) {
							//right
							if (bufferIter == buffer.end() ) {
								functionKey = false;
								iterOffset = 0;
								bufferIter = buffer.end() + iterOffset;
								
								continue;
							}
							else if (bufferIter == buffer.end() - 1) {
								functionKey = false;
								iterOffset += 1;
								cursorX++;
								iterOffset = 0;
								bufferIter = buffer.end() + iterOffset;
								viewer.setCursor(cursorX, cursorY);
								continue;
							}
							else if (bufferIter == buffer.end() - 2) {
								functionKey = false;
								iterOffset += 1;
								cursorX++;
								iterOffset = -1;
								if (*(bufferIter) < 0) {
									iterOffset += 1;
									cursorX++;
									iterOffset = 0;
								}
								viewer.setCursor(cursorX, cursorY);
								bufferIter = buffer.end() + iterOffset;
								continue;
							}

							cursorX++;
							bufferIter = buffer.end() + iterOffset;
							
						
							char ctmp = *(bufferIter + 1);
							char ctmp2 = *(bufferIter + 2);
							char curr = *(bufferIter);
							if (curr == '\n') {
								previousX = --cursorX;
								cursorY++;
								cursorX = 0;
								iterOffset++;
							}
							else if (ctmp < 0 || ctmp2 < 0) {
								cursorX++;
								iterOffset += 2;
							}
							else {


								iterOffset += 1;
							}
							if (iterOffset > 0)
								iterOffset = 0;
							bufferIter = buffer.end() + iterOffset;

						}
						else if (c1 == 83) {
							//del

						}

						functionKey = false;
						viewer.setCursor(cursorX, cursorY);
						continue;
						
					}
					if (c1 == 224) {
						functionKey = true;
						continue;
					}
					else if (c1==96) {
						//f1
						//post
						time_t rawtime;
						struct tm* timeinfo;
						time(&rawtime);
						timeinfo = localtime(&rawtime);
						char year[5], mon[3], mday[3], hour[3], minute[3], sec[3];
						sprintf(year, "%d", timeinfo->tm_year + 1900);
						sprintf(mon, "%d", timeinfo->tm_mon + 1);
						sprintf(mday, "%d", timeinfo->tm_mday);
						sprintf(hour, "%d", timeinfo->tm_hour);
						sprintf(minute, "%d", timeinfo->tm_min);
						sprintf(sec, "%d", timeinfo->tm_sec);
						string times = year;
						times += "/";
						times += mon;
						times += "/";
						times += mday;
						times += " ";
						times += hour;
						times += ":";
						times += minute;
						times += ":";
						times += sec;

						Post temp(post_num + 1,0,boards[selected_board].getName(),"",users[current_user]->getUserName(), title, times ,content);
					
						if (temp.doPost(temp)) {
							++post_num;
							system("cls");
							viewer.successful("標題：" + title + " 發表成功 兩秒後回到看板");
							Sleep(2000);
							state = BOARD;
							break;
						}
						else {
							viewer.error("post failed, file I/O occured an error.");
						}


					}
					else if (c1 == 27) {
						//esc
						state = BOARD;
						break;
					}
					else if (c1 == 8) {
						//backspace


						char ctmp = 0, ctmp2 = 0;
						if (buffer.size() >= 1)
						{
							ctmp = buffer[buffer.size() - 1];
						}
						else {
							continue;
						}
						if (buffer.size() >= 2)
						ctmp2 = buffer[buffer.size() - 2];

						cursorX--;
						if (ctmp < 0 || ctmp2 < 0) {
							cursorX--;
							if (buffer.size() > 0) 
								buffer.erase(buffer.end() - 1);
							if (buffer.size() > 0)
							buffer.erase(buffer.end() - 1);
						}
						else {

							if (buffer.size() > 0)
							buffer.erase(buffer.end() - 1);
						}
					
					}
					else if (c1 == 13) {
						buffer.insert(bufferIter, '\n');
						previousX = cursorX;
						cursorX = 0;
						cursorY++;
					
						viewer.setCursor(cursorX, cursorY);
					}
					else {					
						
						buffer.insert(bufferIter, c1);
						if(!chineseMove)
							cursorX++;
						
						if (c1 < 0) {
							cursorX++;
							chineseMove = true;
							iterOffset+=2;
							if (iterOffset > 0)
								iterOffset = 0;
						}
						else {
							chineseMove = false;
						}
					}

				//	buffer.push_back(c1);
					
				//	cout << "buffer: " << buffer << "\n";
				//	cout << "buffer len: " << buffer.size() << "\n";
					ofstream ofs("buffer.txt", ios::out);
					ofs << buffer;
					ofs.close();
					ifstream ifs("buffer.txt", ios::in);
					string temp;
					content = "";
					while (!ifs.eof()) {
						getline(ifs, temp);
						content += temp + '\n';
					}
				//	cout << "current content: " << "\n";
					system("cls");
					viewer.editor(title);

					cout << "\n";
				


					
				//	cout << "\n=========================\n";
					ifs.close();
					bufferIter = buffer.end() + iterOffset;

				//	buffer.insert(bufferIter, '|');
					cout << buffer;
					//buffer.erase(bufferIter);

					viewer.setCursor(cursorX, cursorY);
				}
				if (state == BOARD) {
					break;
				}
			}
		}
		else if (state == CREATE_BOARD) {
			if (users[current_user]->isAdmin()) {
				string boardName;
				system("cls");
				viewer.askBoardName();				
				cin >> boardName;
				if (boardName == "!") {
					state = LOBBY;
					continue;
				}
				while (!Board::isValidBoardName(boardName)) {
					system("cls");
					viewer.error("invalid boardname (already exist or contain illegal letter)");
					viewer.askBoardName();
					cin >> boardName;		
				}
				viewer.askBoardIntroduction();
				string introduction = "";
				cin.get();
				getline(cin, introduction);
				if (introduction == "\n")
					introduction = "我是預設的看板介紹詞";
					boards.push_back(Board::createBoard(boardName, introduction));
				

				viewer.successful("board create successfully");
				Sleep(2000);
				//system("cls");
				state = LOBBY;
			}
			else {
				//permission denied
				viewer.error("permission denied");
				Sleep(500);
				state = LOBBY;
			}
		}
		/*
		
		EEEEEEEEEEEEEEEEEEEEEEEE
		E
		E
		E
		E
		E
		EEEEEEEEEEEEEEEEEEEEEEEE
		E
		E
		E
		E
		E
		E
		EEEEEEEEEEEEEEEEEEEEEEEE

		EDIT
		
		
		
		*/
		else if (state == EDIT_POST) {
			//edit
			//cin.get();
			
			fflush(stdin);
			Post myPost = boards[current_select_board].posts[current_select_post];
			string title;
			system("cls");
			cout << "原標題：" << boards[current_select_board].posts[current_select_post].getTitle() << "\n";
			cout << "----若要放棄編輯, 請輸入   '!'   繼續----\n";
			cout << "----若不更改標題, 請按下 [Enter] 繼續----\n";
			cout << "新標題：";
			
			getline(cin, title);
			if (title == "") {
				title = myPost.getTitle();
			}
			if (title == "!") {
				state = POST;
				continue;
			}
			viewer.editorForEdit(title);
			//viewer.editor(title);


			int ch1 = 0;
			int ch2 = 0;
			int previousX = 0;
			int cursorX = 0;
			int cursorY = 6;
			viewer.setCursor(cursorX, cursorY);
			while (!cin.eof())
			{//59=f1   224->83=del
				int c1;
				fflush(stdin);
				string buffer = "";
				string content;
				buffer = myPost.getContent();
				cout << buffer;
				bool chineseMove = false;
				auto bufferIter = buffer.end();
				int iterOffset = 0;
				bool functionKey = false;
				while (c1 = _getch()) {

					//	cout << "d: " << c1 << "\n";
					if (functionKey) {
						char ctmp;
						if (bufferIter == buffer.begin()) {
							cursorX = 0;
							viewer.setCursor(cursorX, cursorY);
							functionKey = false;
							bufferIter = buffer.end() + iterOffset;
							if (c1 == 75)
								continue;
							else
								ctmp = 0;
						}
						else {
							ctmp = *(bufferIter - 1);
						}


						if (c1 == 72) {
							//up


						}
						else if (c1 == 80) {
							//down


						}
						else if (c1 == 75) {
							//left
							cursorX--;
							if (ctmp == '\n') {
								cursorX = previousX;
								cursorY--;
								iterOffset--;
							}
							else if (ctmp < 0) {
								cursorX--;

								iterOffset -= 2;

							}
							else {
								iterOffset -= 1;
							}
							if (iterOffset > 0)
								iterOffset = 0;
							bufferIter = buffer.end() + iterOffset;

						}
						else if (c1 == 77) {
							//right
							if (bufferIter == buffer.end()) {
								functionKey = false;
								iterOffset = 0;
								bufferIter = buffer.end() + iterOffset;

								continue;
							}
							else if (bufferIter == buffer.end() - 1) {
								functionKey = false;
								iterOffset += 1;
								cursorX++;
								iterOffset = 0;
								bufferIter = buffer.end() + iterOffset;
								viewer.setCursor(cursorX, cursorY);
								continue;
							}
							else if (bufferIter == buffer.end() - 2) {
								functionKey = false;
								iterOffset += 1;
								cursorX++;
								iterOffset = -1;
								if (*(bufferIter) < 0) {
									iterOffset += 1;
									cursorX++;
									iterOffset = 0;
								}
								viewer.setCursor(cursorX, cursorY);
								bufferIter = buffer.end() + iterOffset;
								continue;
							}

							cursorX++;
							bufferIter = buffer.end() + iterOffset;


							char ctmp = *(bufferIter + 1);
							char ctmp2 = *(bufferIter + 2);
							char curr = *(bufferIter);
							if (curr == '\n') {
								previousX = --cursorX;
								cursorY++;
								cursorX = 0;
								iterOffset++;
							}
							else if (ctmp < 0 || ctmp2 < 0) {
								cursorX++;
								iterOffset += 2;
							}
							else {


								iterOffset += 1;
							}
							if (iterOffset > 0)
								iterOffset = 0;
							bufferIter = buffer.end() + iterOffset;

						}
						else if (c1 == 83) {
							//del

						}

						functionKey = false;
						viewer.setCursor(cursorX, cursorY);
						continue;

					}
					if (c1 == 224) {
						functionKey = true;
						continue;
					}
					else if (c1 == 96) {
						//f1
						//post
						time_t rawtime;
						struct tm* timeinfo;
						time(&rawtime);
						timeinfo = localtime(&rawtime);
						char year[5], mon[3], mday[3], hour[3], minute[3], sec[3];
						sprintf(year, "%d", timeinfo->tm_year + 1900);
						sprintf(mon, "%d", timeinfo->tm_mon + 1);
						sprintf(mday, "%d", timeinfo->tm_mday);
						sprintf(hour, "%d", timeinfo->tm_hour);
						sprintf(minute, "%d", timeinfo->tm_min);
						sprintf(sec, "%d", timeinfo->tm_sec);
						string times = year;
						times += "/";
						times += mon;
						times += "/";
						times += mday;
						times += " ";
						times += hour;
						times += ":";
						times += minute;
						times += ":";
						times += sec;

						myPost.setTitle(title);
						myPost.setContent(content);
						myPost.setTimestamp(times);
						//Post temp(post_num + 1, 0, boards[selected_board].getName(), "", users[current_user]->getUserName(), title, times, content);

						if (myPost.fileUpdate()) {
							++post_num;
							system("cls");
							viewer.successful("標題：" + title + " 編輯成功 兩秒後回到看板");
							Sleep(2000);
							state = BOARD;
							break;
						}
						else {
							viewer.error("post failed, file I/O occured an error.");
						}


					}
					else if (c1 == 27) {
						//esc
						state = BOARD;
						break;
					}
					else if (c1 == 8) {
						//backspace


						char ctmp = 0, ctmp2 = 0;
						if (buffer.size() >= 1) {
							ctmp = buffer[buffer.size() - 1];
						}
						else {
							continue;
						}
						if (buffer.size() >= 2)
							ctmp2 = buffer[buffer.size() - 2];

	//					char ctmp = buffer[(buffer.size() - 1 > 0 ? buffer.size() - 1 : 0)];
		//				char ctmp2 = buffer[(buffer.size() - 2 > 0 ? buffer.size() - 2 : 0)];

						cursorX--;
						if (ctmp < 0 || ctmp2 < 0) {
							cursorX--;
							buffer.erase(buffer.end() - 1);
							buffer.erase(buffer.end() - 1);
						}
						else
							buffer.erase(buffer.end() - 1);


					}
					else if (c1 == 13) {
						buffer.insert(bufferIter, '\n');
						previousX = cursorX;
						cursorX = 0;
						cursorY++;

						viewer.setCursor(cursorX, cursorY);
					}
					else {
						buffer.insert(bufferIter, c1);
						if (!chineseMove)
							cursorX++;

						if (c1 < 0) {
							cursorX++;
							chineseMove = true;
							iterOffset += 2;
							if (iterOffset > 0)
								iterOffset = 0;
						}
						else {
							chineseMove = false;
						}
					}

					//	buffer.push_back(c1);

					//	cout << "buffer: " << buffer << "\n";
					//	cout << "buffer len: " << buffer.size() << "\n";
					ofstream ofs("buffer.txt", ios::out);
					ofs << buffer;
					ofs.close();
					ifstream ifs("buffer.txt", ios::in);
					string temp;
					content = "";
					while (!ifs.eof()) {
						getline(ifs, temp);
						content += temp + '\n';
					}
					//	cout << "current content: " << "\n";
					system("cls");
					viewer.editorForEdit(title);

					cout << "\n";

					//	cout << "\n=========================\n";
					ifs.close();
					bufferIter = buffer.end() + iterOffset;

					//	buffer.insert(bufferIter, '|');
					cout << buffer;
					//buffer.erase(bufferIter);

					viewer.setCursor(cursorX, cursorY);
				}
				if (state = BOARD) {
					break;
				}
			}
		}
		else if (state == MAIL) {	
			


			int ch1 = 0;
			int ch2 = 0;
			int current_select = 0;
			viewer.mailLobby(current_select);
			while (!cin.eof())
			{
				if (ch1 = _getch())
				{//98 109 99 108

					//如果是方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值

					if (ch1 == 224) {
						ch2 = _getch();

						if (ch2 == 72) {
							//up
							current_select--;

						}
						else if (ch2 == 80) {
							//down 往下index增加
							current_select++;

						}
						else if (ch2 == 75) {
							//left
							state = LOBBY;
							break;
						}
						else if (ch2 == 77) {
							//right
							//enter the page
							current_select %= 2;
							if (current_select == 0) {
								state = INBOX;
							}
							else if (current_select == 1) {
								state = SEND;
							}
							break;

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));
							continue;
						}
					}
					viewer.mailLobby(current_select);
				}
				
			}

			/*
			string sTmp;
			while (cin >> sTmp) {
				if (sTmp == "R") {	//進入收信閘
					state = READ_MAIL;
				}
				else if (sTmp == "S") {	//寄信
					state = SEND_MAIL;
				}
				else if (sTmp == "E") {	//回上一頁
					state = LOBBY;
				}
				else {
					viewer.error("Error!Please enter again.");
					viewer.setCursor(0, 15);
				}
			}
			*/
		}
		else if (state == INBOX) {
			int mailIndex = 0;
			bool keepRead = true;
			vector<string> fromWho;
			vector<string> timeStamp;
			vector<string> mailTitle;
			vector<string> temp;
			ifstream ifs;
			while (keepRead) {
				temp.clear();
				ifs.open("MailBox/" + users[current_user]->getUserName() + "_" + to_string(mailIndex) + ".txt", ios::in);
				if (!ifs) {
					keepRead = false;
					
				}
				else {
					mailIndex++;


					string temp_str;
					fflush(stdin);
					//cin.get();
					while (!ifs.eof() && temp.size() < 3) {
						getline(ifs, temp_str);
						temp.push_back(temp_str);
					}
					if (temp.size() >= 3) {
						//沒有就壞檔
						fromWho.push_back(temp[0]);
						mailTitle.push_back(temp[1]);
						timeStamp.push_back(temp[2]);

					}
					else {
						system("cls");
						viewer.error("郵件檔案損毀, 有找到檔案, 但檔案未指示寄件者及其詳細資料");
						Sleep(2000);
						state = LOBBY;
						break;
					}

				}
				ifs.close();
			}
			//顯示所有郵件
			int ch1, ch2;
			int current_select = 0;
			if (fromWho.size() == 0) {

				state = MAIL;
				viewer.error("您目前沒有任何信件");
			//	viewer.error("您目前沒有任何信件, 系統將於2秒後跳轉");
				Sleep(2000);
				continue;
				
			}
			else {

				viewer.showMailBox(fromWho, timeStamp, mailTitle, current_select);
				while (!cin.eof())
				{
					if (ch1 = _getch())
					{
						if (ch1 == 224) {
							ch2 = _getch();
							if (ch2 == 72) {
								//up
								current_select--;

							}
							else if (ch2 == 80) {
								//down 往下index增加
								current_select++;

							}
							else if (ch2 == 75) {
								//left
								state = MAIL;
								break;
							}
							else if (ch2 == 77) {
								//right
								//enter the page
								current_select_mail_index = current_select;
								state = READ_MAIL;
								break;

							}
							else {
								//do nothings
								viewer.error(to_string(ch2));
								continue;
							}

							if (current_select >= fromWho.size()) {
								current_select = 0;
							}
							else if (current_select < 0) {
								current_select = fromWho.size() - 1;
							}

							viewer.showMailBox(fromWho, timeStamp, mailTitle, current_select);
							//	viewer.lobby(current_select, users[current_user]->getUserPermission());

						}
					}
				}
			}
		}
		else if (state == SEND) {
		string toWho;
		fflush(stdin);
			viewer.askTo();
			cin >> toWho;
			if (toWho == "!") {
				state = MAIL;
				continue;
			}
			else {
				if (users[current_user]->isUserExist(toWho)) {
					//可接受的收件者
					string title;
					//char ch_tmp = _getch();
					
					viewer.askMailTitle();
					fflush(stdin);
					bool firstIgnore = true;
					getline(cin, title);
					while (title == "") {
						if (firstIgnore) {
							firstIgnore = false;
							
						}
						else {

							viewer.error("標題不得為空, 如需離開請輸入!");
							Sleep(1000);
						}
						system("cls");
						viewer.askMailTitle();
						getline(cin, title);
					}
					//進editior


					viewer.editorForMail(title);

					vector<string> content;
					int ch1 = 0;
					int ch2 = 0;
					int previousX = 0;
					int cursorX = 0;
					int cursorY = 6;
					viewer.setCursor(cursorX, cursorY);

					while (!cin.eof())
					{//59=f1   224->83=del



						int c1;
						fflush(stdin);
						string buffer = "";
						string content;
						bool chineseMove = false;
						auto bufferIter = buffer.end();
						int iterOffset = 0;
						bool functionKey = false;
						while (c1 = _getch()) {



							//	cout << "d: " << c1 << "\n";
							if (functionKey) {
								char ctmp;
								if (bufferIter == buffer.begin()) {
									cursorX = 0;
									viewer.setCursor(cursorX, cursorY);
									functionKey = false;
									bufferIter = buffer.end() + iterOffset;
									if (c1 == 75)
										continue;
									else
										ctmp = 0;
								}
								else {
									ctmp = *(bufferIter - 1);
								}


								if (c1 == 72) {
									//up


								}
								else if (c1 == 80) {
									//down


								}
								else if (c1 == 75) {
									//left
									cursorX--;
									if (ctmp == '\n') {
										cursorX = previousX;
										cursorY--;
										iterOffset--;
									}
									else if (ctmp < 0) {
										cursorX--;

										iterOffset -= 2;

									}
									else {
										iterOffset -= 1;
									}
									if (iterOffset > 0)
										iterOffset = 0;
									bufferIter = buffer.end() + iterOffset;

								}
								else if (c1 == 77) {
									//right
									if (bufferIter == buffer.end()) {
										functionKey = false;
										iterOffset = 0;
										bufferIter = buffer.end() + iterOffset;

										continue;
									}
									else if (bufferIter == buffer.end() - 1) {
										functionKey = false;
										iterOffset += 1;
										cursorX++;
										iterOffset = 0;
										bufferIter = buffer.end() + iterOffset;
										viewer.setCursor(cursorX, cursorY);
										continue;
									}
									else if (bufferIter == buffer.end() - 2) {
										functionKey = false;
										iterOffset += 1;
										cursorX++;
										iterOffset = -1;
										if (*(bufferIter) < 0) {
											iterOffset += 1;
											cursorX++;
											iterOffset = 0;
										}
										viewer.setCursor(cursorX, cursorY);
										bufferIter = buffer.end() + iterOffset;
										continue;
									}

									cursorX++;
									bufferIter = buffer.end() + iterOffset;


									char ctmp = *(bufferIter + 1);
									char ctmp2 = *(bufferIter + 2);
									char curr = *(bufferIter);
									if (curr == '\n') {
										previousX = --cursorX;
										cursorY++;
										cursorX = 0;
										iterOffset++;
									}
									else if (ctmp < 0 || ctmp2 < 0) {
										cursorX++;
										iterOffset += 2;
									}
									else {


										iterOffset += 1;
									}
									if (iterOffset > 0)
										iterOffset = 0;
									bufferIter = buffer.end() + iterOffset;

								}
								else if (c1 == 83) {
									//del

								}

								functionKey = false;
								viewer.setCursor(cursorX, cursorY);
								continue;

							}
							if (c1 == 224) {
								functionKey = true;
								continue;
							}
							else if (c1 == 96) {
								//f1
								//post
								time_t rawtime;
								struct tm* timeinfo;
								time(&rawtime);
								timeinfo = localtime(&rawtime);
								char year[5], mon[3], mday[3], hour[3], minute[3], sec[3];
								sprintf(year, "%d", timeinfo->tm_year + 1900);
								sprintf(mon, "%d", timeinfo->tm_mon + 1);
								sprintf(mday, "%d", timeinfo->tm_mday);
								sprintf(hour, "%d", timeinfo->tm_hour);
								sprintf(minute, "%d", timeinfo->tm_min);
								sprintf(sec, "%d", timeinfo->tm_sec);
								string times = year;
								times += "/";
								times += mon;
								times += "/";
								times += mday;
								times += " ";
								times += hour;
								times += ":";
								times += minute;
								times += ":";
								times += sec;


								//寫檔
								int findIndex = 0;
								bool keepRead = true;
								ifstream ifs;
								while (keepRead) {
								ifs.open("MailBox/"+toWho + "_" + to_string(findIndex) + ".txt", ios::in);
								if (!ifs) {
									
									break;
								}
								else {
									findIndex++;
								}
								ifs.close();
								}
								ofstream ofs("MailBox/" + toWho + "_" + to_string(findIndex) + ".txt", ios::out);
								ofs << users[current_user]->getUserName() << "\n";
								ofs << title << "\n";
								ofs << times << "\n";
								ofs << buffer << "\n";
								ofs.close();
									//succ
								system("cls");
								viewer.successful("成功寄信給" + toWho + " 系統將於2秒後跳轉");
								Sleep(2000);


									state = MAIL;
									break;
							

							}
							else if (c1 == 27) {
								//esc
								state = MAIL;
								break;
							}
							else if (c1 == 8) {
								//backspace


								char ctmp = 0, ctmp2 = 0;
								if (buffer.size() >= 1)
								{
									ctmp = buffer[buffer.size() - 1];
								}
								else {
									continue;
								}
								if (buffer.size() >= 2)
									ctmp2 = buffer[buffer.size() - 2];

								cursorX--;
								if (ctmp < 0 || ctmp2 < 0) {
									cursorX--;
									if (buffer.size() > 0)
										buffer.erase(buffer.end() - 1);
									if (buffer.size() > 0)
										buffer.erase(buffer.end() - 1);
								}
								else {

									if (buffer.size() > 0)
										buffer.erase(buffer.end() - 1);
								}

							}
							else if (c1 == 13) {
								buffer.insert(bufferIter, '\n');
								previousX = cursorX;
								cursorX = 0;
								cursorY++;

								viewer.setCursor(cursorX, cursorY);
							}
							else {

								buffer.insert(bufferIter, c1);
								if (!chineseMove)
									cursorX++;

								if (c1 < 0) {
									cursorX++;
									chineseMove = true;
									iterOffset += 2;
									if (iterOffset > 0)
										iterOffset = 0;
								}
								else {
									chineseMove = false;
								}
							}

							//	buffer.push_back(c1);

							//	cout << "buffer: " << buffer << "\n";
							//	cout << "buffer len: " << buffer.size() << "\n";
							ofstream ofs("buffer.txt", ios::out);
							ofs << buffer;
							ofs.close();
							ifstream ifs("buffer.txt", ios::in);
							string temp;
							content = "";
							while (!ifs.eof()) {
								getline(ifs, temp);
								content += temp + '\n';
							}
							//	cout << "current content: " << "\n";
							system("cls");
							viewer.editorForMail(title);

							cout << "\n";




							//	cout << "\n=========================\n";
							ifs.close();
							bufferIter = buffer.end() + iterOffset;

							//	buffer.insert(bufferIter, '|');
							cout << buffer;
							//buffer.erase(bufferIter);

							viewer.setCursor(cursorX, cursorY);
						}
						if (state == MAIL) {
							break;
						}
					}








				}
				else {
					viewer.error("抱歉！此用戶不存在");
					Sleep(1000);

					state = MAIL;
					continue;
				}
			}
		}
		else if (state == READ_MAIL) {
			ifstream ifs("MailBox/" + users[current_user]->getUserName() + "_" + to_string(current_select_mail_index) + ".txt", ios::in);
			if (!ifs) {
				viewer.error("讀取郵件失敗");
				Sleep(2000);
				state = LOBBY;
				continue;
			}
			else {
				string title;
				string time;
				string content = "";
				string fromWho;
				int lines = 0;
				string temp;
				
				while (!ifs.eof()) {
					getline(ifs, temp);
					if (lines == 0) {
						fromWho = temp;
					}
					else if (lines == 1) {
						title = temp;
					}
					else if (lines == 2) {
						time = temp;
					}
					else {
						content += temp + "\n";
					}
					++lines;
				}
				ifs.close();
				int ch1, ch2;
				viewer.showMailContent(fromWho, title, time, content);
				//cin.get();
				fflush(stdin);
				while (!cin.eof())
				{

					if (ch1 = _getch())
					{

						state = INBOX;
						break;

					}
				}
			}
		}
		else if (state == GAME) {

			int ch1 = 0;
			int ch2 = 0;
			int current_select = 0;
			viewer.gameLobby(current_select);
			while (!cin.eof())
			{
				if (ch1 = _getch())
				{//98 109 99 108

					//如果是方向鍵 ch1會讀到224 ch2會讀到屬於該按鍵的值

					if (ch1 == 224) {
						ch2 = _getch();

						if (ch2 == 72) {
							//up
							current_select--;

						}
						else if (ch2 == 80) {
							//down 往下index增加
							current_select++;

						}
						else if (ch2 == 75) {
							//left
							state = LOBBY;
							break;
						}
						else if (ch2 == 77) {
							//right
							//enter the page
							current_select %= 3;
							if (current_select == 0) {
								state = GAME_1;
							}
							else if (current_select == 1) {
								state = GAME_2;
							}
							else if (current_select == 2) {
								state = GAME_3;
							}
							break;

						}
						else {
							//do nothings
							viewer.error(to_string(ch2));
							continue;
						}
					}
					viewer.gameLobby(current_select);
				}

			}

		}
		else if (state == GAME_1) {
			int min = 0, max = 100, attempt = 0;
			int guess;
			bool inGame = true;
			int ans = rand() % 99 + 1;
			viewer.game1(min, max, attempt);
			fflush(stdin);
			while (inGame){
				cin >> guess;
				if (guess == -1) {
					inGame = false;					
					break;
				}
				if (!(guess > min && guess < max)) {
					viewer.error("您必須猜測 " + to_string(min+1) + " 到 " + to_string(max-1) + " 的數值, 或使用-1離開");
					Sleep(1500);
				}
				else if(guess == ans){
				
					viewer.successful("您猜對了, 答案是 " + to_string(ans) + " !");
					Sleep(1500);
					inGame = false;
					break;				
				}
				else {
					if (guess < ans) {
						min = guess;
					}
					else {
						max = guess;
					}
					attempt++;
				}
				viewer.game1(min, max, attempt);
			}


			state = GAME;

		}
		else if (state == GAME_2) {
			//賭大小

			int dice[3] = { -1 };
			int moneyHave = 1000;	//剩餘金額
			int type=-1;	//下注類型
			int moneyBet=-1;	//下注金額
			int winner = -1;
			int diceGuess1 = -1,diceGuess2 = -1;

			bool exitGame = false;

			while (1) {
				viewer.game2(moneyHave,type,moneyBet,dice,winner,diceGuess1, diceGuess2);
				
				//type
				viewer.setCursor(22, 13);
				while (cin >> type) {

					if (type == -1) {
						state = GAME;
						exitGame = true;
						break;
					}
					else if (type < 1 || type>6) {
						viewer.error("請選擇1~6之間的下注方式");
						Sleep(1000);
						viewer.clearRow(0, 0);
						viewer.clearRow(22, 13);
					}
					else {
						viewer.game2(moneyHave, type, moneyBet, dice, winner, diceGuess1, diceGuess2);

						if (type == 1 || type == 2 || type == 6) {
							break;
						}
						else if (type == 3) {
							viewer.setCursor(49, 13);
							while (cin >> diceGuess1) {
								if (diceGuess1 < 1 || diceGuess1 > 6) {
									viewer.error("骰子點數需為1~6點");
									Sleep(1000);
									viewer.clearRow(0, 0);
									viewer.clearRow(49, 13, 7);
								}
								else
									break;
							}
							viewer.setCursor(67, 13);
							while (cin >> diceGuess2) {
								if (diceGuess2 < 1 || diceGuess2>6) {		
									viewer.error("骰子點數需為1~6點");
									Sleep(1000);
									viewer.clearRow(0, 0);
									viewer.clearRow(67, 13);
								}
								else if (diceGuess1 == diceGuess2) {
									viewer.error("猜測骰子點數不可一樣");
									Sleep(1000);
									viewer.clearRow(0, 0);
									viewer.clearRow(67, 13);
								}
								else
									break;
							}
							break;
						}
						else if (type == 4 || type == 5) {
							viewer.setCursor(49, 13);
							while (cin >> diceGuess1) {
								if (diceGuess1 < 1 || diceGuess1 > 6) {
									viewer.error("骰子點數需為1~6點");
									Sleep(1000);
									viewer.clearRow(0, 0);
									viewer.clearRow(49, 13);
								}
								else
									break;
							}
							break;
						}
					}
				}
				if (exitGame)
					break;
				
				//moneyBet
				viewer.setCursor(22, 16);
				while (cin >> moneyBet) {
					if (moneyBet <= 0) {
						viewer.error("下注金額須為正數");
						Sleep(1000);
						viewer.clearRow(0, 0);
						viewer.clearRow(22, 16);
					}
					else {
						viewer.game2(moneyHave, type, moneyBet, dice, winner, diceGuess1, diceGuess2);
						break;
					}
				}

				//result
				for (int i = 0; i <= 2; i++)
					dice[i] = rand() % 6 + 1;


				if (type == 1) {
					if (dice[0] + dice[1] + dice[2] >= 11) {
						winner = 1;
						moneyHave += moneyBet;
					}	
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				else if (type == 2) {
					if (dice[0] + dice[1] + dice[2] <= 10) {
						winner = 1;
						moneyHave += moneyBet;
					}
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				else if (type == 3) {
					int matchTimes = 0;
					for (int i = 0; i <= 2; i++) {
						if (dice[i] == diceGuess1) {
							matchTimes++;
							break;
						}	
					}
					for (int i = 0; i <= 2; i++) {
						if (dice[i] == diceGuess2) {
							matchTimes++;
							break;
						}
					}

					if (matchTimes==2) {
						winner = 1;
						moneyHave += moneyBet * 5;
					}
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				else if (type == 4) {
					int matchTimes = 0;
					for (int i = 0; i <= 2; i++) {
						if (dice[i] == diceGuess1)
							matchTimes++;
					}

					if (matchTimes >= 2) {
						winner = 1;
						moneyHave += moneyBet * 8;
					}
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				else if (type == 5) {
					int matchTimes = 0;
					for (int i = 0; i <= 2; i++) {
						if (dice[i] == diceGuess1)
							matchTimes++;
					}

					if (matchTimes == 3) {
						winner = 1;
						moneyHave += moneyBet * 150;
					}
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				else if (type == 6) {
					if (dice[0]==dice[1] && dice[0] == dice[2]) {
						winner = 1;
						moneyHave += moneyBet * 24;
					}
					else {
						winner = 0;
						moneyHave -= moneyBet;
					}
				}
				viewer.game2(moneyHave, type, moneyBet, dice, winner, diceGuess1, diceGuess2);

				Sleep(8000);

				//data reset
				dice[0] = -1;
				type = -1;	
				moneyBet = -1;	
				winner = -1;
				diceGuess1 = -1;
				diceGuess2 = -1;
				
				
			}
			
			



		}
		else if (state == GAME_3) {
			int money = 1000;
			double rate[8];
			int progress[8];
			int method, pay, target;
			vector<int> winTarget;
			bool isPlaying = true;
			bool isFinish = false;
			bool isWin = false;
			bool restart = false;
			bool reset = true;
			while (isPlaying) {
				isFinish = false;
				restart = false;
				if (reset) {
					reset = false;
					winTarget.clear();
					for (int i = 0; i < 8; i++) {
						rate[i] = rand() % 721 + 80;
						rate[i] /= 100;
					}
				}
				viewer.game3Init(money, rate);

				fflush(stdin);
				cin >> method;
				if (method == 3) {
					break;
				}
				while (method != 1 && method != 2 && method != 3) {				
					viewer.error("遊戲方式有誤, 請重新選擇");
					Sleep(1500);
					viewer.game3Init(money, rate);
					cin >> method;
				}
				if (method == 2) {
					for (int i = 0; i < 8; i++)
						rate[i] *= 0.333;
				}
				viewer.game3askTarget();
				cin >> target;
				while (!(target>=1 && target<=8)) {
					viewer.error("馬匹選擇有誤, 請重新選擇");
					Sleep(1500);
					restart = true;
					break;
				}
				if (restart)
					continue;
				viewer.game3askMoney();
				cin >> pay;
				while (pay > money) {
					viewer.error("下注金額不得超過自身金額, 請重新輸入");
					Sleep(1500);
					restart = true;
					break;
				}
				if (restart)
					continue;
				//start
				isWin = false;
				for (int i = 0; i < 8; i++)
					progress[i] = 0;

				viewer.game3Field(progress, target);
				Sleep(200);
				while (!isFinish) {
					if (winTarget.size() >= 8){
						isFinish = true;
						break;
					}
					for (int i = 0; i < 8; i++) {
						progress[i] += rand() % 3 + 1;
						progress[i] += rand() % (8 - (int)rate[i]);
						if (progress[i] >= 100) {
							progress[i] = 100;
							if (find(winTarget.begin(), winTarget.end(), i + 1) != winTarget.end())
								continue;
							if ((i + 1) == target) {
								if (method == 1) {
									if(winTarget.size() == 0)
										isWin = true;
								}
								else if (method == 2) {
									if (winTarget.size() < 3)
										isWin = true;
								}
							}
							winTarget.push_back(i+1);
						}
					}
					viewer.game3Field(progress, target);
					Sleep(200);
				}
				Sleep(1000);
				int char1;
				if (isWin) {
					money += rate[target - 1] * pay;
					viewer.game3Win(winTarget, target);
					fflush(stdin);
					char1 = _getch();
				}
				else {
					money -= pay;
					viewer.game3Lose(winTarget, target);
					fflush(stdin);
					char1 = _getch();

				}
				reset = true;
				if (money <= 0) {
					system("cls");
					viewer.error("抱歉！您的賭金不足, 賽馬場的主人已經把你趕出來了");
					Sleep(2000);
					state = GAME;
					break;
				}
			}
			state = GAME;
			continue;
		}
	}
}

//讀取文字檔user資訊
void BoardManager::getUser() {
	users.clear();
	ifstream ifs;

	ifs.open("userData.txt", ios::in);

	if (!ifs)
		cout << "Can't open userData.txt." << endl;
	else {

		User userTmp;
		string tmpU, tmpP;
		int tmpI;

		while (!ifs.eof()) {
			ifs >> tmpU;
		//	userTmp.setUserName(tmp);
			ifs >> tmpP;
		//	userTmp.setUserPswd(tmpS);
			ifs >> tmpI;
		//	userTmp.setUserPermission(tmpI);
		//	users.push_back(new Adiministrator());
			if (tmpI == 0) {
				users.push_back(new Guest(tmpU, tmpP, tmpI));
			}
			else if (tmpI == 1) {
				users.push_back(new Member(tmpU, tmpP, tmpI));
			}
			else if (tmpI == 2) {
				users.push_back(new Adiministrator(tmpU, tmpP, tmpI));
			}
			else {
				viewer.error("unknown permission");
				exit(0);
			}


			//postsID GET
			ifstream ifs2;
			int postIndex = 2;
			bool keepRead = true;
			while (keepRead) {
				ifs2.open("Post/" + to_string(postIndex) + ".txt", ios::in);
				if (!ifs2) {
					keepRead = false;
				}
				else {
					string temp_str;
					vector<string> temp;
					while (!ifs2.eof() && temp.size() < 3) {
						getline(ifs2, temp_str);
						temp.push_back(temp_str);
					}
					if (temp.size() == 3) {
						if (temp[2] == users[users.size() - 1]->getUserName()) {
							users[users.size() - 1]->postsID.push_back(postIndex);
						}
					}
					else {
						keepRead = false;
					}
					postIndex++;
				}
				ifs2.close();
			}			


		}

	}
	ifs.close();
}
/*


			cin.get();
			Post myPost = boards[current_select_board].posts[current_select_post];
			string title;
			system("cls");
			cout << "原標題：" << boards[current_select_board].posts[current_select_post].getTitle() << "\n";
			cout << "----若要放棄編輯, 請輸入   '!'   繼續----\n";
			cout << "----若不更改標題, 請按下 [Enter] 繼續----\n";
			cout << "新標題：";
			getline(cin, title);
			if (title == "") {
				title = myPost.getTitle();
			}
			if (title == "!") {
				state = POST;
				continue;
			}
			viewer.editor(title);


			int ch1 = 0;
			int ch2 = 0;
			int previousX = 0;
			int cursorX = 0;
			int cursorY = 6;
			viewer.setCursor(cursorX, cursorY);
			while (!cin.eof())
			{//59=f1   224->83=del



				int c1;
				fflush(stdin);
				string buffer = "";
				string content;
				buffer = myPost.getContent();
				bool chineseMove = false;
				auto bufferIter = buffer.end();
				int iterOffset = 0;
				bool functionKey = false;
				while (c1 = _getch()) {

				
				
				
				*/
void BoardManager::getBoard() {
	boards.clear();
	//vector<string> boardName;
	ifstream ifs;
	ifs.open("Board/boardList.txt", ios::in);
	if (!ifs)
		cout << "Can't open Board/boardList.txt" << endl;
	else {
		string boardNameTemp;
		while (!ifs.eof()) {
			getline(ifs,boardNameTemp);
			//ifs >> boardNameTemp;
			if (boardNameTemp == "")
				continue;
			boards.push_back(Board(boardNameTemp));
		}
	}
	ifs.close();
	//update boards amount
	post_num = 0;
	ifs.open("Post/postList.txt", ios::in);
	if (!ifs) {
		cout << "Can't update post amount while opening postList.txt";
	}
	else {
		string buffer;
		while (!ifs.eof()) {
			ifs >> buffer;
			post_num++;
		}
	}
	ifs.close();
	//Board::setBoardAmount(boards.size());
}
