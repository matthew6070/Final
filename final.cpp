// Car Catalog Project

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

// Base Car class (abstract)
class Car {
protected:
    string brand;
    string modelType;
    int modelYear;
    double cost;

public:
    // Constructor
    Car(string brand, string modelType, int modelYear, double cost) {
        this->brand = brand;
        this->modelType = modelType;
        this->modelYear = modelYear;
        this->cost = cost;
    }

    // Virtual destructor
    virtual ~Car() {}

    // Getters
    string getMake() const { return brand; }
    string getModel() const { return modelType; }
    int getModelYear() const { return modelYear; }
    double getCost() const { return cost; }

    // Pure virtual function (makes Car an abstract class)
    virtual string getType() const = 0;

    // Virtual function to show car details
    virtual void showInfo() const {
        cout << modelYear << " " << brand << " " << modelType << endl;
        cout << "Type: " << getType() << endl;
        cout << "cost: $" << cost << endl;
    }

    // Operator overloading for comparing car costs
    bool operator<(const Car& other) const {
        return cost < other.cost;
    }

    bool operator>(const Car& other) const {
        return cost > other.cost;
    }
};

// Sedan -
class Sedan : public Car {
private:
    int doorNum;

public:
    Sedan(string brand, string modelType, int modelYear, double cost, int doors)
        : Car(brand, modelType, modelYear, cost), doorNum(doors) {}

    string getType() const override {
        return "Sedan";
    }

    void showInfo() const override {
        Car::showInfo();
        cout << "Doors: " << doorNum << endl;
    }
};

// SUV- DERIVED CLASS
class SUV : public Car {
private:
    bool hasThirdRow;

public:
    SUV(string brand, string modelType, int modelYear, double cost, bool thirdRow)
        : Car(brand, modelType, modelYear, cost), hasThirdRow(thirdRow) {}

    string getType() const override {
        return "SUV";
    }

    void showInfo() const override {
        Car::showInfo();
        cout << "Third Row: " << (hasThirdRow ? "Yes" : "No") << endl;
    }
};

// Derived class Truck
class Truck : public Car {
private:
    double bedLength;
    double towingCapacity;

public:
    Truck(string brand, string modelType, int modelYear, double cost, double bedLen, double towCap)
        : Car(brand, modelType, modelYear, cost), bedLength(bedLen), towingCapacity(towCap) {}

    string getType() const override {
        return "Truck";
    }

    void showInfo() const override {
        Car::showInfo();
        cout << "Bed Length: " << bedLength << " ft" << endl;
        cout << "Towing Capacity: " << towingCapacity << " lbs" << endl;
    }
};

// Node class for the linked list
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
            delete current; // Delete the Node
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

    // show all cars in the linked list
    void showAllCars() const {
        if (head == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        Node* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << "\n--- Car #" << count++ << " ---" << endl;
            current->car->showInfo();
            current = current->next;
        }
    }

    // show cars of a specific type
    void showCarsByType(const string& type) const {
        if (head == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        Node* current = head;
        int count = 0;
        while (current != nullptr) {
            if (current->car->getType() == type) {
                cout << "\n--- " << type << " #" << ++count << " ---" << endl;
                current->car->showInfo();
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

// Class used to sort cars by costs
class BinarySearchTree {
private:
    TreeNode* root;

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

    // low to high cost Traversal
    void inOrderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            node->car->showInfo();
            cout << endl;
            inOrderTraversal(node->right);
        }
    }

    // high to low cost Traversal
    void reverseInOrderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            reverseInOrderTraversal(node->right);
            node->car->showInfo();
            cout << endl;
            reverseInOrderTraversal(node->left);
        }
    }


    void nodeDeletion(TreeNode* node) {
        if (node != nullptr) {
            nodeDeletion(node->left);
            nodeDeletion(node->right);
            delete node;
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        nodeDeletion(root);
    }

    // Use cost to add cars to BST
    void addCar(Car* car) {
        root = insert(root, car);
    }

    // show cars sorted by low to high costs
    void carCostLowToHigh() const {
        if (root == nullptr) {
            cout << "No cars in the catalog." << endl;
            return;
        }

        cout << "\n----- Cars Sorted by cost (Low to High) -----" << endl;
       inOrderTraversal(root);
    }

};


int main() {
    LinkedList carList;
    BinarySearchTree costTree;

    int choice;
    string brand, modelType, type;
    int modelYear, doors;
    double cost, bedLength, towingCapacity;
    bool hasThirdRow;
    Car* newCar = nullptr;

    cout << "===== Car Catalog System =====" << endl;

    try {
        do {
            cout << "\nMenu:" << endl;
            cout << "1. Add a Sedan" << endl;
            cout << "2. Add an SUV" << endl;
            cout << "3. Add a Truck" << endl;
            cout << "4. show all cars" << endl;
            cout << "5. show cars by type" << endl;
            cout << "6. show cars by cost (Low to High)" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            
            if (!(cin >> choice)) {
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (choice) {
                // adding sedan to LL
                case 1: 
                    cout << "Enter brand: ";
                    cin >> brand;
                    cout << "Enter modelType: ";
                    cin >> modelType;
                    cout << "Enter modelYear: ";
                    cin >> modelYear;
                    cout << "Enter cost: $";
                    cin >> cost;
                    cout << "Enter number of doors: ";
                    cin >> doors;
                    
                    newCar = new Sedan(brand, modelType, modelYear, cost, doors);
                    carList.addCar(newCar);
                    costTree.addCar(newCar);
                    cout << "Sedan added successfully!" << endl;
                    break;
                //adding a SUV to Linked List
                case 2: 
                    cout << "Enter brand: ";
                    cin >> brand;
                    cout << "Enter modelType: ";
                    cin >> modelType;
                    cout << "Enter modelYear: ";
                    cin >> modelYear;
                    cout << "Enter cost: $";
                    cin >> cost;
                    cout << "Has third row? (1 for Yes, 0 for No): ";
                    cin >> hasThirdRow;
                    
                    newCar = new SUV(brand, modelType, modelYear, cost, hasThirdRow);
                    carList.addCar(newCar);
                    costTree.addCar(newCar);
                    cout << "SUV added successfully!" << endl;
                    break;
                
                case 3: // Add a Truck car Type to Linked List
                    cout << "Enter brand: ";
                    cin >> brand;
                    cout << "Enter modelType: ";
                    cin >> modelType;
                    cout << "Enter modelYear: ";
                    cin >> modelYear;
                    cout << "Enter cost: $";
                    cin >> cost;
                    cout << "Enter bed length (in feet): ";
                    cin >> bedLength;
                    cout << "Enter towing capacity (in pounds): ";
                    cin >> towingCapacity;
                    
                    newCar = new Truck(brand, modelType, modelYear, cost, bedLength, towingCapacity);
                    carList.addCar(newCar);
                    costTree.addCar(newCar);
                    cout << "Truck added successfully!" << endl;
                    break;
                
                // list all cars
                case 4: 
                    carList.showAllCars();
                    break;
                // showcase all cars by type
                case 5: 
                    cout << "Enter car type (Sedan, SUV, or Truck): ";
                    cin >> type;
                    carList.showCarsByType(type);
                    break;
                // show cars by cost Low to High cost
                case 6: 
                    costTree.carCostLowToHigh();
                    break;
                // list cars by High to Low cost
                case 7: 
                    costTree.carCostHighToLow();
                    break;
                // Exit the program
                case 8: 
                    cout << "Exiting program. Goodbye!" << endl;
                    break;
                
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}