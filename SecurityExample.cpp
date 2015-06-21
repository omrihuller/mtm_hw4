/*
 * SecurityExample.cpp
 *
 *  Created on: May 28, 2015
 *      Author: idansc
 */

#include "Security.h"
#include "mtmtest.h"
#include "exception.h"

using namespace mtm;

bool basicSecurityExample() {
	Security apple = Security("AAPL",132.04);
	Security microsoft = Security("MSFT",47.61,10);
	ASSERT_NO_THROW(microsoft.setAmount(5));
	ASSERT_NO_THROW(microsoft.setValue(47.7));

	ASSERT_DOUBLE_EQUALS(238.5,microsoft.getTotalValue());

	ASSERT_EQUALS(false, apple == microsoft);
	ASSERT_EQUALS(true, apple != microsoft);
	ASSERT_EQUALS(false, apple < microsoft);
	ASSERT_EQUALS(false, apple <= microsoft);
	ASSERT_EQUALS(true, apple > microsoft);
	ASSERT_EQUALS(true, apple >= microsoft);
	/*
	 * Define
	 * enum QuarterType{
		FIRST_QUARTER,
		SECOND_QUARTER,
		THIRD_QUARTER,
		FOURTH_QUARTER
	};
	in your h file.
	 */
	apple[FIRST_QUARTER] = 115.6;
	apple[SECOND_QUARTER] = 119.5;
	ASSERT_DOUBLE_EQUALS(-14.49,apple.risk());
	apple[THIRD_QUARTER] = 180;
	apple[FOURTH_QUARTER] = apple[THIRD_QUARTER];

	ASSERT_DOUBLE_EQUALS(16.735,apple.risk());

	apple.cancelQuarterPrediction(SECOND_QUARTER);
	apple.cancelQuarterPrediction(FOURTH_QUARTER);
	ASSERT_DOUBLE_EQUALS(15.76,apple.risk());

	ASSERT_NO_THROW(apple += (apple += 2));
	Security apple2 = Security("AAPL",132.04,3);
	ASSERT_NO_THROW(apple -= (apple2 -= 2));
	ASSERT_NO_THROW(apple *= (apple *= 2));

	double  totalValueOfMicrosoftAndApple;
	ASSERT_NO_THROW(totalValueOfMicrosoftAndApple = (double)apple + (double)microsoft);
	ASSERT_EQUALS(13442.5,totalValueOfMicrosoftAndApple);
	return true;

}


int main3() {
	RUN_TEST(basicSecurityExample);

	return 0;
}
