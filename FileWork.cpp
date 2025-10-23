#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxEmployees 1000
#define maxStringLength 100
#define maxLineLength 500

struct Employee {
    char department[maxStringLength];
    char lastName[maxStringLength];
    char firstName[maxStringLength];
    char middleName[maxStringLength];
    char phoneNumber[maxStringLength];
};

struct PhoneDirectory {
    struct Employee employees[maxEmployees];
    int employeeCount;
    char inputFileName[maxStringLength];
};

void initializeDirectory(struct PhoneDirectory* phoneDirectory, const char* fileName) {
    phoneDirectory->employeeCount = 0;
    strcpy(phoneDirectory->inputFileName, fileName);
}

int loadData(struct PhoneDirectory* phoneDirectory) {
    // Функция открывает файл по пути, указанному в phoneDirectory->inputFileName
    FILE* inputFile = fopen(phoneDirectory->inputFileName, "r");
    
    if (inputFile == NULL) {
        fprintf(stderr, "Ошибка: невозможно открыть файл %s\n", phoneDirectory->inputFileName);
        return 0;
    }

    char line[maxLineLength];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Обработка каждой строки файла
        char department[maxStringLength];
        char lastName[maxStringLength];
        char firstName[maxStringLength];
        char middleName[maxStringLength];
        char phoneNumber[maxStringLength];
        
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%s", 
                   department, lastName, firstName, middleName, phoneNumber) == 5) {
            
            if (phoneDirectory->employeeCount < maxEmployees) {
                strcpy(phoneDirectory->employees[phoneDirectory->employeeCount].department, department);
                strcpy(phoneDirectory->employees[phoneDirectory->employeeCount].lastName, lastName);
                strcpy(phoneDirectory->employees[phoneDirectory->employeeCount].firstName, firstName);
                strcpy(phoneDirectory->employees[phoneDirectory->employeeCount].middleName, middleName);
                strcpy(phoneDirectory->employees[phoneDirectory->employeeCount].phoneNumber, phoneNumber);
                ++phoneDirectory->employeeCount;
            }
        }
    }

    fclose(inputFile);
    printf("Загружено записей: %d\n", phoneDirectory->employeeCount);
    return 1;
}

// ... остальные функции (displayDepartmentPhones, displayAllDepartments) без изменений

int main() {
    C:\Users\Mvideo\Documents\GitHub\прога\Work-with-file
    
    struct PhoneDirectory phoneDirectory;
    initializeDirectory(&phoneDirectory, fileName);
    
    if (!loadData(&phoneDirectory)) {
        fprintf(stderr, "Программа завершена с ошибкой.\n");
        return 1;
    }

    printf("\nДоступные команды:\n");
    printf("1 - Показать все подразделения\n");
    printf("2 - Найти телефоны подразделения\n");
    printf("0 - Выход\n");

    int userChoice;
    char targetDepartment[maxStringLength];

    while (1) {
        printf("\nВведите команду: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                displayAllDepartments(&phoneDirectory);
                break;
            case 2:
                printf("Введите название подразделения: ");
                scanf("%s", targetDepartment);
                displayDepartmentPhones(&phoneDirectory, targetDepartment);
                break;
            case 0:
                printf("Выход из программы.\n");
                return 0;
            default:
                printf("Неверная команда!\n");
                break;
        }
    }

    return 0;
}