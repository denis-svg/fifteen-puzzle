#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "stack.h"
#include "queue.h"

#define QUIT "quit"
#define LEFT "a"
#define RIGHT "d"
#define DOWN "s"
#define UP "w"
#define HELP "help"
#define BUFFER 8
#define SIZE 4
#define CLEAR "clear"
#define DO "do"
#define UNDO "undo"
#define RESTART "restart"
#define SAVE "save"
#define RESUME "resume"
#define NEW "new"

char quit[BUFFER] = QUIT;
char left[BUFFER] = LEFT;
char right[BUFFER] = RIGHT;
char up[BUFFER] = UP;
char down[BUFFER] = DOWN;
char help[BUFFER] = HELP;
char clear[BUFFER] = CLEAR;
char doc[BUFFER] = DO;
char undo[BUFFER] = UNDO;
char restart[BUFFER] = RESTART;
char save[BUFFER] = SAVE;
char resume[BUFFER] = RESUME;
char new[BUFFER] = NEW;
int should_check = 0;

void delete_grid(int **arr){
    for(int i=0;i<SIZE;i++)
        free(arr[i]);
    free(arr);
}

int check_win(int **arr){
    int arr1d[SIZE * SIZE];
    if (arr[SIZE-1][SIZE-1] != 0)
        return 0;
    for(int i=0;i<SIZE*SIZE;i++){
        arr1d[i] = arr[i/SIZE][i % SIZE];
    }

    for(int i=0;i<SIZE*SIZE - 2;i++){
        if (arr1d[i] > arr1d[i + 1])
            return 0;
    }
    return 1;
}

void white(){
    printf("\033[0;37m");
}

void green(){
    printf("\033[0;32m");
}

void red(){
    printf("\033[0;31m");
}

void draw(int **arr){
    should_check = 1;
    for(int i=0;i<15;i++){
        printf("#");
    }
    printf("\n");
    int k = 1;
    for(int i=0;i<SIZE;i++){
        printf("# ");
        for(int j=0;j<SIZE;j++){
            if (arr[i][j] == 0){
                printf("   ");
            }else if (arr[i][j] < 10){
                if (arr[i][j] == k)
                    green();
                printf("%d  ", arr[i][j]);
            }else{
                if (arr[i][j] == k)
                    green();
                printf("%d ", arr[i][j]);
            }
            white();
            k++;
        }
        printf("#\n");
    }

    for(int i=0;i<15;i++){
        printf("#");
    }
    printf("\n");
}

int is_solvable(int **arr){
    int inv_count = 0;
    int arr1d[SIZE * SIZE];
    for(int i=0;i<SIZE*SIZE;i++){
        arr1d[i] = arr[i/SIZE][i % SIZE];
    }

    for(int i=0;i<SIZE*SIZE-1;i++){
        for(int j=i+1;j<SIZE*SIZE;j++){
            if (arr1d[i]>arr1d[j] && arr1d[i] && arr1d[j])
                inv_count++;
        }
    }
    
    int x = 0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if (arr[i][j] == 0){
                x = i + 1;
                break;
            }
        }
        if (x != 0)
            break;
    }

    if (x % 2 != 0 && inv_count % 2 != 0)
        return 1;
    if (x % 2 == 0 && inv_count % 2 == 0)
        return 1;
    return 0;
}

int is_in(int **arr, int num){
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++){
            if (arr[i][j] == num)
                return 1;
        }
    return 0;
}

int** generate_random_grid(){
    int ** arr = (int **)malloc(sizeof(int*) * SIZE);
    for(int i=0;i<SIZE;i++){
        arr[i] = (int *)malloc(sizeof(int) * SIZE);
        for(int j=0;j<SIZE;j++){
            arr[i][j] = -1;
        }
    }

    srand(time(NULL));
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            int r = rand() % 16;
            while(is_in(arr, r)){
                r = rand() % (SIZE * SIZE);
            
            }

            arr[i][j] = r;

        }
    }
    return arr;
}


int** generate_grid(){
    int **arr = generate_random_grid();
    while(!is_solvable(arr)){
        delete_grid(arr);
        arr = generate_random_grid();
    }
    return arr;
}

int ** ez_grid(){
    int ** arr = (int **)malloc(sizeof(int*) * SIZE);
    for(int i=0;i<SIZE;i++){
        arr[i] = (int *)malloc(sizeof(int) * SIZE);
    }
    int arr2[SIZE][SIZE] = { {1, 2, 3, 4}, 
                            {5, 6, 7, 8},
                            {9, 10, 11, 0}, 
                            {13, 14, 15, 12}};
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            arr[i][j] = arr2[i][j];
        }
    }
    return arr;
}

void display_help(){
    printf("quit->\033[0;32m%s\n", QUIT);
    white();
    printf("move left->\033[0;32m%s\n", LEFT);
    white();
    printf("move right->\033[0;32m%s\n", RIGHT);
    white();
    printf("move up->\033[0;32m%s\n", UP);
    white();
    printf("move down->\033[0;32m%s\n", DOWN);
    white();
    printf("clear screen->\033[0;32m%s\n", CLEAR);
    white();
    printf("undo->\033[0;32m%s\n", UNDO);
    white();
    printf("redo->\033[0;32m%s\n", DO);
    white();
    printf("restart->\033[0;32m%s\n", RESTART);
    white();
    printf("save game->\033[0;32m%s\n", SAVE);
    white();
    printf("resume game->\033[0;32m%s\n", RESUME);
    white();
    printf("generate new grid->\033[0;32m%s\n", NEW);
    white();
}

int main()
{
    // int **grid = ez_grid();
    int **grid = generate_grid();
    while(check_win(grid)){
        delete_grid(grid);
        grid = generate_grid();
    }
    draw(grid);

    int space_row = 0;
    int space_column = 0;
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if (grid[i][j] == 0){
                space_row = i;
                space_column = j;
            }
        }
    }

    struct Node *Undo_stack = NULL;
    struct NodeQ *front = NULL;
    struct NodeQ *rear = NULL;
    // left=1 right=2 up=3 down=4
   
    while (1)
    {
        printf("15puzzle:");
        char command[BUFFER];
        scanf("%s", command);
        if (strcmp(command, quit) == 0)
        {
            delete_grid(grid);
            free_queue(&front, &rear);
            free_stack(&Undo_stack);
            break;
        }
        else if (strcmp(command, help) == 0){
            display_help();
        }
        else if (strcmp(command, clear) == 0){
            system("clear");
            draw(grid);
        }
        else if (strcmp(command, left) == 0){
            if (space_column == SIZE-1){
                red();
                printf("CANNOT MOVE LEFT\n");
                white();
            }else{
                free_queue(&front, &rear);
                push(&Undo_stack, 1);
                grid[space_row][space_column] = grid[space_row][space_column + 1];
                space_column++;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }
        else if (strcmp(command, right) == 0){
            if (space_column == 0){
                red();
                printf("CANNOT MOVE RIGHT\n");
                white();
            }else{
                free_queue(&front, &rear);
                push(&Undo_stack, 2);
                grid[space_row][space_column] = grid[space_row][space_column - 1];
                space_column--;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }
        else if (strcmp(command, up) == 0){
            if (space_row == SIZE-1){
                red();
                printf("CANNOT MOVE UP\n");
                white();
            }else{
                free_queue(&front, &rear);
                push(&Undo_stack, 3);
                grid[space_row][space_column] = grid[space_row+1][space_column];
                space_row++;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }
        else if (strcmp(command, down) == 0){
            if (space_row == 0){
                red();
                printf("CANNOT MOVE DOWN\n");
                white();
            }else{
                free_queue(&front, &rear);
                push(&Undo_stack, 4);
                grid[space_row][space_column] = grid[space_row-1][space_column];
                space_row--;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }else if(strcmp(command, doc) == 0){
            int move = qpop(&front, &rear);
            if (move != -1)
                push(&Undo_stack, move);
            if (move == -1){
                red();
                printf("NOTHING TO REDO\n");
                white();
            }else if(move == 1){
                grid[space_row][space_column] = grid[space_row][space_column + 1];
                space_column += 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 2){
                grid[space_row][space_column] = grid[space_row][space_column - 1];
                space_column -= 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 3){
                grid[space_row][space_column] = grid[space_row+1][space_column];
                space_row += 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 4){
                grid[space_row][space_column] = grid[space_row-1][space_column];
                space_row -= 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }else if(strcmp(command, undo) == 0){
            int move = pop(&Undo_stack);
            if (move != -1)
                qpush(&front, &rear, move);
            if (move == -1){
                red();
                printf("NOTHING TO UNDO\n");
                white();
            }else if(move == 1){
                grid[space_row][space_column] = grid[space_row][space_column - 1];
                space_column -= 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 2){
                grid[space_row][space_column] = grid[space_row][space_column + 1];
                space_column += 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 3){
                grid[space_row][space_column] = grid[space_row-1][space_column];
                space_row -= 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }else if(move == 4){
                grid[space_row][space_column] = grid[space_row+1][space_column];
                space_row += 1;
                grid[space_row][space_column] = 0;
                draw(grid);
            }
        }else if(strcmp(command, restart) == 0){
            int move = pop(&Undo_stack);
            while(move != -1){
                qpush(&front, &rear, move);
                if(move == 1){
                    grid[space_row][space_column] = grid[space_row][space_column - 1];
                    space_column -= 1;
                    grid[space_row][space_column] = 0;
                }else if(move == 2){
                    grid[space_row][space_column] = grid[space_row][space_column + 1];
                    space_column += 1;
                    grid[space_row][space_column] = 0;
                }else if(move == 3){
                    grid[space_row][space_column] = grid[space_row-1][space_column];
                    space_row -= 1;
                    grid[space_row][space_column] = 0;
                }else if(move == 4){
                    grid[space_row][space_column] = grid[space_row+1][space_column];
                    space_row += 1;
                    grid[space_row][space_column] = 0;
                }
                move = pop(&Undo_stack);
            }
            draw(grid);
        }else if (strcmp(command, save) == 0){
            FILE *fptr;
            fptr = fopen("save.txt","w");
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    fprintf(fptr,"%d ",grid[i][j]);
                }
                fprintf(fptr,"\n");
            }

            int k=0;
            struct Node* t1 = Undo_stack;
            while(t1 != NULL){
                k++;
                t1 = t1->next;
            }
            fprintf(fptr, "%d\n", k);
            k=0;

            struct Node* it = Undo_stack;
            while(it != NULL){
                fprintf(fptr, "%d ", it->val);
                it = it->next;
            }
            fprintf(fptr,"\n");

            struct NodeQ* t2 = front;
            while(t2 != NULL){
                k++;
                t2 = t2->next;
            }
            fprintf(fptr, "%d\n", k);

            struct NodeQ* it2 = front;
            while(it2 != NULL){
                fprintf(fptr, "%d ", it2->val);
                it2 = it2->next;
            }
            fclose(fptr);
        }else if (strcmp(command, resume) == 0){
            system("clear");
            free_queue(&front, &rear);
            free_stack(&Undo_stack);
            FILE *fptr;
            fptr = fopen("save.txt","r");
            if (fptr == NULL){
                red();
                printf("NO SAVE AVAILABLE");
                white();
            }
            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++){
                    int num;
                    fscanf(fptr, "%d", &num);
                    grid[i][j] = num;
                }
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    if (grid[i][j] == 0){
                        space_row = i;
                        space_column = j;
                    }
                }
            }

            int undo_size;
            fscanf(fptr, "%d", &undo_size);
            struct NodeQ *f = NULL;
            struct NodeQ *r = NULL;
            for(int i=0;i<undo_size;i++){
                int move;
                fscanf(fptr, "%d", &move);
                qpush(&f, &r, move);
            }
            int move = qpop(&f, &r);
            while(move != -1){
                push(&Undo_stack, move);
                move = qpop(&f, &r);
            }

            int resume_size;
            fscanf(fptr, "%d", &resume_size);
            struct Node *p = NULL;
            for(int i=0;i<resume_size;i++){
                int move;
                fscanf(fptr, "%d", &move);
                push(&p, move);
            }
            move = pop(&p);
            while(move != -1){
                qpush(&front, &rear, move);
                move = pop(&p);
            }

            fclose(fptr);
            draw(grid);
        }else if (strcmp(command, new) == 0){
            delete_grid(grid);
            free_queue(&front, &rear);
            free_stack(&Undo_stack);
            grid = generate_grid();
            for(int i=0;i<SIZE;i++){
                for(int j=0;j<SIZE;j++){
                    if (grid[i][j] == 0){
                        space_row = i;
                        space_column = j;
                }
            }
            draw(grid);
        }
        }
        else{
            red();
            printf("INVALID COMMAND\n");
            white();
        }
        if (should_check == 1){
            if (check_win(grid)){
                printf("WIN\n");
            }
            should_check = 0;
        }
    }


}