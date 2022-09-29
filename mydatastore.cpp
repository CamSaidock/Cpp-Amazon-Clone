#include <sstream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include "mydatastore.h"
#include "datastore.h"
#include "util.h"

using namespace std;
MyDataStore::MyDataStore() : DataStore() {

}

//Adds a product to the data store
void MyDataStore::addProduct(Product* p) {
	std::set<std::string> keywordSet = p->keywords(); //Create set of Keywords to iterate through
	std::set<std::string>::iterator itr;

	products.push_back(p); //Push back product to easily recreate database file after QUIT

	for(itr = keywordSet.begin(); itr != keywordSet.end(); itr++) {
		if(productMap.find(*itr) == productMap.end()) { //Keyword doesn't exist yet
			std::set<Product*> productSet; //Create new product set
			productSet.insert(p);
			productMap.insert(std::make_pair(*itr, productSet)); //Insert product set into productMap
		}

		else { //Keyword already exists, insert product 
			productMap[*itr].insert(p);
		}
	}
}

//Adds a user to the data store
void MyDataStore::addUser(User* u) {
	std::vector<Product*> userProducts;
	userCart.insert(std::make_pair(u, userProducts));
	userMap.insert(std::make_pair(u->getName(), u));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::vector<Product*> vectorProduct;
	std::set<Product*> setProduct;
	std::set<Product*> termsSet;

	//for each term, add each product into setProduct

	for(unsigned int i = 0; i < terms.size(); i++) {
		if(type == 0) { //AND Search
			termsSet = productMap[terms[0]]; //Initalize termSet so it isn't empty
			setProduct = productMap[terms[i]];
			termsSet = setIntersection(termsSet, setProduct);
		}

		else if(type == 1) { //OR Search
			setProduct = productMap[terms[i]];
			termsSet = setUnion(termsSet, setProduct);
		}
	}

	std::set<Product*>::iterator itr;
	for(itr = termsSet.begin(); itr != termsSet.end(); itr++) {
		vectorProduct.push_back(*itr);
	}

	return vectorProduct;
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << endl;

	for(unsigned int i = 0; i < products.size(); i++) {
    (products[i])->dump(ofile);
  }
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;
	for(map<string, User*>::iterator itr = userMap.begin(); itr != userMap.end(); ++itr) {
    ((itr)->second)->dump(ofile);
  }
	ofile << "</users>" << endl;
}

void MyDataStore::addCart(std::string u, std::string search_hit_string, std::vector<Product*> hits) {
	if(hits.empty()) { //If vector is empty, don't do anything
		cout << "No products available. Search for a product!" << endl;
		return;
	}

	unsigned int search_hit_number = stoi(search_hit_string); //Convert string to integer
	User* user;

	if(search_hit_number > hits.size()) {
		cout << "Enter valid hit number!" << endl;
		return;
	}

	if(userMap.find(u) == userMap.end()) {
		cout << "Error, user doesn't exist" << endl;
		return;
	}
	else {
		user = userMap.find(u)->second;
		userCart[user].push_back(hits[search_hit_number - 1]);
		return;
	}
}

void MyDataStore::viewCart(std::string u) {
	//Search for user's cart
	//In User's cart, go through and display every product.
	User* user;
	user = userMap.find(u)->second;
	vector<Product*> items = (userCart[user]);

	if (items.begin() == items.end()) {
		cout << "Cart is empty!" << endl;
    return;
	}

	for(vector<Product*>::iterator it = items.begin(); it != items.end(); ++it) {
    cout << (*it)->displayString() << endl;
    cout << endl;
  }
}

void MyDataStore::buyCart(std::string u) {

	//Check if you have enough money and if there are enough of the item in stock
	//If you don't have enough money, then add to a new cart, buy other items

	User* user;
	user = userMap.find(u)->second;
	vector<Product*> items = (userCart[user]);

	if (items.begin() == items.end()) { //Check if cart is empty
		cout << "Cart is empty!" << endl;
    return;
	}

	vector<Product*> itemsLeft;

	for(vector<Product*>::iterator it = items.begin(); it != items.end(); ++it) { //Iterate through each item
    if((*it)->getPrice() > user->getBalance()) {
			cout << user->getName() << " doesn't have enough money for: " << (*it)->getName() << " (" << (*it)->getPrice() << ")" << endl;
			itemsLeft.push_back(*it);
		}

		else if((*it)->getQty() == 0) {
			cout << "We are currently out of stock of: " << (*it)->getName() << endl;
		}

		else {
			user->deductAmount((*it)->getPrice());
			(*it)->subtractQty(1);
			cout << user->getName() << " has $" << user->getBalance() << " left." << endl;
		}
  }

	userCart[user] = itemsLeft;
	return;


}