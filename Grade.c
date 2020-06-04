 * name: Haik Shougarian
 * user?? h.shoug
 * date: 5/14/2020
 * file: hw7.c
 */



#include "Grade.h"


void readStudent(Student *stu, char *s){

    char *token = strtok(s, ","); // set string token to everything before first comma
    stu -> firstname = malloc(sizeof(char) * NAME_LEN); // allocate memory
    stu -> lastname = malloc(sizeof(char) * NAME_LEN); // allocatre memory
    stu -> id = malloc(sizeof(char) * ID_LEN); // allocate memory
    stu -> grades = malloc(sizeof(float) * NUM_GRADES); // allocate memory
    


    stu -> firstname = token; // firstname is equal to the first token from s
    stu -> lastname = strtok(NULL, ","); // lastname is everything up to the next comma
    stu -> id = strtok(NULL, ","); // id is everything up to the next comma

    float weightedScore = 0; // initialize weighted score variable with value 0
    for (int i = 0; i < NUM_GRADES; i++) // itterate through the amount of grades
    {
        if (i == 11) // if i is 11
        {
            stu -> grades[i] = 0.0; // then grades[i] is the weighted score which we set to 0
            break; // and we break out of this loop
        }
        token = strtok(NULL, ","); // token set equal to next value before next comma
        stu -> grades[i] = atof(token); // enumarate token and set equal to grades at i
        if (i < 8) // up until the 9th grade
        {
            // we add to the weighted score with weight of 5%
            weightedScore += ((stu -> grades[i])/100) * 5;
        }
        
    }
    float test1 = stu -> grades[8];
    float test2 = stu -> grades[9];
    float test3 = stu -> grades[10];
    // Add to weightedscore based on grades on the test
    weightedScore += (fmax(test3, fmax(test1, test2))) * .35;
    weightedScore += (fmin(test3, fmax(test1, test2))) * .25;
    stu -> grades[11] = weightedScore; // save weighted score in the 12th index of grades
    stu -> weighted = weightedScore;
    stu -> len = NUM_GRADES;
}



Class * readClass(char *s){
    // create a new class of students and allocate memory
    Class *students = malloc(sizeof(Class));
    // Student *stu = malloc(sizeof(Student)); // create and allocate memory to a temporary student
    // allocate memory to an array of all students
    students -> stus = malloc(sizeof(Student) * MAX_STUDENTS);
    students -> len = MAX_STUDENTS; // set length of array to max_students
    students -> num = 0; // set num equal to 0
    FILE *fp = fopen(s, "r"); // create and open a new file with name s
    // allocate memory to a string containing the current student
    char *currentStudent = malloc(sizeof(char) * MAX_LINE);
    char *line = malloc(sizeof(currentStudent)); // allocate memory of whole student
    line[0] = '\0'; // set first character in line equal to null
    // get a portion of the student from fp until file is empty
    while (fgets(currentStudent, sizeof(currentStudent),fp) != NULL)
    {
        // copncvatine portion with line
        strcat(line, currentStudent);
        // if line ending character is reached
        if (line[strlen(line) - 1] == '\n' || line[strlen(line) - 1] == '\0') 
        {
            line[strlen(line) - 1] = '\0';
            readStudent((students -> stus) + students -> num, line); // read line into stu
            // set stus at index n equal to stu
            students -> num += 1;
            line[0] = '\0';
        }
    }
    // students -> num = n;
    

    return students; // return the class of students


	
}

// compararator function for qsort
int compararator(const void *pa, const void *pb)
{
    // create point 1 and point 2
     const Student *s1 = pa;
     const Student *s2 = pb;
     // if y value in 1 is less than 2 return -1
     if (((s1 -> grades[INDEX_SORT]) - (s2 -> grades[INDEX_SORT])) < 0)
     {
         return -1;
     }
     // if y values equal retunr 0
     else if (((s1 -> grades[INDEX_SORT]) - (s2 -> grades[INDEX_SORT])) == 0)
     {
         return 0;
     }
     // otherwise return 1
     else
     {
         return 1;
     }
}
void sortClass(Class * class){
    // sort the students in the class
    qsort(class -> stus, ID_LEN, sizeof(Student), compararator);
    FILE *fp = fopen("sorted.csv", "w"); // create and open a new file
    for (int i = 0; i < ID_LEN; i++) // for the number of students in the class
    {
        // write the first name, lastname, and id separated by a comma
        fprintf(fp, "%s,%s,%s,", class -> stus[1].firstname, class -> stus[0].lastname, class -> stus[0].id);
        for (int j = 0; j < INDEX_SORT; j++) // go trhough the number of grades -1
        {
            fprintf(fp, "%.1f,", (class -> stus) + (class -> num) -> grades[j]); // write the grade at that index
        }
        fprintf(fp, "%.1f\n", class -> stus[i].grades[INDEX_SORT]); // the last grade is weighted score with newline character
    }

}


void freeClass(Class * c){
    // free all variables with memory allocated to them 
    for (int i = 0; i < c -> num; i++)
    {
        free(c -> stus[i].firstname);
        free(c -> stus[i].lastname);
        free(c -> stus[i].id);
        free(c -> stus[i].grades);
    }
    free(c);
}
