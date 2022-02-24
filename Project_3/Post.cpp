#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Post.h"


//Post::Post();
Post::Post(int postID, int status, string boardName, string deleteReason, string author, string title, string timestamp, string content) {
	this->postID = postID;
	this->status = status;
	this->boardName = boardName;
	this->deleteReason = deleteReason;
	this->author = author;
	this->title = title;
	this->timestamp = timestamp;
	this->content = content;
};

bool Post::doPost(Post myPost) {
	ofstream ofs("Post/postList.txt", ios::app);
	if (!ofs) {
		//can't open 
		return false;
	}
	ofs << myPost.getPostID() << "\n";
	ofs.close();
	ofs.open("Post/" + to_string( myPost.getPostID()) + ".txt", ios::out);
	if (!ofs) {
		return false;
	}
	ofs << myPost.getBoardName() << "\n";
	ofs << myPost.getPostID() << "\n";
	ofs << myPost.getAuthor() << "\n";
	ofs << myPost.status << "\n";
	ofs << myPost.getDeleteReason() << "\n";
	ofs << myPost.getTitle() << "\n";
	ofs << myPost.getTimestamp() << "\n";
	ofs << 0 << "\n";
	ofs << 0 << "\n";
	ofs << 0 << "\n";
	ofs << myPost.getContent() << "\n";
	ofs.close();
	return true;

	//寫檔案
};
void Post::setLike(int l) {
	like = l;
};
void Post::setDislike(int d) {
	dislike = d;
};
void Post::setComment(int c) {
	comment = c;
};
void Post::setPostID(int p) {
	postID = p;
};
void Post::setTitle(string t) {
	title = t;
};
void Post::setStatus(int s) {
	status = s;
};
bool Post::isCommentAuthor(int floor, string _username) {
	vector<string> rawData;
	ifstream ifs("Comment/" + to_string(getPostID()) + ".txt", ios::in);
	if (!ifs) {
		//failed or no comment yet
		return false;
	}
	else {
		string temp;
		while (!ifs.eof()) {
			getline(ifs, temp);
			rawData.push_back(temp);
		}
		floor--; //1樓是資料的第0筆
		int dataCnt = 0;
		string username, status, reason, type, timestamp, content;
		for (int i = 0; (i + 5) < rawData.size(); i += 6) {
			if (floor == dataCnt) {				
				//開始判定
				username = rawData[i];
				status = rawData[i + 1];
				reason = rawData[i + 2];
				type = rawData[i + 3];
				timestamp = rawData[i + 4];
				content = rawData[i + 5];
				if (username == _username) {
					return true;
				}
				else {
					return false;
				}
			}
			++dataCnt;
		}
	}
	ifs.close();
	return false;
}
bool Post::isLikeOrDislikeAvailable(string _username) {
	vector<string> rawData;
	ifstream ifs("Comment/" + to_string(getPostID()) + ".txt", ios::in);
	if (!ifs) {
		//failed or no comment yet
		return true;
	}
	else {
		string temp;
		while (!ifs.eof()) {
			getline(ifs, temp);
			rawData.push_back(temp);
		}
	
		string username, status, reason, type, timestamp, content;
		for (int i = 0; (i + 5) < rawData.size(); i += 6) {
			username = rawData[i];
			status = rawData[i + 1];
			reason = rawData[i + 2];
			type = rawData[i + 3];
			timestamp = rawData[i + 4];
			content = rawData[i + 5];
			if (username == _username && (type == "1" || type == "0")) {
				return false;
			}
		}
	}
	ifs.close();
	return true;
}
bool Post::doComment(string username, string type, string content) {

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
	string times = "";
	if (mon[1] == '\0') {
		char temp = mon[0];
		mon[0] = '0';
		mon[1] = temp;
		mon[2] = '\0';
	}
	times += mon;
	times += "/";
	if (mday[1] == '\0') {
		char temp = mday[0];
		mday[0] = '0';
		mday[1] = temp;
		mday[2] = '\0';
	}
	times += mday;
	times += " ";
	if (hour[1] == '\0') {
		char temp = hour[0];
		hour[0] = '0';
		hour[1] = temp;
		hour[2] = '\0';
	}
	times += hour;
	times += ":";
	if (minute[1] == '\0') {
		char temp = minute[0];
		minute[0] = '0';
		minute[1] = temp;
		minute[2] = '\0';
	}
	times += minute;

	int typeInt = 0;
	if (type == "推") {
		this->like++;
		
		typeInt = 1;
	}
	else if (type == "噓") {
		this->dislike++;

		typeInt = 0;

	}
	else if (type == "箭頭") {
		this->comment++;

		typeInt = 2;

	}
	//寫檔案
	ofstream ofs("Comment/" + to_string(postID) + ".txt", ios::app);
	if (!ofs) {
		ofs.open("Comment/" + to_string(postID) + ".txt", ios::out);
		if (!ofs) {
			cout << "create comment file failed" << endl;
			Sleep(1000);
			return false;
		}
	}
	ofs << username << "\n";
	ofs << 0 << "\n";
	ofs << "" << "\n";
	ofs << typeInt << "\n";
	ofs << times << "\n";
	ofs << content << "\n";


	ofs.close();


	//更新推噓數量
	fileUpdate();
	return true;
}
bool Post::doDeleteComment(int floor, string reason) {
	vector<string> rawData;
	ifstream ifs("Comment/" + to_string(getPostID()) + ".txt", ios::in);
	if (!ifs) {
		//failed or no comment yet

		return false;
	}
	else {
		string temp;
		while (!ifs.eof()) {
			getline(ifs, temp);
			rawData.push_back(temp);
		}
		ifs.close();
		--floor; //1f是資料第0筆
		if ((floor * 6) + 5 < rawData.size()){
			rawData[floor * 6 + 1] = "1";
			rawData[floor * 6 + 2] = reason;
			if (rawData[floor * 6 + 3] == "1") {
				//推
				this->like--;
			}else 	if (rawData[floor * 6 + 3] == "0") {
				//噓
				this->dislike--;
			}else 	if (rawData[floor * 6 + 3] == "2") {
				//箭頭
				this->comment--;
			}
			
			//寫回去
			ofstream ofs("Comment/" + to_string(getPostID()) + ".txt", ios::out);
			for (int i = 0; i < rawData.size(); i++) {
				ofs << rawData[i] << "\n";
			}
			ofs.close();

			fileUpdate();

			return true;
		}
		else {
	
			return false;
		}
	
	}

	return true;
}
bool Post::fileUpdate() {
	//更新檔案
	ofstream ofs("Post/" + to_string(getPostID()) + ".txt", ios::out);
	if (!ofs) {
		cout << "updating file failed while updating file";
		Sleep(1000);
		ofs.close();
		return false;
	}
	else {
		status = 0;
		deleteReason = "";
		ofs << getBoardName() << "\n";
		ofs << getPostID() << "\n";
		ofs << getAuthor() << "\n";
		ofs << status << "\n";
		ofs << getDeleteReason() << "\n";
		ofs << getTitle() << "\n";
		ofs << getTimestamp() << "\n";
		ofs << getLike() << "\n";
		ofs << getDislike() << "\n";
		ofs << getComment() << "\n";
		ofs << getContent() << "\n";
	}
	ofs.close();
	return true;
}
void Post::doDelete(string reason) {
	//更新檔案
	ofstream ofs("Post/" + to_string(getPostID()) + ".txt", ios::out);
	if (!ofs) {
		cout << "delete failed while updating file";
		Sleep(1000);
		ofs.close();
		return;
	}
	else {	
		status = 1;
		deleteReason = reason;
		ofs << getBoardName() << "\n";
		ofs << getPostID() << "\n";
		ofs << getAuthor() << "\n";
		ofs << status << "\n";
		ofs << getDeleteReason() << "\n";
		ofs << getTitle() << "\n";
		ofs << getTimestamp() << "\n";
		ofs << 0 << "\n";
		ofs << 0 << "\n";
		ofs << 0 << "\n";
		ofs << getContent() << "\n";		
	}
	ofs.close();
};
void Post::setAuthor(string a) {
	author = a;
}
void Post::setContent(string content) {
	this->content = content;
};
void Post::setTimestamp(string timestamp) {
	this->timestamp = timestamp;
};
void Post::setBoardName(string b) {
	boardName = b;
};
void Post::setDeleteReason(string d) {
	deleteReason = d;
};
bool Post::isDelete() {
	if (status == 1) {
		return true;
	}
	else {
		return false;
	}
};
int Post::getPostID(){
	return postID;
};
int Post::getLike() {
	return like;
};
int Post::getDislike() {
	return dislike;
};
int Post::getComment() {
	return comment;
};
string Post::getBoardName() {
	return boardName;
};
string Post::getDeleteReason() {
	return deleteReason;
};
string Post::getAuthor() {
	return author;
};
string Post::getTitle() {
	return title;
};
string Post::getTimestamp() {
	return timestamp;
};
string Post::getContent() {
	return content;
};