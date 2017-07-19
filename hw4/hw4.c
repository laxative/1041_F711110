#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quicksort(int a[], int low, int high);
int split(int a[], int low, int high);
void float_quicksort(float a[], int low, int high);
float float_split(float a[], int low, int high);
int main(int argc, char *argv[]){

	if(argc!=3)  //輸入格式錯誤提醒
	{
		printf("Please input the correct form: \n");
		printf("%s%s%s\n%s\n%s\n","Usage:",argv[0]," N (data type)","N is the number of integer or floating point numbers.","data type 0 means integer, 1 means floating point number.\n");
		exit(1);
	}
	int N, type;
	N = atoi(argv[1]);
	type = atoi(argv[2]);
	srand(time(NULL));
	if(N>0)
	{
		if(type==0) //integers
		{
			int i,integer[N];
			for(i=0;i<N;i++)
			{
				integer[i] = rand() % 10001;
			}
			printf("numbers to be sorted : ");
			for(i=0;i<N;i++)
			{
				printf("%d ",integer[i]);
			}
			quicksort(integer, 0, N-1);
			printf("\nIn sorted number:       ");
			for(i=0;i<N;i++)
			{
				printf("%d ",integer[i]);
			}
			printf("\n");
	
		}
		else if(type==1)	//floating point numbers
		{
			int i;
			float floatingpoint[N];
			for(i=0;i<N;i++)
			{
				floatingpoint[i] = ((float)rand()/(float)RAND_MAX)*10000;		//(float)rand()/(float)RAND_MAX 可得0到1之間亂數，*10000之後得0-10000之間亂數
			}
			printf("numbers to be sorted : ");
			for(i=0;i<N;i++)
			{
				printf("%.2f ",floatingpoint[i]);
			}
			float_quicksort(floatingpoint, 0, N-1);
			printf("\nIn sorted order:       ");
			for(i=0;i<N;i++)
			{
				printf("%.2f ",floatingpoint[i]);
			}
			printf("\n");
			
		}
		else	//not 1 nor 0
		{
			printf("data type you can only type 1 or 0.\n");
			exit(1);
		}
	}
	else
	{
		printf("The number you input must higher than 0\n");
		exit(1);
	}

return 0;
}

/*以下程式碼來自課本*/

/*for integer*/
void quicksort(int a[], int low, int high)
{
	int middle;

    if (low >= high) 
		return;
	middle = split(a, low, high);
    quicksort(a, low, middle - 1);
	quicksort(a, middle + 1, high);
}

int split(int a[], int low, int high)
{
	int part_element = a[low];

	for (;;) 
	{
	    while (low < high && part_element >= a[high])
		    high--;
	    
		if (low >= high) 
			break;
		
		a[low++] = a[high];

	    while (low < high && a[low] >= part_element)
		    low++;
	    
		if (low >= high) 
			break;
		
		a[high--] = a[low];
	}

	a[high] = part_element;
	return high;
}

/*for floating point numbers*/
void float_quicksort(float a[], int low, int high)
{
	float middle;

    if (low >= high) 
		return;
	middle = float_split(a, low, high);
    float_quicksort(a, low, middle - 1);
	float_quicksort(a, middle + 1, high);
}

float float_split(float a[], int low, int high)
{
	float part_element = a[low];

	for (;;) 
	{
	    while (low < high && part_element >= a[high])
		    high--;
	    
		if (low >= high) 
			break;
		
		a[low++] = a[high];

	    while (low < high && a[low] >= part_element)
		    low++;
	    
		if (low >= high) 
			break;
		
		a[high--] = a[low];
	}

	a[high] = part_element;
	return high;
}
