#include <iostream>
#include "gtest/gtest.h"

#include "core/lsd_core.hpp"
#include "generic/lsd_generic.hpp"

using namespace std;

/**
Template unit test case of CBitfieldCounter class.

@author David Losteiner
@date 2014-08-17
*/
class CBitfieldCounterTest : public ::testing::Test
{
protected:
  
    CBitfieldCounterTest() { }

    virtual ~CBitfieldCounterTest() { }

    //virtual void SetUp() { }

    //virtual void TearDown() { }

    //Foo foo;
};

struct CBitfieldCounterTestStruct {
	bool m_inputValue_b;
	uint8_t m_expectedValue_u8;
};

TEST_F( CBitfieldCounterTest , SmokeTest) 
{
	lsd::CBitfieldCounter<lsd::uint64_t, 8> l_bitfield;

	//cout << "Mask: "<< hex << l_bitfield.getMask() << endl;

	CBitfieldCounterTestStruct l_boolList_ab[29] = {
		{ true, 1}, // 0
		{ true, 2}, // 1
		{ false,2}, // 2
		{ true, 3}, // 3
		{ false,3}, // 4
		{ false,3}, // 5
		{ false,3}, // 6
		{ true, 4}, // 7
		{ false,3}, // 8
		{ true, 3}, // 9
		{ true, 4}, // 10
		{ true, 4}, // 11
		{ true, 5}, // 12
		{ true, 6}, // 13
		{ true, 7}, // 14
		{ true, 7}, // 15 *
		{ true, 8}, // 16
		{ true, 8}, // 17
		{ true, 8}, // 18
		{ false,7}, // 19
		{ false,6}, // 20
		{ false,5}, // 21
		{ false,4}, // 22
		{ false,3}, // 23
		{ false,2}, // 24
		{ false,1}, // 25
		{ false,0}, // 26
		{ false,0}, // 27
		{ true, 1} }; // 28

	for(lsd::uint8_t idx_u8; idx_u8 < 29; ++idx_u8)
	{
		l_bitfield.update( l_boolList_ab[idx_u8].m_inputValue_b);
		cout << "IDX:" << static_cast<uint32_t>(idx_u8) << " Added:"<<  l_boolList_ab[idx_u8].m_inputValue_b << "\tresult:" << static_cast<lsd::uint32_t>( l_bitfield.get() ) << endl;
		ASSERT_EQ(  l_boolList_ab[idx_u8].m_expectedValue_u8 , l_bitfield.get() );

	}

}

