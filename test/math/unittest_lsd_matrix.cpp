#include <iostream>
#include "gtest/gtest.h"

#include "core/lsd_core.hpp"
#include "generic/lsd_matrix.hpp"

using namespace std;

/**
Template unit test case of CBitfieldCounter class.

@author David Losteiner
@date 2015-01-27
*/
class CMatrixTest : public ::testing::Test
{
protected:
  
    CMatrixTest() { }

    virtual ~CMatrixTest() { }

    //virtual void SetUp() { }

    //virtual void TearDown() { }

    //Foo foo;
};

struct CCMatrixTestTestStruct {
	bool m_inputValue_b;
	uint8_t m_expectedValue_u8;
};

TEST_F( CBitfieldCounterTest , SmokeTest) 
{
	// C'tor

	CCMatrixTestTestStruct l_testVector[1] = { };
		
		
	for(lsd::uint8_t idx_u8; idx_u8 < 1; ++idx_u8)
	{
		ASSERT_EQ(  /*EXPECTED*/ , /* MEASURED */ );

	}

}

