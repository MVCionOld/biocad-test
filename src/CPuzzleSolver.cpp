#include "CPuzzleSolver.h"

using namespace swipe_direction_ns;
using namespace swipe_encoding_ns;


std::string CPuzzleSolver::operator() (const CPuzzle & game_puzzle)
{
  this->puzzle.condition = game_puzzle.condition;
  if (game_puzzle.condition.IsSolved())
  {
    return "0\n";
  }
  else if (!game_puzzle.condition.IsSolvable())
  {
    return "-1\n";
  }
  else
  {
    std::list<char> solution;
    launchAStarSearch(solution);
    std::string solution_str;
    std::for_each(solution.rbegin(), solution.rend(), [&solution_str] (char move) {
      solution_str.push_back(move);
    });
    return solution_str;
  }
}


class Comparator
{

public:

  bool operator() (const std::pair<int32_t, CCondition> & arg0,
                   const std::pair<int32_t, CCondition> & arg1)
  {
    return arg0.first >= arg1.first;
  }
};


void CPuzzleSolver::launchAStarSearch (std::list<char> & answer) const
{
  std::priority_queue<std::pair<int32_t, CCondition>,
          std::vector<std::pair<int, CCondition> >,
          Comparator> conditions;
  conditions.push(std::make_pair(0, puzzle.condition));
  std::unordered_map<uint64_t, std::pair<char, uint64_t> > path;
  path.emplace(puzzle.condition.layout, std::make_pair('\0', 0));
  CCondition current_condition, next_condition;
  while (!next_condition.IsSolved())
  {
    current_condition = conditions.top().second;
    conditions.pop();
    for (SwipeDirection move: {RIGHT, LEFT, UP, DOWN})
    {
      next_condition = puzzle.swipe(current_condition, move);
      next_condition.total_swipes++;
      if (next_condition.IsSolved())
      {
        path.emplace(next_condition.layout,
                     std::make_pair(next_condition.direction, current_condition.layout)
        );
        break;
      }
      if (next_condition.layout != 0 && path.find(next_condition.layout) == path.end())
      {
        path.emplace(next_condition.layout,
                     std::make_pair(next_condition.direction, current_condition.layout)
        );
        int32_t heuristic = next_condition.total_swipes + next_condition.ComputeHeuristic();
        conditions.emplace(heuristic, next_condition);
      }
    }
  }
  restoreSwipes(answer, next_condition.layout, path);
}

void CPuzzleSolver::restoreSwipes (std::list<char> & answer, uint64_t current_layout,
                                   const std::unordered_map<uint64_t, std::pair<char, uint64_t> > & path) const
{
  register char direction = '#';
  while (direction != '\0')
  {
    std::tie(direction, current_layout) = path.at(current_layout);
    answer.push_back(direction);
  }
  answer.pop_back();
}
