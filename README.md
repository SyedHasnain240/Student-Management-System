# Student Management System (SMS)

## Project Description
This is a **console-based Student Management System (SMS)** written in C.  
It allows the user to **add, view, search, update, and delete student records** stored in a text file.  
This project is ideal for beginners to learn **file handling, structures, loops, and functions** in C.

## Features
- **Add student records:** ID, Name, Marks, Grade, Result.  
- **View records:** Display all student records in a table format.  
- **Search records:** By Name or ID.  
- **Update records:** Modify existing student information.  
- **Delete records:** Remove a student record.  
- **Exit program:** Close the application safely.

## How to Run
1. Compile the code using a C compiler:
   ```bash
   gcc sms.c -o sms
   
2. Run the program:
  ```bash
    ./sms      # Linux/Mac
    sms.exe    # Windows
```

3. Follow the menu options to manage student records.

## Data Storage

- All student records are stored in a text file (SampleRecord.txt).
- Each record format in the file:
```rust
ID | Name | Marks | Grade | Result
```
- New records are appended to the file, keeping old records safe.

## Input Notes

- Student ID: Integer only.
- Student Name: Can contain multiple words.
- Marks: Floating-point numbers between 0–100.
- Enter `999` as Student ID to exit input when adding records.

## Beginner-friendly Tips

- Great for learning C structures, file handling, and functions.
- Console-based interface makes it simple to understand program flow.
- Step-by-step input ensures beginners do not get overwhelmed.

## Example Console Output
```pgsql 
---SMS Menu---

1. Add student records
2. View student records
3. Search for a student record
4. Delete a student record
5. Update a student record
6. Exit

Enter a Number (1-6): 2

---Students Record---

ID | Name | Marks | Grade | Result
-----------------------------------
101 | Ali Khan | 95.00 | A | Pass
102 | Sara Ahmed | 88.50 | B | Pass
103 | Omar Sheikh | 72.00 | C | Pass
```

## Author

- Syed Hasnain Bokhari
- Beginner-friendly C project for practice and learning.
