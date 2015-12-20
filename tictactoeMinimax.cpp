////////////////////////InDominous X:  Beat it if you can!!


#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<time.h>

int CheckEmpty(int b[9],int pos);				//Check if position is empty
int CheckWin(int b[9]);						//Check if position is winning
int CheckLose(int b[9]);					//Check if position is losing
int CheckDraw(int b[9]);					//Check if position is draw
int CheckStatus(int b[9]);					//Check status of the board(win/lose/draw)
int CheckLegal(int b[9],int s);					//Check if move is legal(legal if inside the bounds(0-8) and position is empty)
int AiMove(int b[9]);						//returns the maximum score for a AIMove
int HumanMove(int b[9]);					//returns the minimum score for a HumanMove
void DisplayBoard(int b[9]);					//Displays the board
int MiniMax(int b[9]);						//Most important function: Gives the position for AI to place X


int a[9]={0,0,0,0,0,0,0,0,0};

int move=0;


////////1=O(Player)  2=X(AI)


void main()
{
	clrscr();
			 int pos;
			 char choice;
			 int legal;
			 
			 cout<<"Do You Want Me to Start?\nChoice(y/n):";					//Who plays the first move?
			 cin>>choice;

			 DisplayBoard(a);

			 switch(choice)
			 {

				case 'y':
					{

						while(move<5)			//First one to move would make a maximum of 5 moves
						{

								pos=MiniMax(a);
								a[pos]=2;
								DisplayBoard(a);
								
								if(CheckWin(a))
									{
										DisplayBoard(a);
										cout<<"\n\nYou lost!";
										delay(5000);
										break;
									}
								else if(CheckDraw(a))
									{
										DisplayBoard(a);
										cout<<"\n\nIts Draw!";
										delay(5000);
										break;
									}

								enterAgain1:
								cout<<"\n\nEnter position(0-8):";
								cin>>pos;
								legal=CheckLegal(a,pos);
								
								if(legal==0)
									{
										cout<<"\nInvalid Move!";
										goto enterAgain1;
									}
								a[pos]=1;

								DisplayBoard(a);
								
								if(CheckLose(a))
									{
										DisplayBoard(a);
										cout<<"\n\nYou won!";
										delay(5000);
										break;
									}
								else if(CheckDraw(a))
									{
										DisplayBoard(a);
										cout<<"\n\nIts Draw!";
										delay(5000);
										break;
									}
											
								move++;
						}

							break;
					}


				case 'n':
					{

						while(move<5)
						{

							DisplayBoard(a);

							enterAgain2:
							cout<<"\n\nEnter position(0-8):";
							cin>>pos;

							legal=CheckLegal(a,pos);
							if(legal==0)
							{
								cout<<"\nInvalid Move!";
								goto enterAgain2;
							}

							a[pos]=1;

							DisplayBoard(a);

							if(CheckLose(a))
							{
								DisplayBoard(a);
								cout<<"\n\nYou won!";
								delay(5000);
								break;
							}
							else if(CheckDraw(a))
							{
								DisplayBoard(a);
								cout<<"\n\nIts Draw!";
								delay(5000);
								break;
							}


							pos=MiniMax(a);
							a[pos]=2;
							cout<<"\n\t"<<pos;
							DisplayBoard(a);

							if(CheckWin(a))
							{
								DisplayBoard(a);
								cout<<"\n\nYou lost!";
								delay(5000);
								break;
							}
							else if(CheckDraw(a))
							{
								DisplayBoard(a);
								cout<<"\n\nIts Draw!";
								delay(5000);
								break;
							}

																													
							move++;
						}


						break;
					}
					
				default:
					{
						break;
					}

			 }


}
			




//Minimax

int MiniMax(int b[9])							
{														//MINimize MAXimum Loss

	int bestMove[9];						//maximum 9 possible moves				
	int moveVal;
	int bestMoveVal=-10;                
	int index=0;							//for random bestMove(if more than 1 bestMoves exist)
	randomize();							//random number initialising

	for(int p=0;p<9;p++)
	{
		if(CheckEmpty(b,p))
		{
			b[p]=2;

			moveVal=HumanMove(b);
			
			if(moveVal > bestMoveVal)       
			{
				bestMoveVal = moveVal;
				index=0;
				bestMove[index]=p;

			}
			else if(moveVal == bestMoveVal)       
			{
				bestMoveVal = moveVal;
				bestMove[++index]=p;
				
			}

			b[p]=0;
		}

	}

		if(index>0)									//Select a random move 
		{
			index = rand() % index;						
		}

	cout<<"\nI am considering:"<<bestMove[index];
	delay(1000);
	return bestMove[index];
}



//AI move    MAX      X=2
int AiMove(int b[9])										//returns MAXIMUM of scores for a move
{
	int bestValue=(-100);        			
	int stateValue=CheckStatus(b);

	
	if(stateValue!=20)         					 
	{
		if(stateValue==1)
		{stateValue=(10);}
		else if(stateValue==(-1))
		{stateValue=(-10);}

		return stateValue;
	}
	

	for(int j=0;j<9;j++)
	{
		if(CheckEmpty(b,j))
		{
			b[j]=2;
			
			int val=HumanMove(b);
			
			if (val >= bestValue)  		
			{
				bestValue = val;
			}

			b[j]=0;
			
			
		}
	}

	return bestValue;
}


//Human move     MIN    O=1
int HumanMove(int b[9])									//returns MINIMUM of the scores for a move 
{
	int bestValue=100;                        
	int stateValue=CheckStatus(b);

	
	if(stateValue!=20)       			 		
	{
		if(stateValue==1)
		{stateValue=(10);}
		else if(stateValue==(-1))
		{stateValue=(-10);}

		return stateValue;
	}
	

	for(int k=0;k<9;k++)
	{
		if(CheckEmpty(b,k))
		{
			b[k]=1;
			//delay(500);
			int val=AiMove(b);

			if (val <= bestValue)  				
			{
				bestValue = val;
			}

			b[k]=0;
		}
	}

	return bestValue;
}





int CheckEmpty(int b[9],int pos)										//return 1 if empty     else 0
{
	if(b[pos]==0)
	{
		return 1;
	}

	return 0;
}




int CheckWin(int b[9])													//Relative to X(AI)  //return 1 for win   else 0
{
																					//For Rows
	if(b[0]==2 && b[1]==2 && b[2]==2)
	{
		return 1;
	}
	else if(b[3]==2 && b[4]==2 && b[5]==2)
	{
		return 1;
	}
	else if(b[6]==2 && b[7]==2 && b[8]==2)
	{
		return 1;
	}

																					//For Columns
	else if(b[0]==2 && b[3]==2 && b[6]==2)
	{
		return 1;
	}
	else if(b[1]==2 && b[4]==2 && b[7]==2)
	{
		return 1;
	}
	else if(b[2]==2 && b[5]==2 && b[8]==2)
	{
		return 1;
	}
																					//For Diagonals

	else if(b[0]==2 && b[4]==2 && b[8]==2)
	{
		return 1;
	}
	else if(b[2]==2 && b[4]==2 && b[6]==2)
	{
		return 1;
	}


return 0;
}







int CheckLose(int b[9])											//Relative to X(AI)  //return -1 for lose    else 0
{

																					//For Rows
	if(b[0]==1 && b[1]==1 && b[2]==1)
	{
		return -1;
	}
	else if(b[3]==1 && b[4]==1 && b[5]==1)
	{
		return -1;
	}
	else if(b[6]==1 && b[7]==1 && b[8]==1)
	{
		return -1;
	}

																					//For Columns
	else if(b[0]==1 && b[3]==1 && b[6]==1)
	{
		return -1;
	}
	else if(b[1]==1 && b[4]==1 && b[7]==1)
	{
		return -1;
	}
	else if(b[2]==1 && b[5]==1 && b[8]==1)
	{
		return -1;
	}
																					//For Diagonals

	else if(b[0]==1 && b[4]==1 && b[8]==1)
	{
		return -1;
	}
	else if(b[2]==1 && b[4]==1 && b[6]==1)
	{
		return -1;
	}


return 0;
}




int CheckDraw(int b[9])														//return 1 for draw     else 0
{
	for(int i=0;i<9;i++)
	{
		if(b[i]==0)
		{
			return 0;
		}
	}

	return 1;
}


int CheckStatus(int b[9])
{
	int status;

	status=CheckWin(b);
	if(status==1)
		{
			return 1;
		}

	status=CheckLose(b);
	if(status==(-1))
		{
			return -1;
		}

	status=CheckDraw(b);
	if(status==1)
		{
			return 0;
		}

	return 20;
}



void DisplayBoard(int b[9])
{
	clrscr();

	for(int i=0;i<9;i++)
	{
		if(b[i]==1)
			{
				cout<<"O";
			}
		else if(b[i]==2)
			{
				cout<<"X";
			}
		else if(b[i]==0)
			{
				cout<<" ";
			}

		if(i==0 || i==1 || i==3 || i==4 || i==6 || i==7)
		{
			cout<<" | ";
		}

		if(i==2 || i==5)
		{
			cout<<"\n----------\n";
		}
	}

}



int CheckLegal(int b[9],int s)										//return 1 if legal move
{
	if(b[s]==0 && s<9 && s>=0)
	{
		return 1;
	}

	return 0;
}


