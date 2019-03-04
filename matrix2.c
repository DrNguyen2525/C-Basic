#include <stdio.h>
#include <stdlib.h>
int i,j;
int  **mat_alloc(int m,int n)
{
    int **X=(int **) malloc(m*sizeof(int *));
    for(i=0;i<m;i++) X[i]=(int *) malloc(n*sizeof(int));
    return X;
}

void mat_input(int **X,char a,int m,int n)
{
    printf("Please enter the elements of matrix %c:\n",a);
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            printf("%c[%d][%d] = ",a,i+1,j+1);
            scanf("%d",&X[i][j]);
        }
}

void mat_print(int **X,int m,int n)
{
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++) printf("%3d",X[i][j]);
        printf("\n    ");
    }
    printf("\n");
}

void mat_free(int **X,int m)
{
    for(i=0;i<m;i++) free(X[i]);
    free(X);
}

void mat_sum()
{
    int m,n,**A,**B,**C;
    printf("Please enter the number of rows: ");
    scanf("%d",&m);
    printf("Please enter the number of columns: ");
    scanf("%d",&n);
    A=mat_alloc(m,n);
    B=mat_alloc(m,n);
    C=mat_alloc(m,n);

    mat_input(A,'A',m,n);
    printf("A = ");         //preview matrix A
    mat_print(A,m,n);

    mat_input(B,'B',m,n);
    printf("B = ");         //preview matrix B
    mat_print(B,m,n);

    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    printf("The sum of matrix A and matrix B is:\n");
    printf("C = ");
    mat_print(C,m,n);
    mat_free(A,m);
    mat_free(B,m);
    mat_free(C,m);
}

void mat_mul()
{
    int m,n,p,a,b,**A,**B,**C;
    printf("Please enter the size of matrix A:\n");
    printf(" - Row: ");
    scanf("%d",&m);
    printf(" - Column: ");
    scanf("%d",&n);
    printf("Please enter the size of matrix B:\n");
    printf(" - Row: %d\n",n);
    printf(" - Column: ");
    scanf("%d",&p);
    A=mat_alloc(m,n);
    B=mat_alloc(n,p);
    C=mat_alloc(m,p);

    mat_input(A,'A',m,n);
    printf("A = ");         //preview matrix A
    mat_print(A,m,n);

    mat_input(B,'B',n,p);
    printf("B = ");         //preview matrix B
    mat_print(B,n,p);
    
    for(i=0;i<m;i++)
        for(j=0;j<p;j++)
        {
            a=0;
            b=0;
            while(a<n)
            {
                C[i][j]+=A[i][a]*B[b][j];
                a++;
                b++;
            }
        }
    printf("The multiplication of matrix A and matrix B is:\n");
    printf("C = ");
    mat_print(C,m,p);
    mat_free(A,m);
    mat_free(B,n);
    mat_free(C,m);
}

int main()
{
    int x;
    do
    {
        printf("\n");
        printf("1. Plus two matrices\n");
        printf("2. Multiply two matrices\n");
        printf("3. Exit\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                mat_sum();
                break;

            case 2:
                mat_mul();
                break;
        }
    }
    while(x!=3);
    return 0;
}