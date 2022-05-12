#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "conio2.h"
#include "rlyres.h"

int enterchoice()
{
    int i;
    int choice;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("-");
    printf("\nSelect an option:\n1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket No\n5- View All Bookings\n6- View Train Bookings\n7- Cancel ticket\n8- Cancel train\n9- Quit\n\n");
    printf("Enter choice:");
    scanf("%d",&choice);
    return choice;
}

void add_trains()
{
    FILE *fp;
    fp=fopen("e:\\C Project Files\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]={
        {"123","BPL","GWA",2100,1500},
        {"546","BPL","DEl",3500,2240},
        {"345","HBJ","AGR",1560,1135},
        {"896","HBJ","MUM",4500,3360}
        };
        fp=fopen("e:\\C Project Files\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("File Saved Succesfully!\n");
        fclose(fp);
    }
    else
    {
        printf("File already present\n");
        fclose(fp);
    }
}

void view_trains()
{
    FILE *fp;
    int i;
    Train tr;   // Here we take train variable because we are going to handle the members of Train.
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
    for(i=1;i<=80;i++)
        printf("-");
    fp=fopen("e:\\C Project Files\\alltrains.dat","rb");
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
    }
    printf("\n\n\n");
    fclose(fp);
}

int check_train_no(char* trainno)
{
    FILE *fp;
    Train tr;
    fp=fopen("e:\\C Project Files\\alltrains.dat","rb");
    while(fread(&tr,sizeof(tr),1,fp)==1)
    {
        if(strcmp(tr.train_no,trainno)==0)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int check_mob_no(char *p_mob)
{
   if(strlen(p_mob)!=10)
        return 0;
   while(*p_mob!='\0')
   {
       if(isdigit(*p_mob)==0)
       {
        return 0;
       }
        p_mob++;
   }
   return 1;
}

Passenger *get_passenger_details()
{
    clrscr();                       //For removing old text
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter passenger name:");
    static Passenger psn;           // because this function will return the address of passenger variable
    fflush(stdin);
    fgets(psn.p_name,20,stdin);     // fgets will also add \n so we have to replace that with \0
    char *pos;
    pos=strchr(psn.p_name,'\n');
    if(pos!=NULL)
       *pos='\0';
    if(strcmp(psn.p_name,"0")==0)
    {
        textcolor(LIGHTRED);
        gotoxy(1,25);
        printf("Reservation Cancelled!");
        getch();
        textcolor(YELLOW);          //at this point we will reach at main menu
        clrscr();                   //reservationis not cleared yet from screen so we use clrscr() here
        return NULL;
    }
    // Taking input of gender
    int valid;
    gotoxy(1,2);
    printf("Enter gender(M/F):");
    do
    {
        valid=1;                    //  ydi valid = 1 rha to mtlb h ki user ne gender shi diya aur loop dobara nhi chlega
        fflush(stdin);
        scanf("%c",&psn.gender);
        if(psn.gender=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.gender!='M' && psn.gender!='F')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Gender should be M or F(in uppercase)");
            valid=0;
            getch();
            gotoxy(19,2);
            printf(" \b");
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    //Taking inputs for train no.
    gotoxy(1,3);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",psn.train_no);
        if(strcmp(psn.train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_train_no(psn.train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Train no)");
            getch();
            gotoxy(20,3);
            printf("\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(20,3);
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");

    //Taking input for class

    gotoxy(1,4);
    printf("Enter travelling class(First AC-F,Second AC-S):");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%c",&psn.p_class);
        if(psn.p_class=='0')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.p_class!='F' && psn.p_class!='S')
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Travelling Class should be F or S(in uppercase)");
            valid=0;
            getch();
            gotoxy(48,4);
            printf(" \b");
            textcolor(YELLOW);
        }
    }while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t\t");

    //Taking input for address
    gotoxy(1,5);
    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,20,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';
    if(strcmp(psn.address,"0")==0)
    {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
    }
    //Taking input for age
    printf("Enter age:");
    do
    {
        valid=1;
        fflush(stdin);
        scanf("%d",&psn.age);
        if(psn.age==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        if(psn.age<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Age should be positive");
            valid=0;
            getch();
            gotoxy(11,4);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(11,4);
            textcolor(YELLOW);
        }
    }while(valid==0);
    //Accepting mobile no
    gotoxy(1,7);
    printf("Enter mobile number:");
    do
    {
        valid=1;
        fflush(stdin);
        fgets(psn.mob_no,12,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(psn.mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid mobile number");
            getch();
            gotoxy(21,7);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(21,7);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return &psn;
}

int get_booked_ticket_count(char* train_no,char tc)   // ye function hme btayega ki particular train ke particular coach m kitte ticket book ho gye
{
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0 && pr.p_class==tc)
            count++;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}

int book_ticket(Passenger p)
{
   int ticket_count;
   ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
   if(ticket_count==2)
   {
       textcolor(LIGHTRED);
       printf("All seats in train no. %s in class %c are full\n",p.train_no,p.p_class);
       return -1;
   }
   int ticket_no=last_ticket_no()+1;
   p.ticketno=ticket_no;
   FILE *fp;
   fp=fopen("e:\\C Project Files\\allbookings.dat","ab");
   if(fp==NULL)
   {
       textcolor(LIGHTRED);
       printf("Sorry file cannot be opened");
       return -1;
   }
   fwrite(&p,sizeof(p),1,fp);
   fclose(fp);
   return ticket_no;
}

int accept_ticket_no()
{
    int valid;
    printf("Enter a valid ticket no:");
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...!");
            getch();
            textcolor(YELLOW);
            clrscr();
            return 0;
        }
        if(ticket_no<0)
        {
            valid=0;
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Ticket number should be positive");
            getch();
            gotoxy(25,1);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(25,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    return ticket_no;
}

void view_ticket(int ticket_no)
{
    Passenger pr;
    int found=0;
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("NAME:%s\nCLASS:%c\nAGE:%d\nADDRESS:%s\nTICKET NO:%d\nMOBILE NO:%s\nTRAIN NO:%s\nGENDER:%c",pr.p_name,pr.p_class,pr.age,pr.address,pr.ticketno,pr.mob_no,pr.train_no,pr.gender);
            found=1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of the ticket no %d found",ticket_no);
    }
    fclose(fp);
}


char* accept_mob_no()
{

    int valid;
    static mob_no[12];
    char*pos;
    printf("Enter valid mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,13,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid mobile number");
            getch();
            gotoxy(27,1);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(27,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}

int* get_ticket_no(char* p_mob_no)
{
    int count=0;
    int i=0;
    Passenger pr;
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened");
        return NULL;
    }
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            count++;
        }
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    int*p=(int*)malloc((count+1)*sizeof(int));
    rewind(fp);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.mob_no,p_mob_no)==0)
        {
            *(p+i)=pr.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

void view_all_tickets(char* pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nSorry! No ticket booked against this mobile number %s",pmob_no);
        textcolor(WHITE);
        printf("\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are ticket booked for mobile no %s",pmob_no);
    int i;
    gotoxy(32,4);
    textcolor(LIGHTRED);
    printf("TICKET NUMBERS\n");
    textcolor(YELLOW);
    for(i=0;i<80;i++)
        printf("-");
    for(i=0;*(pticket_no + i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\nPress any key to go back to main screen");
    textcolor(YELLOW);
    getch();
    free(pticket_no);
}

char* accept_train_no()
{
    clrscr();
    int valid;
    static char train_no[10];//YHA PR STATIC ISLIYE LE RHE H KYUKI HME ARRAY K0 RETRN KRNA H...AURARRAY TBHI REURN HOGA JB BO FXN KE BAD BHI SURVIVE KRR
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);
    printf("Enter train number:");
    do
    {
        fflush(stdin);
        scanf("%s",train_no);
        if(strcmp(train_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
        }
        valid=check_train_no(train_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid train number");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return train_no;
}

void view_bookings(char* train_no)
{
    int found=0,i;
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return;
    }
    Passenger pr;
    clrscr();
    textcolor(LIGHTRED);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=1;i<=80;i++)
        printf("-");
    int row=3;
    textcolor(YELLOW);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,row);    //IMPORTANT
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            row++;
            found=1;
        }
    }
    if(found==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("No details of the train no %s found",train_no);
    }
    textcolor(WHITE);
    printf("\nPress any key to go to main screen");
    textcolor(YELLOW);
    getch();
    fclose(fp);
}

int cancel_ticket(int ticket_no)
{
    FILE *fp1;
    fp1=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("e:\\C Project Files\\temp.dat","wb");
    Passenger pr;
    int found=0,result;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("e:\\C Project Files\\temp.dat");
    }
    else
    {
        result=remove("e:\\C Project Files\\allbookings.dat");
        if(result!=0)
            return 2;
        result=rename("e:\\C Project Files\\temp.dat","e:\\C Project Files\\allbookings.dat");
        if(result!=0)
            return 2;
    }
    return found;
}

void view_all_bookings()
{
    clrscr();
    FILE *fp;
    fp=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet!");
        return;
    }
    Passenger pr;
    int i,row=3;
    textcolor(LIGHTRED);
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE No\n");
    for(i=0;i<80;i++)
        printf("-");
    textcolor(YELLOW);
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
        gotoxy(41,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
    }
    textcolor(WHITE);
    printf("\nPress any key to go back to main screen");
    fclose(fp);
    getch();
}

int cancel_train(char* train_no)
{
    Train tr;
    int found=0,result;
    FILE *fp1;
    fp1=fopen("e:\\C Project Files\\allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("No ticket booked yet!");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("e:\\C Project Files\\allbookings.dat","wb");
    while(fread(&tr,sizeof(tr),1,fp1)==1)
    {
        if(strcmp(tr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            (fwrite(&tr,sizeof(tr),1,fp2));
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==1)
    {
        result=remove("e:\\C Project Files\\allbookings.dat");
        if(result==0)
            return 2;
        result=rename("e:\\C Project Files\\temp.dat","e:\\C Project Files\\allbookings.dat");
        if(result==0)
            return 2;
    }
    else
    {
        remove("e:\\C Project Files\\temp.dat");
    }
    return 1;
}
