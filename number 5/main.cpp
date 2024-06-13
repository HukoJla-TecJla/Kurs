#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// Структура для хранения информации о договоре
struct Contract {
    int number;
    string startDate;
    string endDate;
    int workId;
    int cost;
};

// Класс, представляющий сотрудника
class Employee {
private:
    string fullName;
    vector<Contract*> contracts;

public:
    Employee(string name) : fullName(name) {}

    // Добавление нового договора
    void addContract(Contract* contract) {
        contracts.push_back(contract);
    }

    // Подсчет общей стоимости договоров
    int getTotalCost() const {
        int totalCost = 0;
        for (const auto& contract : contracts) {
            totalCost += contract->cost;
        }
        return totalCost;
    }

    // Получение списка договоров
    vector<Contract*> getContracts() const {
        return contracts;
    }

    // Поиск самого продолжительного договора
    Contract* getLongestContract() const {
        if (contracts.empty()) return nullptr;
        auto longest = *max_element(contracts.begin(), contracts.end(),
            [](Contract* a, Contract* b) {
                return a->endDate > b->endDate;
            });
        return longest;
    }

    // Поиск самого дорогого договора
    Contract* getMostExpensiveContract() const {
        if (contracts.empty()) return nullptr;
        auto expensive = *max_element(contracts.begin(), contracts.end(),
            [](Contract* a, Contract* b) {
                return a->cost < b->cost;
            });
        return expensive;
    }

    // Получение полного имени сотрудника
    string getFullName() const {
        return fullName;
    }

    // Удаление всех договоров сотрудника
    void clearContracts() {
        for (auto& contract : contracts) {
            delete contract;
        }
        contracts.clear();
    }
};

int main() {
    // Ассоциативный контейнер для хранения сотрудников
    map<string, Employee*> employees;

    ifstream file("contracts.txt");
    if (!file) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line.back() == ' ')
        {
            string name = line;
            name.erase(remove_if(name.begin(), name.end(), ::isspace), name.end());
            getline(file, line);
            if (line.back() == '{')
            {
                Employee* employee;
                if (employees.find(name) == employees.end())
                {
                    employee = new Employee(name);
                    employees[name] = employee;
                }
                else 
                {
                    employee = employees[name];
                }

                while (getline(file, line)) 
                {
                    if (line == "}") break;
                    Contract* contract = new Contract;
                    std::istringstream iss(line);

                    // Пропускаем слова до начала даты начала
                    for (int i = 0; i < 3; ++i) {
                        if (i == 1)
                        {
                            iss >> contract->number;
                        }
                        else
                        {
                            std::string temp;
                            iss >> temp;
                        }
                    }
                    // Считываем дату начала
                    iss >> contract->startDate;

                    // Пропускаем слова до начала даты окончания
                    
                    std::string temp;
                    iss >> temp;
                    // Считываем дату окончания
                    iss >> contract->endDate;

                    iss >> temp;

                    iss >> contract->workId;

                    iss >> temp;
                    
                    iss >> contract->cost;
                   
                    employee->addContract(contract);
                }
            }  
        }
    }

    // Пример использования функционала класса
    string searchName = "IvanovIvanIvanovich"; // Пример поиска сотрудника
    if (employees.find(searchName) != employees.end()) {
        Employee* employee = employees[searchName];
        cout << "Total cost of contracts: " << employee->getTotalCost() << endl;
        cout << "Longest contract end date: " << employee->getLongestContract()->endDate << endl;
        cout << "Most expensive contract cost: " << employee->getMostExpensiveContract()->cost << endl;
        cout << "List of contracts:" << endl;
        for (const auto& contract : employee->getContracts()) {
            cout << "Contract № " << contract->number << ", Start date: " << contract->startDate << ", End date: " << contract->endDate << ", Cost: " << contract->cost << endl;
        }
    }
    else {
        cout << "Employee not found." << endl;
    }

    // Удаление информации о сотрудниках и освобождение памяти
    for (auto& pair : employees) {
        pair.second->clearContracts();
        delete pair.second;
    }

    return 0;
}


