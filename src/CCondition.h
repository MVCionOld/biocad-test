#ifndef SRC_CCONDITION_H
#define SRC_CCONDITION_H

#include <cmath>         // std::abs
#include <inttypes.h>    // int8_t, uint8_t, int32_t, uint64_t

#include "SwipeDirection.h"
#include "SwipeEncoding.h"


struct CCondition
{
  CCondition () :
          direction('\0'),
          empty_pos(-1),
          layout(0),
          total_swipes(0)
  {}

  CCondition (const CCondition & condition) :
          empty_pos(condition.empty_pos),
          direction(condition.direction),
          layout(condition.layout),
          total_swipes(condition.total_swipes)
  {}

  ~CCondition () = default;

  CCondition & operator= (const CCondition & condition) = default;

  int32_t GetPlateNumber (int32_t position) const;

  int32_t ComputeInversions () const;

  int32_t ComputeHeuristic () const;

  bool IsSolvable () const;

  bool IsSolved () const;

  void Swap (int32_t first_pos, int32_t second_pos);

  static swipe_encoding_ns::SwipeEncoding
  EncodeSwipe (const CCondition & cond, swipe_direction_ns::SwipeDirection move);

public:

  int32_t empty_pos;

  int32_t total_swipes;

  uint64_t layout;

  char direction;

};


#endif //SRC_CCONDITION_H
