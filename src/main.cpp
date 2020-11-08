#include <iostream>
#include <string>
#include <fstream>
#define DAVID "Hello David!\n"

class Customer {
public:
    std::string name;
    std::string address;
    int value_cents;
    std::string description;

    Customer(std::string in_name, std::string in_address) {
      set_name(in_name);
      address = in_address;
    }

    void set_name(std::string new_name) {
        name = new_name;
    }
    void get_name() {
        std::cout << name;
    }
    std::string get_name_2() {
        return name;
    }
    std::string get_csv() {
      std::string csv_line = "";
      csv_line += name + "," + address + ",";
      return csv_line;
    }
};

int main() {
    Customer c1 = Customer("Jake", "Worcester, MA");
    std::cout << c1.get_csv();

}
