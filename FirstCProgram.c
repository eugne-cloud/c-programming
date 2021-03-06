//Include the libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

//Include Login Details
    char username[15];
    char password[12];

// Login Function Declaration
void login();

//Include Structure in student_record structure
struct student_record
{
    int id, age;
    char name[20],contact[15];
};
struct student_record rec;
struct student_record student_array[5];
FILE *fptr_student;

//setup_subject rec (structure)
struct setup_subject_record{
//Data Type Declaration for setup_subject
  char subject_code[50], subject_name[50];
  int credit_hour;
};
struct setup_subject_record subject_rec;
struct setup_subject_record subject_array[50];
FILE *fptr_subject;

//Enter Results Structure

struct enter_result{
  int id, score;
  char subject_code[50];
  float grade_point;
  int credit_hour;
};
struct enter_result result_rec;
struct enter_result result_array[50];
FILE *fptr_result;

int x=0;
char target_subject_code[50];

//Declaring a Function
void menu();
void enterstudentdetails();
void setup_subjects();
void enter_results();
int search_student_id();
void search_subject_code();
void reporting_tools();
void quit();

//Submenu Function (Reporting Tools)
void displaystudentdetails();
void displaystudentsubjects();
void displayresult();

//function for display gpa
void displaygpa();

//Declaration for submenu function
int sub_opt=1, num1=0;
char target1, no1;


//Declare a Variables
int option = 1, num=0;
char no, target;

//Login Page//
void login()
{
    printf("\n========================================");
    printf("\n WELCOME TO UOW |K|D|U| CS LOGIN PAGE\n");
    printf("========================================\n");
    printf("Username:");
    scanf("%s",username);
    printf("Password:");
    scanf("%s",password);
 
    if(strcmp(username,"kdu")==0){
        if(strcmp(password,"kdu")==0){
        printf("\nWelcome.Login Success!");
        menu();
        }

    else{
    printf("\n Wrong password!!");
    login();
}
    }
    else {
    printf("\n User doesn't exist");
    login();
    }//else
}//do while (login)


//printing main menu//
  void menu ()
  {
do{
      printf("\n===========================================");
      printf("\n Welcome to UOW |K|D|U| Campus Solutions!\n");
      printf("===========================================\n");
      printf("\t[1] Register New Student.\n");
      printf("\t[2] Setup Subjects\n");
      printf("\t[3] Enter Results\n");
      printf("\t[4] Reporting Tools\n");
      printf("\t[0] Quit\n");
      printf("===========================================\n");
      printf("\t\nPlease input your option: ");
      scanf("%d",&num);
      switch(num){
        case 1: 
        enterstudentdetails();
        break; 
        case 2: 
        setup_subjects();
        break;
        case 3:
        enter_results();
        break;
        case 4:
        reporting_tools();
        break;
        case 0:
        login();
        break;
        default:
        printf("Error/Invalid Choice\n");

      }
} while(num != 0);
  }

  //Registring new students
  //Enter Student Details Functions
  void enterstudentdetails()
{
  fptr_student = fopen("student.DAT","ab");
  printf("\t ====================================\n");
  printf("\t\t|K|D|U| REGISTRING NEW STUDENT\n");
  printf("\t ====================================\n");
  printf("Enter Student ID:");
  scanf("%d", &rec.id);

  printf("Enter Student Age:");
  scanf("%d", &rec.age);
  
  printf("Enter Student Name:");
  scanf("%s", rec.name);

  printf("Enter Student Contact Number:");
  scanf("%s", rec.contact);

  fwrite(&rec, sizeof rec, 1, fptr_student);

  fclose(fptr_student);
}
//setup subject functions
void setup_subjects()
{
  fptr_subject = fopen("subject.DAT","ab");
  printf("\t=================================\n");
  printf("\t |K|D|U| REGISTRING NEW SUBJECTS\n");
  printf("\t=================================\n");

  printf("Enter Subject Code:\n");
  scanf("%s", subject_rec.subject_code);
  
  printf("Enter Subject Name:\n");
  scanf("%s", subject_rec.subject_name);

  printf("Enter Credit Hour:\n");
  scanf("%d", &subject_rec.credit_hour);

  fwrite(&subject_rec, sizeof subject_rec, 1, fptr_subject);
  fclose(fptr_subject);
  
}
  void enter_results(){
  fptr_result = fopen("result.DAT","ab");
  printf("\t=================================\n");
  printf("\t |K|D|U| ENTER STUDENT RESULTS \n");
  printf("\t=================================\n");

 int student_id =  search_student_id();
  search_subject_code();

  printf("Enter Score: ");
  scanf("%d", &result_rec.score);
  printf("Enter Subject Credit Hour: ");
  scanf("%d", &result_rec.credit_hour);
  
  // Conversion of grades
            if ((result_rec.score>=80) && (result_rec.score <= 100))
                result_rec.grade_point = 4.0;
            
            else if ((result_rec.score>=70) && (result_rec.score<=79))
                result_rec.grade_point = 3.5;
            
            else if ((result_rec.score>=65) && (result_rec.score<=69))
                result_rec.grade_point = 3.5;

            else if ((result_rec.score>=55) && (result_rec.score<=64))
                result_rec.grade_point = 2.5;
  
            else if ((result_rec.score>=50) && (result_rec.score<=54))
                result_rec.grade_point = 2.0;
            
             else if ((result_rec.score>=40) && (result_rec.score<=49))
                result_rec.grade_point = 1.0;

            else result_rec.grade_point= 0;
            
  if (student_id != 0)
     result_rec.id = student_id;
    strcpy(result_rec.subject_code, target_subject_code);
    fwrite(&result_rec, sizeof result_rec, 1, fptr_result);
  fclose(fptr_result);
  } //close enter results


  //Search Function
  int search_student_id()
  {
  int target;
  FILE *fptr_student;
  struct student_record student_array[50];
  fptr_student = fopen("student.DAT","rb");
  int y=0,z=0, found=0;
  printf("enter student ID: ");
  scanf("%d", &target);
  do{
      fread(&student_array[y], sizeof student_array[y], 1, fptr_student);
      y++;
    }while(!feof(fptr_student));

    for(int idx=0; idx<y; idx++)
    {
         if (target == student_array[idx].id) 
         {
             printf("Name: %s\n",student_array[idx].name);
             found=1;
          }
    }
    if (found==0)
    {
        printf("Not Found/Error");
        target = 0;
    
    }
    return target;
  } // close search 

  void search_subject_code(){
  FILE *fptr_subject;
  struct setup_subject_record subject_array[50];
  fptr_subject = fopen("subject.DAT","rb");
  int y=0,z=0, found_subject=0;
  printf("Enter Subject Code: ");
  scanf("%s", target_subject_code);
  do{
      fread(&subject_array[y], sizeof subject_array[y], 1, fptr_subject);

      y++;
    }while(!feof(fptr_subject));

    for(int idx=0; idx<y; idx++)
    {
          if (strcmp(target_subject_code, subject_array[idx].subject_code)==0)
         {
             printf("Subject Name: %s\n",subject_array[idx].subject_name);
             found_subject=1;
          }
    }
    if (found_subject==0)
        printf("Not Found/Error");

  } // close search by search_subject_code

  //Reporting Tools Submenu
  void reporting_tools()
      {
    do{
      printf("\n==================================");
      printf("\n\t |K|D|U| Reporting Tools\n");
      printf("==================================\n");
      printf("\t[1] Display Student Details.\n");
      printf("\t[2] Display Student Subjects\n");
      printf("\t[3] Display Results\n");
      printf("\t[4] Display Student GPA\n");
      printf("\t[0] Return To Main Menu\n");
      printf("===================================\n");
      printf("\t\nPlease Input your option: ");
      scanf("%d",&num1);
      switch(num1){
        case 1: 
        displaystudentdetails();
        break; 
        case 2: 
        displaystudentsubjects();
        break;
        case 3:
        displayresult();
        case 4:
        displaygpa();
        break; 
        case 0:
        break;
        default:
        printf("Error/Invalid Choice\n");

      }
} while(num1 != 0);
  }

  //Each Functions For Submenu
  //Display student details
  void displaystudentdetails(){
  int y=0, x=0;
  FILE *fptr_student;
  struct student_record student_array[50];
  fptr_student = fopen("student.DAT","rb");
  do{
      fread(&student_array[y], sizeof student_array[y], 1, fptr_student);
      y++;
    }while(!feof(fptr_student));
     printf("\n=====================================");
     printf("|K|D|U| & UOW UNIVERSITY COLLEGE\n");
     printf("=======================================\n");
     printf("ID\t Name\t Age\t Contact Number\n");
     printf("---------------------------------------\n");

     for (x=0; x < y; x++){
     printf("%d\t %s\t %d\t %s\n",student_array[x].id, student_array[x].name, student_array[x].age, student_array[x].contact );


  } //close for loop
  } //close display student details
  void displaystudentsubjects(){
  int y=0, x=0;
  FILE *fptr_subject;
  struct setup_subject_record subject_array[50];
  fptr_subject = fopen("subject.DAT","rb");
  do{
      fread(&subject_array[y], sizeof subject_array[y], 1, fptr_subject);
      y++;
    }while(!feof(fptr_subject));
    fclose(fptr_subject);
     printf("\n=====================================");
     printf("\n\t\t\t|K|D|U| STUDENT DATABASE\n");
     printf("=======================================\n");("\n------------------------------------------------------");
     printf("Subject Code\t \tSubject Name\t Credit Hour\t");
     printf("------------------------------------------------------\n");

     for (x=0; x < y; x++){
     printf("%s\t %s\t %d\n",subject_array[x].subject_code, subject_array[x].subject_name, subject_array[x].credit_hour);

  }//close for loop (Display Subject)
  }//close curly bracket for result

  //display_student_result submenu
  void displayresult(){
  int y=0, x=0;
  FILE *fptr_result;
  struct enter_result result_array[50];
  fptr_result = fopen("result.DAT","rb");
  do{
      fread(&result_array[y], sizeof result_array[y], 1, fptr_result);
      y++;
    }while(!feof(fptr_result));
     printf("\n=====================================");
     printf("\n\t|K|D|U| & UOW EXAM TRANSCRIPT\n");
     printf("=====================================\n");
     printf("\n---------------------------------------------------\n");
     printf("Student ID\t \tSubject Code\t Credit Hour\t Grade Point\t Score\n");
     printf("------------------------------------------------------\n");

     for (x=0; x < y; x++){
     printf("\t%d\t \t\t%s\t \t\t%d\t \t%f\t \t%d\n",result_array[x].id, result_array[x].subject_code, result_array[x].credit_hour, result_array[x].grade_point, result_array[x].score);
  }//close for loop display result
  }//close void display_result

  //Display GPA Function Call
  void displaygpa(){
    int y=0, x=0, target=0;
    float t_gpoint=0, t_chour=0, total_gpoint=0;
  FILE *fptr_result;
  struct enter_result result_array[50];
  fptr_result = fopen("result.DAT","rb");
  printf("enter student ID: ");
  scanf("%d", &target);
  do{
      fread(&result_array[y], sizeof result_array[y], 1, fptr_result);
      y++;
    }while(!feof(fptr_result));
     printf("\n=====================================");
     printf("\n\t|K|D|U| & UOW STUDENT GPA/FINAL\n");
     printf("=====================================\n");
     printf("\n------------------------------------------------------\n");
     printf("Student ID\t \tSubject Code\t Credit Hour\t Score\n");
     printf("------------------------------------------------------\n");

     for (x=0; x < y; x++){
     if (target == result_array[x].id) 
     printf("\t%d\t \t\t%s\t \t%f\t \t%d\n",result_array[x].id, result_array[x].subject_code, result_array[x].grade_point, result_array[x].score);

     // Conversion of grades
            if ((result_array[x].score>=80) && (result_array[x].score <= 100))
                result_array[x].grade_point = 4.0;
            
            else if ((result_array[x].score>=70) && (result_array[x].score<=79))
                result_array[x].grade_point = 3.5;
            
            else if ((result_array[x].score>=65) && (result_array[x].score<=69))
                result_array[x].grade_point = 3.0;

            else if ((result_array[x].score>=55) && (result_array[x].score<=64))
                result_array[x].grade_point = 2.5;
  
            else if ((result_array[x].score>=50) && (result_array[x].score<=54))
                result_array[x].grade_point = 2.0;

            else if ((result_array[x].score>=40) && (result_array[x].score<=49))
                result_array[x].grade_point = 1.0;

            else result_array[x].grade_point= 0;
      
            //calculation
                   
            t_gpoint += result_array[x].grade_point * result_array[x].credit_hour;
            t_chour += result_array[x].credit_hour;


            //GPA Calculation
            
  } //close for loop
   printf("Total Grade Point: %f\n", t_gpoint);
   printf("Total Credit Hour: %f\n", t_chour);


   total_gpoint= t_gpoint/t_chour;
   printf("Your GPA IS:%f\n", total_gpoint);
  }//close void results
  
  //INT MAIN FUNC()
  int main (){
    login();
  return 0;
  }
  

