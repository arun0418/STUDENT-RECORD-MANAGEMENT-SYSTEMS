#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct student
{
    int rollno;
    char name[50];
    float percentage;
    struct student *next;
} STUDENT;

void add_student(STUDENT **headptr);
void delete_student(STUDENT **headptr);
void show_students_list(STUDENT *headptr);
void modify_student(STUDENT **headptr);
void save_students(STUDENT *headptr);
void delete_all(STUDENT **headptr);
void sort_students(STUDENT *headptr);
void reverse_list(STUDENT **headptr);
void exit_program(STUDENT **headptr);

