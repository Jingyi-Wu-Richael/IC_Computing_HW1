#include <iostream>
#include <cstdio>
#include "sudoku.h"
#include <chrono> //timing
#include <cstring>

using namespace std;
void load_board_2(const char filename[30], char board[9][9]);
void solve_display_board(char filename[30], char board[9][9], bool should_analyse = false);
void solve_board_print_details(char filename[30], char board[9][9], bool should_analyse);


int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests
  //test1
  // should not be ok since there is 8 in the same row
  cout << "Putting '8' into C7 is ";
  if (!make_move("C7", '8', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test2: should not be ok since there is 8 in the same column
  cout << "Putting '8' into B4 is ";
  if (!make_move("B4", '8', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test3: should not be ok since there is 5 in the same 3x3 box
  cout << "Putting '5' into G9 is ";
  if (!make_move("G9", '5', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test4: should not be ok since K is out of bound
  cout << "Putting '9' into K9 is ";
  if (!make_move("k9", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test5: should not be ok since the position should be length of two
  cout << "Putting '1' into I is ";
  if (!make_move("I", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test6: should not be ok since the digit is not valid
  cout << "Putting 'a' into I8 is ";
  if (!make_move("I8", 'a', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  //test7: should not be ok since the digit has been occupied by 1
  cout << "Putting '9' into A4 is ";
  if (!make_move("A4", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);
  
  
 
  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';
  
  cout << "=================== Question 5 ===================\n\n";
  /* solve the mystery1; calculate the running time and the steps of make_move */
  load_board("mystery1.dat",board);
  // define the start time
  clock_t start_time1 = clock();
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    // define the end time
    clock_t end_time1 = clock();
    display_board(board);
    cout << "The board costs " << (double) (end_time1 - start_time1) / CLOCKS_PER_SEC << " seconds to run."<< endl;
    // save the solution board
    save_board("mystery1_solution.dat", board);
  } else {
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';
 
 /* solve the mystery2; calculate the running time and the steps of make_move */
 load_board("mystery2.dat",board);
  clock_t start_time2 = clock();
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    clock_t end_time2 = clock();
    display_board(board);
    cout << "The board costs " << (double) (end_time2 - start_time2) / CLOCKS_PER_SEC << " seconds to run." << endl;
    
  } else {
    clock_t end_time2 = clock();
    cout << "The board costs " << (double) (end_time2 - start_time2) / CLOCKS_PER_SEC << " seconds to run." << endl;
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';
 
  // solve the mystery3; calculate the running time and the steps of make_move */
  load_board("mystery3.dat",board);
  clock_t start_time3 = clock();
  
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    clock_t end_time3 = clock();
    display_board(board);
    cout << "The board costs " << (double) (end_time3 - start_time3) / CLOCKS_PER_SEC << " seconds to run." << endl;
  } else {
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';

  // write more tests
  // sukudo boards
  load_board("own_sudoku.dat", board);
  if (solve_board(board)) {
    cout << "The 'own_sudoku' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  } 
  cout << '\n';
 
  
  return 0;
}

