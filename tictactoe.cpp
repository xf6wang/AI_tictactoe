#include <iostream>

#define BOARD_LENGTH 3

extern void pretty_print(int board[]);
extern bool play(int board[]);
extern bool try_to_win(int b[]);
extern bool eliminate_threat(int b[]);
extern bool attack(int b[]);
extern bool claim_middle(int b[]);
extern int winner(int matrix[]);
extern void print_board(int b[]);

/*
0 1 2
3 4 5
6 7 8
*/
using namespace std;

int main(){

	cout << "Welcome to Tic Tac Toe, you play X" << endl;
	char play_again = 'Y';
	do{
		int x, y = 0;
		int board[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		do{
			pretty_print(board);
			cout << "Enter in the x then y co-ordinates to place a move (index at 0)" << endl;
			cin >> x >> y;
			while (x >= BOARD_LENGTH || y >= BOARD_LENGTH || x < 0 || y < 0 || board[y*BOARD_LENGTH + x] != 0){
				cout << "Invalid location, try again" << endl;
				cin >> x >> y;
			}
			board[y*BOARD_LENGTH + x] = 1;
		} while (play(board));

		pretty_print(board);
		cout << "Would you like to play again? (Y/N)" << endl;
		cin >> play_again;
	} while (play_again != 'N');
}

void print_board(int b[]){
	for (int i = 0; i < BOARD_LENGTH; i++){
		for (int j = 0; j < BOARD_LENGTH; j++){
			cout << b[i*BOARD_LENGTH + j];
		}
		cout << endl;
	}
	cout << endl;
}

bool play(int board[]){
	if (winner(board) == 1) {
		cout << "Congrats you win!" << endl;
		return false; //game over
	}

	//if no winner and board full, then it is a tie
	bool tie = true;
	for (int i = 0; i < BOARD_LENGTH*BOARD_LENGTH; i++){
		if (board[i] == 0) tie = false;
	}
	if (tie){
		cout << "tie game" << endl;
		return false;
	}

	//logic for CPU next move

	//if one move away from winning, win game 
	if (try_to_win(board)){
		cout << "Sorry, you lost" << endl;
		return false;
	}
	//if can't win try to prevent immediate win from opponent
	else if (eliminate_threat(board)){}
	//if no threat, CPU attempts to attack to setup win next move
	else if (attack(board)){}
	//random move, attempts to create possibilites for next attack by claiming most middle position
	else{
		claim_middle(board);
	}

	return true;
}

//simple backtrack logic
bool try_to_win(int b[]){
//	cout << "try to win start" << endl;
//	print_board(b); //for debugging

	for (int i = 0; i < BOARD_LENGTH*BOARD_LENGTH; i++){
		if (b[i] == 0){
			b[i] = 2;
			if (winner(b) != -1){
				return true;
			}
			b[i] = 0;
		}
	}
	return false; //no immediate way to win
}

//backtrack logic to see if opponent can win and nullify their move
bool eliminate_threat(int b[]){
//	cout << "eliminate threat start" << endl;
//	print_board(b); //for debugging
	for (int i = 0; i < BOARD_LENGTH*BOARD_LENGTH; i++){
		if (b[i] == 0){
			b[i] = 1;
			if (winner(b) != -1){
				b[i] = 2;
				return true; //successful defend
			}
			b[i] = 0;
		}
	}
	return false; // no immediate threats from opponent
}

//setup to try to win next move
bool attack(int b[]){
//	cout << "attack start" << endl;
//	print_board(b); //for debugging
	for (int i = 0; i < BOARD_LENGTH*BOARD_LENGTH; i++){
		if (b[i] == 0){
			b[i] = 2;
			if (try_to_win(b)) {
				b[i] = 0;
				return true;
			}
			b[i] = 0;
		}
	}
	return false;
}


//try to get middle
bool claim_middle(int b[]){
//	cout << "claim middle start" << endl;
//	print_board(b); //for debugging
	if (b[BOARD_LENGTH / 2 * BOARD_LENGTH + BOARD_LENGTH / 2] == 0){
		b[BOARD_LENGTH / 2 * BOARD_LENGTH + BOARD_LENGTH / 2] = 2;
	}
	else{
		for (int i = 0; i < BOARD_LENGTH*BOARD_LENGTH; i++){
			if (b[i] == 0){
				b[i] = 2;
				return true;
			}
		}
	}
	return true;
}


//currently this check only works for 3x3 scaling upwards become difficult as correct offsetting for diagonal checking becomes awkward
//main focus of this project is AI, need to rewrite winner check funtion in future to make it more dynamic
int winner(int matrix[]){
	//horizontal
	for (int r = 0; r < BOARD_LENGTH; r++){
		if (matrix[r * BOARD_LENGTH] == matrix[r*BOARD_LENGTH + 1] && matrix[r * BOARD_LENGTH] == matrix[r*BOARD_LENGTH + 2] && matrix[r*BOARD_LENGTH] != 0){
			return (matrix[r*BOARD_LENGTH] == 1) ? 1 : 2;
		}
	}
	//vertical
	for (int c = 0; c < BOARD_LENGTH; c++){
		if (matrix[c] == matrix[c + BOARD_LENGTH] && matrix[c] == matrix[c + BOARD_LENGTH + BOARD_LENGTH] && matrix[c] != 0){
			return (matrix[c] == 1) ? 1 : 2;
		}
	}
	//diagonal
	if (matrix[0] == matrix[4] && matrix[0] == matrix[8] && matrix[0] != 0){
		return (matrix[0] == 1) ? 1 : 2;
	}
	if (matrix[2] == matrix[4] && matrix[2] == matrix[6] && matrix[2] != 0){
		return (matrix[2] == 1) ? 1 : 2;
	}

	return -1;
}

void pretty_print(int board[]){
	for (int i = 0; i < BOARD_LENGTH; i++){
		for (int n = 0; n < BOARD_LENGTH; n++){
			cout << "|";
			if (board[BOARD_LENGTH * i + n] == 0){
				cout << " ";
			}
			else if (board[BOARD_LENGTH * i + n] == 1){
				cout << "X";
			}
			else if (board[BOARD_LENGTH * i + n] == 2){
				cout << "O";
			}
			else{
				cerr << "invalid piece" << endl;
			}
		}
		cout << "|" << endl;
		for (int m = 0; m < BOARD_LENGTH; m++){
			cout << "--";
		}
		cout << endl;
	}
	cout << endl;
}