#include "corrector.hh"

namespace corrector
{
    size_t lev_distance(const std::string_view& lhs, const std::string_view& rhs)
    {
        if (lhs.empty())
        {
            return rhs.size();
        }
        if (rhs.empty())
        {
            return lhs.size();
        }

        std::string_view trimed_lhs{lhs};
        std::string_view trimed_rhs{rhs};

        trimed_lhs.remove_prefix(1);
        trimed_rhs.remove_prefix(1);

        if (lhs[0] == rhs[0])
        {
            return lev_distance(trimed_lhs, trimed_rhs);
        }

        return 1 + std::min({lev_distance(trimed_lhs, trimed_rhs), lev_distance(lhs, trimed_rhs), lev_distance(trimed_lhs, rhs)});
    }



    const std::string* Dictionary::FindMostSimilar(const std::string& word) const&
    {
        const std::string* most_similar = nullptr;
        size_t min_dist = MAX_LEV_DISTANCE + 1;
        size_t max_frequency = 0;

        for (auto&& iter : *this)
        {
            if (iter.key == word)
                return std::addressof(iter.key);

            auto&& cur_dist = lev_distance(word, iter.key);

            if ((cur_dist < min_dist) || ((cur_dist == min_dist) && (iter.elem > max_frequency))) 
            {
                min_dist = cur_dist;
                most_similar = std::addressof(iter.key);
                max_frequency = iter.elem;
            }
        }

        return most_similar;
    }

    void Corrector::Correct(const std::string& file_name)
    {
        text_handler_->Read(file_name);
        for (auto&& iter : *text_handler_)
        {
            const std::string* replacement = GetBestWord(iter);
            if (replacement && *replacement != iter)
                LogReplacement(*replacement, iter);
        }
    }

    void Corrector::LogReplacement(const std::string& replacement, const std::string& iter)
    {
        log_handler_->LogReplacement(replacement, iter);
    }

    const std::string* Corrector::GetBestWord(const std::string& str) const
    {
        constexpr size_t maxReplacementWordAmount = 2 * MAX_LEV_DISTANCE + 1;
        std::array<const std::string*, maxReplacementWordAmount> replacements;

        auto&& size = str.size();
        for (size_t i = size - MAX_LEV_DISTANCE; i < size + MAX_LEV_DISTANCE + 1; ++i)
        {
            replacements[i - size + MAX_LEV_DISTANCE] = dictionary_vec_[i - 1].FindMostSimilar(str);
        }

        constexpr size_t zeroLevDistanceIndex = MAX_LEV_DISTANCE;

        if (replacements[zeroLevDistanceIndex] != nullptr)
            return replacements[zeroLevDistanceIndex];

        for (int i = 1; i < MAX_LEV_DISTANCE + 1; ++i)
        {
            if (replacements[zeroLevDistanceIndex + i] != nullptr)
                return replacements[zeroLevDistanceIndex + i];

            if (replacements[zeroLevDistanceIndex - i] != nullptr)
                return replacements[zeroLevDistanceIndex - i];
        }

        return nullptr;
    }

    void Corrector::Learn(const std::string& file_name)
    {
        database_handler_->Read();

        for (auto&& iter : *database_handler_)
        {
            auto&& word_size = iter.first.size();
            if (word_size < DICTIONARY_NUM)
            {
                dictionary_vec_[word_size - 1][iter.first] += iter.second;
            }
        }
    }

    void Corrector::SaveWordBase()
    {
        for (auto&& dict_iter = dictionary_vec_.begin(); dict_iter != dictionary_vec_.end(); dict_iter++)
        {
            database_handler_->Write(dict_iter->begin(), dict_iter->end());
        }
    }



} // namespace corrector
