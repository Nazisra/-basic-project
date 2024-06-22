#include <stdio.h>

#define MAX_STUDENTS 50
#define MAX_MARKS 6

struct student {
    char name[30];
    int roll;
    float marks[MAX_MARKS];
};

int STUDENTNO = 0;
struct student students[MAX_STUDENTS];

void add_student() {
    FILE *file = fopen("rahadnew.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nEnter student name: ");
    scanf("%s", students[STUDENTNO].name);
    printf("Enter admission roll: ");
    scanf("%d", &students[STUDENTNO].roll);
    printf("Student marks (0-100):\n");
    for (int i = 0; i < MAX_MARKS; i++) {
        printf("Score for subject %d: ", i + 1);
        scanf("%f", &students[STUDENTNO].marks[i]);
    }
    fwrite(&students[STUDENTNO], sizeof(struct student), 1, file);
    fclose(file);

    STUDENTNO++;
    printf("Student data added successfully\n\n");
}

void search_student() {
    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int search_roll, count = 0;
    printf("Enter the roll number you want to search: ");
    scanf("%d", &search_roll);

    struct student temp;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (search_roll == temp.roll) {
            printf("\nStudent name: %s\n", temp.name);
            printf("Admission roll: %d\n", temp.roll);
            printf("Student marks:\n");
            for (int j = 0; j < MAX_MARKS; j++) {
                printf("Marks for subject %d: %.2f\n", j + 1, temp.marks[j]);
            }
            count++;
            break;
        }
    }

    fclose(file);

    if (count == 0) {
        printf("Student data not found.\n");
    }
}

void delete_student() {
    FILE *file = fopen("rahadnew.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int admission_no, found = 0;
    printf("\nEnter roll or admission no: ");
    scanf("%d", &admission_no);

    struct student temp;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (admission_no == temp.roll) {
            temp.roll = 0;
            fseek(file, -sizeof(struct student), SEEK_CUR);
            fwrite(&temp, sizeof(struct student), 1, file);
            found++;
        }
    }

    fclose(file);

    if (found == 1) {
        printf("Student deleted successfully\n");
    } else {
        printf("Student not found\n");
    }
}

void show_students() {
    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct student temp;
    printf("Students' names and roll numbers:\n");
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (temp.roll != 0) {
            printf("NAME -- %s ROLL -- %d\n", temp.name, temp.roll);
        }
    }
    printf("Marks: Under development\n");

    fclose(file);
}

void edit_student() {
    FILE *file = fopen("rahadnew.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int found = 0;
    int edit;
    printf("Provide the student roll you want to edit: ");
    scanf("%d", &edit);

    struct student temp;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (edit == temp.roll) {
            printf("Put the new name and roll: ");
            scanf("%s %d", temp.name, &temp.roll);
            fseek(file, -sizeof(struct student), SEEK_CUR);
            fwrite(&temp, sizeof(struct student), 1, file);
            found++;
        }
    }

    fclose(file);

    if (found == 0) {
        printf("Roll not found in the database\n");
    } else {
        printf("Successfully edited data\n");
    }
}

void add_exam_marks() {
    FILE *file = fopen("rahadnew.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int roll;
    float marks[MAX_MARKS];
    printf("Enter student roll: ");
    scanf("%d", &roll);

    struct student temp;
    int found = 0;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (roll == temp.roll) {
            printf("Enter marks for %s (out of 100):\n", temp.name);
            for (int j = 0; j < MAX_MARKS; j++) {
                printf("Mark %d: ", j + 1);
                scanf("%f", &marks[j]);
            }
            fseek(file, -sizeof(struct student), SEEK_CUR);
            for (int j = 0; j < MAX_MARKS; j++) {
                temp.marks[j] = marks[j];
            }
            fwrite(&temp, sizeof(struct student), 1, file);
            found++;
            printf("Exam marks added successfully for %s\n", temp.name);
            break;
        }
    }

    fclose(file);

    if (found == 0) {
        printf("Student roll not found in the database\n");
    }
}

void show_cgp() {
    FILE *file = fopen("rahadnew.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    float res[100];
    float sum = 0, res1;
    int roll;
    printf("Enter the roll of the student you want to find the CGPA: ");
    scanf("%d", &roll);

    struct student temp;
    int found = 0;
    while (fread(&temp, sizeof(struct student), 1, file)) {
        if (roll == temp.roll) {
            for (int j = 0; j < 6; j++) {
                if (temp.marks[j] >= 80) {
                    res[j] = 5.00;
                } else if (temp.marks[j] >= 75 && temp.marks[j] < 80) {
                    res[j] = 4.75;
                } else if (temp.marks[j] >= 70 && temp.marks[j] < 75) {
                    res[j] = 4.50;
                } else if (temp.marks[j] >= 65 && temp.marks[j] < 70) {
                    res[j] = 4.00;
                } else if (temp.marks[j] >= 60 && temp.marks[j] < 65) {
                    res[j] = 3.75;
                } else if (temp.marks[j] >= 55 && temp.marks[j] < 60) {
                    res[j] = 3.50;
                } else if (temp.marks[j] >= 50 && temp.marks[j] < 55) {
                    res[j] = 3;
                } else if (temp.marks[j] >= 45 && temp.marks[j] < 50) {
                    res[j] = 2.5;
                } else if (temp.marks[j] >= 33 && temp.marks[j] < 45) {
                    res[j] = 2;
                } else {
                    res[j] = 0.0;
                }
                found = 1;
            break;
            }

        }
    }

    fclose(file);

    if (found == 1) {
        for (int j = 0; j < 6; j++) {
            sum = sum + res[j];
        }
        res1 = sum / 6;

        if(res1 > 1){
        printf("CGPA of the student: %.2f\n", res1);
        }
        else {
            printf("CGPA of the student: 0.00");
        }
    } else {
        printf("Student roll not found in the database\n");
    }
}

void about_us() {
    printf("NAME: Md Nazmul Islam, Mosabbir Maruf, Towhidul Islam, Mahir Faysal\n");
}

int main() {
    int option;
    char key;
    do {
        printf("\n1. Enter Category\n");
        printf("2. Search Student Info\n");
        printf("3. Add Student Info\n");
        printf("4. Delete Student Info\n");
        printf("5. Show Student Details\n");
        printf("6. Add Exam marks\n");
        printf("7. Show CGPA\n");
        printf("8. Edit Info\n");
        printf("9. Exit\n");
        printf("10. About Us\n");
        printf("Enter your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Option will be available from (2-9)\n");
                break;
            case 2:
                search_student();
                break;
            case 3:
                add_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                show_students();
                break;
            case 6:
                add_exam_marks();
                break;
            case 7:
                show_cgp();
                break;
            case 8:
                edit_student();
                break;
            case 9:
                printf("Press Y to continue and N to exit\n");
                printf("Enter key: ");
                scanf(" %c", &key);
                break;
            case 10:
                about_us();
                break;
        }
    } while (key != 'N');

    return 0;
}
