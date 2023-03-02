#include <gtest/gtest.h>

#include "corrector.hh"
#include "texthandler.hh"

TEST(CorrectorSuite, DefaultConstruct)
{
    corrector::Corrector T9{std::make_unique<text_handlers::DataBaseHandler>(TEST_DATA_BASE_FILE),
                                 std::make_unique<text_handlers::InputTextHandler>(),
                                 std::make_unique<text_handlers::Logger>()};

    T9.Learn(TEST_LEARN_FILE);
    T9.SaveWordBase();

}

TEST(CorrectorSuite, BasicReplacement)
{
    corrector::Corrector T9{std::make_unique<text_handlers::DataBaseHandler>(TEST_DATA_BASE_FILE),
                                 std::make_unique<text_handlers::InputTextHandler>(),
                                 std::make_unique<text_handlers::Logger>()};

    T9.Correct(TEST_WRONG_FILE);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}