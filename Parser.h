#ifndef PARSER_H
#define PARSER_H

#include "Game.h"

namespace jeopardy {

/**
 * @class Parser
 * Class that parses a source file to create a jeopardy game
 */
class Parser
{
public:
    /**
     * Builds a Game from a source file containing html code
     * @param sourceFileName    name of the file containing the source code
     * @return  A Game containing the categories and clues that were in the 
     *          source file
     */
    Game buildGame(const std::string& sourceFileName);
};

}

#endif

