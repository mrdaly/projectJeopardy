#include "Clue.h"

using namespace jeopardy;

Clue::Clue(const std::string& clue, const std::string& answer, int pointValue)
: clue_(clue), answer_(answer), pointValue_(pointValue), isAnswered_(false)
{

}

std::string Clue::getClue() const noexcept
{
    return clue_;
}

std::string Clue::getAnswer() const noexcept
{
    return answer_;
}

int Clue::getPointValue() const noexcept
{
    return pointValue_;
}

bool Clue::isAnswered() const noexcept
{
    return isAnswered_;
}

void Clue::setToAnswered() noexcept
{
    isAnswered_ = true;
}

