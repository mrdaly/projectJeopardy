#include "Parser.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::string;
using std::getline;
using std::vector;

using namespace jeopardy;

const int BASE_CLUE_VALUE = 200; //the point values of the clues are a multiple of 200
const int NUM_CATEGORIES = 6; 
const int NUM_CLUES_PER_CAT = 5;
const string CATEGORY_TAG = "category_name\">"; //identifies where the category name is in the source
const string CATEGORY_END = "</td>"; //identifies where the category name ends
const string ANSWER_TAG = "correct_response"; //identifies the line where the answer is
const string SECONDARY_ANSWER_TAG = "&gt;"; //this is the text that immediately precedes the answer
const string ANSWER_END = "&lt;"; //identifies where the answer ends
const string CLUE_TAG = "clue_text\">"; //identifies where the clue text is
const string CLUE_END = "</td>"; //identifies where the clue ends

Game Parser::buildGame(const string& sourceFileName)
{
    //open the file
    ifstream source;
    source.open(sourceFileName);

    //create vectors that will store the info needed to create the game
    vector<string> categoryNames;
    vector<vector<Clue>> categoryClues;
    for (int i = 0; i < NUM_CATEGORIES; i++)
    {
        vector<Clue> clues;
        categoryClues.push_back(clues);
    }

    int catCount = 0; //count for the creation of the categories
    int clueNum = 1; 
    int categoryIndex = 0;

    while (!source.eof())
    {
        //get a line from the file
        string line;
        getline(source, line);

        if (catCount < NUM_CATEGORIES)
        {
            //find the category name text
            int found = line.find(CATEGORY_TAG);
            if (found != string::npos)
            {
                //extract the substring containing the category name
                int end = line.find(CATEGORY_END, found);
                int begin = found + CATEGORY_TAG.size();
                string name = line.substr(begin, end - begin);
                categoryNames.push_back(name);
                catCount++;
            }
        }

        else if (clueNum <= NUM_CLUES_PER_CAT)
        {
            //find where the answer is
            int found = line.find(ANSWER_TAG);
            if (found != string::npos)
            {
                string answer;
                //after the answer tag, the answer text exists between the next instances of "&gt;" and
                //"&lt;" unless "&gt;" and "&lt;" are immediately next to each other
                while (answer.empty())
                {
                    found = line.find(SECONDARY_ANSWER_TAG, found);
                    if (line.substr(found + SECONDARY_ANSWER_TAG.size(), ANSWER_END.size()) != ANSWER_END)
                    {
                        int end = line.find(ANSWER_END, found);
                        int begin = found + SECONDARY_ANSWER_TAG.size();
                        answer = line.substr(begin, end - begin);
                    }
                    else
                    {
                        found++;
                    }
                }

                string clueText;

                //after we find the answer, get lines until we find the clue text
                while (line.find(CLUE_TAG) == string::npos)
                {
                    getline(source, line);
                }
                //extract the clue text
                found = line.find(CLUE_TAG);
                int end = line.find(CLUE_END, found);
                int begin = found + CLUE_TAG.size();
                clueText = line.substr(begin, end - begin);

                //construct the clue with the clue, answer and point value, then place it 
                //in a vector corresponding to its category
                int pointValue = clueNum * BASE_CLUE_VALUE;
                Clue clue(clueText, answer, pointValue);
                categoryClues[categoryIndex].push_back(clue);
                //go to the next category, after we have all the clues of a certain point
                //value for all the categories, go to the next point value and reset the
                //category index
                categoryIndex++;
                if (categoryIndex == NUM_CATEGORIES)
                {
                    categoryIndex = 0;
                    clueNum++;
                }
            }
        }
    }

    //create the categories from the data extracted, then create the game and return it
    vector<Category> categories;
    for (int i = 0; i < categoryNames.size(); i++)
    {
        Category category(categoryNames[i], categoryClues[i]);
        categories.push_back(category);
    }

    Game game(categories);
    return game;
}
