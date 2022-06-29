// ChessGame2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<cctype>
#include "consola.h"


using namespace std;
// Hecho por Alex Bujosa 1098913 -> Día: 11-16-2021
int k = 0, Vcount = 0;
struct Game {
	char table[8][8];
	int turno = 1;
	bool pawnWhite[8] = { true, true, true, true, true, true, true, true };
	bool pawnBlack[8] = { true, true, true, true, true, true, true, true };
	bool castlingWhite = true;
	bool castlingBlack = true;
	char pieces[2][6] = { {'P','H','B','R','Q','K'},{'p','h','b','r','q','k' } };

};
char asignSymbol(Game* game, int row, int column) {
	char x = (2 * int(column / 2) + row % 2) == column ? '*' : '#';
	return x;
}
void fillTable(Game* game) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == 0) {
				if (j == 0 || j == 7) {
					game->table[i][j] = 'R';
				}
				else if (j == 1 || j == 6) {
					game->table[i][j] = 'H';
				}
				else if (j == 2 || j == 5) {
					game->table[i][j] = 'B';
				}
				else if (j == 3) {
					game->table[i][j] = 'K';
				}
				else if (j == 4) {
					game->table[i][j] = 'Q';
				}
			}
			else if (i == 1) {
				game->table[i][j] = 'P';
			}
			else if (i == 6) {
				game->table[i][j] = 'p';
			}
			else if (i == 7) {
				if (j == 0 || j == 7) {
					game->table[i][j] = 'r';
				}
				else if (j == 1 || j == 6) {
					game->table[i][j] = 'h';
				}
				else if (j == 2 || j == 5) {
					game->table[i][j] = 'b';
				}
				else if (j == 3) {
					game->table[i][j] = 'k';
				}
				else if (j == 4) {
					game->table[i][j] = 'q';
				}
			}
			else {
				game->table[i][j] = asignSymbol(game, i, j);
			}
		}
	}
}
void renderTable(Game* game) {
	int row = 8;
	int column = 8;
	char columnName[8] = { 'A', 'B', 'C','D','E','F','G','H' };
	cout << endl;
	for (int i = 0; i < 9; i++) {
		if (i < 8) {
			PositionXY(3, i +Vcount+ (k*14));
			cout << ConvertToString(8 - i) + "|";
			for (int j = 0; j < 8; j++) {
				PositionXY(j * 2 + 5, i + Vcount+ (k * 14));
				cout << game->table[7 - i][7 - j];
			}
			cout << endl;
		}
		else {
			for (int j = 0; j < 8; j++) {
				PositionXY(j * 2 + 5, i+Vcount + (k * 14));
				cout << "~~";
				PositionXY(j * 2 + 5, i + Vcount + 1 + (k * 14));
				cout << columnName[j];

			}
		}

	}
	k++;
}
int* convertPositioninXY(string positionPiece, string positionToMove) {
	static int arr[4];
	int i = 0;
	string position = positionPiece + positionToMove;
	if (position.length() != 4) {
		arr[0] = -1;
		return arr;
	}
	while (i < 4){
		switch (position[i]) {
			case 'A': 
				arr[i] = 7;
				break;
			case 'B': 
				arr[i] = 6;
				break;
			case 'C':
				arr[i] = 5;
				break;
			case 'D': 
				arr[i] = 4;
				break;
			case 'E':
				arr[i] = 3;
				break;
			case 'F':
				arr[i] = 2;
				break;
			case 'G':
				arr[i] = 1;
				break;
			case 'H':
				arr[i] = 0;
				break;
			case '1':
				arr[i] = 0;
				break;
			case '2':
				arr[i] = 1;
				break;
			case '3':
				arr[i] = 2;
				break;
			case '4':
				arr[i] = 3;
				break;
			case '5':
				arr[i] = 4;
				break;
			case '6':
				arr[i] = 5;
				break;
			case '7':
				arr[i] = 6;
				break;
			case '8':
				arr[i] = 7;
				break;
			default:
				arr[0] = -1;
		}
		i++;
	}
	return arr;
}
string* splitMessagebyspace(string message) {
	static string arr[3];
	for (int i = 0; i < 3; i++) {
		arr[i] = message.substr(0, message.find(" "));
		message.erase(0, message.substr(0, message.find(" ")).length() + 1);
	}
	return arr;
}
int* Move() {
	string userRequest;
	getline(cin, userRequest);

	userRequest = ConvertToupper(userRequest);
	string* token;
	token = splitMessagebyspace(userRequest);
	int* move;
	move = (token[2] != "") ? convertPositioninXY(token[1], token[2]) : NULL;
	return move;
}
class Piece {
protected:
	int columnPiece, rowPiece, columnToMove, rowToMove;
	Game* gamecl;
	public:

		Piece(int* position, Game* game) {
			columnPiece = position[0];
			rowPiece = position[1];
			columnToMove = position[2];
			rowToMove = position[3];
			gamecl = game;
		}
		bool validateMov() {
			gamecl->table[rowToMove][columnToMove] = gamecl->table[rowPiece][columnPiece];
			gamecl->table[rowPiece][columnPiece] = asignSymbol(gamecl, rowPiece, columnPiece);
			return true;
		}


};
class Pawn : public Piece {

public:
	Pawn(int* position, Game* game) : Piece(position, game) {

	}
	void convertPawn() {
		if (gamecl->turno == 1 && rowToMove == 7) {
			char deseo = 'F';
			while (deseo != 'Q' && deseo != 'R' && deseo != 'B' && deseo != 'H') {
				try {
					cout << "\nEn que deseas convertir su peon? (Q -> Queen, R -> Rook, B->Bishop, H->Knight) ";
					cin >> deseo;
					deseo = ConvertToupper(deseo);
					gamecl->table[rowToMove][columnToMove] = deseo;
					cout << "\n";
				}
				catch (exception ex) {
					cout << "Valor incorrecto";
					system("pause");
				}
				Vcount += 3;

			}
		}
		else if (gamecl->turno == 0 && rowToMove == 0) {
			char deseo = 'F';
			while (deseo != 'q' && deseo != 'r' && deseo != 'b' && deseo != 'h') {
				try {
					cout << "\nEn que deseas convertir su peon? (Q -> Queen, R -> Rook, B->Bishop, H->Knight) ";
					cin >> deseo;
					deseo = ConvertTolower(deseo);
					gamecl->table[rowToMove][columnToMove] = deseo;
					cout << "\n";
				}
				catch (exception ex) {
					cout << "Valor incorrecto";
					Vcount += 1;
					system("pause");
				}
				Vcount += 3;
			}
		}
	}
	bool move() {
		int column = ABS(columnToMove - columnPiece);
		int row = ABS(rowToMove - rowPiece);
		if (gamecl->turno == 1 && rowToMove > rowPiece) {
			if (column == 1 && (rowToMove - rowPiece) == 1 && islower(gamecl->table[rowToMove][columnToMove])) {
				return validateMov();
			}
			else if (column == 0 && (rowToMove - rowPiece) == 1 && (gamecl->table[rowToMove][columnToMove] == '*' || gamecl->table[rowToMove][columnToMove] == '#')) {
				return validateMov();
			}
			else if (column == 0 && (rowToMove - rowPiece) == 2 && (gamecl->table[rowToMove][columnToMove] == '*' || gamecl->table[rowToMove][columnToMove] == '#') && gamecl->pawnWhite[columnPiece] == true && rowPiece == 1) {
				return validateMov();
			}
		}
		else if (gamecl->turno == 0 && rowToMove < rowPiece) {
			if (column == 1 && row == 1 && isupper(gamecl->table[rowToMove][columnToMove])) {
				return validateMov();
			}
			else if (column == 0 && row == 1 && (gamecl->table[rowToMove][columnToMove] == '*' || gamecl->table[rowToMove][columnToMove] == '#')) {
				return validateMov();
			}
			else if (column == 0 && row == 2 && (gamecl->table[rowToMove][columnToMove] == '*' || gamecl->table[rowToMove][columnToMove] == '#') && gamecl->pawnBlack[columnPiece] == true && rowPiece == 6) {
				return validateMov();
			}
		}
		return false;
	}

};
class Knight : public Piece {
	public:
		Knight(int* position, Game* game) : Piece(position, game) {

		};
		bool move() {
			int column = ABS(columnToMove - columnPiece);
			int row = ABS(rowToMove - rowPiece);
			if (gamecl->turno == 1 && ((column == 1 && row == 2)||(column == 2 && row == 1))) {
				return validateMov();
			}
			else if (gamecl->turno == 0 && ((column == 1 && row == 2) || (column == 2 && row == 1))) {
				return validateMov();
			}
			return false;
		}
};
class Bishop : public Piece {
	public:
		Bishop(int* position, Game* game) : Piece(position, game) {

		};
		bool movBishop() {
			if (columnToMove > columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i && rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece + i] != '#' && gamecl->table[rowPiece + i][columnPiece + i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove > columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i && rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece + i] != '#' && gamecl->table[rowPiece - i][columnPiece + i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove < columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i && rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece - i] != '#' && gamecl->table[rowPiece + i][columnPiece - i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove < columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i && rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece - i] != '#' && gamecl->table[rowPiece - i][columnPiece - i] != '*') {
						break;
					}
				}
			}
			return false;
		}
		bool move() {
			if (gamecl->turno == 1) {
				return movBishop();
			}
			else {
				return movBishop();
			}
			return false;
		}
};
class King : public Piece {
	public:
		King(int* position, Game* game) : Piece(position, game) {

		};
		bool checkboxes() {
			int R = gamecl->turno;
			int k[2] = { -1, 1 };
			// Verificar si a donde el rey se quiere mover hay un peon atacando
			if ( gamecl->table[rowToMove + k[R]][columnToMove + 1] == gamecl->pieces[R][0] || gamecl->table[rowToMove + k[R]][columnToMove - 1] == gamecl->pieces[R][0]) {
				return false;
			}
			// Verificar si a donde el rey se quiere mover hay un caballo atacando
			if (((rowToMove + 2 > -1 && rowToMove + 2 < 8 && columnToMove + 1 > -1 && columnToMove + 1 < 8)&&(gamecl->table[rowToMove + 2][columnToMove + 1] == gamecl->pieces[R][1])) || ((rowToMove + 2 > -1 && rowToMove + 2 < 8 && columnToMove - 1 > -1 && columnToMove - 1 < 8) && gamecl->table[rowToMove + 2][columnToMove - 1] == gamecl->pieces[R][1]) || ((rowToMove - 2 > -1 && rowToMove - 2 < 8 && columnToMove + 1 > -1 && columnToMove + 1 < 8) && gamecl->table[rowToMove - 2][columnToMove + 1] ==  gamecl->pieces[R][1]) || ((rowToMove - 2 > -1 && rowToMove - 2 < 8 && columnToMove - 1 > -1 && columnToMove - 1 < 8) && gamecl->table[rowToMove - 2][columnToMove - 1] == gamecl->pieces[R][1]) || ((rowToMove + 1 > -1 && rowToMove + 1 < 8 && columnToMove + 2 > -1 && columnToMove + 2 < 8) && gamecl->table[rowToMove + 1][columnToMove + 2] == gamecl->pieces[R][1]) || ((rowToMove + 1 > -1 && rowToMove + 1 < 8 && columnToMove - 2 > -1 && columnToMove - 2 < 8) && gamecl->table[rowToMove + 1][columnToMove - 2] == gamecl->pieces[R][1]) || ((rowToMove - 1 > -1 && rowToMove - 1 < 8 && columnToMove + 2 > -1 && columnToMove + 2 < 8) && gamecl->table[rowToMove - 1][columnToMove + 2] == gamecl->pieces[R][1]) || ((rowToMove - 1 > -1 && rowToMove - 1 < 8 && columnToMove - 2 > -1 && columnToMove - 2 < 8) && gamecl->table[rowToMove - 1][columnToMove - 2] == gamecl->pieces[R][1])) {
				return false;
			}
			return true;
		}
		bool move() {
			int row = ABS(rowToMove - rowPiece);
			int column = ABS(columnToMove - columnPiece);
			if (row == 1 && column == 1) {
				return (checkboxes()== true) ? validateMov() : false;
			}
			else if (row == 1 && column == 0) {
				return (checkboxes() == true) ? validateMov() : false;
			}
			else if (column == 1 && row == 0) {
				return (checkboxes() == true) ? validateMov() : false;
			}
			return false;
		}
};
class Rook : public Piece {
	public:
		Rook(int* position, Game* game) : Piece(position, game) {

		};
		bool moveRook() {
			if (columnToMove == columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (rowToMove - rowPiece); i++) {
					if (rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece] != '#' && gamecl->table[rowPiece + i][columnPiece] != '*') {
						break;
					}
				}
			}
			else if (columnToMove == columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (rowPiece - rowToMove ); i++) {
					if (rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece] != '#' && gamecl->table[rowPiece - i][columnPiece] != '*') {
						break;
					}
				}
			}
			else if (rowToMove == rowPiece && columnToMove > columnPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece][columnPiece + 1] != '#' && gamecl->table[rowPiece][columnPiece + 1] != '*') {
						break;
					}
				}
			}
			else if (rowToMove == rowPiece && columnToMove < columnPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece][columnPiece - 1] != '#' && gamecl->table[rowPiece][columnPiece - 1] != '*') {
						break;
					}
				}
			}
			return false;
		}
		bool move() {
			if (gamecl->turno == 1) {
				return moveRook();
			}
			else {
				return moveRook();
			}
			return false;
		}
};
class Queen : public Piece{
	public:
		Queen(int* position, Game* game) : Piece(position, game) {

		};
		bool movDiagonal() {
			if (columnToMove > columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i && rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece + i] != '#' && gamecl->table[rowPiece + i][columnPiece + i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove > columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i && rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece + i] != '#' && gamecl->table[rowPiece - i][columnPiece + i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove < columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i && rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece - i] != '#' && gamecl->table[rowPiece + i][columnPiece - i] != '*') {
						break;
					}
				}
			}
			else if (columnToMove < columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i && rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece - i] != '#' && gamecl->table[rowPiece - i][columnPiece - i] != '*') {
						break;
					}
				}
			}
			return false;
		}
		bool movehv() {
			if (columnToMove == columnPiece && rowToMove > rowPiece) {
				for (int i = 1; i <= (rowToMove - rowPiece); i++) {
					if (rowToMove == rowPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece + i][columnPiece] != '#' && gamecl->table[rowPiece + i][columnPiece] != '*') {
						break;
					}
				}
			}
			else if (columnToMove == columnPiece && rowToMove < rowPiece) {
				for (int i = 1; i <= (rowPiece - rowToMove); i++) {
					if (rowToMove == rowPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece - i][columnPiece] != '#' && gamecl->table[rowPiece - i][columnPiece] != '*') {
						break;
					}
				}
			}
			else if (rowToMove == rowPiece && columnToMove > columnPiece) {
				for (int i = 1; i <= (columnToMove - columnPiece); i++) {
					if (columnToMove == columnPiece + i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece][columnPiece + 1] != '#' && gamecl->table[rowPiece][columnPiece + 1] != '*') {
						break;
					}
				}
			}
			else if (rowToMove == rowPiece && columnToMove < columnPiece) {
				for (int i = 1; i <= (columnPiece - columnToMove); i++) {
					if (columnToMove == columnPiece - i) {
						return validateMov();
					}
					else if (gamecl->table[rowPiece][columnPiece - 1] != '#' && gamecl->table[rowPiece][columnPiece - 1] != '*') {
						break;
					}
				}
			}
			return false;
		}
		bool move() {
			if (gamecl->turno == 1) {
				return (movDiagonal() || movehv());
			}
			else {
				return (movDiagonal() || movehv());
			}
			return false;
		}
};
bool movePiece(char piece, int* position, Game* game) {
	piece = ConvertToupper(piece);
	bool value;
	switch (piece) {
		case 'P':
		{
			Pawn pawn = Pawn(position, game);
			value = pawn.move();
			pawn.convertPawn();
		}
		break;
		case 'R':
		{
			Rook rook = Rook(position, game);
			value = rook.move();
		}
		break;
		case 'H':
		{
			Knight knight = Knight(position, game);
			value = knight.move();
		}
		break;
		case 'B':
		{
			Bishop bishop = Bishop(position, game);
			value = bishop.move();
		}
		break;
		case 'Q':
		{
			Queen queen = Queen(position, game);
			value = queen.move();
		}
		break;
		case 'K':
		{
			King king = King(position, game);
			value = king.move();
		}
		break;
		default:
		{
			throw std::invalid_argument("oh oh Something is wrong");
		}
		break;
	}
	return value;
}
int main()
{
	Game* game = new Game();
	fillTable(game);
	renderTable(game);
	bool value;
	while (true) {
		if (game->turno == 1) {
			while (true) {
				cout << "\nIt's turn to white to move" << endl;
				int* move;
				move = Move(); 
				if (move != NULL && move[0] != -1 && UpperCase(game->table[move[1]][move[0]]) && !UpperCase(game->table[move[3]][move[2]]) && game->table[move[1]][move[0]] != ('#' && '*') ) {
					value = movePiece(game->table[move[1]][move[0]], move, game);
					game->turno = value ? game->turno -= 1 : game->turno;
					break;
				}
				Vcount += 3;
			}

		}
		else {
			while (true) {
				cout << "\nIt's turn to black to move"<<endl;
				int* move;
				move = Move();
				if (move != NULL && move[0] != -1 && LowerCase(game->table[move[1]][move[0]]) && !LowerCase(game->table[move[3]][move[2]]) && game->table[move[1]][move[0]] != ('#' || '*')) {
					value = movePiece(game->table[move[1]][move[0]], move, game);
					game->turno = value ? game->turno += 1 : game->turno;
					break;
				}
				Vcount += 3;
			}
		}
		renderTable(game);
	}
	cout << "\n";
}