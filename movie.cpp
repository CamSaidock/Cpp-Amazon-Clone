#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, const string genre, const string rating) :
	Product(category, name, price, qty),
	genre_(genre),
  rating_(rating)

{


}

string Movie::getGenre() const
{
		return genre_;
}

string Movie::getRating() const
{
		return rating_;
}

string Movie::displayString() const {
	string display;
	display = getName() + "\n" + "Genre: " + getGenre() + "Rating:" + getRating() + "\n" + to_string(getPrice()) + to_string(getQty()) + "Left";
	return display;
}

set<string> Movie::keywords() const {
	set<string> returnSet;

	set<string> temp = parseStringToWords(getGenre());
	returnSet.insert(temp.begin(), temp.end());

	return returnSet;
}

void Movie::dump(ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}
