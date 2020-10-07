#include "gtest/gtest.h"
#include "table.h"

TEST(table, table_ops_Test) {
    table myTable({",A,B,Cell",
                   "1,1,0,1",
                   "2,2,=A1+Cell30,=A1-B2*Cell30",
                   "30,0,=B1+A1,5"});
    myTable.compute();
    myTable.buildAnswer();
    std::vector<std::string> tmp = {",A,B,Cell",
                                    "1,1,0,1",
                                    "2,2,6,-29",
                                    "30,0,1,5"};
    ASSERT_EQ(myTable.getResult(), tmp);
}


TEST(table, table_ops2_Test) {
    table myTable({",A,B,Cell",
                   "2,=Cell1+B1,=A2+Cell1,=A2+B2",
                   "30,=B2*Cell30+Cell1,=B2/B1*Cell1,=B30*A2",
                   "1,1,2,=A1+B1",});
    myTable.compute();
    myTable.buildAnswer();
    std::vector<std::string> tmp = {",A,B,Cell",
                                    "2,5,8,13",
                                    "30,483,12,60",
                                    "1,1,2,3",};
    ASSERT_EQ(myTable.getResult(), tmp);
}

TEST(table, table_divide_by_zero_err_Test) {
    table myTable({",A,B,Cell",
                   "1,1,0,1",
                   "2,2,=A1+Cell30/B1,0",
                   "30,0,=B1+A1,5"});
    EXPECT_THROW({
                     myTable.compute();
                 }, std::runtime_error);
}

TEST(table, table_cycle_reference_err_Test) {
    table myTable({",A,B,Cell",
                   "1,1,0,1",
                   "2,2,=A1+Cell30,0",
                   "30,0,=B1+A1,=B2"});
    EXPECT_THROW({
                     myTable.compute();
                 }, std::runtime_error);
}

TEST(table, table_unknown_cell_err_Test) {
    table myTable({",A,B,Cell",
                   "1,1,0,1",
                   "2,2,=A1+Cell30,=NewCell",
                   "30,0,=B1+A1,5"});
    EXPECT_THROW({
                     myTable.compute();
                 }, std::runtime_error);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}