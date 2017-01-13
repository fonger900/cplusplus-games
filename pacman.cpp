#include<iostream>
#include<ctime>//for random number
#include<cstdlib>
#include<conio.h>// for using getch()

using namespace std;

int i,j,checkuser,checkenemy,randm,food=0,estate;
int player[2] = {0,0},enemy[2] = {4,4};
void displayboard();
int playerlogic();
int enemylogic();
char board[5][5];
char usermove,temp,nextposition;

//move up function
char moveup(int& a,int& b)
{
    --a;
    temp = board[a][b];
    board[a][b] = board[a+1][b];//replace current character with previous position character
    board[a+1][b] = '-';//previous character set to character '-'
    return temp;//return previous character
}

//move down function
char movedown(int& a,int& b)
{
    ++a;
    temp = board[a][b];
    board[a][b] = board[a-1][b];
    board[a-1][b] = '-';
    return temp;//return previous character
}

//move right function
char moveright(int& a,int& b)
{
    ++b;
    temp = board[a][b];
    board[a][b] = board[a][b-1];
    board[a][b-1] = '-';
    return temp;//return previous character
}

//move left function
char moveleft(int& a,int& b)
{
    --b;
    temp = board[a][b];
    board[a][b] = board[a][b+1];
    board[a][b+1] = '-';
    return temp;//return previous character
}
//detect contact of two object
//if player and enemy move to the same position then return -1
int detectcontact()
{
    if(player[0] == enemy[0] && player[1]==enemy[1])
        {
            board[enemy[0]][enemy[1]] = '*';
            board[player[0]][player[1]] = '*';
            return -1;
        }
        else
            return 0;
}

/**
Pacman game:
- player controls 'P' by using keys as a,s,w,d to move.
- eating up to 3 food(F) to win.
- enemy(G) move randomly, if it catch you, you lose.
**/
int main()
{
    //loop to set all element of array board to '-'
    for( i = 0;i<5;++i)
    {
        for( j = 0;j<5;++j)
        {
            board[i][j] = '-';
        }
    }

    board[0][0] = 'P';// 'P' is player
    board[3][4] = 'F';// 'F' is food
    board[1][2] = 'F';
    board[0][3] = 'F';
    board[4][4] = 'G';// 'G' is enemy
    srand(time(NULL));//seed of random number
    do//loop until win or lose
    {
        displayboard();
        cout << "Enter your move: ";
        cin >> usermove;
        checkuser = playerlogic();//check for lose and win
        checkenemy = enemylogic();// check for lose
    }while( food <3 && checkenemy != -1 && checkuser != -1);
    displayboard();
    if(food == 3)
        cout << "You win!"<<endl;
    else if(checkuser ==-1 || checkenemy ==-1)
        cout << "You lose!"<<endl;
    getch();
    return 0;
}

//player's move logic
int playerlogic()
{
    switch(usermove)
    {
    case 'w':

        if((player[0]-1)>=0)//check whether 'P' is in board or not
        {
            nextposition = moveup(player[0],player[1]);
            if(nextposition == 'F')//food was eaten
                ++food;
        }
        break;
    case 's':

        if((player[0]+1)<5)//same to above
        {
            nextposition=movedown(player[0],player[1]);
            if(nextposition == 'F')
                ++food;
        }
        break;
    case 'a':

        if((player[1]-1)>=0)//same to above
        {
            nextposition = moveleft(player[0],player[1]);
            if(nextposition == 'F')
                ++food;
        }
        break;
    case 'd':

        if((player[1]+1)<5)//same to above
        {
            nextposition = moveright(player[0],player[1]);
            if(nextposition == 'F')
                ++food;
        }
        break;
    default:
        break;
    }

    return detectcontact();//check whether the enemy has catch you or not
}

//enemy's move logic bot
int enemylogic()
{
    //loop until find the appropriate move(avoid 'F' and board's edges)
    do
    {
        randm = rand()%4;//produce random number ranged from 0 to 3
        switch(randm)
        {
        case 0://move up
            if((enemy[0]-1)>=0 && board[enemy[0]-1][enemy[1]] != 'F')//avoid move out of board and move on 'F'
            {
                moveup(enemy[0],enemy[1]);
                estate = 0;//state of enemy. 0 is escape the loop, -1 is continue
            }else
                estate = -1;//continue loop
            break;
        case 1://move down
            if((enemy[0]+1)<5 && board[enemy[0]+1][enemy[1]] !='F')//same to above
            {
                movedown(enemy[0],enemy[1]);
                estate = 0;
            }else
                estate = -1;
            break;
        case 2://move right
            if((enemy[1]+1)<5 && board[enemy[0]][enemy[1]+1] !='F')//same
            {
                moveright(enemy[0],enemy[1]);
                estate = 0;
            }else
                estate = -1;
            break;
        case 3://move left
            if((enemy[1]-1)>=0 && board[enemy[0]][enemy[1]-1] !='F')//same
            {
                moveleft(enemy[0],enemy[1]);
                estate = 0;
            }else
                estate = -1;
            break;
        default:
            estate = -1;
            break;
        }
    }while(estate < 0);

    return detectcontact();//check for player's lost
}

void displayboard()
{
    system("cls");//refresh the console's screen
    for(i = 0;i<5;++i )
    {
        for(j=0;j<5;++j)//using loop to display all elements of array board
        {
            cout << board[i][j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << "food: " <<food<<endl;
    cout << "random: " <<randm<<endl;
}
