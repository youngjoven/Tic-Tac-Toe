//Version 1. Human plays against another human
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void splashScreen(); //displays game and developer's information
void askForUserNames(string &player1, string &player2); //requests for username
void ValidateUserName(string &Username);//validate username
string switchPlayer(string &player1, string &player2, char &OX, string &recentPlayer);//switch from one player to another
																					  //reset the game when one concludes; this includes filling the array with values 0-8
void resetGame(char grid[], bool gridavailable[], string &recentPlayer, char &OX, string &player1);
void displayGrid(char grid[9]); //display the grid after each player makes a move
void playerMakeMove(string &Username, char &OX); //prompts player to make a move
void validatePlayersMove(string &move, int &Int_Move);//validates that user entry X is such that 0<=X<=8
													  //check that the position selected by the user is available
void checkPositionAvailability(char grid[], int &PlayerMove, bool gridavailable[], char OX, char array[], string UserMove);
void checkWin(char grid[], string &recentPlayer, int &counter);//check for a winning player
void checkTie(int counter); //check for a tie
void updategrid(char grid[9]); // this shows conclusion of winner

int main()
{
	string player1;
	string player2;
	string UserMove;
	string recentPlayer;
	string regame;
	char grid[9] = { '0','1','2','3','4','5','6','7','8' };
	char OX = 'X';
	bool gridavailable[9];
	int PlayerMove;
	int counter = 0;

	//initiate
	splashScreen();
	system("pause");
	system("cls");
	askForUserNames(player1, player2);
	system("cls");
	do
	{
		counter = 0;
		resetGame(grid, gridavailable, recentPlayer, OX, player1);
		while (counter < 9)
		{
			system("cls");
			displayGrid(grid);
			playerMakeMove(recentPlayer, OX);
			getline(cin, UserMove);
			validatePlayersMove(UserMove, PlayerMove);
			checkPositionAvailability(grid, PlayerMove, gridavailable, OX, grid, UserMove);
			updategrid(grid);
			checkWin(grid, recentPlayer, counter);
			checkTie(counter);
			recentPlayer = switchPlayer(player1, player2, OX, recentPlayer);
			counter++;
		}
		cout << "game over!, play again? y/n" << endl;
		getline(cin, regame);
		while (regame != "Y" && regame != "y" && regame != "N" && regame != "n")
		{
			cout << "Invalid option" << endl;
			getline(cin, regame);
		}
		system("cls");
	} while (regame == "Y" || regame == "y");
	return 0;
}

void splashScreen()
{
	cout << "*************************" << endl;
	cout << "*************************" << endl;
	cout << "*************************" << endl;
	cout << "****** TIC TAC TOE ******" << endl;
	cout << "******      BY     ******" << endl;
	cout << "****** Young Joong ******" << endl;
	cout << "******    Gwon     ******" << endl;
	cout << "******             ******" << endl;
	cout << "*************************" << endl;
	cout << "*************************" << endl;
	cout << "*************************" << endl;
}

void askForUserNames(string &player1, string &player2)
{
	//request for username
	cout << "Player 1, enter your name" << endl;
	cout << "enter a single word with alpha chars only!" << endl;
	getline(cin, player1);
	ValidateUserName(player1);
	cout << "Player 2, enter your name" << endl;
	cout << "enter a single word with alpha chars only!" << endl;
	getline(cin, player2);
	ValidateUserName(player2);
}
void ValidateUserName(string &Username)
{
	//validate username.
	int strLength;
	int counter = 0;
	strLength = Username.length();

	while (counter < strLength || strLength == 0)
	{
		if (!isalpha(Username[counter]))
		{
			cout << "Invalid Name" << endl;
			getline(cin, Username);
			strLength = Username.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
}
string switchPlayer(string &player1, string &player2, char &OX, string &recentPlayer)
{
	//switch from player to another player in the game
	if (recentPlayer == player1)
	{
		recentPlayer = player2;
	}

	else if (recentPlayer == player2)
	{
		recentPlayer = player1;

	}
	//switch from symbol to another symbol in the game
	if (OX == 'X')
	{
		OX = 'O';

	}

	else if (OX == 'O')
	{
		OX = 'X';
	}
	return recentPlayer;
}
void resetGame(char grid[], bool gridavailable[], string &recentPlayer, char &OX, string &player1)
{
	//reset the game when one concludes; this includes filling the array with values 0-8
	recentPlayer = player1;
	OX = 'X';
	for (int index = 0; index <9; index++)
	{
		gridavailable[index] = false;

		grid[index] = 48 + index;

	}
}

void displayGrid(char grid[9])
{
	//display Grid
	cout << right;
	cout << setw(19) << "Tic Tac Toe" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[0] << "|" << grid[1] << "|" << grid[2] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[3] << "|" << grid[4] << "|" << grid[5] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[6] << "|" << grid[7] << "|" << grid[8] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
}

void playerMakeMove(string &Username, char &OX)
{
	// this function shows who has "turn" now
	cout << "it is the " << Username << "'s turn; You are '" << OX << "'" << endl;
	cout << "Give me your best move!" << endl;

}
void validatePlayersMove(string &move, int &Int_Move)
{
	//validates that user entry X is such that 0<=X<=8
	//validates that user entry X is such that @#%@#$@#$ or SADFSD@#RF232 or spacing, etc
	int strLength = move.length();
	int counter = 0;
	while (counter < strLength || strLength == 0)
	{
		if (!isdigit(move[counter]))
		{
			cout << "Invalid entry." << endl;
			getline(cin, move);
			strLength = move.length();
			counter = 0;
		}

		else if (move != "0" &&  move != "1" && move != "2" && move != "3"  && move != "4" && move != "5" && move != "6" && move != "7"  && move != "8")
		{
			cout << "Invalid entry." << endl;
			getline(cin, move);
			strLength = move.length();
			counter = 0;
		}
		else
		{
			counter++;
		}
	}
	Int_Move = stoi(move);
}

void checkPositionAvailability(char grid[], int &PlayerMove, bool gridavailable[], char OX, char array[], string UserMove)
//If I choose the same number in the game, checkpositionAvailability comes out, and try again
{

	while (grid[PlayerMove] == 'X' || grid[PlayerMove] == 'O')
	{
		cout << "Position not available" << endl;
		cout << "make a different choice" << endl;
		getline(cin, UserMove);
		validatePlayersMove(UserMove, PlayerMove);

	}
	array[PlayerMove] = OX;
}
void checkWin(char grid[], string &recentPlayer, int &counter)
//In order to win, I have to make vertical, oblique,and horizontal possiblity for tic tac toe
{
	if ((grid[0] == grid[1] && grid[1] == grid[2]) || (grid[3] == grid[4] && grid[4] == grid[5]) || (grid[6] == grid[7] && grid[7] == grid[8])

		|| (grid[0] == grid[3] && grid[3] == grid[6]) || (grid[1] == grid[4] && grid[4] == grid[7]) || (grid[2] == grid[5] && grid[5] == grid[8])

		|| (grid[0] == grid[4] && grid[4] == grid[8]) || (grid[2] == grid[4] && grid[4] == grid[6]))
	{
		cout << recentPlayer << " won!" << endl;
		counter = 9;
	}

}

void checkTie(int counter) //Draw Situation
{
	if (counter == 8)
	{
		cout << "It's a tie" << endl;
	}

}

void updategrid(char grid[9]) // The grid shows who won this game
{
	system("cls");
	cout << right;
	cout << setw(19) << "Tic Tac Toe" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[0] << "|" << grid[1] << "|" << grid[2] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[3] << "|" << grid[4] << "|" << grid[5] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
	cout << setw(11) << "|" << grid[6] << "|" << grid[7] << "|" << grid[8] << "|" << endl;
	cout << setw(17) << "|_____|" << endl;
}