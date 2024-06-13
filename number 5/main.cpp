#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// ��������� ��� �������� ���������� � ��������
struct Contract {
    int number;
    string startDate;
    string endDate;
    int workId;
    int cost;
};

// �����, �������������� ����������
class Employee {
private:
    string fullName;
    vector<Contract*> contracts;

public:
    Employee(string name) : fullName(name) {}

    // ���������� ������ ��������
    void addContract(Contract* contract) {
        contracts.push_back(contract);
    }

    // ������� ����� ��������� ���������
    int getTotalCost() const {
        int totalCost = 0;
        for (const auto& contract : contracts) {
            totalCost += contract->cost;
        }
        return totalCost;
    }

    // ��������� ������ ���������
    vector<Contract*> getContracts() const {
        return contracts;
    }

    // ����� ������ ���������������� ��������
    Contract* getLongestContract() const {
        if (contracts.empty()) return nullptr;
        auto longest = *max_element(contracts.begin(), contracts.end(),
            [](Contract* a, Contract* b) {
                return a->endDate > b->endDate;
            });
        return longest;
    }

    // ����� ������ �������� ��������
    Contract* getMostExpensiveContract() const {
        if (contracts.empty()) return nullptr;
        auto expensive = *max_element(contracts.begin(), contracts.end(),
            [](Contract* a, Contract* b) {
                return a->cost < b->cost;
            });
        return expensive;
    }

    // ��������� ������� ����� ����������
    string getFullName() const {
        return fullName;
    }

    // �������� ���� ��������� ����������
    void clearContracts() {
        for (auto& contract : contracts) {
            delete contract;
        }
        contracts.clear();
    }
};

int main() {
    // ������������� ��������� ��� �������� �����������
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

                    // ���������� ����� �� ������ ���� ������
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
                    // ��������� ���� ������
                    iss >> contract->startDate;

                    // ���������� ����� �� ������ ���� ���������
                    
                    std::string temp;
                    iss >> temp;
                    // ��������� ���� ���������
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

    // ������ ������������� ����������� ������
    string searchName = "IvanovIvanIvanovich"; // ������ ������ ����������
    if (employees.find(searchName) != employees.end()) {
        Employee* employee = employees[searchName];
        cout << "Total cost of contracts: " << employee->getTotalCost() << endl;
        cout << "Longest contract end date: " << employee->getLongestContract()->endDate << endl;
        cout << "Most expensive contract cost: " << employee->getMostExpensiveContract()->cost << endl;
        cout << "List of contracts:" << endl;
        for (const auto& contract : employee->getContracts()) {
            cout << "Contract � " << contract->number << ", Start date: " << contract->startDate << ", End date: " << contract->endDate << ", Cost: " << contract->cost << endl;
        }
    }
    else {
        cout << "Employee not found." << endl;
    }

    // �������� ���������� � ����������� � ������������ ������
    for (auto& pair : employees) {
        pair.second->clearContracts();
        delete pair.second;
    }

    return 0;
}


