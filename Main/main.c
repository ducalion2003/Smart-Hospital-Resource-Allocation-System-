#include <stdio.h>

void displayMenu();

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


void displayMenu() {
    printf("\n=== SMART HOSPITAL MANAGEMENT SYSTEM ===\n");
    printf("1. Register New Patient\n");
    printf("2. View Patient Priority List\n");
    printf("3. Display Hospital Reports & Analytics\n");
    printf("4. Save & Exit\n");
    printf("Enter your choice(1-4): ");
}