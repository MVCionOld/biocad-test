#include "CPuzzle.h"


using namespace swipe_direction_ns;
using namespace swipe_encoding_ns;


std::istream & operator>> (std::istream & is, CPuzzle & puzzle)
{
  uint64_t buffer;
  for (uint8_t i = 0; i < 16; i++)
  {
    is >> buffer;
    if (buffer == 0)
    {
      puzzle.condition.empty_pos = i;
    }
    puzzle.condition.layout |= buffer << (i * 4);
  }
  return is;
}

CCondition CPuzzle::swipe (const CCondition & cond, SwipeDirection move) const
{
  SwipeEncoding encoding = CCondition::EncodeSwipe(cond, move);
  if (encoding == SwipeEncoding::ERROR_ENCODING)
  {
    return CCondition();
  }
  CCondition new_cond(cond);
  new_cond.direction = encoding;
  new_cond.Swap(new_cond.empty_pos, new_cond.empty_pos + move);
  new_cond.empty_pos = new_cond.empty_pos + move;
  return new_cond;
}