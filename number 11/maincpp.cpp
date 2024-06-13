#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <forward_list>
#include <locale>
#include <thread>


class Ticket {
private:
    int NumTicket;
    int Prize;
public:
    Ticket(int num) : NumTicket(num) {}
    
    int GetNumTicket() const { return NumTicket; }
    int GetPrize() const { return Prize; }
    void setPrize(int amount) { Prize = amount; }
};


class Lottery {
private:
    std::vector <Ticket> Tickets;
    int NumTickets;
public:
    std::vector <int> GenerationWinNum(int WinNums,int VariantsNums)
    {
        // �������� ������� � ������� �� 1 �� VariantsNums
        std::vector<int> numbers(VariantsNums);
        std::iota(numbers.begin(), numbers.end(), 1);

        // ������������� �������
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(numbers.begin(), numbers.end(), gen);

        // ����� ������ WinNums �����
        std::vector<int> result(numbers.begin(), numbers.begin() + WinNums);

        return result;
    }
  

    void generateTickets(int numTickets)
    {
        Tickets.clear();
        Tickets.reserve(numTickets);
        for (int i = 1; i < numTickets; ++i)
        {
            Tickets.emplace_back(i);
        }
    }

    Ticket& getRandomTicket()
    {
        static std::mt19937 mt(std::time(nullptr)); // ��������� ������ ��������� �����
        std::uniform_int_distribution<int> dist(0, Tickets.size() - 1);
        return Tickets[dist(mt)];
    }
};

class DataProcessor {
private:
    std::forward_list <Ticket*>  WinTickets;
public:

    void conductDraw(Lottery& lottery, int NumBuyTicket, int WinNums, int VariantsNums)
    {
        WinTickets.clear();
        int* arr = new int[WinNums];
        std::cout << "�������� " << WinNums << " ����� �� ��������� �� 1 �� 46:\n";

        for (int i = 0; i < WinNums; ++i) {
            std::cout << "������� ����� " << i + 1 << ": ";
            std::cin >> arr[i];
        }

        int NumTickets;
        std::cout << "������� �����: ";
        std::cin >> NumTickets;
        std::cout << "\n";
        lottery.generateTickets(NumTickets);
     
        for (int i = 0; i < NumBuyTicket;++i)
        {
            Ticket& RandomTicket = lottery.getRandomTicket();
            auto TicketWinNum = lottery.GenerationWinNum(WinNums,VariantsNums);
            std::cout << "����� �����: " << RandomTicket.GetNumTicket() << std::endl;
            int count = 0;

            for (int i = 0; i < WinNums; ++i)
            {
                auto it = std::find(TicketWinNum.begin(), TicketWinNum.end(), arr[i]);

                if (it != TicketWinNum.end())
                {
                    std::cout << "�� �������� ����� " << arr[i] << std::endl;
                    ++count;
                }
                else
                {
                    std::cout << "�� �� �������, ����� " << arr[i] << " ��� � ������" << std::endl;
                }
            }
            std::cout <<"\n";
            int Prize;
            if (count == WinNums)
            {
                Prize = 1500000;
            }
            else
            {
                Prize = count * 100;
            }
            RandomTicket.setPrize(Prize);

            if (count != 0)
            {
                WinTickets.push_front(&RandomTicket);
            }
        }
        delete[] arr;
    }
    // ����� �� ������ ������
    Ticket* findTicketByNumber(int numTicket)
    {
        auto it = std::find_if(WinTickets.begin(), WinTickets.end(),
            [numTicket](Ticket* t) { return t->GetNumTicket() == numTicket; });
        return (it != WinTickets.end()) ? *it : nullptr;
    }

    // ����� ������� �� �������� ��������
    std::vector<Ticket*> findTicketsByPrize(int prize)
    {
        std::vector<Ticket*> result;
        for (auto ticket : WinTickets)
        {
            if (ticket->GetPrize() == prize)
            {
                result.push_back(ticket);
            }
        }
        return result;
    }
    void PrinWinTickets()
    {
        std::cout << "������ � ���������: \n";
        for (auto it = WinTickets.begin(); it != WinTickets.end(); ++it)
        {
            std::cout << "����� �����: " << (*it)->GetNumTicket() << "  ����: " << (*it)->GetPrize() <<"\n";
        }
        std::cout << "\n";
    }
};

int main()
{
    system("color F0");
    setlocale(LC_ALL, "Rus");

    Lottery lottery;
    
    DataProcessor Play;

    int NumBuyTicket;
    std::cout << "������� ���������� ������� ��� �������: ";
    std::cin >> NumBuyTicket;
    Play.conductDraw(lottery, NumBuyTicket, 6, 46);
    Play.PrinWinTickets();
    std::cout << "����� �� �������� ��������: \n";
    auto FindTickets = Play.findTicketsByPrize(100);
    for (auto ticket : FindTickets)
    {
        std::cout << "����� �����: " << ticket->GetNumTicket() << " ����: " << ticket->GetPrize() << "\n";
    }

    return 0;
}