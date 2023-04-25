#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student
{
    int rollno, age;
    char name[50];
    char c1[100], c2[100], c3[100];
    int tc1, tc2, tc3;
    float tc, la;
    int la1, la2, la3;
    float c1_att, c2_att, c3_att, agg_att;
};

void recall();

struct student s;
void insertdata(struct student *s);
void login();
void validateLogin(char user[100], char pass[100]);

void insert(struct student *obj)
{
    FILE *fp = fopen("Student1.txt", "ab");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return;
    }
    fwrite(obj, sizeof(struct student), 1, fp);
    printf("Record inserted successfully\n");
    fclose(fp);
}

void modify(struct student *obj, int rn);

void display(struct student *obj)
{
    FILE *fp = fopen("Student1.txt", "rb");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return;
    }
    printf("Student Data : \n");
    int found = 0;
    while (fread(obj, sizeof(struct student), 1, fp) == 1)
    {
        printf("Roll no:%d\nName:%s\nAge:%d\n", obj->rollno, obj->name, obj->age);
        printf("Aggregrate Attendance :%.2f/%.2f\n i.e %.2f%%\n", obj->la, obj->tc, obj->agg_att);

        printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c1,
               obj->la1,
               obj->tc1,
               obj->c1_att);
        printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c2,
               obj->la2,
               obj->tc2,
               obj->c2_att);
        printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c3, obj->la3, obj->tc3, obj->c3_att);
        printf("\n");
        found = 1;
    }
    fclose(fp);
    if (!found)
    {
        printf("Error: No records found\n");
    }
}

void delete(struct student *obj, int rollno)
{
    FILE *fp = fopen("Student1.txt", "rb");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return;
    }
    FILE *tmp = fopen("temp.txt", "wb");
    if (tmp == NULL)
    {
        printf("Error: could not open file\n");
        fclose(fp);
        return;
    }
    int found = 0;
    while (fread(obj, sizeof(struct student), 1, fp) == 1)
    {
        if (obj->rollno == rollno)
        {
            found = 1;
            printf("Record deleted successfully\n");
        }
        else
        {
            fwrite(obj, sizeof(struct student), 1, tmp);
        }
    }
    fclose(fp);
    fclose(tmp);
    remove("Student1.txt");
    rename("temp.txt", "Student1.txt");
    if (!found)
    {
        printf("Error: record not found\n");
    }
}

void search(struct student *obj, int rn)
{
    FILE *fp = fopen("Student1.txt", "rb");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return;
    }
    int found = 0;
    while (fread(obj, sizeof(struct student), 1, fp) == 1)
    {
        if (obj->rollno == rn)
        {
            printf("Roll no:%d\nName:%s\nAge:%d\n", obj->rollno, obj->name, obj->age);
            printf("Aggregrate Attendance :%.2f/%.2f\n i.e %.2f%%\n", obj->la, obj->tc, obj->agg_att);

            printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c1,
                   obj->la1,
                   obj->tc1,
                   obj->c1_att);
            printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c2,
                   obj->la2,
                   obj->tc2,
                   obj->c2_att);
            printf("Attendance for %s : %d/%d i.e %.2f%%\n", obj->c3, obj->la3, obj->tc3, obj->c3_att);
            printf("\n");
            found = 1;
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Error: record not found\n");
    }
}

int main()
{
    printf("Student Attendance Calculator\n\n");
    int choice, rollno;
    char name[50], fn[50], ln[50];
    while (1)
    {
        printf("1. Login\n");
        printf("2. Display Attendance records\n");
        printf("3. Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            login();

            while (1)
            {
                printf("1. Insert a record\n");
                printf("2. Display all records\n");
                printf("3. Delete a record\n");
                printf("4. Search for a record\n");
                printf("5. Modify a record\n");
                printf("6. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    insertdata(&s);
                    insert(&s);
                    break;
                case 2:
                    system("clear");
                    display(&s);
                    break;
                case 3:
                    printf("Enter roll no to delete: ");
                    scanf("%d", &rollno);
                    delete (&s, rollno);
                    break;
                case 4:
                    printf("Enter rollno to search: ");
                    int rn;
                    scanf("%d", &rn);
                    search(&s, rn);
                    break;
                case 5:
                    printf("Enter the roll no of the student: ");
                    scanf("%d", &rollno);
                    modify(&s, rollno);
                    break;
                case 6:
                    exit(0);
                default:
                    printf("Invalid choice\n");
                }
            }

            break;
        case 2:
            system("clear");
            display(&s);
            break;
        case 3:
            system("clear");
            printf("Enter rollno to search: ");
            int rn;
            scanf("%d", &rn);
            search(&s, rn);
            break;
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

void login()
{
    char user[100], pass[100];
    printf("Enter Username:\n");
    scanf("%s", user);

    printf("Enter Password:\n");
    scanf("%s", pass);

    validateLogin(user, pass);
}

void validateLogin(char user[100], char pass[100])
{
    if ((strcmp(user, "Admin") == 0) && (strcmp(pass, "Pass@1234") == 0))
    {
        printf("Authenication Successful\n");
    }
    else if ((strcmp(user, "Admin") == 0) && (strcmp(pass, "Pass@1234") != 0))
    {
        printf("Authenication Failed ! Invalid Password ! Please try again !\n");
        recall();
    }
    else if ((strcmp(user, "Admin") != 0) && (strcmp(pass, "Pass@1234") != 0))
    {
        printf("Authenication Failed ! Invalid Username and Password ! Please try again !\n");
        recall();
    }
}

void insertdata(struct student *s)
{
    int rollno, age;

    int tc1, tc2, tc3;
    int la1, la2, la3;

    char name[100], fn[100], ln[100];
    char c1[100], c2[100], c3[100];

    printf("Enter roll no: ");

    scanf("%d", &rollno);
    s->rollno = rollno;

    printf("Enter Student First Name :");
    scanf("%s", fn);
    printf("Enter Student Last Name :");
    scanf("%s", ln);
    strcat(fn, " ");
    strcat(fn, ln);
    strcpy(name, fn);
    strcpy(s->name, name);

    printf("Enter age: ");
    scanf("%d", &age);

    s->age = age;

    printf("Enter Course Name 1:");
    scanf("%s", c1);
    printf("Enter Course Name 2:");
    scanf("%s", c2);
    printf("Enter Course Name 3:");
    scanf("%s", c3);

    strcpy(s->c1, c1);
    strcpy(s->c2, c2);
    strcpy(s->c3, c3);

    printf("Enter Total Lectures Delivered for %s:", c1);
    scanf("%d", &tc1);
    printf("Enter Total Lectures Attended for %s:", c1);
    scanf("%d", &la1);

    printf("Enter Total Lectures Delivered for %s:", c2);
    scanf("%d", &tc2);
    printf("Enter Total Lectures Attended for %s:", c2);
    scanf("%d", &la2);

    printf("Enter Total Lectures Delivered for %s:", c3);
    scanf("%d", &tc3);
    printf("Enter Total Lectures Attended for %s:", c3);
    scanf("%d", &la3);

    s->tc1 = tc1;
    s->tc2 = tc2;
    s->tc3 = tc3;

    s->la1 = la1;
    s->la2 = la2;
    s->la3 = la3;

    float la = s->la1 + s->la2 + s->la3;
    float ta = s->tc1 + s->tc2 + s->tc3;

    float agg = (la * 100) / ta;

    float c1_att = (s->la1 * 100) / (float)s->tc1;
    float c2_att = (s->la2 * 100) / (float)s->tc2;
    float c3_att = (s->la3 * 100) / (float)s->tc3;

    s->c1_att = c1_att;
    s->c2_att = c2_att;
    s->c3_att = c3_att;

    s->la = la;
    s->tc = ta;
    s->agg_att = agg;
}

void recall()
{
    printf("Press 1 to retry else press any other key to exit:\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        login();
    }
    else
    {
        printf("Program Terminated\n");
        exit(1);
    }
}

void modify(struct student *obj, int rn)
{   
    int tc1, tc2, tc3;
    int la1, la2, la3;
    FILE *fp = fopen("Student1.txt", "rb+");
    if (fp == NULL)
    {
        printf("Error: could not open file\n");
        return;
    }
    int found = 0;
    while (fread(obj, sizeof(struct student), 1, fp) == 1)
    {
        if (obj->rollno == rn)
        {
            found = 1;
            printf("Enter new attendance data for student %d:\n", rn);
            printf("Attendance for %s (present/total): ", obj->c1);
            scanf("%d/%d", &obj->la1, &obj->tc1);
            obj->c1_att = (float)obj->la1 / obj->tc1 * 100;
            printf("Attendance for %s (present/total): ", obj->c2);
            scanf("%d/%d", &obj->la2, &obj->tc2);
            obj->c2_att = (float)obj->la2 / obj->tc2 * 100;
            printf("Attendance for %s (present/total): ", obj->c3);
            scanf("%d/%d", &obj->la3, &obj->tc3);
            obj->c3_att = (float)obj->la3 / obj->tc3 * 100;
            obj->la = obj->la1 + obj->la2 + obj->la3;
            obj->tc = obj->tc1 + obj->tc2 + obj->tc3;
            obj->agg_att = obj->la / obj->tc * 100;

    float la = obj->la1 + obj->la2 + obj->la3;
    float ta = obj->tc1 + obj->tc2 + obj->tc3;

    float agg = (la * 100) / ta;

    float c1_att = (obj->la1 * 100) / (float)obj->tc1;
    float c2_att = (obj->la2 * 100) / (float)obj->tc2;
    float c3_att = (obj->la3 * 100) / (float)obj->tc3;

    obj->c1_att = c1_att;
    obj->c2_att = c2_att;
    obj->c3_att = c3_att;

    obj->la = la;
    obj->tc = ta;
    obj->agg_att = agg;


            fseek(fp, -sizeof(struct student), SEEK_CUR);
            fwrite(obj, sizeof(struct student), 1, fp);
            printf("Record modified successfully\n");
        }
    }
    fclose(fp);
    if (!found)
    {
        printf("Error: record not found\n");
    }
}
