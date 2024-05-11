// NIM - Name
// NIM - Name

#include <stdio.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/dorm.h"
#include "./libs/student.h"
#include <string.h>
#include <stdlib.h>


int main(int _argc, char **_argv)
{
    struct dorm_t *create_dorms = (struct dorm_t*) malloc(1 * sizeof(struct dorm_t));
    struct student_t *create_student = (struct student_t*) malloc(1 * sizeof(struct student_t));
    unsigned short totalDorm;
    unsigned short totalStudent;
    char line[255];
    char delim[2] = "#";

    while ( 1 ){
        line[0] = '\0';
        fgets(line, 255, stdin);
        fflush(stdin);

        {
            int len = strlen(line);
            for (short a = 0; a < len; a++) {
                if(line[a] == '\r' || line[a] == '\n') {
                    for(short b = a; b < len; b++) { line[b] = line[b + 1]; }
                    len--;
                    a--;
                }
            }
        }
        if ( strcmp(line, "___") == 0 ) break;

        else if ( strcmp(line, "student-print-all") == 0 ) {
            for (short i=0; i<totalStudent; i++){
                printStudent(create_student[i]);
            }
        }
        else if ( strcmp(line, "dorm-print-all") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                print_dorm(create_dorms[i]);
            }
        }

        else if ( strcmp(line, "student-print-all-detail") == 0 ) {
            for (short i=0; i<totalStudent; i++) {
                printStudentDetails(create_student[i]);
            }
            
        }

        else if ( strcmp(line, "dorm-print-all-detail") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                printDormDetails(create_dorms[i]);
            }
        }

        else {
            char *token = strtok(line, delim);

            if ( strcmp(token, "student-add") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); char *_year = token;
                
                token = strtok(NULL, delim);
                if ( totalStudent > 0 ) {
                    create_dorms = (struct dorm_t*) realloc(create_dorms, (totalDorm+1) * sizeof(struct dorm_t));
                }
                if ( strcmp(token, "male") == 0 ) {
                    dorms[totalDorm] = *create_dorm(_id, _name, _year, GENDER_MALE);
                    totalStudent++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    dorms[totalDorm] = *create_dorm(_id, _name, _year, GENDER_FEMALE);
                    totalStudent++;
                }
            }

            else if ( strcmp(token, "dorm-add") == 0 ) {
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); unsigned short _capacity = atoi(token);
                token = strtok(NULL, delim);
                if ( totalDorm > 0 ) {
                    create_dorms = (struct dorm_t*) realloc(create_dorms, (totalDorm+1) * sizeof(struct dorm_t));
                }
                if ( strcmp(token, "male") == 0 ) {
                    create_dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_MALE);
                    totalDorm++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    create_dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_FEMALE);
                    totalDorm++;
                }
            }

            else if ( strcmp(token, "assign-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;

                short studentIdx = findStudentIdx(_id, create_student, totalStudent);
                short dormIdx = findDormIdx(dorm_name, create_dorms, totalDorm);

                if ( studentIdx>=0 && dormIdx>=0 ) {
                    assign(&create_student[studentIdx], &create_dorms[dormIdx]);
                }
            }

            else if ( strcmp(token, "move-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;

                short studentIdx = findStudentIdx(_id, create_student, totalStudent);
                short newDormIdx = findDormIdx(dorm_name, create_dorms, totalDorm);
                char *_name = create_student[studentIdx].dorm->name;
                if (_name != NULL) {
                    short oldDormIdx = findDormIdx( _name, create_dorms, totalDorm );

                    if ( studentIdx>=0 && newDormIdx>=0 && oldDormIdx>=0 ) {
                        moveStudent(&create_student[studentIdx], &create_dorms[newDormIdx] , &create_dorms[oldDormIdx]);
                    }
                } else {
                    assign(&create_student[studentIdx], &create_dorms[newDormIdx]);
                }
            }

            else if ( strcmp(token, "dorm-empty") == 0 ) {
                token = strtok(NULL, delim);
                char *dorm_name = token;
                short target = findDormIdx(dorm_name, create_dorms, totalDorm);
                
                // emptyDorm(&dorms[target], &students, totalStudent);

                for (short i=0; i<totalStudent; i++) {
                    if (create_student[i].dorm != NULL) {     /* MENGHINDARI STRING COMPARATION DGN NULL */
                        if ( strcmp(create_student[i].dorm->name, dorm_name) == 0 ) {
                            unassign(&create_student[i], &create_dorms[target]);
                        }
                    }
                }
            }
        }
    }    
    

    return 0;
}