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
    InputTextHandler(const std::string& file_name);
    InputTextHandler(const InputTextHandler& rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler(InputTextHandler&& rhs) noexcept = default;

    InputTextHandler& operator=(const InputTextHandler &rhs) = delete; // because std::fstream is uncopyable
    InputTextHandler& operator=(InputTextHandler&& rhs) noexcept = default;

    int Read(const std::string& file_name) override;

private:
    std::fstream file;
};

class DataBaseHandler : public IDataBaseHandler
{
public:

    static constexpr const char* DATA_BASE_FILE_NAME = "database";

    DataBaseHandler();
    DataBaseHandler(const DataBaseHandler& rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler(DataBaseHandler&& rhs) noexcept = default;

    DataBaseHandler& operator=(const DataBaseHandler &rhs) = delete; // because std::fstream is uncopyable
    DataBaseHandler& operator=(DataBaseHandler&& rhs) noexcept = default;

    int Read() override;
    int Write(InputIt start, InputIt end) override;

private:
    std::fstream file;
};

}


#endif