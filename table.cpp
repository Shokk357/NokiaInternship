#include "table.h"
#include <stack>
#include <queue>

table::table(std::string &filename) {
    std::freopen(filename.c_str(), "r", stdin);
    std::vector<std::string> tableAsVector;
    getline(std::cin, curLine);
    tableAsVector.push_back(curLine);
    while (getline(std::cin, curLine)) {
        tableAsVector.push_back(curLine);
    }
    parseTable(tableAsVector);
}

table::table(std::vector<std::string> table) {
    parseTable(table);
}

table::cell::cell(std::string val) : val(val), visited(false), res(0) {
}

void table::parseHeader(std::string headerLine) {
    int pos = headerLine.find_first_of(',');
    while (pos != -1) {
        header.push_back(headerLine.substr(0, pos));
        headerLine = headerLine.substr(pos + 1, headerLine.length());
        pos = headerLine.find_first_of(',');
    }
    header.push_back(headerLine);
}

void table::parseLine(std::string num, std::string line) {
    int pos = line.find_first_of(',');
    for (auto i = 0; i < header.size(); i++) {
        myTable.emplace(header[i] + num, line.substr(0, pos));
        line = line.substr(pos + 1, line.length());
        pos = line.find_first_of(',');
    }
}

void table::parseTable(std::vector<std::string> table) {
    std::string curLine = table[0];
    parseHeader(curLine.substr(1, curLine.length()));
    for (int i = 1; i < table.size(); i++) {
        curLine = table[i];
        int pos = curLine.find_first_of(',');
        std::string number = curLine.substr(0, pos);
        numeration.push_back(number);
        parseLine(number, curLine.substr(pos + 1, curLine.length()));
    }
}

std::vector<std::string> table::reversePolishNotation(std::string expr) {
    std::vector<std::string> vals;
    std::stack<char> ops;
    std::string curCell = "";
    for (int i = 0; i < expr.size(); i++) {
        if (!isOperation(expr[i])) {
            curCell += expr[i];
        } else {
            vals.push_back(curCell);
            curCell = "";
            while (!ops.empty() && (priority(ops.top()) >= priority(expr[i]))) {
                std::string curOp;
                curOp = ops.top();
                vals.push_back(curOp);
                ops.pop();
            }
            ops.push(expr[i]);
        }
    }
    vals.push_back(curCell);
    while (!ops.empty()) {
        std::string curOp;
        curOp = ops.top();
        vals.push_back(curOp);
        ops.pop();
    }
    return vals;
}

void table::calc(cell &elem) {
    if (elem.visited && elem.val[0] == '=') {
        throw std::runtime_error("The cycle reference at expression: " + elem.val);
    } else {
        elem.visited = true;
    }
    if (elem.val[0] == '=') {
        std::vector<std::string> expr = reversePolishNotation(elem.val.substr(1, elem.val.length()));
        std::stack<int> ans;
        for (int i = 0; i < expr.size(); i++) {
            if (!isOperation(expr[i][0])) {
                auto arg = myTable.find(expr[i]);
                if (arg == myTable.end()) {
                    throw std::runtime_error("No cell " + expr[i] + " in table at expression: " + elem.val);
                } else {
                    calc(arg->second);
                    ans.push(arg->second.res);
                }
            } else {
                int fst = ans.top();
                ans.pop();
                int snd = ans.top();
                ans.pop();
                if (expr[i] == "+") {
                    ans.push(snd + fst);
                } else if (expr[i] == "-") {
                    ans.push(snd - fst);
                } else if (expr[i] == "*") {
                    ans.push(snd * fst);
                } else if (expr[i] == "/") {
                    if (fst == 0) {
                        throw std::runtime_error("Divide by zero at expression: " + elem.val);
                    } else {
                        ans.push(snd / fst);
                    }
                }
            }
        }
        elem.res = ans.top();
        elem.visited = false;
    } else {
        elem.res = stoi(elem.val);
        elem.visited = false;
    }
}

void table::compute() {
    for (auto i = myTable.begin(); i != myTable.end(); i++) {
        if (!i->second.visited) calc(i->second);
    }
}

void table::printAnswer() {
    for (auto resLine : result) {
        std::cout << resLine << std::endl;
    }
}

void table::buildAnswer() {
    for (int i = 0; i <= numeration.size(); i++) {
        std::string curLine = "";
        if (i == 0) {
            for (auto j = header.begin(); j != header.end(); j++) {
                curLine += ',' + *j;
            }
        } else {
            curLine += numeration[i - 1];
            for (auto j = header.begin(); j != header.end(); j++) {
                curLine += "," + std::to_string(myTable.find(*j + numeration[i - 1])->second.res);
            }
        }
        result.push_back(curLine);
    }
}

bool table::isOperation(char elem) {
    return (elem == '-') || (elem == '+') || (elem == '*') || (elem == '/');
}

int table::priority(char elem) {
    if ((elem == '+') || (elem == '-'))
        return 1;
    if ((elem == '*') || (elem == '/'))
        return 2;
    return -1;
}

std::vector<std::string> table::getResult() { return this->result; }