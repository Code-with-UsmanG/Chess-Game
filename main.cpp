#include<iostream>
#include<windows.h>
using namespace std;
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<fstream>

//Player 1 Characters
char pawn1='P',rook1='R',knight1='N',bishop1='B',queen1='Q',king1='K';
//Player 2 Characters
char pawn2='p',rook2='r',knight2='n',bishop2='b',queen2='q',king2='k';

//checking first move of King of Player 1
int check_moved_1=0;
//checking first move of King of Player 2
int check_moved_2=0;

//Functions Declaration
void print_game_board(int row, int col, char ch, int dim);//1F
void print_labels(int row, int col, int dim);//2F
void print_box_space_for_players(int row, int col, char ch);//3F
void only_generating_array(char A[], int dim);//4F
void array_board(char A[], int dim);//5F
int TwoD_2_OneD(int row, int col, int dim);//6F
void write_on_board(char A[], int old_ri, int old_ci, int new_ri, int new_ci, int dim, bool turn);//7F
void turn_change(bool &turn);//8F
void play_game(char A[],int dim, bool turn);//9F

//Demo Functions(DF)
void print_demo_chess_board(int row, int col, char ch);//DF1
void generating_demo_array(char A[], int dim);//DF2
void print_demo_array_board(char A[], int dim);//DF3
void print_demo_labels(int row, int col, int dim);//DF4

//Additional Functions
void pawn_promotion(char A[], int new_position, int dim);//AF1
void rules_of_chess();//AF2
void privacy_and_legal_info();//AF3
void player_1_castling(char A[],int dim,int old_position,int new_position,bool turn);//AF4
void player_2_castling(char A[],int dim,int old_position,int new_position,bool turn);//AF5

//Code begins
void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos=rpos;
    COORD scrn;
    HANDLE hOuput=GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X=cpos;
    scrn.Y=rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void sleep(int m)
{
    for(int j=0;j<m*21000;j++)
    {

    }
}
//AF1
void pawn_promotion(char A[], int new_position, int dim)
{
    char promotion;
    gotoRowCol(35,0);
    cout<<"Congratulations! Eighth rank reached."<<endl;
    cout<<"Eligible to promote Pawn."<<endl;
    cout<<"Select from choices given below!"<<endl;
    cout<<"(Q)ueen"<<endl;
    cout<<"(R)ook"<<endl;
    cout<<"(B)ishop"<<endl;
    cout<<"K(N)ight."<<endl;
    gotoRowCol(42,0);
    cout<<"Enter your choice:";
    gotoRowCol(42,19);
    cin>>promotion;
    A[new_position]=promotion;
    array_board(A,dim);
}
//1F
void print_game_board(int row, int col, char ch, int dim)
{
    int initial_row=row;
    int initial_col=col;
    //Printing labels on Chess Board
    print_labels(row,col,dim);//2F
    //horizontal loop
    for(int k=0;k<=dim;k++)
    {
        for(int i=col;i<=col+dim*10;i++)
        {
            gotoRowCol(row,i);
            cout<<ch;
        }
        cout<<endl;
        row+=5;
    }
    //changing character
    ch=176;
    //vertical loop
    for (int k=0;k<=dim;k++)
    {
        for (int j=initial_row;j<=initial_row+dim*5;j++)
        {
            gotoRowCol(j,initial_col);
            cout<<ch;
        }
        cout<<endl;
        initial_col+=10;
    }
}
//2F
void print_labels(int row, int col, int dim)
{
    //Printing labels on left and top side
    //Printing column labels on top side(1, 2, 3, ..., 8)
    int col_label_1=1;
    for (int i=col;i<col+dim*10;i+=10)
    {
        gotoRowCol(row-2,i+5);
        cout<<col_label_1;
        col_label_1++;
    }
    //Printing row labels on left side(1, 2, 3, ..., 8)
    int row_label_1=1;
    for (int j=row;j<row+dim*5;j+=5)
    {
        gotoRowCol(j+3,col-3);
        cout<<row_label_1;
        row_label_1++;
    }
    //Printing labels on right and bottom side
    //Printing column labels on bottom side(1, 2, 3, ..., 8)
    int col_label_2=1;
    for (int i=col;i<col+dim*10;i+=10)
    {
        gotoRowCol(row+42,i+5);
        cout<<col_label_2;
        col_label_2++;
    }
    //Printing column labels on right side(1, 2, 3, ..., 8)
    int row_label_2=1;
    for (int j=row;j<row+dim*5;j+=5)
    {
        gotoRowCol(j+3,col+83);
        cout<<row_label_2;
        row_label_2++;
    }
}
//3F
void print_box_space_for_players(int row, int col, char ch)
{
    row=4;
    col=0;
    ch=178;
    //Printing box on Chess Board for Player 1
    //horizontal loop(runs 3 times)
    for(int i=1;i<=3;i++)
    {
        for(int k=col;k<=col+33;k++)
        {
            gotoRowCol(row,k);
            cout<<ch;
            sleep(200);
        }
        row+=15;
        cout<<endl;
    }
    gotoRowCol(6,0);
    cout<<"_________________________________"<<endl;
    sleep(200);
    gotoRowCol(21,0);
    cout<<"_________________________________"<<endl;
    sleep(200);
    //vertical loop
    row=4;
    col=33;
    for (int j=row;j<=row+29;j++)
    {
        gotoRowCol(j,col);
        cout<<ch;
        sleep(200);
    }
    ch=219;
    gotoRowCol(10,34);
    cout<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<endl;
    sleep(200);
    gotoRowCol(30,34);
    cout<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<ch<<endl;
    sleep(200);
}
//4F
void only_generating_array(char A[],int dim)
{
    for(int i=0;i<dim*dim;i++)
    {
        //player1
        if(i==0 || i==7)
        {
            A[i]=rook1;//putting player 1 Character in array
        }
        else if(i==1 || i==6)
        {
            A[i]=knight1;//putting player 1 Character in array
        }
        else if(i==2 || i==5)
        {
            A[i]=bishop1;//putting player 1 Character in array
        }
        else if(i==3)
        {
            A[i]=queen1;//putting player 1 Character in array
        }
        else if(i==4)
        {
            A[i]=king1;//putting player 1 Character in array
        }
        else if(i>=8 && i<=15)
        {
            A[i]=pawn1;//putting player 1 Character in array
        }
        //player2
        else if(i==56 || i==63)
        {
            A[i]=rook2;//putting player 2 Character in array
        }
        else if(i==57 || i==62)
        {
            A[i]=knight2;//putting player 2 Character in array
        }
        else if(i==58 || i==61)
        {
            A[i]=bishop2;//putting player 2 Character in array
        }
        else if(i==59)
        {
            A[i]=queen2;//putting player 2 Character in array
        }
        else if(i==60)
        {
            A[i]=king2;//putting player 2 Character in array
        }
        else if(i>=48 && i<=55)
        {
            A[i]=pawn2;//putting player 2 Character in array
        }
        else
        {
            A[i]='-';//putting space in array
        }
    }
}
//5F
void array_board(char A[],int dim)
{
    int row=5,col=45;
    int initial_row=row;
    int initial_col=col;
    ofstream file("game_state.txt");
    for (int i=0;i<dim*dim;i++)
    {
        gotoRowCol(row+2,col+4);
        cout<<A[i];
        file<<A[i];
        sleep(100);
        if(i%dim==dim-1)
        {
            cout<<endl;
            file<<endl;
            row+=5;
            col=initial_col;
        }
        else
        {
            col+=10;
        }
     }
      file.close();
}
//loading saved game
void reading_saved_game(char A[],int dim,bool turn)
{
    ifstream file01("game_state.txt");
    for (int i=0;i<(dim*dim);i++)
    {
        file01>>A[i];
    }
    file01.close();
}
//6F
int TwoD_2_OneD(int row, int col, int dim)
{
    return (row-1)*dim+(col-1);
}
//7F
void write_on_board(char A[], int old_ri, int old_ci, int new_ri, int new_ci, int dim, bool turn)
{
    //converting old row and old column into old position(making 1D array)
    int old_position=TwoD_2_OneD(old_ri,old_ci,dim);
    //converting new row and new column into old position(making 1D array)
    int new_position=TwoD_2_OneD(new_ri,new_ci,dim);
         ////////////////////////////////////
         //Player 1(Capital_Characters)//////
         ///////////////////////////////////
         if(turn==1)
         {
          if(A[old_position]=='P' || A[old_position]=='B' || A[old_position]=='N' || A[old_position]=='R' || A[old_position]=='K' || A[old_position]=='Q')
          {
              //clearing disclaimer "Please move your own character"
              gotoRowCol(10,0);
              cout<<"                          "<<endl;
              //clearing disclaimer "Please select your character"
              gotoRowCol(10,0);
              cout<<"                          "<<endl;
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Pawn's move(Player 1)////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            // Checking if there is Pawn's move
            if(A[old_position]=='P')
            {
                //checking 1st time move of Pawn
               if(old_position/dim==1)
               {
                 //checking validity for straight move
                 if(old_position+8==new_position || old_position+16==new_position)
                 {
                    //checking if that box is empty (validity of new position)
                    if(A[new_position]=='-')
                    {
                        //Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        //Clearing old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                 }
                 //checking diagonal move of pawn
                 else if(old_position+9 == new_position || old_position+7 == new_position)
                 {
                    if(A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                 }
                 //if the move is neither straight nor diagonal then asking again
                 else
                 {
                    play_game(A,dim,turn);
                 }
               }
               //checking all moves of Pawn after 1st move
               else if(old_position/dim>1)
               {
                //checking validity for straight move(2ND move)
                if(old_position+8==new_position)
                {
                    //checking if that box is empty(validity of new position)
                    if(A[new_position]=='-')
                    {
                        // Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        // Clearing old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                        ///////promotion//////////
                        if(A[new_position]=='P' && new_position/dim>=7)
                        {
                            pawn_promotion(A,new_position,dim);
                        }
                        /////////////////////////
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking diagonal move of pawn
                else if(old_position+9 == new_position || old_position+7 == new_position)
                {
                    if(A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        //Clearing old position
                        A[old_position]='-';
                        //Updating array
                        array_board(A,dim);
                        /////////promotion////////
                        if(A[new_position]=='P' && new_position/dim>=7)
                        {
                            pawn_promotion(A,new_position,dim);
                        }
                        /////////////////////////
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
             }
            }//Pawn's move ended
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Rook's move(Player 1)////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            //Checking if there is Rook's move
            else if(A[old_position]=='R')
            {
               //checking validity of vertical move of rook
               if(old_position+8==new_position || old_position+16==new_position || old_position+24==new_position || old_position+32==new_position || old_position+40==new_position || old_position+48==new_position || old_position+56==new_position || old_position-8==new_position || old_position-16==new_position || old_position-24==new_position || old_position-32==new_position || old_position-40==new_position || old_position-48==new_position || old_position-56==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                       //positive direction move (for assistance)
                      //logical positions of movement (7)
                      if(old_position+8==new_position)
                      {
                        //checking validity of new position)
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clearing old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (7)
                        else if(old_position+16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                //Moving Rook on the new position
                                A[new_position]=A[old_position];
                                //Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+24==new_position)
                        {
                            //checking valid move within the positions(empty places must required)
                            if(A[old_position+8]=='-' && A[old_position+16]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                //Moving Rook on the new position
                                A[new_position]=A[old_position];
                                //Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-' && A[old_position+48]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                //Moving Rook on the new position
                                A[new_position]=A[old_position];
                                //Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative direction move (for assistance)
                        //logical positions of movement (7)
                        else if(old_position-8==new_position)
                        {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            //Moving Rook on the new position
                            A[new_position]=A[old_position];
                            //Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position-16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }

                        }
                        //logical positions of movement (7)
                        else if(old_position-32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' & A[old_position-32]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-' && A[old_position-48]=='-')
                            {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }
                //checking validity of horizontal move of rook
                else if(old_position+1==new_position || old_position+2==new_position || old_position+3==new_position || old_position+4==new_position || old_position+5==new_position || old_position+6==new_position || old_position+7==new_position || old_position-1==new_position || old_position-2==new_position || old_position-3==new_position || old_position-4==new_position || old_position-5==new_position || old_position-6==new_position || old_position-7==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //positive direction move (for assistance)
                        //logical positions of movement (7)
                      if(old_position+1==new_position)
                      {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (7)
                        else if(old_position+2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-')
                            {
                            //this is actually checking new position
                              if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+7==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-' && A[old_position+6]=='-')
                            {
                             //this is actually checking new position
                              if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative direction move(for assistance)
                        //logical positions of movement (7)
                        else if(old_position-1==new_position)
                        {
                        //checking if the very next position is valid or empty or available
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position-2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-')
                            {
                             //this is actually checking new position
                              if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-7==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-' && A[old_position-6]=='-')
                            {
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    //if new position is invalid for rook
                    play_game(A,dim,turn);
                }
             }//Rook's move ended
             /////////////////////////////////////////////////////////////////////////////////////////////
             ///////////////////////////////////////Knight's move(Player 1)//////////////////////////////
             ////////////////////////////////////////////////////////////////////////////////////////////
             //Checking if there is knight's move
            else if(A[old_position]=='N')
            {
                //checking validity of new position
                if(old_position+15==new_position || old_position+17==new_position || old_position+10==new_position || old_position+6==new_position || old_position-15==new_position || old_position-17==new_position || old_position-10==new_position || old_position-6==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='k' || A[new_position]=='q' || A[new_position]=='r')
                    {
                        // Moving Knight on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
            }//Knight's move ended
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Bishop's move(Player 1)//////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='B')
            {
                //checking validity of new position (with multiple of 7)
                if(old_position+7==new_position || old_position+14==new_position || old_position+21==new_position || old_position+28==new_position || old_position+35==new_position || old_position+42==new_position || old_position+49==new_position || old_position-7==new_position || old_position-14==new_position || old_position-21==new_position || old_position-28==new_position || old_position-35==new_position || old_position-42==new_position || old_position-49==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //one diagonal step
                        if(old_position+7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+28==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+35==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+42==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }

                        }
                        else if(old_position+49==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-' && A[old_position+42]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //negative direction movement (for assistance)
                        //logical movements of Bishop(7)
                        else if(old_position-7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]=' ';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-28==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-42==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }

                        }
                        else if(old_position-49==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-' && A[old_position-42]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }

                }// 1st if
                //checking validity of new position (with multiple of 9)
                else if(old_position+9==new_position || old_position+18==new_position || old_position+27==new_position || old_position+36==new_position || old_position+45==new_position || old_position+54==new_position ||old_position+63==new_position || old_position-9==new_position || old_position-18==new_position || old_position-27==new_position || old_position-36==new_position || old_position-45==new_position || old_position-54==new_position ||old_position-63==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //one diagonal step
                        if(old_position+9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+36==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]=' ';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }

                        }
                        else if(old_position+63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-' && A[old_position+54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //one diagonal step
                        if(old_position-9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-36==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]=' ';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }

                        }
                        else if(old_position-63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-' && A[old_position-54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //below is 1st ifs, else and it is required must as if new position is invalid
                else
                {
                    play_game(A,dim,turn);
                }
                //below is else-ifs closing bracket that checks for Bishop's move
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Queen's move(Player 1)///////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='Q')
            {
                /////////////////////////////////
                ////checking rook's like move////

                ////begins///////////////////////
                //checking validity of vertical move of rook(multiple of 8)
               if(old_position+8==new_position || old_position+16==new_position || old_position+24==new_position || old_position+32==new_position || old_position+40==new_position || old_position+48==new_position || old_position+56==new_position || old_position-8==new_position || old_position-16==new_position || old_position-24==new_position || old_position-32==new_position || old_position-40==new_position || old_position-48==new_position || old_position-56==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //positive direction movement (for assistance)
                        //logical positions of movement (7)
                      if(old_position+8==new_position)
                      {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position+8]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (7)
                        else if(old_position+16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+56==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-' && A[old_position+48]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative direction movement (for assistance)
                        //logical positions of movement (7)
                        else if(old_position-8==new_position)
                        {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position-16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]=' ';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-48==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-' && A[old_position-48]=='-')
                            {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // below is ifs(that checks availability of new position)closing bracket and else
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }
                //checking validity of vertical move of rook(incrementing/decrementing in 1 till 8)
                else if(old_position+1==new_position || old_position+2==new_position || old_position+3==new_position || old_position+4==new_position || old_position+5==new_position || old_position+6==new_position || old_position+7==new_position || old_position-1==new_position || old_position-2==new_position || old_position-3==new_position || old_position-4==new_position || old_position-5==new_position || old_position-6==new_position || old_position-7==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //positive direction movement (for assistance)
                        //logical positions of movement (7)
                      if(old_position+1==new_position)
                      {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (7)
                        else if(old_position+2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]==' ' && A[old_position+5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+7==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-' && A[old_position+6]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative direction movement (for assistance)
                        //logical positions of movement (7)
                        else if(old_position-1==new_position)
                        {
                        //checking if the very next position is valid or empty or available
                        if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position-2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-7==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-' && A[old_position-6]=='-')
                            {
                             if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                              else
                              {
                                play_game(A,dim,turn);
                              }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }///////////////rook like move ends of queen (Player 1)/////////////////

                ///////////////////////////////////
                ////checking bishop's like move////

                /////begins////////////////////////
                //checking validity of new position (multiple of 7)
                else if(old_position+7==new_position || old_position+14==new_position || old_position+21==new_position || old_position+28==new_position || old_position+35==new_position || old_position+42==new_position || old_position+49==new_position || old_position-7==new_position || old_position-14==new_position || old_position+21==new_position || old_position-28==new_position || old_position-35==new_position || old_position-42==new_position || old_position-49==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //positive direction movement (for assistance)
                        //one diagonal step
                        if(old_position+7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+28==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+42==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+49==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-' && A[old_position+42]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //negative direction movement (for assistance)
                        //one diagonal step
                        else if(old_position-7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-28==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-42==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-49==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-' && A[old_position-42]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }

                }// else if closing bracket
                //checking validity of new position (multiple of 9)
                else if(old_position+9==new_position || old_position+18==new_position || old_position+27==new_position || old_position+36==new_position || old_position+45==new_position || old_position+54==new_position ||old_position+63==new_position || old_position-9==new_position || old_position-18==new_position || old_position-27==new_position || old_position-36==new_position || old_position-45==new_position || old_position-54==new_position ||old_position-63==new_position)
                {
                    //whole diagonal, checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p'|| A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //positive direction movement (for assistance)
                        //one diagonal step
                        if(old_position+9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+36==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+54==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }

                        }
                        else if(old_position+63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-' && A[old_position+54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //negative direction movement (for assistance)
                        //one diagonal step
                        else if(old_position-9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-36==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-54==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-' && A[old_position -54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='r' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='q' || A[new_position]=='k')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //if the position does not lies in above conditions then
                else
                {
                    play_game(A,dim,turn);
                }
                //////////////Bishop like move ends of queen (Player 1)///////////////
            }
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////King's move(Player 1)///////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='K')
            {
                if((old_position == 4 && new_position== 6) || (old_position == 4 && new_position==2))
                {
                    if(check_moved_1==0)
                    {
                         player_1_castling(A,dim,old_position,new_position,turn);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking valid move of King
                else if(old_position+8==new_position || old_position-8==new_position  || old_position+1==new_position || old_position-1==new_position || old_position+7==new_position || old_position-7==new_position || old_position+9==new_position || old_position-9==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='p' || A[new_position]=='b' || A[new_position]=='n' || A[new_position]=='r' || A[new_position]=='q' || A[new_position]=='k')
                    {
                        //Moving King on the new position
                        A[new_position]=A[old_position];
                        //Clearing old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                        check_moved_1+=1;
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
            }
            //don't touch brackets below
          }
          //if player tries to move empty character(" " or "-")
          else if(A[old_position]=='-')
          {
              gotoRowCol(10,0);
              cout<<"Please select your pieces!"<<endl;
              play_game(A,dim,turn);
          }
          else
          {
              gotoRowCol(10,0);
              cout<<"Please move your own piece!"<<endl;
              play_game(A,dim,turn);
          }
        }
        //Player 1 move ends

        //////////////////////////////////////
        //////Player 2(Small Characters)//////
        //////////////////////////////////////

        //player 2 begins
        else if(turn==0)
        {
          //checking if player 2 moves his/her own character
          if(A[old_position]=='p' || A[old_position]=='n' || A[old_position]=='r' || A[old_position]=='b' || A[old_position]=='k' || A[old_position]=='q')
           {
            //Clearing disclaimer "Please move your pieces"
            gotoRowCol(25,0);
            cout<<"                             "<<endl;
            gotoRowCol(25,0);
            cout<<"                             "<<endl;
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Pawn's move(Player 2)////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            // Checking if there is Pawn's move
            if(A[old_position]=='p')
            {
              //checking 1st time move of pawn(player2)
              if(old_position/dim==6)
              {
                //checking validity for straight move
                if(old_position-8==new_position || old_position-16==new_position)
                {
                    //checking if that place is available
                    if(A[new_position]=='-')
                    {
                        //Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking diagonal move of pawn
                else if(old_position-9 == new_position || old_position-7 == new_position)
                {
                    if(A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        // Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //if pawn tries to perform invalid move
                else
                {
                    play_game(A,dim,turn);
                }
              }
              //checking 2ND time move of pawn
             else if(old_position/dim<6)
             {
                //checking validity for straight move
                if(old_position-8==new_position)
                {
                    //checking if that box is empty
                    if(A[new_position]=='-')
                    {
                        // Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                        ///////promotion//////////
                        if(A[new_position]=='p' && new_position/dim==0)
                        {
                            pawn_promotion(A,new_position,dim);
                        }
                        /////////////////////////
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking diagonal move of pawn
                else if(old_position-9 == new_position || old_position-7 == new_position)
                {
                    if(A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //Moving Pawn on the new position
                        A[new_position]=A[old_position];
                        //Clear the old position
                        A[old_position]='-';
                        //Updating array
                        array_board(A,dim);
                        ///////promotion//////////
                        if(A[new_position]=='p' && new_position/dim==0)
                        {
                            pawn_promotion(A,new_position,dim);
                        }
                        /////////////////////////
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
             //Below is closing bracket of checking if 2ND move of pawn
             }
            //Below is closing bracket of pawn's if statement
           }//Pawn move ends(Player 2)

            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Rook's move(Player 2)////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            //checking if there is Rook's move
            else if(A[old_position]=='r')
            {
               //checking validity of rook's position vertically
               if(old_position+8==new_position || old_position+16==new_position || old_position+24==new_position || old_position+32==new_position || old_position+40==new_position || old_position+48==new_position || old_position+56==new_position || old_position-8==new_position || old_position-16==new_position || old_position-24==new_position || old_position-32==new_position || old_position-40==new_position || old_position-48==new_position || old_position-56==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //positive move
                        //logical positions of movement (7)
                        if(old_position+8==new_position)
                        {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position+16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-')
                            {
                            //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-' && A[old_position+48]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative position
                        //logical positions of movement (7)
                        else if(old_position-8==new_position)
                        {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (7)
                        else if(old_position-16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]==' ' && A[old_position-32]=='-' && A[old_position-40]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-' && A[old_position-48]=='-')
                            {
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking horizontal move of rook
                else if(old_position+1==new_position || old_position+2==new_position || old_position+3==new_position || old_position+4==new_position || old_position+5==new_position || old_position+6==new_position || old_position+7==new_position || old_position-1==new_position || old_position-2==new_position || old_position-3==new_position || old_position-4==new_position || old_position-5==new_position || old_position-6==new_position || old_position-7==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //positive move
                        //logical positions of movement (7)
                      if(old_position+1==new_position)
                      {
                        //checking if the very next position is not empty
                       if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (7)
                        else if(old_position+2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-')
                            {
                            //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position+7==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-' && A[old_position+6]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative position
                        //logical positions of movement (7)
                        else if(old_position-1==new_position)
                        {
                        //checking if the very next position is valid or empty or available
                         if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                         {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                         }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //logical positions of movement (7)
                        else if(old_position-2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (7)
                        else if(old_position-7==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-' && A[old_position-6]=='-')
                            {
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                // main else condition if the move is not in both checks
                else
                {
                    play_game(A,dim,turn);
                }
            }//Rook's move ended
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Knight's move(Player 2)//////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            //Checking if there is Knight's move
            else if(A[old_position]=='n')
            {
                //checking validity of new position
                if(old_position+15==new_position || old_position+17==new_position || old_position+10==new_position || old_position+6==new_position || old_position-15==new_position || old_position-17==new_position || old_position-10==new_position || old_position-6==new_position)
                {
                    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='K' || A[new_position]=='Q' || A[new_position]=='R')
                    {
                        // Moving Knight on the new position
                        A[new_position]=A[old_position];
                        // Clear the old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
            }//Knight's move ended
            /////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Bishop's move(player 2)///////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='b')
            {
                //checking validity of new position (with multiple of 7)
                if(old_position+7==new_position || old_position+14==new_position || old_position+21==new_position || old_position+28==new_position || old_position+35==new_position || old_position+42==new_position || old_position+49==new_position || old_position-7==new_position || old_position-14==new_position || old_position-21==new_position || old_position-28==new_position || old_position-35==new_position || old_position-42==new_position || old_position-49==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P'|| A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //one diagonal step
                        if(old_position+7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P'|| A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+28==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+42==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+49==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-' && A[old_position+42]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //negative positions
                        //one diagonal step
                        else if(old_position-7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P'|| A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-28==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-35==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-42==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-49==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-' && A[old_position-42]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }// 1st if
                //checking validity of new position (with multiple of 9)
                else if(old_position+9==new_position || old_position+18==new_position || old_position+27==new_position || old_position+36==new_position || old_position+45==new_position || old_position+54==new_position ||old_position+63==new_position || old_position-9==new_position || old_position-18==new_position || old_position-27==new_position || old_position-36==new_position || old_position-45==new_position || old_position-54==new_position ||old_position-63==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P'|| A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //one diagonal step
                        if(old_position+9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+36==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-' && A[old_position+54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //one diagonal step
                        else if(old_position-9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                //Moving Rook on the new position
                                A[new_position]=A[old_position];
                                //Clearing old position in array
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-36==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-45==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-' && A[old_position-54]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //below is 1st ifs, else and it is required must as if new position is invalid
                else
                {
                    play_game(A,dim,turn);
                }
                //below is else-ifs closing bracket that checks for Bishop's move
            }//Bishop's move ended
            ////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////Queen's move(Player 2)///////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='q')
            {
                /////////////////////////////////
                ////checking Rook's like move of Queen(Player 2)////

                //checking validity of vertical move of rook
               if(old_position+8==new_position || old_position+16==new_position || old_position+24==new_position || old_position+32==new_position || old_position+40==new_position || old_position+48==new_position || old_position+56==new_position || old_position-8==new_position || old_position-16==new_position || old_position-24==new_position || old_position-32==new_position || old_position-40==new_position || old_position-48==new_position || old_position-56==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-'|| A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //positive move
                        //logical positions of movement (8)
                      if(old_position+8==new_position)
                      {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (8)
                        else if(old_position+16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position+24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position+32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-')
                            {
                            //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position+40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position+48==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position+56==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position+8]=='-' && A[old_position+16]=='-' && A[old_position+24]=='-' && A[old_position+32]=='-' && A[old_position+40]=='-' && A[old_position+48]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative position
                        //logical positions of movement (8)
                      else if(old_position-8==new_position)
                      {
                        //checking if the very next position is not empty
                       if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (8)
                        else if(old_position-16==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position-24==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position-32==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                           if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-')
                           {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position-40==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position-48==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (8)
                        else if(old_position-56==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-8]=='-' && A[old_position-16]=='-' && A[old_position-24]=='-' && A[old_position-32]=='-' && A[old_position-40]=='-' && A[old_position-48]=='-')
                            {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }
                //checking validity of horizontal move of rook
                else if(old_position+1==new_position || old_position+2==new_position || old_position+3==new_position || old_position+4==new_position || old_position+5==new_position || old_position+6==new_position || old_position+7==new_position || old_position-1==new_position || old_position-2==new_position || old_position-3==new_position || old_position-4==new_position || old_position-5==new_position || old_position-6==new_position || old_position-7==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //positive move
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                      if(old_position+1==new_position)
                      {
                        //checking if the very next position is not empty
                        if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position+8]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                      }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-')
                            {
                            //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-')
                            {
                             //this is actually checking new position
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position+7==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position+1]=='-' && A[old_position+2]=='-' && A[old_position+3]=='-' && A[old_position+4]=='-' && A[old_position+5]=='-' && A[old_position+6]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        // negative position
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-1==new_position)
                        {
                        //checking if the very next position is valid or empty or available
                        if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                        {
                            // Moving Rook on the new position
                            A[new_position]=A[old_position];
                            // Clear the old position
                            A[old_position]='-';
                            //updating array
                            array_board(A,dim);
                        }
                        else
                        {
                            play_game(A,dim,turn);
                        }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-2==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-3==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-4==new_position)
                        {
                            //checking if all the positions between old and new position are empty
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-5==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-6==new_position)
                        {
                            //checking valid move within the positions
                            if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-')
                            {
                             //this is actually checking new position
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                 play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        //logical positions of movement (incrementing/decrementing in 1 till 7)
                        else if(old_position-7==new_position)
                        {
                            //checking valid move within the positions
                           if(A[old_position-1]=='-' && A[old_position-2]=='-' && A[old_position-3]=='-' && A[old_position-4]=='-' && A[old_position-5]=='-' && A[old_position-6]=='-')
                            {
                             if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                             {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                             }
                             else
                             {
                                play_game(A,dim,turn);
                             }
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                    }
                    else
                    {
                        //if new position is invalid for rook
                        play_game(A,dim,turn);
                    }
                }////Rook's like move ends of Queen(Player 2)////

                ///////////////////////////////////
                ////checking Bishop's like move of Queen(Player 2)////

                //checking validity of new position (with multiple of 7)
                else if(old_position+7==new_position || old_position+14==new_position || old_position+21==new_position || old_position+28==new_position || old_position+35==new_position || old_position+42==new_position || old_position+49==new_position || old_position-7==new_position || old_position-14==new_position || old_position-21==new_position || old_position-28==new_position || old_position-35==new_position || old_position-42==new_position || old_position-49==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P'|| A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //one diagonal step
                        if(old_position+7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+28==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+42==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+49==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+7]=='-' && A[old_position+14]=='-' && A[old_position+21]=='-' && A[old_position+28]=='-' && A[old_position+35]=='-' && A[old_position+42]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //after this
                        //one diagonal step
                        if(old_position-7==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position+8]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-14==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-21==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-28==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-35==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-42==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-49==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-7]=='-' && A[old_position-14]=='-' && A[old_position-21]=='-' && A[old_position-28]=='-' && A[old_position-35]=='-' && A[old_position-42]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    //if new position is invalid to move, such as can't move on own character place and so on.
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }// 1st if
                //checking validity of new position (with multiple of 9)
                else if(old_position+9==new_position || old_position+18==new_position || old_position+27==new_position || old_position+36==new_position || old_position+45==new_position || old_position+54==new_position ||old_position+63==new_position || old_position-9==new_position || old_position-18==new_position || old_position-27==new_position || old_position-36==new_position || old_position-45==new_position || old_position-54==new_position ||old_position-63==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //one diagonal step
                        if(old_position+9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position+18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-')
                          {
                           if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+36==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]==' ' && A[old_position+45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position+63==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position+9]=='-' && A[old_position+18]=='-' && A[old_position+27]=='-' && A[old_position+36]=='-' && A[old_position+45]=='-' && A[old_position+54]=='-')
                          {
                           if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        //negative positions
                        //one diagonal step
                        else if(old_position-9==new_position)
                        {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                        }
                        else if(old_position-18==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-27==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-')
                          {
                           if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-36==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' )
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-45==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-54==new_position)
                        {
                            //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-')
                          {
                            if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                        else if(old_position-63==new_position)
                        {
                          //checking if previous position before new position is empty
                          if(A[old_position-9]=='-' && A[old_position-18]=='-' && A[old_position-27]=='-' && A[old_position-36]=='-' && A[old_position-45]=='-' && A[old_position-54]=='-')
                          {
                           if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='R' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='Q' || A[new_position]=='K')
                            {
                                // Moving Rook on the new position
                                A[new_position]=A[old_position];
                                // Clear the old position
                                A[old_position]='-';
                                //updating array
                                array_board(A,dim);
                            }
                            else
                            {
                                play_game(A,dim,turn);
                            }
                          }
                          else
                          {
                             play_game(A,dim,turn);
                          }
                        }
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }//////////////Bishop like move ends of queen player 1///////////////
                else
                {
                    play_game(A,dim,turn);
                }
             }
             ////////////////////////////////////////////////////////////////////////////////////////////
             ///////////////////////////////////////King's move(Player 2)///////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////
            else if(A[old_position]=='k')
            {
                if((old_position == 60 && new_position== 62) || (old_position == 60 && new_position== 58))
                {
                    if(check_moved_2==0)
                    {
                         player_2_castling(A,dim,old_position,new_position,turn);
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                //checking valid move of King
                else if(old_position+8==new_position || old_position-8==new_position  || old_position+1==new_position || old_position-1==new_position || old_position+7==new_position || old_position-7==new_position || old_position+9==new_position || old_position-9==new_position)
                {
                    //checking availability of new position
                    if(A[new_position]=='-' || A[new_position]=='P' || A[new_position]=='B' || A[new_position]=='N' || A[new_position]=='R' || A[new_position]=='Q' || A[new_position]=='K')
                    {
                        //Moving King on the new position
                        A[new_position]=A[old_position];
                        //Clearing old position
                        A[old_position]='-';
                        //updating array
                        array_board(A,dim);
                        check_moved_2+=1;
                    }
                    else
                    {
                        play_game(A,dim,turn);
                    }
                }
                else
                {
                    play_game(A,dim,turn);
                }
            }
            ////don't touch brackets below
            //Below checking if player 2 moves his/her character, if closing bracket
         }
          //if player tries to move empty character(" " or "-")
          else if(A[old_position]=='-')
          {
              gotoRowCol(25,0);
              cout<<"Please select your pieces!"<<endl;
              play_game(A,dim,turn);
          }
          else
          {
              gotoRowCol(25,0);
              cout<<"Please move your own piece!"<<endl;
              play_game(A,dim,turn);
          }
        //// Below is Else if(turn==0), closing bracket
      }
       //Below is function's closing bracket
}
//8F
void turn_change(bool &turn)
{
    if(turn==1)
    {
        turn=0;
    }
    else if(turn==0)
    {
        turn=1;
    }
}
//9F
void play_game(char A[],int dim, bool turn)
{
    int o_row,o_col,n_row,n_col;
    while(true)
    {
        //Player 1 & its main "if"
        if(turn==1)
        {
            gotoRowCol(5,0);
            cout<<"Player 1 (Capital_Characters)!"<<endl;
            //old destination
            gotoRowCol(7,0);
            cout<<"Enter your move old(row): ";
            gotoRowCol(7,25);
            cin>>o_row;
            gotoRowCol(8,0);
            cout<<"Enter your move old(Column): ";
            gotoRowCol(8,28);
            cin>>o_col;
            //checking validity of old position (within the dimensions of board)
            if(o_row<=dim && o_col<=dim && o_col>0 && o_col>0)
            {
                //clearing invalid move disclaimer of old positions
                gotoRowCol(10, 0);
                cout<<"                                     "<<endl;
                //new destination
                gotoRowCol(12,0);
                cout<<"Enter your move new(row): ";
                gotoRowCol(12,25);
                cin>>n_row;
                gotoRowCol(13,0);
                cout<<"Enter your move new(Column): ";
                gotoRowCol(13,28);
                cin>>n_col;
                //checking validity of new position(within the dimension of board)
                if(n_row<=dim && n_col<=dim && n_col>0 && n_col>0)
                {
                    //clearing invalid move disclaimer of new positions
                    gotoRowCol(15, 0);
                    cout<<"                                  "<<endl;
                    //displaying player1 character on board
                    write_on_board(A,o_row,o_col,n_row,n_col,dim,turn);
                }
                else
                {
                    // Invalid move disclaimer of new position
                    gotoRowCol(15,0);
                    cout<<"Invalid new position!"<<endl;
                    play_game(A,dim,turn);
                }
            }
            else
            {
                //Invalid move disclaimer of old position
                gotoRowCol(10,0);
                cout<<"Invalid old position!"<<endl;
                play_game(A,dim,turn);
            }
            turn_change(turn);
         }
         //Player2 & its main "if"
         if(turn==0)
         {
            gotoRowCol(20,0);
            cout<<"Player 2 (Small_characters)!"<<endl;
            gotoRowCol(22,0);
            cout<<"Enter your move old(row): ";
            gotoRowCol(22,25);
            cin>>o_row;
            gotoRowCol(23,0);
            cout<<"Enter your move old(Column): ";
            gotoRowCol(23,28);
            cin>>o_col;
            //checking validity of old position
            if (o_row<=dim && o_col<=dim && o_col>0 && o_col>0)
            {
                //clearing invalid move disclaimer of old positions
                gotoRowCol(25, 0);
                cout<<"                                      "<<endl;
                //new destination
                gotoRowCol(27,0);
                cout<<"Enter your move new(row): ";
                gotoRowCol(27,25);
                cin>>n_row;
                gotoRowCol(28,0);
                cout<<"Enter your move new(Column): ";
                gotoRowCol(28,28);
                cin>>n_col;
                //checking validity of new position
                if(n_row<=dim && n_col<=dim && n_col>0 && n_col>0)
                {
                    //clearing invalid move disclaimer of new positions
                    gotoRowCol(30, 0);
                    cout<<"                                       "<<endl;
                    //displaying player1 character on board
                    write_on_board(A,o_row,o_col,n_row,n_col,dim,turn);
                }
                else
                {
                    // Invalid move disclaimer of new position
                    gotoRowCol(30,0);
                    cout<<"Invalid new position!"<<endl;
                    play_game(A,dim,turn);
                }
            }
            else
            {
                // Invalid move disclaimer of old position
                gotoRowCol(25,0);
                cout<<"Invalid old position!"<<endl;
                play_game(A,dim,turn);
            }
            turn_change(turn);
        }
    }
}
//Demo Functions
//DF1
void print_demo_chess_board(int row, int col, char ch)
{
    cout<<" Demo Screen!     Demo Screen!     Demo Screen!      Demo Screen!     Demo Screen!     Demo Screen!     Demo Screen!      Demo Screen!     Demo Screen!     Demo Screen!"<<endl;
    cout<<endl;
    cout<<" Method:"<<endl;
    cout<<" To move a chess-piece, you need to enter the co-ordinates of the old position then the co-ordinates of new position."<<endl;
    cout<<" For example,"<<endl;
    cout<<" To move the Black Pawn(Capital_Character), you simply enter its current row and column then enter the new row and column."<<endl;
    cout<<" 1. If you want to select the Pawn present on 2ND row and 1ST column, just enter the row number and column number to select that specific pawn."<<endl;
    cout<<" 2. Then enter the new row and column such as 3RD row and 1ST column."<<endl;
    cout<<endl;
    cout<<"*****Remember!*****"<<endl;
    cout<<"Your move must be valid otherwise it would not move on the new position."<<endl;
    cout<<"*****Press Enter, to perform TUTORIAL!*****"<<endl;
    gotoRowCol(13,35);
    cout<<"Demo Board!     Demo Board!      Demo Board!     Demo Board!"<<endl;
    int dim=4;
    int initial_row=row;
    int initial_col=col;
    //horizontal loop
    for(int k=0;k<=dim+2;k++)
    {
        for(int i=col;i<=col+dim*15;i++)
        {
            gotoRowCol(row,i);
            cout<<ch;
        }
        cout<<endl;
        row+=5;
    }
    //changing character
    ch=176;
    //vertical loop
    for (int k=0;k<=dim+2;k++)
    {
        for (int j=initial_row;j<=initial_row+dim*8-2;j++)
        {
            gotoRowCol(j,initial_col);
            cout<<ch;
        }
        cout<<endl;
        initial_col+=10;
    }
}
//DF2
void generating_demo_array(char A[], int dim)
{
    for(int i=0;i<dim*dim;i++)
    {
        //Player1
        if(i==0 || i==5)
        {
            A[i]=rook1;//putting player 1 Character in array
        }
        else if(i==1)
        {
            A[i]=knight1;//putting player 1 Character in array
        }
        else if(i==2)
        {
            A[i]=king1;//putting player 1 Character in array
        }
        else if(i==3)
        {
            A[i]=queen1;//putting player 1 Character in array
        }
        else if(i==4)
        {
            A[i]=bishop1;//putting player 1 Character in array
        }
        else if(i>=6 && i<=11)
        {
            A[i]=pawn1;//putting player 1 Character in array
        }
        //Player2
        else if(i==30 || i==35)
        {
            A[i]=rook2;//putting player 2 Character in array
        }
        else if(i==31)
        {
            A[i]=knight2;//putting player 2 Character in array
        }
        else if(i==32)
        {
            A[i]=king2;//putting player 2 Character in array
        }
        else if(i==33)
        {
            A[i]=queen2;//putting player 2 Character in array
        }
        else if(i==34)
        {
            A[i]=bishop2;//putting player 2 Character in array
        }
        else if(i>=24 && i<=29)
        {
            A[i]=pawn2;//putting player 2 Character in array
        }
        else
        {
            A[i]=' ';//putting space remaining array
        }
    }
}
//DF3
void print_demo_array_board(char A[], int dim)
{
    int row=15,col=35;
    int initial_row=row;
    int initial_col=col;
    for (int i=0;i<dim*dim;i++)
    {
        gotoRowCol(row+2,col+4);
        cout<<A[i];
        sleep(1000);
        if(i%dim==dim-1 && i!=dim*dim-1)
        {
            cout<<endl;
            row+=5;
            col=initial_col;
        }
        else
        {
            col+=10;
        }
    }
}
//DF4
void print_demo_labels(int row, int col, int dim)
{
    //Printing column labels on top side(1, 2, 3, ..., 8)
    int col_label=1;
    for (int i=col;i<col+dim*10;i+=10)
    {
        gotoRowCol(row-1,i+5);
        cout<<col_label;
        col_label++;
    }
    //Printing row labels on left side(1, 2, 3, ..., 8)
    int row_label=1;
    for (int j=row;j<row+dim*5;j+=5)
    {
        gotoRowCol(j+3,col-3);
        cout<<row_label;
        row_label++;
    }
}
//AF2
void rules_of_chess()
{
    cout<<endl;
    cout<< "Chess Rules"<<endl;
    cout<<"Chess is an acronym for 'Chariot(rook), Horse( knight), Elephant(bishop) and Soldiers(pawns)'."<<endl;
    cout<<"-----------"<<endl;
    cout<<"1. Each player starts with 16 pieces: 1 king, 1 queen, 2 rooks, 2 knights, 2 bishops, and 8 pawns."<<endl;
    cout<<"2. The objective is to checkmate your opponent's king, meaning the king is in a position to be captured ('in check') and there's no way to escape the threat."<<endl;
    cout<<"3. The chessboard is an 8x8 grid. Rows are labeled 1 to 8, and columns are labeled 1 to 8."<<endl;
    cout<<"4. Each type of piece moves in a specific way:"<<endl;
    cout<<"   - King: 1 box in any direction."<<endl;
    cout<<"   - Queen: Any number of boxes, but remember Queen can move diagonally and vertically or horizontally."<<endl;
    cout<<"   - Rook: Any number of boxes vertically or horizontally."<<endl;
    cout<<"   - Bishop: Any number of boxes diagonally."<<endl;
    cout<<"   - Knight: Moves in an L-shape (two boxes in one direction and one box perpendicular)."<<endl;
    cout<<"   - Pawn: It is capable of moving 1 or 2 boxes for the very first move, then moves one box forward only, and captures diagonally."<<endl;
    cout<<"5. Pawns can be promoted to any other piece upon reaching the opponent's back rank."<<endl;
    cout<<"6. Castling is a special move involving the king and a rook, under certain conditions."<<endl;
    cout<<"7. En passant is a pawn capture that can occur under specific circumstances."<<endl;
    cout<<"8. Stalemate occurs when a player has no legal moves but is not in check, resulting in a draw."<<endl;
    cout<<"9. Fifty-move rule and threefold repetition are draw conditions as well."<<endl;
    cout<<"10. The game is turn-based, and players alternate making moves."<<endl;
    cout<<endl;
    cout<<"Enjoy the game!"<<endl;
}
//AF3
void privacy_and_legal_info()
{
    system("cls");
    cout << "******Privacy & Legal Information******" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Welcome to Chess by Tencent Games Studio. Before you proceed," << endl;
    cout << "please take a moment to review our Privacy & Legal Information." << endl << endl;
    cout << "1. Collection of Information:" << endl;
    cout << "   We collect minimal data required for gameplay analytics." << endl;
    cout << "   No personal information is shared without your consent." << endl << endl;
    cout << "2. Intellectual Property:" << endl;
    cout << "   This game is protected by international copyright laws." << endl;
    cout << "   Unauthorized reproduction or distribution is prohibited." << endl << endl;
    cout << "3. User Conduct:" << endl;
    cout << "   Respect other players. Offensive behavior may result in" << endl;
    cout << "   suspension of your account. Let's keep the game enjoyable for all!" << endl << endl;
    cout << "4. Contact Us:" << endl;
    cout << "   If you have any questions or concerns, please contact:" << endl;
    cout << "    Tencent games studio:" << endl;
    cout << "    Address: Hasilpur, Punjab, Pakistan" << endl;
    cout << "    Email: usman@tencentgames.com" << endl;
    cout << "-------------------------------------------------------" << endl;
}
//AF4 (Player 1 Castling)
void player_1_castling(char A[],int dim,int old_position,int new_position,bool turn)
{
            //Check for king-side castling
            if(old_position==4 && new_position == 6)
            {
                if (A[5] == '-' && A[6] == '-' && A[7] == 'R' && A[4] == 'K')
                {
                    //Perform castling
                    A[6] = A[old_position];
                    A[old_position] = '-';
                    A[5] = A[7];
                    A[7] = '-';
                    //Updating array
                    array_board(A, dim);
                    //return true;
                }
                else
                {
                    play_game(A, dim, turn);
                  //  return false;
                }
            }
            //Check for queen-side castling
            else if (old_position==4 && new_position==2)
            {
                if (A[1] == '-' && A[2] == '-' && A[3] == '-' && A[0] == 'R' && A[4] == 'K')
                {
                    //Perform castling
                    A[2] = A[old_position];
                    A[old_position] = '-';
                    A[3] = A[0];
                    A[0] = '-';
                    //Updating array
                    array_board(A, dim);
                  //  return true;
                }
                else
                {
                    play_game(A, dim, turn);
                  //  return false;
                }
            }
}
//AF5 (Player 2 Castling)
void player_2_castling(char A[],int dim,int old_position,int new_position,bool turn)
{
            //Check for king-side castling
            if(old_position==60 && new_position == 62)
            {
                if (A[61] == '-' && A[62] == '-' && A[63] == 'r' && A[60] == 'k')
                {
                    //Perform castling
                    A[62] = A[old_position];
                    A[old_position] = '-';
                    A[61] = A[63];
                    A[63] = '-';
                    //Updating array
                    array_board(A, dim);
                    //return true;
                }
                else
                {
                    play_game(A, dim, turn);
                  //  return false;
                }
            }
            //Check for queen-side castling
            else if (old_position==60 && new_position==58)
            {
                if (A[59] == '-' && A[58] == '-' && A[57] == '-' && A[56] == 'r' && A[60] == 'k')
                {
                    //Perform castling
                    A[58] = A[old_position];
                    A[old_position] = '-';
                    A[59] = A[56];
                    A[56] = '-';
                    //Updating array
                    array_board(A, dim);
                  //  return true;
                }
                else
                {
                    play_game(A, dim, turn);
                  //  return false;
                }
            }
}
int main()
{
    //Showing Welcome Screen
    int play;
    cout<<"Welcome to the Chess-game developed by Tencent Games Studio."<<endl;
    cout<<"Please take a quick look at the rules before you start playing."<<endl;
    cout<<endl;
    cout<<"******Game Menu******"<<endl;
    cout<<"   1. Start"<<endl;
    cout<<"   2. Learn rules"<<endl;
    cout<<"   3. How to play (demo)"<<endl;
    cout<<"   4. Load/Save"<<endl;
    cout<<"   5. Privacy & Legal"<<endl;
    cout<<"   6. Exit"<<endl;
    cout<<endl;
    cout<<"Enter your choice:";
    cin>>play;
    int row=5,col=45,dim=8;
    char A[dim*dim];
    bool turn=0;
    char ch=178;
    //Code
    if(play==1)
    {
        system("cls");
        cout<<"Starting........."<<endl;
        sleep(15000);
        system("cls");
        gotoRowCol(1,49);
        cout<<"This is Chess -v7.24.2.9F (version)Quantum Edition by UG manufactures Inc."<<endl;
        print_game_board(row,col,ch,dim);//1F
        print_box_space_for_players(row,col,ch);//3F
        only_generating_array(A,dim);//4F
        array_board(A,dim);//5F
        play_game(A,dim,turn);//9F
    }
    //rules of chess
    else if(play==2)
    {
        rules_of_chess();
    }
    else if(play==3)
    {
        //Showing demo screen
        system("cls");
        int row=15,col=35,dim=6;
        char demo=219;
        print_demo_chess_board(row,col,demo);
        print_demo_labels(row,col,dim);
        char A[dim*dim];
        generating_demo_array(A,dim);
        print_demo_array_board(A,dim);
        getch();
        //Loops for understanding of movement (e.g. Pawn)
        for(int f=col;f>=col-8;f--)
        {
            //Clearing old position dynamically in demo
            gotoRowCol(22,39);
            cout<<" "<<endl;
            //updating to new position
            demo=178;
            gotoRowCol(22,f);
            cout<<"P"<<endl;
            sleep(3000);
            gotoRowCol(22,f);
            cout<<" "<<endl;
            sleep(3000);
        }
        row=22;
        for(int u=row;u<=row+5;u++)
        {
            demo=176;
            gotoRowCol(u,26);
            cout<<"P"<<endl;
            sleep(3000);
            gotoRowCol(u,26);
            cout<<" "<<endl;
            sleep(3000);
        }
        for(int g=col-8;g<=col;g++)
        {
            demo=178;
            gotoRowCol(27,g);
            cout<<"P"<<endl;
            sleep(3000);
            gotoRowCol(27,g);
            cout<<" "<<endl;
            sleep(3000);
        }
        //printing Pawn on the new position
            gotoRowCol(27,39);
            cout<<"P"<<endl;
            getch();
    }
    //loading saved game
    else if(play==4)
    {
        system("cls");
        cout<<endl;
        cout<<"Loading........."<<endl;
        sleep(15000);
        system("cls");
        reading_saved_game(A,dim,turn);//loading saved game
        print_game_board(row,col,ch,dim);//1F
        print_box_space_for_players(row,col,ch);//3F
        array_board(A,dim);//5F
        play_game(A,dim,turn);//9F
    }
    else if(play==5)
    {
        //Privacy & Legal
        privacy_and_legal_info();

    }
    else if(play==6)
    {
        system("cls");
        cout<<"Thank you!, Good bye!"<<endl;
    }
    return 0;
}
