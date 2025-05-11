#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

enum class MealType { BREAKFAST, LUNCH, DINNER };
enum class RStatus { SUCCESS, CANCELLED, FAILED };
enum class ReserveDay { SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY };

class User {
protected:
int userId;
string name;
string lastName;
string hashedPassword;

public:
User() : userId(0), name(""), lastName(""), hashedPassword("") {}
User(int uid, const string& n, const string& l, const string& pass)
: userId(uid), name(n), lastName(l), hashedPassword(pass) {}

virtual void print() const {  
    cout << "User Info:" << endl;  
    cout << "User ID: " << userId << endl;  
    cout << "Name: " << name << " " << lastName << endl;  
}  

virtual string getType() const = 0;  

int getUserId() const { return userId; }  
string getName() const { return name; }  
string getLastName() const { return lastName; }  
string getHashedPassword() const { return hashedPassword; }  

void setUserId(int id) { userId = id; }  
void setName(const string& n) { name = n; }  
void setLastName(const string& l) { lastName = l; }  
void setHashedPassword(const string& pass) { hashedPassword = pass; }

};

class Meal;
class DiningHall;
class Reservation;

class Student : public User {
string studentId;
string email;
string phone;
float accountBalance;
bool isActive;
vector<Reservation*> reservations;
vector<string> errorLog;

public:
Student()
: User(), studentId(""), email(""), phone(""), accountBalance(0.0), isActive(true) {}

Student(int uid, const string& sid, const string& first, const string& last,  
        const string& em, const string& ph, float bal, const string& pass)  
    : User(uid, first, last, pass), studentId(sid), email(em), phone(ph),  
      accountBalance(bal), isActive(true) {}  

void print() const override {  
    cout << "Student Info:" << endl;  
    cout << "User ID: " << userId << endl;  
    cout << "Student ID: " << studentId << endl;  
    cout << "Name: " << name << " " << lastName << endl;  
    cout << "Email: " << email << endl;  
    cout << "Phone: " << phone << endl;  
    cout << "Account: " << accountBalance << endl;  
    cout << "Active: " << (isActive ? "Yes" : "No") << endl;  
}

string getType() const override { return "Student"; }  

void activate() { isActive = true; }  
void deactivate() { isActive = false; }  
bool getIsActive() const { return isActive; }  

vector<Reservation*> getReserves() const { return reservations; }

};

class Admin : public User {
public:
Admin() : User() {}
Admin(int uid, const string& n, const string& l, const string& pass)
: User(uid, n, l, pass) {}

void print() const override {  
    cout << "Admin Info:" << endl;  
    cout << "User ID: " << userId << endl;  
    cout << "Name: " << name << " " << lastName << endl;  
}  

string getType() const override { return "Admin"; }

};

class Meal {
    int mealId;
    string name;
    float price;
    bool isActive;
    MealType mealType;
    ReserveDay reserveDay;
    vector<string> sideItems;
    
    public:
    Meal()
    : mealId(0), name(""), price(0.0), isActive(true),
    mealType(MealType::LUNCH), reserveDay(ReserveDay::SATURDAY) {}
    
    void print() const {  
        cout << "Meal ID: " << mealId << endl;  
        cout << "Name: " << name << endl;  
        cout << "Price: " << price << endl;  
        cout << "Type: ";  
        switch (mealType) {  
            case MealType::BREAKFAST: cout << "Breakfast"; break;  
            case MealType::LUNCH: cout << "Lunch"; break;  
            case MealType::DINNER: cout << "Dinner"; break;  
        }  
        cout << endl;  
        cout << "Reserve Day: ";  
        switch (reserveDay) {  
            case ReserveDay::SATURDAY: cout << "Saturday"; break;  
            case ReserveDay::SUNDAY: cout << "Sunday"; break;  
            case ReserveDay::MONDAY: cout << "Monday"; break;  
            case ReserveDay::TUESDAY: cout << "Tuesday"; break;  
            case ReserveDay::WEDNESDAY: cout << "Wednesday"; break;  
        }  
        cout << endl;  
        cout << "Active: " << (isActive ? "Yes" : "No") << endl;  
        cout << "Side Items: ";  
        for (auto& item : sideItems) cout << item << " ";  
        cout << endl;  
    }

    void activate() { isActive = true; }  
void deactivate() { isActive = false; }  
bool getIsActive() const { return isActive; }  

void addSideItem(const string& item) { sideItems.push_back(item); }  
void updatePrice(float newPrice) { price = newPrice; }  

int getMealId() const { return mealId; }  
string getName() const { return name; }  
float getPrice() const { return price; }  
MealType getMealType() const { return mealType; }  
ReserveDay getReserveDay() const { return reserveDay; }  
vector<string> getSideItems() const { return sideItems; }  

void setMealId(int id) { mealId = id; }  
void setName(const string& n) { name = n; }  
void setPrice(float p) { price = p; }  
void setMealType(MealType type) { mealType = type; }  
void setReserveDay(ReserveDay day) { reserveDay = day; }

};

class DiningHall {
    int hallId;
    string name;
    string address;
    int capacity;
    
    public:
    DiningHall() : hallId(0), name(""), address(""), capacity(0) {}
    
    void print() const {  
        cout << "Dining Hall ID: " << hallId << endl;  
        cout << "Name: " << name << endl;  
        cout << "Address: " << address << endl;  
        cout << "Capacity: " << capacity << endl;  
    }  
    
    int getHallId() const { return hallId; }  
    string getName() const { return name; }  
    string getAddress() const { return address; }  
    int getCapacity() const { return capacity; }  
    
    void setHallId(int id) { hallId = id; }  
    void setName(const string& n) { name = n; }  
    void setAddress(const string& addr) { address = addr; }  
    void setCapacity(int cap) { capacity = cap; }
    
    };
    
    class Reservation {
    int reservationId;
    DiningHall* diningHall;
    Meal* meal;
    RStatus status;
    time_t createdAt;
    
    public:
    Reservation()
    : reservationId(0), diningHall(nullptr), meal(nullptr),
    status(RStatus::SUCCESS), createdAt(time(0)) {}

    Reservation(int id, DiningHall* hall, Meal* m)  
    : reservationId(id), diningHall(hall), meal(m),  
      status(RStatus::SUCCESS), createdAt(time(0)) {}  

void print() const {  
    cout << "Reservation ID: " << reservationId << endl;  
    cout << "Status: ";  
    switch (status) {  
        case RStatus::SUCCESS: cout << "Success"; break;  
        case RStatus::CANCELLED: cout << "Cancelled"; break;  
        case RStatus::FAILED: cout << "Failed"; break;  
    }  
    cout << endl;  
    cout << "Created At: " << ctime(&createdAt);  
}  

RStatus getStatus() const { return status; }  
void setStatus(RStatus s) { status = s; }  

int getReservationId() const { return reservationId; }  
Meal* getMeal() const { return meal; }  
DiningHall* getDiningHall() const { return diningHall; }  
time_t getCreatedAt() const { return createdAt; }  

void setReservationId(int id) { reservationId = id; }  
void setMeal(Meal* m) { meal = m; }  
void setDiningHall(DiningHall* d) { diningHall = d; }

};

class Storage {
    private:
    int mealIdCounter;
    int diningHallIdCounter;
    vector<Meal> allMeals;
    vector<DiningHall> allDiningHalls;
    
    Storage() : mealIdCounter(1), diningHallIdCounter(1) {}  
    Storage(const Storage&) = delete;  
    void operator=(const Storage&) = delete;
    
    public:
    static Storage& instance() {
    static Storage storageInstance;
    return storageInstance;
    }
    
    int generateMealId() { return mealIdCounter++; }  
    int generateDiningHallId() { return diningHallIdCounter++; }  
    
    void addMeal(const Meal& meal) { allMeals.push_back(meal); }  
    void addDiningHall(const DiningHall& hall) { allDiningHalls.push_back(hall); }  
    
    vector<Meal>& getMeals() { return allMeals; }  
    vector<DiningHall>& getDiningHalls() { return allDiningHalls; }
    
    };
    
    class Panel {
    public:
    void Action(int action) {}
    void showMenu() {}
    void showStudentInfo();
    void checkBalance();
    void viewReservations();
    void addReservation(Reservation);
    void addToShoppingCart();
    void confirmShoppingCart();
    void removeShoppingCartItem();
    void increaseBalance();
    void viewRecentTransactions();
    void cancelReservation(int);
    void exit() {}
    };



    int main (){}