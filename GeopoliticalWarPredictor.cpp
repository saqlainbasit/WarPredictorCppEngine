// ============================================================
//   Geopolitical War Outcome Predictor — Implementation
//   OOP Project — BSCS Semester 2
// ============================================================
//   Members:
//   [1] Affaan Asif (L) — 2025-cs-015 — Country Data & Input Handling
//   [2] Abdullah        — 2025-cs-017 — OOP Structure & Operator Overloading
//   [3] Saqlain Haider  — 2025-cs-043 — Alliance & Power Management
//   [4] M. Numan Javed  — 2025-cs-071 — War Prediction & History
// ============================================================

#include "GeopoliticalWarPredictor.h"
#include <iostream>
#include <iomanip>
using namespace std;


// ============================================================
//  SECTION 1A — Country: Data Members & Input Handling
//  Responsible: Affaan Asif (L) — 2025-cs-015
// ============================================================

// Static member initialization
int Country::totalCountries = 0;

// Default constructor
Country::Country() {
    name          = "Unknown";
    militaryPower = 0.0;
    gdp           = 0.0;
    population    = 0;
    region        = "Unknown";
    totalCountries++;
}

// Parameterized constructor
Country::Country(string name, double mil, double gdp, int pop, string region) {
    this->name          = name;
    this->militaryPower = mil;
    this->gdp           = gdp;
    this->population    = pop;
    this->region        = region;
    totalCountries++;
}

// Getters
string Country::getName()          const { return name; }
double Country::getMilitaryPower() const { return militaryPower; }
double Country::getGDP()           const { return gdp; }
int    Country::getPopulation()    const { return population; }
string Country::getRegion()        const { return region; }
int    Country::getTotalCountries()      { return totalCountries; }

// Setters with validation
void Country::setMilitaryPower(double m) {
    if (m >= 0 && m <= 100)
        militaryPower = m;
    else
        cout << "  [!] Military power must be between 0 and 100.\n";
}

void Country::setGDP(double g) {
    if (g >= 0)
        gdp = g;
    else
        cout << "  [!] GDP cannot be negative.\n";
}

// Display
void Country::display() const {
    cout << "  +---------------------------+\n";
    cout << "  | Country : " << left << setw(16) << name         << "|\n";
    cout << "  | Region  : " << left << setw(16) << region       << "|\n";
    cout << "  | Military: " << left << setw(14) << fixed << setprecision(1) << militaryPower << "/100 |\n";
    cout << "  | GDP     : $" << left << setw(12) << fixed << setprecision(2) << gdp           << "T |\n";
    cout << "  | Pop.    : " << left << setw(12) << population   << "M    |\n";
    cout << "  +---------------------------+\n";
}


// ============================================================
//  SECTION 1B — Country: OOP Structure & Operator Overloading
//  Responsible: Abdullah — 2025-cs-017
// ============================================================

// Copy constructor — makes a deep copy of another Country
Country::Country(const Country& c) {
    this->name          = c.name;
    this->militaryPower = c.militaryPower;
    this->gdp           = c.gdp;
    this->population    = c.population;
    this->region        = c.region;
    totalCountries++;
}

// Destructor — decrements static counter when a Country is destroyed
Country::~Country() {
    totalCountries--;
}

// Operator > — compare by military power
bool Country::operator>(const Country& c) const {
    return this->militaryPower > c.militaryPower;
}

// Operator < — compare by military power
bool Country::operator<(const Country& c) const {
    return this->militaryPower < c.militaryPower;
}


// ============================================================
//  SECTION 2 — Alliance: Alliance & Power Management
//  Responsible: Saqlain Haider — 2025-cs-043
// ============================================================

// Static member initialization
int Alliance::totalAlliances = 0;

// Default constructor
Alliance::Alliance() {
    allianceName = "Unnamed Alliance";
    memberCount  = 0;
    for (int i = 0; i < 10; i++) members[i] = nullptr;
    totalAlliances++;
}

// Parameterized constructor
Alliance::Alliance(string name) {
    allianceName = name;
    memberCount  = 0;
    for (int i = 0; i < 10; i++) members[i] = nullptr;
    totalAlliances++;
}

// Destructor — Alliance does NOT own Country objects, so no delete
Alliance::~Alliance() {
    totalAlliances--;
}

// Add a country to the alliance (checks for duplicate & capacity)
void Alliance::addCountry(Country& c) {
    if (memberCount >= 10) {
        cout << "  [!] Alliance is full (max 10 members).\n";
        return;
    }
    for (int i = 0; i < memberCount; i++) {
        if (members[i]->getName() == c.getName()) {
            cout << "  [!] " << c.getName() << " is already in this alliance.\n";
            return;
        }
    }
    members[memberCount++] = &c;
    cout << "  [+] " << c.getName() << " added to " << allianceName << ".\n";
}

// Remove a country by name (shifts remaining members left)
void Alliance::removeCountry(string name) {
    for (int i = 0; i < memberCount; i++) {
        if (members[i]->getName() == name) {
            for (int j = i; j < memberCount - 1; j++)
                members[j] = members[j + 1];
            members[memberCount - 1] = nullptr;
            memberCount--;
            cout << "  [-] " << name << " removed from " << allianceName << ".\n";
            return;
        }
    }
    cout << "  [!] Country '" << name << "' not found in alliance.\n";
}

// Aggregate stats across all members
double Alliance::getCombinedMilitary() const {
    double total = 0;
    for (int i = 0; i < memberCount; i++) total += members[i]->getMilitaryPower();
    return total;
}

double Alliance::getCombinedGDP() const {
    double total = 0;
    for (int i = 0; i < memberCount; i++) total += members[i]->getGDP();
    return total;
}

int Alliance::getCombinedPopulation() const {
    int total = 0;
    for (int i = 0; i < memberCount; i++) total += members[i]->getPopulation();
    return total;
}

string Alliance::getName()         const { return allianceName; }
int    Alliance::getMemberCount()  const { return memberCount; }
int    Alliance::getTotalAlliances()     { return totalAlliances; }

// Friend function — accesses private members array directly for power score
// PowerScore = (military * 0.5) + (gdp * 0.3) + (population * 0.2)
double calculatePowerScore(const Alliance& a) {
    if (a.memberCount == 0) return 0.0;
    double totalMil = 0, totalGDP = 0;
    int    totalPop = 0;
    for (int i = 0; i < a.memberCount; i++) {
        totalMil += a.members[i]->getMilitaryPower();
        totalGDP += a.members[i]->getGDP();
        totalPop += a.members[i]->getPopulation();
    }
    return (totalMil * 0.5) + (totalGDP * 0.3) + (totalPop * 0.2);
}

// Display alliance details with combined stats
void Alliance::display() const {
    cout << "\n  ============================\n";
    cout << "  Alliance : " << allianceName << "\n";
    cout << "  Members  : " << memberCount  << "\n";
    cout << "  ----------------------------\n";
    if (memberCount == 0) {
        cout << "  (No members yet)\n";
    } else {
        for (int i = 0; i < memberCount; i++)
            cout << "  [" << (i+1) << "] " << members[i]->getName()
                 << " (" << members[i]->getRegion() << ")\n";
        cout << "  ----------------------------\n";
        cout << "  Combined Military : " << fixed << setprecision(1) << getCombinedMilitary() << "\n";
        cout << "  Combined GDP      : $" << fixed << setprecision(2) << getCombinedGDP() << "T\n";
        cout << "  Combined Pop.     : " << getCombinedPopulation() << "M\n";
        cout << "  Power Score       : " << fixed << setprecision(2) << calculatePowerScore(*this) << "\n";
    }
    cout << "  ============================\n";
}


// ============================================================
//  SECTION 3 — WarEngine: War Prediction & History
//  Responsible: Muhammad Numan Javed — 2025-cs-071
// ============================================================

// Constructor
WarEngine::WarEngine() {
    recordCount = 0;
}

// Destructor
WarEngine::~WarEngine() {
    // No dynamic memory to free
}

// Core score formula: PowerScore = (military * 0.5) + (gdp * 0.3) + (population * 0.2)
double WarEngine::calculateScore(double military, double gdp, int population) const {
    return (military * 0.5) + (gdp * 0.3) + (population * 0.2);
}

// Helper: save a result to history
static void saveRecord(WarRecord* history, int& recordCount,
                       const string& s1, const string& s2,
                       const string& winner, double margin) {
    if (recordCount < 50) {
        history[recordCount].side1            = s1;
        history[recordCount].side2            = s2;
        history[recordCount].winner           = winner;
        history[recordCount].marginOfVictory  = margin;
        recordCount++;
    }
}

// --- Overload 1: Country vs Country ---
void WarEngine::predictWar(const Country& c1, const Country& c2) {
    double score1 = calculateScore(c1.getMilitaryPower(), c1.getGDP(), c1.getPopulation());
    double score2 = calculateScore(c2.getMilitaryPower(), c2.getGDP(), c2.getPopulation());
    double margin = (score1 >= score2) ? score1 - score2 : score2 - score1;
    string winner = (score1 >= score2) ? c1.getName() : c2.getName();
    string loser  = (score1 >= score2) ? c2.getName() : c1.getName();

    cout << "\n  ==============================\n";
    cout << "   WAR PREDICTION RESULT\n";
    cout << "  ==============================\n";
    cout << "  " << c1.getName() << " vs " << c2.getName() << "\n";
    cout << "  ------------------------------\n";
    cout << "  " << c1.getName() << " Score : " << fixed << setprecision(2) << score1 << "\n";
    cout << "  " << c2.getName() << " Score : " << fixed << setprecision(2) << score2 << "\n";
    cout << "  ------------------------------\n";
    cout << "  WINNER : " << winner << "\n";
    cout << "  LOSER  : " << loser  << "\n";
    cout << "  MARGIN : " << fixed << setprecision(2) << margin << "\n";
    cout << "  ==============================\n";

    saveRecord(history, recordCount, c1.getName(), c2.getName(), winner, margin);
}

// --- Overload 2: Alliance vs Alliance ---
void WarEngine::predictWar(const Alliance& a1, const Alliance& a2) {
    double score1 = calculateScore(a1.getCombinedMilitary(), a1.getCombinedGDP(), a1.getCombinedPopulation());
    double score2 = calculateScore(a2.getCombinedMilitary(), a2.getCombinedGDP(), a2.getCombinedPopulation());
    double margin = (score1 >= score2) ? score1 - score2 : score2 - score1;
    string winner = (score1 >= score2) ? a1.getName() : a2.getName();
    string loser  = (score1 >= score2) ? a2.getName() : a1.getName();

    cout << "\n  ==============================\n";
    cout << "   ALLIANCE WAR PREDICTION\n";
    cout << "  ==============================\n";
    cout << "  " << a1.getName() << " vs " << a2.getName() << "\n";
    cout << "  ------------------------------\n";
    cout << "  " << a1.getName() << " Score : " << fixed << setprecision(2) << score1 << "\n";
    cout << "  " << a2.getName() << " Score : " << fixed << setprecision(2) << score2 << "\n";
    cout << "  ------------------------------\n";
    cout << "  WINNER : " << winner << "\n";
    cout << "  LOSER  : " << loser  << "\n";
    cout << "  MARGIN : " << fixed << setprecision(2) << margin << "\n";
    cout << "  ==============================\n";

    saveRecord(history, recordCount, a1.getName(), a2.getName(), winner, margin);
}

// --- Overload 3: Alliance vs Country ---
void WarEngine::predictWar(const Alliance& a, const Country& c) {
    double scoreA = calculateScore(a.getCombinedMilitary(), a.getCombinedGDP(), a.getCombinedPopulation());
    double scoreC = calculateScore(c.getMilitaryPower(), c.getGDP(), c.getPopulation());
    double margin = (scoreA >= scoreC) ? scoreA - scoreC : scoreC - scoreA;
    string winner = (scoreA >= scoreC) ? a.getName() : c.getName();
    string loser  = (scoreA >= scoreC) ? c.getName() : a.getName();

    cout << "\n  ==============================\n";
    cout << "   ALLIANCE vs COUNTRY\n";
    cout << "  ==============================\n";
    cout << "  " << a.getName() << " vs " << c.getName() << "\n";
    cout << "  ------------------------------\n";
    cout << "  " << a.getName() << " Score : " << fixed << setprecision(2) << scoreA << "\n";
    cout << "  " << c.getName() << " Score : " << fixed << setprecision(2) << scoreC << "\n";
    cout << "  ------------------------------\n";
    cout << "  WINNER : " << winner << "\n";
    cout << "  LOSER  : " << loser  << "\n";
    cout << "  MARGIN : " << fixed << setprecision(2) << margin << "\n";
    cout << "  ==============================\n";

    saveRecord(history, recordCount, a.getName(), c.getName(), winner, margin);
}

// Show all recorded war outcomes
void WarEngine::showHistory() const {
    if (recordCount == 0) {
        cout << "\n  [!] No war predictions recorded yet.\n";
        return;
    }
    cout << "\n  ==============================\n";
    cout << "        WAR HISTORY LOG\n";
    cout << "  ==============================\n";
    for (int i = 0; i < recordCount; i++) {
        cout << "  [" << (i+1) << "] " << history[i].side1 << " vs " << history[i].side2 << "\n";
        cout << "      Winner : " << history[i].winner << "\n";
        cout << "      Margin : " << fixed << setprecision(2) << history[i].marginOfVictory << "\n";
        cout << "  ------------------------------\n";
    }
}

// Reset history
void WarEngine::clearHistory() {
    recordCount = 0;
    cout << "  [+] War history cleared.\n";
}
