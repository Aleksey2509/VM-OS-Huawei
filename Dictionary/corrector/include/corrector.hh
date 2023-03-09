#ifndef CORRECTOR_HH
#define CORRECTOR_HH

#include <memory>
#include <array>
#include <vector>
#include <algorithm>

#include "hashtable.hh"

namespace corrector
{

constexpr int MAX_LEV_DISTANCE = 2;
constexpr size_t MIN_WORD_LENGTH = 1;
constexpr size_t DICTIONARY_NUM = 30;

size_t lev_distance(const std::string& lhs, const std::string& rhs);

class Dictionary : public custom_containers::HashTable<std::string, size_t>
{
public:
    std::pair<const std::string*, size_t> FindMostSimilar(const std::string& word) const&;
};

//========================================================================================================================

struct IDataBaseHandler
{
    using InputIt = Dictionary::iterator;

    virtual int Open() = 0;
    virtual void Close() = 0;
    virtual int Read() = 0;
    virtual int Write(InputIt start, InputIt end) = 0;
    virtual ~IDataBaseHandler() = default;

    using iterator = std::vector<std::pair<std::string, size_t>>::iterator;
    using const_iterator = std::vector<std::pair<std::string, size_t>>::const_iterator;

    iterator begin() { return info_vec_.begin(); }
    iterator end() { return info_vec_.end(); }

    const_iterator begin() const { return info_vec_.begin(); }
    const_iterator end() const { return info_vec_.end(); }

    const_iterator cbegin() const { return info_vec_.cbegin(); }
    const_iterator cend() const { return info_vec_.cend(); }

protected:
    std::vector<std::pair<std::string, size_t>> info_vec_;
};

struct IInputTextHandler
{
    using iterator = std::vector<std::string>::iterator;
    using const_iterator = std::vector<std::string>::const_iterator;

    virtual ~IInputTextHandler() = default;

    virtual int Read(const std::string& file_name) = 0;
    virtual int Write(iterator start, iterator end, const std::string& file_name) = 0;

    iterator begin() { return word_vec_.begin(); }
    iterator end() { return word_vec_.end(); }

    const_iterator begin() const { return word_vec_.begin(); }
    const_iterator end() const { return word_vec_.end(); }

    const_iterator cbegin() const { return word_vec_.cbegin(); }
    const_iterator cend() const { return word_vec_.cend(); }

    size_t size() const { return word_vec_.size(); }

protected:
    std::vector<std::string> word_vec_;
};

//========================================================================================================================

struct ILogHandler // defines where log file is 
{
    virtual void LogReplacement(const std::string& replacement, const std::string& word) const = 0;
    virtual ~ILogHandler() = default;
};

//========================================================================================================================

class Corrector
{
public:

    Corrector(IDataBaseHandler* base_handler_ptr, IInputTextHandler* input_text_handler_ptr, ILogHandler* log_handler_ptr);
    Corrector(std::unique_ptr<IDataBaseHandler> base_handler_ptr, std::unique_ptr<IInputTextHandler> input_text_handler_ptr, std::unique_ptr<ILogHandler> log_handler_ptr);

    void Correct(const std::string& file_name);

private:

    const std::string* GetBestWord(const std::string& str) const;
    bool if_parallel = false;

public:
    using iterator = custom_containers::HashTable<std::string, size_t>::iterator;
    using const_iterator = custom_containers::HashTable<std::string, size_t>::const_iterator;

    void Learn(const std::string& file_name);

    void SaveWordBase();
    void setParallel(bool flag) { if_parallel = flag; };

    // LoadWordBase(const std::string& file_name) - loads database

private:

    void LoadWordBase();

    std::unique_ptr<IDataBaseHandler> database_handler_;
    std::unique_ptr<IInputTextHandler> text_handler_;
    std::unique_ptr<ILogHandler> log_handler_;
    std::vector<Dictionary> dictionary_vec_;
};

} // namespace corrector

#endif