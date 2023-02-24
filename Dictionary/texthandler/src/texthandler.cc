#include "texthandler.hh"
#include <utility>

namespace text_handlers
{
    InputTextHandler::InputTextHandler(const std::string& output_file_name) : output_file_{output_file_name}
    {}

    int InputTextHandler::Read(const std::string& file_name)
    {
        word_vec_.clear();
        std::fstream input_file;
        input_file.open(file_name);

        if (!input_file.good())
            return -1;

        while (input_file.good())
        {
            std::string tmp;
            input_file >> tmp;
            word_vec_.push_back(std::move(tmp));
        }
        input_file.close();

        return 0;
    }

    DataBaseHandler::DataBaseHandler(const std::string data_base_name) : data_base_name_(data_base_name)
    {}

    int DataBaseHandler::Read()
    {
        data_base_.open(DATA_BASE_FILE_NAME);
        if (!data_base_.good())
            return -1;

        while (data_base_.good())
        {
            std::string tmp_string;
            size_t tmp_string_frequency;
            data_base_ >> tmp_string;
            data_base_ >> tmp_string_frequency;

            info_vec_.emplace_back(std::move(tmp_string), std::move(tmp_string_frequency));
        }
        data_base_.close();

        return 0;
    } 

    int DataBaseHandler::Write(InputIt start, InputIt end)
    {
        data_base_.open(DATA_BASE_FILE_NAME, std::ios::app | std::ios::out);
        for (auto&& iter = start; iter != end; iter++)
        {
            data_base_ << iter->first << " " << iter->second << std::endl;
        }
        data_base_.close();

        return 0;
    }
}
