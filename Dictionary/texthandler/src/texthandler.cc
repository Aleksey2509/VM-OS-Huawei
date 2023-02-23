#include "texthandler.hh"
#include <utility>

namespace corrector
{
    InputTextHandler::InputTextHandler(const std::string& file_name) : file{file_name}
    {}

    int InputTextHandler::Read(const std::string& file_name)
    {
        std::fstream file{file_name};

        if (!file.good())
            return -1;

        while (file.good())
        {
            std::string tmp;
            file >> tmp;
            word_vec_.push_back(std::move(tmp));
        }
        file.close();

        return 0;
    }

    DataBaseHandler::DataBaseHandler() : file{DATA_BASE_FILE_NAME}
    {}

    int DataBaseHandler::Read()
    {
        if (!file.good())
            return -1;

        while (file.good())
        {
            std::string tmp_string;
            size_t tmp_string_frequency;
            file >> tmp_string;
            file >> tmp_string_frequency;

            info_vec_.emplace_back(std::move(tmp_string), std::move(tmp_string_frequency));
        }
        file.close();

        return 0;
    }

    int DataBaseHandler::Write(InputIt start, InputIt end)
    {
        for (auto&& iter = start; iter != end; iter++)
        {
            file << iter->key << " " << iter->elem << std::endl;
        }

        return 0;
    }
}
