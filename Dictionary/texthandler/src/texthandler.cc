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

        while(buffer_word_end != text_buffer.end())
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

        auto&& underlying_buf = data_base_.rdbuf();
        std::size_t buffer_size = underlying_buf->pubseekoff (0, data_base_.end, data_base_.in);
        underlying_buf->pubseekpos (0,data_base_.in);

        std::string data_base_buffer;
        data_base_buffer.reserve(buffer_size);
        underlying_buf->sgetn(data_base_buffer.data(), buffer_size);

        data_base_.close();

        char* char_buf = data_base_buffer.data();

        auto&& string_iter = data_base_buffer.begin();
        auto&& string_iter_end = data_base_buffer.end();

        size_t word_len = 0;
        for(;string_iter != string_iter_end; string_iter += word_len + 9)
        {
            std::string tmp_string;
            size_t tmp_string_frequency;

            auto&& word_len = std::find(string_iter, string_iter_end, '\0') - string_iter + 1;

            tmp_string.reserve(word_len);
            tmp_string.assign(char_buf, word_len);
            char_buf += word_len + 1;
            tmp_string_frequency = *reinterpret_cast<size_t*>(char_buf);
            char_buf += sizeof(size_t);
        }

        return 0;
    } 

    int DataBaseHandler::Write(InputIt start, InputIt end)
    {
        std::stringstream output;

        for (auto&& iter = start; iter != end; iter++)
        {
            auto&& tmp_string_frequency = start->second;

            output.write(reinterpret_cast<char*>(const_cast<char*>(start->first.c_str())), start->first.size());
            output.write(reinterpret_cast<char*>(&start->second), sizeof(size_t));
        }

        if (!data_base_.is_open())
        {
            auto&& open_result = Open();
            if (open_result == -1)
                return open_result;
        }

        data_base_ << output.str();

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
