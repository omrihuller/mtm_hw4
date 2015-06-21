#include <iostream>
#include "prediction.h"
#include "exception.h"
#include "math.h"

using namespace std;

Prediction::Prediction(){
	prediction = 0;
	canceled = false;
}

void Prediction::cancel() {
	canceled = true;
}

bool Prediction::isCanceled() const {
	return canceled;
}

double Prediction::getPrediction() const {
	if (canceled) {
		return -1;
	}

	return prediction;
}

Prediction& Prediction::operator=(const double prediction) {
	if(prediction < 0){
		throw QuarterOutOfBound();
	}
	this->prediction = prediction;
	canceled = false;

	return *this;
}

Prediction::operator double() const{
	return prediction;
}

Prediction& Prediction::operator +=(const double prediction) {
	if (isCanceled()) {
		throw PredictionNotExistException();
	}

	if((this->prediction + prediction) < 0) {
		throw QuarterOutOfBound();
	}

	this->prediction += prediction;
	canceled = false;

	return *this;
}

Prediction& Prediction::operator +(const double prediction) {
	Prediction* p = new Prediction(*this);
	*p += prediction;

	return *p;
}

bool Prediction::operator==(const Prediction& prediction) const {
	return *this == prediction.prediction &&
			this->canceled == prediction.canceled;
}

bool Prediction::operator!=(const Prediction& prediction) const {
	return !(*this == prediction);
}

bool Prediction::operator==(const double prediction) const {
	return fabs(this->prediction - prediction) < 1e-10;
}

bool Prediction::operator !=(const double prediction) const {
	return !(*this == prediction);
}

