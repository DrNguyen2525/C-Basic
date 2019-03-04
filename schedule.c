#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct work
{
	char *name,*content,s_time[10],e_time[10];
	int level;
	struct work *next;
}work;

typedef struct tree
{
	int date;
	struct tree *left,*right;
	struct work *list;
}tree;

tree *root;

work *last(tree *temp_t)
{
    work *temp;
    temp=temp_t->list;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void insert_head(tree *temp_t,work *new)
{
    new->next=temp_t->list;
    temp_t->list=new;
}

void insert_last(tree *temp_t,work *new)
{
    work *temp=last(temp_t);
    temp->next=new;
}

void insert_middle(work *temp,work *new)
{
    new->next=temp->next;
    temp->next=new;
}

void delete_head(tree *temp_t)
{
    work *temp=temp_t->list;
    temp_t->list=temp->next;
    free(temp);
}

void delete_last(tree *temp_t)
{
    work *temp;
    free(last(temp_t));
    temp=temp_t->list;
    while(temp->next->next!=NULL) temp=temp->next;
    temp->next=NULL;
}

void delete_middle(work *temp)
{
    work *del=temp->next;
    temp->next=temp->next->next;
    free(del);
}

void insert_list(tree *temp_t,char *ten,char start[],char end[],char *nd,int mucdo)
{
    work *temp,*new;
    new=(work *) malloc(sizeof(work));
    new->name=ten;
    strcpy(new->s_time,start);
    strcpy(new->e_time,end);
    new->content=nd;
    new->level=mucdo;
    new->next=NULL;
    temp=temp_t->list;
    if(temp==NULL) insert_head(temp_t,new);
    else
    {
        if(strcmp(start,temp->s_time)<0) insert_head(temp_t,new);   //So sanh voi phan tu dau tien
        else if(temp->next==NULL) insert_last(temp_t,new);      //Neu danh sach cong viec chi co 1 phan tu
        else
        {
            while(temp)
            {
                if(strcmp(start,temp->next->s_time)>=0)
                {
                    temp=temp->next;
                    if(temp->next==NULL)
                    {
                        insert_last(temp_t,new);
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
    }
}

tree *create_node(int ngay)
{
    tree *new=(tree *) malloc(sizeof(tree));
    new->date=ngay;
    new->left=NULL;
    new->right=NULL;
    new->list=NULL;
    return new;
}

tree *search_tree(tree *temp_t,int ngay)
{
	if(temp_t==NULL) return NULL;
	else if(ngay==temp_t->date) return temp_t;
	else if(ngay>temp_t->date) return search_tree(temp_t->right,ngay);
	else return search_tree(temp_t->left,ngay);
}

tree *insert_tree(tree *temp_t,int ngay)
{
    if(ngay<temp_t->date)
    {
        if(temp_t->left==NULL)
        {
            tree *new=create_node(ngay);
            temp_t->left=new;
            return new;
        }
        else insert_tree(temp_t->left,ngay);
    }
    else if(ngay>temp_t->date)
    {
        if(temp_t->right==NULL)
        {
            tree *new=create_node(ngay);
            temp_t->right=new;
            return new;
        }
        else insert_tree(temp_t->right,ngay);
    }
    else return temp_t;
}

void inorder_print(tree *temp_t)
{
    if(temp_t!=NULL)
    {
        inorder_print(temp_t->left);
        printf("- NGAY %d\n",temp_t->date);
        inorder_print(temp_t->right);
    }
}

void list_print(tree *temp_t)
{
    work *temp;
    temp=temp_t->list;
    printf("                                    NGAY %d\n\n",temp_t->date);
    printf("  Thoi gian  |      Ten cong viec      |            Noi dung            | Do quan trong\n");
    while(temp)
    {
        printf(" %-5s-%-5s   ",temp->s_time,temp->e_time);
        printf("%-25s ",temp->name);
        printf("%-35s   ",temp->content);
        printf("%d\n",temp->level);
        temp=temp->next;
    }
    printf("\n");
}

void date_print(tree *temp_t)
{
    if(temp_t!=NULL)
    {
        date_print(temp_t->left);
        list_print(temp_t);
        date_print(temp_t->right);
    }
}

void delete_work(int ngay,char ten[])
{
    tree *temp_t;
    work *temp;
    while(1)
    {
        printf("\nLich lam viec:\n");
        inorder_print(root);
        printf("\nNhap ngay co cong viec can xoa: ");
        scanf("%d",&ngay);
        if(ngay==0) break;
        temp_t=search_tree(root,ngay);
        if(temp_t==NULL) printf(">>>>> Ngay vua nhap khong co trong lich lam viec, vui long nhap lai !\n");
        else
        {
            while(getchar()!='\n');
            while(1)
            {
                temp=temp_t->list;
                if(temp==NULL)
                {
                    printf("\n>>>>> Lich lam viec NGAY %d trong !\n",temp_t->date);
                    break;
                }
                printf("\n");
                list_print(temp_t);
                printf("\nNhap ten cong viec can xoa: ");
                gets(ten);
                if(ten[0]=='\0') break;
                temp=temp_t->list;
                if(strcmp(ten,temp->name)==0)       //Neu cong viec nam dau danh sach
                {
                    delete_head(temp_t);
                    printf(">>>>> Da xoa cong viec vua chon khoi lich !\n");
                }
                else
                {
                    //Neu danh sach chi con 1 cong viec
                    if(temp->next==NULL) printf(">>>>> Ten cong viec vua nhap khong co trong lich lam viec, hay nhap lai !\n");
                    else
                    {
                        while(temp)
                        {
                            if(strcmp(ten,temp->next->name)==0)
                            {
                                if(temp->next->next==NULL)        //Neu cong viec nam cuoi danh sach
                                {
                                    delete_last(temp_t);
                                    printf(">>>>> Da xoa cong viec vua chon khoi lich !\n");
                                    break;
                                }
                                else
                                {
                                    delete_middle(temp);
                                    printf(">>>>> Da xoa cong viec vua chon khoi lich !\n");
                                    break;
                                }
                            }
                            else
                            {
                                temp=temp->next;
                                if(temp->next==NULL)
                                {
                                    printf(">>>>> Ten cong viec vua nhap khong co trong lich lam viec, hay nhap lai !\n");
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void list_free(tree *temp_t)
{
    work *temp=temp_t->list;
    while(temp)
    {
        temp_t->list=temp_t->list->next;
        free(temp);
        temp=temp_t->list;
    }
}

void tree_free(tree *temp_t)
{
    if(temp_t==NULL) return;
    tree_free(temp_t->left);
    tree_free(temp_t->right);
    list_free(temp_t);
    free(temp_t);
    return;
}

int main()
{
    int x,ngay,mucdo;
    char *p_ten,*p_nd,ten[50],nd[100],start[10],end[10];
    root=NULL;
    printf("\n*****   CHUONG TRINH QUAN LY LICH LAM VIEC    *****\n");
    do
    {
        printf("\n");
        printf("1. Them cong viec\n");
        printf("2. Xem lich lam viec theo ngay\n");
        printf("3. Xoa lich lam viec\n");
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
                    if(root==NULL) root=create_node(ngay);
                    while(1)
                    {
                        while(getchar()!='\n');
                        printf("Nhap ten cong viec: ");
                        gets(ten);
                        if(ten[0]=='\0') break;
                        p_ten=(char *) malloc((strlen(ten)+1)*sizeof(char));
                        strcpy(p_ten,ten);
                        printf("Nhap thoi gian thuc hien cong viec (dinh dang 24h):\n");
                        printf("- Bat dau: ");
                        gets(start);
                        printf("- Ket thuc: ");
                        gets(end);
                        printf("Noi dung cong viec: ");
                        gets(nd);
                        p_nd=(char *) malloc((strlen(nd)+1)*sizeof(char));
                        strcpy(p_nd,nd);
                        printf("Muc do quan trong: ");
                        scanf("%d",&mucdo);
                        insert_list(insert_tree(root,ngay),p_ten,start,end,p_nd,mucdo);
                        printf("\n");
                    }
                }
                break;

            case 2:
                printf("                 >>>>>>>>>>>>>>> LICH LAM VIEC <<<<<<<<<<<<<<\n\n");
                date_print(root);
                break;

            case 3:
                delete_work(ngay,ten);
                break;

            case 4:
                tree_free(root);
                break;
        }
    }
    while(x!=4);
    return 0;
}