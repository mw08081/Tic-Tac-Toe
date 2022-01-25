#include <iostream>
#include <iomanip>

using namespace std;

class Person
{
private :
	string name;
	int sc;

public :
	Person()
	{
		this->name = "noCont";
		this->sc = 0;
	}
	Person(string _name)
	{
		this->name = _name;
		this->sc = 0;
	}

	//set
	void setName(string _name)
	{
		this->name = _name;
	}
	void setSc(int _sc)
	{
		this->sc = _sc;
	}

	//get
	string getName()
	{
		return this->name;
	}
	int getSc()
	{
		return this->sc;
	}

	pair<int, int> MarkLoacation()
	{
		int x, y;
		cin >> x >> y;

		//잘못된 좌표값을 입력한 경우
		while (!(x >= 1 && x <= 3 && y >= 1 && y <= 3))
			cin >> x >> y;

		return pair<int, int>(x, y);
	}
};

class Game
{
private :
	char (* board)[3];
	int cnt;
	bool isP1;
	Person* players;

public :
	Game(Person * _players)
	{
		board = new char[3][3]{ {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} }; // { {'O', 'O', 'O'}, { 'O', 'O', 'O' }, { 'O', 'O', 'O' } };
		isP1 = true;
		cnt = 0;
		players = new Person[2]();

		for (int i = 0; i < 2; i++)
		{
			players[i].setName((_players + i)->getName());
			players[i].setSc((_players + i)->getSc());
		}
	}

	void PlayGame()
	{
		int res = -1;
		char continueGame = 'Y';
		
		while (continueGame == 'Y')
		{
			PrintGameInfo();
			PrintBoard();

			while (res == -1)
			{
				MarkBoard();

				PrintBoard();
				isP1 = isP1 ? false : true;

				res = CheckBoard();
			}
			players[res].setSc(players[res].getSc() + 1);

			PrintRes(res);
			cout << '\n' << "Do you want to play one more? (Y/N) : ";
			cin >> continueGame;

			ClearBoard();
			res = -1;
		}
	}

public :

	void PrintGameInfo()
	{
		cout << "Number of games : " << cnt << '\n';
		cout << "Player 1 Name = " << players[0].getName() << '\n';
		cout << "Player 2 Name = " << players[1].getName() << '\n';
		cout << "     Tic Tac Toe" << '\n';
		cout << "  " << players[0].getName() << "(X) - " << players[1].getName() << "(O)" << '\n' << '\n';
	}

	void PrintBoard()
	{
		cout << "     1     2      3" << '\n';
		cout << "        |      |  " << '\n';
		cout << "1   " << this->board[0][0] << "   |  " << this->board[0][1] << "   |  " << this->board[0][2] << '\n';
		cout << "   _____|______|_____  " << '\n';
		cout << "        |      |  " << '\n';
		cout << "2   " << this->board[1][0] << "   |  " << this->board[1][1] << "   |  " << this->board[1][2] << '\n';
		cout << "   _____|______|_____  " << '\n';
		cout << "        |      |  " << '\n';
		cout << "3   " << this->board[2][0] << "   |  " << this->board[2][1] << "   |  " << this->board[2][2] << '\n';
		cout << "        |      |      " << '\n';
	}

	void MarkBoard()
	{
		cout << players[isP1 ? 0 : 1].getName() << " " << (isP1 ? "(X)" : "(O)") << " Mark Location:  ";
		pair<int, int> tmp = players[isP1 ? 0 : 1].MarkLoacation();
		
		//이미 marked된 곳에 mark할 경우
		while (board[tmp.first - 1][tmp.second - 1] != ' ') {
			cout << players[isP1 ? 0 : 1].getName() << " " << (isP1 ? "(X)" : "(O)") << " Mark Location:  ";
			tmp = players[isP1 ? 0 : 1].MarkLoacation();
		}
		
		int x = tmp.first - 1, y = tmp.second - 1;

		if (isP1)
			board[x][y] = 'X';
		else
			board[x][y] = 'O';
	}

	//return none -> -1, p1 -> 0, p2 -> 1;
	int CheckBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			//가로줄 확인
			if (this->board[i][0] != ' ' && this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2])
			{
				if (this->board[i][0] == 'X')
					return 0;
				else
					return 1;
			}
			//세로줄 확인
			else if(this->board[0][i] != ' ' && this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i])
			{
				if (this->board[0][i] == 'X')
					return 0;
				else
					return 1;
			}
		}
		if (this->board[1][1] != ' ' && (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] || this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]))
		{
			if (this->board[1][1] == 'X')
				return 0;
			else
				return 1;
		}

		return -1;
	}

	void PrintRes(int res)
	{
		cout << players[res].getName() << " wins this round" << '\n';
		cout << std::setw(5) << std::right << players[0].getName() << " : " << players[0].getSc() << '\n';
		cout << std::setw(5) << std::right << players[1].getName() << " : " << players[1].getSc() << '\n';
		cout << "Congratulation " << players[res].getName() << ". You won!" << '\n';
	}

	void ClearBoard()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->board[i][j] = ' ';

		//this->isP1 = true;
		cnt++;
	}
};


int main()
{
	Person* players = new Person[2]{ {"Karl"}, {"Sofia"} };
	Game game(players);

	game.PlayGame();

	return 0;
}