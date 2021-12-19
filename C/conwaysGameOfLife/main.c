#include <unistd.h>
#include <stdio.h>

#define MAXL 20
#define MAXB 20
#define L 20
#define B 20
#define SLEEP_DELAY 250000


/***
char box[MAXL][MAXB] = {"  *                ",
	          "   **              ",
	          "  **               ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "   *               ",
	          "    **             ",
	          "   **              ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   "};
***/


/*** Pentadecathlon 
char box[MAXL][MAXB] = {"                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "         *         ",
	          "         *         ",
	          "        * *        ",
	          "         *         ",
	          "         *         ",
	          "         *         ",
	          "         *         ",
	          "        * *        ",
	          "         *         ",
	          "         *         ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   "};

***/

char box[MAXL][MAXB] = {"                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "       **          ",
	          "      * *          ",
	          "      *    *       ",
	          "       *****       ",
	          "       *****       ",
	          "      *    *       ",
	          "      * *          ",
	          "       **          ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   ",
	          "                   "};



int dirs[8][2] = {{-1, -1},
		  {-1, +0},
		  {-1, +1},
		  {+0, -1},
		  {+0, +1},
		  {+1, -1},
		  {+1, +0},
		  {+1, +1}};

void clrscr() {
	printf("\e[1;1H\e[2J");
}

int countNeighbors(int i, int j) {
	int cnt = 0;
	int r, c;

	for (int x = 0; x < 8; ++x) {
		r = i+dirs[x][0];
		c = j+dirs[x][1];
		if ( r < 0) r = L-1;
		else if ( r >= L) r = 0;

		if ( c < 0 ) c = B-1;
		else if ( c >= B ) c = 0; 

		if (box[r][c] == '*') {
			++cnt;
		}
	}
	return cnt;
}

void calc() {

	int c = 0;
	char tmp[L][B];

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < B; ++j)  {
			tmp[i][j] = ' ';
		}
	}


	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < B; ++j) {
			c = countNeighbors(i,j);
			if (box[i][j] == '*' && c < 2) {
				tmp[i][j] = ' '; // dies
			} else if (box[i][j] == '*' && c < 4) {
				tmp[i][j] = '*'; // continues to live
			} else if (box[i][j] == '*' && c > 3) {
				tmp[i][j] = ' '; // dies
			} else if (box[i][j] == ' ' && c == 3) {
				tmp[i][j] = '*';
			}
		}
	}

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < B; ++j) {
			box[i][j] = tmp[i][j];
		}
	}
}

void printBox() {
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < B; ++j) {
			printf("%c", box[i][j]);
		}
		printf("\n");
	}
}

int isEmpty() {
	for (int i = 0; i < L; ++i) 
		for (int j = 0; j < B; ++j) 
			if (box[i][j] == '*')
				return 0;

	return 1;
}

int main() {


	while(1) {
		if (isEmpty()) {
			return 0;
		}
		clrscr();
		printBox();
		calc();
		usleep(SLEEP_DELAY);

	}
	return 0;
}

