#include "CppUTest/TestHarness.h"

extern "C" {
#include "MA_Filter.h"
#include "stddef.h"
}

TEST_GROUP(MAFilter)
{
	iMA_Filter filter;
	unsigned int size;
	void setup()
	{

	}

	void teardown()
	{

	}
};


TEST(MAFilter, ProtectionAgainstNullPointer)
{
	MA_FilterReset(NULL);
	MA_FilterPush(NULL,0);
	MA_FilterGetValue(NULL);
	MA_FilterDestroy(NULL);
}

TEST(MAFilter,InitiallyGetValueReturnsZero)
{
	filter = MA_FilterCreate(1);

	LONGS_EQUAL(0, MA_FilterGetValue(filter));

	MA_FilterDestroy(filter);
}

TEST(MAFilter, UnitySizeFilterReturnsLastValue)
{
	int input[10] = {9,2,3,7,1,8,5,4,6};

	filter = MA_FilterCreate(1);

	for(int i = 0; i < 10; i++)
	{
		MA_FilterPush(filter,input[i]);
		LONGS_EQUAL(input[i], MA_FilterGetValue(filter));
	}

	MA_FilterDestroy(filter);
}

TEST(MAFilter, FiltersAreIndependent)
{
	iMA_Filter another_filter;

	filter = MA_FilterCreate(1);
	another_filter = MA_FilterCreate(1);

	MA_FilterPush(filter, 123);

	LONGS_EQUAL(0, MA_FilterGetValue(another_filter));

	MA_FilterDestroy(filter);
	MA_FilterDestroy(another_filter);
}

TEST(MAFilter,MovingWindowIsInitializedByZeros)
{
	size = 10;
	filter = MA_FilterCreate(size);

	for(int i = 0; i < 6; i++)
	{
		MA_FilterPush(filter,0);
		
		
		LONGS_EQUAL(0, MA_FilterGetValue(filter));
		if( MA_FilterGetValue(filter) != 0)
		{
			FAIL("Window buffer might contain garbage after memmory allocation");
		}
	}
	MA_FilterDestroy(filter);
}

TEST(MAFilter, ImpulseResponseOfAnArbitrarySizeFilter)
{
	size = 13;
	int expected = 123;
	int input = expected*size;

	filter = MA_FilterCreate(size);

	MA_FilterPush(filter, input);

	for (int i = 0; i < size; i++)
	{
		LONGS_EQUAL(expected, MA_FilterGetValue(filter));

		MA_FilterPush(filter, 0);
	}

	LONGS_EQUAL(0, MA_FilterGetValue(filter));

	MA_FilterDestroy(filter);
}

TEST(MAFilter, ResetFillsWindowWithZeros)
{
	size = 5;
	filter = MA_FilterCreate(size);

	MA_FilterPush(filter,123);

	MA_FilterReset(filter);

	for (int i = 0; i < size; i++)
	{
		LONGS_EQUAL(0, MA_FilterGetValue(filter));
	}

	MA_FilterDestroy(filter);
}

TEST(MAFilter, ZeroSizeFilterAlwaysReturnsZero)
{
	filter = MA_FilterCreate(0);

	int input[10] = {9,2,3,7,1,8,5,4,6};

	for(int i = 0; i < 10; i++)
	{
		MA_FilterPush(filter,input[i]);
		LONGS_EQUAL(0, MA_FilterGetValue(filter));
	}

	MA_FilterDestroy(filter);
}