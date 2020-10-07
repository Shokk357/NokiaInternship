#include <string>
#include "table.h"

using namespace std;

int main(int argc, char *argv[]) {
    string filename = argv[1];
    table myTable(filename);
    myTable.compute();
    myTable.buildAnswer();
    myTable.printAnswer();
    return 0;
}
