// ============================================================
//   Geopolitical War Outcome Predictor — main.cpp
//   OOP Project — BSCS Semester 2
// ============================================================
//   Members:
//   [1] Affaan Asif (L) — 2025-cs-015 — Country Data & Input Handling
//   [2] Abdullah        — 2025-cs-017 — OOP Structure & Operator Overloading
//   [3] Saqlain Haider  — 2025-cs-043 — Alliance & Power Management
//   [4] M. Numan Javed  — 2025-cs-071 — War Prediction & History
//
//   Description:
//   A terminal-based C++ simulation that predicts war outcomes
//   between countries using real stats like military power, GDP,
//   and population. Users can form alliances, compare nations,
//   and run conflict simulations with calculated results.
//   Built on core OOP principles with clean class design,
//   operator overloading, and a full history log.
// ============================================================

#include <iostream>
#include <string>
#include "GeopoliticalWarPredictor.h"
using namespace std;

// ── Global Storage ────────────────────────────────────────────
const int MAX_COUNTRIES = 20;
const int MAX_ALLIANCES = 5;

Country  countries[MAX_COUNTRIES];
int      countryCount = 0;

Alliance alliances[MAX_ALLIANCES];
int      allianceCount = 0;

WarEngine engine;

// ── Helpers ───────────────────────────────────────────────────

int findCountry(const string& name) {
    for (int i = 0; i < countryCount; i++)
        if (countries[i].getName() == name) return i;
    return -1;
}

int findAlliance(const string& name) {
    for (int i = 0; i < allianceCount; i++)
        if (alliances[i].getName() == name) return i;
    return -1;
}

// ============================================================
//  MENU FUNCTIONS
//  [Affaan] addCountry, viewAllCountries, updateCountryStats
// ============================================================

void addCountry() {
    if (countryCount >= MAX_COUNTRIES) {
        cout << "  [!] Maximum country limit reached.\n";
        return;
    }
    string name, region;
    double mil, gdp;
    int pop;

    cout << "\n  --- Add New Country ---\n";
    cout << "  Name              : "; cin.ignore(); getline(cin, name);
    cout << "  Region            : "; getline(cin, region);
    cout << "  Military (0-100)  : "; cin >> mil;
    cout << "  GDP (trillion $)  : "; cin >> gdp;
    cout << "  Population (mil.) : "; cin >> pop;

    countries[countryCount++] = Country(name, mil, gdp, pop, region);
    cout << "  [+] " << name << " added successfully.\n";
}

void viewAllCountries() {
    if (countryCount == 0) {
        cout << "\n  [!] No countries added yet.\n";
        return;
    }
    cout << "\n  === All Countries (" << countryCount << ") ===\n";
    for (int i = 0; i < countryCount; i++) {
        cout << "\n  [" << (i+1) << "]";
        countries[i].display();
    }
    cout << "  Total countries tracked: " << Country::getTotalCountries() << "\n";
}

void updateCountryStats() {
    cout << "\n  --- Update Country Stats ---\n";
    string name;
    cout << "  Country name: "; cin.ignore(); getline(cin, name);
    int idx = findCountry(name);
    if (idx == -1) { cout << "  [!] Country not found.\n"; return; }

    double mil, gdp;
    cout << "  New Military Power (0-100) : "; cin >> mil;
    cout << "  New GDP (trillion $)       : "; cin >> gdp;
    countries[idx].setMilitaryPower(mil);
    countries[idx].setGDP(gdp);
    cout << "  [+] Stats updated.\n";
}

// ============================================================
//  [Abdullah] compareCountries — uses overloaded operators
// ============================================================

void compareCountries() {
    cout << "\n  --- Compare Two Countries (Military Power) ---\n";
    string name1, name2;
    cout << "  Country 1: "; cin.ignore(); getline(cin, name1);
    cout << "  Country 2: "; getline(cin, name2);

    int i1 = findCountry(name1), i2 = findCountry(name2);
    if (i1 == -1 || i2 == -1) {
        cout << "  [!] One or both countries not found.\n";
        return;
    }
    if (countries[i1] > countries[i2])
        cout << "  " << name1 << " has higher military power than " << name2 << ".\n";
    else if (countries[i1] < countries[i2])
        cout << "  " << name2 << " has higher military power than " << name1 << ".\n";
    else
        cout << "  Both countries have equal military power.\n";
}

// ============================================================
//  [Saqlain] Alliance management menu functions
// ============================================================

void createAlliance() {
    if (allianceCount >= MAX_ALLIANCES) {
        cout << "  [!] Maximum alliance limit reached.\n";
        return;
    }
    string name;
    cout << "\n  --- Create Alliance ---\n";
    cout << "  Alliance name: "; cin.ignore(); getline(cin, name);
    alliances[allianceCount++] = Alliance(name);
    cout << "  [+] Alliance '" << name << "' created.\n";
    cout << "  Total alliances: " << Alliance::getTotalAlliances() << "\n";
}

void addCountryToAlliance() {
    cout << "\n  --- Add Country to Alliance ---\n";
    string aName, cName;
    cout << "  Alliance name: "; cin.ignore(); getline(cin, aName);
    int ai = findAlliance(aName);
    if (ai == -1) { cout << "  [!] Alliance not found.\n"; return; }

    cout << "  Country name : "; getline(cin, cName);
    int ci = findCountry(cName);
    if (ci == -1) { cout << "  [!] Country not found.\n"; return; }

    alliances[ai].addCountry(countries[ci]);
}

void removeCountryFromAlliance() {
    cout << "\n  --- Remove Country from Alliance ---\n";
    string aName, cName;
    cout << "  Alliance name: "; cin.ignore(); getline(cin, aName);
    int ai = findAlliance(aName);
    if (ai == -1) { cout << "  [!] Alliance not found.\n"; return; }

    cout << "  Country name : "; getline(cin, cName);
    alliances[ai].removeCountry(cName);
}

void viewAlliances() {
    if (allianceCount == 0) {
        cout << "\n  [!] No alliances created yet.\n";
        return;
    }
    cout << "\n  === All Alliances (" << allianceCount << ") ===\n";
    for (int i = 0; i < allianceCount; i++)
        alliances[i].display();
}

// ============================================================
//  [Numan] War prediction menu functions
// ============================================================

void predictCountryVsCountry() {
    if (countryCount < 2) { cout << "\n  [!] Need at least 2 countries.\n"; return; }
    string n1, n2;
    cout << "\n  --- Country vs Country ---\n";
    cout << "  Country 1: "; cin.ignore(); getline(cin, n1);
    cout << "  Country 2: "; getline(cin, n2);
    int i1 = findCountry(n1), i2 = findCountry(n2);
    if (i1 == -1 || i2 == -1) { cout << "  [!] One or both countries not found.\n"; return; }
    if (i1 == i2)              { cout << "  [!] Cannot simulate a country against itself.\n"; return; }
    engine.predictWar(countries[i1], countries[i2]);
}

void predictAllianceVsAlliance() {
    if (allianceCount < 2) { cout << "\n  [!] Need at least 2 alliances.\n"; return; }
    string n1, n2;
    cout << "\n  --- Alliance vs Alliance ---\n";
    cout << "  Alliance 1: "; cin.ignore(); getline(cin, n1);
    cout << "  Alliance 2: "; getline(cin, n2);
    int i1 = findAlliance(n1), i2 = findAlliance(n2);
    if (i1 == -1 || i2 == -1) { cout << "  [!] One or both alliances not found.\n"; return; }
    if (i1 == i2)              { cout << "  [!] Cannot simulate an alliance against itself.\n"; return; }
    engine.predictWar(alliances[i1], alliances[i2]);
}

void predictAllianceVsCountry() {
    if (allianceCount < 1 || countryCount < 1) {
        cout << "\n  [!] Need at least 1 alliance and 1 country.\n"; return;
    }
    string aName, cName;
    cout << "\n  --- Alliance vs Country ---\n";
    cout << "  Alliance name: "; cin.ignore(); getline(cin, aName);
    cout << "  Country name : "; getline(cin, cName);
    int ai = findAlliance(aName), ci = findCountry(cName);
    if (ai == -1 || ci == -1) { cout << "  [!] Alliance or country not found.\n"; return; }
    engine.predictWar(alliances[ai], countries[ci]);
}

// ── Main ──────────────────────────────────────────────────────
int main() {

    // Pre-loaded sample data
    countries[countryCount++] = Country("USA",     96.0, 25.5, 335,  "North America");
    countries[countryCount++] = Country("China",   90.0, 17.7, 1400, "Asia");
    countries[countryCount++] = Country("Russia",  85.0, 1.8,  144,  "Europe/Asia");
    countries[countryCount++] = Country("India",   72.0, 3.5,  1400, "Asia");
    countries[countryCount++] = Country("Germany", 60.0, 4.0,  83,   "Europe");
    cout << "  [*] 5 sample countries pre-loaded.\n";

    int choice;
    do {
        cout << "\n  ============================================\n";
        cout << "    Geopolitical War Outcome Predictor\n";
        cout << "  ============================================\n";
        cout << "   1.  Add Country\n";
        cout << "   2.  View All Countries\n";
        cout << "   3.  Update Country Stats\n";
        cout << "   4.  Compare Countries (Military)\n";
        cout << "   5.  Create Alliance\n";
        cout << "   6.  Add Country to Alliance\n";
        cout << "   7.  Remove Country from Alliance\n";
        cout << "   8.  View Alliances\n";
        cout << "   9.  Predict War (Country vs Country)\n";
        cout << "   10. Predict War (Alliance vs Alliance)\n";
        cout << "   11. Predict War (Alliance vs Country)\n";
        cout << "   12. View War History\n";
        cout << "   13. Clear War History\n";
        cout << "   0.  Exit\n";
        cout << "  ============================================\n";
        cout << "  Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:  addCountry();               break;
            case 2:  viewAllCountries();          break;
            case 3:  updateCountryStats();        break;
            case 4:  compareCountries();          break;
            case 5:  createAlliance();            break;
            case 6:  addCountryToAlliance();      break;
            case 7:  removeCountryFromAlliance(); break;
            case 8:  viewAlliances();             break;
            case 9:  predictCountryVsCountry();   break;
            case 10: predictAllianceVsAlliance(); break;
            case 11: predictAllianceVsCountry();  break;
            case 12: engine.showHistory();        break;
            case 13: engine.clearHistory();       break;
            case 0:  cout << "\n  Goodbye!\n";   break;
            default: cout << "  [!] Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
