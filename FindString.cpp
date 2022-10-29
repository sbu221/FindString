#include <iostream>

using namespace std;

int countStudents{};

// структура студента
struct Student 
{
    char* name{}; // имя
    int age{}; // возраст
};

Student CreateStudent(char name[], int age); // метод для создания студента

void InitializeStudents(Student*& students); // создание студентов 
// *& разыменование указателя, вспоминаем. Берем указатель и находим адрес, где он сам находится, а не куда указывает

void FindName(Student* students); // Поиск имени

void PrintStudent(Student& student); // вывод на экран студента

bool IsExist(Student& student, char findString[]); // проверка на соответствие имени

int main()
{
    setlocale(0, "");

    Student* students = nullptr;

    InitializeStudents(students);

    FindName(students);

    for (size_t i = 0; i < countStudents; i++)
        delete[] students[i].name;
}

Student CreateStudent(char name[], int age)
{
    int lenght = strnlen_s(name, 24) + 1; // определяем длину имени
    char* tempName = new char[lenght]; // создаем новую область памяти для имени

    strcpy_s(tempName, lenght, name); // копируем имя в tempName

    return Student{ tempName, age }; // возращаем студента
}

void InitializeStudents(Student*& students)
{
    cout << "Введите количество студентов:" << endl;
    cin >> countStudents;

    students = new Student[countStudents]{}; // выделяем новую область памяти

    for (size_t i = 0; i < countStudents; i++)
    {
        char name[25];
        int age;
        cout << "Введите имя:" << endl;
        cin >> name;

        cout << "Введите возраст:" << endl;
        cin >> age;

        students[i] = CreateStudent(name, age);
    }

    system("cls");
    cout << "Студенты были проинициализированы!\n" << endl;
}

void FindName(Student* students)
{
    char findName[25];
    
    cout << "Введите имя для поиска:" << endl;
    cin >> findName;

    for (size_t i = 0; i < countStudents; i++)
    {
        auto student = students[i]; // определяем текущего студента, чтоб каждый раз не обращаться через students[i]

        if (IsExist(student, findName)) // если найден, то выводим на экран
            PrintStudent(student);
    }
}

void PrintStudent(Student& student)
{
    cout << "\nИмя: " << student.name << endl;
    cout << "Возраст: " << student.age << endl;
}

bool IsExist(Student& student, char findString[])
{
    char tmpName[25]{};
    int lenght = strnlen_s(student.name, 24) + 1; // узнаем длину строки, которую будем копировать

    strcpy_s(tmpName, lenght, student.name); // копируем в tmpName строку из student.name

    _strlwr_s(tmpName, lenght); // переводим скопированное имя в нижний регистр
    _strlwr_s(findString, strlen(findString) + 1); // тоже самое, но для строки поиска

    auto isFound = strstr(tmpName, findString); // сравниваем 2е строки

    return isFound; // возращаем true, если совпадают символы и false - не совпадают
}
