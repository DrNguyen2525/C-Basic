#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buf_clear while(getchar()!='\n');
typedef struct tree
{
    char *name,*pass;
    struct tree *left,*right;
}
tree;

tree *root;

tree *create_node(char *p1,char *p2)
{
    tree *new=(tree *) malloc(sizeof(tree));
    new->name=p1;
    new->pass=p2;
    new->left=NULL;
    new->right=NULL;
    return new;
}

tree *tree_insert(tree *temp,char *p1,char *p2)
{
        if(strcmp(p1,temp->name)<0)
        {
            if(temp->left==NULL)
            {
                tree *new=create_node(p1,p2);
                temp->left=new;
                return new;
            }
            else tree_insert(temp->left,p1,p2);
        }
        else if(strcmp(p1,temp->name)>0)
        {
            if(temp->right==NULL)
            {
                tree *new=create_node(p1,p2);
                temp->right=new;
                return new;
            }
            else tree_insert(temp->right,p1,p2);
        }
}

tree *search_tree(tree *temp,char *p)
{
	if(temp==NULL) return NULL;
	else if(strcmp(p,temp->eng)==0) return temp;
	else if(strcmp(p,temp->eng)>0) return search_tree(temp->right,p);
	else return search_tree(temp->left,p);
}

void inorder_print(tree *temp)
{
    if(temp!=NULL)
    {
        inorder_print(temp->left);
        printf("%s %s\n",temp->name,temp->pass);
        inorder_print(temp->right);
    }
}

void pass_edit(tree *temp,char *p)
{

}

void file_read()
{

}

int main()
{
    int x=0;
    char name[15],pass[15],*p1,*p2;
    tree *temp;
    file_read();
    if(root==NULL)
    {
        p1=(char *) malloc(6*sizeof(char));
        strcpy(p1,"admin");
        root=create_node(p1,p1);
    }
    printf("Username: ");
    gets(name);
    printf("Password: ");
    gets(pass);
    if(strcmp(name,"admin")!=0)
    {
        do
        {
            printf("\n");
            printf("1. Doi mat khau\n");
            printf("2. Thoat chuong trinh\n");
            printf("\n");
            scanf("%d",&x);
            switch(x)
            {
                case 1:
                    do
                    {
                        printf("Nhap mat khau cu: ");
                        gets(pass);
                        if(strcmp(pass,temp->pass)!=0) printf("Nhap sai mat khau, hay nhap lai !\n");
                    }
                    while(strcmp(pass,temp->pass)!=0)
                    printf("Nhap mat khau moi: ");
                    gets(pass);
                    p2=(char *) malloc((strlen(pass)+1)*sizeof(char));
                    strcpy(p2,pass);
                    break;

                case 2:
                    break;
            }
        }
        while(x!=2);
    }
    else
    {
        do
        {
            printf("\n");
            printf("1. Them nguoi dung moi\n");
            printf("2. Doi mat khau tai khoan nguoi dung\n");
            printf("3. In danh sach nguoi dung\n");
            printf("4. Thoat chuong trinh\n");
            printf("\n");
            scanf("%d",&x);
            switch(x)
            {
                case 1:
                    buf_clear;
                    while(1)
                    {
                        printf("\nNhap ten nguoi dung moi: ");
                        gets(name);
                        if(name[0]=='\0') break;
                        printf("Nhap mat khau: ");
                        gets(pass);
                        p1=(char *) malloc((strlen(name)+1)*sizeof(char));
                        strcpy(p1,name);
                        p2=(char *) malloc((strlen(pass)+1)*sizeof(char));
                        strcpy(p2,pass);
                        tree_insert(root,p1,p2);
                    }
                    break;

                case 2:
                    while(1)
                    {
                        printf("Nhap ten nguoi dung: ");
                        gets(name);
                        if(name[0]=='\0') break;
                        p1=(char *) malloc((strlen(name)+1)*sizeof(char));
                        strcpy(p1,name);
                        temp=search_tree(root,p1);
                        if(temp==NULL) printf("Ten nguoi dung khong co trong he thong, hay nhap lai !\n");
                        else
                        {
                            printf("Nhap mat khau moi: ");
                            gets(pass);
                            p2=(char *) malloc((strlen(pass)+1)*sizeof(char));
                            strcpy(p2,pass);
                        }
                    }
                    break;

                case 3:
                    inorder_print(root);
                    break;

                case 4:
                    break;
            }
        }
        while(x!=4);
    }
    return 0;
}