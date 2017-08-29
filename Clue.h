#ifndef CLUE_H
#define CLUE_H

#include <string>

namespace jeopardy {

/**
 * @class Clue
 * A class representing a clue in jeopardy
 */
class Clue
{
public:
    /**
     * Constructs a clue.
     * @param clue      string representing the clue
     * @param answer    string representing the answer to the clue
     * @param pointVal  integer point value of this clue
     */
    Clue(const std::string& clue, const std::string& answer, int pointValue);
    /**
     * Get the clue
     * @return string representing the clue
     */
    std::string getClue() const noexcept;
    /**
     * Gets the answer to this clue
     * @return string representing the answer
     */
    std::string getAnswer() const noexcept;
    /**
     * Gets the point value of this clue
     * @return integer representing the point value
     */
    int getPointValue() const noexcept;
    /**
     * Returns whether this clue is answered
     * @return bool saying whether this clue is answered
     */
    bool isAnswered() const noexcept;
    /**
     * Change this clue to be answered
     */
    void setToAnswered() noexcept;
private:
    std::string clue_;
    std::string answer_;
    int pointValue_;
    bool isAnswered_;
};

}

#endif

