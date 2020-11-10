#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define DAVID "Hello David!\n"

class Customer {
  public:
    std::string name;
    std::string address;
    int value_cents;
    std::string description;

    Customer(std::string in_name, std::string in_address);

    void set_name(std::string);
    void get_name();
    std::string get_name_2();
    std::string get_csv();
    std::string get_csv_header();
    std::string get_pretty_print();
};

class Database {
  public:
    std::vector<Customer> customer_db;
    std::vector<std::string> names;
    std::vector<std::string> addresses;
    std::vector<int> values;
    std::vector<std::string> descriptions;
    std::string db_filename;

    Database();
    Database(std::string);

    void load();
    void save();
    void add_customer(Customer);
    void input_customer();
    void print_all_customers();
    // TO IMPLEMENT, return a vector of all customers
    // who spent above a certain amount
    std::vector<Customer> get_richos(int);
    std::string sanitize(std::string);
    std::string unsanitize(std::string);

};

Database::Database() {
  db_filename = "./data/customer_db.csv";
}

Database::Database(std::string in_db_filename) {
  db_filename = in_db_filename;
}

void Database::add_customer(Customer in_customer) {
  customer_db.push_back(in_customer);
  names.push_back(in_customer.name);
  addresses.push_back(in_customer.address);
}

std::string Database::sanitize(std::string in_string) {
  std::size_t found = in_string.find(",");
  while (found!=std::string::npos) { 
    in_string.replace(found, 1, "^");
    found = in_string.find(",");
  }
  return in_string;
}

std::string Database::unsanitize(std::string in_string) {
  std::size_t found = in_string.find("^");
  while (found!=std::string::npos) { 
    in_string.replace(found, 1, ",");
    found = in_string.find("^");
  }
  return in_string;
}

void Database::load() {
  std::ifstream filestream;
  filestream.open(db_filename, std::ios::in);
  if (filestream.is_open()) {
    std::string temp_name;
    std::string temp_addr;
    getline(filestream, temp_name); //Dump header line
    while( getline( filestream, temp_name, ',' ) ) { //Line up to ','
      getline( filestream, temp_addr); //Line up to '\n'
      temp_name = sanitize(temp_name);
      temp_addr = sanitize(temp_addr);
      add_customer(Customer(temp_name, temp_addr));
    }
  }
  filestream.close();
}

void Database::save() {
  std::string db_text = customer_db[0].get_csv_header();
  for (int i=0; i < customer_db.size(); i++) {
    db_text = db_text + customer_db[i].get_csv();
  }
  std::ofstream filestream;
  filestream.open(db_filename);
  filestream << db_text;
  filestream.close();
}

void Database::input_customer() {
  std::string temp_name;
  std::string temp_addr;
  std::cout << "Enter Customer Details:\nName: ";
  getline(std::cin, temp_name);
  temp_name = sanitize(temp_name);
  std::cout << "Address: ";
  getline(std::cin, temp_addr);
  temp_addr = sanitize(temp_addr);
  add_customer(Customer(temp_name, temp_addr));
  std::cout << '\n';
}

void Database::print_all_customers() {
  for (int i=0; i < customer_db.size(); i++) {
    std::cout << "Index: " << i << "\n";
    std::cout << unsanitize(customer_db[i].get_pretty_print());
    std::cout << std::endl;
  }
}

Customer::Customer(std::string in_name, std::string in_address) {
  set_name(in_name);
  address = in_address;
}


void Customer::set_name(std::string new_name) {
  name = new_name;
}
void Customer::get_name() {
  std::cout << name;
}
std::string Customer::get_name_2() {
  return name;
}
std::string Customer::get_csv() {
  std::string csv_line = "";
  csv_line += name + "," + address + "\n";
  return csv_line;
}

std::string Customer::get_csv_header() {
  return "Name,Address\n";
}

std::string Customer::get_pretty_print() {
  std::string temp_string;
  temp_string +=  "Name: " + name + "\n";
  temp_string += "Address: " + address + "\n";
  return temp_string;
}

int main() {
  Database cust_db = Database();
  cust_db.load();
  //cust_db.input_customer(); 
  cust_db.print_all_customers();
  cust_db.save();
}
