#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Monomial {
private:
    vector<int> powers;
    vector<char> variables;
    double coefficient;

public:
    // Constructors
    Monomial() : coefficient(0) {}
    Monomial(double coeff, const vector<int>& p, const vector<char>& v) : coefficient(coeff), powers(p), variables(v) {}
    Monomial(const char* monomial_str) {
        stringstream ss(monomial_str);
        char c;
        ss >> c >> coefficient;
        while (ss >> c) {
            int power;
            ss >> c >> power;
            variables.push_back(c);
            powers.push_back(power);
        }
    }

    // Accessors
    double getCoefficient() const { return coefficient; }
    const vector<int>& getPowers() const { return powers; }
    const vector<char>& getVariables() const { return variables; }

    // Overloaded operators
    Monomial& operator+=(const Monomial& other) {
        if (variables != other.variables || powers != other.powers) {
            throw invalid_argument("Monomials must have the same variables and powers.");
        }
        coefficient += other.coefficient;
        return *this;
    }

    friend Monomial operator+(Monomial lhs, const Monomial& rhs) {
        lhs += rhs;
        return lhs;
    }

    Monomial& operator-=(const Monomial& other) {
        if (variables != other.variables || powers != other.powers) {
            throw invalid_argument("Monomials must have the same variables and powers.");
        }
        coefficient -= other.coefficient;
        return *this;
    }

    friend Monomial operator-(Monomial lhs, const Monomial& rhs) {
        lhs -= rhs;
        return lhs;
    }

    Monomial& operator*=(const Monomial& other) {
        coefficient *= other.coefficient;
        for (size_t i = 0; i < variables.size(); ++i) {
            powers[i] += other.powers[i];
        }
        return *this;
    }

    friend Monomial operator*(Monomial lhs, const Monomial& rhs) {
        lhs *= rhs;
        return lhs;
    }

    bool operator==(const Monomial& other) const {
        return coefficient == other.coefficient && powers == other.powers && variables == other.variables;
    }

    bool operator!=(const Monomial& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Monomial& monomial) {
        os << "<" << monomial.coefficient;
        for (size_t i = 0; i < monomial.variables.size(); ++i) {
            os << "*" << monomial.variables[i] << "^" << monomial.powers[i];
        }
        os << ">";
        return os;
    }
};

int main() {
    // Пример использования класса Monomial
    Monomial m1("<5*x^2y^3z>");
    Monomial m2("<3*a^2b^3c>");
    cout << "m1: " << m1 << endl;
    cout << "m2: " << m2 << endl;
    Monomial m3 = m1 + m2;
    cout << "m1 + m2: " << m3 << endl;
    Monomial m4 = m1 * m2;
    cout << "m1 * m2: " << m4 << endl;

    return 0;
}
