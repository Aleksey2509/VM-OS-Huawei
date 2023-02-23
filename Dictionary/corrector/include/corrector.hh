#ifndef CORRECTOR_HH
#define CORRECTOR_HH

#include <memory>
#include <array>
#include <string_view>
#include <algorithm>

#include "hashtable.hh"

namespace corrector
{

constexpr size_t MAX_LEV_DISTANCE = 2;
constexpr size_t DICTIONARY_NUM = 30;

size_t lev_distance(const std::string_view& lhs, const std::string_view& rhs);

class Dictionary : public custom_containers::HashTable<std::string, size_t>
{
public:
    const std::string* FindMostSimilar(const std::string& word) const&;
};

//========================================================================================================================

struct IDataBaseHandler
{
    using InputIt = Dictionary::iterator;

    virtual int Read() = 0;
    virtual int Write(InputIt start, InputIt end) = 0;

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
    virtual int Read(const std::string& file_name) = 0;

    using iterator = std::vector<std::string>::iterator;
    using const_iterator = std::vector<std::string>::const_iterator;

    iterator begin() { return word_vec_.begin(); }
    iterator end() { return word_vec_.end(); }

    const_iterator begin() const { return word_vec_.begin(); }
    const_iterator end() const { return word_vec_.end(); }

    const_iterator cbegin() const { return word_vec_.cbegin(); }
    const_iterator cend() const { return word_vec_.cend(); }

protected:
    std::vector<std::string> word_vec_;
};

//========================================================================================================================

struct ILogHandler // defines where log file is 
{
    virtual void LogReplacement(const std::string& replacement, const std::string& word) = 0;
};

//========================================================================================================================

class Corrector
{
public:

    void Correct(const std::string& file_name);

private:

    void LogReplacement(const std::string& replacement, const std::string& iter);
    const std::string* GetBestWord(const std::string& str) const;

public:
    using iterator = custom_containers::HashTable<std::string, size_t>::iterator;
    using const_iterator = custom_containers::HashTable<std::string, size_t>::const_iterator;

    void Learn(const std::string& file_name);
    void SaveWordBase();

private:

    std::vector<Dictionary> dictionary_vec_;
    std::unique_ptr<IDataBaseHandler> database_handler_;
    std::unique_ptr<IInputTextHandler> text_handler_;
    std::unique_ptr<ILogHandler> log_handler_;
};

} // namespace corrector

#endif