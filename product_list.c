#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sp
{
	int num;
	int price;
	int amount;
	char name[30];
	struct sp *next;
}sp;

sp *first;
FILE *f;

sp *last()
{
    sp *temp;
    temp=first;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void insert_head(sp *new)
{
    new->next=first;
    first=new;
}

void insert_last(sp *new)
{
    sp *temp=last();
    temp->next=new;
}

void insert_middle(sp *temp,sp *new)
{
    new->next=temp->next;
    temp->next=new;
}

void list_insert(int maso,int gia,int sl,char ten[])
{
	sp *temp;
	sp *new=(sp *) malloc(sizeof(sp));
	new->num=maso;
	new->price=gia;
	new->amount=sl;
	strcpy(new->name,ten);
	temp=first;
	if(first==NULL) insert_head(new);
	else
	{
		if(new->price < first->price) insert_head(new);
		else
		{
			if(first->next==NULL)
			{
				if(new->price > first->price) insert_last(new);
			}
			else
			{
				while(temp)
				{
					if(new->price < temp->next->price)
					{
						insert_middle(temp,new);
						break;
					}
					else
					{
						temp=temp->next;
						if(temp->next==NULL)
						{
							insert_last(new);
							break;
						}
					}
				}
			}
		}
	}
}

void list_print()
{
	sp *temp;
	temp=first;
	printf("\n  Ma so  |  Gia  | So luong |		  Ten san pham\n");
	while(temp)
	{
		printf("%-7d   ",temp->num);
		printf("%-7d  ",temp->price);
		printf("%-7d   ",temp->amount);
		printf("%s\n",temp->name);
		temp=temp->next;
	}
}

void file_print()
{
	sp *temp;
	f=fopen("product_list.txt","w");
	temp=first;
	fprintf(f,"  Ma so  |  Gia  | So luong |		Ten san pham\n");
	while(temp)
	{
		fprintf(f,"%-7d   ",temp->num);
		fprintf(f,"%-7d  ",temp->price);
		fprintf(f,"%-7d   ",temp->amount);
		fprintf(f,"%s\n",temp->name);
		temp=temp->next;
	}
}

void file_write()
{
	sp s;
	f=fopen("sanpham.txt","w");
	while(1)
	{
		printf("\n");
		printf("Nhap ma san pham: ");
		scanf("%d",&s.num);
		if(s.num==0) break;
		printf("Gia san pham: ");
		scanf("%d",&s.price);
		printf("So luong: ");
		scanf("%d",&s.amount);
		while(getchar()!='\n');
		printf("Ten san pham: ");
		gets(s.name);
		fprintf(f,"%d %d %d %s\n",s.num,s.price,s.amount,s.name);
	}
	fclose(f);
}

void file_read()
{
	sp s;
	f=fopen("sanpham.txt","r");
	if(f!=NULL)
	{
		while(1)
		{
			fscanf(f,"%d %d %d ",&s.num,&s.price,&s.amount);
			if(feof(f)) break;
			fgets(s.name,30,f);
			s.name[strlen(s.name)-1]='\0';
			list_insert(s.num,s.price,s.amount,s.name);
		}
		list_print();
		file_print();
		fclose(f);
	}
}

int main()
{
    file_write();
    file_read();
    return 0;
}