#include<stdio.h>
#include<stdlib.h>

int main()
{
	/*<-------------------------- open files ----------------------------->*/
	FILE *fp_read, *fp_write, *fp_write_ano;
	fp_read = fopen("buckets.in","r");
	fp_write = fopen("buckets.out","w");
	fp_write_ano = fopen("mapping.out","w");
	/*<----------- if buckets.in not exists, show error message ---------->*/
	if(!fp_read)
	{
		printf("file not found!!");
		exit(1);
	}
	/*<---------------- detect row and element of bucket.in --------------->*/
	int row = 1, element = 1;
	int element_max = 0;
	char ch;
	while((ch = fgetc(fp_read))!=EOF)
	{
		if(ch == ' ')
			element++;
		if(ch == '\n')
		{
			row++;
			if(element > element_max)
				element_max = element;
			element = 1;
		}
	}
	printf("row = %d, element_max = %d\n",row,element_max);
	/*<---------------------- create new array ----------------------------->*/
	int n;
	printf("input the column that you want to store : ");
	scanf("%d",&n);
	if(n < element_max)
	{
		printf("you have to input n higher or equal to element_max\n");
		exit(1);
	}
	int i=0, j=0;
	int store_element[row][n];
	for(i=0;i<row;i++)
	{
		for(j=0;j<n;j++)
		{
			store_element[i][j] = 0;
		}
	}
	/*<--------------------- put elements into array ----------------------->*/
	i=0, j=0;
	char temp;
	rewind(fp_read);	//reset    (important!!!!)
	while(fscanf(fp_read,"%d%c",&store_element[i][j],&temp)!=EOF)
	{
		j++;
		if(temp == '\n' || temp == '\r')
		{
			i++;
			j=0;
		}
	}
	/*<-------------------- detect the length of data ---------------------------->*/
	int store_length[row];
	element = 0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<n && store_element[i][j] != 0;j++)
		{
			if(store_element[i][j] != 0)
				element++;
		}
		store_length[i] = element;
		element = 0;
	}
	/*for(i=0;i<row;i++)
	{
		printf("%d lines : %d\n",i+1,store_length[i]);
	}*/
	/*<----------------------------- arrange ------------------------------------->*/
	int new_array[row][n], left[row], output[row];
	int k,l;
	for(i=0;i<row;i++)
	{
		output[i] = store_length[i]; //store the length of data
		left[i] = n; //store how many can still store into
		for(j=0;j<n;j++)
			new_array[i][j] = 0;
	}
	for(i=0;i<row;i++)
	{
	/*<------------------- detect the length and same data ----------------------->*/
		for(j=0;j<row;j++)
		{
			for(k=0;k<store_length[i];k++) // k<store_length[i] -> avoid to store 0
			{
				for(l=0;l<n;l++)
				{
					if(store_element[i][k] == new_array[j][l])
					{
						output[i]--;
						break;
					}
				}
			}
			if(left[j] < output[i])
				output[i] = store_length[i];
			else
				break;
		}
	/*<----------------------- put data into new array --------------------------->*/
		for(k=0;k<store_length[i];k++)
		{
			for(l=0;l<n;l++)
			{
				if(store_element[i][k] == new_array[j][l]) //not put the same data
					break;
				if(new_array[j][l] == 0)
				{
					new_array[j][l] = store_element[i][k];
					left[j]--; //the space that can store -1 (from n)
					break;
				}
			}
		}
	}
	/*<---------------------- contain of mapping.out ---------------------------->*/
	int check;
	int map[row][n], index[row];
	//create a new array -> map[][]
	for(i=0;i<row;i++)
	{
		for(j=0;j<n;j++)
		{
			map[i][j] = 0;
		}
	}
	//begin check
	for(i=0;i<row;i++)
	{
		for(j=0;j<row;j++)
		{
			check = 0;
			for(k=0;k<store_length[i];k++)
			{
				for(l=0;l<n;l++)
				{
					if(store_element[i][k] == new_array[j][l])
					{
						check++;
						break;
					}
				}
			}
			if(check == store_length[i])
				break;
		}
		index[i] = j;
		for(k=0;k<store_length[i];k++)
		{
			for(l=0;l<n;l++)
			{
				if(store_element[i][k] == new_array[j][l])
				{
					map[i][l] = 1;
					break;
				}
			}
		}
	}
	/*<-------------- put contain of array into buckets.out ---------------------->*/
	for(i=0;i<row;i++)
	{
		for(j=0;j<n && new_array[i][j]!=0 ;j++)
			fprintf(fp_write,"%d ",new_array[i][j]);
		fprintf(fp_write,"\n");
	}
	/*<-------------- put contain of array into mapping.out ----------------------->*/
	for(i=0;i<row;i++)
	{
		fprintf(fp_write_ano,"%d ",index[i]);
		for(j=0;j<n;j++)
		{
			fprintf(fp_write_ano,"%d",map[i][j]);
		}
		fprintf(fp_write_ano,"\n");
	}
	/*<-------------------- remember to close the file ---------------------------->*/
	fclose(fp_read);
	fclose(fp_write);
	fclose(fp_write_ano);
	printf("finish!!\n");
	return 0;
}
