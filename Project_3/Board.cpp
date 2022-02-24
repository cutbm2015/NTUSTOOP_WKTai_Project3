#include "Board.h"

using namespace std;
Board::Board() {};
Board::Board(string filename) {
	posts.clear();//�M���ӪO���U��posts
	name = "";
	bool readSuccess = true;
	if (filename == "") {
		cout << "boardList.txt is empty (no board exist)" << endl;
		return;
	}
	ifstream ifs;
	ifs.open("Board/" + filename, ios::in);
	if (!ifs) {
		cout << "Can't open Board/" << filename << "" << endl;
		readSuccess = false;
	}
	else {
		vector<string> data;
		string temp;
		/*
			name(�W��)
			popularity(+15/-30/*50)	(+:��	-:�N	*:�b�Y)
			viewAmount(�[�ݤH��, �i�ݪO�N+1)
			introduction(�p�Y�g�峹�����D)
		*/

		while (!ifs.eof()) {
			ifs >> temp;
			data.push_back(temp);
		}
		if (data.size() < 4) {
			cout << "reading " << filename << " occurred data missing" << endl;
			readSuccess = false;
		}
		else {
			name = data[0];
			popularity = atoi(data[1].c_str());
			viewAmount = atoi(data[2].c_str());
			introduction = data[3];


		}
	}
	ifs.close();
	//Ū��posts
	if (readSuccess) {

		ifs.open("Post/postList.txt", ios::in);
		if (!ifs) {
			cout << "Can't open postList.txt while reading post" << endl;
		}
		else {
			string temp;
			vector<string> postFileName;
			while (!ifs.eof()) {
				getline(ifs, temp);
				postFileName.push_back(temp);
			}
			ifs.close();

			for (string filename : postFileName) {
				if (filename == "")
					continue;
				ifs.close();
				ifs.open("Post/" + filename + ".txt", ios::in);
				if (!ifs) {
					
					cout << "Can't open Post/" << filename << ".txt while reading post" << endl;
					Sleep(1000);
				}


/*
boardName(string)
postID(int)
username(author��s)
status(���0 / �R��1)
reason(�R������])
title(�峹���D)
timestamp(�ɶ��W, YYYY/MM/DD HH:MM:SS)
��
�N
�b�Y
content(�峹���e)
*/
				string temp;
				string content = "";
				vector<string> postDetails;
				while (!ifs.eof()) {
					getline(ifs, temp);
					postDetails.push_back(temp);
					
				}
				if (postDetails.size() < 11)
					continue;
				if (postDetails[0] != name) {
					//�峹���ݩ�Ӥl��
					continue;
				}
				
				Post p;
				p.setBoardName(name);
				p.setPostID(atoi(postDetails[1].c_str()));
				p.setAuthor(postDetails[2]);
				p.setStatus(atoi(postDetails[3].c_str()));
				p.setDeleteReason(postDetails[4]);
				p.setTitle(postDetails[5]);
				p.setTimestamp(postDetails[6]);

				p.setLike(atoi(postDetails[7].c_str()));
				p.setDislike(atoi(postDetails[8].c_str()));
				p.setComment(atoi(postDetails[9].c_str()));

				



				postDetails.erase(postDetails.begin(), postDetails.begin()+10);

				for (string s : postDetails) {
					content += s + "\n";
				}

				p.setContent(content);
				
				posts.push_back(p);
			
			
				ifs.close();
			}			
		}
		
	}
	ifs.close();
}

bool Board::isValidBoardName(string boardName) {
	for (char c : boardName) {
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
			//invalid boardname
			return false;
		}
	}
	//�g�ɮ�(boardList)
	boardName = boardName + ".txt";
	string temp;
	ifstream ifs;
	ifs.open("Board/boardList.txt", ios::in);
	if (!ifs) {
		cout << "Can't read Board/boardList.txt when check valid board name" << endl;
	}
	else {
		while (!ifs.eof()) {
			ifs >> temp;
			if (temp == boardName){
				ifs.close();
				return false;
			}
		}
	}
	ifs.close();
	return true;
}
Board Board::createBoard(string boardName, string intro) {
	Board result;
	result.name = boardName;
	result.popularity = 0;
	result.viewAmount = 0;
	result.introduction = intro;
	
	//�g�ɮ�(boardList)
	ofstream ofs;
	ofs.open("Board/boardList.txt", ios::app);	//�q�����}�l�g�J
	if (!ofs)
		cout << "Can't open Board/boardList.txt when createBoard" << endl;
	else {
		ofs << boardName << ".txt\n";
	}
	ofs.close();
	//�g�W���ɮ�
	
	ofs.open("Board/" + boardName+ ".txt", ios::out);	
	if (!ofs)
		cout << "Can't wrtie Board/"<< boardName << ".txt when createBoard" << endl;
	else {
		ofs << boardName << "\n";
		ofs << result.popularity << "\n";
		ofs << result.viewAmount << "\n";
		ofs << result.introduction << "";
	}
	ofs.close();

	return result;
}
void Board::increaseViewAmount() {

	//�g�ɮ�(boardList)
	ofstream ofs;
	ofs.open("Board/" + getName() + ".txt", ios::out);	//
	if (!ofs){
		cout << "Can't open Board/"<<getName()<<".txt when increasing view amount" << endl;
}
	else {
	
			ofs << getName() << "\n";
			ofs << getPopularity() << "\n";
			ofs << getViewAmount()+1 << "\n";
			ofs << getIntroduction() << "";
		
	}
	ofs.close();

	return;
}
void Board::doDelete(vector<Board> boards) {
	//�g�ɮ�(boardList)
	ofstream ofs;
	ofs.open("Board/boardList.txt", ios::out);	//�������g
	if (!ofs)
		cout << "Can't open Board/boardList.txt when deleteBoard" << endl;
	else {
		for (Board b : boards) {
			if (b.name == this->name) {
				//���g
			}
			else {
				ofs << b.name << ".txt\n";
			}
		}
	}
	ofs.close();
}
string Board::getName() {
	return name;
}
string Board::getIntroduction() {
	return introduction;
}
void Board::setName(string name) {
	this->name = name;
}
void Board::setIntroduction(string intro) {
	this->introduction = intro;
}
int Board::getPopularity() {
	return popularity;
}
void Board::setPopularity(int p) {
	this->popularity = p;
}
int Board::getViewAmount() {
	return viewAmount;
}
void Board::setViewAmount(int v) {
	this->viewAmount = v;
}
/*
int Board::getBoardAmount() {
	return boardAmount;
}
void Board::setBoardAmount(int b) { 
	boardAmount = b;
}*/