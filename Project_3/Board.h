#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>

#include "Post.h"

using namespace std;

class Board {
public:
	Board();
	Board(string filename);

	static bool isValidBoardName(string name);
	static Board createBoard(string name, string intro);
	string getName();
	string getIntroduction();
	void setName(string);
	void setIntroduction(string);
	int getPopularity();
	void increaseViewAmount();
	void setPopularity(int);
	int getViewAmount();
	void setViewAmount(int);
	void doDelete(vector<Board>);
	//static int getBoardAmount();
	//static void setBoardAmount(int);
	vector<Post> posts;
private:
	//static int boardAmount;

	string name;
	string introduction;
	int popularity;
	int viewAmount;
	
};
