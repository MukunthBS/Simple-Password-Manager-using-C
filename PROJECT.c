#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>
char user[50],pass[50],luser[50],lpass[50];
int r=1;
struct entry
{
    char data[50];
    struct entry* next;
};
struct passgen
{
    char random[9];
    struct passgen* next;
}*first=NULL,*last=NULL;
void main()
{
    int choice1;
    printf("\n\t\t***** PASSWORD MANAGER *****\n");
    printf("\n\t1.SIGN UP\n\t2.LOGIN\n\t3.EXIT\n");
    printf("\n\tEnter Your Choice: ");
    scanf("%d",&choice1);
    if(choice1==1)
    {
        system("cls");
        FILE *file;
        printf("\n\t\t***** SIGN UP *****");
        printf("\n\n\tUsername: ");
        scanf("%s",user);
        password(pass);
        file=fopen(user,"rb");
        if(file!=NULL)
        {
            printf("\n\n\t** USERNAME ALREADY EXISTS **");
            fclose(file);
            file=NULL;
        }
        else
        {
            fclose(file);
            file=NULL;
            saveuser(user,pass);
            printf("\n\n\t** PROFILE CREATED SUCCESSFULLY **");
        }
        wait();
        system("cls");
        main();
    }
    else if(choice1==3)
    {
        printf("\n\n\n\t**Thank You for using PASSWORD MANAGER !**\n\n\t** DSA PROJECT BY \n\t\t\tMUKUNTH BS (19BCE0625) **\n\n");
        wait();
        exit(0);
    }
    else if(choice1==2)
    {
        system("cls");
        printf("\n\t\t***** LOGIN *****");
        printf("\n\n\tUsername: ");
        scanf("%s",luser);
        password(lpass);
        checkuser(luser,lpass);
    }
    else
    {
        printf("\n\n\t\t** PLEASE ENTER A VALID CHOICE. **\n");
        wait();
        system("cls");
        main();
    }
}
void login(char luser[50])
{
    printf("\n\t\t***** WELCOME, @%s ! *****",luser);
    printf("\n\n\n\t1.VIEW ENTRY\n\t2.NEW ENTRY\n\t3.EDIT ENTRY\n\t4.DELETE ENTRY\n\t5.LOGOUT\n\t6.EXIT\n\n\n\tEnter your choice: ");
    int choice;
    scanf("%d",&choice);
    if(choice==1)
    {
        view(luser);
        wait();
        wait();
        system("cls");
        login(luser);
    }
    else if(choice==2)
    {
        new_entry(luser);
        wait();
        system("cls");
        login(luser);
    }
    else if(choice==3)
    {
        edit(luser);
    }
    else if(choice==4)
    {
        del(luser);
    }
    else if(choice==5)
    {
        printf("\n\n\n\t\tLOGGING OUT...");
        wait();
        system("cls");
        main();
    }
    else if(choice==6)
    {
        printf("\n\n\n\t** Thank You for using PASSWORD MANAGER ! **\n\n\t** DSA PROJECT BY \n\t\t\tMUKUNTH BS (19BCE0625) **\n\n");
        wait();
        exit(0);
    }
    else
    {
        printf("\n\n\t\t** INVALID CHOICE **");
        wait();
        system("cls");
        login(luser);
    }
}
void password(char pass[])
{
    printf("\tPassword: ");
    char ch;
    int i=0;
    while(1)
    {
        if(i<0)
        {
            i=0;
        }
        ch=getch();
        if(ch==13)
        {
            break;
        }
        if(ch==8)
        {
            putch('\b');
            putch(NULL);
            putch('\b');
            i--;
            continue;
        }
        pass[i++]=ch;
        ch='*';
        putch(ch);
    }
    pass[i] = '\0';
}
void wait()
{
    clock_t start=clock();
    while(clock()<start+1250)
        ;
}
void new_entry(char luser[])
{
    system("cls");
    printf("\n\t\t***** NEW ENTRY *****\n");
    FILE *file;
    struct entry *site=NULL;
    struct entry *username=NULL;
    struct entry *password=NULL;

    site=(struct entry*)malloc(sizeof(struct entry));
    username=(struct entry*)malloc(sizeof(struct entry));
    password=(struct entry*)malloc(sizeof(struct entry));

    printf("\n\n\tEnter Site Name: ");
    scanf("%s",site->data);
    char conc[100];
    strcpy(conc,luser);
    strcat(conc,site->data);
    file=fopen(conc,"rb");
    if(file!=NULL)
    {
        printf("\n\n\t\t** SITE CREDENTIALS SAVED ALREADY **");
        wait();
        fclose(file);
        file=NULL;
    }
    else
    {
        printf("\n\tEnter Username: ");
        scanf("%s",username->data);

        printf("\n\t* (If you want a randomly generated password, type \"random\") *\n");
        printf("\n\tEnter Password: ");
        scanf("%s",password->data);

        char random[25]="random";

        if(!strcmp(password->data,random))
        {
            generate();
            gensave(password);
        }
        site->next=username;
        username->next=password;
        password->next=NULL;
        file=fopen(conc,"wb");
        while(site->next!=NULL)
        {
            char temp[50];
            strcpy(temp,site->next->data);
            fprintf(file,"%s ",temp);
            site=site->next;
        }
        fclose(file);
        file=NULL;
        printf("\n\t\t** SAVED SUCCESSFULLY ! **");
    }
}
void view(char luser[])
{
    system("cls");
    FILE *file;
    char sname[50],cred[50];
    int c=0;
    printf("\n\t\t***** VIEW FILE ******\n");
    printf("\n\n\tEnter the site name: ");
    scanf("%s",sname);

    char conc[100];
    strcpy(conc,luser);
    strcat(conc,sname);
    file=fopen(conc,"rb");
    if(file!=NULL)
    {

        while(fscanf(file,"%s",cred)!=EOF)
        {
            if(c==0)
            {
                printf("\n\tUsername: %s",cred);
            }
            else
            {
                printf("\n\tPassword: %s\n",cred);
            }
            c++;
        }
    }
    else
    {
        printf("\n\n\t\t** INVALID SITE NAME **\n");
        wait();
        system("cls");
        login(luser);
    }
    fclose(file);
    file=NULL;
}
void edit(char luser[])
{
    system("cls");
    char fname[50];
    printf("\n\t\t***** EDIT FILE *****\n");
    printf("\n\n\tEnter the name of site: ");
    scanf("%s",fname);
    char conc[100];
    strcpy(conc,luser);
    strcat(conc,fname);
    if(remove(conc)!=0)
    {
        printf("\n\n\t\t** NO ENTRIES FOUND **");
        wait();
        system("cls");
        login(luser);
    }
    else
    {
        FILE *file;
        struct entry *username=NULL;
        struct entry *password=NULL;

        username=(struct entry*)malloc(sizeof(struct entry));
        password=(struct entry*)malloc(sizeof(struct entry));


        printf("\n\tEnter Username: ");
        scanf("%s",username->data);

        printf("\n\t* (If you want a randomly generated password, type \"random\") *\n");
        printf("\n\tEnter Password: ");
        scanf("%s",password->data);

        char random[25]="random";

        if(!strcmp(password->data,random))
        {
            generate();
            gensave(password);
        }

        username->next=password;
        password->next=NULL;
        file=fopen(conc,"wb");
        while(username!=NULL)
        {
            char temp[50];
            strcpy(temp,username->data);
            fprintf(file,"%s ",temp);
            username=username->next;
        }
        fclose(file);
        file=NULL;
        printf("\n\t\t** SAVED SUCCESSFULLY ! **");
    }
    wait();
    system("cls");
    login(luser);
}
void saveuser(char user[],char pass[])
{
    FILE *file;
    file=fopen(user,"wb");
    fputs(pass,file);
    fclose(file);
    file=NULL;
}
void checkuser(char luser[],char lpass[])
{
    FILE *file;
    int check=0;
    file=fopen(luser,"rb");
    if(file==NULL)
    {
        check=1;
    }
    else
    {
        char cpass[50];
        fgets(cpass,50,file);
        if(strcmp(cpass,lpass))
        {
            check=1;
        }
    }
    if(check==1)
    {
        printf("\n\n\t\t** INVALID USERNAME OR PASSWORD **\n");
        wait();
        system("cls");
        main();
    }
    else
    {
        printf("\n\n\t\t** LOGGED IN SUCCESSFULLY **\n");
        wait();
        system("cls");
        login(luser);
    }
    fclose(file);
    file=NULL;
}
void del(char luser[])
{
    system("cls");
    char fname[50];
    printf("\n\t\t***** DELETE ENTRY *****\n");
    printf("\n\tEnter Site Name: ");
    scanf("%s",fname);
    char conc[100];
    strcpy(conc,luser);
    strcat(conc,fname);
    if(remove(conc)!=0)
    {
        printf("\n\n\t\t** NO ENTRIES FOUND **",fname);
        wait();
        system("cls");
    }
    else
    {
        printf("\n\n\t\t** ENTRY DELETED SUCCESSFULLY **");
        wait();
        system("cls");
    }
    login(luser);
}
void generate()
{
    int i,j;
    struct passgen *newnode=NULL;
    system("cls");
    srand((unsigned int)(time(NULL)));
    for(j=0;j<10;j++)
    {
        char pass[10];
        for(i=0;i<3;i++)
        {
            char a,b,c,temp[4];
            a='0'+(rand()%9);
            b='A'+(rand()%26);
            c='a'+(rand()%26);
            sprintf(temp,"%c%c%c",a,b,c);
            if(i==0)
                strcpy(pass,temp);
            else
                strcat(pass,temp);
        }
        newnode=(struct passgen*)malloc(sizeof(struct passgen));
        strcpy(newnode->random,pass);
        newnode->next=NULL;
        if(first==NULL)
        {
            first=newnode;
            last=first;
        }
        else
        {
            last->next=newnode;
            last=newnode;
        }
    }
}
void gensave(struct entry *a)
{
    choice:
    printf("\n\tGENERATED PASSWORD: %s\n",first->random);
    printf("\n\tWhat do you want to do?\n");
    printf("\n\t1.SAVE THIS AS PASSWORD\n\t2.VIEW ANOTHER RANDOM PASSWORD\n\t3.TYPE YOUR OWN PASSWORD\n\n\tEnter Your Choice: ");
    int cho;
    scanf("%d",&cho);
    switch(cho)
    {
        case 1:
            strcpy(a->data,first->random);
            break;
        case 2:
            system("cls");
            first=first->next;
            r+=1;
            if(r<11)
            {
                gensave(a);
            }
            else
            {
                generate();
                gensave(a);
                r=1;
            }
            break;
        case 3:
            printf("\n\n\tEnter Your Password: ");
            char typ[20];
            scanf("%s",typ);
            strcpy(a->data,typ);
            break;
        default:
            printf("\n\n\t** ENTER A VALID CHOICE **");
            wait();
            system("cls");
            goto choice;
            break;
    }
}
