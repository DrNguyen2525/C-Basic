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
    if(root==NULL) root=create_node(p1,p2);
    else
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
}

tree *search_tree(tree *temp,char *p)
{
	if(temp==NULL) return NULL;
	else if(strcmp(p,temp->name)==0) return temp;
	else if(strcmp(p,temp->name)>0) return search_tree(temp->right,p);
	else return search_tree(temp->left,p);
}

void inorder_print(tree *temp)
{
    if(temp!=NULL)
    {
        inorder_print(temp->left);
        printf("%-16s %s\n",temp->name,temp->pass);
        inorder_print(temp->right);
    }
}

int name_check(char name[])
{
    for(int i=0;i<strlen(name);i++)
        if(name[i]==' ')
        {
            printf("Ten dang nhap khong duoc chua dau cach, hay nhap lai !\n");
            return 0;
            break;
        }
}

int pass_check(char pass[])
{
    if(strlen(pass)<6)
    {
        printf(">>> Mat khau phai dai toi thieu 6 ki tu, hay nhap lai !\n");
        return 0;
    }
    /*else
    {
        for(int i=0;i<strlen(pass);i++)
            if(pass[i]!='_' && pass[i]!='$')
            {
                printf(">>> Mat khau chi duoc bao gom chu cai va chu so cung cac ki tu \"_\" va \"$\" !\n");
                return 0;
                break;
            }
    }*/
}

void pass_edit(tree *temp,char *p)
{
    temp->pass=p;
}

void file_read(FILE *f,char name[],char pass[],char *p1,char *p2)
{
    while(1)
    {
        fscanf(f,"%s",name);
        if(feof(f)) break;
        fscanf(f,"%s",pass);
        p1=(char *) malloc((strlen(name)+1)*sizeof(char));
        strcpy(p1,name);
        p2=(char *) malloc((strlen(pass)+1)*sizeof(char));
        strcpy(p2,pass);
        tree_insert(root,p1,p2);
    }
    fclose(f);
}

void file_write(FILE *f,tree *temp)
{
    if(temp!=NULL)
    {
        file_write(f,temp->left);
        fprintf(f,"%s %s\n",temp->name,temp->pass);
        file_write(f,temp->right);
    }
}

int main()
{
    int x;
    char name[15],pass[15],*p1,*p2;
    tree *temp;
    FILE *f;
    while(1)
    {
        x=0;
        f=fopen("pass.txt","r");
        if(f!=NULL) file_read(f,name,pass,p1,p2);
        if(root==NULL)
        {
            p1=(char *) malloc(6*sizeof(char));
            strcpy(p1,"admin");
            root=create_node(p1,p1);
        }
        do
        {
            printf("\n\t>>>>> LOGIN <<<<<\n");
            printf("\n- Username: ");
            gets(name);
            if(name[0]=='\0') exit(1);
            p1=(char *) malloc((strlen(name)+1)*sizeof(char));
            strcpy(p1,name);
            temp=search_tree(root,p1);
            if(temp==NULL) printf("Ten nguoi dung vua nhap khong co trong he thong !\n");
        }
        while(temp==NULL);

        do
        {
            printf("- Password: ");
            gets(pass);
            if(strcmp(pass,temp->pass)!=0)
            {
                x++;
                if(x<3) printf(">>> Nhap sai mat khau, hay nhap lai !\n\n");
                else printf("\n*** Ban da nhap sai mat khau 3 lan lien tiep, hay thu lai sau ! ***\n\n");
            }
        }
        while(strcmp(pass,temp->pass)!=0 && x<3);
        if(x==3) exit(1);

        printf("\n\t>>>>> Hello %s ! <<<<<\n",temp->name);
        if(strcmp(name,"admin")!=0)
        {
            do
            {
                printf("\n");
                printf("1. Doi mat khau\n");
                printf("2. Dang xuat\n");
                printf("\n");
                scanf("%d",&x);
                switch(x)
                {
                    case 1:
                        buf_clear;
                        do
                        {
                            printf("\nNhap mat khau cu: ");
                            gets(pass);
                            if(pass[0]=='\0') break;
                            if(strcmp(pass,temp->pass)!=0) printf(">>> Nhap sai mat khau, hay nhap lai !\n");
                        }
                        while(strcmp(pass,temp->pass)!=0);

                        if(strcmp(pass,temp->pass)==0)
                        {
                            do
                            {
                                printf("Nhap mat khau moi: ");
                                gets(pass);
                                if(pass[0]=='\0') break;
                                x=pass_check(pass);
                            }
                            while(x==0);
                            p2=(char *) malloc((strlen(pass)+1)*sizeof(char));
                            strcpy(p2,pass);
                            pass_edit(temp,p2);
                            printf(">>> Doi mat khau thanh cong !\n");
                        }
                        break;

                    case 2:
                        f=fopen("pass.txt","w");
                        file_write(f,root);
                        fclose(f);
                        buf_clear;
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
                printf("4. Dang xuat\n");
                printf("\n");
                scanf("%d",&x);
                switch(x)
                {
                    case 1:
                        buf_clear;
                        while(1)
                        {
                            do
                            {
                                printf("\nNhap ten nguoi dung moi: ");
                                gets(name);
                                if(name[0]=='\0') break;
                                x=name_check(name);
                            }
                            while(x==0);
                            if(name[0]=='\0') break;

                            do
                            {
                                printf("Nhap mat khau: ");
                                gets(pass);
                                if(pass[0]=='\0') break;
                                x=pass_check(pass);
                            }
                            while(x==0);
                            if(pass[0]=='\0') break;
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
                                pass_edit(temp,p2);
                            }
                        }
                        break;

                    case 3:
                        printf("\n  Username     | Password\n");
                        inorder_print(root);
                        break;

                    case 4:
                        f=fopen("pass.txt","w");
                        file_write(f,root);
                        fclose(f);
                        buf_clear;
                        break;
                }
            }
            while(x!=4);
        }
    }
    return 0;
}