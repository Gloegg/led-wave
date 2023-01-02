#include "Utils.hpp"

int Utils::getIndexFromPos( int col, int row )
{
  if ( row < 0 || row >= LED_ROWS || col < 0 || col >= LED_COLUMNS )
  {
    return -1;
  }
#ifdef LED_ZIG_ZAG
  if ( row % 2 == 1 )
  {
    col = LED_COLUMNS - 1 - col;
  }
#endif
  return LED_COLUMNS * row + col;
}
