//學號：F74046242
//姓名：謝耀賢
//編譯方式：gcc -o hw3 hw3.c -lm
//執行方式：./hw3 (number) (position)
//功能：玩家輸入number以及position,程式隨機產生變數答案,讓玩家可以進行猜測（遊戲規則類似1A2B）
//新增 : 次函式*3
//更新日期：2015.11.02
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>

void decorate(void);
int checklength(int a);
int checksame(int *guess,int b);
int main(int argc,char *argv[])
{
	if(argc!=3)   //輸入格式錯誤提醒
	{
		printf("Please input the correct form: \n");
		printf("%s%s%s\n%s\n%s\n","Usage:",argv[0]," N P","N is the number that you want to play with.","P is the position that you can guess.");
		exit(1);
	}
	//將字串轉成數字
	int number = atoi(argv[1]);
	int position = atoi(argv[2]);
	int i, j, answer[position], temp, guess[position], *guessp = &guess[0];
	int a, b, times;
	srand(time(NULL));
	//設定密碼
	for(i=0;i<position;i++)
	{
		answer[i] = (rand() % number) + 1;
		
		//判斷數字是否重複
		for(j=0;j<i;j++)
		{
			if(answer[i]==answer[j])
				i--;		
		}
	}
	
	decorate();
	printf("answer : ");
	for(i=0;i<position;i++)
	{
		printf("%d",answer[i]);
	}
	printf("\n");
			
	printf("Please input %d numbers to guess the answer(from 1 to %d)\n",position,number);
	printf("\nLet's begin to play this game:\n\n");
	times=1;
	
	while(1)
	{		
		while(1)
		{
			//開始猜
			printf("Please input your guess here : ");
			scanf("%d",&temp);
			if(checklength(temp) == position)  //檢查輸入數字長度
			{
				j = position - 1;
				for(i=0;i<position;i++)
				{
					guess[i] = temp / pow(10,j);
					temp -= guess[i]*pow(10,j);
					j--;
				}
				if(checksame(guessp, position)==0)
				{
					break;
				}
				else
				{
					printf("You cannot input the same number!!!\n");
				}
			}
			else
			{	
				printf("Please input the correct position of number!!!\n");
			}		
		}

		
			//判斷
			a=0;                 
			b=0;
			for(i=0;i<position;i++)
			{
				for(j=0;j<position;j++)
				{
					if(guess[i]==answer[j]&&i==j) 
						a++;
					if(guess[i]==answer[j]&&i!=j) 
						b++;
				}
			}
		
			for(i=0;i<position;i++)
			{
				printf("%d",guess[i]);
			}
			if(a==position)
			{
				printf("     %dH%dX",a,b);
				printf("\n\nCongratulations, you pass this game in %d times\n",times);
				break;
			}
			else
			{
				printf("     %dH%dX\n",a,b);
				times++;
			}
	}
	return 0;
}

void decorate(void)
{
	system("clear");
	printf("\n");
	printf("*       *  *********  *            *******    *****    *       *  *********\n");
	printf("*       *  *          *           *          *     *   * *   * *  *        \n");
	printf("*       *  *          *          *          *       *  *   *   *  *        \n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*       *  *********  *          *          *       *  *       *  *********\n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*       *  *          *          *          *       *  *       *  *        \n");
	printf("*   *   *  *          *          *          *       *  *       *  *        \n");
	printf("* *   * *  *          *           *          *     *   *       *  *        \n");
	printf("*       *  *********  *********    *******    *****    *       *  *********\n");
	printf("\n");
}

int checklength(int a)
{
	size_t llength;
	char length[10];
	sprintf(length, "%d", a); //將數字轉成字串
	llength = strlen(length);
	return llength;
}
int checksame(int *guess,int b)	//判斷輸入數字是否重複
{
	int i, j, same=0;
	for(i=0;i<b;i++)
	{
		for(j=i+1;j<b;j++)
		{
			if(guess[i]==guess[j])
				same++;
		}
	}
	return same;
}
