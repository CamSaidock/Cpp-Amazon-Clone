#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

using namespace std;
Clothing::Clothing(const string category, const string name, double price, int qty, const string size, const string brand) :
	Product(category, name, price, qty),
	size_(size),
  brand_(brand)
{

}

string Clothing::getSize() const
{
	return size_;
}

string Clothing::getBrand() const
{
	return brand_;
}

string Clothing::displayString() const {
	string display;
	display = getName() + "\n" + "Size: " + getSize() + " Brand: " + getBrand() + "\n" + to_string(getPrice()) + "\n" + to_string(getQty()) + " Left";
	return display;
}

set<string> Clothing::keywords() const {
	set<string> returnSet;

	set<string> temp = parseStringToWords(getBrand());
	returnSet.insert(temp.begin(), temp.end());

	temp = parseStringToWords(getName());
	returnSet.insert(temp.begin(), temp.end());

	return returnSet;
}

void Clothing::dump(ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
