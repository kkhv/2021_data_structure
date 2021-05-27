#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "stack.h"
#include "pos.h"

#define MAX 100
#define PATH '0'
#define WALL '1'
#define VISITED '2'
#define BACKTRACKED '3'
#define EXIT 'x'

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

char maze[MAX][MAX];
int N; /* 세로*/
int M; /* 가로*/
void read_maze();
void print_maze();
int move();
bool movable(Position pos, int dir);

int main()
{
	read_maze();
	Stack* s = create(); /* 이번에는 Position대신 정수들을 저장하는 스택을 사용한다. */
	Position cur;
	cur.x = 0;
	cur.y = 0;
	int dir = 0; /* 어떤 위치에 도착했을 떄 처음으로 시도해 볼 이동 방향 */
	
	while(1) {
		if (maze[cur.x][cur.y] == EXIT) {
			printf("Found the path.\n");
			break;
		}
		maze[cur.x][cur.y] = VISITED; /*visited */
		bool forwarded = false;  /* 0:N, 1:E, 2:S, 3:W */
		dir = move();
		push(s, dir);
		cur = move_to(cur, dir);
 /* 스택에는 현재 위치 대신 이동하는 방향을 push */
		if (movable(cur, dir)) {

			forwarded = true;
		}
		if (!forwarded) { /* nowhere to go  forward*/
			if (is_empty(s)) {
				printf("No path exists.\n");
			}
			int d = pop(s);
			cur = move_to(cur, (d+2)%4);
			maze[cur.x][cur.y] = BACKTRACKED; /* backtracked */
		}
		print_maze();
	}

}

void read_maze(){
	printf("input:row column\n");
	printf("input:");
	scanf("%d %d", &N, &M);
	FILE *fp = fopen("maze.txt", "w");
	for (int i = 0; i < N; i++)
	{ 
		scanf("%s", maze[i]);
		fwrite(maze[i], strlen(maze[i]), 1, fp);
		fputs("\n", fp);
	}
	fputs("\n", fp);
	fclose(fp); 
	}

void print_maze(){
	FILE *fp = fopen("maze.txt", "a");
	for (int i = 0; i < N; i++)
	{
		fwrite(maze[i], strlen(maze[i]), 1, fp);
		fputs("\n", fp);
		printf("%s\n", maze[i]);
	}
	fputs("\n", fp);
	fclose(fp); 
}

bool movable(Position pos, int dir){
	if(maze[pos.x][pos.y] != WALL){
		return true;
	}
	else return false;
}

int move(){
	FILE *fp = fopen("maze.txt", "a");
	int c = getch();
    while (1) {
        if (kbhit()) {               // 2. while문안에서 키보드 눌렸을 시 if문이 실행된다.        
            c = getch();        // 5. 뒤의 값 00을 판별하여 좌우상하 출력
                switch (c) {           
					case LEFT:
						fputs("move left\n", fp);
						fclose(fp); 
						printf("move left\n");
						return 3;
					case RIGHT:
						fputs("move right\n", fp);
						fclose(fp); 
						printf("move right\n");
						return 1;
					case UP:
						fputs("move up\n", fp);
						fclose(fp); 
						printf("move up\n");
						return 0;
					case DOWN:
						fputs("move down\n", fp);
						fclose(fp); 
						printf("move down\n");
						return 2;
                }
            }
        }
    }