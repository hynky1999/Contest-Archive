/*
    ID: frceped1
    LANG: C
    TASK: transform
 */

#include <stdio.h>

#define UPLOAD 1

#if UPLOAD
	#define openFiles() freopen("transform.in", "r", stdin); freopen("transform.out", "w", stdout)
#else
	#define openFiles()
#endif

// USACO upload macros

#define MAXSIZE 10

typedef struct {
	int x,y;
} Point;

char before[MAXSIZE][MAXSIZE];
char after[MAXSIZE][MAXSIZE];
int size;

void readArr(char arr[MAXSIZE][MAXSIZE]){
	int x, y;
	for (y = 0; y < size; y++){
		scanf("%*[ \n\r]");
		for (x = 0; x < size; x++){
			scanf("%c", &arr[x][y]); 
		}
	}
}

int compare(Point (*transform)(int, int)){
	int x, y;
	for (x = 0; x < size; x++){
		for (y = 0; y < size; y++){
			Point new = (*transform)(x,y);
			if (before[x][y] != after[new.x][new.y])
				return 1;
		}
	}
	return 0;
}

Point doNothing(int x, int y){
	Point p = {x,y};
	return p;
}

Point rotate90(int x, int y){
	Point p = {size-1-y, x};
	return p;
}

Point rotate180(int x, int y){
	Point p = rotate90(x, y);
	p = rotate90(p.x, p.y);
	return p;
}

Point rotate270(int x, int y){
	Point p = rotate90(x,y);
	p = rotate180(p.x,p.y);
	return p;
}

Point mirror(int x, int y){
	Point p = {size-1-x, y};
	return p;
}

Point (*afunc)(int, int);
Point (*bfunc)(int, int);

Point combine(int x, int y){
	Point p = (*afunc)(x, y);
	p = (*bfunc)(p.x, p.y);
	return p;
}

int main(void){
	openFiles();
	scanf("%d", &size);
	readArr(before);
	readArr(after);
	int answer = 7;
	afunc = mirror;
	if (compare(rotate90) == 0) answer = 1;
	else if (compare(rotate180) == 0) answer = 2;
	else if (compare(rotate270) == 0) answer = 3;
	else if (compare(mirror) == 0) answer = 4;
	else if (bfunc = rotate90, compare(combine) == 0) answer = 5;
	else if (bfunc = rotate180, compare(combine) == 0) answer = 5;
	else if (bfunc = rotate270, compare(combine) == 0) answer = 5;
	else if (compare(doNothing) == 0) answer = 6;
	printf("%d\n", answer);
	return 0;
}
