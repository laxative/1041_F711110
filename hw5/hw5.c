#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void RANDOM(int number, int position);
void save_all(int position);
void try(int number, int position);
void HX_compare(int position);
void detect(int position);
void printarr(int position);

int times;
int save[20][11];
int guess[9];
int H,X;
int answer[9];
int detect_H, detect_X, HX_detect;


int main(int argc, char *argv[])
{
	//ensure the form:
	if(argc!=3)
	{
		printf("Please input the correct form: \n");
		printf("%s%s%s\n%s\n%s\n","Usage:",argv[0]," N P","N is the number you want to play with.","P is the position that you can guess.");
		exit(1);
	}
	srand(time(NULL));
	
	int number = atoi(argv[1]);
	int position = atoi(argv[2]);
	
	//ensure 0<number<=9 and 0<position<=9
	if(number>9||number<=0)
	{
		printf("number must between 1-9\n");
		exit(1);
	}
	else if(position>9||position<=0)
	{
		printf("position must between 1-9\n");
		exit(1);
	}
	//ensure number >= position
	if(number<position)
	{
		printf("number must higher or equal to position\n");
		exit(1);
	}
	//set answer
	int i, j;
	for(i=0;i<position;i++)
	{
		answer[i]=(rand()%number)+1;
		for(j=0;j<i;j++)
		{
			if(answer[i]==answer[j])
				i--;
		}
	}
	printf("answer:");
	for(i=0;i<position;i++)
	{
		printf("%d",answer[i]);
	}
	printf("\n");

	
	
	try(number,position);
	return 0;
}

void RANDOM(int number, int position)
{
	//create array randomly
	int i, j;
	for(i=0;i<position;i++)
	{
		guess[i]=(rand()%number)+1;
		for(j=0;j<i;j++)
		{
			if(guess[i]==guess[j])
				i--;
		}
	}
}

void save_all(int position)
{
	//save try to save array
	int i;
	for(i=0;i<position;i++)
	{
		save[times][i]=guess[i];
	}
	save[times][9] = H;
	save[times][10] = X;
}

void try(int number, int position)
{
	printf("%dtimes:   ", times+1);
	RANDOM(number,position);
	detect(position);
	while(HX_detect!=0)
	{
		RANDOM(number,position);
		detect(position);
	}
	printarr(position);
	HX_compare(position);

	if(H!=position)
	{
		save_all(position);
		times++;
		try(number,position);
	}
	else
		printf("finish~~\n");
}

void HX_compare(int position)
{
	int i, j;
	H=0;
	X=0;
	for(i=0;i<position;i++)
	{
		for(j=0;j<position;j++)
		{
			if(guess[i]==answer[j]&&i==j)
				H++;
			else if(guess[i]==answer[j]&&i!=j)
				X++;
		}
	}
	printf("    %dH%dX\n",H,X);
}
void detect(int position)
{
	int i,j,k;
	HX_detect=0;
	for(i=0;i<times;i++)
	{
		detect_H=0;
		detect_X=0;
		for(j=0;j<position;j++)
		{
			for(k=0;k<position;k++)
			{
				if(guess[j]==save[i][k]&&j==k)
					detect_H++;
				else if(guess[j]==save[i][k]&&j!=k)
					detect_X++;
			}
		}
		if(detect_H != save[i][9] || detect_X != save[i][10])
			HX_detect++;
	}
}

void printarr(int position)
{
	int i;
	for(i=0;i<position;i++)
	{
		printf("%d",guess[i]);
	}
}
