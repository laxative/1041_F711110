#include<stdio.h>
#include<stdlib.h>

typedef unsigned int ui;
typedef struct node{
	ui ip[4];
	ui length;
	struct node *next;
}set;
ui element(ui *temp);
ui divide(ui bin, int group);
set *new_node(set *head, ui *temp, ui length);
set *search_data(set *head, ui *temp);
void output_data(FILE *result, set *match);
set *delete_node(set *head, ui *temp, ui length);
void free_all(set *head);
//void print_list(set *head, FILE *chk);     //for check
int main()
{
	inline unsigned long long int rdtsc()
	{
		 unsigned long long int x;
		 asm volatile ("rdtsc" : "=A" (x));
		 return x;
	}
	unsigned long long int begin, end;
	//Open Files
	FILE *origin, *search, *insert, *delete, *result, *csv_search, *csv_insert, *csv_delete;
	origin = fopen("IPv4_400k.txt","r");
	search = fopen("IPv4_search.txt","r");
	insert = fopen("IPv4_insert.txt","r");
	delete = fopen("IPv4_delete.txt","r");
	result = fopen("result.txt","w");
	csv_search = fopen("search.csv","w");
	csv_insert = fopen("insert.csv","w");
	csv_delete = fopen("delete.csv","w");

	//set linklist and array
	set **first, **second, **third;
	first = malloc(256 * sizeof(set*));
	second = malloc(4096 * sizeof(set*));
	third = malloc(4096 * sizeof(set*));

	int i;
	for(i=0;i<256;i++)
		first[i] = NULL;
	for(i=0;i<4096;i++)
	{
		second[i] = NULL;
		third[i] = NULL;
	}
	//store data
	ui temp[4], length;
	ui num, temp_num;
	while(fscanf(origin,"%u.%u.%u.%u/%u",&temp[0],&temp[1],&temp[2],&temp[3],&length) != EOF)
	{
		if(8<=length&&length<16)
		{
			temp_num = element(temp);
			num = divide(temp_num,1);
			first[num] = new_node(first[num],temp,length);
		}
		else if(16<=length&&length<24)
		{
			temp_num = element(temp);
			num = divide(temp_num,2);
			second[num] = new_node(second[num],temp,length);
		}
		else if(24<=length)
		{
			temp_num = element(temp);
			num = divide(temp_num,3);
			third[num] = new_node(third[num],temp,length);
		}
	}
/*	//check data
	FILE *chk;
	chk = fopen("check.txt","w");
	for(i = 0; i < 1 << 8;i++) {
		print_list(first[i], chk);
		fprintf(chk, "==============================\n");
	}
	for(i = 0;i < 1 << 12;i++) {
		print_list(second[i], chk);
		fprintf(chk, "==============================\n");
		print_list(third[i], chk);
	}
*/
	//search data
	set *match = NULL;
	while(fscanf(search,"%u.%u.%u.%u",&temp[0],&temp[1],&temp[2],&temp[3]) != EOF)
	{
		begin = rdtsc();
		temp_num = element(temp);
		ui bin_8 = divide(temp_num,1);
		ui bin_12 = divide(temp_num,2);

		match = search_data(third[bin_12],temp);
		if(match == NULL)
			match = search_data(second[bin_12],temp);
		if(match == NULL)
			match = search_data(first[bin_8],temp);
		end = rdtsc();
		output_data(result,match);
		fprintf(csv_search,"%llu\n",end-begin);
	}

	//insert data
	while(fscanf(insert,"%u.%u.%u.%u/%u",&temp[0],&temp[1],&temp[2],&temp[3],&length) != EOF)
	{
		begin = rdtsc();
		if(8<=length&&length<16)
		{
			temp_num = element(temp);
			num = divide(temp_num,1);
			first[num] = new_node(first[num],temp,length);
		}
		else if(16<=length&&length<24)
		{
			temp_num = element(temp);
			num = divide(temp_num,2);
			second[num] = new_node(second[num],temp,length);
		}
		else if(24<=length)
		{
			temp_num = element(temp);
			num = divide(temp_num,3);
			third[num] = new_node(third[num],temp,length);
		}
		end = rdtsc();
		fprintf(csv_insert,"%llu\n",end-begin);
	}
	//delete data
	while(fscanf(delete,"%u.%u.%u.%u/%u",&temp[0],&temp[1],&temp[2],&temp[3],&length) != EOF)
	{
		begin = rdtsc();
		if(8<=length&&length<16)
		{
			temp_num = element(temp);
			num = divide(temp_num,1);
			first[num] = delete_node(first[num],temp,length);
		}
		else if(16<=length&&length<24)
		{
			temp_num = element(temp);
			num = divide(temp_num,2);
			second[num] = delete_node(second[num],temp,length);
		}
		else if(24<=length)
		{
			temp_num = element(temp);
			num = divide(temp_num,3);
			third[num] = delete_node(third[num],temp,length);
		}
		end = rdtsc();
		fprintf(csv_delete,"%llu\n",end-begin);
	}
	//free list
	for(i=0;i<256;i++)
		free_all(first[i]);
	for(i=0;i<4096;i++)
	{
		free_all(second[i]);
		free_all(third[i]);
	}
	//Close Files
	fclose(origin);
	fclose(search);
	fclose(insert);
	fclose(delete);
	fclose(result);
	fclose(csv_search);
	fclose(csv_insert);
	fclose(csv_delete);
	//fclose(chk);
	return 0;
}
//function of checking where to store data
ui element(ui *temp)
{
	ui bin = 0x00000000;
	bin |= (temp[0] << 24);
	bin |= (temp[1] << 16);
	bin |= (temp[2] << 8);
	bin |= temp[3];

	return bin;
}
ui divide(ui bin, int group)
{
	if(group == 1)
		return (bin >> 24);
	else
		return (bin >> 20);	
}
//function of set new node, input data, and arrange
set *new_node(set *head, ui *temp, ui length)
{
	set *t = head, *new = malloc(sizeof(set));
	new->length = length;
	int i;
	for(i=0;i<4;i++)
	{
		new->ip[i] = temp[i];
	}
	new->next = NULL;
	//input to first node if there are no data inside
	if(head == NULL)
		return new;
	//arrange from high length to low length
	//first space is right and input
	if(head->length <= length)
	{
		new->next = head;
		return new;
	}
	//find right space and input
	while(t->next != NULL)
	{
		if((t->next)->length <= length)
		{
			new->next = t->next;
			t->next = new;
			return head;
		}
		else
			t = t->next;
	}
	//input data at the bottom(lowest length)
	t->next = new;
	return head;
}
//function of searching match data
set *search_data(set *head, ui *temp)
{
	ui origin, new;
	set *t = head;
	while(t != NULL)
	{
		origin = element(t->ip) >> (32 - t->length);
		new = element(temp) >> (32 - t->length);
		if(origin == new)
			break;
		else
			t = t->next;
	}
	return t;
}
//output result to result.txt
void output_data(FILE *result, set *match)
{
	if(match != NULL)
		fprintf(result,"%u.%u.%u.%u/%u\n",match->ip[0],match->ip[1],match->ip[2],match->ip[3],match->length);
	else
		fprintf(result,"0.0.0.0/0\n");

	return;
}
//function of checking data
/*void print_list(set *head, FILE *chk)
{
	set *t = head;
	while(t != NULL) 
	{
		output_data(chk, t);
		t = t -> next;
	}
	return;
}*/
set *delete_node(set *head, ui *temp, ui length)
{
	set *t = head, *need_free;
	ui headorigin, headnew, origin, new;
	//no data inside
	if(head == NULL)
		return head;

	//if the first node match and need to be deleted
	headorigin = element(head->ip);
	headnew = element(temp);
	if(headorigin == headnew && head->length == length)
	{
		need_free = head;
		head = head->next;
		free(need_free);
		return head;
	}
	//find data to be deleted
	while(t->next != NULL)
	{
		origin = element((t->next)->ip);
		new = element(temp);
		if(origin == new && (t->next)->length == length)
		{
			need_free = t->next;
			t->next = (t->next)->next;
			free(need_free);
			return head;
		}
		else
			t = t->next;
	}
	return head;
}
void free_all(set *head)
{
	set *t = head;
	while(t != NULL)
	{
		head = head->next;
		free(t);
		t = head;
	}
}
