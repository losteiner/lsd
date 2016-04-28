#include <iostream>
#include "gtest/gtest.h"

#include "lsd/core/lsd_core.hpp"
#include "lsd/generic/lsd_ringbuffer.hpp"

using namespace std;

/**
Template unit test case of CRingBuffer class.

@author David Losteiner
@date 2015-02-17
*/
class CRingBufferTest : public ::testing::Test
{
protected:
  
    CRingBufferTest() { }

    virtual ~CRingBufferTest() { }

    //virtual void SetUp() { }

    //virtual void TearDown() { }

    //Foo foo;
};

struct CRingBufferTestStruct {
	lsd::uint32_t m_inputValue_u32;
	lsd::uint32_t m_sizeExpectedValue_u32;
	lsd::uint32_t m_frontExpectedValue_u32;
	lsd::uint32_t m_backExpectedValue_u32;
};

TEST_F( CRingBufferTest , SmokeTestPush) 
{
	lsd::TRingBuffer<lsd::uint32_t, 5> l_ringBuffer;

	CRingBufferTestStruct l_testVector_au32[10] = {
		{  13,  1 , 13,   13}, // 0
		{  66,  2 , 66,   13}, // 1
		{   1,  3 ,  1,   13}, // 2
		{ 333,  4 ,333,   13}, // 3
		{  84,  5 , 84,   13}, // 4
		{ 101,  5 ,101,   66}, // 5
		{   0,  5 ,  0,    1}, // 6
		{   9,  5 ,  9,  333}, // 7
		{  20,  5 ,  20,  84}, // 8
		{   4,  5 ,  4,  101}  // 9
		};

	for(lsd::uint8_t idx_u8=0; idx_u8 < 10; ++idx_u8)
	{
		l_ringBuffer.push( l_testVector_au32[idx_u8].m_inputValue_u32);
		//cout << "IDX:" << static_cast<uint32_t>(idx_u8) << "\tPushed:"<<  l_testVector_au32[idx_u8].m_inputValue_u32 << "\tsize:" << l_ringBuffer.size() << "\tfront:" << l_ringBuffer.front() << "\tback:" << l_ringBuffer.back() << endl;
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_sizeExpectedValue_u32 , l_ringBuffer.size() );
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_frontExpectedValue_u32 , l_ringBuffer.front() );
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_backExpectedValue_u32 , l_ringBuffer.back() );

	}

}

TEST_F( CRingBufferTest , SmokeTestPop) 
{
	lsd::TRingBuffer<lsd::uint32_t, 5> l_ringBuffer;

	CRingBufferTestStruct l_testVector_au32[5] = {
		{  13,  4 ,		84,    66}, // 0
		{  66,  3 ,		84,     1}, // 1
		{   1,  2 ,		84,   333}, // 2
		{ 333,  1 ,		84,    84}, // 3
		{  84,  0 ,		84,    13}, // 4
		};

	for(lsd::uint8_t idx_u8=0; idx_u8 < 5; ++idx_u8)
	{
		l_ringBuffer.push( l_testVector_au32[idx_u8].m_inputValue_u32);
		//cout << "IDX:" << static_cast<uint32_t>(idx_u8) << "\tPushed:"<<  l_testVector_au32[idx_u8].m_inputValue_u32 << "\tsize:" << l_ringBuffer.size() << "\tfront:" << l_ringBuffer.front() << "\tback:" << l_ringBuffer.back() << endl;
		
	}
	
	for(lsd::uint8_t idx_u8=0; idx_u8 < 5; ++idx_u8)
	{
		lsd::uint32_t l_popped_u32 = 0xFFFFFFFF;
		l_ringBuffer.pop(l_popped_u32);
		//cout << "IDX:" << static_cast<uint32_t>(idx_u8) << "\tPopped:"<<  l_popped_u32 << "\tsize:" << l_ringBuffer.size() << "\tfront:" << l_ringBuffer.front() << "\tback:" << l_ringBuffer.back() << endl;
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_sizeExpectedValue_u32 , l_ringBuffer.size() );
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_frontExpectedValue_u32 , l_ringBuffer.front() );
		ASSERT_EQ(  l_testVector_au32[idx_u8].m_backExpectedValue_u32 , l_ringBuffer.back() );
	}

}
