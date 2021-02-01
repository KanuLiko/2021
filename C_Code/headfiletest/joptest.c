#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#define U 1
#define D 2
#define L 3
#define R 4

typedef struct SNAKE
{
    int x;
    int y;
    struct SNAKE *next;
} snake;

//global variable
int score = 0, add = 10;
int status, sleeptime = 200;
snake *head, *food; //snake header and food pointer
snake *q;
int endgamestatus = 0;

//aLl the func statement
void Pos(int, int);
void creatMap();
void initsnake();
int biteself();
void createfood();
void cantcrosswall();
void snakemove();
void pause();
void gamecircle();
void welcometogame();
void endgame();
void gamestart();

void Pos(int x, int y)
{
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void creatMap()
{
    int i;
    for (i = 0; i < 58; i += 2)
    {
        Pos(i, 0);
        printf("鈻?");
        Pos(i, 26);
        printf("鈻?");
    }
    for (i = 1; i < 26; i++)
    {
        Pos(0, i);
        printf("鈻?");
        Pos(56, i);
        printf("鈻?");
    }
}

void initsnake()
{
    snake *tail;
    int i;
    tail = (snake *)malloc(sizeof(snake));
    tail->x = 24;
    tail->y = 5;
    tail->next = NULL;
    for (i = 1; i < 4; i++)
    {
        head = (snake *)malloc(sizeof(snake));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 5;
        tail = head;
    }
    while (tail != NULL)
    {
        Pos(tail->x, tail->y);
        printf("鈻?");
        tail = tail->next;
    }
}

int biteself()
{
    snake *self;
    self = head->next;
    while (self != NULL)
    {
        if (self->x == head->x && self->y == head->y)
        {
            return 1;
        }
        self = self->next;
    }
    return 0;
}

void createfood()
{
    snake *food_1;
    srand((unsigned)time(NULL));
    food_1 = (snake *)malloc(sizeof(snake));
    while (food_1->x % 2 != 0)
    {
        food_1->x = rand() % 52 + 2;
    }
    food_1->y = rand() % 24 + 1;
    while (q->next == NULL)
    {
        if (q->x == food_1->x && q->y == food_1->y)
        {
            free(food_1);
            createfood();
        }
        q = q->next;
    }
    Pos(food_1->x, food_1->y);
    food = food_1;
    printf("鈻?");
}

void cantcrosswall()
{
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
    {
        endgamestatus = 1;
        endgame();
    }
}

void snakemove()
{
    snake *nexthead;
    cantcrosswall();
    nexthead = (snake *)malloc(sizeof(snake));
    if (status == U)
    {
        nexthead->x = head->x;
        nexthead->y = head->y - 1;
        if (nexthead->x == food->x && nexthead->y == food->y)
        {
            nexthead->next = food;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("鈻?");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
    }
    else
    {
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q->next->next != NULL)
        {
            Pos(q->x, q->y);
            printf("鈻?");
            q = q->next;
        }
        Pos(q->next->x, q->next->y);
        printf(" ");
        free(q->next);
        q->next = NULL;
    }

    if (status == D)
    {
        nexthead->x = head->x;
        nexthead->y = head->y + 1;
        if (nexthead->x == food->x && nexthead->y == food->y)
        {
            nexthead->next = food;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("-");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
    }
    else
    {
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q->next->next != NULL)
        {
            Pos(q->x, q->y);
            printf("-");
            q = q->next;
        }
        Pos(q->next->x, q->next->y);
        printf("-");
        free(q->next);
        q->next = NULL;
    }

    if (status == L)
    {
        nexthead->x = head->x - 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)
        {
            nexthead->next = food;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("-");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
    }
    else
    {
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q->next->next != NULL)
        {
            Pos(q->x, q->y);
            printf("-");
            q = q->next;
        }
        Pos(q->next->x, q->next->y);
        printf(" ");
        free(q->next);
        q->next = NULL;
    }

    if (status == R)
    {
        nexthead->x = head->x + 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)
        {
            nexthead->next = food;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("-");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
    }
    else
    {
        nexthead->next = head;
        head = nexthead;
        q = head;
        while (q->next->next != NULL)
        {
            Pos(q->x, q->y);
            printf("-");
            q = q->next;
        }
        Pos(q->next->x, q->next->y);
        printf(" ");
        free(q->next);
        q->next = NULL;
    }
}

void pause()
{
    while (1)
    {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE))
        {
            break;
        }
    }
}

void gamecircle() //control game
{
    Pos(64, 15);
    printf("Don't cross the Wall");
    Pos(64, 16);
    printf("Game Recycle");
    Pos(64, 17);
    printf("F1 start game again!\n");
    Pos(64, 18);
    printf("ESC exit game!,space Pause the game!");
    status = R;
    while (1)
    {
        Pos(64, 10);
        printf("Game Score:%d", score);
        Pos(64, 11);
        printf("SingleFood Score:%d?", add);
        if (GetAsyncKeyState(VK_UP) && status != D)
        {
            status = U;
        }
        else if (GetAsyncKeyState(VK_DOWN) && status != U)
        {
            status = D;
        }
        else if (GetAsyncKeyState(VK_LEFT) && status != R)
        {
            status = L;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && status != L)
        {
            status = R;
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            pause();
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus = 3;
            break;
        }
        else if (GetAsyncKeyState(VK_F1))
        {
            if (sleeptime >= 50)
            {
                sleeptime = sleeptime - 30;
                add = add + 2;
                if (sleeptime == 320)
                {
                    add = 2; //闃叉鍑忓埌1涔嬪悗鍐嶅姞鍥炴潵鏈夐敊
                }
            }
        }
        else if (GetAsyncKeyState(VK_F2))
        {
            if (sleeptime < 350)
            {
                sleeptime = sleeptime + 30;
                add = add - 2;
                if (sleeptime == 350)
                {
                    add = 1; //淇濊瘉鏈€浣庡垎涓?1
                }
            }
        }
        Sleep(sleeptime);
        snakemove();
    }
}

void welcometogame() //寮€濮嬬晫闈?
{
    Pos(40, 12);
    system("SNAKE GAME");
    printf("Welcome To Snake Game!");
    Pos(40, 25);
    system("pause");
    system("cls");
    Pos(25, 12);
    printf("use up/dowm/right/left key to control snake moving,F1 accelerate or F2 slow down\n");
    Pos(25, 13);
    printf("Acceleration can aquire higher scores!\n");
    system("pause");
    system("cls");
}

void endgame() //缁撴潫娓告垙
{

    system("cls");
    Pos(24, 12);
    if (endgamestatus == 1)
    {
        printf("You kit the Wall,Game Over!.");
    }
    else if (endgamestatus == 2)
    {
        printf("You bite yourself,Game Over!.");
    }
    else if (endgamestatus == 3)
    {
        printf("You has turn off the game!");
    }
    Pos(24, 13);
    printf("You get the SCORE:%d\n", score);
    exit(0);
}

void gamestart() //娓告垙鍒濆鍖?
{
    system("mode con cols=100 lines=30");
    welcometogame();
    creatMap();
    initsnake();
    createfood();
}

int main()
{
    gamestart();
    gamecircle();
    endgame();
    return 0;
}