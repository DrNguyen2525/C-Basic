#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector
{
    int dim;
    float *data,TB;
    struct vector *next;
}vector;

FILE *f;
vector *first;
int i;

vector *last_c()
{
    vector *temp;
    temp=first;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void insert_head(vector *new)
{
    new->next=first;
    first=new;
}

void insert_last(vector *new)
{
    vector *temp=last_c();
    new->next=temp->next;
    temp->next=new;
}

vector *vector_input(vector *new,int i,float sl)
{
    new->data[i]=sl;
    return new;
}

void file_read()
{
    vector *new;
    int j,m,n;
    float sl,sum=0;
    fscanf(f,"%d",&m);
    for(i=0;i<m;i++)
    {
        fscanf(f,"%d",&n);
        new=(vector *) malloc(sizeof(vector));
        new->data=(float *) malloc(n*sizeof(float));
        new->dim=n;
        for(j=0;j<n;j++)
        {
            fscanf(f,"%f",&sl);
            new=vector_input(new,j,sl);
            sum+=sl;
        }
        new->TB=sum/n;
        if(first==NULL) insert_head(new);
        else insert_last(new);
        printf("%.2f\n\n",new->TB);
    }
}

void min_max()
{
    float min,max;
    vector *temp;
    temp=first;
    while(temp)
    {
        min=temp->data[0];
        for(i=0;i<temp->dim;i++) if(temp->data[i]<min) min=temp->data[i];
        printf("Min = %.2f\n",min);
        max=temp->data[0];
        for(i=0;i<temp->dim;i++) if(temp->data[i]>max) max=temp->data[i];
        printf("Max = %.2f\n",max);
        temp=temp->next;
    }
}

void vector_sort()
{
    vector *temp;
    int j,m;
    float a[10];
    i=0;
    temp=first;
    while(temp)
    {
        a[i]=temp->TB;
        i++;
    }
    m=i;
}

int main()
{
    vector *new;
    int x,dim;
    float sl,sum=0;
    f=fopen("ketqua.txt","r");
    if(f!=NULL) file_read();
    do
    {
        printf("\n");
        printf("1. Bo sung vector\n");
        printf("2. Min, max, trung binh cong vector\n");
        printf("3. In danh sach trung binh cong giam dan\n");
        printf("4. Cap nhat noi dung vector\n");
        printf("5. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                while(1)
                {
                    printf("\nNhap so chieu vector: ");
                    scanf("%d",&dim);
                    if(dim==0) break;
                    new=(vector *) malloc(sizeof(vector));
                    new->data=(float *) malloc(dim*sizeof(float));
                    new->dim=dim;
                    for(i=0;i<dim;i++)
                    {
                        printf("Nhap so lieu: ");
                        scanf("%f",&sl);
                        new=vector_input(new,i,sl);
                        sum+=sl;
                    }
                    new->TB=sum/dim;
                    if(first==NULL) insert_head(new);
                    else insert_last(new);
                }
                break;

            case 2:
                min_max();
                break;

            case 3:
                break;

            case 4:
                break;
        }
    }
    while(x!=5);
    return 0;
}