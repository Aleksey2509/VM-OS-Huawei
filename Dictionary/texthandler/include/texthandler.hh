#ifndef TEXTHANDLERS_HH
#define TEXTHANDLERS_HH

#include "corrector.hh"
#include <fstream>
#include <string>

namespace text_handlers
{

class InputTextHandler : public corrector::IInputTextHandler
{
public:

    InputTextHandler() = default;
    InputTextHandler(const std::string& output_file_name);
    InputTextHandler(const InputTextHandler& rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler(InputTextHandler&& rhs) noexcept = delete;

    InputTextHandler& operator=(const InputTextHandler &rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler& operator=(InputTextHandler&& rhs) noexcept = delete;

    int Read(const std::string& file_name) override;
    int Write(iterator start, iterator end, const std::string& file_name);

public: // for debug
    void ProcessWord(std::string& word);
    const std::string delimiters = {';', ' ', ',', '-', '\n', '!', '?'};

    std::fstream output_file_;
    std::string text_buffer;
};

class DataBaseHandler : public corrector::IDataBaseHandler
{
public:

    static constexpr const char* DATA_BASE_FILE_NAME = STANDART_DATA_BASE;

    DataBaseHandler(const std::string data_base_name = DATA_BASE_FILE_NAME);
    DataBaseHandler(const DataBaseHandler& rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler(DataBaseHandler&& rhs) noexcept = default;

    DataBaseHandler& operator=(const DataBaseHandler &rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler& operator=(DataBaseHandler&& rhs) noexcept = default;

    int Open() override;
    void Close() override;
    int Read() override;
    int Write(InputIt start, InputIt end) override;

private:
    std::string data_base_name_;
    std::fstream data_base_;
};

class Logger : public corrector::ILogHandler // maybe do so that the log file is open while Logger is alive
{
public:
    Logger() = default;
    Logger(const char* log_file_name);
    void LogReplacement(const std::string& replacement, const std::string& word) override;

private:
    const char* log_file_name_ = DEFAULT_LOG_FILE_NAME;
};

}


#endif