#include "CCondition.h"


using namespace swipe_direction_ns;
using namespace swipe_encoding_ns;


SwipeEncoding CCondition::EncodeSwipe (const CCondition & cond, SwipeDirection move)
{
  switch (move)
  {
    case SwipeDirection::RIGHT:
      return cond.empty_pos % 4 == 3 || cond.direction == SwipeEncoding::LEFT_ENCODING
             ? ERROR_ENCODING
             : RIGHT_ENCODING;
    case SwipeDirection::LEFT:
      return cond.empty_pos % 4 == 0 || cond.direction == SwipeEncoding::RIGHT_ENCODING
             ? ERROR_ENCODING
             : LEFT_ENCODING;
    case SwipeDirection::DOWN:
      return cond.empty_pos / 4 == 3 || cond.direction == SwipeEncoding::UP_ENCODING
             ? ERROR_ENCODING
             : DOWN_ENCODING;
    case SwipeDirection::UP:
      return cond.empty_pos / 4 == 0 || cond.direction == SwipeEncoding::DOWN_ENCODING
             ? ERROR_ENCODING
             : UP_ENCODING;
    default:
      return SwipeEncoding::ERROR_ENCODING;
  }
}

int32_t CCondition::GetPlateNumber (int32_t position) const
{
  return static_cast<int32_t>((layout >> ((1LL * position) << 2)) & 0xF);
}

int32_t CCondition::ComputeInversions () const
{
  register int32_t inversions = 0;
  for (uint8_t i = 0; i < 16; i++)
  {
    for (auto j = static_cast<uint8_t>(i + 1); j < 16; j++)
    {
      if (GetPlateNumber(i) != 0 && GetPlateNumber(j) != 0 &&
          GetPlateNumber(j) < GetPlateNumber(i))
      {
        inversions++;
      }
    }
  }
  return inversions;
}

inline int32_t ComputeRow (int32_t position)
{
  return position >> 2;
}

inline int32_t ComputeColumn (int32_t position)
{
  return position & 3;
}

int32_t CCondition::ComputeHeuristic () const
{
  register uint8_t heuristic = 0;
  for (uint8_t i = 0; i < 16; i++)
  {
    if (GetPlateNumber(i) == 0)
    {
      continue;
    }
    heuristic += 4 * (std::abs(ComputeColumn(i) - (ComputeColumn(GetPlateNumber(i) - 1)))
                      + std::abs(ComputeRow(i) - ComputeRow(GetPlateNumber(i) - 1)));
  }
  for (uint8_t i = 0; i < 16; i++)
  {
    if (i == empty_pos)
    {
      continue;
    }
    for (auto j = static_cast<uint8_t>(i + 1); j < 16; j++)
    {
      if (j == empty_pos)
      {
        continue;
      }
      if (ComputeRow(i) == ComputeRow(GetPlateNumber(i) - 1) &&
          ComputeRow(i) == ComputeRow(j) &&
          ComputeRow(j) == ComputeRow(GetPlateNumber(j) - 1) &&
          GetPlateNumber(i) > GetPlateNumber(j))
      {
        heuristic += 2;
      }
      if (ComputeColumn(i) == ComputeColumn(GetPlateNumber(i) - 1) &&
          ComputeColumn(i) == ComputeColumn(j) &&
          ComputeColumn(j) == ComputeColumn(GetPlateNumber(j) - 1) &&
          GetPlateNumber(i) > GetPlateNumber(j))
      {
        heuristic += 2;
      }
    }
  }
  return heuristic / 2;
}

bool CCondition::IsSolvable () const
{
  int32_t inversions = ComputeInversions();
  return !(inversions & 1) == ((empty_pos >> 2) & 1);
}

bool CCondition::IsSolved () const
{
  return layout == 0x0FEDCBA987654321ULL;
}

void CCondition::Swap (int32_t first_pos, int32_t second_pos)
{
  int32_t first = GetPlateNumber(first_pos);
  int32_t second = GetPlateNumber(second_pos);
  uint64_t delta_first = layout & ((1LL << (first_pos << 2)) - 1);
  layout >>= 4 * first_pos + 4;
  layout <<= 4;
  layout |= second;
  layout <<= 4 * first_pos;
  layout |= delta_first;
  uint64_t delta_second = layout & ((1LL << (second_pos << 2)) - 1);
  layout >>= 4 * second_pos + 4;
  layout <<= 4;
  layout |= first;
  layout <<= 4 * second_pos;
  layout |= delta_second;
}