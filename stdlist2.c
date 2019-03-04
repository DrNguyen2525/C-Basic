#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sv
{
    char num[9];
    char *name;
    char sex[4];
    float point;
    struct sv *next;
}sv;

typedef struct class
{
    char *name_c;
    struct class *next_c;
    struct sv *next_s;
}class;

int i;
class *first;

int name_loc(char name[])
{
    i=strlen(name)-1;
    while(name[i]!=' ' && i>-1) i--;
    return i+1;
}

int name_cmp(char name1[],char name2[])
{
    int j;
    char cut1[10],cut2[10];
    i=name_loc(name1);
    j=0;
    while(name1[i]!='\0')
    {
        cut1[j]=name1[i];
        i++;
        j++;
    }
    i=name_loc(name2);
    j=0;
    while(name2[i]!='\0')
    {
        cut2[j]=name2[i];
        i++;
        j++;
    }
    if(strcmp(cut1,cut2)<0) return 0;
    if(strcmp(cut1,cut2)==0)
    {
        if(strcmp(name1,name2)<0) return 0;
        else return 1;
    }
    else return 1;
}

class *last_c()
{
    class *temp;
    temp=first;
    while(temp->next_c!=NULL) temp=temp->next_c;
    return temp;
}

sv *last_s(class *lop)
{
    sv *temp;
    temp=lop->next_s;
    while(temp->next!=NULL) temp=temp->next;
    return temp;
}

void cls_insert_head(class *new)
{
    new->next_c=first;
    first=new;
}

void cls_insert_last(class *new)
{
    class *temp=last_c();
    new->next_c=temp->next_c;
    temp->next_c=new;
}

void cls_insert_middle(class *temp,class *new)
{
    new->next_c=temp->next_c;
    temp->next_c=new;
}

void sv_insert_head(class *lop,sv *new)
{
    new->next=lop->next_s;
    lop->next_s=new;
}

void sv_insert_last(class *lop,sv *new)
{
    sv *temp=last_s(lop);
    temp->next=new;
}

void sv_insert_middle(sv *temp,sv *new)
{
    new->next=temp->next;
    temp->next=new;
}

class *insert_class(char *lop)
{
    class *temp;
    i=0;
    temp=first;
    while(temp)
    {
        if(strcmp(lop,temp->name_c)==0)
        {
            i=1;
            return temp;
            break;
        }
        else
        {
            if(temp->next_c==NULL) break;
            temp=temp->next_c;
        }
    }
    if(i!=1)
    {
        temp=first;
        class *new=(class *) malloc(sizeof(class));
        new->name_c=lop;
        if(first==NULL) cls_insert_head(new);
        else
        {
            if(strcmp(new->name_c,first->name_c)<0) cls_insert_head(new);   //So sanh voi phan tu dau tien
            else
            {
                while(temp)
                {
                    if(first->next_c==NULL)             //Neu danh sach lop chi co 1 phan tu
                        if(strcmp(new->name_c,temp->name_c)>0)
                        {
                            cls_insert_last(new);
                            break;
                        }
                    if(strcmp(new->name_c,temp->next_c->name_c)>0)
                    {
                        temp=temp->next_c;
                        if(temp->next_c==NULL)
                        {
                            cls_insert_last(new);
                            break;
                        }
                    }
                    if(strcmp(new->name_c,temp->next_c->name_c)<0)
                    {
                        cls_insert_middle(temp,new);
                        break;
                    }
                }
            }
        }
        return new;
    }
}

sv *insert_sv(class *lop,char maso[],char *ten,char gioitinh[])
{
    sv *temp;
    sv *new=(sv *) malloc(sizeof(sv));
    strcpy(new->num,maso);
    new->name=ten;
    strcpy(new->sex,gioitinh);
    new->next=NULL;
    temp=lop->next_s;
    if(lop->next_s==NULL) sv_insert_head(lop,new);
    else
    {
        if(name_cmp(new->name,lop->next_s->name)==0) sv_insert_head(lop,new);      //So sanh voi phan tu dau tien
        else
        {
            while(temp)
            {
                if(lop->next_s->next==NULL)             //Neu danh sach lop chi co 1 phan tu
                    if(name_cmp(new->name,temp->name)==1)
                    {
                        sv_insert_last(lop,new);
                        break;
                    }
                if(lop->next_s->next!=NULL)
                {
                    if(name_cmp(new->name,temp->next->name)==0)
                    {
                        sv_insert_middle(temp,new);
                        break;
                    }
                    else
                    {
                        temp=temp->next;
                        if(temp->next==NULL)
                        {
                            sv_insert_last(lop,new);
                            break;
                        }
                    }
                }
            }
        }
    }
    return new;
}

void print()
{
    class *temp_c;
    sv *temp_s;
    temp_c=first;
    while(temp_c)
    {
        temp_s=temp_c->next_s;
        printf("                            LOP %s        \n\n",temp_c->name_c);
        printf("  MSSV  |           Ho va ten          | Gioi tinh | Diem Cbasic\n");
        while(temp_s)
        {
            printf("%-9s ",temp_s->num);
            printf("%-31s   ",temp_s->name);
            printf("%-3s         ",temp_s->sex );
            printf("%.2f\n",temp_s->point);
            temp_s=temp_s->next;
        }
        printf("\n");
        temp_c=temp_c->next_c;
    }
}

void point_class(char lop[])
{
    class *temp_c;
    sv *temp_s;
    float diem;
    temp_c=first;
    while(temp_c)
    {
        if(strcmp(lop,temp_c->name_c)==0)
        {
            temp_s=temp_c->next_s;
            while(temp_s)
            {
                printf("Nhap diem sinh vien %s: ",temp_s->name);
                scanf("%f",&diem);
                temp_s->point=diem;
                temp_s=temp_s->next;
            }
            break;
        }
        else
        {
            if(temp_c->next_c==NULL)
            {
                printf("Lop can cap nhap diem khong co trong danh sach !\n");
                printf("Nhan Enter de nhap lai............");
                break;
            }
            temp_c=temp_c->next_c;
        }
    }
}

void point_edit(char lop[],char ten[])
{
    float diem;
    class *temp_c;
    sv *temp_s;
    while(1)
    {
        printf("\nNhap ten lop: ");
        gets(lop);
        if(lop[0]=='\0') break;
        temp_c=first;
        while(temp_c)
        {
            if(strcmp(lop,temp_c->name_c)==0)
            {
                while(1)
                {
                    temp_s=temp_c->next_s;
                    printf("                            LOP %s        \n\n",temp_c->name_c);
                    printf("  MSSV  |           Ho va ten          | Gioi tinh | Diem Cbasic\n");
                    while(temp_s)
                    {
                        printf("%-9s ",temp_s->num);
                        printf("%-31s   ",temp_s->name);
                        printf("%-3s         ",temp_s->sex );
                        printf("%.2f\n",temp_s->point);
                        temp_s=temp_s->next;
                    }
                    printf("\n");
                    printf("\nNhap ho ten sinh vien can chinh sua diem: ");
                    gets(ten);
                    if(ten[0]=='\0') break;
                    temp_s=temp_c->next_s;
                    while(temp_s)
                    {
                        if(strcmp(ten,temp_s->name)==0)
                        {
                            printf("Nhap diem sinh vien %s: ",temp_s->name);
                            scanf("%f",&diem);
                            temp_s->point=diem;
                            break;
                        }
                        else
                        {
                            if(temp_s->next==NULL)
                            {
                                printf("Sinh vien can chinh sua diem khong co trong danh sach !\n");
                                printf("Nhan Enter de nhap lai............");
                                break;
                            }
                            temp_s=temp_s->next;
                        }
                    }
                    while(getchar()!='\n');
                }
                break;
            }
            else
            {
                if(temp_c->next_c==NULL)
                {
                    printf("Lop vua nhap khong co trong danh sach !\n");
                    printf("Nhan Enter de nhap lai............");
                    break;
                }
                temp_c=temp_c->next_c;
            }
        }
        while(getchar()!='\n');
    }
}

void list_free()
{
    class *temp_c;
    sv *temp_s;
    temp_c=first;
    while(temp_c)       //Giai phong danh sach sinh vien
    {
        temp_s=temp_c->next_s;
        while(temp_s)
        {
            temp_c->next_s=temp_c->next_s->next;
            free(temp_s);
            temp_s=temp_c->next_s;
        }
        temp_c=temp_c->next_c;
    }
    temp_c=first;
    while(temp_c)       //Giai phong danh sach lop
    {
        first=first->next_c;
        free(temp_c);
        temp_c=first;
    }
}

void file_read(FILE *f,class *lop1,char *p,char maso[],char ten[],char lop[],char gioitinh[])
{
    float diem;
    while(1)
    {
        fgets(lop,15,f);
        if(feof(f)) break;
        lop[strlen(lop)-1]='\0';
        p=(char *) malloc((strlen(lop)+1)*sizeof(char));
        strcpy(p,lop);
        lop1=insert_class(p);
        while(1)
        {
            fscanf(f,"%s %f %s ",maso,&diem,gioitinh);
            fgets(ten,50,f);
            ten[strlen(ten)-1]='\0';
            p=(char *) malloc((strlen(ten)+1)*sizeof(char));
            strcpy(p,ten);
            insert_sv(lop1,maso,p,gioitinh)->point=diem;
            if(fgetc(f)=='.')
            {
                fseek(f,+1,SEEK_CUR);
                break;
            }
            else fseek(f,-1,SEEK_CUR);
        }
    }
    fclose(f);
}

void file_write(FILE *f)
{
    class *temp_c;
    sv *temp_s;
    f=fopen("student_list.txt","w");
    temp_c=first;
    while(temp_c)
    {
        temp_s=temp_c->next_s;
        fprintf(f,"%s\n",temp_c->name_c);
        while(temp_s)
        {
            fprintf(f,"%s %.2f %s %s\n",temp_s->num,temp_s->point,temp_s->sex,temp_s->name);
            temp_s=temp_s->next;
        }
        fprintf(f,".\n");
        temp_c=temp_c->next_c;
    }
    fclose(f);
}

int main()
{
    int x;
    class *lop1;
    char *p,maso[9],ten[50],lop[15],gioitinh[4];
    FILE *f;
    f=fopen("student_list.txt","r");
    if(f!=NULL) file_read(f,lop1,p,maso,ten,lop,gioitinh);      //Nap du lieu tu file vao danh sach
    do
    {
        printf("\n");
        printf("1. Them sinh vien\n");
        printf("2. In ra danh sach sinh vien\n");
        printf("3. Cap nhat diem sinh vien theo lop\n");
        printf("4. Chinh sua diem sinh vien\n");
        printf("5. Thoat chuong trinh\n");
        printf("\n");
        scanf("%d",&x);
        while(getchar()!='\n');
        switch(x)
        {
            case 1:
                while(1)
                {
                    printf("Nhap lop sinh vien: ");
                    gets(lop);
                    if(lop[0]=='\0') break;
                    p=(char *) malloc((strlen(lop)+1)*sizeof(char));
                    strcpy(p,lop);
                    lop1=insert_class(p);
                    while(1)
                    {
                        printf("Nhap ma so sinh vien: ");
                        gets(maso);
                        if(maso[0]=='\0')
                        {
                            printf("\n");
                            break;
                        }
                        printf("Ho va ten sinh vien: ");
                        gets(ten);
                        p=(char *) malloc((strlen(ten)+1)*sizeof(char));
                        strcpy(p,ten);
                        printf("Gioi tinh: ");
                        gets(gioitinh);
                        insert_sv(lop1,maso,p,gioitinh);
                        printf("\n");
                    }
                }
                break;

            case 2:
                print();
                break;

            case 3:
                while(1)
                {
                    printf("\nNhap ten lop: ");
                    gets(lop);
                    if(lop[0]=='\0') break;
                    point_class(lop);
                    while(getchar()!='\n');
                }
                break;

            case 4:
                point_edit(lop,ten);
                break;

            case 5:
                file_write(f);
                list_free();
                break;
        }
    }
    while(x!=5);
    return 0;
}