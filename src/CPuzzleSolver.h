#ifndef SRC_CPUZZLESOLVER_H
#define SRC_CPUZZLESOLVER_H

#include <algorithm>     // std::for_each
#include <list>          // std::list
#include <string>        // std::string
#include <queue>         // std::priority_queue
#include <unordered_map> // std::unordered_map
#include <vector>        // std::vector, std::pair

#include "CPuzzle.h"
#include "SwipeDirection.h"
#include "SwipeEncoding.h"


class CPuzzleSolver
{

public:

  std::string operator() (const CPuzzle & game_puzzle);

private:

  void launchAStarSearch (std::list<char> & answer) const;

  void restoreSwipes (std::list<char> & answer, uint64_t current_layout,
                      const std::unordered_map<uint64_t, std::pair<char, uint64_t> > & path) const;

private:

  CPuzzle puzzle;

};


#endif //SRC_CPUZZLESOLVER_H
