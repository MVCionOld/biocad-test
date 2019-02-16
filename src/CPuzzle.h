#ifndef SRC_CPUZZLE_H
#define SRC_CPUZZLE_H

#include <iostream>         // std::istream, std::ostream, std::cin, std::cout

#include "CCondition.h"     // CCondition
#include "SwipeDirection.h" // swipe_direction_ns::SwipeDirection


class CPuzzle
{

  friend class CPuzzleSolver;


public:

  CPuzzle () = default;

  ~CPuzzle () = default;

  CPuzzle & operator= (const CPuzzle & puzzle) = default;

  friend std::istream & operator>> (std::istream & is, CPuzzle & puzzle);

private:

  CCondition swipe (const CCondition & cond,
                    swipe_direction_ns::SwipeDirection move) const;

public:

  CCondition condition;
};


#endif //SRC_CPUZZLE_H
