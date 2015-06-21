#include "Security.h"
#include "mtmtest.h"
#include "exception.h"

using namespace mtm;

bool testCreate() {
	//ASSERT_THROW(IllegalSecurityNameException, Security(NULL, 12, 2));
	ASSERT_THROW(IllegalSecurityNameException, Security("AAAAA", 12, 2));
	ASSERT_THROW(IllegalSecurityNameException, Security("AaaA", 12, 2));
	ASSERT_THROW(NegetiveSecurityValueException, Security("NAAT", -3));
	ASSERT_THROW(InvalidSecurityAmountException, Security("NAAT", 23, 0));
	return true;
}

bool testSetValueAndGetValue() {
	Security apple = Security("AAPL", 132.04);
	ASSERT_DOUBLE_EQUALS(132.04, apple.getValue());
	ASSERT_THROW(NegetiveSecurityValueException, apple.setValue(-1));
	ASSERT_NO_THROW(apple.setValue(0));
	ASSERT_DOUBLE_EQUALS(0, apple.getValue());
	ASSERT_NO_THROW(apple.setValue(130));
	ASSERT_DOUBLE_EQUALS(130, apple.getValue());
	return true;
}

bool testSetAmountAndGetAmount() {
	Security apple = Security("AAPL", 132.04);
	Security microsoft = Security("MSFT", 47.61, 10);
	ASSERT_EQUALS(1, apple.getAmount());
	ASSERT_EQUALS(10, microsoft.getAmount());
	ASSERT_THROW(InvalidSecurityAmountException, apple.setAmount(0));
	ASSERT_THROW(InvalidSecurityAmountException, apple.setAmount(-1));
	ASSERT_NO_THROW(apple.setAmount(2));
	ASSERT_DOUBLE_EQUALS(132.04 * 2, apple.getTotalValue());
	ASSERT_EQUALS(2, apple.getAmount());
	return true;
}

bool testGetTotalValue() {
	Security microsoft = Security("MSFT", 47.61, 10);
	ASSERT_DOUBLE_EQUALS(476.1, microsoft.getTotalValue());
	ASSERT_NO_THROW(microsoft.setAmount(300));
	ASSERT_NO_THROW(microsoft.setValue(0));
	ASSERT_DOUBLE_EQUALS(0, microsoft.getTotalValue());
	ASSERT_NO_THROW(microsoft.setValue(200));
	ASSERT_DOUBLE_EQUALS(60000, microsoft.getTotalValue());
	return true;
}

bool testGetName() {
	Security microsoft = Security("MSFT", 47.61, 10);
	ASSERT_EQUALS(true, "MSFT" == microsoft.getName());
	return true;
}

bool testRisk() {
	Security microsoft = Security("MSFT", 45, 10);
	ASSERT_DOUBLE_EQUALS(0, microsoft.risk()); // no forecasts = 0 risk
	microsoft[FIRST_QUARTER] = 45;
	ASSERT_DOUBLE_EQUALS(0, microsoft.risk()); // 1 exact forecast
	microsoft[SECOND_QUARTER] = 35;
	ASSERT_DOUBLE_EQUALS(-5, microsoft.risk());
	microsoft[FIRST_QUARTER] = 35;
	ASSERT_DOUBLE_EQUALS(-10, microsoft.risk());
	microsoft[THIRD_QUARTER] = 65;
	ASSERT_DOUBLE_EQUALS(0, microsoft.risk());
	ASSERT_NO_THROW(microsoft.cancelQuarterPrediction(FIRST_QUARTER));
	ASSERT_DOUBLE_EQUALS(5, microsoft.risk());
	ASSERT_NO_THROW(microsoft.cancelQuarterPrediction(SECOND_QUARTER));
	ASSERT_DOUBLE_EQUALS(20, microsoft.risk());
	return true;
}

bool testCancelQuarterPrediction() {
	Security microsoft = Security("MSFT", 45, 10);
	ASSERT_NO_THROW(microsoft.cancelQuarterPrediction(FIRST_QUARTER));
	return true;
}

bool testPredictions() {
	Security microsoft = Security("MSFT", 45, 10);
	ASSERT_NO_THROW(microsoft.cancelQuarterPrediction(FIRST_QUARTER));
	ASSERT_THROW(QuarterOutOfBound, microsoft[FIRST_QUARTER] = -1);
	ASSERT_NO_THROW(microsoft[FIRST_QUARTER] = 0);
	ASSERT_EQUALS(-45, microsoft.risk());
	ASSERT_NO_THROW(microsoft[FIRST_QUARTER] = (microsoft[FIRST_QUARTER]) + 90);
	ASSERT_EQUALS(45, microsoft.risk());
	ASSERT_NO_THROW(microsoft[SECOND_QUARTER] = 123.4567);
	ASSERT_EQUALS(microsoft[SECOND_QUARTER], 123.4567);
	ASSERT_EQUALS(61.72835, microsoft.risk());
	ASSERT_NO_THROW(microsoft.cancelQuarterPrediction(SECOND_QUARTER));
	ASSERT_EQUALS(45, microsoft.risk());
	ASSERT_THROW(PredictionNotExistException,
			microsoft[FIRST_QUARTER] = (microsoft[SECOND_QUARTER]) + 90); // second in uninitialized
	return true;
}

bool testOperators() {
	Security microsoft = Security("MSFT", 45, 10);
	Security apple = Security("AAPL", 50);
	Security microzift = Security("MSFT", 45);
	ASSERT_NO_THROW(microsoft -= 9);
	ASSERT_THROW(InvalidSecurityAmountException, microsoft -= 1);
	ASSERT_EQUALS(1, microsoft.getAmount());
	ASSERT_THROW(IllegealOperationException,microsoft += apple);
	ASSERT_EQUALS(1, microsoft.getAmount());
	ASSERT_NO_THROW(microsoft += microzift);
	ASSERT_EQUALS(2, microsoft.getAmount());
	ASSERT_EQUALS(10, (microsoft *= 5).getAmount());
	return true;
}

bool testCompare() {
	Security microsoft = Security("MSFT", 45, 10);
	Security apple = Security("AAPL", 50);
	Security microzift = Security("MSFT", 45);
	ASSERT_EQUALS(true, microzift < microsoft);
	ASSERT_NO_THROW(microzift += 9);
	ASSERT_EQUALS(true, microzift == microsoft);
	ASSERT_NO_THROW(apple += 9);
	ASSERT_EQUALS(true, apple > microsoft);
	ASSERT_NO_THROW(apple.setValue(45));
	ASSERT_NO_THROW(apple.setAmount(11));
	ASSERT_EQUALS(true, apple > microsoft);
	ASSERT_NO_THROW(apple -= 1);
	ASSERT_EQUALS(true, apple < microsoft);
	return true;
}

bool testDoubles() {
	Security apple = Security("AAPL", 50);
	Security microzift = Security("MSFT", 45);
	ASSERT_NO_THROW(microzift += 9);
	ASSERT_NO_THROW(apple += 9);
	ASSERT_NO_THROW(apple.setValue(45));
	ASSERT_NO_THROW(apple.setAmount(11));
	ASSERT_EQUALS(450, (double)microzift);
	ASSERT_EQUALS(45*11, (double)apple);
	return true;
}

int main() {
	RUN_TEST(testCreate);
	RUN_TEST(testSetValueAndGetValue);
	RUN_TEST(testSetAmountAndGetAmount);
	RUN_TEST(testGetTotalValue);
	RUN_TEST(testGetName);
	RUN_TEST(testRisk);
	RUN_TEST(testCancelQuarterPrediction);
	RUN_TEST(testPredictions);
	RUN_TEST(testOperators);
	RUN_TEST(testCompare);
	RUN_TEST(testDoubles);
}

