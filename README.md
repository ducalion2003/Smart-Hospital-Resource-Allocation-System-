# 🏥 Smart Hospital & Resource Allocation System

![Language](https://img.shields.io/badge/Language-C-blue?logo=c)
![Status](https://img.shields.io/badge/Status-In%20Progress-yellow)
![License](https://img.shields.io/badge/Course-CSC%201012-lightgrey)

A modular, menu-driven **C program** that simulates patient intake, bed allocation, emergency triage sorting, and medical billing for a hospital.

> 🎓 **Course:** CSC 1012 – Introduction to Computer Programming
> 🏛️ **Institution:** University of Sri Jayewardenepura – Faculty of Applied Sciences
> 📋 **Type:** Individual Assignment

---

## 📖 Overview

The system manages:

- 🔍 Doctor specialty and hospital ward lookup data
- 🛏️ Bed occupancy tracking (2D array)
- 📝 Patient registration (name, age, triage level, specialty, ward admission)
- 💰 Billing calculations (consultation fee, emergency surcharge, ward cost, age-based discount)
- ⏱️ Estimated waiting time per specialty queue
- 🚨 Priority-based patient listing (sorted by urgency, then registration order)
- 📊 Summary reports and analytics
- 💾 Persistent file storage for bed status and patient records

---

## 🧩 Data Structures

Implemented using **parallel arrays** (structs not used).

**📋 Lookup tables**
- Doctor specialties: ID, name, base fee, consultation time, daily cap
- Hospital wards: ID, name, daily bed rate, total bed capacity
- Bed occupancy: `int bedOccupancy[4][20]` (0 = available, 1 = occupied)

**🧍 Patient records** (parallel arrays indexed by patient index `i`)
- Name, age, triage level, specialty ID, ward admission flag, ward ID, days admitted, billing figures

---

## ⚙️ Features / Functions

| Function | Purpose |
|---|---|
| 📝 `registerPatient()` | Collects patient details and specialty/ward selection |
| ⏱️ `calculateWaitTime()` | Queue count × average consultation time |
| 🚨 `calculateSurcharge()` | Emergency surcharge by triage level |
| 🛏️ `calculateWardCost()` | Days admitted × ward daily rate |
| 🎫 `calculateDiscount()` | 15% age-based subsidy (age < 5 or > 65) |
| 🧾 `generateBill()` | Prints formatted bill |
| 🔀 `sortPatientsByPriority()` | Sorts by urgency level, then registration order |
| 📊 `generateReports()` | Patient counts by urgency, revenue/discount totals, bed occupancy %, highest-paying patient |
| 💾 `saveBedStatus()` / `loadBedStatus()` | Persist bed occupancy to `beds_status.txt` |
| 📁 `logPatientRecord()` | Append billing record to `patient_records.txt` |

---

## 🧮 Billing Formulas

| Item | Formula |
|---|---|
| ⏱️ Wait Time (min) | Queue Count × Avg Time per Patient |
| 🚨 Emergency Surcharge | 0% / 20% / 50% of Base Fee (Level 1 / 2 / 3) |
| 🛏️ Ward Stay Cost | Days Admitted × Ward Daily Rate |
| 💵 Gross Total | Base Fee + Surcharge + Ward Cost |
| 🎫 Age Subsidy Discount | 15% of Gross Total if Age < 5 or Age > 65 |
| ✅ Final Payable | Gross Total − Discount |

---

## 💾 File Handling

| File | Purpose |
|---|---|
| 🛏️ `beds_status.txt` | Saves/loads bed occupancy across runs |
| 📁 `patient_records.txt` | Appends permanent patient billing logs |

---

## 📂 Project Structure

```
.
├── src/
│   ├── main.c
│   └── ...          # additional .c/.h files
├── beds_status.txt
├── patient_records.txt
├── Project_Report.pdf
└── README.md
```

---

## 🚀 How to Compile & Run

```bash
gcc -o hospital_system src/*.c
./hospital_system
```

---

## 🖥️ Sample Output

```
====================================================
 SMART HOSPITAL ADMISSION & BILL
----------------------------------------------------------------------------------------
Patient ID : PAT-1001
Patient Name : Mr. Kamal Perera
Age : 70 Years (15% Subsidy Eligible)
Specialty : Cardiology
Assigned Ward : ICU (Bed #01)
Urgency Level : Level 3 (Critical)
----------------------------------------------------------------------------------------
Base Consultation Fee : LKR 4,500.00
Emergency Surcharge : LKR 2,250.00 (50%)
Ward Stay Cost (2 Days) : LKR 50,000.00
----------------------------------------------------------------------------------------
Gross Total Bill : LKR 56,750.00
Age Subsidy Discount : LKR -8,512.50 (15%)
----------------------------------------------------------------------------------------
Final Payable Amount : LKR 48,237.50
Estimated Waiting Time : 0.00 mins (Immediate Attention)
====================================================
```

---

## 📝 Assumptions

- Bed numbers within a ward are assigned to the first available slot in `bedOccupancy`.
- Patient IDs are generated sequentially (e.g., `PAT-1001`, `PAT-1002`, ...).
- Queue counts reset only when the program restarts (not persisted).

---

## 👤 Author

**Chamod Madushan** — BSc (General) Degree, First Year
