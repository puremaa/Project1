#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <locale>
using namespace std;

class Game
{
    enum class Player
    {
        none = '-',
        human = 'X',
        computer = 'O'
    };

    struct Move
    {
        unsigned int x = 0;
        unsigned int y = 0;
    };

    Player board[3][3];

public:
    Game() 
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                board[i][j] = Player::none;
            }
        }
    }

    void printBoard()
    {
        std::cout << "+-----------------+";
        for (unsigned int i = 0; i < 3; i++)
        {
            std::cout << "\n|";
            for (unsigned int j = 0; j < 3; j++)
            {
                std::cout << std::setw(3) << static_cast<char>(board[i][j]) << std::setw(3) << " |";
            }
        }
        std::cout << "\n+-----------------+\n";
    }

    bool isTie()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }

    bool checkWin(Player player)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
              {  return true;
                 }

            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
               { return true;
                 }
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            {return true;
           }

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            {return true;
             }

        return false;
    }

    Move minimax() 
    {
        int score = std::numeric_limits<int>::max();
        Move move;

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;

                    int temp = maxSearch();

                    if (temp < score)
                    {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }

        return move;
    }

    int maxSearch() 
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = std::numeric_limits<int>::min();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::human;
                    score = std::max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    int minSearch()
    {
        if (checkWin(Player::human)) { return 10; }
        else if (checkWin(Player::computer)) { return -10; }
        else if (isTie()) { return 0; }

        int score = std::numeric_limits<int>::max();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::computer;
                    score = std::min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    void getHumanMove()
    {
        bool fail = true;
        unsigned int x = -1, y = -1;

        do
        {
            std::cout << "Your Move: ";

            char c;
            std::cin >> c;
            x = c - '0';
            std::cin >> c;
            y = c - '0';
 
            fail = board[x][y] != Player::none;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        } while (fail);

        board[x][y]=Player::human  ;
    }

   void play(int Lev)
    {
        unsigned int turn = 0;
        bool exit = false;

    printBoard();
        std::cout << "Enter your move in coordinate form[row, col]. ex: 02\n";

        do
        {
            // human move
            if (turn == 0)
            {
                getHumanMove();

                if (checkWin(Player::human))
                {
                    std::cout << "Human Wins\n";
                    exit = true;
            cout<<"if you want to play again press enter"<<endl;
                }
            }
            else
            {
                std::cout << "\nComputer Move: ";
           if ( Lev == 2){
                Move aimove = minimax();
                std::cout << aimove.x << aimove.y << "\n";
                board[aimove.x][aimove.y] = Player::computer;

                if (checkWin(Player::computer))
                {
                    std::cout << "Computer Wins\n";
                    exit = true;
            cout<<"if you want to play again press enter"<<endl;
                }
            }
         else{
             Move RANDOM;
             int randx , randy;
             srand(time(NULL));
             randx = (rand()%3) ;
             randy = (rand()%3) ;
             while (board[randx][randy] != Player::none ){
             srand(time(NULL));
             randx = (rand()%3) ;
             randy = (rand()%3) ;}
             RANDOM.x = randx;
             RANDOM.y = randy;
         Move aimove = RANDOM;
                  std::cout<<aimove.x<<aimove.y<<"\n";
                  board[aimove.x][aimove.y] = Player::computer;

         if (checkWin(Player::computer))
                {
                    std::cout << "Computer Wins\n";
                    exit = true;
            cout<<"if you want to play again press enter"<<endl;
                }
               }}

            if (isTie())
            {
                std::cout << "\n** DRAW **\n";
                exit = true;
            cout<<"if you want to play again press enter"<<endl;
            }

            turn ^= 1;
            printBoard();

        } while (!exit);
        return ;
    }

};

struct board
{
    bool square, circle, empty; //square refers to sign "X"   circle refers to sign "O"
    int pos;
    board* next; //pointer to the next node
};
void twoplayers();
void startGame(int first, board* fullBoard);
board* getBoard(board* fullBoard);
double enter_number(double x);
double enter_choice(double y);
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
int main()
{
     int start = clock();
     
    bool Quit = false;
double Answer;

while(!Quit) {
       
    int level;
    double num_of_players;
    cout<< "( SELECT THE NUMBER OF PLAYES ) "<<endl <<endl<<"1- multiple players"<<endl<<"2- single player"<<endl;
     num_of_players =enter_number(num_of_players);

    if ( num_of_players ==1 )
    {
        twoplayers();
    
    }
    else{
        cout<<endl<<"1-medium "<<endl<<"2-hard"<<endl;
       level=enter_number(level);
        
    
    Game tictactoe;
    tictactoe.play(level);
    cin.ignore();
}
 int end = clock();
    // Calculating total time taken by the program.

        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed << time_taken;
    cout << " sec " << endl;

        
     cout << "Would you like to play again? Yes=1 / No=2" << endl;
    Answer=enter_number(Answer);

  
    if (Answer == 2) {
         Quit = true;
    }
} 
}
