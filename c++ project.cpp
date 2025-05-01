#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Car structure
struct Car {
    string name;
    string model;
    double daily_rate;
};

// Customer structure
struct Customer {
    string name;
    int renting_days;
    Car rented_car;
    bool is_returned; // New attribute to track if the car is returned
};

// Function to calculate total rental cost
double calculateRentalCost(Customer customer) {
    return customer.renting_days * customer.rented_car.daily_rate;
}

// Function to display car details
void displayCar(Car car) {
    cout << "Car Name: " << car.name << endl;
    cout << "Car Model: " << car.model << endl;
    cout << "Daily Rental Rate: $" << car.daily_rate << endl;
}

// Function to display customer details
void displayCustomer(Customer customer) {
    cout << "Customer Name: " << customer.name << endl;
    cout << "Renting Days: " << customer.renting_days << endl;
    displayCar(customer.rented_car);
    cout << "Total Rental Cost: $" << calculateRentalCost(customer) << endl;
    cout << "Car Returned: " << (customer.is_returned ? "Yes" : "No") << endl;
}

// Function to add a new car
Car addCar() {
    Car car;
    cout << "Enter car name: ";
    getline(cin, car.name);
    cout << "Enter car model: ";
    getline(cin, car.model);
    cout << "Enter daily rental rate: ";
    cin >> car.daily_rate;
    cin.ignore(); // To ignore the newline character
    return car;
}

// Function to add a new customer
Customer addCustomer(vector<Car>& cars) {
    Customer customer;
    cout << "Enter customer name: ";
    getline(cin, customer.name);
    cout << "Enter number of renting days: ";
    cin >> customer.renting_days;
    cin.ignore(); // To ignore the newline character
    customer.is_returned = false; // Initialize as not returned

    // Display available cars
    cout << "Available cars:" << endl;
    for (size_t i = 0; i < cars.size(); i++) {
        cout << i + 1 << ". " << cars[i].name << " (" << cars[i].model << ")" << endl;
    }

    // Select car
    int car_choice;
    cout << "Select a car by number: ";
    cin >> car_choice;
    cin.ignore(); // To ignore the newline character
    customer.rented_car = cars[car_choice - 1];

    return customer;
}

// Function to return a car
void returnCar(vector<Customer>& customers) {
    string customer_name;
    cout << "Enter customer name to return car: ";
    getline(cin, customer_name);

    for (auto& customer : customers) {
        if (customer.name == customer_name && !customer.is_returned) {
            customer.is_returned = true;
            cout << "Car returned successfully." << endl;
            return;
        }
    }

    cout << "Customer not found or car already returned." << endl;
}

int main() {
    vector<Car> cars = {
        {"Toyota", "Camry", 50},
        {"Honda", "Civic", 45},
        {"Ford", "Mustang", 75},
        {"Chevrolet", "Malibu", 55},
        {"BMW", "3 Series", 100}
    };
    vector<Customer> customers;
    int choice;

    while (true) {
        cout << "\nCar Rental Management System\n";
        cout << "1. Add a new car\n";
        cout << "2. Add a new customer\n";
        cout << "3. Display all cars\n";
        cout << "4. Display all customers\n";
        cout << "5. Return a car\n"; // New option to return a car
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character

        if (choice == 1) {
            cars.push_back(addCar());
        } else if (choice == 2) {
            if (cars.empty()) {
                cout << "No cars available. Please add cars first." << endl;
            } else {
                customers.push_back(addCustomer(cars));
            }
        } else if (choice == 3) {
            for (const auto& car : cars) {
                displayCar(car);
                cout << endl;
            }
        } else if (choice == 4) {
            for (const auto& customer : customers) {
                displayCustomer(customer);
                cout << endl;
            }
        } else if (choice == 5) {
            if (customers.empty()) {
                cout << "No customers available." << endl;
            } else {
                returnCar(customers);
            }
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
