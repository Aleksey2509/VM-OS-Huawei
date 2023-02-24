#include <gtest/gtest.h>

#include "texthandler.hh"
#include <algorithm>

TEST(InputTextHander, BasicReading)
{
    corrector::InputTextHandler test_subj(TEST_FILE);
    test_subj.Read(TEST_FILE);
    std::vector<std::string> test_file_expected_content = {"audible", "crazy", "worthless", "dumb",
                                                            "damn", "skip", "this", "party", "quick"};

    auto&& expected_iter = test_file_expected_content.begin();
    for (auto&& iter = test_subj.begin(); iter != test_subj.end(); ++iter, ++expected_iter)
    {
        EXPECT_EQ(*iter, *expected_iter);
    }

    test_subj.Read(TEST_FILE2);
    std::vector<std::string> test_file2_expected_content = { "damn", "skip", "this", "party", "quick",
                                                            "audible", "crazy", "worthless", "dumb",
                                                            "some", "new", "information" };
    auto&& expected_iter2 = test_file2_expected_content.begin();
    for (auto&& iter = test_subj.begin(); iter != test_subj.end(); ++iter, ++expected_iter2)
    {
        EXPECT_EQ(*iter, *expected_iter2);
    }


    std::cout << std::endl;
}

TEST(DataBaseHander, BasicReadingWriting)
{
    corrector::InputTextHandler test_subj(TEST_FILE);
    test_subj.Read(TEST_FILE);
    std::vector<size_t> hashes;
    std::list<std::pair<std::string, size_t>> lst;

    for (auto&& iter : test_subj)
    {
        lst.push_back({iter, std::hash<std::string>{}(iter)});
    }

    corrector::DataBaseHandler data_base;
    data_base.Write(lst.begin(), lst.end());

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}