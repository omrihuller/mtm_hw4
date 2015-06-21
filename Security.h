#ifndef  SECURITY_H_
#define  SECURITY_H_

#include <iostream>
#include "prediction.h"
using namespace std;

namespace mtm {

enum QuarterType {
	FIRST_QUARTER,
	SECOND_QUARTER,
	THIRD_QUARTER,
	FOURTH_QUARTER
};

class Security {
		string name;
		double price;
		int amount;
		Prediction quarters[4];

	public:
		Security(const char* name, double price, int amount = 1);
		string getName() const;
		void setValue(double price);
		void setAmount(int amount);
		void cancelQuarterPrediction(const QuarterType& type);
		double getTotalValue() const;
		double risk() const;
		const Prediction& operator [](const QuarterType& type) const;
		Prediction& operator [](const QuarterType& type);
		Security& operator +=(int amount);
		Security& operator -=(int amount);
		Security& operator *=(int amount);
		Security& operator +=(const Security& security);
		Security& operator -=(const Security& security);
		Security& operator *=(const Security& security);

		bool operator >(Security security);
		bool operator >=(Security security);
		bool operator ==(Security security);
		bool operator <=(Security security);
		bool operator <(Security security);
		bool operator !=(Security security);

		explicit operator double() const;
};

} // namespace mtm

#endif /* SECURITY_H_ */
