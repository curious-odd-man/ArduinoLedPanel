#include <cxxtest/TestSuite.h>
#include "TimeProgram.h"

  class MyTestSuite : public CxxTest::TestSuite
  {
  public:
      void testTimerDotIsBlinking( void )
      {
          TimeProgram tp;

          TS_ASSERT( 1 + 1 > 1 );
          TS_ASSERT_EQUALS( 1 + 1, 2 );
      }
  };
