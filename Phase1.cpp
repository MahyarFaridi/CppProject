#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class MealType { BREAKFAST, LUNCH, DINNER };
enum class ReservationStatus { SUCCESS, CANCELLED, FAILED };

class Student {
int userId;
string studentId;
string firstName;
string lastName;
string email;
float accountBalance;
bool isActive;
vector<Reservation*> reservations;
vector<string> errorLog;

public:
Student() : userId(0), studentId(""), firstName(""), lastName(""), email(""), accountBalance(0.0), isActive(true) {}
Student(int uid, const string& sid, const string& first, const string& last, const string& em, float bal)
: userId(uid), studentId(sid), firstName(first), lastName(last), email(em), accountBalance(bal), isActive(true) {}
void print() const {
    cout << "Student Info:\n";
    cout << "User ID: " << userId << "\n";
    cout << "Student ID: " << studentId << "\n";
    cout << "Name: " << firstName << " " << lastName << "\n";
    cout << "Email: " << email << "\n";
    cout << "Account: " << accountBalance << "\n";
    cout << "Active: " << (isActive ? "Yes" : "No") << "\n";
}
bool hasActiveReservationFor(const string& date, MealType type) const {
    for (auto res : reservations) {
        if (res->getDate() == date && res->getMealType() == type && res->getStatus() == ReservationStatus::SUCCESS) {
            return true;
        }
    }
    return false;
}
bool reserveMeal(Meal* meal, DiningHall* hall, const string& date, int reservationId) {
    if (hasActiveReservationFor(date, meal->getMealType())) {
        string msg = "Already reserved for this meal type on " + date;
        errorLog.push_back(msg);
        cout << msg << "\n";
        return false;
    }
    if (hall->getCapacity() <= 0) {
        string msg = "Hall full on " + date;
        errorLog.push_back(msg);
        cout << msg << "\n";
        return false;
    }
    string time = date + " 00:00";
    Reservation* r = new Reservation(reservationId, this, meal, hall, time, date);
    reservations.push_back(r);
    hall->setCapacity(hall->getCapacity() - 1);
    cout << "Reserved!\n";
    return true;
}
bool cancelReservation(Reservation* reservation) {
    return reservation->cancel();
}
void printErrorLog() const {
    cout << "Error Log:\n";
    for (const auto& e : errorLog) {
        cout << "- " << e << "\n";
    }
}
int getUserId() const { return userId; }
string getStudentId() const { return studentId; }
string getFirstName() const { return firstName; }
string getLastName() const { return lastName; }
string getEmail() const { return email; }
float getAccountBallance() const { return accountBalance; }
bool getIsActive() const { return isActive; }
vector<Reservation*> getReservations() const { return reservations; }
vector<string> getErrorLog() const { return errorLog; }
void setUserId(int uid) { userId = uid; }
void setStudentId(const string& sid) { studentId = sid; }
void setFirstName(const string& fn) { firstName = fn; }
void setLastName(const string& ln) { lastName = ln; }
void setEmail(const string& em) { email = em; }
void setAccountBallance(float bal) { accountBalance = bal; }
void setIsActive(bool active) { isActive = active; }
};
class Meal {
    int mealId;
    string name;
    float price;
    MealType mealType;
    vector<string> sideItems;
    
    public:
    Meal() : mealId(0), name(""), price(0.0), mealType(MealType::LUNCH) {}
    void print() const {
        cout << "Meal ID: " << mealId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Price: " << price << "\n";
        cout << "Type: ";
        switch (mealType) {
            case MealType::BREAKFAST: cout << "Breakfast"; break;
            case MealType::LUNCH: cout << "Lunch"; break;
            case MealType::DINNER: cout << "Dinner"; break;
        }
        cout << "\nSide Items: ";
        for (auto& item : sideItems) cout << item << " ";
        cout << "\n";
    }
    void updatePrice(float newPrice) { price = newPrice; }
    void addSideItem(const string& item) { sideItems.push_back(item); }
    int getMealId() const { return mealId; }
    string getName() const { return name; }
    float getPrice() const { return price; }
    MealType getMealType() const { return mealType; }
    vector<string> getSideItems() const { return sideItems; }
    void setMealId(int id) { mealId = id; }
    void setName(const string& n) { name = n; }
    void setPrice(float p) { price = p; }
    void setMealType(MealType type) { mealType = type; }
    };
    class DiningHall {
        int hallId;
        string name;
        string address;
        int capacity;
        
        public:
        DiningHall() : hallId(0), name(""), address(""), capacity(0) {}
        void print() const {
            cout << "Dining Hall ID: " << hallId << "\n";
            cout << "Name: " << name << "\n";
            cout << "Address: " << address << "\n";
            cout << "Capacity: " << capacity << "\n";
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
            Student* student;
            Meal* meal;
            DiningHall* diningHall;
            ReservationStatus status;
            string createdAt;
            string date;
            
            public:
            Reservation() : reservationId(0), student(nullptr), meal(nullptr), diningHall(nullptr), status(ReservationStatus::SUCCESS), createdAt("unknown"), date("unknown") {}
            Reservation(int id, Student* s, Meal* m, DiningHall* d, const string& time, const string& resDate)
            : reservationId(id), student(s), meal(m), diningHall(d), status(ReservationStatus::SUCCESS), createdAt(time), date(resDate) {}
            void print() const {
                cout << "Reservation ID: " << reservationId << "\n";
                cout << "Status: ";
                switch (status) {
                    case ReservationStatus::SUCCESS: cout << "Success"; break;
                    case ReservationStatus::CANCELLED: cout << "Cancelled"; break;
                    case ReservationStatus::FAILED: cout << "Failed"; break;
                }
                cout << "\nCreated At: " << createdAt << "\nDate: " << date << "\n";
            }
            bool cancel() {
                if (status == ReservationStatus::CANCELLED) {
                    cout << "Reservation already cancelled.\n";
                    return false;
                }
                status = ReservationStatus::CANCELLED;
                return true;
            }
            int getReservationId() const { return reservationId; }
            Student* getStudent() const { return student; }
            Meal* getMeal() const { return meal; }
            DiningHall* getDiningHall() const { return diningHall; }
            ReservationStatus getStatus() const { return status; }
            string getCreatedAt() const { return createdAt; }
            string getDate() const { return date; }
            MealType getMealType() const { return meal->getMealType(); }
            void setReservationId(int id) { reservationId = id; }
            void setStudent(Student* s) { student = s; }
            void setMeal(Meal* m) { meal = m; }
            void setDiningHall(DiningHall* d) { diningHall = d; }
            void setStatus(ReservationStatus st) { status = st; }
            void setCreatedAt(const string& time) { createdAt = time; }
            void setDate(const string& d) { date = d; }
            };

            int main (){

                return 0;
            }