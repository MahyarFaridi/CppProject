#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

enum class MealType { BREAKFAST, LUNCH, DINNER };
enum class RStatus { SUCCESS, CANCELLED, FAILED, NOT_PAID };
enum class ReserveDay { SATURDAY, SUNDAY, MONDAY, TUESDAY, WEDNESDAY };
enum class TransactionType { TRANSFER, PAYMENT };
enum class TransactionStatus { PENDING, COMPLETED, FAILED };
enum class SessionStatus { AUTHENTICATED, ANONYMOUS };

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
class Transaction;

class Student : public User {
string studentId;
string email;
string phone;
float accountBalance;
bool isActive;
vector<Reservation*> reservations;
vector<Transaction> transactions;
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
vector<Transaction> getTransactions() const { return transactions; }
void addTransaction(const Transaction& t) { transactions.push_back(t); }
void setAccountBalance(float b) { accountBalance = b; }
float getAccountBalance() const { return accountBalance; }

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
            case RStatus::NOT_PAID: cout << "Not Paid"; break;
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

class Transaction {
    int transactionID;
    string trackingCode;
    float amount;
    TransactionType type;
    TransactionStatus status;
    time_t createdAt;

public:
    Transaction()
        : transactionID(0), trackingCode(""), amount(0.0),
          type(TransactionType::PAYMENT), status(TransactionStatus::PENDING),
          createdAt(time(0)) {}

    int getTransactionID() const { return transactionID; }
    string getTrackingCode() const { return trackingCode; }
    float getAmount() const { return amount; }
    TransactionType getType() const { return type; }
    TransactionStatus getStatus() const { return status; }
    time_t getCreatedAt() const { return createdAt; }

    void setTransactionID(int id) { transactionID = id; }
    void setTrackingCode(const string& code) { trackingCode = code; }
    void setAmount(float amt) { amount = amt; }
    void setType(TransactionType t) { type = t; }
    void setStatus(TransactionStatus s) { status = s; }
    void setCreatedAt(time_t t) { createdAt = t; }
};

class IDGenerator {
    static int reservationCounter;
    static int transactionCounter;

public:
    static int generateReservationId() { return reservationCounter++; }
    static int generateTransactionId() { return transactionCounter++; }
};

int IDGenerator::reservationCounter = 1;
int IDGenerator::transactionCounter = 1000;

class ShoppingCart {
    vector<Reservation> reservations;

public:
    void addReservation(const Reservation& reservation) {
        reservations.push_back(reservation);
    }

    void removeReservation(int id) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if (it->getReservationId() == id) {
                reservations.erase(it);
                break;
            }
        }
    }

    void viewShoppingCartItems() const {
        cout << "Shopping Cart Items:" << endl;
        for (const auto& res : reservations) {
            res.print();
            cout << "------------------------" << endl;
        }
    }

    void clear() {
        reservations.clear();
    }

    vector<Reservation> getReservations() const {
        return reservations;
    }

    Transaction confirm();
};

class SessionBase {
    protected:
        time_t createdAt;
        time_t lastLoginTime;
        SessionStatus status;
    
    public:
        SessionBase()
            : createdAt(time(0)), lastLoginTime(time(0)), status(SessionStatus::ANONYMOUS) {}
    
        virtual void loadSession() = 0;
        virtual void saveSession() = 0;
        virtual void login(const string& username, const string& password) = 0;
        virtual void logout() = 0;
    
        time_t getCreatedAt() const { return createdAt; }
        time_t getLastLoginTime() const { return lastLoginTime; }
        SessionStatus getStatus() const { return status; }
    
        void setCreatedAt(time_t t) { createdAt = t; }
        void setLastLoginTime(time_t t) { lastLoginTime = t; }
        void setStatus(SessionStatus s) { status = s; }
    };

    namespace StudentSession {

        class SessionManager : public SessionBase {
            Student* currentStudent;
            ShoppingCart* shoppingCart;
            int studentID;
        
            SessionManager()
                : currentStudent(nullptr), shoppingCart(new ShoppingCart()), studentID(0) {}
        
            SessionManager(const SessionManager&) = delete;
            SessionManager& operator=(const SessionManager&) = delete;
        
        public:
            static SessionManager& instance() {
                static SessionManager sessionInstance;
                return sessionInstance;
            }
        
            void loadSession() override {}
            void saveSession() override {}
            void login(const string& username, const string& password) override {}
            void logout() override {
                currentStudent = nullptr;
                studentID = 0;
                status = SessionStatus::ANONYMOUS;
            }
        
            Student* getCurrentStudent() const { return currentStudent; }
            ShoppingCart* getShoppingCart() const { return shoppingCart; }
            int getStudentID() const { return studentID; }
        
            void setCurrentStudent(Student* s) { currentStudent = s; }
            void setStudentID(int id) { studentID = id; }
        };
        
        }


class Panel {
    public:
        void Action(int action) {
            switch (action) {
                case 1: showStudentInfo(); break;
                case 2: checkBalance(); break;
                case 3: viewReservations(); break;
                case 4: viewShoppingCart(); break;
                case 5: addToShoppingCart(); break;
                case 6: confirmShoppingCart(); break;
                case 7: removeShoppingCartItem(); break;
                case 8: increaseBalance(); break;
                case 9: viewRecentTransactions(); break;
                case 10: cancelReservation(0); break;
                case 0: exit(); break;
                default: cout << "Invalid action." << endl;
            }
        }
    
        void showMenu() {
            cout << "1. Show Info\n2. Check Balance\n3. View Reservations\n4. View Shopping Cart\n"
                 << "5. Add to Shopping Cart\n6. Confirm Shopping Cart\n7. Remove Cart Item\n"
                 << "8. Increase Balance\n9. View Transactions\n10. Cancel Reservation\n0. Exit\n";
        }
    
        void showStudentInfo() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
            if (sm.getCurrentStudent())
                sm.getCurrentStudent()->print();
            else
                cout << "No student logged in.\n";
        }
    
        void checkBalance() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
            if (sm.getCurrentStudent())
                cout << "Balance: " << sm.getCurrentStudent()->getAccountBalance() << endl;
        }
    
        void viewReservations() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
            vector<Reservation*> reserves = sm.getCurrentStudent()->getReserves();
            for (auto* r : reserves) {
                r->print();
                cout << "-----------------------\n";
            }
        }
    
        void viewShoppingCart() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
            sm.getShoppingCart()->viewShoppingCartItems();
        }
    
        void addToShoppingCart() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
    
            int mealId;
            cout << "Enter Meal ID to add to cart: ";
            cin >> mealId;
    
            Meal* selectedMeal = nullptr;
            for (auto& meal : Storage::instance().getMeals()) {
                if (meal.getMealId() == mealId && meal.getIsActive()) {
                    selectedMeal = &meal;
                    break;
                }
            }
    
            if (!selectedMeal) {
                cout << "Invalid meal ID or inactive meal.\n";
                return;
            }
    
            int hallId;
            cout << "Enter Dining Hall ID: ";
            cin >> hallId;
    
            DiningHall* selectedHall = nullptr;
            for (auto& hall : Storage::instance().getDiningHalls()) {
                if (hall.getHallId() == hallId) {
                    selectedHall = &hall;
                    break;
                }
            }
    
            if (!selectedHall) {
                cout << "Invalid dining hall ID.\n";
                return;
            }
    
            Reservation newRes;
            newRes.setReservationId(IDGenerator::generateReservationId());
            newRes.setMeal(selectedMeal);
            newRes.setDiningHall(selectedHall);
            newRes.setStatus(RStatus::NOT_PAID);
    
            sm.getShoppingCart()->addReservation(newRes);
            cout << "Reservation added to cart.\n";
        }
    
        void confirmShoppingCart() {
            StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
            Student* student = sm.getCurrentStudent();
            vector<Reservation> items = sm.getShoppingCart()->getReservations();
    
            float total = 0.0;
            for (auto& res : items) {
                total += res.getMeal()->getPrice();
            }
    
            if (student->getAccountBalance() < total) {
                cout << "Insufficient balance.\n";
                return;
            }
    
            student->setAccountBalance(student->getAccountBalance() - total);
            Transaction t;
        t.setTransactionID(IDGenerator::generateTransactionId());
        t.setAmount(total);
        t.setType(TransactionType::PAYMENT);
        t.setStatus(TransactionStatus::COMPLETED);
        t.setCreatedAt(time(0));
        student->addTransaction(t);

        for (auto& res : items) {
            Reservation* r = new Reservation(res);
            r->setStatus(RStatus::SUCCESS);
            student->getReserves().push_back(r);
        }

        sm.getShoppingCart()->clear();
        cout << "Reservation(s) confirmed.\n";
    }

    void removeShoppingCartItem() {
        int id;
        cout << "Enter Reservation ID to remove: ";
        cin >> id;

        StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
        sm.getShoppingCart()->removeReservation(id);
    }

    void increaseBalance() {
        float amount;
        cout << "Enter amount to add: ";
        cin >> amount;

        StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
        Student* student = sm.getCurrentStudent();
        student->setAccountBalance(student->getAccountBalance() + amount);
        cout << "Balance increased.\n";
    }

    void viewRecentTransactions() {
        StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
        vector<Transaction> txs = sm.getCurrentStudent()->getTransactions();

        cout << "Recent Transactions:\n";
        for (const auto& t : txs) {
            cout << "ID: " << t.getTransactionID() << ", Amount: " << t.getAmount()
                 << ", Type: " << (t.getType() == TransactionType::PAYMENT ? "Payment" : "Transfer")
                 << ", Status: ";
            switch (t.getStatus()) {
                case TransactionStatus::PENDING: cout << "Pending"; break;
                case TransactionStatus::COMPLETED: cout << "Completed"; break;
                case TransactionStatus::FAILED: cout << "Failed"; break;
            }
            time_t created = t.getCreatedAt();
            cout << ", Date: " << ctime(&created);
        }
    }

    void cancelReservation(int id) {
        StudentSession::SessionManager& sm = StudentSession::SessionManager::instance();
        vector<Reservation*> resList = sm.getCurrentStudent()->getReserves();

        for (auto* r : resList) {
            if (r->getReservationId() == id && r->getStatus() == RStatus::SUCCESS) {
                r->setStatus(RStatus::CANCELLED);
                cout << "Reservation cancelled.\n";
                return;
            }
        }
        cout << "Reservation not found or not cancellable.\n";
    }

    void exit() {
        cout << "Goodbye!\n";
    }
};
int main (){}