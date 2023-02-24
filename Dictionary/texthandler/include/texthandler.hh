#ifndef TEXTHANDLERS_HH
#define TEXTHANDLERS_HH

#include "corrector.hh"
#include <fstream>
#include <string>

namespace corrector
{

class InputTextHandler : public IInputTextHandler
{
public:

    InputTextHandler() = default;
    InputTextHandler(const std::string& output_file_name);
    InputTextHandler(const InputTextHandler& rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler(InputTextHandler&& rhs) noexcept = default;

    InputTextHandler& operator=(const InputTextHandler &rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler& operator=(InputTextHandler&& rhs) noexcept = default;

    int Read(const std::string& file_name) override;

private:
    std::fstream output_file_;
};

class DataBaseHandler : public IDataBaseHandler
{
public:

    static constexpr const char* DATA_BASE_FILE_NAME = STANDART_DATA_BASE;

    DataBaseHandler(const std::string data_base_name = DATA_BASE_FILE_NAME);
    DataBaseHandler(const DataBaseHandler& rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler(DataBaseHandler&& rhs) noexcept = default;

    DataBaseHandler& operator=(const DataBaseHandler &rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler& operator=(DataBaseHandler&& rhs) noexcept = default;

    int Read() override;
    int Write(InputIt start, InputIt end) override;

private:
    std::string data_base_name_;
    std::fstream data_base_;
};

}


#endif