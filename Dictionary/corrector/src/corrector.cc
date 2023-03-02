#include "corrector.hh"

#include <iostream>

#include <numeric>

namespace corrector
{
    size_t lev_distance(const std::string& lhs, const std::string& rhs)
    {
        if (lhs.size() > rhs.size())
        {
            return lev_distance(rhs, lhs);
        }

        size_t min_size = lhs.size();
        size_t max_size = rhs.size();

        std::vector<size_t> lev_dist(min_size + 1);
        std::iota(lev_dist.begin(), lev_dist.end(), 0);

        for (size_t j = 1; j <= max_size; ++j)
        {
            size_t previous_diagonal = lev_dist[0];
            size_t previous_diagonal_save = 0;
            lev_dist[0]++;

            for (size_t i = 1; i <= min_size; ++i)
            {
                previous_diagonal_save = lev_dist[i];
                if (lhs[i - 1] == rhs[j - 1])
                {
                    lev_dist[i] = previous_diagonal;
                }
                else
                {
                    lev_dist[i] = std::min({lev_dist[i - 1], lev_dist[i], previous_diagonal}) + 1;
                }
                previous_diagonal = previous_diagonal_save;
            }
        }

        return lev_dist[min_size];
    }



    const std::string* Dictionary::FindMostSimilar(const std::string& word) const&
    {
        const std::string* most_similar = nullptr;
        size_t min_dist = MAX_LEV_DISTANCE;
        size_t max_frequency = 0;


        for (auto&& iter : *this)
        {
            // std::cout << "checking: " << iter.first << " " << word << std::endl;
            if (iter.first == word)
                return std::addressof(iter.first);

            auto&& cur_dist = lev_distance(word, iter.first);

            if ((cur_dist < min_dist) || ((cur_dist == min_dist) && (iter.second > max_frequency))) 
            {
                min_dist = cur_dist;
                most_similar = std::addressof(iter.first);
                max_frequency = iter.second;
            }
        }

        return most_similar;
    }

    Corrector::Corrector(IDataBaseHandler* base_handler_ptr, IInputTextHandler* input_text_handler_ptr, ILogHandler* log_handler_ptr) :
                         database_handler_(base_handler_ptr), text_handler_(input_text_handler_ptr), log_handler_(log_handler_ptr),
                         dictionary_vec_(DICTIONARY_NUM)
    {
        LoadWordBase();
    }

    Corrector::Corrector(std::unique_ptr<IDataBaseHandler> base_handler_ptr, std::unique_ptr<IInputTextHandler> input_text_handler_ptr, std::unique_ptr<ILogHandler> log_handler_ptr):
              database_handler_(std::move(base_handler_ptr)), text_handler_(std::move(input_text_handler_ptr)), log_handler_(std::move(log_handler_ptr)),
              dictionary_vec_(DICTIONARY_NUM)
    {
        LoadWordBase();
    }

    void Corrector::LoadWordBase()
    {
        database_handler_->Open();
        database_handler_->Read();

        for (auto&& iter : *database_handler_)
        {
            // std::cout << iter.first << " " << iter.second << std::endl;
            auto&& word_size = iter.first.size();
            if (word_size < DICTIONARY_NUM)
            {
                // std::cout << word_size  << std::endl;
                dictionary_vec_[word_size - 1][iter.first] += iter.second;
            }
        }

        database_handler_->Close();
    }

    void Corrector::Correct(const std::string& file_name)
    {
        text_handler_->Read(file_name);
        for (auto&& iter : *text_handler_)
        {
            const std::string* replacement = GetBestWord(iter);
            if (replacement && (*replacement != iter))
                log_handler_->LogReplacement(*replacement, iter);
        }
    }

    const std::string* Corrector::GetBestWord(const std::string& str) const
    {
        // std::cout << "trying to correct " << str << std::endl;
        constexpr size_t max_replacement_word_amount = 2 * MAX_LEV_DISTANCE + 1;
        std::array<const std::string*, max_replacement_word_amount> replacements{nullptr};

        auto&& size = str.size();
        for (size_t i = size - MAX_LEV_DISTANCE; i < size + MAX_LEV_DISTANCE + 1; ++i)
        {
            replacements[i - size + MAX_LEV_DISTANCE] = dictionary_vec_[i - 1].FindMostSimilar(str);
        }

        constexpr size_t zero_lev_distance_index = MAX_LEV_DISTANCE;

        if (replacements[zero_lev_distance_index] != nullptr)
        {
            // std::cout << "it is wrongly written: " << str << " replacing with " << *replacements[zero_lev_distance_index] << std::endl;
            return replacements[zero_lev_distance_index];
        }

        for (int i = 1; i < MAX_LEV_DISTANCE + 1; ++i)
        {
            if (replacements[zero_lev_distance_index + i] != nullptr)
                return replacements[zero_lev_distance_index + i];

            if (replacements[zero_lev_distance_index - i] != nullptr)
                return replacements[zero_lev_distance_index - i];
        }

        return nullptr;
    }

    void Corrector::Learn(const std::string& file_name)
    {
        text_handler_->Read(file_name);
        for (auto&& iter : *text_handler_)
        {
            // std::cout << "loading " << iter << " hash = " << std::hash<std::string>{}(iter)<< std::endl;
            auto&& word_size = iter.size();
            if ((word_size > MIN_WORD_LENGTH) && (word_size < DICTIONARY_NUM))
            {
                // std::cout << "was " << dictionary_vec_[word_size - 1][iter] << std::endl;
                dictionary_vec_[word_size - 1][iter] += 1;
                // std::cout << "now " << dictionary_vec_[word_size - 1][iter] << std::endl;
            }
        }
    }

    void Corrector::SaveWordBase()
    {
        database_handler_->Open();
        for (auto&& dict_iter = dictionary_vec_.begin(); dict_iter != dictionary_vec_.end(); dict_iter++)
        {
            // std::cout << "working with dict " << i << "empty: " << std::boolalpha << (dict_iter->begin() == dict_iter->end()) << std::endl;
            database_handler_->Write(dict_iter->begin(), dict_iter->end());
        }
        database_handler_->Close();
    }



} // namespace corrector
