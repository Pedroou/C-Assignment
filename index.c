#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Constants ---
#define MAX_PEOPLE 10           // Maximum number of people that can be registered
#define MAX_NAME_LENGTH 51      // Maximum length of a person's name (50 characters + null terminator)

// --- Global Variables ---
// These arrays store the data for each registered person.
// The index of each array corresponds to a specific person.
char names[MAX_PEOPLE][MAX_NAME_LENGTH]; // Array to store names of registered people
int ages[MAX_PEOPLE];                    // Array to store ages of registered people
float heights[MAX_PEOPLE];               // Array to store heights of registered people
int num_people = 0;                      // Current number of registered people, also acts as an index for the next empty slot

// Function to register a new person
void register_person() {
    // Check if the maximum registration limit has been reached
    if (num_people >= MAX_PEOPLE) {
        printf("Maximum number of registrations reached.\n");
        return; // Exit the function if no more space is available
    }

    // Prompt for and read the person's name
    printf("Enter name: ");
    fgets(names[num_people], MAX_NAME_LENGTH, stdin);
    // Remove trailing newline character captured by fgets.
    // strcspn finds the first occurrence of '\n' and returns its index.
    // Setting that index to '\0' effectively truncates the string there.
    names[num_people][strcspn(names[num_people], "\n")] = 0;

    // Prompt for and read the person's age
    printf("Enter age: ");
    scanf("%d", &ages[num_people]);

    // Prompt for and read the person's height
    printf("Enter height: ");
    scanf("%f", &heights[num_people]);

    // Clear the input buffer to remove any leftover characters (especially the newline after scanf).
    // This is crucial because if a newline is left in the buffer, subsequent calls to fgets
    // might read it as an empty string, leading to unexpected behavior.
    int c; // Use int to accommodate EOF
    while ((c = getchar()) != '\n' && c != EOF);

    num_people++; // Increment the count of registered people
    printf("Person registered successfully!\n");
}

// Function to list all registered people
void list_people() {
    // Check if there are any people registered
    if (num_people == 0) {
        printf("No people registered yet.\n");
        return; // Exit if the list is empty
    }

    printf("\n--- Registered People ---\n");
    // Loop through all registered people and print their details
    for (int i = 0; i < num_people; i++) {
        printf("Name: %s, Age: %d, Height: %.2f\n", names[i], ages[i], heights[i]);
    }
    printf("-------------------------\n");
}

// Function to search for a person by name
void search_person() {
    // Check if there are any people registered before attempting a search
    if (num_people == 0) {
        printf("No people registered yet. Cannot search.\n");
        return;
    }

    char search_name[MAX_NAME_LENGTH]; // Buffer to store the name to search for
    printf("Enter name to search: ");
    fgets(search_name, MAX_NAME_LENGTH, stdin);
    // Remove trailing newline character from search_name for accurate comparison
    search_name[strcspn(search_name, "\n")] = 0;

    // Loop through registered people to find a match
    for (int i = 0; i < num_people; i++) {
        // Compare the search name with the current person's name using strcmp.
        // strcmp returns 0 if the strings are identical.
        if (strcmp(search_name, names[i]) == 0) {
            printf("--- Person Found ---\n");
            printf("Name: %s, Age: %d, Height: %.2f\n", names[i], ages[i], heights[i]);
            printf("--------------------\n");
            return; // Exit function once the person is found
        }
    }

    // If the loop completes without returning, the person was not found
    printf("Person not found.\n");
}

// Main function - serves as the entry point of the program
int main() {
    int choice; // Variable to store the user's menu choice

    // Main loop to display the menu and process user input
    // The loop continues until the user chooses to exit (option 4)
    do {
        // Display menu options
        printf("\n--- Customer Registration System ---\n");
        printf("1. Register a new person\n");
        printf("2. List all registered people\n");
        printf("3. Search for a person by name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Read the user's menu choice

        // Clear the input buffer after scanf. This is important because scanf (especially for %d)
        // often leaves the newline character in the buffer. If not cleared, subsequent fgets calls
        // (e.g., in register_person or search_person) would immediately consume this newline,
        // interpreting it as an empty input.
        int c; // Use int to accommodate EOF
        while ((c = getchar()) != '\n' && c != EOF);

        // Process the user's choice using a switch statement
        switch (choice) {
            case 1:
                register_person(); // Call function to register a new person
                break;
            case 2:
                list_people();     // Call function to list all registered people
                break;
            case 3:
                search_person();   // Call function to search for a person
                break;
            case 4:
                printf("Exiting program. Goodbye!\n"); // Print exit message
                break;
            default:
                // Handle invalid menu choices
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4); // Continue loop as long as the user does not choose to exit

    return 0; // Indicate successful program termination to the operating system
}
