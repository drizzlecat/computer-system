#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define max 1000


struct room{
    int room_number;
    char draw[max];
    int room_north;
    int room_south;
    int room_east;
    int room_west;
};

int main() {
    char filename[max];
    char command[max];
    char one[max];


    FILE *fp = NULL;

    char command0[max] = "loaddungeon";
    char command1[max] = "north";
    char command2[max] = "south";
    char command3[max] = "east";
    char command4[max] = "west";
    char command5[max] = "quit";

    struct room r[100];
    int has_dungeon = 0;



    while (1) {
        scanf("%s", command);
        if (strcmp(command, command0) == 0 ) {
            scanf("%s", filename);
            fp = fopen(filename, "r");
            if (fp != NULL) {
                int tag = 0;
                int index = 1;
                while (fgets(one, max, fp) != NULL) {//read file
                    char *p1 = strtok(one, "$");
                    char *p2 = strtok(NULL, "$");
                    char *p3 = strtok(NULL, "$");
                    int i = 1;
                    while (i <= index) {         //check if there is the same room number.
                        if (r[i].room_number == atoi(p1)) {
                            puts("Error room number.File is wrong.");
                            tag++;
                            break;
                        }
                        i++;
                    }
                    if (tag != 0) break;
                    r[index].room_number = atoi(p1);
                    strcpy(r[index].draw, p2);
                    r[index].room_north = atoi(strtok(p3, " "));
                    r[index].room_south = atoi(strtok(NULL, " "));
                    r[index].room_east = atoi(strtok(NULL, " "));
                    r[index].room_west = atoi(strtok(NULL, " "));
                    index++;
                }
                if (tag == 0)
                has_dungeon++;
                tag == 0;
            }

            if(fp == NULL )
                printf("%s\n", "Wrong file name.");

            fclose(fp);

            if ( has_dungeon != 0) {
                puts(r[1].draw);
            }
        }

        if( strcmp(command,command1) == 0 || strcmp(command,command2) == 0 || strcmp(command,command3) == 0
           || strcmp(command,command4) == 0 ){
            if(has_dungeon == 0)
                printf("%s\n", "You need to load a file first.");
        }
        int num = 1;
        if ( has_dungeon != 0) {//has a file.
            if (strcmp(command, command1) == 0) {

                int new_num = r[num].room_north;
                if (new_num != -1) {
                    printf("%s\n", r[new_num].draw);
                    num = new_num;
                } else if (new_num == -1)
                    printf("%s\n", "You cant go there.");
            }

            if (strcmp(command, command2) == 0) {

                int new_num = r[num].room_south;
                if (new_num != -1) {
                    printf("%s\n", r[new_num].draw);
                    num = new_num;
                } else if (new_num == -1)
                    printf("%s\n", "You cant go there.");
            }
            if (strcmp(command, command3) == 0) {

                int new_num = r[num].room_east;
                if (new_num != -1) {
                    printf("%s\n", r[new_num].draw);
                    num = new_num;
                } else if (new_num == -1)
                    printf("%s\n", "You cant go there.");
            }
            if (strcmp(command, command4) == 0) {

                int new_num = r[num].room_west;
                if (new_num != -1) {
                    printf("%s\n", r[new_num].draw);
                    num = new_num;
                } else if (new_num == -1)
                    printf("%s\n", "You cant go there.");
            }
            else if(strcmp(command,command5) == 0) return 0;
        }
        else if(strcmp(command,command5) == 0) break;
        if(strcmp(command,command0) != 0 && strcmp(command,command1) != 0 && strcmp(command,command2) != 0 && strcmp(command,command3) != 0
           && strcmp(command,command4) != 0 && strcmp(command,command5) != 0)
        printf("%s\n", "Wrong command,please enter again.");
        }
    return 0;
}


