#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <map>
#include "datastore.h"
#include "user.h"

class MyDataStore : public DataStore {
public:
	MyDataStore();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	void addCart(std::string u, std::string search_hit_string, std::vector<Product*> hits);
	void viewCart(std::string u);
	void buyCart(std::string u);

private:
	std::vector<Product*> products;
	std::map<std::string, User*> userMap;
	std::map<User*, std::vector<Product*>> userCart;
	std::map<std::string, std::set<Product*>> productMap;
};

