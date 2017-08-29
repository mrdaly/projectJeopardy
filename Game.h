#ifndef GAME_H
#define GAME_H

#include "Category.h"

namespace jeopardy {

/**
 * @class Game
 * Class representing a game of jeopardy
 */
class Game
{
public:
    /**
     * Constructs a Game
     * @param categories    vector of categories in this game
     */
    Game(const std::vector<Category>& categories);
    /**
     * Gets the clue given the category and point value
     * @param categoryName  name of the category containing the clue
     * @param pointValue    point value of the clue
     * @return string representing the clue
     * @throws domain_error if there is no clue with the given category
     *         name or point value
     */
    std::string getClue(const std::string& categoryName, int pointValue);
    /**
     * Tels whether the given clue is answered
     * @param categoryName  name of the category containing the clue
     * @param pointValue    point value of the clue
     * @return bool showing whether the given clue is answered
     * @throws domain_error if there is no clue with the given category
     *         name or point value
     */
    bool isClueAnswered(const std::string& categoryName, int pointValue);
    /**
     * Answers the given clue
     * @param categoryName  name of the category containing the clue
     * @param pointValue    point value of the clue
     * @param answer        given answer to be checked if it is correct
     * @param correctAnwer  reference to a string where the correct answer
     *                      will be stored if the given answer is wrong
     * @return bool showing whether the given answer was correct
     * @throws domain_error if there is no clue with the given category
     *          name or point value
     */
    bool answerClue(const std::string& categoryName, int pointValue,
                    const std::string& answer, std::string& correctAnswer);
    /**
     * Gets the player's score
     * @return integer representing the players score in points
     */
    int getPlayerScore() const noexcept;
    /**
     * Creates a string representation of the game board
     * @return  string representing the game board
     */
    std::string toString() const noexcept;
private:
    std::vector<Category> categories_;
    int playerScore_;
};

}

#endif

