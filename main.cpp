#include <iostream>
#include <string>
#include "Game.h"
#include "Parser.h"

using namespace std;

/**
 * @namespace jeopardy
 * Namespace for the classes that represent clues, categories, and a
 * game in jeopardy.
 *
 * @author Matthew Daly
 */
using namespace jeopardy;

/**
 * Main program to run the jeopardy game
 * @return the return status, normal is 0
 */
int main()
{
    string commands = "Commands:\n  b - display board \n" 
                                 "  s - display score \n" 
                                 "  c - choose clue \n" 
                                 "  x - exit\n" 
                                 "  h - show commands \n";
    

    //take name of file containing html source and parses it into a game
    string file;
    cout << "Game file: ";
    cin >> file;
    Parser parser;
    Game game = parser.buildGame(file);

    cout << game.toString();

    cout << commands;
    for (;;)
    {
        //take commands
        cout << "input: ";
        string input;
        cin >> input;

        if (input == "x")
        {
            break;
        }
        else if (input == "h")
        {
            cout << commands;
        }
        else if (input == "b")
        {
            cout << game.toString();
        }
        else if (input == "s")
        {
            cout << game.getPlayerScore() << endl;
        }
        else if (input == "c")
        {
            //ask for the category and point value for the clue to be chosen
            cout << "Which category? ";
            string categoryName;
            cin.ignore();
            getline(cin, categoryName);
            cout << "Point value: ";
            string pointVal;
            cin >> pointVal;
            try
            {
                //display the clue then ask for an answer
                string clue = game.getClue(categoryName, stoi(pointVal));
                cout << clue << endl << "Answer: ";
                string answer;
                cin.ignore();
                getline(cin, answer);
                string correctAnswer;
                if (game.answerClue(categoryName, stoi(pointVal), answer, correctAnswer))
                {
                    cout << "Correct! \nNew Score: " << game.getPlayerScore() << endl;
                }
                else
                {
                    cout << "Wrong! \nCorrect Answer: " << correctAnswer <<
                        "\nNew Score: " << game.getPlayerScore() << endl;
                }
            }
            catch (exception& e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}

