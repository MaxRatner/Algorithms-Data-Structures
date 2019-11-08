#ifndef INC_1_BIGINTEGER_H
#define INC_1_BIGINTEGER_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

#define uint unsigned int
using std::vector;
using std::string;
using std::to_string;
using std::max;
using std::istream;
using std::ostream;


class BigInteger {
public:

    BigInteger() = default;
    ~BigInteger() = default;
    BigInteger(const string &str); //////////

    BigInteger(const BigInteger& arg);  // +

    BigInteger(const int arg) : BigInteger(to_string(arg)) {}   // +

    const string toString() const;  // +

    // операторы сравнения == != < > <= >=, оператор присваивания
    BigInteger& operator=(const BigInteger& value); // +
    bool operator<(const BigInteger& second_arg) const;   // +
    bool operator==(const BigInteger& second_arg) const;  // +
    bool operator!=(const BigInteger& second_arg) const;  // +
    bool operator<=(const BigInteger& second_arg) const;  // +
    bool operator>(const BigInteger& second_arg) const;   // +
    bool operator>=(const BigInteger& second_arg) const;  // +

    // унарный минус, постфиксный и префиксный инкремент и декремент
    BigInteger operator-() const;       // +
    BigInteger& operator--();           // +
    BigInteger operator--(int);         // +
    BigInteger& operator++();           // +
    BigInteger operator++(int);         // +

    // вспомогательные функции
    void sum(BigInteger &first_arg, const BigInteger &second_arg);
    void dif(BigInteger &first_arg, const BigInteger &second_arg);

    // сложение, вычитание, умножение, деление, остаток по модулю, работающие так же, как и для int;
    friend BigInteger operator+(const BigInteger& first_arg, const BigInteger& second_arg); // +
    friend BigInteger operator-(const BigInteger& first_arg, const BigInteger& second_arg); // +
    friend BigInteger operator*(const BigInteger& first_arg, const BigInteger& second_arg); // +
    friend BigInteger operator/(const BigInteger& first_arg, const int& second_arg);        // +
    friend BigInteger operator/(const BigInteger& first_arg, const BigInteger& second_arg); // +
    friend BigInteger operator%(const BigInteger& first_arg, const BigInteger& second_arg); // +

    // составное присваивание с этими операциями
    BigInteger& operator+=(const BigInteger second_arg) {
        *this = *this + second_arg;
        return *this;
    }
    BigInteger& operator-=( const BigInteger& other ) {
        *this = *this - other;
        return *this;
    }
    BigInteger& operator*=( const BigInteger& other ) {
        *this = *this * other;
        return *this;
    }
    BigInteger& operator/=( const BigInteger& other ) {
        *this = *this / other;
        return *this;
    }
    BigInteger& operator%=( const BigInteger& other ) {
        *this = *this % other;
        return *this;
    }

    //
    friend std::istream &operator>>(std::istream& stream, BigInteger& arg);
    friend std::ostream &operator<<(std::ostream& stream, const BigInteger& arg);


    // неявное преобразование в bool
    explicit operator bool() const {
        return (!number.empty() && number.back() != 0);
    }

private:
    vector<uint> number;
    bool is_negative = false;
};


BigInteger::BigInteger(const BigInteger& argument) {
    number = argument.number;
    is_negative = argument.is_negative;
}


BigInteger::BigInteger(const string& str) {
    is_negative = str[0] == '-';
    for (int i = str.size() - 1; i >= is_negative; i--) {
        number.emplace_back(str[i] - '0');
    }
    /*if (str == "-0" || str == "" || str == "0") {
        number.emplace_back('0');
        return;
    }
    is_negative = false;



    for (size_t i = str.length() - 1; i > 0; i--) {
        number.emplace_back(str[i] - '0');
    }
    if (str[0] == '-') {
        is_negative = true;
    } else {
        number.emplace_back(str[0] - '0');
    }*/
}

BigInteger& BigInteger::operator=(const BigInteger& argument) {
    this->number = argument.number;
    this->is_negative = argument.is_negative;
    return *this;
}

bool BigInteger::operator<(const BigInteger &second_arg) const {

    // если наше число -0
    if (this->is_negative && (this->number.empty() || (this->number.size() == 1 && this->number.back() == 0))) {
        // второгй аргумент -0
        if ((second_arg.number.empty()) || (second_arg.number.size() == 1 && second_arg.number.back() == 0)) {
            return false;
        }
        if (second_arg.is_negative) {
            return false;
        }
    }

    // отриц < полож; полож !< отриц;
    if (this->is_negative && !(second_arg.is_negative)) {
        return true;
    } else if (!this->is_negative && second_arg.is_negative) {
        return false;
    }
    // отриц отриц; полож полож; но разное кол-во символов
    if (this->number.size() < second_arg.number.size() && this->is_negative) {
        return false;
    } else if (this->number.size() < second_arg.number.size() && !this->is_negative) {
        return true;
    }
    if (this->number.size() > second_arg.number.size() && this->is_negative) {
        return  true;
    } else if (this->number.size() > second_arg.number.size() && !this->is_negative) {
        return false;
    }
    // если одного знака и одинаковое кол-во символов
    for (auto i = static_cast<int>(this->number.size()) - 1; i >= 0; i--) {
        if (this->number[i] < second_arg.number[i]) {
            return true;
        } else if (this->number[i] > second_arg.number[i]) {
            return false;
        }
    }
    return false;
}

bool BigInteger::operator==(const BigInteger &second_arg) const {
    return !(*this < second_arg) && !(second_arg < *this);
}

bool BigInteger::operator!=(const BigInteger& second_arg) const {
    return !(*this == second_arg);
}

bool BigInteger::operator<=(const BigInteger& second_arg) const {
    return (*this < second_arg) || (*this == second_arg);
}

bool BigInteger::operator>(const BigInteger& second_arg) const {
    return !(*this == second_arg) && !(*this < second_arg);
}

bool BigInteger::operator>=(const BigInteger& second_arg) const {
    return (*this == second_arg) || (*this > second_arg);
}

BigInteger BigInteger::operator-() const {
    BigInteger result(*this);
    result.is_negative = !(this->is_negative);
    if (result.number.size() == 1 && result.number[0] == 0) {
        result.is_negative = false;
        result.number[0] = 0;
    }
    return result;
}

BigInteger operator+(const BigInteger& first_arg, const BigInteger& second_arg) {
    BigInteger local_first(first_arg);
    BigInteger local_second(second_arg);
    BigInteger zero(0);
    // если отрицательные или разные по знаку; пользуемся однознаковым вычитанием
    bool is_inverted = 0;
    if (local_first < zero && local_second < zero) {
        local_first = -local_first;
        local_second = -local_second;
        is_inverted = 1;
    } else if (local_second < zero) {
        return local_first - (-local_second);
    } else if (local_first < zero) {
        return local_second - (-local_first);
    }
    // складываем одинаковые по знаку числа
    local_first.sum(local_first, local_second);
    if (is_inverted) {
        return -local_first;
    }
    return local_first;
}

BigInteger operator-(const BigInteger& first_arg, const BigInteger& second_arg) {
    BigInteger local_first(first_arg);
    BigInteger local_second(second_arg);
    BigInteger zero( 0 );
    bool is_inverted = false;
    if (local_first < zero and local_second < zero) {
        local_first = -local_first;
        local_second = -local_second;
        is_inverted = true;
    } else if (local_second < zero) {
        return local_first + (-local_second);
    } else if (local_first < zero) {
        return -(-local_first + local_second);
    }
    if (local_first < local_second) {
        BigInteger temp = local_first;
        local_first = local_second;
        local_second = temp;
        is_inverted = true;
    }
    // находим разницу двух неотрицательных чисел
    local_first.dif(local_first, local_second);
    if (is_inverted) {
        return -local_first;
    }
    return local_first;
}

BigInteger& BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger& BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger temp_object(*this);
    *this += 1;
    return temp_object;
}

BigInteger BigInteger::operator--(int) {
    BigInteger temp_object(*this);
    *this -= 1;
    return temp_object;
}

void BigInteger::sum(BigInteger &first_arg, const BigInteger &second_arg) {
    size_t  max_size = max(first_arg.number.size(), second_arg.number.size());
    int carry = 0;
    uint basis = 10;
    for (size_t i = 0; i < max_size || carry; i++) {
        if (i == first_arg.number.size()) {
            first_arg.number.push_back(0);
        }
        first_arg.number[i] += carry;
        if (i < second_arg.number.size()) {
            first_arg.number[i] += second_arg.number[i];
        }
        carry = first_arg.number[i] >= basis;
        if (carry) {
            first_arg.number[i] -= basis;
        }
    }
}

void BigInteger::dif(BigInteger &first_arg, const BigInteger &second_arg) {
    int carry = 0, basis = 10;
    for (size_t i = 0; i < second_arg.number.size() || carry; i++) {
        int temp_number_i = first_arg.number[i];
        temp_number_i -= carry;
        if (i < second_arg.number.size()) {
            temp_number_i -= second_arg.number[i];
        }
        carry = temp_number_i < 0;
        if (carry) {
            temp_number_i += basis;
        }
        first_arg.number[i] = static_cast<uint>(temp_number_i); // static cast?
    }
    // удаляем лишние 0
    while (first_arg.number.size() > 1 && first_arg.number.back() == 0) {
        first_arg.number.pop_back();
    }
}

BigInteger operator*(const BigInteger& first_arg, const BigInteger& second_arg) {
    BigInteger result;
    int basis = 10;
    result.number.resize(first_arg.number.size() + second_arg.number.size()); ////
    for (size_t i =0; i < first_arg.number.size(); i++) {
        int carry = 0;
        for (size_t j = 0; j < second_arg.number.size() || carry; j++) {
            long long current = result.number[j + i] + carry;
            if (j < second_arg.number.size()) {
                current += first_arg.number[i] * 1ll * second_arg.number[j];
            }
            result.number[j + i] = static_cast<uint>(current % basis);
            carry = int(current / basis);
        }
    }
    // удаляем лишние 0
    while (result.number.size() > 1 && result.number.back() == 0) {
        result.number.pop_back();
    }
    if (first_arg.is_negative ^ second_arg.is_negative) {
        return -result;
    }
    return result;
}

BigInteger operator/(const BigInteger& first_arg, const int& second_arg) {
    BigInteger local_first(first_arg);
    uint carry = 0;
    int basis = 10;
    auto size = static_cast<int>(local_first.number.size());
    for (int i = size - 1; i >= 0; --i) {
        uint current = local_first.number[i] + carry * basis;
        local_first.number[i] = current / second_arg;
        carry = current % second_arg;
    }
    while (local_first.number.size() > 1 && local_first.number.back() == 0) {
        local_first.number.pop_back();
    }
    return local_first * (second_arg < 0 ? -1 : 1);
}

BigInteger operator/(const BigInteger& first_arg, const BigInteger& second_arg) {
    if(second_arg == 2){
        return first_arg/2;
    }
    bool neg_sign = first_arg.is_negative ^ second_arg.is_negative;
    BigInteger local_first(first_arg);
    BigInteger local_second(second_arg);
    local_first.is_negative = false;
    local_second.is_negative = false;
    if (local_first < local_second) {
        return BigInteger(0);
    }
    if (local_first == local_second) {
        return BigInteger(1) * (neg_sign ? -1 : 1);
    }
    BigInteger top = local_first / 2, bottom(0);
    while (top > bottom) {
        BigInteger middle = (top + bottom) / 2;
        BigInteger multiply = middle * local_second;
        if (multiply < local_first) {
            if ((middle + 1) * local_second > local_first) {
                while (middle.number.size() > 1 && middle.number.back() == 0) {
                    middle.number.pop_back();
                }
                return middle * (neg_sign ? -1 : 1);
            }
            bottom = middle;
        } else if (multiply > local_first) {
            top = middle;
        } else {
            while (middle.number.size() > 1 && middle.number.back() == 0) {
                middle.number.pop_back();
            }
            return middle * (neg_sign ? -1 : 1);
        }
    }
    while (bottom.number.size() > 1 && bottom.number.back() == 0) { /////////////
        bottom.number.pop_back();
    }
    return bottom * (neg_sign ? -1 : 1);
}

BigInteger operator%(const BigInteger& first, const BigInteger& second) {
    BigInteger div_result = first / second;
    return first - div_result * second;
}

istream& operator>>(std::istream &str, BigInteger &arg) {
    std::string temp;
    str >> temp;
    BigInteger new_arg(temp);
    arg = new_arg;
    return str;
}

ostream& operator<<(ostream& stream, const BigInteger& arg) {
    string temp_str;
    temp_str = arg.toString();
    stream << temp_str;
    return stream;
}

const string BigInteger::toString() const {
    std::string s = is_negative ? "-" : "";
    if (number[0] == 0 && number.size() == 1) {
        s = '0';
        return s;
    }

    bool forw_nuls = true;
    for (int i = int(number.size()) - 1; i >= 0; --i) {
        if (number[i] == 0 && forw_nuls) {
            continue;
        } else {
            forw_nuls = false;
            s += number[i] + '0';
        }
    }
    if (s.empty() || (s[0] == '-' && s.length() == 1))
        s = '0';
    return s;
}

#endif //INC_1_BIGINTEGER_H