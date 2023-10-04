#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

// A function to show the current board status
void showBoard(char board[][SIDE])
{
    for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            if(j==SIDE-1) cout<<board[i][j];
            else cout<<board[i][j]<<" |";
        }
        cout<<endl;
        if(i<SIDE-1)
        {
            for(int i=0; i<SIDE*5; i++) cout<<"-";
        }
        cout<<endl;
    }
}

// A function to show the instructions
void showInstructions()
{
	cout<<"\nChoose a cell numbered from 1 to "<<SIDE*SIDE<<" as below and play"<<endl;

	int con = 0;
	for(int i=0; i<SIDE; i++)
    {
        for(int j=0; j<SIDE; j++)
        {
            con++;
            if(j==SIDE-1) cout<<con;
            else cout<<con<<"   |";
        }
        cout<<endl;
        if(i<SIDE-1)
        {
            for(int i=0; i<SIDE*5; i++) cout<<"-";
        }
        cout<<endl;
    }
}



bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') return (true);
	}
	return(false);
}

bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') return (true);
	}
	return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
	if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') || (board[0][2] == board[1][1] && board[1][1] == board[2][0] &&board[0][2] != ' ')) return(true);
	return(false);
}


bool gameOver(char board[SIDE][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

///MINIMAX ALGORITHM
int minimax(char board[SIDE][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
	{
		if (isAI == true) return -1;
		if (isAI == false)return +1;
	}
	else
	{
		if(depth < SIDE*SIDE)
		{
			if(isAI == true) //true mani human er move, ekhane bestscore maximum korte hobe
			{
				bestScore = -1e5;
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
							bestScore = max(bestScore, score);

						}
					}
				}
				return bestScore;
			}
			else  //false mani human er move, ekhane bestscore maximum korte hobe
			{
				bestScore = 1e5;
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
							bestScore = min(bestScore,score);
						}
					}
				}
				return bestScore;
			}
		}
		else return 0;

	}
}

int bestMove(char board[SIDE][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
			}
		}
	}
	return x*SIDE+y;
}


// A function to play Tic-Tac-Toe
void playTicTacToe(int my_turn)
{
	char board[SIDE][SIDE] ;
	int moveIndex = 0, x = 0, y = 0;

	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++) board[i][j] = ' ';
	}
	showInstructions();

	// Keep playing till the game is over or it is a draw
	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
		int n;
		if (my_turn == COMPUTER)
		{
			n = bestMove(board, moveIndex); ///computer best move decide kortase (0,1,2..n)
			x = n / SIDE; //koto number row te ase
			y = n % SIDE; // koto number column e ase
			board[x][y] = COMPUTERMOVE; // oi row column fill up kortasi
			cout<<"COMPUTER has put a "<<COMPUTERMOVE<<" in cell "<<n+1<<endl;
			showBoard(board);
			moveIndex ++;
			my_turn = HUMAN;
		}

		else if (my_turn == HUMAN)
		{
			cout<<"You can insert in the following positions : "<<endl;
			for(int i=0; i<SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == ' ') cout<<(i*SIDE + j) + 1<<" ";
                }
            }
            cout<<endl;
			cout<<"Enter the position = "<<endl;
			cin>>n; ///Human best move decide kortase (0,1,2..n)
			n--;
			x = n/SIDE;
			y = n%SIDE;
			if(board[x][y] == ' ' && n<9 && n>=0)
			{
				board[x][y] = HUMANMOVE;
				printf ("\nHUMAN has put a %c in cell %d\n\n", HUMANMOVE, n+1);
				showBoard(board);
				moveIndex ++;
				my_turn = COMPUTER;
			}
			else if(board[x][y] != ' ' && n<9 && n>=0) cout<<"Position is occupied, select any one place from the available places"<<endl;
			else if(n<0 || n>8) cout<<"Invalid position100"<<endl;
		}
	}

	// If the game has drawn
	if (gameOver(board) == false && moveIndex == SIDE * SIDE) cout<<"It's a draw"<<endl;
	else
	{
		// Toggling the user to declare the actual winner
		if (my_turn == COMPUTER) my_turn = HUMAN; //Karon last move deyar por human computer re pass kore disilo
		else if (my_turn == HUMAN) my_turn = COMPUTER; //Karon last move deyar por computer human re pass kore disilo


		if (my_turn == COMPUTER) cout<<"COMPUTER has won"<<endl;
		else cout<<"Human has won"<<endl;
	}
}

int main()
{
	printf("\n-------------------------------------------------------------------\n\n");
	printf("\t\t\t Tic-Tac-Toe\n");
	printf("\n-------------------------------------------------------------------\n\n");
	char ind ='n';
	while(ind=='n')
    {
        char choice;
//        cout<<"Do you want to play on default board?(y/n) : "<<endl;
//        cin>>choice;
//        if(choice=='n') SIDE = 3;
//        else
//        {
//            cout<<"Input the board size(nxn) : "<<endl;
//            cin>>SIDE;
//        }
	 	cout<<"Do you want to start first?(y/n) : "<<endl;
	 	cin>>choice;

		if(choice=='n') playTicTacToe(COMPUTER);
		else if(choice=='y') playTicTacToe(HUMAN);
		else cout<<"Invalid choice"<<endl;

		cout<<"\nDo you want to quit(y/n) : "<<endl;
       	cin>>ind;
    }

}
