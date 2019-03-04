#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct work
{
	char name[20],time_s[5],time_e[5],content[50];
	int level;
	struct work *next;
}work;

typedef struct tree
{
	int date;
	struct tree *left;
	struct tree *right;
	struct work *list;
}tree;

tree *search_tree(int ngay,tree *temp_t)
{
	if(temp_t==NULL) return NULL;
	else if(ngay==temp_t->date) return temp_t;
	else if(ngay>temp_t->date) return search_tree(ngay,temp_t->right);
	else return search_tree(ngay,temp_t->left);
}

void insert_tree(tree *root,int ngay)
{
	tree *temp_t;
    temp_t=search_tree(ngay,root);
	if(temp_t==NULL)
    {
        tree *new=(tree *) malloc(sizeof(tree));
        new->date=ngay;
        new->left=NULL;
        new->right=NULL;
	}
	else if(ngay<temp_t->date) insert_tree(temp_t->left,ngay);
	else if(ngay>temp_t->date) insert_tree(temp_t->right,ngay);
}

int main()
{
    int x,ngay;
    tree *root;
    do
    {
        printf("\n");
        printf("1. Them cong viec\n");
        printf("2. Chinh sua cong viec\n");
        printf("3. Xoa cong viec\n");
        printf("4. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                while(1)
                {
                    printf("Nhap ngay can them cong viec: ");
                    scanf("%d",&ngay);
                    if(ngay==0) break;
                    insert_tree(root,ngay);
                }
                break;

            case 2:
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