#ifndef CATEGORY_H
#define CATEGORY_H

#include "Clue.h"
#include <vector>

namespace jeopardy {

/**
 * @class Category
 * Class representing a category of clues in jeopardy
 */
class Category
{
public:
    /**
     * Constructs a category
     * @param name  string of the name of this category
     * @param clues vector of clues that belong in this category
     */
    Category(const std::string& name, const std::vector<Clue>& clues);
    /**
     * Get the name of this category
     * @return string of the name of this category
     */
    std::string getName() const noexcept;
    /**
     * Gets the clue with the given point value
     * @param pointValue    point value of the clue being requested
     * @return a reference to te clue with the given point value
     * @throws  domain_error if there is no clue with the given point value
     */
    Clue& getClue(int pointValue);
    /**
     * Gets the clues stored in this category
     * @return a const reference to the vector of clues of this category
     */
    const std::vector<Clue>& getClues() const noexcept;
private:
    std::string name_;
    std::vector<Clue> clues_;
};

}

#endif

