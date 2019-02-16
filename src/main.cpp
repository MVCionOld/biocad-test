/*
 ПЯТНАШКИ

 Написать алгоритм для решения игры в “пятнашки”.
 Решением задачи является приведение к виду:
    [ 1 2 3 4 ]
    [ 5 6 7 8 ]
    [ 9 10 11 12]
    [ 13 14 15 0 ],
 где 0 задает пустую ячейку. Достаточно найти хотя бы
 какое-то решение. Число перемещений костяшек не обязано
 быть минимальным.

 Пример:

  input:

    1 2 3 0 5 6 7 4 9 10 11 8 13 14 15 12

  output:

    3
    UUU
 */

#include <iostream>        // std::istream, std::ostream, std::cin, std::cout

#include "CPuzzle.h"       // CPuzzle
#include "CPuzzleSolver.h" // CPuzzleSolver


/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @param argc Number of arguments
 * @param argv List of arguments
 *
 * @return Program exit status
 */
int main (int argc, char ** argv)
{
  CPuzzle puzzle;
  std::cin >> puzzle;
  CPuzzleSolver solver;
  auto solution = solver(puzzle);
  if (solution == "0\n" || solution == "-1\n")
  {
    std::cout << solution;
  }
  else
  {
    std::cout << solution.size() << std::endl << solution;
  }
  return 0;
}
