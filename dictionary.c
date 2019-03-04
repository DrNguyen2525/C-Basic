#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree
{
    char *eng,*viet;
    struct tree *left,*right;
}
tree;

tree *root;

tree *create_node(char *p1,char *p2)
{
    tree *new=(tree *) malloc(sizeof(tree));
    new->eng=p1;
    new->viet=p2;
    new->left=NULL;
    new->right=NULL;
    return new;
}

tree *tree_insert(tree *temp,char *p1,char *p2)
{
    if(root==NULL) root=create_node(p1,p2);
    else
    {
        if(strcmp(p1,temp->eng)<0)
        {
            if(temp->left==NULL)
            {
                tree *new=create_node(p1,p2);
                temp->left=new;
                return new;
            }
            else tree_insert(temp->left,p1,p2);
        }
        else if(strcmp(p1,temp->eng)>0)
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

void inorder_print(tree *temp)
{
    if(temp!=NULL)
    {
        inorder_print(temp->left);
        printf("%s %s\n",temp->eng,temp->viet);
        inorder_print(temp->right);
    }
}

tree *search_tree(tree *temp,char *token)
{
	if(temp==NULL) return NULL;
	else if(strcmp(token,temp->eng)==0) return temp;
	else if(strcmp(token,temp->eng)>0) return search_tree(temp->right,token);
	else return search_tree(temp->left,token);
}

int translate(tree *temp,int n,char *add,char *token,char *p2,char tu1[])
{
    printf("\nENGLISH     |     VIETNAMESE\n");
    token=strtok(tu1," ");
    while(token!=NULL)
    {
        temp=search_tree(root,token);
        if(temp==NULL)
        {
            printf("%-12s No data !\n",token);
            n+=strlen(token)+1;
            if(add==NULL)
            {
                add=(char *) malloc(n*sizeof(char));
                strcpy(add,token);
            }
            else
            {
                add=(char *) realloc(add,n*sizeof(char));
                strcat(add," ");
                strcat(add,token);
            }
        }
        else
        {
            printf("%-12s %s\n",temp->eng,temp->viet);
        }
        token=strtok(NULL," ");
    }
    token=strtok(add," ");
    while(token!=NULL)
    {
        printf("\n>>>>> Tu \"%s\" chua co trong tu dien, ban co muon bo sung vao CSDL khong ?\n",token);
        printf("\t1/0: ");
        scanf("%d",&n);
        while(getchar()!='\n');
        if(n==1)
        {
            printf("Nhap nghia cua tu moi %s: ",token);
            gets(tu1);
            p2=(char *) malloc((strlen(tu1)+1)*sizeof(char));
            strcpy(p2,tu1);
            tree_insert(root,token,p2);
            printf(">>>>> Da bo sung du lieu moi vao tu dien !\n");
        }
        token=strtok(NULL," ");
    }
    return n;
}

void file_read(FILE *f,char tu1[],char tu2[],char *p1,char *p2)
{
    while(1)
    {
        fscanf(f,"%s",tu1);
        if(feof(f)) break;
        fgetc(f);
        fgets(tu2,20,f);
        tu2[strlen(tu2)-1]='\0';
        p1=(char *) malloc((strlen(tu1)+1)*sizeof(char));
        strcpy(p1,tu1);
        p2=(char *) malloc((strlen(tu2)+1)*sizeof(char));
        strcpy(p2,tu2);
        tree_insert(root,p1,p2);
    }
    fclose(f);
}

void file_write(FILE *f,tree *temp)
{
    if(temp!=NULL)
    {
        file_write(f,temp->left);
        fprintf(f,"%s %s\n",temp->eng,temp->viet);
        file_write(f,temp->right);
    }
}

void tree_free(tree *temp)
{
    if(temp!=NULL) return;
    tree_free(temp->left);
    tree_free(temp->right);
    free(temp);
    return;
}

int main()
{
    FILE *f;
    tree *temp;
    int x;
    char tu1[30],tu2[30],TG[30],*p1,*p2,*token,*add;
    f=fopen("data.txt","r");
    if(f!=NULL) file_read(f,tu1,tu2,p1,p2);
    do
    {
        printf("\n");
        printf("1. Hien thi toan bo tu dien\n");
        printf("2. Tra tu dien\n");
        printf("3. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
                printf("        DICTIONARY        \n\n");
                inorder_print(root);
                break;

            case 2:
                while(getchar()!='\n');
                while(1)
                {
                    printf("\nNhap tu can tra: ");
                    gets(tu1);
                    if(tu1[0]=='\0') break;
                    x=0;
                    while(tu1[x])
                    {
                        tu1[x]=tolower(tu1[x]);
                        x++;
                    }
                    strcpy(TG,tu1);
                    x=translate(temp,0,add,token,p2,tu1);
                    if(x==1) translate(temp,0,add,token,p2,TG);
                }
                break;

            case 3:
                f=fopen("data.txt","w");
                file_write(f,root);
                fclose(f);
                tree_free(root);
                break;
        }
    }
    while(x!=3);
    return 0;
}