//INCLUDES START
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//INCLUDES END

long teacher_password = 5901634; //This password can do everything

typedef struct{
    char username[50];//The username is public and everyone can see it
    char firstname[50];//Can only be accessed by a teacher via a password
    char lastname[50]; //Can only be accessed by a teacher via a password 
    char password[50]; //Writen in binary to keep privacy
    char fathers_name[50]; //Can only be accessed by a teacher via a password
    char mothers_name[50]; //Can only be accessed by a tecaher via a password
    char class[2];//THe class the student is in, can be like so: 5A, 5B, 5C and so on
    int age; //Can only be accesed by a teacher via a password
    struct date{
        int dd; //the day they were born
        int mm; //the month they were born
        int yyyy; //the year they were born
    }doj;
}Student;



typedef struct{
    char firstname[50]; //The first name is public and anyone can see it in a file
    char lastname[50]; //the last name is public and anyone can see it in a file
    char mastering_class[5]; //this is the class that the master is mastering
    struct birth{
        int dd;
        int mm;
        int yyyy;
    }doj;
}Master;




void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (78 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s",message);
}




void headMessage(const char *message)
{
    printf("\e[2J\e[H");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############   Student Record Management System Project in C   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}



void welcomeMessage()
{
    headMessage("Arn Design.com");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =               Student Record              =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
}



void search_students(){
    FILE* filePointer;
    //We are using an int here cuz there are no boolean values in C
	int AccExist=0;
	int bufferLength = 255;
    //The word you are searching can be 100 lines or less
	char search[100];
	printf("Enter Account to be searched: ");
    //Gets the Account you want to search
	scanf("%s",search);
	char line[bufferLength];
    //Opens the file to search for the Account
	filePointer = fopen(search, "r");
	while(fgets(line, bufferLength, filePointer))
	{
		char *ptr = strstr(line, search);
		if (ptr != NULL) 
		{
            //If the search finds the Account
            //it changes the var to true
			AccExist=1;
			break;
		}
	}
	fclose(filePointer);
	if (AccExist==1)
	{
        //If the account exists it prints it out
		printf("Student Exists.\n");
	}
	else 
	{
        //If the account doesnt exist in prints out this
		printf("Student doesn't exist.\n");
	}
}



void new_master(){
    Master *master = (Master*)malloc(sizeof(Master));
    headMessage("Making a new Master object");

    //Gets first name
    printf("\nFirst name: ");
    scanf("%s", master->firstname);

    //Gets last name
    printf("Last name: ");
    scanf("%s", master->lastname);

    //Gets the class which he/she will be mastering
    printf("\nMastering Class: ");
    scanf("%s", master->mastering_class);

    //Gets birth date
    printf("Birthday (in dd/mm/yyyy format): ");
    scanf("%d/%d%d", &master->doj.dd, &master->doj.mm, &master->doj.yyyy);


    //check year
    if(master->doj.yyyy>=1900 && master->doj.yyyy<=9999)
    {
        //check month
        if(master->doj.mm>=1 && master->doj.mm<=12)
        {
            //check days
            if((master->doj.dd>=1 && master->doj.dd<=31) && (master->doj.mm==1 || master->doj.mm==3 || master->doj.mm==5 || master->doj.mm==7 || master->doj.mm==8 || master->doj.mm==10 || master->doj.mm==12))
                printf("Date is valid.\n");
            else if((master->doj.dd>=1 && master->doj.dd<=30) && (master->doj.dd==4 || master->doj.dd==6 || master->doj.dd==9 || master->doj.dd==11))
                printf("Date is valid.\n");
            else if((master->doj.dd>=1 && master->doj.dd<=28) && (master->doj.mm==2))
                printf("Date is valid.\n");
            else if(master->doj.dd==29 && master->doj.mm==2 && (master->doj.yyyy%400==0 ||(master->doj.yyyy%4==0 && master->doj.yyyy%100!=0)))
                printf("Date is valid.\n");
            else
                printf("Day is invalid.\n");
        }
        else
        {
            printf("Month is not valid.\n");
        }
    }
    else
    {
        printf("Year is not valid.\n");
    }

    FILE *fptr;
    fptr = fopen("Masters", "w");
    fprintf(fptr, "\nMaster: %s class %s\n", master->lastname, master->mastering_class);
}



void new_student(){
    //Makes a new Student and assigns as much memory as it needs
    Student *student = (Student*)malloc(sizeof(Student));
    welcomeMessage();

    //Gets the fathers name
    printf("\nFull Fathers name: ");
    scanf("%s", student->fathers_name);

    //Gets the mothers name
    printf("Full mothers name: ");
    scanf("%s", student->mothers_name);

    //Gets the first name of the new student
    printf("Students first name: ");
    scanf("%s", student->firstname);

    //Gets the last name of the new student
    printf("Students last name: ");
    scanf("%s", student->lastname);

    //Gets the age of the student
    printf("Student age: ");
    scanf("%d", &student->age);

    //The day they were born
   printf("Enter date (DD/MM/YYYY format): ");
   scanf("%d/%d/%d", &student->doj.dd, &student->doj.mm, &student->doj.yyyy);

   //check year
    if(student->doj.yyyy>=1900 && student->doj.yyyy<=9999)
    {
        //check month
        if(student->doj.mm>=1 && student->doj.mm<=12)
        {
            //check days
            if((student->doj.dd>=1 && student->doj.dd<=31) && (student->doj.mm==1 || student->doj.mm==3 || student->doj.mm==5 || student->doj.mm==7 || student->doj.mm==8 || student->doj.mm==10 || student->doj.mm==12))
                printf("Date is valid.\n");
            else if((student->doj.dd>=1 && student->doj.dd<=30) && (student->doj.dd==4 || student->doj.dd==6 || student->doj.dd==9 || student->doj.dd==11))
                printf("Date is valid.\n");
            else if((student->doj.dd>=1 && student->doj.dd<=28) && (student->doj.mm==2))
                printf("Date is valid.\n");
            else if(student->doj.dd==29 && student->doj.mm==2 && (student->doj.yyyy%400==0 ||(student->doj.yyyy%4==0 && student->doj.yyyy%100!=0)))
                printf("Date is valid.\n");
            else
                printf("Day is invalid.\n");
        }
        else
        {
            printf("Month is not valid.\n");
        }
    }
    else
    {
        printf("Year is not valid.\n");
    }


    //The student needs a username
    printf("\nWhat's gonna be your username? ");
    scanf("%s", student->username);

    //The student needs a password
    printf("Password: ");
    scanf("%s", student->password);

    //Gets the class
    printf("\nWhat class will the student be in? ");
    scanf("%s", student->class);


    //PRINTS OUT ALL OF THE STUDENTS DATA
    printf("\nAll of your data is: \n\n");
    printf("Fathers name: %s", student->fathers_name);
    printf("Mothers name: %s\n", student->mothers_name);
    printf("Students first name: %s\n", student->firstname);
    printf("Students last name: %s\n", student->lastname);
    printf("Students age: %d\n", student->age);
    printf("Students username: %s\n", student->username);
    printf("Students password: %s\n", student->password);

    

    //Creates a fptr variable for writing the students data to a file
    FILE *fptr;
    //Creates a new file 
    fptr = fopen("Students.bin", "ab");
    //Writes all the data in binary form
    fwrite(&student, sizeof(Student), 1, fptr);
    fclose(fptr);


    //Writes only the username to a file in english
    FILE *write_fptr;
    write_fptr = fopen("Usernames.txt", "a");
    fprintf(fptr,"Username: %s class %s\n",  student->username, student->class);
    fclose(write_fptr);
}



void print_students(){
    FILE *fptr;
  
    char filename[100], c; 
  
    printf("Enter the filename to open \n"); 
    scanf("%s", filename); 
  
    // Open file 
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr); 
}


//Function to enter the password
void try_password(){
    int try;
    printf("\nPassword: ");
    scanf("%d", &try);

    while(try != teacher_password){
        printf("\nPassword: ");
        scanf("%d", &try);
    }
}


void print_masters(){
    FILE *fptr;
  
    char filename[100], c; 
  
    printf("Enter the filename to open \n"); 
    scanf("%s", filename); 
  
    // Open file 
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr); 
    while (c != EOF) 
    { 
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 
  
    fclose(fptr); 
}



void menu(){
    int ch;
    headMessage("See the options below\n");
    do{
        printf("\n\n\t[1]. new student\n");
        printf("\t[2]. Search Student.\n");
        printf("\t[3]. See all students\n");
        printf("\t[4]. New Class Master\n");
        printf("\t[5]. Show Class Masters\n");
        printf("\t[0]. EXIT\n");
        printf("\tChoice> ");
        scanf("%d", &ch);
    
        switch(ch){

            case 1:
                try_password();
                new_student();
                break;

            case 2:
                try_password();
                search_students();
                break;

            case 3:
                try_password();
                print_students();
                break;

            case 4:
                try_password();
                new_master();
                break;

            case 5:
                try_password();
                print_masters();
        }
    }while(ch != 0);
}


int main(void)
{
    menu();
}
