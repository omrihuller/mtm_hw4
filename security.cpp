#include <iostream>
#include <string.h>
#include "Security.h"
#include "CompareDouble.h"
#include "exception.h"
#include "prediction.h"
#include "math.h"

using namespace std;
using namespace mtm;

static bool doublesEqual(double d1, double d2) {
	const double EPSILON = 1e-10;
	return fabs(d1 - d2) < EPSILON;
}

Security::Security(const char* name, double price, int amount) {
	int nameLen = strlen(name);
	if (nameLen == 0 || nameLen > 4) {
		throw IllegalSecurityNameException();
	}

	int i = 0;
	while(name[i] != '\0') {
		if(name[i] < 'A' || name[i] > 'Z') {
			throw IllegalSecurityNameException();
		}
		i++;
	}

	this->name = name;

	if( amount <= 0) {
		throw InvalidSecurityAmountException();
	}
	this->amount = amount;

	if(price <= 0) {
		throw NegetiveSecurityValueException();
	}
	this->price = price;

	for(int i = 0; i < 4; i++) {
		quarters[i] = 0;
		quarters[i].cancel();
	}
}

string Security:: getName() const {
	return this->name;
}

void Security:: setAmount(int amount) {
	if( amount <= 0) {
		throw InvalidSecurityAmountException();
	}
	this->amount = amount;
}

void Security::setValue(double price) {
	if(price < 0) {
		throw NegetiveSecurityValueException();
	}
	this->price = price;
}

void Security::cancelQuarterPrediction(const QuarterType& type) {
	quarters[type].cancel();
}

double Security:: getTotalValue() const {
	return amount*price;
}

double Security::risk() const {
	int count = 0;
	double sum = 0;
	for(int i = 0; i < 4; i++) {
		if(!quarters[i].isCanceled()) {
			sum += (double)quarters[i] - price;
			count++;
		}
	}
	return count == 0 ? 0 : sum / count;
}

const Prediction& Security:: operator [](const QuarterType& type) const {
	return quarters[(int)type];
}

Prediction& Security:: operator [](const QuarterType& type) {
	return quarters[(int)type];
}

Security& Security:: operator +=(int amount) {
	if( this->amount + amount <= 0) {
		throw InvalidSecurityAmountException();
	}

	this->amount += amount;

	return *this;
}

Security& Security:: operator -=(int amount) {
	if( this->amount - amount <= 0) {
		throw InvalidSecurityAmountException();
	}

	this->amount -= amount;

	return *this;
}

Security& Security:: operator *=(int amount) {
	if( this->amount * amount <= 0) {
		throw InvalidSecurityAmountException();
	}

	this->amount *= amount;

	return *this;
}

Security& Security:: operator +=(const Security& security) {
	if (this->name != security.name) {
		throw IllegealOperationException();
	}

	return *this += security.amount;
}

Security& Security:: operator -=(const Security& security) {
	if (this->name != security.name) {
		throw IllegealOperationException();
	}

	return *this -= security.amount;
}

Security& Security:: operator *=(const Security& security) {
	if (this->name != security.name) {
		throw IllegealOperationException();
	}

	return *this *= security.amount;
}

bool Security:: operator >(Security security) {
	if(!doublesEqual(this->price, security.price)) {
		return compareIsBigger(this->price, security.price);
	}

	if (this->amount != security.amount) {
		return this->amount > security.amount;
	}

	return this->name > security.name;
}

bool Security:: operator <(Security security) {
	return !(*this >= security);
}

bool Security:: operator >=(Security security) {
	return *this > security || *this == security;
}

bool Security:: operator ==(Security security) {
	if(doublesEqual(this->price, security.price) && this->amount == security.amount) {
		if (this->name == security.name) {
			return true;
		}
	}
	return false;
}

bool Security:: operator <=(Security security) {
	return !(*this > security);
}


bool Security:: operator !=(Security security) {
	return !(*this == security);
}

Security::operator double() const {
	return getTotalValue();
}
