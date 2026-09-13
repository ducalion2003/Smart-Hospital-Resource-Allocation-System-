#include <stdio.h>

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


//Hospital Wards Data Table
const char wardNames[numberOfWards][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU (Intensive Care Unit)"
};
const double wardRates[numberOfWards] = {3000.00, 6000.00, 12000.00, 25000.00};
const int wardCapacities[numberOfWards] = {20, 10, 10, 5};


//2D Bed Occupancy (0 = Available, 1 = Occupied)
int bedOccupancy[numberOfWards][20] = {0};



void displayMenu();


// Main Function
int main() {
    int choice;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\n[Patient Registration Selected]\n");
                break;
            case 2:
                printf("\n[Priority Sorting Selected]\n");
                break;
            case 3:
                printf("\n[Analytics Selected]\n");
                break;
            case 4:
                printf("\nExiting System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid option! Please try again.\n");
        }
    } while (choice != 4);


    return 0;
}

// Function to display the main menu
void displayMenu() {
    printf("\n=== SMART HOSPITAL MANAGEMENT SYSTEM ===\n");
    printf("1. Register New Patient\n");
    printf("2. View Patient Priority List\n");
    printf("3. Display Hospital Reports & Analytics\n");
    printf("4. Save & Exit\n");
    printf("Enter your choice(1-4): ");
}
