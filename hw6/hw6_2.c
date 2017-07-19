#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i;
	char floating_c[33], double_c[65];


	/*same as hw6_1, just change something to union*/


	union{
		unsigned int in_num;
		float f_num;
	}flo;

	union{
		unsigned long int l_in_num;
		double d_num;
	}dou;

	printf("Input the floating number : ");
	scanf("%f",&flo.f_num);

	for(i=31;i>=0;i--)
	{
		printf("%d",(flo.in_num >> i) & 1);
	}
	printf("\n");


	printf("Input binary : ");
	scanf("%s",floating_c);
	for(i=31;i>=0;i--)
	{
		if(floating_c[31-i] == '1')
			flo.in_num |= (1 << i);
	}
	printf("%e\n",flo.f_num);


	printf("Input the double number: ");
	scanf("%lf",&dou.d_num);

	for(i = 63; i>=0 ; i--)
	{
		printf("%ld",(dou.l_in_num >> i) & 1);
	}
	printf("\n");

	printf("Input binary : ");
	scanf("%s",double_c);
	for(i = 63; i>=0 ; i--)
	{
		if(double_c[63-i] == '1')
			dou.l_in_num |= ((unsigned long)1 << i);
	}
	printf("%e\n",dou.d_num);
	

	return 0;
}
