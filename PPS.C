#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for data
struct Member {
    int id;
    char name[50];
    int age;
    float weight;
};

struct Staff {
    int id;
    char name[50];
    char position[50];
};

// Function prototypes
void addMember();
void displayMembers();
void addStaff();
void displayStaff();
void clearDatabase();
void clearMemberById(int memberId);
void clearStaffById(int staffId);

int main() {
    int choice;

    do {
        printf("\nGym Management System\n");
        printf("1. Add Member\n");
        printf("2. Display Members\n");
        printf("3. Add Staff\n");
        printf("4. Display Staff\n");
        printf("5. Clear Database\n");
        printf("6. Clear Member by ID\n");
        printf("7. Clear Staff by ID\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                displayMembers();
                break;
            case 3:
                addStaff();
                break;
            case 4:
                displayStaff();
                break;
            case 5:
                clearDatabase();
                break;
            case 6:
                {
                    int memberId;
                    printf("Enter Member ID to clear: ");
                    scanf("%d", &memberId);
                    clearMemberById(memberId);
                }
                break;
            case 7:
                {
                    int staffId;
                    printf("Enter Staff ID to clear: ");
                    scanf("%d", &staffId);
                    clearStaffById(staffId);
                }
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 8);

    return 0;
}

void addMember() {
    FILE *memberFile;
    struct Member member;

    memberFile = fopen("members.txt", "a");
    if (memberFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Member ID: ");
    scanf("%d", &member.id);
    printf("Enter Member Name: ");
    scanf("%s", member.name);
    printf("Enter Member Age: ");
    scanf("%d", &member.age);
    printf("Enter Member Weight: ");
    scanf("%f", &member.weight);

    fprintf(memberFile, "%d %s %d %.2f\n", member.id, member.name, member.age, member.weight);

    fclose(memberFile);
}

void displayMembers() {
    FILE *memberFile;
    struct Member member;

    memberFile = fopen("members.txt", "r");
    if (memberFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nMembers:\n");
    printf("ID\tName\tAge\tWeight\n");

    while (fscanf(memberFile, "%d %s %d %f", &member.id, member.name, &member.age, &member.weight) != EOF) {
        printf("%d\t%s\t%d\t%.2f\n", member.id, member.name, member.age, member.weight);
    }

    fclose(memberFile);
}

void addStaff() {
    FILE *staffFile;
    struct Staff staff;

    staffFile = fopen("staff.txt", "a");
    if (staffFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter Staff ID: ");
    scanf("%d", &staff.id);
    printf("Enter Staff Name: ");
    scanf("%s", staff.name);
    printf("Enter Staff Position: ");
    scanf("%s", staff.position);

    fprintf(staffFile, "%d %s %s\n", staff.id, staff.name, staff.position);

    fclose(staffFile);
}

void displayStaff() {
    FILE *staffFile;
    struct Staff staff;

    staffFile = fopen("staff.txt", "r");
    if (staffFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nStaff:\n");
    printf("ID\tName\tPosition\n");

    while (fscanf(staffFile, "%d %s %s", &staff.id, staff.name, staff.position) != EOF) {
        printf("%d\t%s\t%s\n", staff.id, staff.name, staff.position);
    }

    fclose(staffFile);
}

void clearDatabase() {
    FILE *memberFile, *staffFile;

    memberFile = fopen("members.txt", "w");
    if (memberFile == NULL) {
        printf("Error opening members file.\n");
        return;
    }
    fclose(memberFile);

    staffFile = fopen("staff.txt", "w");
    if (staffFile == NULL) {
        printf("Error opening staff file.\n");
        return;
    }
    fclose(staffFile);

    printf("Database cleared successfully.\n");
}

void clearMemberById(int memberId) {
    FILE *memberFile, *tempFile;
    struct Member member;

    memberFile = fopen("members.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (memberFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    while (fscanf(memberFile, "%d %s %d %f", &member.id, member.name, &member.age, &member.weight) != EOF) {
        if (member.id != memberId) {
            fprintf(tempFile, "%d %s %d %.2f\n", member.id, member.name, member.age, member.weight);
        }
    }

    fclose(memberFile);
    fclose(tempFile);

    remove("members.txt");
    rename("temp.txt", "members.txt");

    printf("Member with ID %d cleared successfully.\n", memberId);
}

void clearStaffById(int staffId) {
    FILE *staffFile, *tempFile;
    struct Staff staff;

    staffFile = fopen("staff.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (staffFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    while (fscanf(staffFile, "%d %s %s", &staff.id, staff.name, staff.position) != EOF) {
        if (staff.id != staffId) {
            fprintf(tempFile, "%d %s %s\n", staff.id, staff.name, staff.position);
        }
    }

    fclose(staffFile);
    fclose(tempFile);

    remove("staff.txt");
    rename("temp.txt", "staff.txt");

    printf("Staff with ID %d cleared successfully.\n", staffId);
}
