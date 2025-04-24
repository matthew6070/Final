
int main() {
     // Create containers
     LinkedList<Car*> carCatalog;
     BinarySearchTree<Car*> priceSortedCars;
     
     bool running = true;
     int choice;
     
     // Add some sample cars to the catalog
     try {
         // Add a Sedan
         Sedan* sedan1 = new Sedan("Toyota", "Camry", 2022, 25000);
         carCatalog.addByCategory(sedan1);
         priceSortedCars.insert(sedan1);
         
         // Add an SUV
         SUV* suv1 = new SUV("Honda", "CR-V", 2023, 32000);
         carCatalog.addByCategory(suv1);
         priceSortedCars.insert(suv1);
         
         // Add a Truck
         Truck* truck1 = new Truck("Ford", "F-150", 2021, 40000);
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
             cout << "7. Remove a car from catalog\n";
             cout << "8. Exit\n";


             cout << "Enter your choice: ";
             
             if (!(cin >> choice)) {
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
                     cout << "\nThank you for using the Car Catalog. Bye!" << endl;
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