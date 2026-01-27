#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void delay(int seconds);

void readRecord(){

    int i=0;

    fptr = fopen("student_records.txt", "a");
 
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

        do {
            printf("Student Marks (0-100): ");
            scanf("%f", &s[i].marks);
        } while(s[i].marks < 0 || s[i].marks > 100);

            
        if(s[i].marks > 90) s[i].grade = 'A';
        else if(s[i].marks > 80) s[i].grade = 'B';
        else if(s[i].marks > 70) s[i].grade = 'C';
        else if(s[i].marks > 60) s[i].grade = 'D';
        else if(s[i].marks > 50) s[i].grade = 'E';
        else s[i].grade = 'F';

        if(s[i].grade=='F') strcpy(s[i].result, "Fail");
        else strcpy(s[i].result, "Pass");

        fprintf(fptr, "%-3d | %-20s | %6.2f | %c | %-4s\n", s[i].id, s[i].name, s[i].marks, s[i].grade, s[i].result);

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

    fptr = fopen("student_records.txt", "r");

    if (fptr == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n---Students Record---\n\n");
    printf("ID | Name | Marks | Grade | Result\n");
    printf("-----------------------------------\n");


    int i = 0;

    while(i<MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s", &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5){
        
        int c;
        while ((c = fgetc(fptr)) != '\n' && c != EOF);

        i++;
    }

    int j=0;
    while (j<i)
    {

        printf("%-3d | %-20s | %6.2f | %c | %-4s\n", s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);

        j++;
    }
    

    fclose(fptr);
}

int searchByName(){

    fptr = fopen("student_records.txt", "r");

    int found = 0;

    if (fptr == NULL) {
        printf("\nNo records found.\n");
        return 0;
    }


    printf("\nEnter Student Name to Search: ");
    char search[15];
    // fgets(search, sizeof(search), stdin);
    scanf("%14s", search);

    printf("\n");

    int i = 0;
    while(i<MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s", &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5){

        int c;
        while ((c = fgetc(fptr)) != '\n' && c != EOF);

        i++;
    }

    int j=0;
    while (j<i)
    {
        char *result;

        result = strstr(s[j].name, search); 
        

        if(result != NULL) {
            if (!found) {  // print header only once
                printf("ID | Name | Marks | Grade | Result\n");
                printf("----------------------------------\n");
            }
            printf("%-3d | %-20s | %6.2f | %c | %-4s\n", s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);
            found = 1;
        }

        j++;
    }

    if (!found) {
        printf("No matching record found.\n");
    }

    fclose(fptr);

    return found;
}


int searchById() {

    fptr = fopen("student_records.txt", "r");

    int found = 0;

    if (fptr == NULL) {
        printf("\nNo records found.\n");
        return 0;
    }

    printf("\nEnter Student ID (numeric only): ");
    char search[15];
    scanf("%14s", search);   // safe input

    int searchId = atoi(search);  // convert to integer once

    printf("\n");

    int i = 0;
    while (i < MAX && fscanf(fptr, "%d | %19[^|] | %f | %c | %9s",
                             &s[i].id, s[i].name, &s[i].marks, &s[i].grade, s[i].result) == 5) {
        int c;
        while ((c = fgetc(fptr)) != '\n' && c != EOF);
        
        i++;
    }

    // Loop to find the matching ID
    for (int j = 0; j < i; j++) {
        if (s[j].id == searchId) {
            if (!found) {  // print header only once
                printf("ID | Name | Marks | Grade | Result\n");
                printf("----------------------------------\n");
            }
            printf("%-3d | %-20s | %6.2f | %c | %-4s\n",
                   s[j].id, s[j].name, s[j].marks, s[j].grade, s[j].result);
            found = 1;
            break;  // stop after finding the exact ID
        }
    }

    if (!found){
        printf("No matching record found.\n");
    }

    fclose(fptr);

    return found;
}

int searchRecord(){

    printf("\nChoose Search Method:\n");
    printf("1. Search By Name\n");
    printf("2. Search By ID\n\n");

    printf("Enter a number (1-2): ");
    int ch;
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        return searchByName();

    case 2:
        return searchById();
    
    default:
        printf("Invalid choice! \n");
        return 0;
    }

}

void deleteRecord(){

    FILE *fptr, *temp;
    struct Student stemp;
    int delId;
    int found = 0;

    // Open original file for reading
    fptr = fopen("student_records.txt", "r");
    if (!fptr) {
        printf("\nFile not found!\n");
        return;
    }

    if (!searchRecord()) return;

    // Ask which record to delete
    printf("\nEnter the student ID which you want to delete: ");
    scanf("%d", &delId);

    // Open temporary file for writing
    temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Unable to create temp file!\n");
        fclose(fptr);
        return;
    }

    // Read each record and copy to temp if it does NOT match the ID
    while (fscanf(fptr, "%d | %49[^|] | %f | %c | %9s",
                &stemp.id, stemp.name, &stemp.marks, &stemp.grade, stemp.result) == 5) {
        int c;
        while ((c = fgetc(fptr)) != '\n' && c != EOF);
        
        if (stemp.id == delId) {
            printf("\nDeleting record:\n%-3d | %-20s | %6.2f | %c | %-4s\n",
                stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
            found = 1;  // mark that we found the record
            continue;   // skip writing this record to temp
        }
        // Write all other records to temp file
        fprintf(temp, "%-3d | %-20s | %6.2f | %c | %-4s\n",
                stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        delay(2);
        printf("\nRecord not found. Please check the ID.\n");
        // Delete temp file since nothing changed
        remove("temp.txt");
        return;
    }

    // Replace original file with temp file
    remove("student_records.txt");
    rename("temp.txt", "student_records.txt");
    delay(2);
    printf("\nRecord deleted successfully!\n");
}

void updateRecord(){

    FILE *fptr, *temp;
    struct Student stemp;
    int updateID;
    int found = 0;

    // Open original file for reading
    fptr = fopen("student_records.txt", "r");
    if (!fptr) {
        printf("\nFile not found!\n");
        return;
    }

    if (!searchRecord()) return;

    // Ask which record to delete
    printf("\nEnter the student ID which you want to update: ");
    scanf("%d", &updateID);

    // Open temporary file for writing
    temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Unable to create temp file!\n");
        fclose(fptr);
        return;
    }

    // Read each record and copy to temp if it does NOT match the ID
    while (fscanf(fptr, "%d | %49[^|] | %f | %c | %9s",
                  &stemp.id, stemp.name, &stemp.marks, &stemp.grade, stemp.result) == 5) {

        int c;
        while ((c = fgetc(fptr)) != '\n' && c != EOF);

        if (stemp.id == updateID) {

            printf("\nEnter the New Details of Student\n");


            stemp.id = updateID;
            printf("Student ID: %d\n", stemp.id);

            printf("Student Name: ");
            scanf(" "); // consume leftover newline
            fgets(stemp.name, sizeof(stemp.name), stdin);
            stemp.name[strcspn(stemp.name, "\n")] = 0;
            
            do {
                printf("Student Marks (0-100): ");
                scanf("%f", &stemp.marks);
            } while(stemp.marks < 0 || stemp.marks > 100);

            
            if(stemp.marks > 90) stemp.grade = 'A';
            else if(stemp.marks > 80) stemp.grade = 'B';
            else if(stemp.marks > 70) stemp.grade = 'C';
            else if(stemp.marks > 60) stemp.grade = 'D';
            else if(stemp.marks > 50) stemp.grade = 'E';
            else stemp.grade = 'F';

            if(stemp.grade=='F') strcpy(stemp.result, "Fail");
            else strcpy(stemp.result, "Pass");

            found = 1;  // mark that we found the record
        }

        

        // Write all other records to temp file
        fprintf(temp, "%-3d | %-20s | %6.2f | %c | %-4s\n",
                stemp.id, stemp.name, stemp.marks, stemp.grade, stemp.result);
    }

    fclose(fptr);
    fclose(temp);

    if (!found) {
        printf("\nRecord not found. Please check the ID.\n");
        delay(2);
        // Delete temp file since nothing changed
        remove("temp.txt");
        return;
    }

    // Replace original file with temp file
    remove("student_records.txt");
    rename("temp.txt", "student_records.txt");

    delay(2);
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

void delay(int seconds){
    time_t start = time(NULL);
    while (time(NULL) - start < seconds);
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
            delay(2);
            break;

        case 2:
            displayRecord();
            delay(2);
            break;

        case 3:
            searchRecord();
            delay(2);
            break;

        case 4:
            deleteRecord();
            delay(2);
            break;

        case 5:
            updateRecord();
            delay(2);
            break;

        case 6:
            delay(2);
            printf("\nExiting Program.....\n");
            delay(2);
            return 0;
        
        default:
            printf("\nInvalid Choice! Please enter Valid Choice. \n");
            delay(2);
            break;
        }
    }

    return 0;
}
