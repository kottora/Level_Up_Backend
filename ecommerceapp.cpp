#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Product;

map<string, Product*> Catalog;
vector<Product*>* Orders_Report = NULL;

enum Command {
	error, save_product, purchase_product, order_product, get_quantity_of_product,
	get_average_price, get_product_profit, get_fewest_product, get_most_popular_product, Exit,
	get_orders_report, export_orders_report
};

class Product
{
	string ProductID, ProductName, Order_History;
	double Price, Purchase_price, Purchased, Sold;
	int purchase_quantity, order_quantity;

public:

	Product();
	Product(string ProductID, string ProductName, double Price);
	~Product();
	string get_ProductID()const
	{
		return ProductID;
	}
	string get_ProductName()const
	{
		return ProductName;
	}
	string get_Order_History()const
	{
		return Order_History;
	}
	double get_Price()const
	{
		return Price;
	}
	double get_Purchased()const
	{
		return Purchased;
	}
	double get_Sold()const
	{
		return Sold;
	}
	int get_purchase_quantity()const
	{
		return purchase_quantity;
	}
	int get_order_quantity()const
	{
		return order_quantity;
	}
	double get_Purchase_price()const
	{
		return Purchase_price;
	}
	void set_ProductID(string ProductID)
	{
		this->ProductID = ProductID;
	}
	void set_ProductName(string ProductName)
	{
		this->ProductName = ProductName;
	}
	void set_Order_History(string Order_History)
	{
		this->Order_History = Order_History;
	}
	void set_Price(double Price)
	{
		this->Price = Price;
	}
	void set_Purchased(double Purchased)
	{
		this->Purchased = Purchased;
	}
	void set_Sold(double Sold)
	{
		this->Sold = Sold;
	}
	void set_purchase_quantity(int purchase_quantity)
	{
		this->purchase_quantity = purchase_quantity;
	}
	void set_order_quantity(int order_quantity)
	{
		this->order_quantity = order_quantity;
	}
	void set_Purchase_price(double Purchase_price)
	{
		this->Purchase_price = Purchase_price;
	}

	int get_remaining_quanitity()const
	{
		return purchase_quantity - order_quantity;
	}
	double get_COGS()const
	{
		return this->get_Purchased() - get_remaining_quanitity() * get_Price();
	}
};

Product::Product()
{
	ProductID = ProductName = Order_History = "";
	purchase_quantity = order_quantity = 0;
	Purchased = Sold = Price = Purchase_price = 0;
}
Product::Product(string ProductID, string ProductName, double Price)
{
	this->Price = Price;
	this->ProductID = ProductID;
	this->ProductName = ProductName;
	Order_History = "";
	Purchased = Sold = Purchase_price = 0;
	purchase_quantity = order_quantity = 0;
}
Product::~Product() {}


// Global Functions
void Welcome();
void Userinput();

void Save_Product(const vector<string>&);
void Purchase_Product(const vector<string>&);
void Order_Product(const vector<string>&);
void Get_Quantity_Of_Product(const vector<string>&);
void Get_Average_Price(const vector<string>&);
void Get_Product_Profit(const vector<string>&);
void Get_Fewest_Product(const vector<string>&);
void Get_Most_Popular_Product(const vector<string>&);
void Get_Orders_Report(const vector<string>&);
void Export_Orders_Report(const vector<string>&);


// Entry point
int main()
{
	Welcome();
	Userinput();

	// free allocated memory
	for (auto it = Catalog.begin(); it != Catalog.end(); ++it)
	{
		delete it->second;
	}
	if (Orders_Report != NULL)
	{
		delete Orders_Report;
	}
}

void Welcome()
{
	cout << "Welcome to Ecommerce application!\n"
		<< "You can use these commands : \n\n"
		<< "1) save_product -  to Add a new product to the catalog or modify an existing one\n"
		<< "2) purchase_product - to Purchase a product\n"
		<< "3) order_product - to Place an order for the product\n"
		<< "4) get_quantity_of_product - to Return the remaining quantity of a specific product\n"
		<< "5) get_average_price - to Calculate and display the average price of a specific product based on its purchase history\n"
		<< "6) get_product_profit - to Calculate and display the profit earned from a specific product\n"
		<< "7) get_fewest_product - to Return the name of the product with the lowest remaining quantity\n"
		<< "8) get_most_popular_product - to Return the name of the product with the highest number of orders\n"
		<< "9) get_orders_report - to Generate a report of all orders\n"
		<< "10) export_orders_report - to Export the report to a CSV file at the specified file path\n"
		<< "11) exit - to Close the console application\n" << endl;
}

void Userinput()
{
	map<string, Command> convert = {
		{"*", error}, {"save_product", save_product}, {"purchase_product", purchase_product},
		{"order_product", order_product}, {"get_quantity_of_product",get_quantity_of_product},
		{"get_average_price", get_average_price}, {"get_product_profit", get_product_profit},
		{"get_fewest_product", get_fewest_product}, {"get_most_popular_product", get_most_popular_product},
		{"exit", Exit}, {"get_orders_report", get_orders_report}, {"export_orders_report", export_orders_report}
	};

	string commandWithArgs, word;
	while (cin.eof() != 1)
	{
		//
		cout << "LevelUp:~$ ";
		getline(cin, commandWithArgs);
		//
		vector<string> CommandsAtFirst;
		word = "";
		for (size_t i = 0; i < commandWithArgs.length(); i++)
		{
			if (commandWithArgs[i] != ' ')
			{
				word += commandWithArgs[i];
			}
			else
			{
				CommandsAtFirst.push_back(word);
				word = "";
			}
		}
		CommandsAtFirst.push_back(word);
		//
		vector<string> CommandsAtLast;
		for (size_t i = 0; i < CommandsAtFirst.size(); i++)
		{
			if (CommandsAtFirst[i] != "")
			{
				CommandsAtLast.push_back(CommandsAtFirst[i]);
			}
		}
		//
		if (CommandsAtLast.size() < 1)
		{
			continue;
		}
		//
		Command Cm = convert[CommandsAtLast[0]];
		switch (Cm)
		{
		case save_product: Save_Product(CommandsAtLast); break;
		case purchase_product:Purchase_Product(CommandsAtLast); break;
		case order_product:Order_Product(CommandsAtLast); break;
		case get_quantity_of_product:Get_Quantity_Of_Product(CommandsAtLast); break;
		case get_average_price:Get_Average_Price(CommandsAtLast); break;
		case get_product_profit:Get_Product_Profit(CommandsAtLast); break;
		case get_fewest_product:Get_Fewest_Product(CommandsAtLast); break;
		case get_most_popular_product: Get_Most_Popular_Product(CommandsAtLast); break;
		case Exit: return;
		case get_orders_report: Get_Orders_Report(CommandsAtLast); break;
		case export_orders_report: Export_Orders_Report(CommandsAtLast); break;
		default: cout << CommandsAtLast[0] << ": command not found" << endl;
		}
	}
}

void Save_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 4)
	{
		cout << "Usage: save_product {product_id} {product_name} {price}\n";
		return;
	}

	double sellingprice;
	try
	{
		sellingprice = stod(argv[3]);
	}
	catch (const exception&)
	{
		cout << "Occurred cast exception, wrong arguments\n";
		cout << "Usage: save_product {product_id} {product_name} {price}\n";
		return;
	}
	
	if (sellingprice <= 0)
	{
		cout << "{price} must be positive\n";
		return;
	}

	if (Catalog.count(argv[1])) // if key exists
	{
		Catalog[argv[1]]->set_ProductName(argv[2]);
		Catalog[argv[1]]->set_Price(sellingprice);
	}	
	else
	{
		Catalog.emplace(argv[1], new Product(argv[1], argv[2], sellingprice));
	}
}
void Purchase_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 4)
	{
		cout << "Usage: purchase_product {product_id} {quantity} {price}\n";
		return;
	}

	double purchaseprice;
	int quantity;
	try
	{
		purchaseprice = stod(argv[3]);
		quantity = stoi(argv[2]);
	}
	catch (const exception&)
	{
		cout << "Occurred cast exception, wrong arguments\n";
		cout << "Usage: purchase_product {product_id} {quantity} {price}\n";
		return;
	}

	if (purchaseprice <= 0)
	{
		cout << "{price} must be positive\n";
		return;
	}
	else if (quantity <= 0)
	{
		cout << "{quantity} must be positive\n";
		return;
	}

	auto it = Catalog.find(argv[1]);
	if (it == Catalog.end())
	{
		cout << "Can't Purchase, product \'" << argv[1] << "\' is not in Catalog\n";
		return;
	}
	else
	{
		it->second->set_Purchased(it->second->get_Purchased() + quantity * purchaseprice);
		it->second->set_purchase_quantity(it->second->get_purchase_quantity() + quantity);
		it->second->set_Purchase_price(purchaseprice);
	}
}
void Order_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 3)
	{
		cout << "Usage: order_product {product_id} {quantity}\n";
		return;
	}

	int quantity;
	try
	{
		quantity = stoi(argv[2]);
	}
	catch (const exception&)
	{
		cout << "Occurred cast exception, wrong arguments\n";
		cout << "Usage: order_product {product_id} {quantity}\n";
		return;
	}

	if (quantity <= 0)
	{
		cout << "{quantity} must be positive\n";
		return;
	}

	auto it = Catalog.find(argv[1]);
	if (it == Catalog.end())
	{
		cout << "Can't Order, product \'" << argv[1] << "\' is not in the warehouse\n";
		return;
	}
	else if (it->second->get_remaining_quanitity() >= quantity)
	{
		it->second->set_Sold(it->second->get_Sold() + quantity * it->second->get_Price());
		it->second->set_order_quantity(it->second->get_order_quantity() + quantity);
		it->second->set_Order_History(it->second->get_Order_History() +
			"\nProductID: " + it->second->get_ProductID() +
			"\nProductName: " + it->second->get_ProductName() +
			"\nProductPrice: " + to_string(it->second->get_Price()) +
			"\nProduct remaining quantity:" + to_string(it->second->get_remaining_quanitity()) + '\n'
		);
	}
	else if(it->second->get_remaining_quanitity() < quantity && it->second->get_remaining_quanitity() > 0)
	{
		cout << "Can't Order, not enough quantity of product \'" << argv[1] << "\' in the warehouse\n";
		return;
	}
	else
	{
		cout << "Can't Order, we dont have product \'" << argv[1] << "\' in the warehouse right now\n";
		return;
	}
}
void Get_Quantity_Of_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 2)
	{
		cout << "Usage: get_quantity_of_product {product_id}\n";
		return;
	}

	auto it = Catalog.find(argv[1]);
	if (it == Catalog.end())
	{
		cout << "product \'" << argv[1] << "\' is not in the Catalog\n";
		return;
	}
	else
	{
		cout << it->second->get_remaining_quanitity() << '\n';
	}
}
void Get_Average_Price(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 2)
	{
		cout << "Usage: get_average_price {product_id}\n";
		return;
	}

	auto it = Catalog.find(argv[1]);
	if (it == Catalog.end())
	{
		cout << "product \'" << argv[1] << "\' is not in the Catalog\n";
		return;
	}
	else if(it->second->get_purchase_quantity() != 0)
	{
		cout << it->second->get_Purchased() / it->second->get_purchase_quantity() << '\n';
	}
	else
	{
		cout << "We have not bought product \'" << argv[1] << "\' yet\n";
		return;
	}
}
void Get_Product_Profit(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 2)
	{
		cout << "Usage: get_product_profit {product_id}\n";
		return;
	}
	auto it = Catalog.find(argv[1]);
	if (it == Catalog.end())
	{
		cout << "product \'" << argv[1] << "\' is not in the Catalog\n";
		return;
	}
	else
	{
		double Average_purchase_price = it->second->get_Purchased() / it->second->get_purchase_quantity();
		double average_order_price = it->second->get_Sold() / it->second->get_order_quantity();
		double profit_per_unit = average_order_price - Average_purchase_price;

		cout << profit_per_unit * it->second->get_order_quantity() << endl;
	}
}
void Get_Fewest_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 1)
	{
		cout << "Usage: get_fewest_product\n";
		return;
	}
	if (Catalog.size() < 1)
	{
		cout << "Catalog is empty\n";
		return;
	}

	auto it = Catalog.begin();
	auto fewestRem = it;
	for (++it; it != Catalog.end(); ++it)
	{
		if (it->second->get_remaining_quanitity() < fewestRem->second->get_remaining_quanitity())
		{
			fewestRem = it;
		}
	}
	cout << fewestRem->second->get_ProductName() << endl;
}
void Get_Most_Popular_Product(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 1)
	{
		cout << "Usage: get_most_popular_product\n";
		return;
	}
	if (Catalog.size() < 1)
	{
		cout << "Catalog is empty\n";
		return;
	}

	auto it = Catalog.begin();
	auto MostPopular = it;
	for (++it; it != Catalog.end(); ++it)
	{
		if (it->second->get_order_quantity() > MostPopular->second->get_order_quantity())
		{
			MostPopular = it;
		}
	}
	cout << MostPopular->second->get_ProductName() << endl;
}
void Get_Orders_Report(const vector<string>& argv)
{
	if (Orders_Report != NULL)
	{
		delete Orders_Report;
	}

	// Ensure proper usage
	if (argv.size() != 1)
	{
		cout << "Usage: get_orders_report\n";
		return;
	}

	Orders_Report = new vector<Product*>;
	for (auto it = Catalog.begin(); it != Catalog.end(); ++it)
	{
		Orders_Report->push_back(it->second);
	}
}
void Export_Orders_Report(const vector<string>& argv)
{
	// Ensure proper usage
	if (argv.size() != 2)
	{
		cout << "Usage: export_orders_report {path}\n";
		return;
	}
	if (Orders_Report == NULL)
	{
		cout << "Generate a report at first\n";
		return;
	}

	string path_str = argv[1];	
	try {
		std::filesystem::create_directories(path_str);
	}
	catch (const exception&) {
		std::cerr << "Failed to create path at " << path_str << endl;
		return;
	}

	// Generate the report
	try
	{
		// Open the CSV file for writing
		ofstream fout(path_str + "/report.CSV"); // Path/report.CSV

		// Write the header row
		fout << "ProductID,ProductName,Quantity,Price,COGS,Selling_Price" << endl;

		// Write the data rows
		for (int i = 0; i < Orders_Report->size(); ++i) {
			fout << Orders_Report->at(i)->get_ProductID() << ","
				<< Orders_Report->at(i)->get_ProductName() << ","
				<< Orders_Report->at(i)->get_remaining_quanitity() << ","
				<< Orders_Report->at(i)->get_Purchase_price() << ","
				<< Orders_Report->at(i)->get_COGS() << ","
				<< Orders_Report->at(i)->get_Price() << endl;
		}

		// Close the file
		fout.close();
	}
	catch (const exception&)
	{
		cout << "Could not create a CSV file at the specified file path: \'" << argv[1] << '\'' << endl;
		return;
	}
}
