#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>
#include "Post.h"
#include "Board.h"
#include "User.h"
#include "Viewer.h"

using namespace std;

enum BoardState {
    CREATE_POST,
    DELETE_POST,
    DELETE_BOARD,
    MENU, //default
    LOBBY,
    SELECT_BOARD, //default
    BOARD, //default
    POST, //default
    MAIL,
    GAME,
    INBOX,
    SEND,
    SEND_MAIL,
    READ_MAIL,
    CREATE_BOARD,
    EDIT_POST,
    GAME_1,
    GAME_2,
    GAME_3,
};
class BoardManager {
public:

    BoardManager();

    void getUser();
    void getBoard();
    void createBoard();

    void startBoard();
    vector <User*> users; //req
    vector <Board> boards; //req
    int current_user; //req
    BoardState state; //req
    Viewer viewer; //req
private:
    int selected_board = 0;
    int post_num = 0;
};
