#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>

/* sNaKe GaMe */


void init( void );
int snake( void );
void fruit( void );
//void bonus( int X,int Y );
void display( void );
void curVis( int );
int step( void );
int control( void );
void turn( int target );
int forw_x( void );
int forw_y( void );
int a( int arg1, int arg2 );
void mainpage( void );
void gameover( void );
int worldRecord( void );
void clearScreen( void );
WORD textColor( int color );
void queue( void );
int enqueue( int X, int Y );
int dequeue( void );

struct node{
	int x;
	int y;
	struct node* next;
};

typedef struct node* NODE;

NODE head,tail;
int length;
int record, worldrecord;

enum{	RIGHT, UP, LEFT, DOWN	};
#define L 16
#define W 24
#define F_DEFAULT 310
int S=6;
int F;

char input;
int dir;

	clock_t start;
	char map[L][W];
	
int main( void )
{
	int foo,bar=1;
	record=0;
	worldrecord=0;
	mainpage();
	
		while(1){
			
		record=max( length-S-1, record );
		bar=worldRecord();
		F=F_DEFAULT;
		init();
		queue();
		if( snake())
		{
			getch();
			return -1;
		}
		fruit();
		
			while(1){
				
			start = clock();
			if(kbhit()){
				input=_getch();
				control();
			}
			else
			{
				input='\0';	
			}	
			foo=step();
			if( foo==0 )
			{
				gameover();
				break;
			}
			else if( foo==-1)
			{
				getch();
				return -1;
			}
			clearScreen();
			display();
			curVis(1);
			
			printf("\n score: \t\t %d \n your record: \t\t %d \n ", length-S-1, record  );
			if(bar)
			{
				printf("worldrecord: \t\t ?");
			}
			else
			{
				printf("world record: \t\t %d \n", worldrecord );	
			}
				
			while(clock()-start<F);
		

		}
	}
}


void init( void )
{
	int i,j;
	for (i=0;i<L;i++){
	for (j=0;j<W;j++){
	if((i&&i<L-1)&&(j&&j<W-1)){
		map[i][j]=' ';		
	}
	else{
		map[i][j]='#';
	}
	}
}
}

int snake( void )
{
	int j;
	for(j=1;j<=S+1;j++)
	{
		map[1][j]='*';	
		if(enqueue( j, 1))
		{
			return -1;
		}	
	}
	dir=RIGHT;
	return 0;
}

void fruit( void )
{
	int x=0,y=0;
	srand( time( NULL ));
	while(map[y][x]!=' '){
		x=rand()%(W-2)+1;
		y=rand()%(W-2)+1;
	}
	/*
	if(length%5){
		bonus(x,y);
	}
	else*/
//	{	
	map[y][x]='$';
//	}
if(length<30){
	F-=length<20?10:5;
}

}

/*
void bonus(int X, int Y)
{
	
}
*/

void display( void )
{
	int color;
	int i,j;
	char* foo=&map[0][0];
	for (i=0;i<L;i++,printf("\n")){
		for (j=0;j<W;j++,foo++){
			if(!(*(foo)==' ')){
				color=(int)*(foo)%16+3;
				textColor( color );
		}
		curVis(0);
		printf("%c", *foo );
	}
}
textColor( 15 );
}

void curVis( int yes )
{
	HANDLE					hStdOut;		
	CONSOLE_CURSOR_INFO 	conCurInfo;
	
	  GetConsoleCursorInfo( hStdOut , &conCurInfo );
	  conCurInfo.bVisible=yes;	
	  SetConsoleCursorInfo( hStdOut , &conCurInfo );
}

int step( void )
{
	int X,Y,leave_x, leave_y;
	
	X=forw_x();
	Y=forw_y();
	leave_x=tail->x;
	leave_y=tail->y;
	if( map[ Y ][ X ]=='#' || map[ Y ][ X ]=='*' )
	{
		return 0;
	}
	else
	{	
		if( map[ Y ][ X ]==' ' )
		{
			dequeue();
			map[ leave_y ][ leave_x ]=' ';
		}
		else
		{
			fruit();
		}
		map[ Y ][ X ]='*';
		
		if(enqueue( X, Y ))
			{ perror("DYNAMIC MEMORY ALLOCATION ERROR!");
		return -1;
		}
	return 1;		
	}

}

int control( void )
{
	switch( input ){
		case 'w':
		case '8':
			turn(UP);
			break;
		case 's':
		case '5':
			turn(DOWN);
			break;
		case 'a':
		case '4':
			turn(LEFT);
			break;
		case 'd':
		case '6':
			turn(RIGHT);
			break;
		case ' ':
			getch();
			break;
		default:
			return 0;
	}
	return 1;

}



void turn( int target )
{
	if( target!=a(dir, 2 )){
		dir=target;
	}
}


int forw_x( void )
{
	if( head ){
	if( dir == LEFT )
	{
		return head->x-1;
	}
	else if( dir == RIGHT )
	{
		return head->x+1;
	}
	else
	{
		return head->x;
	}
	}
	else
	{
		perror("null head");
		return -1;
	}
}

int forw_y( void )
{
	if( head ){
	if( dir == UP )
	{
		return head->y-1;
	}
	else if( dir == DOWN )
	{
		return head->y+1;
	}
	else
	{
		return head->y;
	}
	}
	else
	{
		perror("null head");
		return -1;
	}
}

int a( int arg1, int arg2 )
{
	return (arg1+arg2)%4;
}

void gameover( void )
{	
	F=F_DEFAULT;
	clock_t pace;
	int even=1;
	int bar=worldRecord();
	int recordTmp=record;
	int worldrecordTmp=worldrecord;
	record=max( length-S-1, record );
	worldRecord();
	
	while(1){
		pace=clock();
		if(kbhit()){
		break;
		}
		clearScreen();
		curVis(0);
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t GAME OVER \n\n");	printf("\n \t\t\t\t score: \t\t %d \n \t\t\t\t your record: \t\t %d \n \t\t\t\t ", length-S-1, recordTmp  );
		if(bar)
		{
			printf(" worldrecord: \t\t ?");
		}
		else
		{
			printf("world record: \t\t %d \n", worldrecordTmp );	
		}
		printf("\n\n \t\t\t\t Controls: \t W/A/S/D OR 8/4/5/6 \n\n \t\t\t\t Pause: SPACE\n\n\n");
		if(even){printf("\t\t\t\t [PRESS ANY KEY TO CONTINUE] \n");}
		else{
			printf("\n");
		}
		curVis(1);
		even=++even%2;
		while(clock()-pace<F);	
	}
		_getch();
}

void mainpage( void )
{
	F=F_DEFAULT;
	clock_t pace;
	int even=1;
	while(1){
		pace=clock();
		if(kbhit()){
			break;
		}
		clearScreen();
		curVis(0);
		printf("\n\n\n\n\n\n");
		printf("\t\t\t\t #######  #    ##     ##     ###   #  ####### \n");
		printf("\t\t\t\t #######  ##   ##    ####    ###  ##  ####### \n");
		printf("\t\t\t\t ###      #### ##   ##  ##   ### ##   ###     \n");
		printf("\t\t\t\t #######  #######  ########  ####     ####### \n");
		printf("\t\t\t\t     ###  ### ###  ###   ##  ### ##   ###     \n");
		printf("\t\t\t\t #######  ###  ##  ###   ##  ###  ##  ####### \n");
		printf("\t\t\t\t #######  ###  ##  ###   ##  ###   #  ####### \n\n");
		printf("\t\t\t\t RETRO GAME REMAKE \n\n \t\t\t\t by A.S. Soylu				\n\n\n\n");
		printf("\t\t\t\t Controls: \t W/A/S/D OR 8/4/5/6 \n\n \t\t\t\t Pause: SPACE\n\n\n");
		
		if(even){
			printf("\t\t\t\t [PRESS ANY KEY TO CONTINUE] \n");}
		else{
			printf("\n");
		}
		curVis(1);
		even=++even%2;
		while(clock()-pace<F);	
	}
		_getch();
}



int worldRecord( void )
{

FILE *fPtr=fopen("record.dat", "rb");
	
		if(fPtr==NULL)
		{
			perror("record.dat file reading failed");
			fPtr=fopen("record.dat", "wb");
			fclose(fPtr);
			fPtr=fopen("record.dat", "rb");
		if(fPtr==NULL)
		{
			perror("record.dat file access error");
			getch();
			return -1;
		}
		else
		{
			printf("new file constructed\n");
			getch();
		}
		}

		fscanf(fPtr,"%d", &worldrecord );
		fclose(fPtr);
		
		if(record>worldrecord){
		fPtr=fopen("record.dat", "wb");
			worldrecord= record;
			fprintf(fPtr, "%d\n", worldrecord );	
		fclose(fPtr);
		}
		return 0;
}

void clearScreen( void )
{
	HANDLE						hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO	csbi;

	DWORD						count;
	DWORD						cellCount;
	COORD						homeCoords = { 0, 0 };
	
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if(hStdOut == INVALID_HANDLE_VALUE)
	return;
	
	/* Get the number of cells in the your buffer */
	if(!GetConsoleScreenBufferInfo( hStdOut, &csbi ))
	return;
		
	cellCount =csbi.dwSize.X *csbi.dwSize.Y;
	
	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		))
	return;
		
	/* Fill the entire buffer with your colors and attributes */
	if(!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		))
	return;
		
	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );


}

WORD textColor( int color )
{
	HANDLE						hStdOut;//console
	CONSOLE_SCREEN_BUFFER_INFO	csbi;//console info
	WORD						saved_attributes;

	
	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if(hStdOut == INVALID_HANDLE_VALUE)
	return;
	
	/* save your attributes */
	if(!GetConsoleScreenBufferInfo( hStdOut, &csbi ))
	return;
	
	saved_attributes= csbi.wAttributes;
	
	SetConsoleTextAttribute( hStdOut, color );

	return saved_attributes;
}

void queue( void )
{
	tail=head=NULL;
	length=0;
}


int enqueue( int X, int Y )
{
	NODE newNode;
	newNode=( NODE )malloc( sizeof( struct node ));
	if( newNode ){
		newNode->x=X;
		newNode->y=Y;
		newNode->next=NULL;
		if( tail )
		{
		head->next=newNode;
			if( tail->next==NULL )
			{
				tail->next=newNode;
			}
		}
		else
		{
			tail=newNode;
		}
		head=newNode;
		length++;
		return 0;
	}
	else
	{
		return 1;
	}
}
int dequeue( void )
{
	NODE temp;
	if( tail ){	
		temp=tail;
		tail=tail->next;
	if( tail==NULL )
	{
		head=NULL;
	}
	free(temp);
	length--;
		return 1;
	}
	else
	{
		return 0;
	}
}




