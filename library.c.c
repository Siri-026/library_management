#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_PATRONS 50
#define MAX_TRANSACTIONS 500
// Struct to represent a book in the library
struct Book {
    char title[100];
    char author[50];
    char isbn[20];
    int quantity_available;
};
// Struct to represent a patron in the library
struct Patron {
    char name[100];
    int id;
    int num_books_borrowed;
};
// Struct to represent a transaction (book borrowing)
struct Transaction {
    int patron_id;
    char book_isbn[20];
    char borrowing_date[20];
};

// Arrays to store books, patrons, and transactions
struct Book books[MAX_BOOKS];
struct Patron patrons[MAX_PATRONS];
struct Transaction transactions[MAX_TRANSACTIONS];

// Variables to keep track of the number of books, patrons, and transactions
int num_books = 0;
int num_patrons = 0;
int num_transactions = 0;

// Function prototypes
void addBook();
void removeBook();
void addPatron();
void removePatron();
void borrowBook();
void returnBook();
void displayBooks();
void displayPatrons();
void displayBooksByPatron();

int main() {
    int choice;

    do {
        // Display menu
        printf("\n===== Library Management System Menu =====\n");
        printf("1. Add a new book\n");
        printf("2. Remove a book\n");
        printf("3. Add a new patron\n");
        printf("4. Remove a patron\n");
        printf("5. Borrow a book\n");
        printf("6. Return a book\n");
        printf("7. Display all books\n");
        printf("8. Display all patrons\n");
        printf("9. Display books borrowed by a patron\n");
        printf("0. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                removeBook();
                break;
            case 3:
                addPatron();
                break;
            case 4:
                removePatron();
                break;
            case 5:
                borrowBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                displayBooks();
                break;
            case 8:
                displayPatrons();
                break;
            case 9:
                displayBooksByPatron();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 0 and 9.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
// Function to add a new book to the library
void addBook() {
    if (num_books >= MAX_BOOKS) {
        printf("Cannot add more books. Library capacity reached.\n");
        return;
    }

    printf("Enter book title: ");
    scanf(" %[^\n]s", books[num_books].title);
    printf("Enter book author: ");
    scanf(" %[^\n]s", books[num_books].author);
    printf("Enter book ISBN: ");
    scanf(" %s", books[num_books].isbn);
    printf("Enter quantity available: ");
    scanf("%d", &books[num_books].quantity_available);

    num_books++;
    printf("Book added successfully.\n");
}
// Function to remove a book from the library
void removeBook() {
    char isbn[20];
    int i, found = 0;

    if (num_books == 0) {
        printf("No books available to remove.\n");
        return;
    }

    printf("Enter ISBN of the book to remove: ");
    scanf("%s", isbn);
     // Search for the book by ISBN
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            // Shift books array to remove the book at index i
            for (int j = i; j < num_books - 1; j++) {
                books[j] = books[j + 1];
            }
            num_books--;
            printf("Book removed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book not found.\n");
    }
}
// Function to add a new patron to the library system
void addPatron() {
    if (num_patrons >= MAX_PATRONS) {
        printf("Cannot add more patrons. Patron capacity reached.\n");
        return;
    }

    printf("Enter patron name: ");
    scanf(" %[^\n]s", patrons[num_patrons].name);
    patrons[num_patrons].id = num_patrons + 1; // Assigning ID sequentially
    patrons[num_patrons].num_books_borrowed = 0;

    num_patrons++;
    printf("Patron added successfully. Patron ID is %d.\n", patrons[num_patrons - 1].id);
}
// Function to remove a patron from the library system
void removePatron() {
    int patron_id, i, found = 0;

    if (num_patrons == 0) {
        printf("No patrons available to remove.\n");
        return;
    }

    printf("Enter ID of the patron to remove: ");
    scanf("%d", &patron_id);
    // Search for the patron by ID
    for (i = 0; i < num_patrons; i++) {
        if (patrons[i].id == patron_id) {
            // Shift patrons array to remove the patron at index i
            for (int j = i; j < num_patrons - 1; j++) {
                patrons[j] = patrons[j + 1];
            }
            num_patrons--;
            printf("Patron removed successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patron not found.\n");
    }
}
// Function to borrow a book from the library
void borrowBook() {
    int patron_id, found_patron = 0;
    char isbn[20];
    int i, found_book = 0;

    if (num_patrons == 0 || num_books == 0) {
        printf("No patrons or books available for borrowing.\n");
        return;
    }

    printf("Enter patron ID: ");
    scanf("%d", &patron_id);
    // Search for the patron by ID
    for (i = 0; i < num_patrons; i++) {
        if (patrons[i].id == patron_id) {
            found_patron = 1;
            break;
        }
    }

    if (!found_patron) {
        printf("Patron not found.\n");
        return;
    }

    printf("Enter ISBN of the book to borrow: ");
    scanf("%s", isbn);
    // Search for the book by ISBN
    for (i = 0; i < num_books; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            found_book = 1;
            if (books[i].quantity_available > 0) {
                // Add transaction
                strcpy(transactions[num_transactions].book_isbn, isbn);
                transactions[num_transactions].patron_id = patron_id;
                // Assuming borrowing date for simplicity
                strcpy(transactions[num_transactions].borrowing_date, "2024-06-16");
                num_transactions++;

                // Update book quantity and patron's book count
                books[i].quantity_available--;
                patrons[i].num_books_borrowed++;

                printf("Book borrowed successfully.\n");
            } else {
                printf("Book not available for borrowing.\n");
            }
            break;
        }
    }

    if (!found_book) {
        printf("Book not found.\n");
    }
}
// Function to return a borrowed book to the library
void returnBook() {
    int patron_id, found_patron = 0;
    char isbn[20];
    int i, found_transaction = 0;

    if (num_patrons == 0 || num_books == 0 || num_transactions == 0) {
        printf("No patrons, books, or transactions available for returning.\n");
        return;
    }

    printf("Enter patron ID: ");
    scanf("%d", &patron_id);
    // Search for the patron by ID
    for (i = 0; i < num_patrons; i++) {
        if (patrons[i].id == patron_id) {
            found_patron = 1;
            break;
        }
    }

    if (!found_patron) {
        printf("Patron not found.\n");
        return;
    }

    printf("Enter ISBN of the book to return: ");
    scanf("%s", isbn);
    // Search for the transaction by patron ID and book ISBN
    for (i = 0; i < num_transactions; i++) {
        if (transactions[i].patron_id == patron_id && strcmp(transactions[i].book_isbn, isbn) == 0) {
            found_transaction = 1;

            // Remove transaction (shift transactions array)
            for (int j = i; j < num_transactions - 1; j++) {
                transactions[j] = transactions[j + 1];
            }
            num_transactions--;

            // Update book quantity and patron's book count
            for (int k = 0; k < num_books; k++) {
                if (strcmp(books[k].isbn, isbn) == 0) {
                    books[k].quantity_available++;
                    break;
                }
            }
            patrons[i].num_books_borrowed--;

            printf("Book returned successfully.\n");
            break;
        }
    }

    if (!found_transaction) {
        printf("No such transaction found.\n");
    }
}
// Function to display all books in the library
void displayBooks() {
    if (num_books == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\n===== List of Books =====\n");
    for (int i = 0; i < num_books; i++) {
        printf("Title: %s\n", books[i].title);
        printf("Author: %s\n", books[i].author);
        printf("ISBN: %s\n", books[i].isbn);
        printf("Quantity available: %d\n", books[i].quantity_available);
        printf("-------------------------\n");
    }
}
// Function to display all patrons in the library system
void displayPatrons() {
    if (num_patrons == 0) {
        printf("No patrons available in the library system.\n");
        return;
    }

    printf("\n===== List of Patrons =====\n");
    for (int i = 0; i < num_patrons; i++) {
        printf("Name: %s\n", patrons[i].name);
        printf("ID: %d\n", patrons[i].id);
        printf("Number of books borrowed: %d\n", patrons[i].num_books_borrowed);
        printf("-------------------------\n");
    }
}
// Function to display books borrowed by a specific patron
void displayBooksByPatron() {
    int patron_id, i, found_patron = 0;

    if (num_patrons == 0 || num_transactions == 0) {
        printf("No patrons or transactions available.\n");
        return;
    }

    printf("Enter patron ID: ");
    scanf("%d", &patron_id);
    // Search for the patron by ID
    for (i = 0; i < num_patrons; i++) {
        if (patrons[i].id == patron_id) {
            found_patron = 1;
            break;
        }
    }

    if (!found_patron) {
        printf("Patron not found.\n");
        return;
    }

    printf("\n===== Books Borrowed by Patron %d =====\n", patron_id);
    // List all transactions of the specified patron
    for (i = 0; i < num_transactions; i++) {
        if (transactions[i].patron_id == patron_id) {
            // Find the book details for each transaction
            for (int j = 0; j < num_books; j++) {
                if (strcmp(transactions[i].book_isbn, books[j].isbn) == 0) {
                    printf("Title: %s\n", books[j].title);
                    printf("Author: %s\n", books[j].author);
                    printf("ISBN: %s\n", books[j].isbn);
                    printf("Borrowing Date: %s\n", transactions[i].borrowing_date);
                    printf("-------------------------\n");
                    break;
                }
            }
        }
    }
}



