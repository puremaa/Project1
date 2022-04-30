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
void startGame(int first, board* fullBoard)
{
    int choice;
    bool isPlaying;
    board *arr[9];
    //loop to make our linked list containing 9 nodes
    for(int i = 1; i <= 9; i++)
    {
        fullBoard = getBoard(fullBoard);
        arr[i-1]=fullBoard;
    }
// starting the game
    bool isGameOn = true;
    board* head = fullBoard;
    while(isGameOn == true)
    {
        board* current = fullBoard;
        while(current != NULL)
        {
            //after each play we print the board and put the number of each box if empty or a sign of the box if not empty.
            if(current->empty == true)
                cout << "   " << current->pos;
            else if(current->circle == true)
                cout << "   " << "O";
            else
                cout << "   " << "X";
            if( current->pos == 4 || current->pos == 7)
            {
                cout << "\n";
                cout << "-----------------------\n";
            }
            else if (current->pos == 1)
                cout << "\n";
            else
                cout << "   |";
            current = current->next;
        }


// the turn of player 1
        if(first == 1)
        {
            isPlaying = true;
            while(isPlaying == true)
            {
                cout << "Player 1, please put the number corresponding to the area you want to fill: ";
                choice=enter_choice(choice);
                current = fullBoard;
                while(current != NULL && current->pos != choice)
                    current = current->next;
//check if the place which the player choose is empty or not
                if(current->empty == true)
                {
                    current->empty = false;
                    current->square = true;
                    isPlaying = false;
                    first = 2;
                    arr[(current->pos)-1]=current;
                }
                else
                    cout << "The field that you chose is already used...\n";
            }

        }
        else
        {
            // the turn of player 2
            isPlaying = true;
            while(isPlaying == true)
            {
                cout << "Player 2, please put the number corresponding to the area you want to fill: ";
                 choice=enter_choice(choice);
                current = fullBoard;
                while(current != NULL && current->pos != choice)
                    current = current->next;
//check if the place which the player choose is empty or not
                if(current->empty == true)
                {
                    current->empty = false;
                    current->circle = true;
                    isPlaying = false;
                    first = 1;
                    arr[(current->pos)-1]=current;
                }
                else
                    cout << "The field that you chose is already used...\n";
            }
        }

        system("cls");
        //check if player 1 is the winner
        
        if(( arr[0]->square== true && arr[1]->square== true && arr[2]->square== true)
        || ( arr[0]->square== true && arr[3]->square== true && arr[6]->square== true)
        || ( arr[0]->square== true && arr[4]->square== true && arr[8]->square== true)
        || ( arr[6]->square== true && arr[7]->square== true && arr[8]->square== true)
        || ( arr[6]->square== true && arr[4]->square== true && arr[2]->square== true)
        || ( arr[8]->square== true && arr[5]->square== true && arr[2]->square== true)
        || ( arr[3]->square== true && arr[4]->square== true && arr[5]->square== true)){
            cout<<"the winner is player 1 "<<endl;
            isGameOn=false;
        }
         //check if player 2 is the winner
        else if(( arr[0]->square== true && arr[1]->square== true && arr[2]->square== true)
        || ( arr[0]->circle== true && arr[3]->circle== true && arr[6]->circle== true)
        || ( arr[0]->circle== true && arr[4]->circle== true && arr[8]->circle== true)
        || ( arr[6]->circle== true && arr[7]->circle== true && arr[8]->circle== true)
        || ( arr[6]->circle== true && arr[4]->circle== true && arr[2]->circle== true)
        || ( arr[8]->circle== true && arr[5]->circle== true && arr[2]->circle== true)
        || ( arr[3]->circle== true && arr[4]->circle== true && arr[5]->circle== true)){
            cout<<"the winner is player 2 "<<endl;
            isGameOn=false;
    }
    //check if draw
    else if (  arr[0]->empty== false && arr[1]->empty== false && arr[2]->empty== false
         && arr[3]->empty== false && arr[4]->empty== false && arr[5]->empty== false
         && arr[6]->empty== false && arr[7]->empty== false && arr[8]->empty== false){
             cout<<"--------------DRAW-------------"<<endl;
             isGameOn=false;
         }
    }
   
}
// function to give numbers to the position of each new node in the linked list
board* getBoard(board* fullBoard)
{
    board* newBoard = new board;
    newBoard->empty = true;
    newBoard->circle = false;
    newBoard->square = false;
    newBoard->next = fullBoard;
    if(newBoard->next != NULL)
        newBoard->pos = newBoard->next->pos + 1;
    else
        newBoard->pos = 1;
    return newBoard;


}
void twoplayers()
{
    int dice, first;

    board* fullBoard = NULL;
    cout << "Welcome to Tic-tac-toe DOS Game. (2 Player version)\n\n";
    cout << "X is Player 1 and O is Player 2.\nI will decide who is starting in the first match...\n ";
    srand(time(NULL));
    dice = 1;//rand() % 6 + 1;
    cout << dice;
    if(dice <= 3)
    {
        first = 1;
        cout << "Player 1 is the first!\n";
    }
    else
    {
        first = 2;
        cout << "Player 2 is the first!\n\n";
    }
    system("pause");
    system("cls");
    startGame(first, fullBoard);
    return;
}
double enter_number(double x)
{
     label:
         cin>>x;
   if (cin.fail())
    {
        //Print error message
        cout << "Invalid Input , it should only consist of digits!! Enter Another "<<endl;
        //Clear error flags
        cin.clear();
        //Ignore any whitespace left on input stream by cin
        cin.ignore(256, '\n');
        goto label;
   }
   else if (x != 1 && x != 2  )
    {
        cout<<"please enter valid number"<<endl;
        goto label;
    } 
                //Validating that the Input Number Is A POSITIVE INTEGER
else if ( x<0  ){
    cout<<"Invalid Input, Input cannot be a Negative Value!! Enter Another "<<endl;
goto label;
}
return x;
}
double enter_choice(double y)
{
     label:
         cin>>y;
   if (cin.fail())
    {
        //Print error message
        cout << "Invalid Input , it should only consist of digits!! Enter Another "<<endl;
        //Clear error flags
        cin.clear();
        //Ignore any whitespace left on input stream by cin
        cin.ignore(256, '\n');
        goto label;
   }
   else if (y < 1 || y > 9)
                {
                    cout << "Invalid choice. Please choose a valid option: ";
                   goto label;
                }
   
               
return y;
}
