#include <stdio.h>
#include <string.h>

#define maxPatients 100
#define numberOfSpecialties 4
#define numberOfWards 4

// Doctor Specialties Data Table
const char SpecialityNames[numberOfSpecialties][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};
const double BaseConsultationFee[numberOfSpecialties] = {1500.00, 2500.00, 4500.00, 5000.00};
const int ConsultationTime[numberOfSpecialties] = {15, 20, 30, 30};
const int DailyPatientCap[numberOfSpecialties] = {30, 20, 12, 10};

// Hospital Wards Data Table
const char wardNames[numberOfWards][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU (Intensive Care Unit)"
};
const double wardRates[numberOfWards] = {3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacities[numberOfWards] = {20, 10, 10, 5};

// 2D Bed Occupancy (0 = Available, 1 = Occupied)
int bedOccupancy[numberOfWards][20] = {0};

// Arrays Patient Records
int patientID[maxPatients];
char patientName[maxPatients][50];
int patientAge[maxPatients];
int urgencyLevel[maxPatients];
int specialtyID[maxPatients];
int isAdmitted[maxPatients];
int wardID[maxPatients];
int daysAdmitted[maxPatients];
int allocatedBedNumber[maxPatients];
double finalBills[maxPatients];

int patientCount = 0;
int queueCounts[numberOfSpecialties] = {0};

// Function Prototypes
void loadBedStatus();
void saveBedStatus();
void savePatientRecordToFile(int index, double finalBill);
void displayLookupData();
void displayBedMatrix();
void displayMenu();
void registerPatient();
void displayTriageList();
void generateAnalyticsReport();

// Main Function
int main() {
    loadBedStatus();
    int choice;
    
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();
        
        switch (choice) {
            case 1:
                displayLookupData();
                displayBedMatrix();
                break;
            case 2:
                registerPatient();
                break;
            case 3:
                displayTriageList();
                break;
            case 4:
                generateAnalyticsReport();
                break;
            case 5:
                saveBedStatus();
                printf("\nBed status saved to file. Exiting System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Loads bed occupancy status file
void loadBedStatus() {
    FILE *fp = fopen("beds_status.txt", "r");
    if (!fp) return; 
    for (int i = 0; i < numberOfWards; i++) {
        for (int j = 0; j < wardCapacities[i]; j++) {
            fscanf(fp, "%d", &bedOccupancy[i][j]);
        }
    }
    fclose(fp);
}

// Saves bed occupancy status file
void saveBedStatus() {
    FILE *fp = fopen("beds_status.txt", "w");
    if (!fp) return;
    for (int i = 0; i < numberOfWards; i++) {
        for (int j = 0; j < wardCapacities[i]; j++) {
            fprintf(fp, "%d ", bedOccupancy[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

// Saves patient records into permanent log file
void savePatientRecordToFile(int index, double finalBill) {
    FILE *fp = fopen("patient_records.txt", "a");
    if (!fp) return;
    fprintf(fp, "PAT-%d | %s | Age: %d | Urgency: %d | Bill: LKR %.2f\n",
            patientID[index], patientName[index], patientAge[index],
            urgencyLevel[index], finalBill);
    fclose(fp);
}

// Main Menu
void displayMenu() {
    printf("\n=== SMART HOSPITAL MANAGEMENT SYSTEM ===\n");
    printf("1. View Lookup Data & Bed Availability\n");
    printf("2. Register New Patient\n");
    printf("3. View Patient Priority List\n");
    printf("4. Display Hospital Reports & Analytics\n");
    printf("5. Save & Exit\n");
    printf("Enter your choice(1-5): ");
}

// Ward & Specialty Lookup Tables
void displayLookupData() {
    printf("\n---------------- DOCTOR SPECIALTIES ----------------\n");
    printf("ID | Specialty Name            | Base Fee   | Time/Pt\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < numberOfSpecialties; i++) {
        printf("%-2d | %-24s | LKR %7.2f | %2d mins\n",
               i + 1, SpecialityNames[i], BaseConsultationFee[i], ConsultationTime[i]);
    }

    printf("\n------------------- HOSPITAL WARDS -------------------\n");
    printf("ID | Ward Name                 | Daily Rate | Capacity\n");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < numberOfWards; i++) {
        printf("%-2d | %-24s | LKR %7.2f | %d beds\n",
               i + 1, wardNames[i], wardRates[i], wardCapacities[i]);
    }
}

// Display Bed Status
void displayBedMatrix() {
    printf("\n---------------- BED OCCUPANCY STATUS ----------------\n");
    for (int w = 0; w < numberOfWards; w++) {
        printf("%-25s: ", wardNames[w]);
        for (int b = 0; b < wardCapacities[w]; b++) {
            printf("[%s] ", bedOccupancy[w][b] == 1 ? "X" : "O");
        }
        printf("\n");
    }
    printf("(O = Available, X = Occupied)\n");
}

// Patient Registration 
void registerPatient() {
    if (patientCount >= maxPatients) {
        printf("\nError: Patient database is full!\n");
        return;
    }

    int idNumber = patientCount;
    patientID[idNumber] = 1001 + idNumber;

    printf("\n--- New Patient Registration ---\n");
    printf("Enter Patient Name: ");
    fgets(patientName[idNumber], sizeof(patientName[idNumber]), stdin);
    patientName[idNumber][strcspn(patientName[idNumber], "\n")] = 0;

    printf("Enter Patient Age: ");
    scanf("%d", &patientAge[idNumber]);

    do {
        printf("Enter Triage/Urgency Level (1=Normal, 2=Urgent, 3=Critical): ");
        scanf("%d", &urgencyLevel[idNumber]);
    } while (urgencyLevel[idNumber] < 1 || urgencyLevel[idNumber] > 3);

    displayLookupData();

    do {
        printf("\nSelect Specialty ID (1-4): ");
        scanf("%d", &specialtyID[idNumber]);
    } while (specialtyID[idNumber] < 1 || specialtyID[idNumber] > numberOfSpecialties);

    printf("Is Admitted to Ward? (1=Yes, 0=No): ");
    scanf("%d", &isAdmitted[idNumber]);

    allocatedBedNumber[idNumber] = -1;
    if (isAdmitted[idNumber] == 1) {
        do {
            printf("Select Ward ID (1-4): ");
            scanf("%d", &wardID[idNumber]);
        } while (wardID[idNumber] < 1 || wardID[idNumber] > numberOfWards);

        printf("Enter Days Admitted: ");
        scanf("%d", &daysAdmitted[idNumber]);

        int wIdx = wardID[idNumber] - 1;
        int bedFound = 0;
        
        // Find and assign first available bed in ward
        for (int b = 0; b < wardCapacities[wIdx]; b++) {
            if (bedOccupancy[wIdx][b] == 0) {
                bedOccupancy[wIdx][b] = 1; // Mark bed occupied
                allocatedBedNumber[idNumber] = b + 1;
                bedFound = 1;
                break;
            }
        }

        if (!bedFound) {
            printf("Warning: Selected ward is full! Patient admitted without reserved bed.\n");
        }
    } else {
        wardID[idNumber] = 0;
        daysAdmitted[idNumber] = 0;
    }

    // Bill
    int sIdx = specialtyID[idNumber] - 1;
    double waitTime = (urgencyLevel[idNumber] == 3) ? 0.0 : (double)(queueCounts[sIdx] * ConsultationTime[sIdx]);
    queueCounts[sIdx]++;

    double baseFee = BaseConsultationFee[sIdx];
    double surcharge = 0.0;
    if (urgencyLevel[idNumber] == 2) surcharge = baseFee * 0.20;
    else if (urgencyLevel[idNumber] == 3) surcharge = baseFee * 0.50;

    double wardCost = 0.0;
    if (isAdmitted[idNumber] == 1 && wardID[idNumber] > 0) {
        wardCost = daysAdmitted[idNumber] * wardRates[wardID[idNumber] - 1];
    }

    double grossTotal = baseFee + surcharge + wardCost;
    double discount = 0.0;
    if (patientAge[idNumber] < 5 || patientAge[idNumber] > 65) {
        discount = grossTotal * 0.15;
    }
    double finalAmount = grossTotal - discount;
    finalBills[idNumber] = finalAmount;

    // Billing Receipt
    printf("\n==================================================\n");
    printf("         SMART HOSPITAL ADMISSION & BILL          \n");
    printf("==================================================\n");
    printf("Patient ID             : PAT-%d\n", patientID[idNumber]);
    printf("Patient Name           : %s\n", patientName[idNumber]);
    printf("Age                    : %d Years %s\n", patientAge[idNumber],
           (patientAge[idNumber] < 5 || patientAge[idNumber] > 65) ? "(15% Subsidy Eligible)" : "");
    printf("Specialty              : %s\n", SpecialityNames[sIdx]);
    
    if (isAdmitted[idNumber] == 1 && allocatedBedNumber[idNumber] != -1) {
        printf("Assigned Ward          : %s (Bed #%02d)\n", wardNames[wardID[idNumber] - 1], allocatedBedNumber[idNumber]);
    } else if (isAdmitted[idNumber] == 1) {
        printf("Assigned Ward          : %s (No Bed Free)\n", wardNames[wardID[idNumber] - 1]);
    } else {
        printf("Assigned Ward          : Outpatient (OPD)\n");
    }

    printf("Urgency Level          : Level %d (%s)\n", urgencyLevel[idNumber],
           urgencyLevel[idNumber] == 1 ? "Normal" : (urgencyLevel[idNumber] == 2 ? "Urgent" : "Critical"));
    printf("Base Consultation Fee  : LKR %10.2f\n", baseFee);
    printf("Emergency Surcharge    : LKR %10.2f (%s)\n", surcharge,
           urgencyLevel[idNumber] == 1 ? "0%" : (urgencyLevel[idNumber] == 2 ? "20%" : "50%"));
    printf("Ward Stay Cost (%d Days): LKR %10.2f\n", daysAdmitted[idNumber], wardCost);
    printf("Gross Total Bill       : LKR %10.2f\n", grossTotal);
    printf("Age Subsidy Discount   : LKR %10.2f (%s)\n", -discount,
           (patientAge[idNumber] < 5 || patientAge[idNumber] > 65) ? "15%" : "0%");
    printf("--------------------------------------------------\n");
    printf("Final Payable Amount   : LKR %10.2f\n", finalAmount);
    printf("Estimated Waiting Time : %.2f mins %s\n", waitTime,
           urgencyLevel[idNumber] == 3 ? "(Immediate Attention)" : "");
    printf("==================================================\n");

    savePatientRecordToFile(idNumber, finalAmount);
    saveBedStatus();                                

    patientCount++;
}

// Emergency Priority Queue
void displayTriageList() {
    if (patientCount == 0) {
        printf("\nNo patients registered in system yet.\n");
        return;
    }

    int order[maxPatients];
    for (int i = 0; i < patientCount; i++) {
        order[i] = i;
    }

    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (urgencyLevel[order[j]] < urgencyLevel[order[j + 1]]) {
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    printf("\n===============================================================\n");
    printf("                  EMERGENCY TRIAGE SORTED QUEUE                 \n");
    printf("===============================================================\n");
    printf("Queue Pos | Patient ID | Name               | Urgency Level\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < patientCount; i++) {
        int idx = order[i];
        const char *urgencyStr = (urgencyLevel[idx] == 3) ? "Level 3 (Critical)" :
                                 (urgencyLevel[idx] == 2) ? "Level 2 (Urgent)"   : "Level 1 (Normal)";
        printf("%-9d | PAT-%-6d | %-18s | %s\n", i + 1, patientID[idx], patientName[idx], urgencyStr);
    }
    printf("===============================================================\n");
}

// Performance & Analytics Report
void generateAnalyticsReport() {
    if (patientCount == 0) {
        printf("\nNo data available to generate analytics.\n");
        return;
    }

    int n1 = 0, n2 = 0, n3 = 0;
    double totalRevenue = 0.0, totalDiscounts = 0.0;
    int highestIdx = 0;

    for (int i = 0; i < patientCount; i++) {
        if (urgencyLevel[i] == 1) n1++;
        else if (urgencyLevel[i] == 2) n2++;
        else if (urgencyLevel[i] == 3) n3++;

        int sIdx = specialtyID[i] - 1;
        double baseFee = BaseConsultationFee[sIdx];
        double surcharge = (urgencyLevel[i] == 2) ? baseFee * 0.20 : ((urgencyLevel[i] == 3) ? baseFee * 0.50 : 0.0);
        double wardCost = (isAdmitted[i] == 1 && wardID[i] > 0) ? daysAdmitted[i] * wardRates[wardID[i] - 1] : 0.0;
        double gross = baseFee + surcharge + wardCost;
        double disc = (patientAge[i] < 5 || patientAge[i] > 65) ? gross * 0.15 : 0.0;

        totalRevenue += finalBills[i];
        totalDiscounts += disc;

        if (finalBills[i] > finalBills[highestIdx]) {
            highestIdx = i;
        }
    }

    printf("\n======================================================\n");
    printf("            PERFORMANCE REPORTS & ANALYTICS            \n");
    printf("======================================================\n");
    printf("Total Patients Registered : %d\n", patientCount);
    printf("  - Level 1 (Normal)     : %d\n", n1);
    printf("  - Level 2 (Urgent)     : %d\n", n2);
    printf("  - Level 3 (Critical)   : %d\n", n3);
    printf("------------------------------------------------------\n");
    printf("Total Revenue Earned      : LKR %.2f\n", totalRevenue);
    printf("Total Discounts Granted   : LKR %.2f\n", totalDiscounts);
    printf("------------------------------------------------------\n");
    printf("Bed Occupancy per Ward:\n");
    for (int w = 0; w < numberOfWards; w++) {
        int occupiedCount = 0;
        for (int b = 0; b < wardCapacities[w]; b++) {
            if (bedOccupancy[w][b] == 1) occupiedCount++;
        }
        double percentage = ((double)occupiedCount / wardCapacities[w]) * 100.0;
        printf("  - %-25s: %d/%d occupied (%.1f%%)\n", wardNames[w], occupiedCount, wardCapacities[w], percentage);
    }
    printf("------------------------------------------------------\n");
    printf("Highest-Paying Patient    : %s (PAT-%d)\n", patientName[highestIdx], patientID[highestIdx]);
    printf("Highest Bill Amount       : LKR %.2f\n", finalBills[highestIdx]);
    printf("======================================================\n");
}