#include "corrector.hh"

#include <iostream>

#include <numeric>
#include <future>

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
                if (lhs[i] == rhs[j])
                {
                    lev_dist[i] = previous_diagonal;
                }
                else
                {
                    lev_dist[i] = std::min({lev_dist[i], lev_dist[i], previous_diagonal}) + 1;
                }
                previous_diagonal = previous_diagonal_save;
            }
        }

        return lev_dist[min_size];
    }



    std::pair<const std::string*, size_t> Dictionary::FindMostSimilar(const std::string& word) const&
    {
        const std::string* most_similar = nullptr;
        size_t min_dist = MAX_LEV_DISTANCE;
        size_t max_frequency = 0;


        for (auto&& iter : *this)
        {
            if (iter.first == word)
                return {std::addressof(iter.first), iter.second};

            auto&& cur_dist = lev_distance(word, iter.first);

            if ((cur_dist < min_dist) || ((cur_dist == min_dist) && (iter.second > max_frequency))) 
            {
                min_dist = cur_dist;
                most_similar = std::addressof(iter.first);
                max_frequency = iter.second;
            }
        }

        return {most_similar, max_frequency};
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
            auto&& word_size = iter.first.size();
            if ((word_size > MIN_WORD_LENGTH) && (word_size < DICTIONARY_NUM))
            {
                dictionary_vec_[word_size][iter.first] += iter.second;
            }
        }

        database_handler_->Close();
    }

    void Corrector::Correct(const std::string& file_name)
    {
        text_handler_->Read(file_name);
        if (!if_parallel)
        {
            for (const auto iter : *text_handler_)
            {
                
                const std::string* replacement = GetBestWord(iter);
                if (!replacement)
                    log_handler_->LogReplacement("nothing", iter);
                if (replacement && (*replacement != iter))
                    log_handler_->LogReplacement(*replacement, iter);
            }
        }
        else
        {
            auto&& work_for_thread = [this](IInputTextHandler::const_iterator begin, IInputTextHandler::const_iterator end)
            {
                std::vector<std::pair<const std::string*, const std::string*>> replacements;
                for (auto iter = begin; iter != end; iter++)
                {
                    const std::string* replacement = GetBestWord(*iter);
                    replacements.push_back({replacement, std::addressof(*iter)});
                }

                return replacements;
            };
            using thread_return_type = std::vector<std::pair<const std::string*, const std::string*>>;

            auto word_vec_size = text_handler_->size();

            int num_of_threads = std::thread::hardware_concurrency();
            std::vector<std::future<thread_return_type>>  handle_vector;

            for (auto i = 0; i < num_of_threads - 1; i++)
            {
                handle_vector.push_back(std::async(std::launch::async, work_for_thread, 
                    text_handler_->cbegin() + i * word_vec_size / num_of_threads, text_handler_->cbegin() + (i + 1) * word_vec_size / num_of_threads));
            }

            handle_vector.push_back(std::async(std::launch::async, work_for_thread, 
                text_handler_->cbegin() + word_vec_size * (num_of_threads - 1) / num_of_threads, text_handler_->cend()));

            for (int i = 0; i < handle_vector.size(); i++)
            {
                handle_vector[i].wait();
                auto&& word_vector = handle_vector[i].get();
                for (auto&& word_iter : word_vector)
                {
                    if (!word_iter.first)
                        log_handler_->LogReplacement("nothing", *word_iter.second);
                    if (word_iter.first && (*word_iter.first != *word_iter.second))
                        log_handler_->LogReplacement(*word_iter.first, *word_iter.second);
                }
            }
        }

    }

    const std::string* Corrector::GetBestWord(const std::string& str) const
    {
        constexpr int max_replacement_word_amount = 2 * MAX_LEV_DISTANCE + 1;
        std::array<std::pair<const std::string*, size_t>, max_replacement_word_amount> replacements{};
        constexpr size_t zero_lev_distance_index = MAX_LEV_DISTANCE;

        auto&& size = str.size();
        if (size <= MAX_LEV_DISTANCE)
            return nullptr;

        for (size_t i = size - MAX_LEV_DISTANCE; i < size + MAX_LEV_DISTANCE + 1; ++i)
        {
            replacements[i - size + MAX_LEV_DISTANCE] = dictionary_vec_[i].FindMostSimilar(str);
        }


        if ((replacements[zero_lev_distance_index].first != nullptr))
        {
            return replacements[zero_lev_distance_index].first;
        }

        auto&& better_word_cmp =  [](std::pair<const std::string*, size_t> lhs, std::pair<const std::string*, size_t> rhs){return lhs.second < rhs.second;};

        auto better_word = std::max_element(replacements.begin(), replacements.end(), better_word_cmp);
        return better_word->first;

        return nullptr;
    }

    void Corrector::Learn(const std::string& file_name)
    {
        text_handler_->Read(file_name);
        for (auto&& iter : *text_handler_)
        {
            auto&& word_size = iter.size();
            if ((word_size > MIN_WORD_LENGTH) && (word_size < DICTIONARY_NUM))
            {
                dictionary_vec_[word_size][iter] += 1;
            }
        }
    }

    void Corrector::SaveWordBase()
    {
        database_handler_->Open();
        for (auto dict_iter = dictionary_vec_.begin(); dict_iter != dictionary_vec_.end(); dict_iter++)
        {
            database_handler_->Write(dict_iter->begin(), dict_iter->end());
        }
        database_handler_->Close();
    }



} // namespace corrector
