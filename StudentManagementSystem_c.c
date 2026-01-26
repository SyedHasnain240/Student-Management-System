#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

FILE *fptr;

struct Student{
    int id;
    char name[20];
    float marks;
    char grade;
    char result[10];
};

struct Student s[MAX];

void readRecord(){

    int i=0;

    fptr = fopen("SampleRecord.txt", "a");
 
    while (1)
    {
        printf("\nEnter the Details of Student");
        if(i>0) printf("\n         Or\nPress 999 to exit");

        printf("\nStudent ID: ");
        scanf("%d", &s[i].id);

        if (s[i].id==999) break;

        printf("Student Name: ");
        scanf(" "); // consume leftover newline
        fgets(s[i].name, sizeof(s[i].name), stdin);

        // remove trailing newline if exists
        s[i].name[strcspn(s[i].name, "\n")] = 0;


        printf("Student Marks: ");
        scanf("%f", &s[i].marks);

        if (s[i].marks > 100 || s[i].marks < 0) {
            printf("\nStudent Marks should be between 0-100: ");
            scanf("%f", &s[i].marks);
        }
            
        if(s[i].marks > 90) s[i].grade = 'A';
        else if(s[i].marks > 80) s[i].grade = 'B';
        else if(s[i].marks > 70) s[i].grade = 'C';
        else if(s[i].marks > 60) s[i].grade = 'D';
        else if(s[i].marks > 50) s[i].grade = 'E';
        else s[i].grade = 'F';

        if(s[i].grade=='F') strcpy(s[i].result, "Fail");
        else strcpy(s[i].result, "Pass");

        fprintf(fptr, "%d | %s | %f | %c | %s\n", s[i].id, s[i].name, s[i].marks, s[i].grade, s[i].result);

        if (i == 0) {   // first iteration (recommended)
            char yORn;
            printf("Want to Continue adding Student Record? (y/n): ");
            scanf(" %c", &yORn);   // note the space before %c

            if (yORn != 'y' && yORn != 'Y')
                break;
        }

        i++;
    }
    
    fclose(fptr);
}

void displayRecord(){

    fptr = fopen("SampleRecord.txt", "r");

    if (fptr == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n---Students Record---\n\n");
    printf("ID | Name | Marks | Grade | Result\n");
    printf("-----------------------------------\n");


    int i = 0;

    while(i<MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s", &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5){

        i++;
    }

    int j=0;
    while (j<i)
    {

        printf("%d | %s | %.2f | %c | %s \n", s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);

        j++;
    }
    

    fclose(fptr);
}

void searchByName(){

    fptr = fopen("SampleRecord.txt", "r");

    if (fptr == NULL) {
        printf("No records found.\n");
        return;
    }


    printf("\nEnter Student Name to Search: ");
    char search[15];
    // fgets(search, sizeof(search), stdin);
    scanf("%s", search);

    printf("\n");

    int i = 0;
    while(i<MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s", &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5){
        i++;
    }

    int j=0;
    while (j<i)
    {
        char *result;

        result = strstr(s[j].name, search); 
        

        if(result != NULL) 
            printf("%d | %s | %f | %c | %s\n", s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);

        j++;
    }

    fclose(fptr);
    
}


void searchById(){

    fptr = fopen("SampleRecord.txt", "r");

    if (fptr == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nEnter Student ID to Search: ");
    char search[15];
    // fgets(search, sizeof(search), stdin);
    scanf("%s", search);

    printf("\n");

    int i = 0;
    while(i<MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s", &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5){
        i++;
    }

    int j=0;
    while (j<i)
    {
        char *result;

        char idStr[15];
        sprintf(idStr, "%d", s[j].id);
        result = strstr(idStr, search);


        if(result != NULL) 
            printf("%d | %s | %f | %c | %s\n", s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);
        j++;
    }

    fclose(fptr);
}

void searchRecord(){

    printf("\nChoose Search Method:\n");
    printf("1. Search By Name\n");
    printf("2. Search By ID\n\n");

    printf("Enter a number (1-2): ");
    int ch;
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        searchByName();
        break;
    
    case 2:
        searchById();
        break;
    
    default:
        printf("Invalid choice! \n");
        searchRecord();
        break;
    }
    

}

void deleteRecord(){

    FILE *fptr, *temp;
    struct Student stemp;
    int delId;
    int found = 0;
    
    searchByName();

    // Ask which record to delete
    printf("\nEnter the student ID which you want to delete: ");
    scanf("%d", &delId);

    // Open original file for reading
    fptr = fopen("SampleRecord.txt", "r");
    if (!fptr) {
        printf("File not found!\n");
        return;
    }

    // Open temporary file for writing
    temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Unable to create temp file!\n");
        fclose(fptr);
        return;
    }

    // Read each record and copy to temp if it does NOT match the ID
    while (fscanf(fptr, "%d | %49[^|] | %f | %c | %4s",
                  &stemp.id, stemp.name, &stemp.marks, &stemp.grade, stemp.result) == 5) {
        if (stemp.id == delId) {
            printf("\nDeleting record:\n%d | %s | %.2f | %c | %s\n",
                   stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
            found = 1;  // mark that we found the record
            continue;   // skip writing this record to temp
        }
        // Write all other records to temp file
        fprintf(temp, "%d | %s | %.2f | %c | %s\n",
                stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("Record not found. Please check the ID.\n");
        // Delete temp file since nothing changed
        remove("temp.txt");
        return;
    }

    // Replace original file with temp file
    remove("SampleRecord.txt");
    rename("temp.txt", "SampleRecord.txt");

    printf("\nRecord deleted successfully!\n");

}

void updateRecord(){

    FILE *fptr, *temp;
    struct Student stemp;
    int updateID;
    int found = 0;
    
    searchByName();

    // Ask which record to delete
    printf("\nEnter the student ID which you want to update: ");
    scanf("%d", &updateID);

    // Open original file for reading
    fptr = fopen("SampleRecord.txt", "r");
    if (!fptr) {
        printf("File not found!\n");
        return;
    }

    // Open temporary file for writing
    temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Unable to create temp file!\n");
        fclose(fptr);
        return;
    }

    // Read each record and copy to temp if it does NOT match the ID
    while (fscanf(fptr, "%d | %49[^|] | %f | %c | %4s",
                  &stemp.id, stemp.name, &stemp.marks, &stemp.grade, stemp.result) == 5) {

        if (stemp.id == updateID) {

            printf("\nEnter the New Details of Student\n");


            stemp.id = updateID;
            printf("Student ID: %d\n", stemp.id);


            printf("Student Name: ");
            scanf("%s", stemp.name);

            printf("Student Marks: ");
            scanf("%f", &stemp.marks);

            if (stemp.marks > 100 || stemp.marks < 0) {
                printf("\nStudent Marks should be between 0-100: ");
                scanf("%f", &stemp.marks);
            }
            
            if(stemp.marks > 90) stemp.grade = 'A';
            else if(stemp.marks > 80) stemp.grade = 'B';
            else if(stemp.marks > 70) stemp.grade = 'C';
            else if(stemp.marks > 60) stemp.grade = 'D';
            else if(stemp.marks > 50) stemp.grade = 'E';
            else stemp.grade = 'F';

            if(stemp.grade=='F') strcpy(stemp.result, "Fail");
            else strcpy(stemp.result, "Pass");

            found = 1;  // mark that we found the record
            // continue;   // skip writing this record to temp
        }

        

        // Write all other records to temp file
        fprintf(temp, "%d | %s | %.2f | %c | %s\n",
                stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("Record not found. Please check the ID.\n");
        // Delete temp file since nothing changed
        remove("temp.txt");
        return;
    }

    // Replace original file with temp file
    remove("SampleRecord.txt");
    rename("temp.txt", "SampleRecord.txt");

    printf("\nRecord updated successfully!\n");

}

void menu(){
    
    printf("\n---SMS Menu---\n\n");
    
    printf("1. Add student records\n");
    printf("2. View student records\n");
    printf("3. Search for a student record\n");
    printf("4. Delete a student record\n");
    printf("5. Update a student record\n");
    printf("6. Exit\n");
}

int main() {

    printf("---Welcome to Student Management System (SMS)---\n");

    while (1)
    {
        menu();

        printf("\nEnter a Number (1-6): ");
        int ch;
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            readRecord();
            break;

        case 2:
            displayRecord();
            break;

        case 3:
            searchRecord();
            break;

        case 4:
            deleteRecord();
            break;

        case 5:
            updateRecord();
            break;

        case 6:
            printf("\nExiting Program.....\n");
            return 0;
        
        default:
            printf("\nInvalid Choice! Please enter Valid Choice. \n");
            break;
        }
    }

    return 0;
}
