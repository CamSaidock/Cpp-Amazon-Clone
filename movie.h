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

class Movie : public Product {
public:
	Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
	std::string displayString() const;
	std::set<std::string> keywords() const;
	void dump(std::ostream& os) const;

	std::string getGenre() const;
	std::string getRating() const;

private:
	std::string genre_;
	std::string rating_;
};