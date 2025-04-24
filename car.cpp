/*
 * Car Catalog System
 * 
 * This program implements a car catalog system that allows users to:
 * - Add different types of cars (Sedan, SUV, Truck)
 * - Display all cars or cars by category
 * - Sort and display cars by price (low to high or high to low)
 * - Find cars by make and model
 * - Apply discounts to cars
 * - Remove cars from the catalog
 * 
 * The implementation demonstrates:
 * - Object-oriented design with multi-level inheritance
 * - Operator and function overloading
 * - Virtual and pure virtual functions
 * - Abstract classes
 * - Self-implemented linked list and binary search tree
 * - Dynamic memory allocation
 * - Exception handling
 * - Console input/output
 */

 #include <iostream>
 #include <string>
 #include <stdexcept>
 #include <limits>
 #include <iomanip>
 using namespace std;
 
 // Forward declarations
 class Car;
 
 // ==================== CAR CLASS HIERARCHY ====================
 
 // Base class - Abstract class
 class Car {
 protected:
     string make;
     string model;
     int year;
     double price;
     
 public:
     // Constructors
     Car() : make(""), model(""), year(0), price(0.0) {}
     
     Car(string make, string model, int year, double price) 
         : make(make), model(model), year(year), price(price) {
         if (price < 0) {
             throw invalid_argument("Price cannot be negative");
         }
         if (year < 1886 || year > 2025) { // First car was invented in 1886
             throw invalid_argument("Invalid year");
         }
     }
     
     // Virtual destructor
     virtual ~Car() {
         // cout << "Car destructor called for " << make << " " << model << endl;
     }
     
     // Getters
     string getMake() const { return make; }
     string getModel() const { return model; }
     int getYear() const { return year; }
     double getPrice() const { return price; }
     
     // Setters
     void setPrice(double newPrice) {
         if (newPrice < 0) {
             throw invalid_argument("Price cannot be negative");
         }
         price = newPrice;
     }
     
     // Virtual functions for polymorphism
     virtual void displayDetails() const {
         cout << year << " " << make << " " << model << endl;
         cout << "Price: $" << fixed << setprecision(2) << price << endl;
     }
     
     // Pure virtual functions (makes Car an abstract class)
     virtual string getCategory() const = 0;
     virtual double calculateInsurance() const = 0;
     
     // Operator overloading
     bool operator>(const Car& other) const {
         return price > other.price;
     }
     
     bool operator<(const Car& other) const {
         return price < other.price;
     }
     
     // Other methods
     virtual void applyDiscount(double percentage) {
         if (percentage < 0 || percentage > 100) {
             throw invalid_argument("Discount percentage must be between 0 and 100");
         }
         price = price * (1 - percentage / 100);
     }
 };
 
 // First level of inheritance
 class PassengerCar : public Car {
 protected:
     int seatingCapacity;
     bool hasNavigation;
     
 public:
     PassengerCar() : Car(), seatingCapacity(0), hasNavigation(false) {}
     
     PassengerCar(string make, string model, int year, double price 
                 int seatingCapacity, bool hasNavigation)
         : Car(make, model, year, price), 
           seatingCapacity(seatingCapacity), hasNavigation(hasNavigation) {
         if (seatingCapacity <= 0) {
             throw invalid_argument("Seating capacity must be positive");
         }
     }
     
     virtual ~PassengerCar() {
         // cout << "PassengerCar destructor called" << endl;
     }
     
     // Getters
     int getSeatingCapacity() const { return seatingCapacity; }
     bool getHasNavigation() const { return hasNavigation; }
     
     // Function overriding
     virtual void displayDetails() const override {
         Car::displayDetails();
         cout << "Seating Capacity: " << seatingCapacity << endl;
         cout << "Navigation System: " << (hasNavigation ? "Yes" : "No") << endl;
     }
     
     // Implementation of pure virtual function
     virtual double calculateInsurance() const override {
         // Base calculation plus extra for passenger cars
         return price * 0.05 + (seatingCapacity * 100);
     }
 };
 
 // Second level of inheritance - Sedan
 class Sedan : public PassengerCar {
 private:
     bool hasSunroof;
     string trunkSize;  // Small, Medium, Large
     
 public:
     Sedan() : PassengerCar(), hasSunroof(false), trunkSize("") {}
     
     Sedan(string make, string model, int year, double price,
          int seatingCapacity, bool hasNavigation, bool hasSunroof, string trunkSize)
         : PassengerCar(make, model, year, price, seatingCapacity, hasNavigation),
           hasSunroof(hasSunroof), trunkSize(trunkSize) {}
     
     ~Sedan() {
         // cout << "Sedan destructor called" << endl;
     }
     
     // Getters
     bool getHasSunroof() const { return hasSunroof; }
     string getTrunkSize() const { return trunkSize; }
     
     // Function overriding
     void displayDetails() const override {
         PassengerCar::displayDetails();
         cout << "Sunroof: " << (hasSunroof ? "Yes" : "No") << endl;
         cout << "Trunk Size: " << trunkSize << endl;
         cout << "Category: " << getCategory() << endl;
         cout << "Estimated Insurance: $" << fixed << setprecision(2) << calculateInsurance() << "/year" << endl;
     }
     
     string getCategory() const override {
         return "Sedan";
     }
     
     double calculateInsurance() const override {
         // PassengerCar calculation plus sedan-specific factors
         double baseInsurance = PassengerCar::calculateInsurance();
         return baseInsurance + (hasSunroof ? 150 : 0);
     }
 };
 
 // Second level of inheritance - SUV
 class SUV : public PassengerCar {
 private:
     bool isAWD;  // All-Wheel Drive
     int cargoSpace;  // in cubic feet
     
 public:
     SUV() : PassengerCar(), isAWD(false), cargoSpace(0) {}
     
     SUV(string make, string model, int year, double price,
        int seatingCapacity, bool hasNavigation, bool isAWD, int cargoSpace)
         : PassengerCar(make, model, year, price, seatingCapacity, hasNavigation),
           isAWD(isAWD), cargoSpace(cargoSpace) {
         if (cargoSpace < 0) {
             throw invalid_argument("Cargo space cannot be negative");
         }
     }
     
     ~SUV() {
         // cout << "SUV destructor called" << endl;
     }
     
     // Getters
     bool getIsAWD() const { return isAWD; }
     int getCargoSpace() const { return cargoSpace; }
     
     // Function overriding
     void displayDetails() const override {
         PassengerCar::displayDetails();
         cout << "All-Wheel Drive: " << (isAWD ? "Yes" : "No") << endl;
         cout << "Cargo Space: " << cargoSpace << " cubic feet" << endl;
         cout << "Category: " << getCategory() << endl;
         cout << "Estimated Insurance: $" << fixed << setprecision(2) << calculateInsurance() << "/year" << endl;
     }
     
     string getCategory() const override {
         return "SUV";
     }
     
     double calculateInsurance() const override {
         // PassengerCar calculation plus SUV-specific factors
         double baseInsurance = PassengerCar::calculateInsurance();
         return baseInsurance + (isAWD ? 250 : 0) + (cargoSpace * 0.5);
     }
 };
 
 // First level of inheritance
 class CommercialVehicle : public Car {
 protected:
     double payloadCapacity;  // in tons
     string transmissionType;  // Automatic, Manual, etc.
     
 public:
     CommercialVehicle() : Car(), payloadCapacity(0), transmissionType("") {}
     
     CommercialVehicle(string make, string model, int year, double price,
                     double payloadCapacity, string transmissionType)
         : Car(make, model, year, price), 
           payloadCapacity(payloadCapacity), transmissionType(transmissionType) {
         if (payloadCapacity <= 0) {
             throw invalid_argument("Payload capacity must be positive");
         }
     }
     
     virtual ~CommercialVehicle() {
         // cout << "CommercialVehicle destructor called" << endl;
     }
     
     // Getters
     double getPayloadCapacity() const { return payloadCapacity; }
     string getTransmissionType() const { return transmissionType; }
     
     // Function overriding
     virtual void displayDetails() const override {
         Car::displayDetails();
         cout << "Payload Capacity: " << payloadCapacity << " tons" << endl;
         cout << "Transmission Type: " << transmissionType << endl;
     }
     
     // Implementation of pure virtual function
     virtual double calculateInsurance() const override {
         // Base calculation plus extra for commercial vehicles
         return price * 0.08 + (payloadCapacity * 200);
     }
 };
 
 // Second level of inheritance - Truck
 class Truck : public CommercialVehicle {
 private:
     int axleCount;
     bool hasSleeper;  // Sleeper cabin
     
 public:
     Truck() : CommercialVehicle(), axleCount(0), hasSleeper(false) {}
     
     Truck(string make, string model, int year, double price,
          double payloadCapacity, string transmissionType, int axleCount, bool hasSleeper)
         : CommercialVehicle(make, model, year, price, payloadCapacity, transmissionType),
           axleCount(axleCount), hasSleeper(hasSleeper) {
         if (axleCount <= 0) {
             throw invalid_argument("Axle count must be positive");
         }
     }
     
     ~Truck() {
         // cout << "Truck destructor called" << endl;
     }
     
     // Getters
     int getAxleCount() const { return axleCount; }
     bool getHasSleeper() const { return hasSleeper; }
     
     // Function overriding
     void displayDetails() const override {
         CommercialVehicle::displayDetails();
         cout << "Axle Count: " << axleCount << endl;
         cout << "Sleeper Cabin: " << (hasSleeper ? "Yes" : "No") << endl;
         cout << "Category: " << getCategory() << endl;
         cout << "Estimated Insurance: $" << fixed << setprecision(2) << calculateInsurance() << "/year" << endl;
     }
     
     string getCategory() const override {
         return "Truck";
     }
     
     double calculateInsurance() const override {
         // CommercialVehicle calculation plus truck-specific factors
         double baseInsurance = CommercialVehicle::calculateInsurance();
         return baseInsurance + (axleCount * 150) + (hasSleeper ? 300 : 0);
     }
 };
 
 // ==================== LINKED LIST IMPLEMENTATION ====================
 
 // Node structure for the linked list
 template <typename T>
 class Node {
 public:
     T data;
     Node* next;
     
     Node(T data) : data(data), next(nullptr) {}
 };
 
 // Linked list class
 template <typename T>
 class LinkedList {
 private:
     int size;
     
 public:
     Node<T>* head;
     // Constructor
     LinkedList() : head(nullptr), size(0) {}
     
     // Destructor
     ~LinkedList() {
         clear();
     }
     
     // Clear the list
     void clear() {
         Node<T>* current = head;
         Node<T>* next = nullptr;
         
         while (current != nullptr) {
             next = current->next;
             delete current;
             current = next;
         }
         
         head = nullptr;
         size = 0;
     }
     
     // Add to the front of the list
     void addToFront(T data) {
         Node<T>* newNode = new Node<T>(data);
         newNode->next = head;
         head = newNode;
         size++;
     }
     
     // Add to the end of the list
     void addToEnd(T data) {
         Node<T>* newNode = new Node<T>(data);
         
         if (head == nullptr) {
             head = newNode;
         } else {
             Node<T>* current = head;
             while (current->next != nullptr) {
                 current = current->next;
             }
             current->next = newNode;
         }
         
         size++;
     }
     
     // Add car by category (organizes entries)
     void addByCategory(T data) {
         if (head == nullptr) {
             addToFront(data);
             return;
         }
         
         // Compare categories
         string category = data->getCategory();
         
         // If the new car's category comes before the head's category
         if (category < head->data->getCategory()) {
             addToFront(data);
             return;
         }
         
         // Find the appropriate position to insert
         Node<T>* current = head;
         Node<T>* prev = nullptr;
         
         while (current != nullptr && current->data->getCategory() <= category) {
             prev = current;
             current = current->next;
         }
         
         // Insert the new node
         Node<T>* newNode = new Node<T>(data);
         newNode->next = current;
         prev->next = newNode;
         
         size++;
     }
     
     // Remove a car
     bool remove(T data) {
         if (head == nullptr) {
             return false;
         }
         
         // If the head is the one to be removed
         if (head->data == data) {
             Node<T>* temp = head;
             head = head->next;
             delete temp;
             size--;
             return true;
         }
         
         // Search for the node to remove
         Node<T>* current = head;
         Node<T>* prev = nullptr;
         
         while (current != nullptr && current->data != data) {
             prev = current;
             current = current->next;
         }
         
         // If the node was found
         if (current != nullptr) {
             prev->next = current->next;
             delete current;
             size--;
             return true;
         }
         
         return false;
     }
     
     // Find a car by make and model
     T find(const string& make, const string& model) const {
         Node<T>* current = head;
         
         while (current != nullptr) {
             if (current->data->getMake() == make && current->data->getModel() == model) {
                 return current->data;
             }
             current = current->next;
         }
         
         return nullptr;  // Not found
     }
     
     // Check if the list is empty
     bool isEmpty() const {
         return head == nullptr;
     }
     
     // Get the size of the list
     int getSize() const {
         return size;
     }
     
     // Display all cars
     void displayAll() const {
         if (isEmpty()) {
             cout << "The catalog is empty." << endl;
             return;
         }
         
         Node<T>* current = head;
         int count = 1;
         
         while (current != nullptr) {
             cout << "\n--- Car #" << count << " ---" << endl;
             current->data->displayDetails();
             cout << "--------------------" << endl;
             current = current->next;
             count++;
         }
     }
     
     // Display cars by category
     void displayByCategory(const string& category) const {
         if (isEmpty()) {
             cout << "The catalog is empty." << endl;
             return;
         }
         
         Node<T>* current = head;
         int count = 0;
         
         while (current != nullptr) {
             if (current->data->getCategory() == category) {
                 cout << "\n--- " << category << " #" << ++count << " ---" << endl;
                 current->data->displayDetails();
                 cout << "--------------------" << endl;
             }
             current = current->next;
         }
         
         if (count == 0) {
             cout << "No " << category << "s found in the catalog." << endl;
         }
     }
 };
 
 // ==================== BINARY SEARCH TREE IMPLEMENTATION ====================
 
 // Node structure for the binary search tree
 template <typename T>
 class TreeNode {
 public:
     T data;
     TreeNode* left;
     TreeNode* right;
     
     TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
 };
 
 // Binary search tree class
 template <typename T>
 class BinarySearchTree {
 private:
     TreeNode<T>* root;
     
     // Helper function to insert a node
     void insertNode(TreeNode<T>*& node, T data) {
         if (node == nullptr) {
             node = new TreeNode<T>(data);
         } else if (*data < *(node->data)) {
             insertNode(node->left, data);
         } else {
             insertNode(node->right, data);
         }
     }
     
     // Helper function for in-order traversal (low to high)
     void inOrderTraversal(TreeNode<T>* node, void (*visit)(T)) const {
         if (node != nullptr) {
             inOrderTraversal(node->left, visit);
             visit(node->data);
             inOrderTraversal(node->right, visit);
         }
     }
     
     // Helper function for reverse in-order traversal (high to low)
     void reverseOrderTraversal(TreeNode<T>* node, void (*visit)(T)) const {
         if (node != nullptr) {
             reverseOrderTraversal(node->right, visit);
             visit(node->data);
             reverseOrderTraversal(node->left, visit);
         }
     }
     
     // Helper function to delete the tree
     void deleteTree(TreeNode<T>*& node) {
         if (node != nullptr) {
             deleteTree(node->left);
             deleteTree(node->right);
             delete node;
             node = nullptr;
         }
     }
     
 public:
     // Constructor
     BinarySearchTree() : root(nullptr) {}
     
     // Destructor
     ~BinarySearchTree() {
         deleteTree(root);
     }
     
     // Insert a node
     void insert(T data) {
         insertNode(root, data);
     }
     
     // Check if the tree is empty
     bool isEmpty() const {
         return root == nullptr;
     }
     
     // Display cars from low to high price
     void displayLowToHigh(void (*visit)(T)) const {
         if (isEmpty()) {
             cout << "The catalog is empty." << endl;
             return;
         }
         
         cout << "\nCars sorted by price (Low to High):" << endl;
         cout << "=================================" << endl;
         inOrderTraversal(root, visit);
     }
     
     // Display cars from high to low price
     void displayHighToLow(void (*visit)(T)) const {
         if (isEmpty()) {
             cout << "The catalog is empty." << endl;
             return;
         }
         
         cout << "\nCars sorted by price (High to Low):" << endl;
         cout << "=================================" << endl;
         reverseOrderTraversal(root, visit);
     }
 };
 
 // ==================== MAIN PROGRAM ====================
 
 void displayCar(Car* car) {
     car->displayDetails();
     cout << "--------------------" << endl;
 }
 
 int main() {
     // Create containers
     LinkedList<Car*> carCatalog;
     BinarySearchTree<Car*> priceSortedCars;
     
     bool running = true;
     int choice;
     
     // Add some sample cars to the catalog
     try {
         // Add a Sedan
         Sedan* sedan1 = new Sedan("Toyota", "Camry", 2022, 25000, "Gasoline", 5, true, false, "Medium");
         carCatalog.addByCategory(sedan1);
         priceSortedCars.insert(sedan1);
         
         // Add an SUV
         SUV* suv1 = new SUV("Honda", "CR-V", 2023, 32000, "Hybrid", 7, true, true, 75);
         carCatalog.addByCategory(suv1);
         priceSortedCars.insert(suv1);
         
         // Add a Truck
         Truck* truck1 = new Truck("Ford", "F-150", 2021, 40000, "Diesel", 1.5, "Automatic", 2, false);
         carCatalog.addByCategory(truck1);
         priceSortedCars.insert(truck1);
     } catch (const exception& e) {
         cout << "Error adding sample cars: " << e.what() << endl;
     }
     
     // Main program loop
     try {
         while (running) {
             cout << "\n===== Car Catalog System =====\n";
             cout << "1. Add a new car\n";
             cout << "2. Display all cars\n";
             cout << "3. Display cars by category\n";
             cout << "4. Display cars sorted by price (low to high)\n";
             cout << "5. Display cars sorted by price (high to low)\n";
             cout << "6. Find a car by make and model\n";
             cout << "7. Apply discount to a car\n";
             cout << "8. Remove a car from catalog\n";
             cout << "9. Exit\n";
             cout << "Enter your choice: ";
             
             if (!(cin >> choice)) {
                 cin.clear();
                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                 throw runtime_error("Invalid input. Please enter a number.");
             }
             
             switch (choice) {
                 case 1: {
                     // Add a new car
                     int carType;
                     string make, model;
                     int year;
                     double price;
                     
                     cout << "\nSelect car type:\n";
                     cout << "1. Sedan\n";
                     cout << "2. SUV\n";
                     cout << "3. Truck\n";
                     cout << "Enter choice: ";
                     
                     if (!(cin >> carType) || carType < 1 || carType > 3) {
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         throw runtime_error("Invalid car type selection.");
                     }
                     
                     // Common details for all car types
                     cout << "Enter make: ";
                     cin.ignore();
                     getline(cin, make);
                     
                     cout << "Enter model: ";
                     getline(cin, model);
                     
                     cout << "Enter year: ";
                     if (!(cin >> year)) {
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         throw runtime_error("Invalid year input.");
                     }
                     
                     cout << "Enter price: $";
                     if (!(cin >> price)) {
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         throw runtime_error("Invalid price input.");
                     }
                     
                     
                     Car* newCar = nullptr;
                     
                     switch (carType) {
                         case 1: {
                             // Sedan-specific details
                             int seatingCapacity;
                             bool hasNavigation, hasSunroof;
                             string trunkSize;
                             char navChoice, sunroofChoice;
                             
                             cout << "Enter seating capacity: ";
                             if (!(cin >> seatingCapacity)) {
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                 throw runtime_error("Invalid seating capacity input.");
                             }
                             
                             cout << "Has navigation system? (y/n): ";
                             cin >> navChoice;
                             hasNavigation = (navChoice == 'y' || navChoice == 'Y');
                             
                             cout << "Has sunroof? (y/n): ";
                             cin >> sunroofChoice;
                             hasSunroof = (sunroofChoice == 'y' || sunroofChoice == 'Y');
                             
                             cout << "Enter trunk size (Small/Medium/Large): ";
                             cin.ignore();
                             getline(cin, trunkSize);
                             
                             newCar = new Sedan(make, model, year, price, seatingCapacity, hasNavigation, hasSunroof, trunkSize);
                             break;
                         }
                         case 2: {
                             // SUV-specific details
                             int seatingCapacity, cargoSpace;
                             bool hasNavigation, isAWD;
                             char navChoice, awdChoice;
                             
                             cout << "Enter seating capacity: ";
                             if (!(cin >> seatingCapacity)) {
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                 throw runtime_error("Invalid seating capacity input.");
                             }
                             
                             cout << "Has navigation system? (y/n): ";
                             cin >> navChoice;
                             hasNavigation = (navChoice == 'y' || navChoice == 'Y');
                             
                             cout << "Has all-wheel drive? (y/n): ";
                             cin >> awdChoice;
                             isAWD = (awdChoice == 'y' || awdChoice == 'Y');
                             
                             cout << "Enter cargo space (cubic feet): ";
                             if (!(cin >> cargoSpace)) {
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                 throw runtime_error("Invalid cargo space input.");
                             }
                             
                             newCar = new SUV(make, model, year, price, seatingCapacity, hasNavigation, isAWD, cargoSpace);
                             break;
                         }
                         case 3: {
                             // Truck-specific details
                             double payloadCapacity;
                             string transmissionType;
                             int axleCount;
                             bool hasSleeper;
                             char sleeperChoice;
                             
                             cout << "Enter payload capacity (tons): ";
                             if (!(cin >> payloadCapacity)) {
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                 throw runtime_error("Invalid payload capacity input.");
                             }
                             
                             cout << "Enter transmission type: ";
                             cin.ignore();
                             getline(cin, transmissionType);
                             
                             cout << "Enter axle count: ";
                             if (!(cin >> axleCount)) {
                                 cin.clear();
                                 cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                 throw runtime_error("Invalid axle count input.");
                             }
                             
                             cout << "Has sleeper cabin? (y/n): ";
                             cin >> sleeperChoice;
                             hasSleeper = (sleeperChoice == 'y' || sleeperChoice == 'Y');
                             
                             newCar = new Truck(make, model, year, price, payloadCapacity, transmissionType, axleCount, hasSleeper);
                             break;
                         }
                     }
                     
                     if (newCar != nullptr) {
                         carCatalog.addByCategory(newCar);
                         priceSortedCars.insert(newCar);
                         cout << "\nCar added successfully!" << endl;
                     }
                     
                     break;
                 }
                 case 2: {
                     // Display all cars
                     cout << "\n===== All Cars in Catalog =====" << endl;
                     carCatalog.displayAll();
                     break;
                 }
                 case 3: {
                     // Display cars by category
                     int categoryChoice;
                     cout << "\nSelect category to display:\n";
                     cout << "1. Sedan\n";
                     cout << "2. SUV\n";
                     cout << "3. Truck\n";
                     cout << "Enter choice: ";
                     
                     if (!(cin >> categoryChoice) || categoryChoice < 1 || categoryChoice > 3) {
                         cin.clear();
                         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                         throw runtime_error("Invalid category selection.");
                     }
                     
                     string category;
                     switch (categoryChoice) {
                         case 1:
                             category = "Sedan";
                             break;
                         case 2:
                             category = "SUV";
                             break;
                         case 3:
                             category = "Truck";
                             break;
                     }
                     
                     cout << "\n===== " << category << "s in Catalog =====" << endl;
                     carCatalog.displayByCategory(category);
                     break;
                 }
                 case 4: {
                     // Display cars sorted by price (low to high)
                     priceSortedCars.displayLowToHigh(displayCar);
                     break;
                 }
                 case 5: {
                     // Display cars sorted by price (high to low)
                     priceSortedCars.displayHighToLow(displayCar);
                     break;
                 }
                 case 6: {
                     // Find a car by make and model
                     string make, model;
                     cout << "\nEnter make: ";
                     cin.ignore();
                     getline(cin, make);
                     
                     cout << "Enter model: ";
                     getline(cin, model);
                     
                     Car* foundCar = carCatalog.find(make, model);
                     
                     if (foundCar != nullptr) {
                         cout << "\n===== Car Found =====" << endl;
                         foundCar->displayDetails();
                     } else {
                         cout << "\nCar not found." << endl;
                     }
                     break;
                 }
                 case 7: {
                     // Apply discount to a car
                     string make, model;
                     double discountPercentage;
                     
                     cout << "\nEnter make: ";
                     cin.ignore();
                     getline(cin, make);
                     
                     cout << "Enter model: ";
                     getline(cin, model);
                     
                     Car* foundCar = carCatalog.find(make, model);
                     
                     if (foundCar != nullptr) {
                         cout << "\nCurrent price: $" << fixed << setprecision(2) << foundCar->getPrice() << endl;
                         cout << "Enter discount percentage (0-100): ";
                         
                         if (!(cin >> discountPercentage) || discountPercentage < 0 || discountPercentage > 100) {
                             cin.clear();
                             cin.ignore(numeric_limits<streamsize>::max(), '\n');
                             throw runtime_error("Invalid discount percentage.");
                         }
                         
                         // Apply the discount
                         foundCar->applyDiscount(discountPercentage);
                         
                         cout << "\nDiscount applied successfully!" << endl;
                         cout << "New price: $" << fixed << setprecision(2) << foundCar->getPrice() << endl;
                     } else {
                         cout << "\nCar not found." << endl;
                     }
                     break;
                 }
                 case 8: {
                     // Remove a car from catalog
                     string make, model;
                     cout << "\nEnter make: ";
                     cin.ignore();
                     getline(cin, make);
                     
                     cout << "Enter model: ";
                     getline(cin, model);
                     
                     Car* foundCar = carCatalog.find(make, model);
                     
                     if (foundCar != nullptr) {
                         // Need to rebuild BST after removal
                         // First, get all cars from linked list except the one to remove
                         LinkedList<Car*> tempList;
                         Node<Car*>* current = carCatalog.head;
                         
                         while (current != nullptr) {
                             if (current->data != foundCar) {
                                 tempList.addToEnd(current->data);
                             }
                             current = current->next;
                         }
                         
                         // Remove from linked list
                         bool removed = carCatalog.remove(foundCar);
                         
                         if (removed) {
                             // Rebuild BST
                             BinarySearchTree<Car*> newBST;
                             current = tempList.head;
                             
                             while (current != nullptr) {
                                 newBST.insert(current->data);
                                 current = current->next;
                             }
                             
                             // Replace old BST with new one
                             priceSortedCars = newBST;
                             
                             // Delete the car object
                             delete foundCar;
                             
                             cout << "\nCar removed successfully!" << endl;
                         } else {
                             cout << "\nFailed to remove car." << endl;
                         }
                     } else {
                         cout << "\nCar not found." << endl;
                     }
                     break;
                 }
                 case 9: {
                     running = false;
                     cout << "\nThank you for using the Car Catalog System. Goodbye!" << endl;
                     break;
                 }
                 default: {
                     cout << "\nInvalid choice. Please try again." << endl;
                     break;
                 }
             }
         }
     } catch (const exception& e) {
         cout << "\nError: " << e.what() << endl;
     }
     
     // Clean up dynamic memory by clearing the linked list
     carCatalog.clear();
     
     return 0;
 }