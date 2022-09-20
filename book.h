#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

/*

Implementing the keywords() which returns the appropriate keywords 
to index the product, displayString() [to create a string that contains 
the product info] and dump() [that outputs the database format of the 
product info].

*/

class Book : public Product {
public:
	Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);
	std::string displayString() const;
	std::set<std::string> keywords() const;
	void dump(std::ostream& os) const;

	std::string getAuthor() const;
	std::string getISBN() const;

private:
	std::string author_;
	std::string isbn_;
};