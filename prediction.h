#ifndef PREDICTION_H_
#define PREDICTION_H_

#include <iostream>
using namespace std;

class Prediction {
		double prediction;
		bool canceled;

	public:
		Prediction();
		void cancel();
		bool isCanceled() const;
		double getPrediction() const;
		Prediction& operator =(const double prediction);
		explicit operator double() const;
		Prediction& operator +=(const double prediction);
		Prediction& operator +(const double prediction);
		bool operator==(const Prediction& prediction) const;
		bool operator!=(const Prediction& prediction) const;
		bool operator==(const double prediction) const;
		bool operator!=(const double prediction) const;
};

#endif /* PREDICTION_H_ */
