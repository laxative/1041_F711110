#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[]) {

	system("clear");
	int number = atoi(argv[1]);
	int position = atoi(argv[2]);
	int answer[position], guess[position];
	int i,j;
	srand(time(NULL));
	for(i=0;i<position;i++) {
		answer[i] = rand() % number + 1;
		for(j=0;j<i;j++) {
			if(answer[i] == answer[j]) {
				i--;
			}
		}
	}
/*	printf("answer : ");
	for(i=0;i<position;i++) {
		printf("%d",answer[i]);
	}
	printf("\n");
*/
	int temp;
	int a=0, b=0, time=0;
	while(a != position) {
		printf("plz enter your guess: ");
		scanf("%d",&temp);
		for(i=position-1;i>=0;i--) {
			guess[i] = temp % 10;
			temp /= 10;
		}
	
		a=0, b=0;
		for(i=0;i<position;i++) {
			for(j=0;j<position;j++) {
				if(answer[i] == guess[j] && i == j)
					a++;
				else if(answer[i] == guess[j] && i != j)
					b++;
			}
		}
		for(i=0;i<position;i++) {
			printf("%d",guess[i]);
		}
		printf("    %dA%dB\n",a,b);
		time++;
	}
	printf("Congratulation, you pass this game in %d times\n",time);
	return 0;
}

