#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int empID;
    char name[50];
    float salary;
};

void writeRecord(FILE *file, int position, struct Employee *emp) {
    fseek(file, position * sizeof(struct Employee), SEEK_SET);
    fwrite(emp, sizeof(struct Employee), 1, file);
}

void readRecord(FILE *file, int position, struct Employee *emp) {
    fseek(file, position * sizeof(struct Employee), SEEK_SET);
    fread(emp, sizeof(struct Employee), 1, file);
}

int main() {
    FILE *employeeFile;
    int choice;
    int empID, recordPosition;
    struct Employee emp;

    employeeFile = fopen("employee.dat", "rb+");  // Open or create a binary file for reading and writing

    if (employeeFile == NULL) {
        employeeFile = fopen("employee.dat", "wb+");
        if (employeeFile == NULL) {
            printf("Unable to create or open the file.\n");
            return 1;
        }
    }

    while (1) {
        printf("1. Add employee record\n");
        printf("2. Read employee record\n");
        printf("3. Update employee record\n");
        printf("4. Delete employee record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter employee ID: ");
                scanf("%d", &emp.empID);
                printf("Enter employee name: ");
                scanf(" %[^\n]s", emp.name);  // Read a whole line
                printf("Enter employee salary: ");
                scanf("%f", &emp.salary);
                writeRecord(employeeFile, emp.empID, &emp);
                break;

            case 2:
                printf("Enter employee ID to read: ");
                scanf("%d", &empID);
                readRecord(employeeFile, empID, &emp);
                if (emp.empID != 0) {
                    printf("Employee ID: %d\n", emp.empID);
                    printf("Employee Name: %s\n", emp.name);
                    printf("Employee Salary: %.2f\n", emp.salary);
                } else {
                    printf("Record not found.\n");
                }
                break;

            case 3:
                printf("Enter employee ID to update: ");
                scanf("%d", &empID);
                readRecord(employeeFile, empID, &emp);
                if (emp.empID != 0) {
                    printf("Enter new salary: ");
                    scanf("%f", &emp.salary);
                    writeRecord(employeeFile, empID, &emp);
                    printf("Record updated.\n");
                } else {
                    printf("Record not found.\n");
                }
                break;

            case 4:
                printf("Enter employee ID to delete: ");
                scanf("%d", &empID);
                readRecord(employeeFile, empID, &emp);
                if (emp.empID != 0) {
                    memset(&emp, 0, sizeof(struct Employee));  // Mark the record as deleted
                    writeRecord(employeeFile, empID, &emp);
                    printf("Record deleted.\n");
                } else {
                    printf("Record not found.\n");
                }
                break;

            case 5:
                fclose(employeeFile);
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}