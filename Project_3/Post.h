#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

class Post {
public:

	Post() {};
	Post(int postID, int status, string boardName,string deleteReason, string author, string title,string timestamp, string content);
	bool doPost(Post myPost);

	void setPostID(int);
	void setTitle(string);
	void setStatus(int);
	void doDelete(string reason);
	void setAuthor(string);
	void setContent(string content);
	void setTimestamp(string timestamp);
	void setBoardName(string);
	void setDeleteReason(string);
	
	void setLike(int);
	void setDislike(int);
	void setComment(int);
	bool isCommentAuthor(int, string);
	bool isLikeOrDislikeAvailable(string username);
	bool fileUpdate();
	bool isDelete();
	bool doComment(string username, string type, string content);
	bool doDeleteComment(int floor, string reason);

	int getPostID();
	
	int getLike();
	int getDislike();
	int getComment();

	string getBoardName();
	string getDeleteReason();
	string getAuthor();
	string getTitle();
	string getTimestamp();
	string getContent();

private:
	
	int postID;
	int like;
	int dislike;
	int comment;
	int status;
	string boardName;
	string deleteReason;
	string author;
	string title;
	string timestamp;
	string content;
	
};
