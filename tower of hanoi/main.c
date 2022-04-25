#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct stackNode{
    int e;
    struct stackNode *next;
}StackNode;
typedef struct stack{
    StackNode *top;
    int size;
}Stack;
int level;
void createStack(Stack *ps);
void push(Stack *ps, int e);
int pop(Stack *ps);
int moveDisk(Stack *first, Stack *second);
void moveDisks(Stack *s,int first, int second, int temp, int size);
void clearstack(Stack *ps);
void printTower(Stack *s);
void waitFor (unsigned int secs);
int main()
{
    int close = 0;
    while(!close){
        printf("enter level:");
        scanf("%d", &level);
        Stack s[3];
        createStack(&s[0]);
        s[1].top = NULL;
        s[1].size = 0;
        s[2].top = NULL;
        s[2].size = 0;
        printTower(s);
        int move;
        int finish = 0;
        int whoSolve;
        printf("Who would you like to solve\nEnter 1 for you or 2 for Computer:");
        scanf("%d", &whoSolve);
        if(whoSolve == 2){
            moveDisks(s, 0, 2, 1, level);
            finish = 1;
        }
        while(!finish){
            printf("your move:");
            scanf("%d", &move);
            if(moveDisk(&s[move/10],&s[move%10])==0){
                printf("wrong move\n");
                continue;
            }
            if(s[2].size == level){
                int i = 1;
                StackNode *pn;
                for(pn=s[2].top;i!=level+1;pn=pn->next){
                    if(pn->e != i){
                        break;
                    }
                    i++;
                }
                if(i==level+1){
                    printf("you won\n");
                    break;
                }
            }
            printTower(&s);
        }
        printf("enter 1 to close or 0 two complete:");
        scanf("%d", &close);
        clearstack(&s[2]);
    }
    return 0;
}
void createStack(Stack *ps){
    ps->top = NULL;
    ps->size = 0;
    for(int i = level; i > 0; i--){
        push(ps, i);
    }
}
void push(Stack *ps, int e){
    StackNode *pn = malloc(sizeof(StackNode));
    pn->e = e;
    pn->next = ps->top;
    ps->top = pn;
    ps->size++;
}
int pop(Stack *ps){
    int e = ps->top->e;
    StackNode *pn = ps->top;
    ps->top = ps->top->next;
    ps->size--;
    free(pn);
    return e;
}
int moveDisk(Stack *first, Stack *second){
    if(first->size){
        if(!second->size){
            push(second, pop(first));
            return 1;
        }
        else if(first->top->e < second->top->e){
            push(second, pop(first));
            return 1;
        }
    }
    return 0;
}
void moveDisks(Stack *s,int first, int second, int temp, int size){
    if(size == 1){
        waitFor(1);
        moveDisk(&s[first], &s[second]);
        printTower(s);
        return;
    }
    moveDisks(s, first, temp, second, size-1);
    moveDisks(s, first, second, temp, 1);
    moveDisks(s, temp, second, first, size-1);
}
void clearstack(Stack *ps){
    StackNode *pn;
    while(ps->top != NULL){
        pn = ps->top;
        ps->top = ps->top->next;
        free(pn);
    }
}
void printTower(Stack *s){
    for(int j = 0; j<3; j++){
        printf("|");
        for(int i = 0; i < (level-1)/2;i++){
            printf(" ");
        }
        printf("%d",j);
        for(int i = 0; i< level-1-(level-1)/2;i++){
            printf(" ");
        }
        printf("|");
    }
    printf("\n");
    StackNode* pn[] = {s[0].top, s[1].top, s[2].top};
    for (int i = 0; i < level ;i++){
        for(int j = 0; j<3;j++){
            printf("|");
            if(i < level-(s[j].size)){
                for(int k = 0; k< level; k++){
                    printf(" ");
                }
            }
            else{
                int space = level - (pn[j]->e);
                for (int k = 0; k < space / 2; k++)
                {
                    printf(" ");
                }
                for (int k = 0; k < level - space ; k++)
                {
                    printf("*");
                }
                for (int k = 0; k < space - space / 2; k++)
                {
                    printf(" ");
                }
                pn[j] = pn[j] ->next;
            }
            printf("|");
        }
        printf("\n");
    }
}
void waitFor(unsigned int secs){
    unsigned int retTime = time(0) + secs;
    while (time(0) < retTime);
}
