#include "texthandler.hh"

#include <utility>
#include <memory>
#include <sstream>

#include <iostream>

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
        // init buffer part
        word_vec_.clear();
        text_buffer.clear();

        std::ifstream input_file;
        input_file.open(file_name);

        if (!input_file.good())
            return -1;

        std::stringstream buf;
        buf << input_file.rdbuf();
        text_buffer = buf.str();

        input_file.close();
        // init buffer end

        // parse part
        auto&& if_delimiter = [del = delimiters](char ch){ return del.find(ch) != del.npos; };

        auto buffer_word_begin = std::find_if_not(text_buffer.begin(), text_buffer.end(), if_delimiter);
        auto buffer_word_end = std::find_if(buffer_word_begin, text_buffer.end(), if_delimiter);

        while(buffer_word_begin != text_buffer.end())
        {
            word_vec_.push_back({buffer_word_begin, buffer_word_end});

            buffer_word_begin = std::find_if_not(buffer_word_end, text_buffer.end(), if_delimiter);
            buffer_word_end = std::find_if(buffer_word_begin, text_buffer.end(), if_delimiter);
        }

        return 0;
    }

    int InputTextHandler::Write(iterator start, iterator end, const std::string& file_name)
    {
        std::ofstream output_file;
        std::stringstream output;

        auto&& if_delimiter = [del = delimiters](char ch){ return del.find(ch) != del.npos; };

        auto delims_begin = std::find_if(text_buffer.begin(), text_buffer.end(), if_delimiter);
        auto delims_end = std::find_if_not(delims_begin, text_buffer.end(), if_delimiter);

        for (auto iter = start; iter != end; iter++)
        {
            output << *iter;
            output << std::string{delims_begin, delims_end};

            delims_begin = std::find_if(delims_end, text_buffer.end(), if_delimiter);
            delims_end = std::find_if_not(delims_begin, text_buffer.end(), if_delimiter);
        }


        output_file.open(file_name);

        if (!output_file.good())
            return -1;

        output_file << output.str();
        output_file.close();

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

        std::stringstream buf;
        buf << data_base_.rdbuf();
        data_base_.close();

        std::string text_buffer = buf.str();

        char* actual_buf = text_buffer.data();
        char* actual_buf_end = actual_buf + text_buffer.size();

        size_t word_len = 0;
        size_t stupid = 0;
        for(; actual_buf != actual_buf_end;)
        {
            std::string tmp_string;
            size_t tmp_string_frequency;

            auto word_len = std::find(actual_buf, actual_buf_end, '\0') - actual_buf;

            tmp_string.reserve(word_len);
            tmp_string.assign(actual_buf, word_len);
            actual_buf += word_len + 1;

            tmp_string_frequency = *reinterpret_cast<size_t*>(actual_buf);
            actual_buf += sizeof(size_t);

            info_vec_.push_back({std::move(tmp_string), std::move(tmp_string_frequency)});
        }

        return 0;
    } 

    int DataBaseHandler::Write(InputIt start, InputIt end)
    {
        std::stringstream output;

        for (auto&& iter = start; iter != end; iter++)
        {
            auto&& tmp_string_frequency = start->second;

            output.write(reinterpret_cast<char*>(const_cast<char*>(start->first.c_str())), start->first.size() + 1);
            output.write(reinterpret_cast<char*>(&start->second), sizeof(size_t));
        }

        if (!data_base_.is_open())
        {
            auto&& open_result = Open();
            if (open_result == -1)
                return open_result;
        }

        // std::cout << "writng" << output.str() << std::endl;
        data_base_ << output.str();
        // data_base_ << "ended";

        return 0;
    }

    Logger::Logger(const char* log_file_name) : log_file_name_{log_file_name}
    {}

    void Logger::LogReplacement(const std::string& replacement, const std::string& word) const
    {
        std::fstream log_file;
        log_file.open(log_file_name_, std::ios::out | std::ios::app);

        log_file << "replaced " << word << " with " << replacement << std::endl;
        log_file.close();
    }
}
