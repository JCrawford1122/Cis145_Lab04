/*
  Author: Justin Crawford
  Date: 11/15/2016
*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_COUNT 30
#define FILE_ERROR "There was an error opening the file"
#define NUMBER_OF_LABS 1
#define NUMBER_OF_EXAMS 1
#define LABS_WEIGHT .4f
#define EXAMS_WEIGHT .4f
#define FINAL_WEIGHT .2f
#define GPA_TXT_FILE "StudentsByGpa.txt"
#define NAMES_TXT_FILE "StudentsByName.txt"
#define MENU_DEFAULT ""
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct students{
  char firstName[15];
  char lastName[20];
  float percentGrade;
  char letterGrade;
};
typedef struct students STUDENTS;

void calcPercent(float *);
void calcLabs(float *);
void calcExams(float *);
void calcFinal(float *);
void calcLetterGrade(float, char *);
void enterStudents(STUDENTS[], int *);
void sortByName(STUDENTS[], int);
void sortByGpa(STUDENTS[], int);
void displayStudents(STUDENTS[], int, char[] );
void writeStudents(STUDENTS[], int, char[]);
void loadClass(STUDENTS[], int *, char[]);
void writeClass(STUDENTS[], int, char[]);

int main(int argc, char *argv[])
{
  char className[20];
  char classFileName[24];
  int selection = 0;
  STUDENTS students[30];
  int studentCount = 0;

  strcpy(className, argv[01]);
  sprintf(classFileName, "%s.dat", argv[01]);
 
  loadClass(students, &studentCount, classFileName);
  // Display the menu
  do {
    printf("\nSelect an Option (0-5)\n");
    printf("\n1. Enter Students");
    printf("\n2. GPA to Screen");
    printf("\n3. GPA to File");
    printf("\n4. Names to Screen");
    printf("\n5. Names to File");
    printf("\n0. Exit\n");
    printf("\nEnter your Selection: ");
    fflush(stdin);
    scanf("%d", &selection);

    switch (selection)
    {
    case 0:
      break;
    case 1: enterStudents(students, &studentCount);
      break;
    case 2: sortByGpa(students, studentCount);
      displayStudents(students, studentCount, className);
      break;
    case 3: sortByGpa(students, studentCount);
      writeStudents(students, studentCount, GPA_TXT_FILE);
      break;
    case 4: sortByName(students, studentCount);
      displayStudents(students, studentCount, className);
      break;
    case 5: sortByName(students, studentCount);
      writeStudents(students, studentCount, NAMES_TXT_FILE);
      break;
    default: printf("Enter 0-5");
      break;

    }
  } while (selection);

  writeClass(students, studentCount, classFileName);
  return(0);
}

/*
  Add students data into struct array. calls functions
  to calculate grades.
*/
void enterStudents(STUDENTS students[], int * ptr_studentCount)
{
  char firstName[15];
  char lastName[20];
  char letterGrade;
  float percentGrade = 0.0f;
  printf("Enter student's first name: ");
  fflush(stdin);
  scanf(" %14[^\n]s", firstName);
  while (firstName[0] != '0' && *ptr_studentCount < MAX_COUNT)
  {

    printf("enter student's last name: ");
    fflush(stdin);
    scanf(" %19[^\n]s", lastName);

    calcPercent(&percentGrade);
    calcLetterGrade(percentGrade, &letterGrade);
    strcpy(students[*ptr_studentCount].firstName, firstName);
    strcpy(students[*ptr_studentCount].lastName, lastName);
    students[*ptr_studentCount].percentGrade = percentGrade;
    students[*ptr_studentCount].letterGrade = letterGrade;
    (*ptr_studentCount)++;

    
    if (*ptr_studentCount == MAX_COUNT - 1)
    {
      printf("\nClass is full after one more student.");
    }
    else if (*ptr_studentCount == MAX_COUNT)
    {
      printf("\n\nThe class is now full\n");
      printf("Main Menu");
      break;
    }
    printf("\nEnter student's first name or (0) to Exit: ");
    fflush(stdin);
    scanf(" %14[^\n]s", firstName);
  }

}

/*
  Sorts STUDENTS by last name in ascending order. 
  When the last names are the same they are sorted by first name
*/
void sortByName(STUDENTS students[], int studentCount)
{
  STUDENTS temp;
  int i;
  int x;

  
  for (x = 0; x<studentCount; x++)
  {
    for (i = 0; i<studentCount - 1 - x; i++)
    {
      if (strcmp(students[i].lastName, students[i + 1].lastName) > 0 ||
        strcmp(students[i].lastName, students[i + 1].lastName) == 0 &&
        strcmp(students[i].firstName, students[i + 1].firstName) > 0)
      {
        temp = students[i];
        students[i] = students[i + 1];
        students[i + 1] = temp;
      }
    }
  }
}

/* 
  Sorts STUDENTS by GPA (percent grade) in descending order. 
  (A - F)
*/
void sortByGpa(STUDENTS students[], int studentCount)
{
  STUDENTS temp;
  int i;
  int x;

  for (x = 0; x < studentCount; x++)
  {
    for (i = 0; i < studentCount - 1 - x; i++) 
    {
      if (students[i].percentGrade < students[i + 1].percentGrade)
      {
        temp = students[i];
        students[i] = students[i + 1];
        students[i + 1] = temp;
      }
    }
  }
}

/* 
  Displays a report of students names, percent grade, and letter grade
*/
void displayStudents(STUDENTS students[], int studentCount, char className[])
{
  printf("\n\nDisplaying grades for %s\n\n", className);
  int i;
  printf("%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  for (i = 0; i < studentCount; i++)
  {
    printf("\n%-10s%-20s%6.2f % 10c", students[i].lastName, students[i].firstName, students[i].percentGrade, students[i].letterGrade);
  }
  printf("\n\nTotal Students - %d", studentCount);
}

/*
  Writes a report of students names, percent grade, and letter grade
  to filename passed in.
*/
void writeStudents(STUDENTS students[], int studentCount, char file[])
{
  // Open the file
  FILE * rpt;
  rpt = fopen(file, "w");
  int i;
  if (rpt == NULL)
  {
    printf(FILE_ERROR);
    fflush(stdin); getchar();
    exit(0);
  }
  // Write file headings
  fprintf(rpt, "%-30s %-10s %-15s", "Name", "% Grade", "Letter Grade\n");
  for (i = 0; i < studentCount; i++)
  {
    fprintf(rpt, "\n%-10s%-20s%6.2f % 10c", students[i].lastName, students[i].firstName, students[i].percentGrade, students[i].letterGrade);
  }
  fprintf(rpt, "\n\nTotal Students - %d", studentCount);
  fclose(rpt);
}

/*
  Calculates the overall percent grade of the student
*/
void calcPercent(float *ptr_percentGrade)
{
  float labs = 0;
  float exams = 0;
  float final = 0;
  float total = 0;
  calcLabs(&labs);
  calcExams(&exams);
  calcFinal(&final);
  total = labs + exams + final;
  *ptr_percentGrade = total;
}

/*
  P&G the lab scores. Calculates percent grade
  of labs.
*/
void calcLabs(float *ptr_labs)
{
  int i;
  float score;
  for (i = 0; i < NUMBER_OF_LABS; i++)
  {

    printf("%s %d %s", "Enter lab", i + 1, "score: ");
    fflush(stdin);
    scanf(" %f", &score);
    *ptr_labs += score;
  }
  *ptr_labs /= NUMBER_OF_LABS;
  *ptr_labs *= (float)LABS_WEIGHT;
}

/*
  P&G exam scores. Calculate Exam percent grade
*/
void calcExams(float *ptr_exams)
{
  int i;
  float score;
  for (i = 0; i < NUMBER_OF_EXAMS; i++)
  {
    printf("%s %d %s", "Enter exam", i + 1, "score: ");
    fflush(stdin);
    scanf(" %f", &score);
    *ptr_exams += score;
  }

  *ptr_exams /= NUMBER_OF_EXAMS;
  *ptr_exams *= EXAMS_WEIGHT;
}

/*
  P&G Final. Calculate final percent grade.
*/
void calcFinal(float *ptr_final)
{
  float score;
  printf("Enter final exam score :");
  fflush(stdin);
  scanf(" %f", &score);

  *ptr_final = score;
  *ptr_final *= (float)FINAL_WEIGHT;
}

/*
  Calculates the lettergrade based on the overall
  percent grade.
*/
void calcLetterGrade(float percentGrade, char *ptr_letterGrade)
{
  if (percentGrade >= 94)
    *ptr_letterGrade = 'A';
  else if (percentGrade >= 85)
    *ptr_letterGrade = 'B';
  else if (percentGrade >= 75)
    *ptr_letterGrade = 'C';
  else if (percentGrade >= 65)
    *ptr_letterGrade = 'D';
  else
    *ptr_letterGrade = 'F';
}

/* Load the data from existing class file. */
void loadClass(STUDENTS students[], int *ptr_studentCount, char classFileName[])
{
  FILE * fptr;
  fptr = fopen(classFileName, "rb");
  int i = 0;
  int rc;
  if (fptr != NULL)
  {
   
    fread(&students[i], sizeof(STUDENTS), 1, fptr);
    while (!feof(fptr))
    {
      i++;
      printf("\nreading the next student");
      fread(&students[i], sizeof(STUDENTS), 1, fptr);
    }
    
    *ptr_studentCount = i;
  }
  fclose(fptr);
  printf("%d", i);
}

/* Write the class to a data file */
void writeClass(STUDENTS students[], int studentCount, char classFileName[])
{
  FILE * fptr;
  int i = 0;
  fptr = fopen(classFileName, "wb");

  if (fptr == NULL)
  {
    printf("Error opening the file");
    system("pause");
    return;
  }

  for (i = 0; i<studentCount; i++)
  {
    fwrite(&students[i], sizeof(STUDENTS), 1, fptr);
  }

  fclose(fptr);
}