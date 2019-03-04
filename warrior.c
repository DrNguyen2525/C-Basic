#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct warrior
{
    char name[10];
    int hp,atk,agi,def,point,team;
    struct warrior *next;
}
warrior;

typedef struct rank
{
    char name[10];
    int point;
}
rank;

warrior *front1,*front2,*rear1,*rear2;

void enqueue(warrior **front,warrior **rear,char ten[],int mau,int cong,int nhanh,int thu,int doi)
{
    warrior *new=(warrior *) malloc(sizeof(warrior));
    strcpy(new->name,ten);
    new->hp=mau;
    new->atk=cong;
    new->agi=nhanh;
    new->def=thu;
    new->point=0;
    new->team=doi;
    if(*rear==NULL)
    {
        *rear=new;
        *front=new;
    }
    else
    {
        (*rear)->next=new;
        *rear=new;
    }
}

void file_read(FILE *f,int doi,warrior **front,warrior **rear)
{
    char ten[10];
    int mau,cong,nhanh,thu,i=0;
    while(1)
    {
        fscanf(f,"%s",ten);
        if(feof(f)) break;
        fscanf(f,"%d %d %d %d",&mau,&cong,&nhanh,&thu);
        i++;
        printf("%d. %-10s %3d %3d %3d %3d\n",i,ten,mau,cong,nhanh,thu);
        enqueue(&*front,&*rear,ten,mau,cong,nhanh,thu,doi);
    }
    fclose(f);
}

int fight(int turn,char c,warrior *temp1,warrior *temp2)
{
    while(temp1->hp!=0 && temp2->hp!=0)
    {
        scanf("%c",&c);
        if(c=='0') break;
        if(temp1->atk>temp2->def)
        {
            printf("%s (%d) tan cong, %s (%d) mat %d mau !\n",temp1->name,temp1->hp,temp2->name,temp2->hp,temp1->atk - temp2->def);
            temp2->hp -= temp1->atk - temp2->def;
            temp1->point++;
            turn++;
            if(temp2->hp<=0)
            {
                temp2->hp=0;
                if(turn==1 || turn==2)
                {
                    printf("\n\t----- %s bi KNOCK OUT !!! -----\n",temp2->name);
                    temp1->point+=2;
                }
                else printf("\n\t----- %s bi loai ! -----\n",temp2->name);
                
            }
            else fight(turn,c,temp2,temp1);
        }
        else
        {
            printf("%s tan cong, %s khong mat mau !\n",temp1->name,temp2->name);
            temp1->point++;
            turn++;
            fight(turn,c,temp2,temp1);
        }
    }
    if(temp1->hp==0) return temp1->team;
    else return temp2->team;
}

void swap(rank *x,rank *y)
{
    rank TG;
    TG=*x;
    *x=*y;
    *y=TG;
}

void rank_sort(rank a[])
{
    for(int i=5;i>=0;i--)
        for(int j=0;j<=i;j++)
            if(a[j].point<a[i].point) swap(&a[j],&a[i]);
}

void queue_free(warrior *temp1,warrior *temp2)
{
    temp1=front1;
    temp2=front2;
    while(temp1)
    {
        front1=front1->next;
        free(temp1);
        temp1=front1;
    }
    while(temp2)
    {
        front2=front2->next;
        free(temp2);
        temp2=front2;
    }
}

int main()
{
    FILE *f;
    warrior *temp1,*temp2;
    rank a[6];
    int x,n=0,check;
    char c;
    f=fopen("Monphai1.txt","r");
    printf("\n\tMON PHAI 1\n");
    if(f!=NULL) file_read(f,1,&front1,&rear1);
    f=fopen("Monphai2.txt","r");
    printf("\n\tMON PHAI 2\n");
    if(f!=NULL) file_read(f,2,&front2,&rear2);
    do
    {
        printf("\n");
        printf("1. Tien hanh thi dau\n");
        printf("2. Xep hang vo si\n");
        printf("3. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                check=0;
                temp1=front1;
                temp2=front2;
                while(temp1->next!=NULL || temp2->next!=NULL)
                {
                    scanf("%c",&c);
                    if(c=='0') break;
                    if(check==1) temp1=temp1->next;
                    else if(check==2) temp2=temp2->next;
                    n++;
                    printf("\t\t  >>>>>     TRAN %d     <<<<<\n",n);
                    printf("MP%d - %s(%d,%d,%d,%d) vs MP%d - %s(%d,%d,%d,%d)\n",temp1->team,temp1->name,temp1->hp,temp1->atk,temp1->agi,temp1->def,temp2->team,temp2->name,temp2->hp,temp2->atk,temp2->agi,temp2->def);
                    if(temp1->agi>temp2->agi) check=fight(0,c,temp1,temp2);
                    else check=fight(0,c,temp2,temp1);
                }
                printf("\n\t***** Ket qua: MON PHAI %d THUA TRAN ! *****\n",check);
                break;

            case 2:
                temp1=front1;
                temp2=front2;
                x=0;
                while(temp1)
                {
                    strcpy(a[x].name,temp1->name);
                    a[x].point=temp1->point;
                    temp1=temp1->next;
                    x++;
                }
                x=3;
                while(temp2)
                {
                    strcpy(a[x].name,temp2->name);
                    a[x].point=temp2->point;
                    temp2=temp2->next;
                    x++;
                }
                rank_sort(a);
                printf("\n Ten vo si | Diem\n");
                for(x=0;x<6;x++)
                {
                    printf(" %-10s   %d\n",a[x].name,a[x].point);
                }
                break;

            case 3:
                queue_free(temp1,temp2);
                break;
        }
    }
    while(x!=3);
    return 0;
}