#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buf_clear while(getchar()!='\n');
typedef struct fc
{
    int id,point,win,lose;
    char name[15];
    struct fc *next;
}
fc;

typedef struct stage
{
    char match[8];
    int *team;
}
stage;

fc *first;
stage *a;

void insert_head(fc *new)
{
    new->next=first;
    first=new;
}

void delete_head()
{
    fc *temp=first;
    first=temp->next;
    free(temp);
}

fc *last()
{
    fc *temp=first;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void delete_last()
{
    fc *temp=first;;
    free(last());
    while(temp->next->next!=NULL) temp=temp->next;
    temp->next=NULL;
}

void delete_middle(fc *temp)
{
    fc *del=temp->next;
    temp->next=temp->next->next;
    free(del);
}

int file_read(FILE *f)
{
    char ten[15];
    int id,diem,thang,thua,i,j,m;
    fc *new;
    fscanf(f,"%d",&m);
    for(i=0;i<m;i++)
    {
        fscanf(f,"%d ",&id);
        fgets(ten,15,f);
        ten[strlen(ten)-1]='\0';
        new=(fc *) calloc(1,sizeof(fc));
        new->id=id;
        strcpy(new->name,ten);
        insert_head(new);
    }
    a=(stage *) malloc((m-1)*sizeof(stage));
    for(i=0;i<m-1;i++)
    {
        fgets(a[i].match,8,f);
        a[i].match[strlen(a[i].match)-1]='\0';
        a[i].team=(int *) malloc(m*sizeof(int));
        for(j=0;j<m;j++) fscanf(f,"%d ",&a[i].team[j]);
    }
    return m;
}

void team_print()
{
    fc *temp;
    temp=first;
    printf(" ID |   Ten doi bong   | Diem | So ban thang | So ban thua\n");
    while(temp)
    {
        printf("%2d\t",temp->id);
        printf("%-18s",temp->name);
        printf("%d\t     ",temp->point);
        printf("%d\t\t   ",temp->win);
        printf("%d\n",temp->lose);
        temp=temp->next;
    }
    printf("\n");
}

void single_print(fc *temp)
{
    printf("%2d\t",temp->id);
    printf("%-18s",temp->name);
    printf("%d\t     ",temp->point);
    printf("%d\t\t   ",temp->win);
    printf("%d\n",temp->lose);
}

void stage_print(int m)
{
    int i,j;
    fc *temp;
    for(i=0;i<m-1;i++)
    {
        printf("%s\n",a[i].match);
        for(j=0;j<m;j++)
        {
            temp=first;
            while(temp)
            {
                if(temp->id==a[i].team[j])
                {
                    printf("%s",temp->name);
                    break;
                }
                else temp=temp->next;
            }
            if(j%2==0) printf(" - ");
            else printf("\n");
        }
        printf("\n");
    }
}

void update(int m)
{
    int i,j,x,y;
    fc *temp1,*temp2;
    for(i=0;i<m-1;i++)
    {
        printf("\nCap nhat ket qua %s:\n",a[i].match);
        printf("%s\n",a[i].match);
        for(j=0;j<m;j++)
        {
            temp1=first;
            while(temp1)
            {
                if(temp1->id==a[i].team[j])
                {
                    printf("%s - ",temp1->name);
                    break;
                }
                else temp1=temp1->next;
            }
            temp2=first;
            while(temp2)
            {
                if(temp2->id==a[i].team[j+1])
                {
                    printf("%s: ",temp2->name);
                    break;
                }
                else temp2=temp2->next;
            }
            scanf("%d %d",&x,&y);
            temp1->win=x;
            temp1->lose=y;
            temp2->win=y;
            temp2->lose=x;
            if(x>y) temp1->point+=3;
            else if(x<y) temp2->point+=3;
            else
            {
                temp1->point++;
                temp2->point++;
            }
            j++;
        }
        printf("\n\t  >>>>> Ket qua thi dau %s <<<<<\n\n",a[i].match);
        team_print();
    }
}

int team_min()
{
    int min=first->point;
    fc *temp=first;
    while(temp)
    {
        if(temp->point<min) min=temp->point;
        temp=temp->next;
    }
    return min;
}

void team_delete(fc *temp)
{
    fc *del;
    if(temp==first) delete_head();
    else if(temp->next!=NULL)
    {
        del=first;
        while(del->next!=NULL)
        {
            if(del->next->point==temp->point) delete_middle(del);
            else del=del->next;
        }
    }
    else delete_last();
}

void statistic()
{
    fc *temp;
    int min;
    printf("\t>>>>> CAC DOI CO SO DIEM THAP NHAT <<<<<\n\n");
    printf(" ID |   Ten doi bong   | Diem | So ban thang | So ban thua\n");
    temp=first;
    min=team_min();
    while(temp)
    {
        if(temp->point==min)
        {
            single_print(temp);
            team_delete(temp);
        }
        temp=temp->next;
    }
    printf("\n\t      >>>>> CAC DOI CON LAI <<<<<\n\n");
    team_print();
}

int main()
{
    int x,m;
    FILE *f;
    f=fopen("bongda.txt","r");
    if(f!=NULL) m=file_read(f);
    do
    {
        printf("\n");
        printf("1. In thong tin cac doi bong\n");
        printf("2. In lich thi dau\n");
        printf("3. Cap nhat ket qua vong dau\n");
        printf("4. Thong ke\n");
        printf("5. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                team_print();
                break;

            case 2:
                stage_print(m);
                break;

            case 3:
                update(m);
                break;

            case 4:
                statistic();
                break;
        }
    }
    while(x!=5);
    return 0;
}