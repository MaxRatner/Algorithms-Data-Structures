#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <fstream>

using std::vector;
using std::string;
using std::map;
using std::queue;
using std::min;
using std::max;
using std::cin;
using std::pair;
using std::make_pair;

struct Cell {
    int x, y;

    Cell() = default;
    Cell(int a, int b) : x(a), y(b) {}
    Cell(const string a);

    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;
    bool operator<(const Cell& other) const;
    bool is_step(int stepX, int stepY);

    pair<int, int> cell_pair = make_pair(8 * x, y);

    Cell step(int stepX, int stepY);
};

Cell::Cell(const string a) {
    x = a[0] - 'a' + 1;
    y = a[1] - '0';
}

bool Cell::operator==(const Cell& other) const {
    return x == other.x && y == other.y;
}

bool Cell::operator!=(const Cell& other) const {
    return not(*this == other);
}

bool Cell::operator<(const Cell& other) const {
    if (x < other.x) {
        return true;
    } else if (x > other.x) {
        return false;
    } else if (y < other.y) {
        return true;
    } else {
        return false;
    }
}

bool Cell::is_step(int stepX, int stepY) {
    return ((x + stepX) >= 1) && ((x + stepX) <= 8) && ((y + stepY) >= 1) && ((y + stepY) <= 8);
}

Cell Cell::step(int stepX, int stepY) {
    return Cell(x + stepX, y + stepY);
}

const Cell WhiteKing = Cell("c3");

struct Table {
    Cell WhiteQueen;
    Cell BlackKing;
    bool turn_color; // 1 - white, 0 - black

    Table(Cell a, Cell b, bool d) : WhiteQueen(a), BlackKing(b), turn_color(d) {}

    bool operator<(const Table& a) const {
        return board_pair() < a.board_pair();
    }

    pair<int, int> board_pair() const;
    //int get_hash() const;
};

pair<int, int> Table::board_pair() const {
    if (turn_color) {
        return make_pair(WhiteQueen.cell_pair.first * (-64) - BlackKing.cell_pair.first,
                         WhiteQueen.cell_pair.second * (-64) - BlackKing.cell_pair.second);
    } else {
        return make_pair(WhiteQueen.cell_pair.first * 64 + BlackKing.cell_pair.first,
                         WhiteQueen.cell_pair.second * 64 + BlackKing.cell_pair.second);
    }
}

class Endspiel {
public:
    Endspiel() : x_step{1, 1, 1, -1, -1, -1, 0, 0}, y_step{1, -1, 0, 1, -1, 0, 1, -1} {}

    int solve(const Cell& WQ, const Cell& BK);

private:
    map<Table, int> results;

    void white_turn(Cell& king, Cell& queen, queue<Table>& queueSituation);
    void black_turn(Cell& king, Cell& queen, queue<Table>& queueSituation);

    void add_white_queens(const Cell& queen, const Cell& BK, queue<Table>& queueSituations, int maxStep);
    void add_black_kings(const Cell& queen, const Cell& Bking, queue<Table>& queueSituations, int minStep);

    void check();
    bool is_check(const Cell& King, const Cell& Queen);
    bool step_with_WK(Cell BK, Cell WK, Cell WQ);

    const int x_step[8];
    const int y_step[8];
};

bool Endspiel::step_with_WK(Cell BK, Cell WK, Cell WQ) {
    for (int i = 0; i < 8; ++i) {
        if (BK.step(x_step[i], y_step[i]) == WK) {
            return false;
        }
    }
    return true;
}

bool Endspiel::is_check(const Cell& King, const Cell& Queen) {
    for (int i = 0; i < 8; i++) {
        Cell tempQueen = Queen;
        while (tempQueen.is_step(x_step[i], y_step[i])) {
            tempQueen = tempQueen.step(x_step[i], y_step[i]);

            if (!(tempQueen != WhiteKing)) {
                break;
            } else {
                if (tempQueen == King) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Endspiel::add_black_kings(const Cell& queen, const Cell& Bking, queue<Table>& queueSituations, int minStep) {
    for (int i = 0; i < 8; i++) {
        Cell tempKing = Bking;
        if (tempKing.is_step(x_step[i], y_step[i])) {
            tempKing = tempKing.step(x_step[i], y_step[i]);
            if (tempKing != WhiteKing && tempKing != queen &&
                step_with_WK(tempKing, WhiteKing, queen)) {
                if (results.find(Table{queen, tempKing, false}) != results.end()) {
                    if (results[Table{queen, tempKing, false}] >= minStep + 1) {
                        continue;
                    }
                }
                queueSituations.push(Table{queen, tempKing, false});
            } else {
                continue;
            }
        }
    }
}

void Endspiel::add_white_queens(const Cell& queen, const Cell& BK, queue<Table>& queueSituations, int maxStep) {
    for (int i = 0; i < 8; i++) {
        Cell tempQueen(queen);
        while (tempQueen.is_step(x_step[i], y_step[i])) {
            tempQueen = tempQueen.step(x_step[i], y_step[i]);
            if (tempQueen != WhiteKing && tempQueen != BK) {
                if (is_check(tempQueen, BK)) {
                    continue;
                }
                if (results.find(Table{tempQueen, BK, true}) != results.end()) {
                    if (results[Table{tempQueen, BK, true}] <= maxStep + 1) {
                        continue;
                    }
                }
                queueSituations.push(Table{tempQueen, BK, true});
            } else {
                break;
            }
        }
    }
}


int Endspiel::solve(const Cell& WQ, const Cell& BK) {
    bool flag;
    for (int i = 1; i <= 8; ++i) {
        for (int j = 1; j <= 8; ++j) {
            Cell BlackKing(i, j);
            if (!(BlackKing == WhiteKing ||  !step_with_WK(BlackKing, WhiteKing, Cell(0, 0)))) {
                for (int k = 1; k <= 8; ++k) {
                    for (int l = 1; l <= 8; ++l) {
                        Cell queen(k, l);
                        if (!(queen == BlackKing || queen == WhiteKing)) {
                            if (is_check(BlackKing, queen)) {
                                flag = false;
                                for (int t = 0; t < 8; t++) {
                                    if (BlackKing.is_step(x_step[t], y_step[t])) {
                                        Cell tempKing;
                                        tempKing = BlackKing.step(x_step[t], y_step[t]);
                                        if (tempKing != WhiteKing) {
                                            if (step_with_WK(tempKing, WhiteKing, queen)) {
                                                if (!is_check(tempKing, queen)) {
                                                    flag = true;
                                                }
                                            }
                                        }
                                    }
                                }
                                if (!flag) {
                                    results[Table(queen, BlackKing, false)] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    check();
    if (results.find(Table(WQ, BK, true)) != results.end()) {
        return results[Table(WQ, BK, true)];
    }
}

void Endspiel::white_turn(Cell& king, Cell& queen, queue<Table>& queueSituation) {
    if (not is_check(king, queen)) {
        bool isSure = false;
        int minStep = 0;
        for (auto i = 0; i < 8; i++) {
            Cell tempQueen = queen;
            while (tempQueen.is_step(x_step[i], y_step[i])) {
                tempQueen = tempQueen.step(x_step[i], y_step[i]);
                if (tempQueen != WhiteKing && tempQueen != king) {
                    if (results.find(Table{tempQueen, king, false}) != results.end()) {
                        if (!isSure) {
                            minStep = results[Table{tempQueen, king, false}];
                        }
                        isSure = true;
                        minStep = min(minStep, results[Table{tempQueen, king, false}]);
                    }
                } else {
                    break;
                }
            }
        }

        if (isSure) {
            if (results.find(Table{queen, king, true}) == results.end() ||
                results[Table{queen, king, true}] > minStep + 1) {
                results[Table(queen, king, true)] = minStep + 1;
                if (!is_check(king, queen)) {
                    add_black_kings(queen, king, queueSituation, minStep + 1);
                }
            }
        }
    }
}

void Endspiel::black_turn(Cell& king, Cell& queen, queue<Table>& queueSituation) {
    bool isNotSure = false;
    int maxCountStep = -3;
    for (auto i = 0; i < 8; i++) {
        if (king.is_step(x_step[i], y_step[i])) {
            Cell tempKing = king.step(x_step[i], y_step[i]);
            if (tempKing != WhiteKing && step_with_WK(tempKing, WhiteKing, queen) && !is_check(tempKing, queen)) {
                results.end() == results.find(Table{queen, tempKing, true}) ? (isNotSure = true)
                                                                            : (maxCountStep = max(maxCountStep, results[Table{queen, tempKing, true}]));
            }
        }
    }
    if (!isNotSure && (results.find(Table{queen, king, false}) == results.end() ||
                results[Table{queen, king, false}] < maxCountStep + 1)) {
                results[Table(queen, king, false)] = maxCountStep + 1;
                add_white_queens(queen, king, queueSituation, maxCountStep + 1);
    }
}

void Endspiel::check() {
    queue<Table> queueSituation;
    for (const auto& situation: results) {
        add_white_queens(situation.first.WhiteQueen, situation.first.BlackKing, queueSituation, -3);
    }
    while (!queueSituation.empty()) {
        Table situation = queueSituation.front();
        queueSituation.pop();
        Cell king = situation.BlackKing;
        Cell queen = situation.WhiteQueen;
        (situation.turn_color ? white_turn : black_turn)(king, queen, queueSituation);
    }
}

int main() {
    Endspiel solver;
    char qx, qy, kx, ky;
    cin >> qx >> qy >> kx >> ky;

    Cell WQ(int(qx - 'a' + 1), int(qy - '0'));
    Cell BK(int(kx - 'a' + 1), int(ky - '0'));

    int result = solver.solve(WQ, BK);
    if (result > 0) {
        std::cout << result;
    } else {
        std::cout << "IMPOSSIBLE";
    }
}