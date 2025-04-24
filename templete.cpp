// Car Catalog Project
// This program demonstrates linked lists, binary search trees, and OOP concepts
// including inheritance, polymorphism, and virtual functions

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

// Base Car class (abstract)
class Car {
protected:
    string make;
    string model;
    int year;
    double price;

public:
    // Constructor
    Car(string make, string model, int year, double price) {
        this->make = make;
        this->model = model;
        this->year = year;
        this->price = price;
    }

    // Virtual destructor
    virtual ~Car() {}

    // Getters
    string getMake() const { return make; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    double getPrice() const { return price; }

    // Pure virtual function (makes Car an abstract class)
    virtual string getType() const = 0;

    // Virtual function to display car details
    virtual void displayInfo() const {
        cout << year << " " << make << " " << model << endl;
        cout << "Type: " << getType() << endl;
        cout << "Price: $" << price << endl;
    }

    // Operator overloading for comparing car prices
    bool operator<(const Car& other) const {
        return price < other.price;
    }

    bool operator>(const Car& other) const {
        return price > other.price;
    }
};

// Derived class - Sedan
class Sedan : public Car {
private:
    int numDoors;

public:
    Sedan(string make, string model, int year, double price, int doors)
        : Car(make, model, year, price), numDoors(doors) {}

    string getType() const override {
        return "Sedan";
    }

    void displayInfo() const override {
        Car::displayInfo();
        cout << "Doors: " << numDoors << endl;
    }
};

// Derived class - SUV
class SUV : public Car {
private:
    bool hasThirdRow;

public:
    SUV(string make, string model, int year, double price, bool thirdRow)
        : Car(make, model, year, price), hasThirdRow(thirdRow) {}

    string getType() const override {
        return "SUV";
    }

    void displayInfo() const override {
        Car::displayInfo();
        cout << "Third Row: " << (hasThirdRow ? "Yes" : "No") << endl;
    }
};

// Derived class - Truck
class Truck : public Car {
private:
    double bedLength;
    double towingCapacity;

public:
    Truck(string make, string model, int year, double price, double bedLen, double towCap)
        : Car(make, model, year, price), bedLength(bedLen), towingCapacity(towCap) {}

    string getType() const override {
        return "Truck";
    }

    void displayInfo() const override {
        Car::displayInfo();
        cout << "Bed Length: " << bedLength << " ft" << endl;
        cout << "Towing Capacity: " << towingCapacity << " lbs" << endl;
    }
};

// Node class for linked list
class Node {
public:
    Car* car;
    Node* next;

    Node(Car* car) {
        this->car = car;
        next = nullptr;
    }
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current->car; // Delete the Car object
            delete current;      // Delete the Node
            current = next;
        }
    }

    // Add a car to the linked list
    void addCar(Car* car) {
        Node* newNode = new Node(car);

        // If list is empty or the new car should be at the beginning
        if (head == nullptr || car->getType() < head->car->getType()) {
            newNode->next = head;
            head = newNode;
            return;
        }

        // Find the right position to insert
        Node* current = head;
        while (current->next != nullptr && current->next->car->getType() <= car->getType()) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    // Display all cars in the linked list
    void displayAllCars() const {
        if (head == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        Node* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << "\n--- Car #" << count++ << " ---" << endl;
            current->car->displayInfo();
            current = current->next;
        }
    }

    // Display cars of a specific type
    void displayCarsByType(const string& type) const {
        if (head == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->car->getType() == type) {
                cout << "\n--- " << type << " #" << ++count << " ---" << endl;
                current->car->displayInfo();
            }
            current = current->next;
        }

        if (count == 0) {
            cout << "No " << type << "s found in the catalog." << endl;
        }
    }
};

// Node class for Binary Search Tree
class TreeNode {
public:
    Car* car;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Car* car) {
        this->car = car;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree class for price-based sorting
class BinarySearchTree {
private:
    TreeNode* root;

    // Helper method for adding a car
    TreeNode* insert(TreeNode* node, Car* car) {
        if (node == nullptr) {
            return new TreeNode(car);
        }

        if (*car < *(node->car)) {
            node->left = insert(node->left, car);
        } else {
            node->right = insert(node->right, car);
        }

        return node;
    }

    // Helper method for in-order traversal (low to high)
    void inOrderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            node->car->displayInfo();
            cout << endl;
            inOrderTraversal(node->right);
        }
    }

    // Helper method for reverse in-order traversal (high to low)
    void reverseInOrderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            reverseInOrderTraversal(node->right);
            node->car->displayInfo();
            cout << endl;
            reverseInOrderTraversal(node->left);
        }
    }

    // Helper method for cleanup
    void cleanup(TreeNode* node) {
        if (node != nullptr) {
            cleanup(node->left);
            cleanup(node->right);
            // Note: Don't delete car objects here, as they are owned by the LinkedList
            delete node;
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        cleanup(root);
    }

    // Add a car to the BST based on price
    void addCar(Car* car) {
        root = insert(root, car);
    }

    // Display cars sorted by price (low to high)
    void displayLowToHigh() const {
        if (root == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        cout << "\n----- Cars Sorted by Price (Low to High) -----" << endl;
        inOrderTraversal(root);
    }

    // Display cars sorted by price (high to low)
    void displayHighToLow() const {
        if (root == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        cout << "\n----- Cars Sorted by Price (High to Low) -----" << endl;
        reverseInOrderTraversal(root);
    }
};

// Main function
int main() {
    LinkedList carList;
    BinarySearchTree priceTree;

    int choice;
    string make, model, type;
    int year, doors;
    double price, bedLength, towingCapacity;
    bool hasThirdRow;
    Car* newCar = nullptr;

    cout << "===== Car Catalog System =====" << endl;

    try {
        do {
            cout << "\nMenu:" << endl;
            cout << "1. Add a Sedan" << endl;
            cout << "2. Add an SUV" << endl;
            cout << "3. Add a Truck" << endl;
            cout << "4. Display all cars" << endl;
            cout << "5. Display cars by type" << endl;
            cout << "6. Display cars by price (Low to High)" << endl;
            cout << "7. Display cars by price (High to Low)" << endl;
            cout << "8. Exit" << endl;
            cout << "Enter your choice: ";
            
            if (!(cin >> choice)) {
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (choice) {
                case 1: // Add a Sedan
                    cout << "Enter make: ";
                    cin >> make;
                    cout << "Enter model: ";
                    cin >> model;
                    cout << "Enter year: ";
                    cin >> year;
                    cout << "Enter price: $";
                    cin >> price;
                    cout << "Enter number of doors: ";
                    cin >> doors;
                    
                    newCar = new Sedan(make, model, year, price, doors);
                    carList.addCar(newCar);
                    priceTree.addCar(newCar);
                    cout << "Sedan added successfully!" << endl;
                    break;
                
                case 2: // Add an SUV
                    cout << "Enter make: ";
                    cin >> make;
                    cout << "Enter model: ";
                    cin >> model;
                    cout << "Enter year: ";
                    cin >> year;
                    cout << "Enter price: $";
                    cin >> price;
                    cout << "Has third row? (1 for Yes, 0 for No): ";
                    cin >> hasThirdRow;
                    
                    newCar = new SUV(make, model, year, price, hasThirdRow);
                    carList.addCar(newCar);
                    priceTree.addCar(newCar);
                    cout << "SUV added successfully!" << endl;
                    break;
                
                case 3: // Add a Truck
                    cout << "Enter make: ";
                    cin >> make;
                    cout << "Enter model: ";
                    cin >> model;
                    cout << "Enter year: ";
                    cin >> year;
                    cout << "Enter price: $";
                    cin >> price;
                    cout << "Enter bed length (in feet): ";
                    cin >> bedLength;
                    cout << "Enter towing capacity (in pounds): ";
                    cin >> towingCapacity;
                    
                    newCar = new Truck(make, model, year, price, bedLength, towingCapacity);
                    carList.addCar(newCar);
                    priceTree.addCar(newCar);
                    cout << "Truck added successfully!" << endl;
                    break;
                
                case 4: // Display all cars
                    carList.displayAllCars();
                    break;
                
                case 5: // Display cars by type
                    cout << "Enter car type (Sedan, SUV, or Truck): ";
                    cin >> type;
                    carList.displayCarsByType(type);
                    break;
                
                case 6: // Display cars by price (Low to High)
                    priceTree.displayLowToHigh();
                    break;
                
                case 7: // Display cars by price (High to Low)
                    priceTree.displayHighToLow();
                    break;
                
                case 8: // Exit
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 8);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}