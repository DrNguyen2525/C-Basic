#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct sv
{
    char num[9];
    char *name;
    char *class;
    char sex[3];
    float point;
    struct sv *next;
}sv;
int i;
sv *first;

int name_loc(char name[])
{
    i=strlen(name)-1;
    while(name[i]!=' ' && i>-1) i--;
    return i+1;
}

int name_cmp(char name1[],char name2[])
{
    int j;
    char cut1[10],cut2[10];
    i=name_loc(name1);
    j=0;
    while(name1[i]!='\0')
    {
        cut1[j]=name1[i];
        i++;
        j++;
    }
    i=name_loc(name2);
    j=0;
    while(name2[i]!='\0')
    {
        cut2[j]=name2[i];
        i++;
        j++;
    }
    if(strcmp(cut1,cut2)<0) return 0;
    if(strcmp(cut1,cut2)==0)
    {
        if(strcmp(name1,name2)<0) return 0;
        else return 1;
    }
    else return 1;
}

sv *last()
{
    sv *temp;
    temp=first;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void insert_head(sv *new)
{
    new->next=first;
    first=new;
}

void insert_last(sv *new)
{
    sv *temp=last();
    new->next=temp->next;
    temp->next=new;
}

void insert_middle(sv *temp,sv *new)
{
    new->next=temp->next;
    temp->next=new;
}

void insert(char maso[],char *ten,char *lop,char gioitinh[],int n)
{
    sv *temp;
    sv *new=(sv *) malloc(sizeof(sv));
    strcpy(new->num,maso);
    new->name=ten;
    new->class=lop;
    strcpy(new->sex,gioitinh);
    temp=first;
    if(first==NULL) insert_head(new);
    else
    {
        if(strcmp(new->class,temp->class)<0) insert_head(new);          //So sanh voi phan tu dau danh sach
        if(strcmp(new->class,temp->class)==0)
        {
            if(name_cmp(new->name,temp->name)==0) insert_head(new);
        }
        if(strcmp(new->class,temp->class)>0 || (strcmp(new->class,temp->class)==0 && name_cmp(new->name,temp->name)==1))
        {
            while(temp)
            {
                if(n==1)                //Neu danh sach chi co 1 phan tu
                {
                    if(strcmp(new->class,temp->class)>0)
                    {
                        insert_last(new);
                        break;
                    }
                    if(strcmp(new->class,temp->class)==0)
                    {
                        if(name_cmp(new->name,temp->name)==0) insert_head(new);
                        else insert_last(new);
                        break;
                    }
                }
                else
                {
                    if(temp->next==NULL)
                    {
                        if(strcmp(new->class,temp->next->class)<0)
                        {
                            insert_middle(temp,new);
                            break;
                        }
                        if(strcmp(new->class,temp->next->class)>0)
                        {
                            temp=temp->next;
                            if(temp->next==NULL)
                            {
                                insert_last(new);
                                break;
                            }
                        }
                        if(strcmp(new->class,temp->next->class)==0)
                        {
                            if(name_cmp(new->name,temp->next->name)==1)
                            {
                                temp=temp->next;
                                if(temp->next==NULL)
                                {
                                    insert_last(new);
                                    break;
                                }
                            }
                            else
                            {
                                insert_middle(temp,new);
                                break;
                            }
                        }
                    }
                    else
                    {
                        insert_last(new);
                        break;
                    }
                }
            }
        }
    }
}

void print()
{
    sv *temp;
    temp=first;
    printf("  MSSV  |           Ho va ten          | Lop | Gioi tinh | Diem Cbasic\n");
    while(temp)
    {
        printf("%-9s ",temp->num);
        printf("%-31s ",temp->name);
        printf("%-3s     ",temp->class);
        printf("%-3s         ",temp->sex );
        printf("%.2f\n",temp->point);
        temp=temp->next;
    }
}

int main()
{
    int x,n=0;
    char maso[9],ten[50],lop[10],gioitinh[3];
    char *p_ten,*p_lop;
    float diem;
    do
    {
        printf("\n");
        printf("1. Them sinh vien\n");
        printf("2. In ra danh sach sinh vien\n");
        printf("3. Cap nhat diem sinh vien\n");
        printf("4. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        while(getchar()!='\n');
        switch(x)
        {
            case 1:
                while(1)
                {
                    printf("Nhap ma so sinh vien: ");
                    gets(maso);
                    if(maso[0]=='\0') break;
                    printf("Ho va ten sinh vien: ");
                    gets(ten);
                    p_ten=(char *) malloc((strlen(ten)+1)*sizeof(char));
                    strcpy(p_ten,ten);
                    printf("Lop: ");
                    gets(lop);
                    p_lop=(char *) malloc((strlen(ten)+1)*sizeof(char));
                    strcpy(p_lop,lop);
                    printf("Gioi tinh: ");
                    gets(gioitinh);
                    n++;
                    insert(maso,p_ten,p_lop,gioitinh,n);
                    printf("\n");
                }
                break;

            case 2:
                print();
                break;

            case 3:
                break;

            case 4:
                break;
        }
    }
    while(x!=4);
    return 0;
}
