/***********PROJECT DESCRIPTION****************
***********************************************
**                                           **
** PROJECT NAME : BRICK GAME			     **
** PROGRAMMED BY: MUHAMMAD TASNIM MOHIUDDIN  **
** STUDENT NO : 0805115				         **
** DEPARTMENT : CSE						     **
** SUPERVISOR : SAYED ISTIAQUE AHMED		 **
**                                           **
***********************************************
***********************************************/


#include "iGraphics.h"
#include<string.h>
#include<shellapi.h>

#define ROW 20
#define COLM 10
#define BrickRow 4
#define BrickColm 4
#define BrickSize 25
#define ChoiceNum 8
#define ON 1
#define OFF 0

/********************FUNCTION PROTOTYPES**************************************************************/ 

void rotate();
void move_down();
void draw_board();
int check_move();
void del();
void vanish(int);
void create_score(char *,int);
void show_score();


/********************* GLOBAL VARIABLES *****************************************************************/

int h=0,m=0,s=0;
int len;
char ch1[2],ch2[2],cm1[2],cm2[2],cs1[2],cs2[2];
int cx=COLM/3, cy=ROW-3, toss, STATE=ON, Game=ON, score=0, Page=0, Pause=1, bip=1,ni=0;
char s_score[20], name[20];
int board[ROW][COLM] ,crnt_brick[BrickRow][BrickColm],next_brick[BrickRow][BrickColm];
struct{
	char name[40];
	int scr;
}t_h_scr, h_scr[6];


/******************* BRICKS OF DIFFERENT SHAPES **********************************************************/

int rand_choice[ChoiceNum][BrickRow][BrickColm]=
{
	/*shape 1: 
				  ****
						           */
	{
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}         
	},
	
	/*shape 2:       
					 *
					***
						            */
	
	{ 
		{0,0,0,0},
		{0,0,2,0},
		{0,2,2,2},
		{0,0,0,0}  
	},

	/*shape 3: 
				   *
				   *
				   **
									*/
	
	{ 
		{0,0,3,0},
		{0,0,3,0},
		{0,0,3,3},
		{0,0,0,0} 
	},

	/*shape 4: 
				  **
				  **
									*/

	{ 
		{0,0,0,0},
		{0,4,4,0},
		{0,4,4,0},
		{0,0,0,0}        
	},

	/*shape 5: 
				  *
				  **
				   *
									*/
	{ 
		{0,5,0,0},
		{0,5,5,0},
		{0,0,5,0},
		{0,0,0,0}        
	},

	/*shape 6: 
				*
				*
			   **
									*/

	{ 
		{0,0,6,0},
		{0,0,6,0},
		{0,6,6,0},
		{0,0,0,0}   
    },

	/*shape 7: 
				
				*
			   **
			   *
									*/

	{ 
		{0,0,7,0},
		{0,7,7,0},
		{0,7,0,0},
		{0,0,0,0} 
	},

	/*shape 8: 
				*
				*
				*
				*
									*/

	{ 
		{0,8,0,0},
		{0,8,0,0},
		{0,8,0,0},
		{0,8,0,0} 
	}
};




void iDraw()
{
	iClear();
	if(Page == 0){
		iShowBMP(0,0,"images/begin.bmp");    //starting page
			
	}
	if(Page == 1)
	{		
		iShowBMP(0,0,"images/main menu.bmp");     //main menu page
	}
	if(Page == 11)
	{
		iShowBMP(0,0,"images/play4.bmp");         //playing page         
			draw_board();
		
	}
	if(Page == 111)
	{		
		iShowBMP(0,0,"images/game over.bmp");     // game over page 
	}
	if(Page == 12)
	{		
		iShowBMP(0,0,"images/score.bmp");     //high score page
			show_score();
	}
	if(Page == 13)
	{		
		iShowBMP(0,0,"images/help 1.bmp");
	}
	if(Page == 131)							  //help pages
	{		
		iShowBMP(0,0,"images/help 2.bmp");
	}
	if(Page == 14)
	{		
		iShowBMP(0,0,"images/credit.bmp");        //credits page     
	}
	if(Page == 15)
	{		
		iShowBMP(0,0,"images/contact1.bmp");         //contact page
	}





}

void iMouseMove(int mx, int my)
{
	iClear();
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(Page==0){
			if(mx >= 100 && mx <= 650 && my >= 50 && my <= 120){  //main menu page
					Page=1;
					PlaySound("sounds\\enter.wav", NULL, SND_ASYNC);
			}
		
		}
		else if(Page==1)
		{
		   	if(mx >= 280 && mx <= 480 && my >= 425 && my <= 475)  //playing page   
			{
				Page = 11;
				PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
				cx = COLM/3, cy = ROW - 3;
				for(int i =0;i<ROW;i++)
				{
					for(int j =0;j<COLM;j++)
						board[i][j] = 0;
				}
				STATE = ON;
				Game = ON;
				Pause = 1;
				score=0;
			
			}
		  else	if(mx >= 280 && mx <= 480 && my >= 360 && my <= 410)  //high score page
			{
				PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
				Page = 12;
			}
		  else	if(mx >= 280 && mx <= 480 && my >= 275 && my <= 335)  //help page
			{
				PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
				Page = 13;
			}
		  else	if(mx >=280 && mx <= 480 && my >= 190 && my <=250)   //credits page 
			{
				 PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
				Page = 14;
			}
		  else	if(mx >= 280 && mx <= 480 && my >= 125 && my <= 180) //contact page
			{
				PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
				Page = 15;
			}
		   else	if(mx >= 280 && mx <= 480 && my >= 50 && my <= 110)  //exit
			{
			   	exit(0);
			}
		}
		
		//***** RETURNING TO PREVIOUS PAGE *****************//
		
		if(Page==12){
			if(mx >=90 && mx <=200 && my >= 60 && my <= 110){
					Page=1;
			PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
	}

		if(Page==13){
			if(mx >= 90 && mx <= 210 && my >= 60 && my <= 120){
					Page=1;
					PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
			else if(mx >= 600 && mx <= 740 && my >= 60 && my <= 100){
						Page=131;
						PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
			
		}
		if(Page==131){
			if(mx >= 300 && mx <=440 && my >= 60 && my <= 110){
					Page=13;
					PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
	}
		if(Page==14){
			if(mx >= 90 && mx <=200 && my >= 60 && my <= 110){
					Page=1;
					PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
	}
		if(Page==15){
			if(mx >=110 && mx <=220 && my >= 60 && my <= 130){
					Page=1;
					PlaySound("sounds\\button.wav", NULL, SND_ASYNC);
			}
	}
		
		if(Page==11){
			if(mx >=600 && mx <=720 && my >= 50 && my <= 110){
				Page=1;
				PlaySound("sounds\\losegame.wav", NULL, SND_ASYNC);
			}
	}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	
	}
}

void iKeyboard(unsigned char key)
{
	//***** RETURNING TO PREVIOUS PAGE *****************//
	
	if(key == 27)    //if "ESC" is pressed
	{
		if(Page == 11)
			Page = 1;
		else if(Page == 12)
			Page = 1;
		else if(Page == 13)
			Page = 1;
		else if(Page == 131)
			Page = 13;
		else if(Page == 14)
			Page = 1;
		else if(Page == 15)
			Page = 1;
		else if(Page == 1)
			exit(1);
		
	}
	if(Page == 11)
	{
		if(key == 'p')        
			iPauseTimer(0);    //pausing the game
		if(key == 'r')			
			iResumeTimer(0);   //resuming the game
	}

	 if(Page == 11 && Game == OFF && bip >10) // conditions for name entry
	{
		if(key != '\r')         // if 'ENTER' is not pressed
		{
			
			name[len] = key;
			len++;
			}
		else
		{
			create_score(name,score);
			Page = 12;                //showing the high score page
			STATE = OFF;
			ni = 0;
			name[ni] = 0;
			for(int i =0;i<ROW;i++)
			{
				for(int j =0;j<COLM;j++)
					board[i][j] = 0;
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	if(Pause == 1)
	{
		if(key == GLUT_KEY_UP)       //rotating the brick
		{
			if(STATE == ON)
			{
				rotate();
			}
		}
		if(key == GLUT_KEY_LEFT)     //moving the brick to left
		{
			if(STATE == ON)
			{
				cx--;
				if(!check_move())    //if not possible
					cx++;
			}
		}
		if(key == GLUT_KEY_RIGHT)   //moving the brick to right
		{
			if(STATE == ON)
			{
				cx++;
				if(!check_move())     //if not possible
					cx--;
			}
		}
		if(key == GLUT_KEY_DOWN)    // falling the brick faster
		{
			if(STATE == ON)
			{
				cy--;
				if(!check_move())    //if not possible
					cy++;
			}
		}
	}
	
	
}

/******************************************* DRAWING THE BOARD *******************************************************/

void draw_board(void)
{
	int i,j;
	char str[50];
	sprintf(str,"%d",score);    //saving the score in str
	iSetColor(0,0,255);
	iText(690,480,str,GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(255,255,0);
	iFilledRectangle(245,30,5,502);
	iFilledRectangle(501,30,5,502);   //drawing the frame of the board
	iFilledRectangle(245,530,261,5);
	iFilledRectangle(245,26,261,5);

/********************************* drawing the next brick *******************************************************/

    for(i=0;i<BrickRow;i++)										
	{
		for(j=0;j<BrickColm;j++)
		{
			if(next_brick[i][j])
			{

				if(next_brick[i][j]==1)
					iSetColor(100,100,200 );
				else if(next_brick[i][j]==2)
					iSetColor(255,0,0);
				else if(next_brick[i][j]==3)
					iSetColor(0.28,252.87,153.43);
				else if(next_brick[i][j]==4)
					iSetColor(252.45,0.5,153.69);
				else if(next_brick[i][j]==5)
					iSetColor(153.98,252.16,0.3);
				else if(next_brick[i][j]==6)
					iSetColor(100.48,251.26,190.88);
				else if(next_brick[i][j]==7)
					iSetColor(0.6,0.2,254.4);
				else if(next_brick[i][j]==8)
					iSetColor(200.8,100.2,132.6);
				iFilledRectangle(600+j*BrickSize,280+i*BrickSize,BrickSize,BrickSize);//drawing the bricks
				iSetColor(0.7,0.7,0.7);
				iRectangle(600+j*BrickSize,280+i*BrickSize,BrickSize,BrickSize);
			}
				
		}
	}

/****************************** drawing the falling brick on board **************************************************/

	for(i=0;i<BrickRow;i++)        
	{
		for(j=0;j<BrickColm;j++)
		{
			if(crnt_brick[i][j]!=0)
			{
				if(crnt_brick[i][j]==1)
					iSetColor(100,100,200 );
				else if(crnt_brick[i][j]==2)
					iSetColor(255,0,0);
				else if(crnt_brick[i][j]==3)
					iSetColor(0.28,252.87,153.43);
				else if(crnt_brick[i][j]==4)
					iSetColor(252.45,0.5,153.69);
				else if(crnt_brick[i][j]==5)
					iSetColor(153.98,252.16,0.3);
				else if(crnt_brick[i][j]==6)
					iSetColor(100.48,251.26,190.88);
				else if(crnt_brick[i][j]==7)
					iSetColor(0.6,0.2,254.4);
				else if(crnt_brick[i][j]==8)
					iSetColor(200.8,100.2,132.6);
				
				iFilledRectangle((cx+j)*BrickSize+250,(cy+i)*BrickSize+31,BrickSize,BrickSize);//drawing the bricks

				iSetColor(0.7,0.7,0.7);
				iRectangle((cx+j)*BrickSize+250,(cy+i)*BrickSize+31,BrickSize,BrickSize);
			}
			
		}
	}

/******************** drawing the brick on board when it is stabled *******************************************/

	
	for(i=0;i<ROW;i++)                                       
	{
		for(j=0;j<COLM;j++)
		{
			if(board[i][j]!=0)
			{
				if(board[i][j]==1)
					iSetColor(100,100,200 );
				else if(board[i][j]==2)
						iSetColor(255,0,0);
				else if(board[i][j]==3)
					iSetColor(0.28,252.87,153.43);
				else if(board[i][j]==4)
					iSetColor(252.45,0.5,153.69);
				else if(board[i][j]==5)
					iSetColor(153.98,252.16,0.3);
				else if(board[i][j]==6)
					iSetColor(100.48,251.26,190.88);
				else if(board[i][j]==7)
					iSetColor(0.6,0.2,254.4);
				else if(board[i][j]==8)
					iSetColor(200.8,100.2,132.6);
				
				iFilledRectangle(j*BrickSize+250,i*BrickSize+31,BrickSize,BrickSize);//drawing the bricks

				iSetColor(0.7,0.7,0.7);
				iRectangle(j*BrickSize+250,i*BrickSize+31,BrickSize,BrickSize);
			}
		}
	}
	
	if(Game==OFF)
	{
		if(bip<10)
		{
			PlaySound("sounds\\bomb.wav", NULL, SND_ASYNC);
			iShowBMP(0,0,"images/game over.BMP");		//showing game over page
			iSetColor(254,254,254);
		    iText(580,140,str,GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else 
		{	
			iShowBMP(0,0,"images/game over 2.BMP");
			iSetColor(0,0,250);
			iText(490,140,name,GLUT_BITMAP_HELVETICA_18);
		}
	

	}

/**************************************** SHOWING TIME ON SCREEN *******************************************************/

    iSetColor(255,0,0);
	sprintf(ch1,"%d",h/10);
	sprintf(ch2,"%d",h%10);
	sprintf(cm1,"%d",m/10);
	sprintf(cm2,"%d",m%10);
	sprintf(cs1,"%d",s/10);
	sprintf(cs2,"%d",s%10);

	iText(650,535,ch1,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(662,535,ch2,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(674,535,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(686,535,cm1,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(698,535,cm2,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(710,535,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(722,535,cs1,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(734,535,cs2,GLUT_BITMAP_TIMES_ROMAN_24);




}

/********************************************* ROTATING BRICK 90 DEGREE CLOCKWISE*************************************/

void rotate(void)
{
	int i,j,k,l,temp[BrickRow][BrickColm];
	for(i=0;i<BrickRow;i++)
	{
		l=BrickRow-i-1;
		for(j=0;j<BrickColm;j++)                   //1st row of cur brick becomes last col in temp,
		{											//2nd row of cur brick becomes 3rd col in temp,
			k=j;									//3rd row of cur brick becomes 2nd col in temp,				
			temp[k][l] = crnt_brick[i][j];			//last row of cur brick becomes 1st col in temp,
		}
	}
	for(i=0;i<BrickRow;i++)
	{
		for(j=0;j<BrickColm;j++)
		{
			crnt_brick[i][j]=temp[i][j];           //copying temp in cur brick 
		}
	}
	if(!check_move())           //if rotation is not valid than make it as earlier by rotating 90 degree anticlockwise
	{
		for(i=0;i<BrickRow;i++)
		{
			l=i;
			for(j=0;j<BrickColm;j++)
			{
				k=BrickColm-j-1;
				temp[k][l] = crnt_brick[i][j];
			}
		}
		for(i=0;i<BrickRow;i++)
		{
			for(j=0;j<BrickColm;j++)
			{
				crnt_brick[i][j]=temp[i][j];
			}
		}
	}
}

/********************************************* DROPPING THE BRICK ********************************************************/

void move_down(void)
{
	int i, j;
	if(Pause == 1)
	{
		if(STATE == ON)
		{
			cy--;
			if(!check_move())       //when the down movement is not possible then go to state off
			{
				cy++;
				STATE = OFF;
			}
		}

		if(STATE == OFF)
		{
			for(i=0;i<BrickRow;i++)
			{
				for(j=0;j<BrickColm;j++)
				{
					if(crnt_brick[i][j])
					{
						board[cy+i][cx+j] = crnt_brick[i][j];   //saving the current brick position on the board
					}
				}
			}
			
			del();
			
			for(j=0;j<COLM;j++)
			{
				if(board[ROW-1][j])   // if brick in uppermost row
				{
					Game = OFF;
					ni = 0;
					bip = 0;
					Pause = 7;
					create_score(name,score);
					return;
				}
			}
	
			toss = rand() % ChoiceNum;                       //chosing  bricks randomly
			for(i=0;i<BrickRow;i++)
			{
				for(j=0;j<BrickColm;j++)
				{
					crnt_brick[i][j] = next_brick[i][j];     //getting the next brick into the current brick
				}
			}
			
			for(i=0;i<BrickRow;i++)
			{
				for(j=0;j<BrickColm;j++)
				{
					next_brick[i][j] = rand_choice[toss][i][j];//getting the newly chosen brick into next brick
				}
			}
			cx=COLM/3, 
			cy=ROW-3;                              
			STATE = ON;                                        //getting the state on
		}
	}
	bip += 1;
}

/******************************************* COUNTING TIME **************************************************************/

void sec()
{

	s++;
	if(s==60) s=0;  

}


void miin()
{

	m++;
	if(m==60) m=0;

}

void hour()
{

	h++;
}

/*********************************** CHECKING WHETHER MOVING OR ROTATING IS POSSIBLE ****************************************/

int check_move(void)               
{
	int i, j;
	for(i=0;i<BrickRow;i++)
	{
		for(j=0;j<BrickColm;j++)
		{
			if(crnt_brick[i][j])
			{
				if(cx+j<0)
					return 0;
				else if(cx+j>COLM-1)
					return 0;
				else if(cy+i<0)
					return 0;
				else if(board[cy+i][cx+j])   //if that position is filled up
					return 0;
			}
		}
	}
	return 1;
}

/******************************** DELETING A FILLED LINE AND SCORING **************************************************************/

void del()
{
	int count, i, j ,line_counter=0;
	for(i=0;i<ROW;i++)
	{
		count=0;
		for(j=0;j<COLM;j++)
		{
			if(board[i][j])
			{
				count++;
			}
		}
		if(!count)           // if there is no brick in a row means above that row is empty
		{
			break;
		}
		if(count==COLM)     //if row is filled up
		{
			vanish(i);
			
			score +=100;
			if(line_counter==1) // if 2 consecutive lines vanish BONUS 150
				score+=150;
			if(line_counter==2) // if 3 consecutive lines vanish BONUS 250
				score += 250;
			if(line_counter==3) // if 4 consecutive lines vanish BONUS 400
				score += 400;
			line_counter++;
		    i--;             //decrimenting i because that line we counted is vanished
			PlaySound("sounds\\wow.wav", NULL, SND_ASYNC);              
		}
	}
}


void vanish(int i)
{
	int count, j;
	for(;i<ROW;i++)
	{
		count=0;
		for(j=0;j<COLM;j++)
		{
			board[i][j]=board[i+1][j];   //each brick above row i is downing by 1 row
			if(board[i+1][j]!=0)
				count++;

		} 
		if(!count)          // if there is no brick in a row means above that row is empty
		{
			break;
		}
	}
}

/**************************** SAVING HIGH SCORES ***************************************************/

void create_score(char *new_name,int scr)
{
	FILE *fp;
	int i;
	fp = fopen("High Score.txt","r");
	for(i=0;i<6;i++)
		fscanf(fp,"%s %d",h_scr[i].name,&h_scr[i].scr);
	fclose(fp);
	if(h_scr[5].scr<scr)
	{	
		fp = fopen("High Score.txt","w");
		
		for(i=0;i<6;i++)
		{
			if(h_scr[i].scr<scr)
			{
				break;
			}
		}
		for(int j=0;j<5-i;j++)
		{
			h_scr[5-j] = h_scr[5-j-1]; 
		}
		strcpy(h_scr[5-j].name,new_name);
		h_scr[5-j].scr = scr;
		for(i=0;i<6;i++)
		{
			fprintf(fp,"%s\n %d\n",h_scr[i].name,h_scr[i].scr);
		}
		fclose(fp);
	}
}

/************************* SHOWING HIGH SCORE ****************************************************/

void show_score()
{
	FILE *fp;
	int i;
	char cur_scr[20];
	fp = fopen("High Score.txt","r");
	for(i=0;i<6;i++){
		fscanf(fp,"%s %d",h_scr[i].name,&h_scr[i].scr);
		sprintf(cur_scr,"%d",h_scr[i].scr);              //saving h_scr[i].scr in string cur_scr
		iSetColor(255,255,255);
		iText(270, 420-60*i,h_scr[i].name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(520, 420-60*i,cur_scr,GLUT_BITMAP_TIMES_ROMAN_24);
	fclose(fp);
	}

}

/******************************** main() function *******************************************/

int main()
{
	int i, j, toss;
	toss = rand() % ChoiceNum;  //randomly brick chosen
	for(i=0;i<BrickRow;i++)
	{
		for(j=0;j<BrickColm;j++)
		{
			next_brick[i][j] = rand_choice[toss][i][j];//getting the newly chosen brick into next brick
		}
	}
	STATE=OFF;
	create_score("name",0);
	iSetTimer(200,move_down);
	iSetTimer(1000,sec);
	iSetTimer(60000,miin);
	iSetTimer(3600000,hour);
	iInitialize(800,600,"BRICK GAME");
	return 0;
}	


