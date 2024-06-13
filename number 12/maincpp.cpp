#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

// ��������� ��� ������������� ��������� ������������
struct Message {
    std::string userName;
    std::string time;
    std::string message;

    Message(const std::string& user, const std::string& t, const std::string& msg)
        : userName(user), time(t), message(msg) {}

    // �������� ��� ��������� ��������� �� userName � time
    bool operator<(const Message& other) const {
        if (userName != other.userName) {
            return userName < other.userName;
        }
        return time < other.time;
    }
};

// ������� ��� ������ ��������� ������������
void printUserMessages(const std::set<Message*>& messages, const std::string& userName) {
    for (const auto& message : messages) {
        if (message->userName == userName) {
            std::cout << message->userName << " "
                << message->time << ": "
                << message->message << std::endl;
        }
    }
}

// ������� ��� ������ ��������� ������������ � �������� ��������� ���������
void printUserMessagesInTimeInterval(const std::set<Message*>& messages, const std::string& userName,
    const std::string& startTime,
    const std::string& endTime) {
    for (const auto& message : messages) {
        if (message->userName == userName && message->time >= startTime && message->time <= endTime) {
            std::cout << message->userName << " "
                << message->time << ": "
                << message->message << std::endl;
        }
    }
}

// ������� ��� ������ ���� ��������� �� ��������� ���������� ���������
void printMessagesInTimeInterval(const std::set<Message*>& messages,
    const std::string& startTime,
    const std::string& endTime) {
    for (const auto& message : messages) {
        if (message->time >= startTime && message->time <= endTime) {
            std::cout << message->userName << " "
                << message->time << ": "
                << message->message << std::endl;
        }
    }
}

// ������� ��� �������� ���������
void deleteMessage(std::set<Message*>& messages, Message* messageToDelete) {
    auto it = messages.find(messageToDelete);
    if (it != messages.end()) {
        delete* it;
        messages.erase(it);
    }
}

// ������� ��� �������� ���� ��������� ������������
void deleteUserMessages(std::set<Message*>& messages, const std::string& userName) {
    for (auto it = messages.begin(); it != messages.end();) {
        if ((*it)->userName == userName) {
            delete* it;
            it = messages.erase(it);
        }
        else {
            ++it;
        }
    }
}


int main() {
    system("color F0");

    std::set<Message*> messages;
   
    // ����� ���������� ���������� ��������� �� ������ � ���������� �� � messages
    std::ifstream inputFile("messages.txt");
    if (inputFile.is_open())
    {
        std::string userName;
        std::string timeStr;
        std::string message;
        std::string line;
        while (getline(inputFile, line))
        {
            std::stringstream ss(line);
            std::string user, time, messageText;
            ss >> user;
            ss >> time;
            getline(ss, messageText); // ��������� ���������� ����� ������ ��� ����� ���������
            Message* msg = new Message(user, time, messageText);
            messages.insert(msg);
        }
        inputFile.close();
    }

    // ������ ������������� �������
    std::cout << "All messages of user 'Alice':" << std::endl;
    printUserMessages(messages, "Alice");


    std::cout << "\nMessages of user 'Bob' between 10:00:00 and 12:00:00:" << std::endl;
    printUserMessagesInTimeInterval(messages, "Bob", "10:00:00", "12:00:00");

    std::cout << "\nAll messages between 09:00:00 and 13:00:00:" << std::endl;
    printMessagesInTimeInterval(messages, "09:00:00", "13:00:00");

     // ������ �������� ���������
    Message* messageNum2 = *(++messages.begin());
    deleteMessage(messages, messageNum2);
    std::cout << "\nAll messages between 09:00:00 and 13:00:00:" << std::endl;
    printMessagesInTimeInterval(messages, "09:00:00", "13:00:00");
    std::cout << "\n";

     // ������ �������� ���� ��������� ������������
    deleteUserMessages(messages, "Alice");
    std::cout << "\nAll messages between 09:00:00 and 13:00:00:" << std::endl;
     printMessagesInTimeInterval(messages, "09:00:00", "13:00:00");

     // ������� ������
    for (auto message : messages) {
        delete message;
    }
    messages.clear();

    return 0;
}
