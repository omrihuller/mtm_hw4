/*
 * PrintHelper.h
 *
 *  Created on: May 24, 2015
 *      Author: idansc
 */

#ifndef PRINTHELPER_H_
#define PRINTHELPER_H_
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
namespace mtm{


inline void printCustomerHeader(const string& id){
	cout << "Customer Id: " << id << endl;
}

inline void printBondCustomerDetails(const string& companyName,
		double totalValue, double totalProfit){
	cout << "Bond " << companyName
			<< " Details: Value:" << totalValue << "NIS, Profit: "
			<< totalProfit << "NIS" << endl;
}

inline void printShareCustomerDetails(const string& companyName,
		double totalValue, double totalProfit){
	cout << "Share " << companyName
			<< " Details: Value:" << totalValue << "NIS, Profit: "
			<< totalProfit << "NIS" << endl;
}

inline void printCustomerFooter(double totalValue, double totalProfit, double totalMoneyLeft){
	cout << "Total Portfolio Value: " << totalValue << "nis, " <<
			"Total Portfolio Profit: " << totalProfit << "nis, " <<
			"Money Left: " << totalMoneyLeft << "nis" << endl;
}

inline void printFullReportHeader(){
	cout << "Total Report:" << endl;
}

inline void printFullReportTotalBonds(int totalBonds){
	cout << "Total  Bonds: total: " << totalBonds << endl;
}

inline void printFullReportBondDetails(const string& companyName,
		double value, int amountLeft){
	cout << companyName << " Details: Value:" << value <<
			"nis Amount left: " << amountLeft << endl;
}

inline void printFullReportTotalShares(int totalShares){
	cout << "Total  shares: total: " << totalShares << endl;
}
inline void printFullReportShareDetails(const string& companyName,
		double value, int amount){
	cout << companyName << " Details: Value:" << value <<
			"nis Amount left: " << amount << endl;
}

inline void printFullReportTotalCustomers(int size){
	cout << "Customers: total "<< size << " customers" << endl;
}

inline void printFullReportCustomer(const string& id, double totalPortfolioValue, double totalPortfolioProfit){
	cout << "Customer id: " << id << " total portfolio value: " << totalPortfolioValue
			<< "nis total profit: " << totalPortfolioProfit << endl;
}

inline void printFullReportFooter(double totalValue, double totalProfit){
	cout << "Total customer portfolio value: "<< totalValue << " total portfolio profit: " << totalProfit << endl;
}

}



#endif /* PRINTHELPER_H_ */
