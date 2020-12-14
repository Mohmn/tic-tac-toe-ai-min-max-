#include<stdio.h>
#include<stdlib.h>

typedef struct list{
	
	int x,y;
	// tempory name list & it is a pointer to the node of smae datatype
	struct list *next;
}POINT;

typedef struct pos{
	int val;
	int x,y;
}POS;

POINT* insert(POINT *h,int x,int y)
{	
	if(h==NULL)
	{
	POINT *list=(POINT*)malloc(sizeof(POINT)*1);
	list->x = x; list->y = y;
	list->next = NULL;
	return list;	
	}
	POINT *sechead,*list=(POINT*)malloc(sizeof(POINT)*1);
	sechead = h;
 	list->x = x; list->y = y;
	list->next = sechead;
	h = list;
	return h;
}

void moves(char arr[][3],POINT **h)
{
	int i,j;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(arr[i][j] == ' ')
				*h = insert(*h,i,j);
		}
	}
}



void put_values(char arr[][3]);
void print_table(char arr[][3]);
void take_input_from_user(char arr[][3],int user);
int win(char arr[][3],char to_see,int user);


POS max(POS a,POS b);
POS min(POS a,POS b);

int  Aiwin(char arr[][3],char to_see,POINT **head);
POS minimax(char table[][3],char user);

int main()
{
	char arr[3][3];
	put_values(arr);
	print_table(arr);
	int draw = 0;
	
	printf("\n\n\n");
	
	printf("In this game there are two users\nuser1 and user2\n");
	printf("user1 gets X and user 2 gets O\n\n\n");
	
	while(1)
	{
		
		printf("\n\nTurn for user 1\n");
		POS val = minimax(arr,'X');
		arr[val.x][val.y] = 'X';
		system("cls");
		print_table(arr);
		if(win(arr,'X',1) == 100)
			break;	
		draw++;
		
		if(draw >= 9)
		{
			printf("game drawn\n");
			break;
		}
		
		printf("\n\nTurn for User 2\n");
		take_input_from_user(arr,2);
		system("cls");
		print_table(arr);
		if(win(arr,'O',2) == 100)
			break;
			
			
		draw++;

	}
	return 0;
}


void print_table(char arr[][3])
{
	int i,j;
	printf("\n\n");
	for(i=0;i<3;i++)
	{	
		for(j=0;j<3;j++)
			printf("===%c===||",arr[i][j]);
			
		printf("\n");
			
	}

}


void put_values(char arr[][3])
{
	int i,j;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		    arr[i][j] = ' ';
		
	}

}



void take_input_from_user(char arr[][3],int user)
{
   	int i,j,ok = 1;
	char value; 
	while(ok)
	{
	printf("give the ith and jth value for user%d \n",user);
	
	scanf("%d%d",&i,&j);
                                         
	if(i>3 || j>3)
		printf("cant have values greater 2\n");
	else if( arr[i][j] != ' ')
		printf("u cant overwrite the current  symbol\n");
	else
		ok = 0;
		
    }
	
    ok = 1;
	
	
	while(ok)
	{
	fflush(stdin);	
	printf("give the value for user%d\n",user);
	scanf("%c",&value);
	if(user == 1)
	{
		if(value != 'X')
			printf("user1 can only give X\n");
		else
			ok = 0;
	}
	else if(user == 2)
	{
		if(value != 'O')
			printf("user2 can only give O\n");
		else
			ok = 0;
	}

	}

	arr[i][j] = value;
}


int  win(char arr[][3],char to_see,int user)
{
	int i,j,a,b;
	for(i=0;i<3;i++)
	{
		
		a = 0;
		b = 0;
		for(j=0;j<3;j++)
		{
			a+= arr[i][j];
			b+= arr[j][i];

		}

		if(a == (3 *(to_see)) || b == (3 *(to_see)) )
		{
			printf("user %d won\n",user);
			return 100;
		}
	}
	
	// checking the diagonals
	a = arr[0][0] +arr[1][1] +arr[2][2];
	if(a == (3 *(to_see)))
	{
			printf("user %d won\n",user);
			return 100;	
	}
	b = arr[0][2] + arr[1][1] + arr[2][0];
	if(b == (3 *(to_see)))
	{
			printf("user %d won\n",user);
			return 100;	
	}
	return 1;
	// 00 01 02
	
	// 10 11 12
	// 20 21 22

	// 00 10 20
	// 01 11 21
 //    02 12 22

	// 00 11 22
	// 02 11 20	
}

int  Aiwin(char arr[][3],char to_see,POINT **head)
{
	int i,j,a,b,num_spaces=0;
	
	for(i=0;i<3;i++)
	{	
		a = 0;
		b = 0;
		for(j=0;j<3;j++)
		{
			a+= arr[i][j];
			b+= arr[j][i];
			if(arr[i][j] == ' ')
			{
				num_spaces +=1;
				*head = insert(*head,i,j);
		    }
			
		}

		if(a == (3 *(to_see)) || b == (3 *(to_see)) )
		{
			if(to_see == 'X')
				return 1;
			else if(to_see == 'O')
				return -1;
		}
	}
	
	a = arr[0][0] +arr[1][1] +arr[2][2];
	if(a == (3 *(to_see)))
	{
		if(to_see == 'X')
			return 1;
		else if(to_see == 'O')
			return -1;	
	}
	b = arr[0][2] + arr[1][1] + arr[2][0];
	if(b == (3 *(to_see)))
	{
		if(to_see == 'X')
			return 1;
		else if(to_see == 'O')
			return -1;	
	}
	
	
	if(num_spaces == 0)
		return 0;
	return -4;

}


POS max(POS a,POS b)
{
	if(a.val>b.val)
		return a;
	return b;
}

POS min(POS a,POS b)
{
	if(a.val>b.val)
		return b;
	return a;
}
POS minimax(char table[][3],char user)
{
// 	  print_table(table);
//	  printf("\n\n");
	  POS x;POINT *head = NULL;
	  
	  if(user == 'X')
	  	x.val = Aiwin(table,'O',&head);
	  else
		x.val = Aiwin(table,'X',&head);
  	
 	  x.x = 0 ; x.y = 0;
	  if(x.val != -4)
	  	return x;

		if(user == 'X')
		{
			POS low;
			low.val = -100; low.x = 0; low.y = 0;
			while(head!=NULL)
			{
				table[(head)->x][head->y] = 'X';
				
				POS value;
				value = minimax(table,'O');
				value.x = head->x; value.y = head->y;
				
				low = max(low,value);
					
				table[head->x][head->y] = ' ';
				
				head = (head)->next;
			}
			
			return low;
					
		}	
		else if(user == 'O')
		{
			POS high;
			high.val = 100;
			high.x =0; high.y = 0;
			while(head!=NULL)
			{
				table[head->x][head->y] = 'O';
				
				POS value = minimax(table,'X');
				
				value.x = head->x; value.y = head->y;
				
				high = min(high,value);

				table[head->x][head->y] = ' ';	

				head = (head)->next;
			}
			
			return high;
			
		}
	
}
