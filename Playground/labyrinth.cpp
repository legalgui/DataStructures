// Sebastian Galguera
// Recursive path finder for N x M labyrinth

#include <iostream>
#include <array>

#include <stdlib.h>
#include <time.h>

// Avoiding macros
namespace labyrinthsolverdata{
  class Specs{
  public:
    static constexpr int N { 5 };
    static constexpr int M { 6 };
  };
};

typedef labyrinthsolverdata::Specs Specs;
typedef std::array<std::array<int, Specs::M >, Specs::N> Matrix;

void fillMatrix(Matrix &, size_t, size_t);
void findPath(Matrix &, size_t, size_t);
int hasPath(Matrix);
void printMatrix(Matrix);

int main(){
  srand (time(NULL));

  Matrix M;
  fillMatrix(M, 0, 0);
  findPath(M, 0, 0);

  if(hasPath(M)){
    std::cout << "Path found for labyrinth" << std::endl;
  }else{
    std::cout << "Path not found for labyrinth" << std::endl;
  }

  printMatrix(M);
  return 1;
}

// Function to populate matrix recursively
void fillMatrix(Matrix & t_M, size_t t_row, size_t t_col){
  if(t_row == t_M.size()){ return; }

  t_M[t_row][t_col] = rand() % 2 + 0;

  if(t_col < t_M[0].size()){
    fillMatrix(t_M, t_row, ++t_col);
  }
  fillMatrix(t_M, ++t_row, 0);

}

// Function to find path recursively
void findPath(Matrix & t_M, size_t t_row, size_t t_col){

  if(t_M[t_row][t_col] == 0){

    t_M[t_row][t_col] = 3;

    if(t_col + 1 < t_M[0].size()){ findPath(t_M, t_row, t_col + 1); }
    if(t_row + 1 < t_M.size()){ findPath(t_M, t_row + 1, t_col); }
    if(t_col > 0){ findPath(t_M, t_row, t_col - 1); }
    if(t_row > 0){ findPath(t_M, t_row - 1, t_col); }

  }
}

// Function to evaluate and print if there is path
int hasPath(Matrix t_M){
  return t_M[t_M.size() - 1][t_M[0].size() - 1] == 3;
}

// Function to print matrix non-recursively
void printMatrix(Matrix t_M){
  for(auto row : t_M){
    for(auto col : row){
      std::cout << col << ' ';
    }
    std::cout << std::endl;
  }
}
