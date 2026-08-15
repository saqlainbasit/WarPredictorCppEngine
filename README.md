# Geopolitical War Outcome Predictor

A terminal‑based C++ simulation that predicts war outcomes between countries using real‑world stats like military power, GDP, and population. Users can form alliances, compare nations, and run conflict simulations with calculated results. Built on core OOP principles with clean class design, operator overloading, and a full history log of past predictions.

---

## 📌 Project Features

- Add and manage countries with stats (military, GDP, population, region)
- Compare countries using overloaded operators
- Create alliances and manage their members
- Predict war outcomes:
  - Country vs Country
  - Alliance vs Alliance
  - Alliance vs Country
- War history log (view & clear)
- Fully menu‑driven terminal interface

---

## 🧠 OOP Concepts Used

- Classes & Objects
- Constructors / Copy Constructors
- Destructors
- Static Members
- Operator Overloading
- Friend Functions
- Function Overloading
- Aggregation (Alliance → Country pointers)

---

## 📂 File Structure

```
.
├── main.cpp
├── GeopoliticalWarPredictor.h
└── GeopoliticalWarPredictor.cpp
```

---

## Individual Roles

| Role |
|------|
| Country Data & Input Handling |
| OOP Structure & Operator Overloading |
| Alliance & Power Management |
| War Prediction & History |

---

## ▶️ How to Compile & Run

```bash
g++ main.cpp GeopoliticalWarPredictor.cpp -o predictor
./predictor
```

---

## ✅ Sample Preloaded Countries

- USA
- China
- Russia
- India
- Germany

---

## 📜 License

This project was created as part of a BSCS Semester‑2 OOP course project.  
Free to use for educational purposes.
