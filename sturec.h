#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<math.h>
#include"visual.h"

//Structure to store student information
typedef struct student
{
	int rollno;
	char name[20];
	char class_nm[5];
	char pass[20];
}STU;

//Structure to store course information
typedef struct subject
{
	int subcode;
	char subnm[20];
	int subcredits;
	char pass[20];
}SUB;

//Structure to store student's Marks of a particular course
typedef struct stumarks
{
	int rollNo;
	int subcode;
	int marks;
}STUMARKS;

//Structure to Store a question of a Quiz
typedef struct quiz
{
	char subname[20];
	char ques[50];
	char opt1[20];
	char opt2[20];
	char opt3[20];
	char opt4[20];
	int ans;
}QUE;

STU stu;
int code=0;

//Function to add student account(called in create account fn)
void add_student()
{
	FILE *fp;
	
	fp=fopen("record.txt","ab+");
	
	if(fp==NULL)
	{
		gotoxy(2,10);
		
		printf(" Error in opening file");
		
		getch();
		
		return;
	}
	else
	{
		fflush(stdin);
		
		gotoxy(4,12);
		
		printf("Enter Roll No : ");
		
		scanf("%d",&stu.rollno);
		
		fflush(stdin);
		
		gotoxy(4,14);
		
		printf("Enter Name : ");
		
		gets(stu.name);
		
		gotoxy(4,16);
		
		printf("Enter Class : ");
		
		gets(stu.class_nm);
		
		gotoxy(4,18);
		
		printf("Password assigned...");
		
		strcpy(stu.pass,stu.name);
		
		fwrite(&stu,sizeof(STU),1,fp);
		
		gotoxy(4,19);
		
		printf("Record Successfully added...");
		
		getch();
		
		clearWindow();
	}
	fclose(fp);
	
	return;
}

//Function to add multiple student records
void create_acc()
{
	int n,i;
	
	clearWindow();
	
	print_heading(" Create Account");
	
	gotoxy(2,10);
	
	printf(" Enter number of students : ");
	
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	
		add_student();
		
	return;
}

//Function to display all student's profile
void display()
{
	clearWindow();
	
	int i=1;
	FILE *fp;
	
	fp=fopen("record.txt","rb");
	
	if(fp==NULL)
	{
		gotoxy(2,8);
	
		printf(" Error while opening file...");
		
		getch();
		
		return;
	}
	
	clearWindow();
	
	gotoxy(2,7);
	
	printf(" Student Record");
	
    while(fread(&stu,sizeof(STU),1,fp)==1)
    {
    	gotoxy(2,10+i);
    	
        printf("Roll No : %d",stu.rollno);
        
        i++;
        
        gotoxy(2,10+i);
        
        printf("Name : %s",stu.name);
        
        i++;
        
        gotoxy(2,10+i);
        
        printf("Class : %.5s",stu.class_nm);
  		
		i=i+2;  
    }
    
	fclose(fp);
	
	getch();
	
	clearWindow();
	
	return;
}

//Function to search for a student record by passing roll no as an argument
int search_stu(int rno)
{
	int flag=0;
	FILE *fp;
	
	fp=fopen("record.txt","rb");
	
	if(fp==NULL)
	
		printf(" File Not Found");
		
	else
	{
		while(fread(&stu,sizeof(STU),1,fp)==1)
		{
			if(stu.rollno==rno)
			{
				flag=1;
				
				break;
			}
		}
	}
	
	fclose(fp);
	
	return (flag==1);
}

//Function to search and display record of a student with roll no as an argument
void search_and_display(int sv)
{
	FILE *fp;
	int i=0,isFound=0;
	
	fp=fopen("record.txt","rb");
	
	if(fp==NULL)
	{
		gotoxy(2,10);
		
		printf(" File Not Found");
		
		clearWindow();
		
		return;
	}
	
	print_heading("Student Profile");
	
	while(fread(&stu,sizeof(STU),1,fp)==1)
	{
		if(stu.rollno==sv)
		{
			gotoxy(2,12+i);
			
			printf("Roll No : %d",stu.rollno);
			
			i++;
			
			gotoxy(2,12+i);
			
			printf("Name : %s",stu.name);
			
			i++;
			
			gotoxy(2,12+i);
			
			printf("Class : %.5s",stu.class_nm);
			
			i=i+2;
			
			isFound=1;
			
			break;
		}
	}
	if(isFound==0)
	{
		gotoxy(2,12);
	
		printf(" Record Not Found...");
	}
		
	fclose(fp);
	
	getch();
	
	clearWindow();
	
	return;
}

//Function to update the subject code
void prev_code()
{
	FILE *fsub;
	SUB sub;
	int cd;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		code=0;
		
		return;
	}
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
	{
		if(code<=sub.subcode)
		
			code=sub.subcode;
	}
	
	return;
}

//Function to search for a subject with subject code as an argument
char* search_sub_code(int cd)
{
	FILE *fsub;
	static char subnm[10];
	SUB sub;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		gotoxy(2,13);
		
		printf(" File Not Found...");
		
		getch();
		
		return subnm;
	}
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
	{
		if(sub.subcode==cd)
		{
			strcpy(subnm,sub.subnm);
			
			break;
		}
	}
	return subnm;
	
}

//Function to add subject
void add_subject()
{
	clearWindow();
	
	print_heading(" Add Subject");
	
	FILE *fsub;
	SUB sub;
	int n,i,scrdt,j=0,cd;
	char snm[20];
	
	gotoxy(2,10);
	
	printf(" Enter Number of Subjects : ");
	
	scanf("%d",&n);
	
	fsub=fopen("subject.txt","ab+");
	
	if(fsub==NULL)
	{
		gotoxy(2,12);
		
		printf(" Error while opening file...");
		
		clearWindow();
		
		return;
	}
	
	for(i=0;i<n;i++)
	{
		gotoxy(2,12+j);
		
		printf(" Enter Subject Name : ");
				
		fflush(stdin);
				
		gets(snm);
				
		strcpy(sub.subnm,snm);
		
		j++;
		
		gotoxy(2,12+j);
				
		printf(" Enter Subjects credits : ");
				
		scanf("%d",&scrdt);
				
		sub.subcredits=scrdt;
		
		prev_code();
		
		sub.subcode=++code;
	
		j=j+2;
		
		strcpy(sub.pass,snm);
		
		fwrite(&sub,sizeof(sub),1,fsub);
	}
	
	fclose(fsub);
	
	getch();
	
	clearWindow();
	
	return;
}

//Function to display all subjects
void display_subjects()
{
	clearWindow();
	
	FILE *fsub;
	int i=0;
	SUB sub;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		gotoxy(2,10);
	
		printf(" Error while opening file...");
		
		getch();
		
		return;
	}
	
	gotoxy(2,10);
		
	print_heading("Available Courses");
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
    {
    	gotoxy(2,12+i);
    	
        printf("Name : %s",sub.subnm);
        
        i++;
        
        gotoxy(2,12+i);
        
        printf("Credits : %d",sub.subcredits);
        
        i++;
        
        gotoxy(2,12+i);
        
        printf("Code : %d",sub.subcode);
        
        i=i+2;
	}
    fclose(fsub);
    
    getch();
    
    clearWindow();
    
    return;
}

//Function to view subject details
void view_subjects(char *subname)
{
	clearWindow();
	
	FILE *fsub;
	int i=0;
	SUB sub;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		gotoxy(2,10);
	
		printf(" Error while opening file...");
		
		getch();
		
		return;
	}
	
	gotoxy(2,10);
		
	print_heading("Course Info");
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
    {
    	if(strcmp(sub.subnm,subname)==0)
    	{
    		gotoxy(2,12);
    	
        	printf(" Name : %s",sub.subnm);
        
       	 	gotoxy(2,14);
        
        	printf(" Credits : %d",sub.subcredits);
		}
	}
    fclose(fsub);
    
    getch();
	
	clearWindow();
    
    return;
}

//Function check the subject
int search_sub(char *snm)
{
	FILE *fsub;
	SUB sub;
	int cd=0;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		gotoxy(2,10);
	
		printf(" Error while opening file...");
		
		getch();
		
		return 0;
	}
		
	while(fread(&sub,sizeof(sub),1,fsub)==1)
	{
		if(strcmp(sub.subnm,snm)==0)
		{
			cd=sub.subcode;
			
			break;
		}
	}
	fclose(fsub);
	
	return cd;
}

//Funcion to get credits
int get_credits(int subcd)
{
	FILE *fsub;
	SUB sub;
	int crd;
	
	fsub=fopen("subject.txt","rb");
	
	if(fsub==NULL)
	{
		gotoxy(2,13);
		
		printf(" File Not Found...");
		
		getch();
		
		return 0;
	}
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
	{
		if(sub.subcode==subcd)
		{
			crd=sub.subcredits;
			
			break;
		}
	}
	fclose(fsub);
	
	return crd;
}

//Function to check existence of marks
int check_rno_sub(int rno,int cd)
{
	FILE *fmrk;
	STUMARKS smrk;
	int isFound=0;
	
	fmrk=fopen("marks.txt","rb");
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno&&smrk.subcode==cd)
		{
			isFound=1;
			
			break;
		}
	}
	return (isFound==1);
}

//Function to add marks
void add_marks(char *subname)
{
	clearWindow();
	
	print_heading("Add Marks");
	
	int rno,mrk,cd;
	FILE *fmrk;
	STUMARKS smrk;
	
	fmrk=fopen("marks.txt","ab+");
	
	gotoxy(2,12);
	
	printf(" Enter Roll no : ");
	
	scanf("%d",&rno);
	
	if(search_stu(rno)==0)
	{
		gotoxy(2,15);
		
		printf(" Student Record Not Exists...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	cd=search_sub(subname);
	
	if(check_rno_sub(rno,cd)==1)
	{
		gotoxy(2,17);
		
		printf(" Record Already Exists...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	gotoxy(2,14);
	
	printf(" Enter marks : ");
	
	scanf("%d",&mrk);
	
	smrk.rollNo=rno;
	
	smrk.subcode=cd;
	
	smrk.marks=mrk;
	
	fwrite(&smrk,sizeof(smrk),1,fmrk);
	
	fclose(fmrk);
	
	gotoxy(2,17);
	
	printf(" Marks successfully added...");
	
	getch();
		
	clearWindow();
	
	return;	
}

//Function to add marks subject wise for multiple entries
void add_marks_subjectwise(char *subname)
{
	clearWindow();
	
	print_heading("Add Subjectwise Marks");
	
	int cd,rno,n,i,mrk;
	STUMARKS smrk;
	FILE *fmrk;
	
	fmrk=fopen("marks.txt","ab+");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf("File Not Found...");
		
		getch();
		
		return;
	}
	
	cd=search_sub(subname);
	
	if(cd==0)
	{
		gotoxy(2,12);
		
		printf(" Subject Not Found...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	gotoxy(2,12);
	
	printf(" Enter No. of Students : ");
	
	scanf("%d",&n);
	
	for(i=0;i<n;i++)
	{
		clearWindow();
		
		gotoxy(2,12);
		
		printf(" Enter Roll No : ");
		
		scanf("%d",&rno);
		
		if(search_stu(rno)==0)
		{
			gotoxy(2,14);
			
			printf(" Student Not Found...");
			
			getch();
		
			clearWindow();
			
			continue;
		}
		
		if(check_rno_sub(rno,cd)==1)
		{
			gotoxy(2,17);
		
			printf(" Record Already Exists...");
		
			getch();
		
			clearWindow();
		
			continue;
		}
		
		gotoxy(2,14);
		
		printf(" Enter Marks : ");
		
		scanf("%d",&mrk);
		
		smrk.rollNo=rno;
		
		smrk.subcode=code;
		
		smrk.marks=mrk;
		
		fwrite(&smrk,sizeof(smrk),1,fmrk);
		
		getch();
	}
	fclose(fmrk);
		
	clearWindow();
	
	return;
}

//Function to display marks(for student login)
void display_marks(int rno)
{
	clearWindow();
	
	print_heading("View Marks");
	
	FILE *fmrk;
	STUMARKS smrk;
	int cd,isFound=0;
	char subname[10];
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf("File Not Found...");
		
		getch();
		
		return;
	}
	
	if(search_stu(rno)==0)
	{
		gotoxy(2,12);
		
		printf(" Student Record Not Found...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	gotoxy(2,12);
	
	printf(" Enter Subject Name : ");
	
	fflush(stdin);
	
	gets(subname);
	
	cd=search_sub(subname);
	
	if(cd==0)
	{
		gotoxy(2,14);
		
		printf(" Subject Not Found...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno&&smrk.subcode==cd)
		{
			clearWindow();
			
			print_heading("View Marks");
			
			gotoxy(2,12);
			
			printf("Roll No : %d",smrk.rollNo);
			
			gotoxy(2,14);
			
			printf("Subject : %s",subname);
			
			gotoxy(2,16);
			
			printf("Marks : %d",smrk.marks);
			
			isFound=1;
			
			break;
		}
	}
	if(isFound==0)
	{
		gotoxy(2,14);
		
		printf("Record Not Found...");
	}
	fclose(fmrk);
	
	getch();
		
	clearWindow();
	
	return;
}

//Function to display marks(for faculty login)
void display_marks_t(char *subname)
{
	clearWindow();
	
	print_heading("View Marks");
	
	FILE *fmrk;
	STUMARKS smrk;
	int cd,isFound=0,rno;
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf("File Not Found...");
		
		getch();
		
		return;
	}
	
	gotoxy(2,12);
	
	printf(" Enter Roll No : ");
	
	scanf("%d",&rno);
	
	cd=search_sub(subname);
	
	if(search_stu(rno)==0)
	{
		gotoxy(2,12);
		
		printf(" Student Record Not Found...");
		
		getch();
		
		return;
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno&&smrk.subcode==cd)
		{
			clearWindow();
			
			print_heading("View Marks");
			
			gotoxy(2,12);
			
			printf("Roll No : %d",smrk.rollNo);
			
			gotoxy(2,14);
			
			printf("Subject : %s",subname);
			
			gotoxy(2,16);
			
			printf("Marks : %d",smrk.marks);
			
			isFound=1;
			
			break;
		}
	}
	if(isFound==0)
	{
		gotoxy(2,14);
		
		printf(" Record Not Found...");
	}
	fclose(fmrk);
	
	getch();
	
	clearWindow();
	
	return;
}

//Function to calculate subject average
float sub_avg(char *subname)
{
	int cd,n=0,subtot=0;
	FILE *fmrk;
	STUMARKS smrk;
	
	cd=search_sub(subname);
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf(" Record Not Found...");
		
		getch();
		
		clearWindow();
		
		return 0;
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.subcode==cd)
		{
			subtot+=smrk.marks;
			
			n++;
		}
	}
	fclose(fmrk);
	
	return ((float)subtot/(float)n);
}

//Function to add subject standard deviation
float sub_sd(char *subname)
{
	float avg=sub_avg(subname),sd=0,n=0;
	FILE *fmrk;
	STUMARKS smrk;
	int cd=search_sub(subname);
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf(" Record not found");
		
		getch();
		
		clearWindow();
		
		return 0;
	}
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.subcode==cd)
		{
			sd+=pow(smrk.marks-avg,2);
			
			n++;
		}
	}
	fclose(fmrk);
	
	return sqrt(sd/n);
}

//Function to calculate grades
char* calc_grades(int rno,char *subname)
{
	int cd;
	float subavg,subsd,limits[6];
	FILE *fmrk;
	STUMARKS smrk;
	static char grade[2];
	
	cd=search_sub(subname);
	
	subavg=sub_avg(subname);
	
	subsd=sub_sd(subname);
	
	limits[0]=subavg-(1.745*subsd);
	
	if(limits[0]<43)
	
		limits[0]=43;
		
	if(limits[0]>46)
	
		limits[0]=46;
		
	limits[1]=subavg-(1.175*subsd);
	
	if(limits[1]<47)
	
		limits[1]=47;
		
	if(limits[1]>52)
	
		limits[1]=52;
		
	limits[2]=subavg-(0.613*subsd);
	
	if(limits[2]<56)
	
		limits[2]=56;
		
	if(limits[2]>63)
	
		limits[2]=63;
		
	limits[3]=subavg-(0.05*subsd);
	
	if(limits[3]<64)
	
		limits[3]=64;
		
	if(limits[3]>73)
	
		limits[3]=73;
		
	limits[4]=subavg+(0.5836*subsd);
	
	if(limits[4]<70)
	
		limits[4]=70;
		
	if(limits[4]>82)
	
		limits[4]=82;
		
	limits[5]=subavg+(1.225*subsd);
	
	if(limits[5]<75)
	
		limits[5]=75;
		
	if(limits[5]>90)
	
		limits[5]=90;
		
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,17);
		
		printf(" File Not Found...");
		
		return grade;
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno&&smrk.subcode==cd)
		{
			if(smrk.marks>limits[5])
			
				strcpy(grade,"AA");
				
			else if(smrk.marks>limits[4])
			
				strcpy(grade,"AB");
				
			else if(smrk.marks>limits[3])
			
				strcpy(grade,"BB");
				
			else if(smrk.marks>limits[2])
			
				strcpy(grade,"BC");
				
			else if(smrk.marks>limits[1])
			
				strcpy(grade,"CC");
				
			else if(smrk.marks>limits[0])
			
				strcpy(grade,"CD");
				
			else if(smrk.marks>40)
			
				strcpy(grade,"DD");
				
			else 
				strcpy(grade,"FF");
		}
	}
	
	fclose(fmrk);
	
	return grade;
}

//Function to display result
void result(int rno)
{
	clearWindow();
	
	print_heading("Result");
	
	FILE *fmrk;
	STUMARKS smrk;
	int i=0;
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,12);
		
		printf(" Record Not Found...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno)
		{
			gotoxy(2,12+i);
		
			printf(" Subject : ");
		
			puts(search_sub_code(smrk.subcode));
		
			i++;
		
			gotoxy(2,12+i);
		
			printf(" Grade : ");
		
			puts(calc_grades(smrk.rollNo,search_sub_code(smrk.subcode)));
		
			i=i+2;
		}
	}
	fclose(fmrk);
	
	getch();
	
	clearWindow();
	
	return;
}

//Function to calculate grade point from grades
int grade_to_gp(int rno,char *subname)
{
	char grade[2];
	int pt;
	
	strcpy(grade,calc_grades(rno,subname));
	
	if(strcmp(grade,"AA")==0)
		pt=10;
		
	else if(strcmp(grade,"AB")==0)
		pt=9;
		
	else if(strcmp(grade,"BB")==0)
		pt=8;
		
	else if(strcmp(grade,"BC")==0)
		pt=7;
		
	else if(strcmp(grade,"CC")==0)
		pt=6;
		
	else if(strcmp(grade,"CD")==0)
		pt=5;
		
	else if(strcmp(grade,"DD")==0)
		pt=4;
		
	else 
		pt=0;
		
	return pt;
}

//Function to calculate cpi
float calc_cpi(int rno)
{
	FILE *fmrk;
	STUMARKS smrk;
	int tot=0,crd=0,pt;
	
	fmrk=fopen("marks.txt","rb");
	
	if(fmrk==NULL)
	{
		gotoxy(2,15);
		
		printf(" File Not Found...");
	}
	
	while(fread(&smrk,sizeof(smrk),1,fmrk)==1)
	{
		if(smrk.rollNo==rno)
		{
			pt=grade_to_gp(smrk.rollNo,search_sub_code(smrk.subcode));
			
			tot+=(pt*(get_credits(smrk.subcode)));
			
			crd+=(get_credits(smrk.subcode));
		}
	}
	fclose(fmrk);
	
	return (float)tot/crd;
}

//Function to attempt quiz(for student login)
void attempt_quiz(char *subnm)
{
	clearWindow();
	
	print_heading("MCQ Quiz");
	
	gotoxy(2,10);
	
	printf(" Course Name : ");
	
	puts(subnm);
	
	if(search_sub(subnm)==0)
	{
		gotoxy(2,13);
		
		printf("%d",search_sub(subnm));
		
		printf("   Course Not Found...");
		
		getch();
		
		return;
	}
	
	FILE *fquiz;
	QUE quiz;
	int opt,count=0;
	
	fquiz=fopen("quiz.txt","rb");
	
	if(fquiz==NULL)
	{
		gotoxy(2,13);
		
		printf(" File Not Found...");
		
		getch();
		
		clearWindow();
		
		return;
	}
	
	while(fread(&quiz,sizeof(QUE),1,fquiz)==1)
	{
		if(strcmp(quiz.subname,subnm)==0)
		{
			clearWindow();
			
			print_heading("MCQ Quiz");
			
			gotoxy(2,12);
			
			printf(" Que. ");
			
			puts(quiz.ques);
			
			gotoxy(2,14);
			
			printf(" 1. ");
			
			puts(quiz.opt1);
			
			gotoxy(2,15);
			
			printf(" 2. ");
			
			puts(quiz.opt2);
			
			gotoxy(2,16);
			
			printf(" 3. ");
			
			puts(quiz.opt3);
			
			gotoxy(2,17);
			
			printf(" 4. ");
			
			puts(quiz.opt4);
			
			gotoxy(2,19);
			
			printf(" Enter your answer : ");
			
			scanf("%d",&opt);
			
			if(opt==quiz.ans)
				count++;
		}
	}
	
	fclose(fquiz);
	
	clearWindow();
	
	gotoxy(2,11);
	
	printf(" You have scored %d marks...",count);
	
	getch();
	
	return;
}

//Function to create quiz(for faculty login)
void create_quiz(char *subnm)
{
	clearWindow();
	
	int qno,i;
	FILE *fquiz;
	QUE quiz;
	
	print_heading("Create Quiz");
	
	gotoxy(2,10);
	
	printf(" Enter No. of Questions : ");
	
	scanf("%d",&qno);
	
	fquiz=fopen("quiz.txt","ab+");
	
	while(qno--)
	{
		clearWindow();
		
		strcpy(quiz.subname,subnm);
		
		print_heading("Create Quiz");
		
		gotoxy(2,10);
		
		printf(" Enter Question : ");
		
		fflush(stdin);
		
		gets(quiz.ques);
		
		gotoxy(2,12);
		
		printf(" Options");
		
		fflush(stdin);
		
		gotoxy(2,13);
		
		printf("  1. ");
		
		gets(quiz.opt1);
		
		fflush(stdin);
		
		gotoxy(2,14);
		
		printf("  2. ");
		
		gets(quiz.opt2);
		
		fflush(stdin);
		
		gotoxy(2,15);
		
		printf("  3. ");
		
		gets(quiz.opt3);
		
		fflush(stdin);
		
		gotoxy(2,16);
		
		printf("  4. ");
		
		gets(quiz.opt4);
		
		gotoxy(2,17);
		
		printf(" Answer : ");
		
		scanf("%d",&quiz.ans);
		
		fwrite(&quiz,sizeof(quiz),1,fquiz);
	}
	fclose(fquiz);
	
	clearWindow();
		
	return;
}

//Function to take password as input
char* get_pass()
{
	static char pass[10];
	int i=0;
				
	do
	{
		pass[i]=getch();
					
		if(pass[i]!='\r'&&pass[i]!=8)
		{
			printf("*");
		}
		i++;
	}while(pass[i-1]!='\r');
	
	i--;
	
	pass[i]='\0';
	
	return pass;
}

//Function to check password of student account
int check_pass(int rno,char *pass)
{
	FILE *fp;
	STU stu;
	int check;

	fp=fopen("record.txt","rb");
	
	while(fread(&stu,sizeof(stu),1,fp)==1)
	{
		if(stu.rollno==rno)
		{
			check=strcmp(pass,stu.pass);
		}
	}
	
	return check==0;
}

//Function to check Faculty Password
int check_pass_fac(char *subname,char *pass)
{
	FILE *fsub;
	SUB sub;
	int check=1,cd;
	
	cd=search_sub(subname);
	
	fsub=fopen("subject.txt","rb");
	
	while(fread(&sub,sizeof(sub),1,fsub)==1)
	{
		if(cd==sub.subcode)
		{
			check=strcmp(pass,sub.pass);
			
			break;
		}
	}
	
	return check==0;
}
//Function to print student menu
void student_menu(int rno,char *class_n)
{
	int opt;
	char subname[10];
	
	while(1)
	{
		clearWindow();
		
		gotoxy(2,10);
	
		printf("Class : %s",class_n);
		
		gotoxy(2,11);
		
		printf("Roll No : %d",rno);
	
		gotoxy(2,13);
	
		printf(" 1.View Your Profile");
	
		gotoxy(2,15);
	
		printf(" 2.View All Courses");
	
		gotoxy(2,17);
	
		printf(" 3.View Marks");
	
		gotoxy(2,19);
	
		printf(" 4.View Subject Grade");
	
		gotoxy(2,21);
	
		printf(" 5.View Gradesheet");
	
		gotoxy(2,23);
	
		printf(" 6.View CPI");
		
		gotoxy(2,25);
		
		printf(" 7.Attempt Quiz");
		
		gotoxy(2,27);
		
		printf(" 8.Log out");
	
		gotoxy(2,30);
	
		printf(" Enter Your Choice : ");
	
		scanf("%d",&opt);
	
		if(opt>7)
			break;
		
		switch(opt)
		{
			case 1 :
				clearWindow();
				
				search_and_display(rno);break;
			
			case 2 :
				display_subjects();break;
				
			case 3 :
				display_marks(rno);break;
				
			case 4 :
				clearWindow();
				
				print_heading("View Subject Grade");
				
				gotoxy(2,12);
				
				printf(" Enter Subject Name : ");
				
				fflush(stdin);
				
				gets(subname);
				
				gotoxy(2,15);
				
				printf(" Grade : ");
				
				puts(calc_grades(rno,subname));
				
				getch();
				
				clearWindow();
				
				break;
				
			case 5 :
				result(rno);break;
				
			case 6 :
				clearWindow();
				
				print_heading("CPI");
				
				gotoxy(2,12);
				
				printf(" CPI : %f",calc_cpi(rno));
				
				getch();
				
				clearWindow();
				
				break;
			
			case 7 :
				clearWindow();
				
				print_heading("Attempt Quiz");
				
				gotoxy(2,10);
				
				printf(" Enter Subject Name : ");
				
				fflush(stdin);
				
				gets(subname);
				
				attempt_quiz(subname);
				
				break;
		}
	}
	clearWindow();
	
	return;
}

//Function to print faculty menu
void faculty_menu(char *subname)
{
	int rno,opt;
	
	while(1)
	{
		clearWindow();
		
		gotoxy(2,10);
		
		printf("Faculty Subject : %s",subname);
		
		gotoxy(2,13);
		
		printf(" 1.View Subject Info");
		
		gotoxy(2,15);
		
		printf(" 2.Add Student Marks");
		
		gotoxy(2,17);
		
		printf(" 3.Add All Students Marks");
		
		gotoxy(2,19);
		
		printf(" 4.View Marks");
		
		gotoxy(2,21);
		
		printf(" 5.View Subject Average");
		
		gotoxy(2,23);
		
		printf(" 6.View Subject Standard Deviation");
		
		gotoxy(2,25);
		
		printf(" 7.View Subject Grade");
		
		gotoxy(2,27);
		
		printf(" 8.Create Quiz");
		
		gotoxy(2,29);
		
		printf(" 9.Log out");
		
		gotoxy(2,32);
		
		printf(" Enter Your Choice : ");
		
		scanf("%d",&opt);
		
		if(opt>8)
			break;
			
		switch(opt)
		{
			case 1 :
				view_subjects(subname);
				
				getch();
				
				clearWindow();
				
				break;
				
			case 2 :
				add_marks(subname);break;
				
			case 3 :
				add_marks_subjectwise(subname);break;
				
			case 4 :
				display_marks_t(subname);break;
				
			case 5 :
				clearWindow();
				
				print_heading("Course Average Marks");
				
				gotoxy(2,12);
				
				printf("Average Marks : %f",sub_avg(subname));
				
				getch();
				
				clearWindow();
				
				break;
				
			case 6 :
				clearWindow();
				
				print_heading("Course Standard Deviation");
				
				gotoxy(2,12);
				
				printf("Standard Deviation : %f",sub_sd(subname));
				
				getch();
				
				clearWindow();
				
				break;
				
			case 7 :
				clearWindow();
				
				print_heading("Course Grades");
				
				gotoxy(2,12);
				
				printf(" Enter Roll No : ");
				
				scanf("%d",&rno);
				
				gotoxy(2,14);
				
				printf(" Course : %s",subname);
				
				gotoxy(2,16);
				
				printf(" Grade : %.2s",calc_grades(rno,subname));
				
				getch();
				
				clearWindow();
				
				break;
				
			case 8 :
				create_quiz(subname);break;
			
		}
	}
	return;
}

//Function to print admin menu
void admin_menu()
{
	int rno,opt;
	char subname[10],pass[10];
	
	while(1)
	{
		clearWindow();
		
		gotoxy(2,10);
		
		printf("Admin");
		
		gotoxy(2,12);
		
		printf(" 1.Create Student Account");
		
		gotoxy(2,14);
		
		printf(" 2.Search Student Account");
		
		gotoxy(2,16);
		
		printf(" 3.View All Student Accounts");
		
		gotoxy(2,18);
		
		printf(" 4.Add Course");
		
		gotoxy(2,20);
		
		printf(" 5.View All Courses");
		
		gotoxy(2,22);
		
		printf(" 6.Search Course");
		
		gotoxy(2,24);
		
		printf(" 7.View Result & CPI");
		
		gotoxy(2,26);
		
		printf(" 8.Log out");
		
		gotoxy(2,29);
		
		printf(" Enter Your Choice : ");
		
		scanf("%d",&opt);
		
		if(opt>7)
			break;
			
		switch(opt)
		{
			case 1 :
				create_acc();break;
				
			case 2 :
				clearWindow();
				
				print_heading("Search Student Account");
				
				gotoxy(2,12);
				
				printf(" Enter Roll No : ");
				
				scanf("%d",&rno);
				
				clearWindow();
				
				search_and_display(rno);
				
				clearWindow();
				
				break;
				
			case 3 :
				display();break;
				
			case 4 :
				add_subject();break;
				
			case 5 :
				display_subjects();break;
				
			case 6 :
				clearWindow();
				
				gotoxy(2,10);
				
				printf(" Enter Course Name : ");
				
				fflush(stdin);
				
				gets(subname);
				
				if(search_sub(subname)!=0)
				{
					gotoxy(2,13);
					
					printf(" Course Found...");
				}
				else
				{
					gotoxy(2,13);
					
					printf(" Course Not Found...");
				}
				getch();
				
				break;
				
			case 7 :
				clearWindow();
				
				print_heading("Result");
				
				gotoxy(2,10);
				
				printf(" Enter Roll No : ");
				
				scanf("%d",&rno);
				
				result(rno);
				
				getch();
				
				clearWindow();
				
				print_heading("CPI");
				
				gotoxy(2,13);
				
				printf(" CPI : %f",calc_cpi(rno));
				
				getch();
				
				clearWindow();
				
				break;
		}
	}
	clearWindow();
	
	return;
}
