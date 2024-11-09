#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>

struct Method {
    char author[50];
    char discipline[50];
    char specialty[50];
    int pages;
    int fileSize;
    char format[10];
    int regnum;
};

struct Queue {
    struct Method book;
    struct Queue* next;
};

struct Queue* q = NULL;
struct Queue* p = NULL;

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void enqueue(struct Method book) {
    struct Queue* temp = (struct Queue*)malloc(sizeof(struct Queue));
    temp->book = book;
    temp->next = NULL;
    if (q == NULL && p == NULL) {
        q = p = temp;
    } else {
        p->next = temp;
        p = temp;
    }
    printf("\n");
}

void delqueue() {
    struct Queue* temp = q;
    if (q == NULL) {
        printf("\nQueue is empty\n");
        return;
    }

    int regnum;
    printf("Enter the registration number of the book to delete: ");
    scanf("%d", &regnum);
    clearInputBuffer();

    struct Queue* prev = NULL;
    int bookFound_d = 0; // Флаг, указывающий на наличие книги с указанным номером регистрации

    while (temp != NULL) {
        if (temp->book.regnum == regnum) {
            bookFound_d = 1;
            printf("Are you sure you want to delete the book with registration number %d? (Y/N): ", regnum);
            char choice_d;
            scanf("%c", &choice_d);
            clearInputBuffer();

            if (choice_d == 'Y' || choice_d == 'y') {
                if (prev == NULL) {
                    q = temp->next;
                } else {
                    prev->next = temp->next;
                }

                if (temp == p) {
                    p = prev;
                }

                printf("Book with registration number %d was removed from the queue\n", temp->book.regnum);
                free(temp);
            } else {
                printf("Deletion canceled.\n");
            }
            break; // Выход из цикла, если книга найдена и обработана
        }
        prev = temp;
        temp = temp->next;
    }

    if (!bookFound_d) {
        printf("Book with registration number %d not found.\n", regnum);
        delqueue(); // Вызов функции рекурсивно для повторного запроса номера регистрации
    }
}



void display() {
    struct Queue* temp = q;
    if (q == NULL) {
        printf("\nQueue is empty\n");
        printf("\n");
        printf("-----------------------------------");
        printf("\n");
        return;
    }
    while (temp != NULL) {
        printf("Author: %s\n", temp->book.author);
        printf("Discipline: %s\n", temp->book.discipline);
        printf("Specialty: %s\n", temp->book.specialty);
        printf("Pages: %d\n", temp->book.pages);
        printf("File Size: %d\n", temp->book.fileSize);
        printf("Format: %s\n", temp->book.format);
        printf("Registration Number: %d\n\n", temp->book.regnum);
        temp = temp->next;
    }
}

void modifyBook() {
    int regnum;
    printf("Enter the registration number of the book to modify: ");
    scanf("%d", &regnum);

    struct Queue* temp = q;
    int bookFound_m = 0;

    while (temp != NULL) {
        if (temp->book.regnum == regnum) {
            bookFound_m = 1;
            printf("Are you sure you want to modify the book with registration number %d? (Y/N): ", regnum);
            char choice_m;
            scanf(" %c", &choice_m); // Добавлен пробел перед %c для пропуска пробела или символа новой строки
            clearInputBuffer();

            if (choice_m == 'Y' || choice_m == 'y') {
                struct Method modifiedBook;
                printf("Enter modified author: ");
                do {
                    fgets(modifiedBook.author, sizeof(modifiedBook.author), stdin);
                    modifiedBook.author[strcspn(modifiedBook.author, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(modifiedBook.author[0])) {
                        printf("Invalid input for author. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter modified discipline: ");
                do {
                    fgets(modifiedBook.discipline, sizeof(modifiedBook.discipline), stdin);
                    modifiedBook.discipline[strcspn(modifiedBook.discipline, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(modifiedBook.discipline[0])) {
                        printf("Invalid input for discipline. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter modified specialty: ");
                do {
                    fgets(modifiedBook.specialty, sizeof(modifiedBook.specialty), stdin);
                    modifiedBook.specialty[strcspn(modifiedBook.specialty, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(modifiedBook.specialty[0])) {
                        printf("Invalid input for specialty. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter modified number of pages: ");
                do {
                    if (scanf("%d", &modifiedBook.pages) != 1 || modifiedBook.pages <= 0) {
                        printf("Invalid input for pages. Please enter a positive integer: ");
                        clearInputBuffer();
                    } else {
                        clearInputBuffer();
                        break;
                    }
                } while (1);

                printf("Enter modified file size: ");
                do {
                    if (scanf("%d", &modifiedBook.fileSize) != 1 || modifiedBook.fileSize <= 0) {
                        printf("Invalid input for file size. Please enter a positive integer: ");
                        clearInputBuffer();
                    } else {
                        clearInputBuffer();
                        break;
                    }
                } while (1);

                printf("Enter modified format: ");
                do {
                    fgets(modifiedBook.format, sizeof(modifiedBook.format), stdin);
                    modifiedBook.format[strcspn(modifiedBook.format, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(modifiedBook.format[0])) {
                        printf("Invalid input for format. Please enter a valid format: ");
                    } else {
                        break;
                    }
                } while (1);

                temp->book = modifiedBook;

                printf("Book with registration number %d has been modified.\n", regnum);
            } else {
                printf("Modification canceled.\n");
            }

            return;
        }

        temp = temp->next;
    }

    if (!bookFound_m) {
        printf("Book with registration number %d not found.\n", regnum);
        modifyBook(); // Вызов функции рекурсивно для повторного запроса номера регистрации
    }
}




void filterByDiscipline() {
    char discipline[50];
    printf("Enter the discipline to filter by: \n");
    fgets(discipline, sizeof(discipline), stdin);
    discipline[strcspn(discipline, "\n")] = '\0'; // Удаление символа новой строки

    printf("-----------------------------------");
    printf("\n");

    struct Queue* temp = q;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->book.discipline, discipline) == 0) {
            printf("Author: %s\n", temp->book.author);
            printf("Discipline: %s\n", temp->book.discipline);
            printf("Specialty: %s\n", temp->book.specialty);
            printf("Pages: %d\n", temp->book.pages);
            printf("File Size: %d\n", temp->book.fileSize);
            printf("Format: %s\n", temp->book.format);
            printf("Registration Number: %d\n\n", temp->book.regnum);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("No books found for the discipline: %s\n", discipline);
    }
}


void sortByRegNumber() {
    if (q == NULL) {
        printf("Queue is empty. No books to sort.\n");
        return;
    }

    int swapped;
    struct Queue* ptr1;
    struct Queue* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = q;

        while (ptr1->next != lptr) {
            if (ptr1->book.regnum > ptr1->next->book.regnum) {
                struct Method temp = ptr1->book;
                ptr1->book = ptr1->next->book;
                ptr1->next->book = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    printf("Books sorted by registration number in ascending order.\n");
}

void maxFileSizeBooks() {
    if (q == NULL) {
        printf("Queue is empty. No books found.\n");
        return;
    }

    int maxFileSize = 0;
    struct Queue* temp = q;

    while (temp != NULL) {
        if (temp->book.fileSize > maxFileSize) {
            maxFileSize = temp->book.fileSize;
        }
        temp = temp->next;
    }

    temp = q;
    printf("Books with maximum file size:\n");
    while (temp != NULL) {
        if (temp->book.fileSize == maxFileSize) {
            printf("Author: %s\n", temp->book.author);
            printf("Discipline: %s\n", temp->book.discipline);
            printf("Specialty: %s\n", temp->book.specialty);
            printf("Pages: %d\n", temp->book.pages);
            printf("File Size: %d\n", temp->book.fileSize);
            printf("Format: %s\n", temp->book.format);
            printf("Registration Number: %d\n\n", temp->book.regnum);
        }
        temp = temp->next;
    }
}

void saveToFile() {
    if (q == NULL) {
        printf("The queue is empty. No books to save.\n");
        return;
    }

    char filename[50];
    printf("Enter the filename to save the book data: ");
    scanf("%s", filename);

    // Проверка существования файла
    if (access(filename, F_OK) == 0) {
        printf("File %s already exists. Do you want to overwrite it? (Y/N): ", filename);
        char choice_s;
        clearInputBuffer();
        scanf("%c", &choice_s);
        if (toupper(choice_s) != 'Y') {
            printf("File not saved.\n");
            return;
        }
    }

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct Queue* temp = q;
    while (temp != NULL) {
        fprintf(file, "Author: %s\n", temp->book.author);
        fprintf(file, "Discipline: %s\n", temp->book.discipline);
        fprintf(file, "Specialty: %s\n", temp->book.specialty);
        fprintf(file, "Pages: %d\n", temp->book.pages);
        fprintf(file, "File Size: %d\n", temp->book.fileSize);
        fprintf(file, "Format: %s\n", temp->book.format);
        fprintf(file, "Registration Number: %d\n\n", temp->book.regnum);
        temp = temp->next;
    }

    fclose(file);
    printf("Book data saved to the file: %s\n", filename);
}


void filterByPagesRange() {
    if (q == NULL) {
        printf("The queue is empty. No books to filter.\n");
        return;
    }

    int minPages, maxPages;
    printf("Enter the minimum number of pages: ");
    scanf("%d", &minPages);
    printf("Enter the maximum number of pages: ");
    scanf("%d", &maxPages);

    struct Queue* temp = q;
    int found = 0;

    while (temp != NULL) {
        if (temp->book.pages >= minPages && temp->book.pages <= maxPages) {
            printf("Author: %s\n", temp->book.author);
            printf("Discipline: %s\n", temp->book.discipline);
            printf("Specialty: %s\n", temp->book.specialty);
            printf("Pages: %d\n", temp->book.pages);
            printf("File Size: %d\n", temp->book.fileSize);
            printf("Format: %s\n", temp->book.format);
            printf("Registration Number: %d\n\n", temp->book.regnum);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("No books found within the specified range of pages.\n");
    }
}

void readFromFile() {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    clearInputBuffer();

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    struct Method book;
    while (fscanf(file, "Author: %[^\n]\nDiscipline: %[^\n]\nSpecialty: %[^\n]\nPages: %d\nFile Size: %d\nFormat: %[^\n]\nRegistration Number: %d\n\n",
            book.author, book.discipline, book.specialty, &book.pages, &book.fileSize, book.format, &book.regnum) == 7) {
        enqueue(book);
    }

    fclose(file);
    printf("Data has been successfully read from the file.\n");
}



int main() {
    printf("Programm created by Eugene Kornei. Group -  AI-221 \n");
    printf("\n");
    printf("Subject area - digital library \n");
    printf("\n");
    printf("This programm allows you to add, delete, edit sort and filter books. \n ");
    printf("Save data to file and read data from file. \n ");
    printf("\n");
    int choice;

    while (1) {
        printf("\n*** Book Queue Menu ***\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Display Books\n");
        printf("4. Modify Book\n");
        printf("5. Filter Books by Discipline\n");
        printf("6. Sort Books by Registration Number\n");
        printf("7. Find Books with Maximum File Size\n");
        printf("8. Filter Books by Pages Range\n");
        printf("9. Save Books to File\n");
        printf("10. Read from file\n");
        printf("0. Exit\n");
        printf("\n");
        printf("-----------------------------------");
        printf("\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearInputBuffer();

        switch (choice) {
            case 1:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                struct Method book;
                printf("Enter author: ");
                do {
                    fgets(book.author, sizeof(book.author), stdin);
                    book.author[strcspn(book.author, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(book.author[0])) {
                        printf("Invalid input for author. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter discipline: ");
                do {
                    fgets(book.discipline, sizeof(book.discipline), stdin);
                    book.discipline[strcspn(book.discipline, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(book.discipline[0])) {
                        printf("Invalid input for discipline. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter specialty: ");
                do {
                    fgets(book.specialty, sizeof(book.specialty), stdin);
                    book.specialty[strcspn(book.specialty, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(book.specialty[0])) {
                        printf("Invalid input for specialty. Please enter a valid name: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter number of pages: ");
                do {
                    if (scanf("%d", &book.pages) != 1 || book.pages <= 0) {
                        printf("Invalid input for pages. Please enter a positive integer: ");
                        clearInputBuffer();
                    } else {
                        clearInputBuffer();
                        break;
                    }
                } while (1);

                printf("Enter file size: ");
                do {
                    if (scanf("%d", &book.fileSize) != 1 || book.fileSize <= 0) {
                        printf("Invalid input for file size. Please enter a positive integer: ");
                        clearInputBuffer();
                    } else {
                        clearInputBuffer();
                        break;
                    }
                } while (1);

                printf("Enter format: ");
                do {
                    fgets(book.format, sizeof(book.format), stdin);
                    book.format[strcspn(book.format, "\n")] = '\0'; // Удаление символа новой строки
                    if (isdigit(book.format[0])) {
                        printf("Invalid input for format. Please enter a valid format: ");
                    } else {
                        break;
                    }
                } while (1);

                printf("Enter registration number: ");
                do {
                    if (scanf("%d", &book.regnum) != 1 || book.regnum <= 0) {
                        printf("Invalid input for registration number. Please enter a positive integer: ");
                        clearInputBuffer();
                    } else {
                        clearInputBuffer();
                        break;
                    }
                } while (1);

                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                printf("Book added successfully.\n");
                printf("-----------------------------------");

                enqueue(book);
                break;
            case 2:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                delqueue();
                break;
            case 3:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                display();
                break;
            case 4:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                modifyBook();
                break;
            case 5:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                filterByDiscipline();
                break;
            case 6:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                sortByRegNumber();
                break;
            case 7:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                maxFileSizeBooks();
                break;
            case 8:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                filterByPagesRange();
                break;
            case 9:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                saveToFile();
                break;
            case 10:
                printf("\n");
                printf("-----------------------------------");
                printf("\n");
                readFromFile();
                break;
            case 0:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
