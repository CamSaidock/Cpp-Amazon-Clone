#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;
Book::Book(const string category, const string name, double price, int qty, const string author, const string isbn) :
	Product(category, name, price, qty),
	author_(author),
  isbn_(isbn)
{

}

string Book::getAuthor() const
{
	return author_;
}

string Book::getISBN() const
{
	return isbn_;
}



string Book::displayString() const {
	string display;

	ostringstream priceFormatted;
	priceFormatted << fixed << setprecision(2) << getPrice();

	display = getName() + "\n" + "Author: " + getAuthor() + " ISBN: " + getISBN() + "\n" + priceFormatted.str() + " " + to_string(getQty()) + " left.";
	return display;
}

set<string> Book::keywords() const {
	set<string> returnSet;

	set<string> temp = parseStringToWords(getAuthor());
	returnSet.insert(temp.begin(), temp.end());

	temp = parseStringToWords(getName());
	returnSet.insert(temp.begin(), temp.end());

	returnSet.insert(getISBN());

	return returnSet;
}

void Book::dump(ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}