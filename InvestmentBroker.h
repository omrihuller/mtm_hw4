/*
 * InvesmentBroker.h
 * Module to handle trade. 
 */

#ifndef INVESTMENTBROKER_H_
#define INVESTMENTBROKER_H_

#include <string>
using std::string;

namespace mtm {
	
	enum RequestType{ LOW_RISK, HIGH_RISK } ;
	enum PaperType { PAPER_SHARE,PAPER_BOND,PAPER_BOTH };
	
class InvestmentBroker {
public:

	/*
	 * Adds a new share to the broker's shares database.
	 * */
	void addShare(const string& name, double value, int amount = 1);

	/*
	 *  Adds a new bond to the broker's bonds database.
	 *  */
	void addBond(const string& name, double value, int amount = 1);

	/*
	 *  Adds a new customer to the broker's customer database
	 *   */
	void addCustomer(const string& id, double money,
			RequestType type);

	/* indication that a new trade day started.
	 * updates the customers' bonds,
	 * execute two users request.
	 */
	void nextTradeDay();

	/*
	 * sell the customer portfolio and adds the sell value to the customer
	 * */
	void sellPortfolio(const string& id);

	/*
	 * Let the given user change his investment type, we can add priority to handle the request.
	 */
	void changePreference(const string& id, RequestType type, int priority=1);
	
	/*
	 * print customer report with specific type of securities
	 */
	void printCustomerReport(const string& id,PaperType paperType=PAPER_BOTH);

	/*
	 * print full report
	 */
	void printFullReport();



private:
	/*you should add data structures*/
};

} /* namespace mtm */

#endif /* INVESTMENTBROKER_H_ */
