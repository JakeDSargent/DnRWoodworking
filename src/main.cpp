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
    Customer c1 = Customer();
    c1.set_name("Jake");
    c1.address = "Worcester, MA";
    std::cout << c1.get_csv();

}
