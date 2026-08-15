// ============================================================
//   Geopolitical War Outcome Predictor
//   OOP Project — BSCS Semester 2
// ============================================================
//   Members:
//   [1] Affaan Asif (L) — 2025-cs-015 — Country Data & Input Handling
//   [2] Abdullah        — 2025-cs-017 — OOP Structure & Operator Overloading
//   [3] Saqlain Haider  — 2025-cs-043 — Alliance & Power Management
//   [4] M. Numan Javed  — 2025-cs-071 — War Prediction & History
// ============================================================

#ifndef GEOPOLITICAL_WAR_PREDICTOR_H
#define GEOPOLITICAL_WAR_PREDICTOR_H

#include <string>
using namespace std;

// ============================================================
//  SECTION 1 — Country Class
//  Responsible: Affaan Asif (L) & Abdullah
//  Affaan   → Data members, constructors, getters/setters
//  Abdullah → Copy constructor, destructor, operator overloading
// ============================================================

class Country {
private:
    string name;
    double militaryPower;   // Scale: 0 – 100
    double gdp;             // In trillion USD
    int    population;      // In millions
    string region;

    static int totalCountries;  // Tracks all Country objects alive

public:
    // --- Constructors & Destructor (Affaan) ---
    Country();
    Country(string name, double mil, double gdp, int pop, string region);

    // --- Copy Constructor & Destructor (Abdullah) ---
    Country(const Country& c);
    ~Country();

    // --- Getters (Affaan) ---
    string getName()        const;
    double getMilitaryPower() const;
    double getGDP()         const;
    int    getPopulation()  const;
    string getRegion()      const;
    static int getTotalCountries();

    // --- Setters with validation (Affaan) ---
    void setMilitaryPower(double m);
    void setGDP(double g);

    // --- Operator Overloading — compares military power (Abdullah) ---
    bool operator>(const Country& c) const;
    bool operator<(const Country& c) const;

    void display() const;
};


// ============================================================
//  SECTION 2 — Alliance Class
//  Responsible: Saqlain Haider (2025-cs-043)
//  Alliance & Power Management
// ============================================================

class Alliance {
private:
    string   allianceName;
    Country* members[10];   // Aggregation — stores pointers, does NOT own them
    int      memberCount;

    static int totalAlliances;

public:
    Alliance();
    Alliance(string name);
    ~Alliance();

    void addCountry(Country& c);
    void removeCountry(string name);

    double getCombinedMilitary()   const;
    double getCombinedGDP()        const;
    int    getCombinedPopulation() const;

    string getName()        const;
    int    getMemberCount() const;
    static int getTotalAlliances();

    // Friend function — directly accesses private members for power score
    friend double calculatePowerScore(const Alliance& a);

    void display() const;
};

// Forward declaration of friend function
double calculatePowerScore(const Alliance& a);


// ============================================================
//  SECTION 3 — WarEngine Class
//  Responsible: Muhammad Numan Javed (2025-cs-071)
//  War Prediction & History
// ============================================================

struct WarRecord {
    string side1;
    string side2;
    string winner;
    double marginOfVictory;
};

class WarEngine {
private:
    WarRecord history[50];
    int       recordCount;

public:
    WarEngine();
    ~WarEngine();

    // Function Overloading — three prediction modes
    void predictWar(const Country&  c1, const Country&  c2);
    void predictWar(const Alliance& a1, const Alliance& a2);
    void predictWar(const Alliance& a,  const Country&  c);

    void showHistory()  const;
    void clearHistory();

    double calculateScore(double military, double gdp, int population) const;
};

#endif // GEOPOLITICAL_WAR_PREDICTOR_H
