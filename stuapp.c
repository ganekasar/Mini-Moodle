#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include"sturec.h"

int main()
{
	ClearConsoleToColors(17,15); //17 is for Blue and 15 is for white(screen Background)
	
	window();
	
	int opt,rno,i;
	char subnm[10],class_n[5],pass[10];
	
	SetColorAndBackground(28,15); //28 is for Red(Text Color) and 15 is for white(Text Background)
	
	while(1)
	{
		gotoxy(2,9);
		
		printf("Choose Account Type...");
		
		gotoxy(2,11);
		
		printf(" 1.Student");
		
		gotoxy(2,13);
		
		printf(" 2.Faculty");
		
		gotoxy(2,15);
		
		printf(" 3.Admin");
		
		gotoxy(2,17);
		
		printf(" 4.Exit");
		
		gotoxy(2,20);
		
		printf(" Enter your choice : ");
		
		scanf("%d",&opt);
		
		if(opt>3)
			break;
			
		switch(opt)
		{
			case 1 :
				clearWindow();
				
				print_heading("Student Login");
				
				gotoxy(2,12);
				
				printf(" Enter Class Name : ");
				
				fflush(stdin);
				
				i=0;
				
				for(i=0;i<5;i++)
				{
					scanf("%c",&class_n[i]);
					
					if(class_n[i]>=91&&class_n[i]<=122)
					
						class_n[i]-=32;
					
					if(class_n[i]<65||class_n[i]>91)
						
						break;
				}
				if(i!=5)
				{
					gotoxy(2,15);
					
					printf("  Invalid Class Name...");
					
					getch();
					
					clearWindow();
					
					break;
				}
				
				gotoxy(2,14);
				
				printf(" Roll No : ");
				
				scanf("%d",&rno);
				
				if(search_stu(rno)==0)
				{
					gotoxy(2,17);
					
					printf(" Student Record Not Found...");
					
					getch();
					
					clearWindow();
					
					break;
				}
				
				gotoxy(2,16);
				
				printf(" Password : ");
				
				strcpy(pass,get_pass());
				
				if(check_pass(rno,pass)!=1)
				{
					gotoxy(2,19);
					
					printf(" Incorrect Password...");
					
					getch();
					
					clearWindow();
					
					break;
				}
								
				getch();
				
				clearWindow();
				
				student_menu(rno,class_n);
				
				clearWindow();
				
				break;
			
			case 2 :
				clearWindow();
				
				print_heading("Faculty Login");
				
				gotoxy(2,12);
				
				printf(" Enter Course Name : ");
				
				fflush(stdin);
				
				gets(subnm);
				
				if(search_sub(subnm)==0)
				{
					gotoxy(2,15);
					
					printf(" Course Record Not Found...");
					
					getch();
					
					clearWindow();
					
					break;
				}
				
				gotoxy(2,14);
				
				printf(" Password : ");
				
				strcpy(pass,get_pass());
				
				if(check_pass_fac(subnm,pass)!=1)
				{
					gotoxy(2,19);
					
					printf(" Incorrect Password...");
					
					getch();
					
					clearWindow();
					
					break;
				}
				
				faculty_menu(subnm);
				
				clearWindow();
				
				break;
			
			case 3 :
				clearWindow();
				
				print_heading("Admin Login");
				
				gotoxy(2,13);
				
				printf(" Password : ");
				
				strcpy(pass,get_pass());
				
				if(strcmp("admin\0",pass)!=0)
				{
					gotoxy(2,16);
					
					printf(" Incorrect Password...");
					
					getch();
					
					clearWindow();
					
					break;
				}
				
				admin_menu();
				
				clearWindow();
				
				break;
		}
	}
	return 0;
}

