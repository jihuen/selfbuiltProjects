#include <stdio.h>
#include <stdlib.h>
#include <conio.h>                   //contains delay(),getch(),gotoxy(),etc.
#include <string.h>
#include <windows.h>
#include <dos.h>

int i;
char password[10]={"admin"};


struct employeeData {
	char name[20];
	int ID;
	float workHours;
	float weeklySalary;
}; 

typedef struct employeeData employeeData;
employeeData inputData;
employeeData arrayData[50];
employeeData tempData;
employeeData ableOT[50];
employeeData unableOT[50];


struct node {
	struct node *prev;
	employeeData Data;
	struct node *next;
};
typedef struct node node;

node	*head = NULL,
		*newPointer,
		*prevPointer,
		*current,
		*temp;
		
		
void gotoxy();		
void login();
void welcome();		
void menu();
int InputEmployeeCount();
void takeInput(int count);
void showResultArray(int count);
void sortList(int count);
void createList(int count);
void fillList(int count);
int deleteData(int deleteID);
node *addData(node *head);
int search(node *head, int searchID);
void displayData();
void type(const char *p);

void gotoxy(int x, int y) {	
	printf("%c[%d;%df",0x1B,y,x);
}

void login(){
	
	int i = 0;
	char x, inputPass[10];
	printf("--->developed by shahrul, faralysha, danish and muzanee");
	Sleep(2000);
	system("cls");
	type("\n\n\n\t\t\t******************** SYSTEM LOG IN ********************");
	gotoxy(26, 13);
	type("*******************************************************");
	gotoxy(17,7);
	printf("\tPlease enter the password in order to access the system...");
	gotoxy(32,10);
	printf("Password: ");	
	
	while(x != 13) {
		x = getch();
		if (x != 13 && x != 8){
			putch('*');
			inputPass[i] = x;
			i++;
		}
	}
	inputPass[i] = '\0';
	if ( strcmp(inputPass, password) == 0) {
		system("cls");
		type("\n\tLogging in...");
		system("cls");
		type("\n\t\aWelcome, Admin!");
		Sleep(100);
		system("cls");
	} 
	else {
		gotoxy(0,15);
		printf("\a\t\tIncorrect password! Please enter the correct login details..\n\t\t");
		system("pause");
		login();
	}
}

void welcome(){
	printf("\n\n\t\t\t.;*` ALI BABA CORPS HR SYSTEM `*;.");
	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	type("\n\n--->PLEASE BE NOTED UNAUTHORISED PERSONNEL WILL BE TAKEN LEGAL ACTION");
	type("\n\nDo you still wish to continue?\n");
	system("pause");
	printf("\a");
}


void menu(){
	printf("\n\t\t\t\t************** OPTIONS MENU **************");
	printf("\n\t\t\t\t1.\tShow data after arrangements.");
	printf("\n\t\t\t\t2.\tSearch data.");
	printf("\n\t\t\t\t3.\tDisplay list of OT-able and Non OT-able employees.");
	printf("\n\t\t\t\t4.\tDelete data.");
	printf("\n\t\t\t\t5.\tAdd new data.");
	printf("\n\t\t\t\t6.\tEnd program.");	
	printf("\n\t\t\t\t******************************************");
}


int InputEmployeeCount(){
	int n;
	printf("\n\nPlease enter the number of employees to input: ");
	scanf("%d", &n);
	return n;
}


void takeInput(int count){
	current = head;
	for( i = 0; i<count; i++) {
		printf("\nEnter the data for employee %d", i+1);
		printf("\n\tEmployee ID: ");
		scanf("%d", &arrayData[i].ID);
		printf("\tEmployee name: ");
		scanf("%s", &arrayData[i].name);
		printf("\tTotal working hours (past week): ");
		scanf("%f", &arrayData[i].workHours);
		/*if (current!=NULL)
			current->Data = inputData;
		current = current->next;*/
	}
}


void createList (int count) {
	if(count == 0) {
		printf("Employee records data : 0");
		return;
	}	else
	if (count == 1) {
		head  = malloc(sizeof(node));
		head->prev = NULL;
		head->next = NULL;
	} else
	if (count > 1) {
		head  = malloc(sizeof(node));
		head->prev = NULL;
		head->next = NULL;
		current = head;
		for ( i = 1; i<count; i++) {
			temp = malloc(sizeof(node));
			temp->prev = NULL;
			temp->next = NULL;
			current->next = temp;
			current= current->next;
		}
	}
}


int deleteData(int deleteID){
	int delete = 0;
	if(deleteID == head->Data.ID){
		temp = head;
		head = head->next;
		free(temp);
		delete++;
	}
	else{
		prevPointer = head;
		current = head->next;
	while (current != NULL && current->Data.ID != deleteID){
		prevPointer = current;
		current = current->next;
	}
	if (current != NULL){
		temp = current;
		prevPointer->next = current->next;
		free(temp);
		delete++;
		}
	}
	return delete;
}

node *addData(node *head){
	newPointer = malloc(sizeof(node));
	newPointer->prev = NULL;
	newPointer->next = NULL;
	printf("\n\n\t~>ADDING NEW USER: ");
	type("\n\t\t~Enter ID: ");
	scanf("%d", &newPointer->Data.ID);
	type("\t\t~Enter Name: ");
	scanf("%s", &newPointer->Data.name);
	type("\t\t~Enter Work Hours (Past Week): ");
	scanf("%f", &newPointer->Data.workHours);
	printf("\a\n\t\t==>Data has been successfully added!");
	
	int key = newPointer->Data.ID;
	if( head == NULL || key < head->Data.ID){
		newPointer->next = head;
		head = newPointer;
	}
	else {
		temp = head;
		while (temp->next != NULL && temp->next->Data.ID < key)
			temp = temp->next;
	newPointer->next = temp->next;
	temp->next = newPointer;
	newPointer->prev = temp; 
	return head;
	}
}


void sortList(int count){
	
	for (i = 0; i<count; i++){
		for (int j = 0; j < count-i-1; j++){
			if(arrayData[j].ID > arrayData[j+1].ID) {
				
				tempData.ID = arrayData[j].ID;
				strcpy(tempData.name, arrayData[j].name);
				tempData.workHours = arrayData[j].workHours;
				
				arrayData[j].ID = arrayData[j+1].ID;
				strcpy(arrayData[j].name, arrayData[j+1].name);
				arrayData[j].workHours = arrayData[j+1].workHours;
				
				
				arrayData[j+1].ID = tempData.ID;
				strcpy(arrayData[j+1].name, tempData.name);
				arrayData[j+1].workHours = tempData.workHours;
			}
		}
	}
}
	
void fillList(int count){
	current = head;
	for (i = 0; i<count; i++){
		inputData.ID = arrayData[i].ID;
		strcpy(inputData.name,arrayData[i].name);
		inputData.workHours = arrayData[i].workHours;
		if (current != NULL)
			current->Data = inputData;
		current = current->next;
	}
}
	

void displayData(){
	current = NULL;
	current = head;
	printf("\n\t\t\t .;*\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ALI BABA EMPLOYEE RECORDS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2*;.");
	printf("\n\t\t  ======================================================================");
	printf("\n\t\t\t User ID\t\tName\t\t\tWork Hours(Past week)\t\n");
	printf("\t\t  ======================================================================");
	while (current!= NULL){
		printf("\n\t\t\t %d\t\t\t%s\t\t\t%.2f", current->Data.ID, current->Data.name, current->Data.workHours);
		current = current->next;
	}
}


void showSortedOT(node *head){
	
	current = head;
	printf("\n\n\n\n\t\t\t\t.;*\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 OVERTIME ELIGIBLE EMPLOYEES \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2*;.");
	printf("\n\t\t\t =========================================================================");
	printf("\n\t\t\tEmployee ID.\t\t\tName\t\t\tWork Hours");
	printf("\n\t\t\t =========================================================================");
	while (current != NULL){
		if (current->Data.workHours < 62)
			printf("\n\t\t\tAI%d\t\t\t\t%s\t\t\t%.2f", current->Data.ID, current->Data.name, current->Data.workHours);
		current = current->next;
	}
	
	current = head;
	printf("\n\n\n\t\t\t\t.;*\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 OVERTIME INELIGIBLE EMPLOYEES \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2*;.");
	printf("\n\t\t\t =========================================================================");
	printf("\n\t\t\tEmployee ID.\t\t\tName\t\t\tWork Hours");
	printf("\n\t\t\t =========================================================================");
	while (current != NULL){
		if (current->Data.workHours >= 62)
			printf("\n\t\t\tAI%d\t\t\t\t%s\t\t\t%.2f", current->Data.ID, current->Data.name, current->Data.workHours);
		current = current->next;
	}
	return;
}


int search(node *head, int searchID) {
	current = head;
	int found = 0, deleteOption;
	while (current != NULL){
		if(current->Data.ID == searchID) {
			while (deleteOption != 1){
			system("cls");
			printf("\n\t\t\t------------------EMPLOYEE ID %d DETAILS----------------", current->Data.ID);
			printf("\n\t\t\t| \t\t\t\t\t \t\t | ");
			gotoxy(25, 4);
			printf("| Name: %s", current->Data.name);
			gotoxy(82,4);
			printf("|");
			printf("\n\t\t\t| Job Title: Retail Assistant\t\t\t\t |");
			printf("\n\t\t\t| Work Hours (Past week): %.2f\t\t\t\t |", current->Data.workHours);
			printf("\n\t\t\t| \t\t\t\t\t \t\t | ");
			printf("\n\t\t\t----------------------------------------------------------");
			printf("\n\t\t\t------------------PAYROLL FOR THE MONTH-------------------");
			printf("\n\t\t\t EARNINGS\t\tAMOUNT\t\t|DEDUCTION\t |");
			printf("\n\t\t\t----------------------------------------------------------");
			printf("\n\t\t\t|\t\t\t\t\t|\t\t |\n\t\t\t| Basic Pay:\t\t1536.54\t\t|EPF @ 9%% %.2f", current->Data.workHours*8*4*0.09);
			gotoxy(82,13);
			printf("|");
			printf("\n\t\t\t| \t\t\t\t\t| \t\t | ");
			printf("\n\t\t\t| \t\t\t\t\t| \t\t | ");
			printf("\n\t\t\t==========================================================");
			printf("\n\t\t\t  Gross Pay:\t\t%.2f\t\t|NetPay   %.2f", current->Data.workHours*8*4, current->Data.workHours*8*4*0.91 );
			printf("\n\t\t\t==========================================================");
			printf("\n\n\t\t\t1. Proceed?");
			printf("\n\t\t\t2. Delete this ID?");
			type("\n\t\t\tEnter option: ");
			scanf("%d", &deleteOption);

			found++;
			
				switch (deleteOption){
					case 2:
						deleteData(current->Data.ID);
						break;
					default:
						printf("\n\t\t\tInvalid Option!");
						Sleep(150);
						break;
				}
			}	
			//PALANG X = 25 PALANG KEDUA X = 64 PALANG LAST  X = 82 
		}
		current = current->next;
	}
	return found;
}


void type(const char *p) {
	if  (p == NULL)
		return;
	while (*p) {
		printf("%c\xDB", *p++ );
		Sleep(35);
		printf("\b \b");
		Sleep(35);
	}
	Sleep(1000);
}

void endMessage (){
	printf("\n\n\t\t\t.;*` ALI BABA CORPS HR SYSTEM `*;.");
	printf("\n\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	type("\n\n\\n\nt\t\t<(^_^)> Thank you for using Ali Baba HR System! <(^_^)> ");
}


int main(){
	
	int count = 0;
	int deleteID, addID, searchID, deleteStatus, foundStatus;
	int option;
	
	//login();
//	welcome();
	system("cls");
	count = InputEmployeeCount();
	createList(count);
	takeInput(count);
	type("\n\nYour record has been saved...\nProceeding...");
	Sleep(100);
	system("cls");
	
	if (count>1)
		sortList(count);
	fillList(count);
	
	menu();
	printf("\n\tChoose menu option: ");
	scanf("%d", &option);
	Sleep(100);
	system("cls");
	menu();
	
	while (option != 6) {
		switch (option) {
			case 1:
				type("\n\n\tData after arrangements:\n\n ");
				printf("\a");
				displayData();
				break;
			case 2:
				type("\n\tSearch ID: ");
				scanf("%d", &searchID);
				foundStatus = search(head, searchID);
				if (foundStatus == 0){
					printf("\n\t\tEmployee ID %d not found!", searchID);
				}
				
				break;
			case 3:
				showSortedOT(head);
				break;
			case 4:
				type("\n\tDeleted ID : ");
				scanf("%d", &deleteID);
				deleteStatus = deleteData(deleteID);
				if (deleteStatus != 0)
					printf("\a\t\t==>Employee ID %d has been successfully deleted!", deleteID);
				else
					printf("\a\t\t==>Employee ID %d not found!", deleteID);
				break;
			case 5:
				head = addData(head);
				break;
			default:
				printf("\a\n\t==> Invalid choice!\n\n");
				system("pause");
				system("cls");
				menu();
				break;
		}
		printf("\n\n");
		system("pause");	
		type("\n\n\n\tChoose menu option: ");
		scanf("%d", &option);	
		Sleep(100);	
		system("cls");
		menu();	
	}
	system("cls");
	endMessage();
	return 0;
}
		

