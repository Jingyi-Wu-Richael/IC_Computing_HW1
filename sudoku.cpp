#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;


/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/* TASK 1 */
/* A function to test whether the board has been completed by excluding the empty and the out-of bound situations */
bool is_complete(const char board[9][9]){
  for (int r=0; r<9; r++){
    for (int c=0; c<9; c++){
      if (board[r][c] == '.'){
	return false;
      }else if (!(board[r][c] >='1' && board[r][c] <= '9')){
      return false;
        }
      } 
    }
    return true;
  }

/* TASK 2 */
/* helper functions/
/* make sure the position length is two: row and column */
bool position_length(const char* position){
  int count = 0;
  while(position[count]!= '\0'){
    count ++;
  }
  return count == 2;
}

/* make sure the position has not existed any digits already */
/* first check the row position */
bool exist_row(const char digit, const char board[9][9], const int rowpos){
  for(int c = 0; c < 9; c++){
    if (board[rowpos][c] == digit){
      return true;
    }
  }
  return false;
}

/* second check the column position */
bool exist_column(const char digit, const char board[9][9], const int colpos){
  for(int r = 0; r < 9; r++){
    if (board[r][colpos] == digit){
      return true;
    }
  }
    return false;
}

/* make sure the digit and position are both within the bound and valid */
bool check_bound(const char input, const char lowerbound, const char upperbound){
  if (input > upperbound || input < lowerbound){
    return false;
  }else{
    return true;
  }
}

/* make sure the 3 X 3 box is valid */
bool check_box(const int rowpos, const int colpos, const char digit, const char board[9][9]){
  int row_num = 0;
  int column_num = 0;
  if (0 <= rowpos && rowpos <=2){
    row_num = 0;}
  else if (3 <= rowpos && rowpos <=5){
    row_num = 1;}
  else if (6 <= rowpos && rowpos <=8){
    row_num = 2;}

  if (0 <= colpos && colpos <=2){
    column_num = 0;}
  else if (3<= colpos && colpos <=5){
    column_num = 1;}
  else if (6 <= colpos && colpos <=8){
    column_num = 2;}
    
  // nine 3 x 3 boxes in total
  for (int r = row_num *3; r < (row_num*3)+3; r++){
    for (int c = column_num *3; c < (column_num*3)+3; c++){
      if (board[r][c] == digit){
	return true;
      }
    }
  }
  return false;
}

/* the function to put the digit in the board at a given position */
bool make_move(const char* position, const char digit, char board[9][9]){

  int rowpos = position[0] - 'A';
  int colpos = position[1] - '1';
  
  //check the existence of the position
  if (position == nullptr){
   // cout << "There exists an error since the position input is a null pointer";
    return false;
  }
  //check the length of the position
  if (!position_length(position)){ 
      return false;
  }
  //check the row bound
  if (!check_bound(position[0], 'A','I')){
    return false;
  }
  //check the column bound
  if (!check_bound(position[1],'1','9')){ 
    return false;
  }
  //check the digit bound
  if (!check_bound(digit,'1','9')){ 
    return false;
  }
  //check whether the given position already exists the digit
  if (board[(rowpos)][(colpos)] != '.'){ 
    return false;
  }
  //check whether the row of the given position already exists the digit
  if (exist_row(digit, board, rowpos)){ 
    return false;
  }
  //check whether the column of the given position already exists the digit
  if (exist_column(digit, board, colpos)){
    return false;
  }
  //check whether the 3 X 3 box exist the digit
  if (check_box(rowpos, colpos, digit, board)){
    return false;
  } 
  //write digit ino the board
  
  board[rowpos][colpos] = digit;
  return true;
}

/* TASK 3 */
/* the function to write the board into a file named by the filename*/
bool save_board(const char* filename, char board[9][9]){
  ofstream file;
  file.open(filename);

  if(file.is_open()){
    for(int r=0; r < 9; r++){
      for(int c=0; c < 9; c++)
	file << board[r][c]; 
      // change to a new line
      file.put('\n');
    }
  }else {
    return false;}
    
  file.close();
  return true;
}

/* TASK 4 & 5 */
/* solve the board from the A1 position */
bool solve_board(char board[9][9]){
  int sum = 0;
  int rec_sum = 0;
  int back_sum =0; 
  char pos[] = "A1";
  bool solve_value = false;
  solve_value = solver(board, sum, rec_sum, back_sum, pos);
  // print the number of steps of make_move
  // cout << "The board needs " << sum << " steps of make_move." << endl;
  // cout << "The number of recursions of this board is " << rec_sum << endl;
  // cout << "The number of backwards of this board is " << back_sum << endl;
  return solve_value;
  }

/* solve the board step by step by defining pos and next_pos */
bool solver(char board[9][9], int &sum, int &rec_sum, int &back_sum, char *pos){
   
  char next_pos[ ] ="A1";
  char first_pos []= "A1";
  
  if (rec_sum ==0 &&board[0][0]!='.'){
    while(board[(first_pos[0] - 65)][(first_pos[1] - 49)] != '.'){
  // Apply the function to each line and row
    if (first_pos[1] == '9'){
      first_pos[0] = first_pos[0] + 1; //turn to the next row
      first_pos[1] = '1';}
    else{
      first_pos[0] = first_pos[0];
      first_pos[1] = first_pos[1] + 1;}
  }
  	strcpy(pos,first_pos);
  }
 
  rec_sum++;
  // Check whether the board has been comlpeted
  if (is_complete(board) == true){
    return true;}
  // Apply the function to each line and row
  else if (pos[1] == '9'){
    next_pos[0] = pos[0] + 1; //turn to the next row
    next_pos[1] = '1';}
  else{
      next_pos[0] = pos[0];
      next_pos[1] = pos[1] + 1;} 
  
  //Repeatedly Check whether there exists a default value in next_pos[]
  while(board[(next_pos[0] - 65)][(next_pos[1] - 49)] != '.'){
  // Apply the function to each line and row
    if (next_pos[1] == '9'){
      next_pos[0] = next_pos[0] + 1; //turn to the next row
      next_pos[1] = '1';}
    else{
      next_pos[0] = next_pos[0];
      next_pos[1] = next_pos[1] + 1;}
  }
  
	
  //Choose an appropriate value and write it into the position
  for(int value = 0; value < 9; value ++){
    char char_value = static_cast<char>(value + 49);
    if(make_move(pos, char_value, board)){
    	// calculate the number of steps
    	sum++;
	bool solved = solver(board, sum, rec_sum, back_sum, next_pos);
	if (solved) {
	  return true;}
	      back_sum++;
	 board[(pos[0] - 65)][(pos[1] - 49)] = '.'; 
	}   
      }	    
    return false;
    }

