#include "Category.h"
#include <stdexcept>

using namespace jeopardy;

Category::Category(const std::string& name, const std::vector<Clue>& clues)
: name_(name), clues_(clues)
{

}

std::string Category::getName() const noexcept
{
    return name_;
}

Clue& Category::getClue(int pointValue)
{
    //loop through clues vector to find the one with the given point value
    for (auto it = clues_.begin(); it != clues_.end(); it++)
    {
        if (it->getPointValue() == pointValue)
        {
            return *it;
        }
    }

    //throw exception if there is none
    throw std::domain_error("No clue with the given point value");
}

const std::vector<Clue>& Category::getClues() const noexcept
{
    return clues_;
}

