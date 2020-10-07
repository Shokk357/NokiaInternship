#ifndef NOKIAINTERNSHIP_TABLE_H
#define NOKIAINTERNSHIP_TABLE_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

struct table {
private:
    struct cell {
    public:
        std::string val;
        bool visited;
        int res;

        cell(std::string val);
    };

    std::string curLine;
    std::map<std::string, cell> myTable;

    std::vector<std::string> header, numeration, result;

    void parseHeader(std::string header);

    void parseLine(std::string num, std::string line);

    std::vector<std::string> reversePolishNotation(std::string expr);

    bool isOperation(char elem);

    void calc(cell &curCell);

    int priority(char elem);

    void parseTable(std::vector<std::string> table);

public:
    table(std::string &filename);

    table(std::vector<std::string> table);

    void compute();

    void buildAnswer();

    void printAnswer();

    std::vector<std::string> getResult();
};

#endif //NOKIAINTERNSHIP_TABLE_H
