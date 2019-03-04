#include <stdio.h>
#include <stdlib.h>
void mat_input(int *X,char a,int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            printf("%c[%d][%d] = ",a,i+1,j+1);
            scanf("%d",&X[i*n+j]);
        }
}

void mat_print(int *X,int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++) printf("%3d",X[i*n+j]);
        printf("\n    ");
    }
    printf("\n");
}

void mat_sum()
{
    int i,j,m,n,*A,*B,*C;
    printf("Please enter the number of rows: ");
    scanf("%d",&m);
    printf("Please enter the number of columns: ");
    scanf("%d",&n);
    A=(int *) malloc(m*n*sizeof(int));
    B=(int *) malloc(m*n*sizeof(int));
    C=(int *) malloc(m*n*sizeof(int));
    printf("Please enter the elements of matrix A:\n");
    mat_input(A,'A',m,n);
    printf("A = ");         //preview matrix A
    mat_print(A,m,n);

    printf("Please enter the elements of matrix B:\n");
    mat_input(B,'B',m,n);
    printf("B = ");         //preview matrix B
    mat_print(B,m,n);

    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {
            C[i*n+j] = A[i*n+j] + B[i*n+j];
        }
    printf("The sum of matrix A and matrix B is:\n");
    printf("C = ");
    mat_print(C,m,n);
    free(A);
    free(B);
    free(C);
}

void mat_mul()
{
    int m,n,p,i,j,a,b,*A,*B,*C;
    printf("Please enter the size of matrix A:\n");
    printf(" - Row: ");
    scanf("%d",&m);
    printf(" - Column: ");
    scanf("%d",&n);
    printf("Please enter the size of matrix B:\n");
    printf(" - Row: %d\n",n);
    printf(" - Column: ");
    scanf("%d",&p);
    A= (int *) malloc(m*n*sizeof(int));
    B= (int *) malloc(n*p*sizeof(int));
    C= (int *) calloc(m*p,sizeof(int));
    printf("Please enter the elements of matrix A:\n");
    mat_input(A,'A',m,n);
    printf("A = ");         //preview matrix A
    mat_print(A,m,n);

    printf("Please enter the elements of matrix B:\n");
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
                C[i*p+j]+=A[i*n+a]*B[b*p+j];
                a++;
                b++;
            }
        }
    printf("The multiplication of matrix A and matrix B is:\n");
    printf("C = ");
    mat_print(C,m,p);
    free(A);
    free(B);
    free(C);
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