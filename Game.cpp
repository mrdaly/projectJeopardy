#include "Game.h"
#include <sstream>
#include <iomanip>
#include <string.h>

using std::left;
using std::right;
using std::setw;
using std::setfill;
using std::endl;

using namespace jeopardy;

Game::Game(const std::vector<Category>& categories)
: categories_(categories)
{

}

std::string Game::getClue(const std::string& categoryName, int pointValue)
{
    //loop through the categories to find the right one then get the clue
    for (auto it = categories_.begin(); it != categories_.end(); it++)
    {   
        if (strcasecmp(it->getName().c_str(), categoryName.c_str()) == 0)
        {
            return (it->getClue(pointValue)).getClue();
        }
    }

    //throw an exception if the category wasn't found
    throw std::domain_error("No category with the given name");
}

bool Game::isClueAnswered(const std::string& categoryName, int pointValue)
{
    for (auto it = categories_.begin(); it != categories_.end(); it++)
    {
        if (strcasecmp(it->getName().c_str(), categoryName.c_str()) == 0)
        {
            return (it->getClue(pointValue)).isAnswered();
        }
    }

    throw std::domain_error("No category with the given name");
}

bool Game::answerClue(const std::string& categoryName, int pointValue,
                      const std::string& answer, std::string& correctAnswer)
{
    for (auto it = categories_.begin(); it != categories_.end(); it++)
    {
        if (strcasecmp(it->getName().c_str(), categoryName.c_str()) == 0)
        {
            Clue& clue = it->getClue(pointValue);
            if (!clue.isAnswered())
            {
                clue.setToAnswered();
                //increment the score by the point value and return true if correct
                if (strcasecmp(answer.c_str(), clue.getAnswer().c_str()) == 0)
                {
                    playerScore_ += pointValue;
                    return true;
                }
                //if wrong, set the correct answer then decrement the score and return false
                else
                {
                    correctAnswer = clue.getAnswer();
                    playerScore_ -= pointValue;
                    return false;
                }
            }
            else
            {
                //throw an exception if the clue was already answered
                throw std::domain_error("Clue already answered");
            }
        }
    }

    throw std::domain_error("No category with the given name");
}

int Game::getPlayerScore() const noexcept
{
    return playerScore_;
}

std::string Game::toString() const noexcept
{
    std::stringstream sstream;

    //find longest category name
    int nameSize = 0;
    for (int i = 0; i < categories_.size(); i++)
    {
        if (categories_[i].getName().size() > nameSize)
        {
            nameSize = categories_[i].getName().size();
        }
    }

    //print each category
    for (auto it = categories_.begin(); it != categories_.end(); it++)
    {
        //print the name of the category
        sstream << left << setw(nameSize) << setfill(' ') << it->getName();

        const std::vector<Clue>& clues = it->getClues();

        //print the point value for each clue if it is unanswered, 
        //otherwise leave a blank space
        for (int i = 0; i < clues.size(); i++)
        {
            sstream << right << setw(10) << setfill(' ');
            if (clues[i].isAnswered())
            {
                sstream << " ";
            }
            else
            {
                sstream << clues[i].getPointValue();
            }
        }
        sstream << endl;
    }

    return sstream.str();
}
