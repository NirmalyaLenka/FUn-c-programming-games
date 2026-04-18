#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
char board[3][3];
void initBoard() {
char c = '1';
for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
board[i][j] = c++;
}
void printBoard() {
printf("\n");
printf("  %c | %c | %c \n",board[0][0],board[0][1],board[0][2]);
printf(" ---|---|---\n");
printf("  %c | %c | %c \n",board[1][0],board[1][1],board[1][2]);
printf(" ---|---|---\n");
printf("  %c | %c | %c \n",board[2][0],board[2][1],board[2][2]);
printf("\n");
}
int checkWin() {
for(int i=0;i<3;i++) {
if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) return 1;
if(board[0][i]==board[1][i] && board[1][i]==board[2][i]) return 1;
}
if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) return 1;
if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) return 1;

return 0;
}
int isMovesLeft() {
for(int i=0;i<3;i++)
for(int j=0;j<3;j++)
if(board[i][j] != 'X' && board[i][j] != 'O')
return 1;
return 0;
}
int evaluate() {
for(int i=0;i<3;i++) {
if(board[i][0]==board[i][1] && board[i][1]==board[i][2]) {
if(board[i][0]=='O') return +10;
else if(board[i][0]=='X') return-10;
}
}
for(int i=0;i<3;i++) {
if(board[0][i]==board[1][i] && board[1][i]==board[2][i]) {
if(board[0][i]=='O') return +10;
else if(board[0][i]=='X') return-10;
}
}
if(board[0][0]==board[1][1] && board[1][1]==board[2][2]) {
if(board[0][0]=='O') return +10;
else if(board[0][0]=='X') return-10;
}
if(board[0][2]==board[1][1] && board[1][1]==board[2][0]) {
if(board[0][2]=='O') return +10;
else if(board[0][2]=='X') return-10;
}
return 0;
}
int minimax(int depth, int isMax) {
int score = evaluate();
if(score == 10) return score;
if(score ==-10) return score;
if(isMovesLeft()==0) return 0;
if(isMax) {
int best =-1000;
for(int i=0;i<3;i++) {
for(int j=0;j<3;j++) {
if(board[i][j] != 'X' && board[i][j] != 'O') {
char temp = board[i][j];
board[i][j] = 'O';
best = best > minimax(depth+1,0) ? best : minimax(depth+1,
0);
board[i][j] = temp;
}
}
}
return best;
}
else {
int best = 1000;
for(int i=0;i<3;i++) {
for(int j=0;j<3;j++) {
if(board[i][j] != 'X' && board[i][j] != 'O') {
char temp = board[i][j];
board[i][j] = 'X';
best = best < minimax(depth+1,1) ? best : minimax(depth+1,
1);
board[i][j] = temp;
}
}
}
return best;
}
}
void bestMove() {
int bestVal =-1000;
int row =-1;
int col =-1;
for(int i=0;i<3;i++) {
for(int j=0;j<3;j++) {
if(board[i][j] != 'X' && board[i][j] != 'O') {
char temp = board[i][j];
board[i][j] = 'O';
int moveVal = minimax(0,0);
board[i][j] = temp;
if(moveVal > bestVal) {
row = i;
col = j;
bestVal = moveVal;
}
}
}
}
board[row][col] = 'O';
}
int main() {
int move;
initBoard();
while(1) {
printBoard();
printf("Your Move (X): ");
scanf("%d",&move);
int r = (move-1)/3;
int c = (move-1)%3;
if(board[r][c]=='X' || board[r][c]=='O') {
printf("Invalid move\n");
continue;
}
board[r][c]='X';
if(checkWin()) {
printBoard();
printf("You Win!\n");
break;
}
if(!isMovesLeft()) break;
bestMove();
if(checkWin()) {
printBoard();
printf("Computer Wins!\n");
break;
}
if(!isMovesLeft()) break;
}
printBoard();
printf("Draw\n");
}

