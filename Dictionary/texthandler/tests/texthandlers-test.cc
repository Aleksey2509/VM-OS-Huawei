#include <gtest/gtest.h>

#include "texthandler.hh"
#include <algorithm>

TEST(InputTextHander, BasicReading)
{
    text_handlers::InputTextHandler test_subj(TEST_FILE);
    test_subj.Read(TEST_FILE);
    std::vector<std::string> test_file_expected_content = {"audible", "crazy", "worthless", "dumb",
                                                            "damn", "skip", "this", "party", "quick"};

    test_subj.Write(test_file_expected_content.begin(), test_file_expected_content.end(), TEST_FILE);

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
    text_handlers::InputTextHandler test_subj(TEST_FILE2);
    test_subj.Read(TEST_FILE2);
    std::vector<size_t> hashes;
    std::list<std::pair<std::string, size_t>> lst;
    std::size_t rand_freq = 0;

    for (auto&& iter : test_subj)
    {
        rand_freq += 1;
        lst.push_back({iter, rand_freq});
    }

    text_handlers::DataBaseHandler data_base{TEST_DATA_BASE_FILE};

    EXPECT_EQ(data_base.Read(), 0);
    auto iter_data_base = data_base.begin();
    auto iter_lst = lst.begin();
    for (; (iter_data_base != data_base.end()) && (iter_lst != lst.begin()); ++iter_data_base, ++iter_lst)
    {
        EXPECT_EQ(*iter_data_base == *iter_lst, true);
    }

    EXPECT_EQ(data_base.Write(lst.begin(), lst.end()), 0);

    data_base.Close();

}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}