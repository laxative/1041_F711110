#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i;
	char floating_c[33], double_c[65];
	float floating_num;
	double double_num;
	unsigned int *ipt = (unsigned int *)&floating_num;  //(unsigned int*) change the type
	unsigned long int *lipt = (unsigned long int *)&double_num; //same as above
	printf("Input the floating number : ");
	scanf("%f",&floating_num);

	for(i=31;i>=0;i--)
	{
		printf("%d",(*ipt >> i) & 1); //00.....0 = 0, 00.....01 = 1(in int type), so print one number(1 or 0) per time
	}
	printf("\n");


	printf("Input binary : ");
	scanf("%s",floating_c);
	for(i=31;i>=0;i--)
	{
		if(floating_c[31-i] == '1')
			*ipt |= ((unsigned int)1 << i); //gradually store numbers into array
	}
	printf("%e\n", floating_num);


	printf("Input the double number: ");
	scanf("%lf",&double_num);

	for(i = 63; i>=0 ; i--)
	{
		printf("%ld",(*lipt >> i) & 1); //same as above
	}
	printf("\n");

	printf("Input binary : ");
	scanf("%s",double_c);
	for(i = 63; i>=0 ; i--)
	{
		if(double_c[63-i] == '1')
			*lipt |= ((unsigned long int)1 << i); //same as above
	}
	printf("%e\n",double_num);
	

	return 0;
}
