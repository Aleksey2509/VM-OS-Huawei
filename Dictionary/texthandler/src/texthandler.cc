#include "texthandler.hh"
#include <utility>

namespace text_handlers
{
    InputTextHandler::InputTextHandler(const std::string& output_file_name) : output_file_{output_file_name}
    {}

    void InputTextHandler::ProcessWord(std::string& word)
    {
        word.erase(std::remove_if(word.begin(), word.end(), [](char ch){return !std::isalpha(ch);}), word.end());
    }

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
            ProcessWord(tmp);
            if (!tmp.empty())
            {
                word_vec_.push_back(std::move(tmp));
            }
        }
        input_file.close();

        return 0;
    }

    DataBaseHandler::DataBaseHandler(const std::string data_base_name) : data_base_name_(data_base_name)
    {}

    int DataBaseHandler::Open()
    {
        data_base_.open(data_base_name_);
        if (!data_base_.good())
            return -1;

        return 0;
    }
    void DataBaseHandler::Close()
    {
        data_base_.close();
    }

    int DataBaseHandler::Read()
    {
        if (!data_base_.is_open())
        {
            auto&& open_result = Open();
            if (open_result == -1)
                return open_result;
        }

        while (data_base_.good())
        {
            std::string tmp_string;
            size_t tmp_string_frequency;
            data_base_ >> tmp_string;
            if (!data_base_.good())
                break;
            data_base_ >> tmp_string_frequency;

            info_vec_.emplace_back(std::move(tmp_string), std::move(tmp_string_frequency));
        }

        return 0;
    } 

    int DataBaseHandler::Write(InputIt start, InputIt end)
    {
        if (!data_base_.is_open())
        {
            auto&& open_result = Open();
            if (open_result == -1)
                return open_result;
        }

        for (auto&& iter = start; iter != end; iter++)
        {
            data_base_ << iter->first << " " << iter->second << std::endl;
        }

        return 0;
    }

    Logger::Logger(const char* log_file_name) : log_file_name_{log_file_name}
    {}

    void Logger::LogReplacement(const std::string& replacement, const std::string& word)
    {
        std::fstream log_file;
        log_file.open(log_file_name_, std::ios::out | std::ios::app);

        log_file << "replaced " << word << " with " << replacement << std::endl;
        log_file.close();
    }
}
