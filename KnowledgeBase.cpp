// KnowledgeBase.cpp
// Daniel Nelson (102578897)

#include "KnowledgeBase.h"
#include <fstream>
#include <sstream>
#include <regex>



KnowledgeBase::KnowledgeBase(std::ifstream& aFile)
{
    //Load knowledge base from file
    std::vector<std::string> lKnowledgeVect = LoadKnowledgeBase(aFile);
    
    //Initialize knowledge base member variables
    InitKnowledgeBase(lKnowledgeVect);
    
}

std::vector<std::string>  KnowledgeBase::LoadKnowledgeBase(std::ifstream& aFile)
{
    std::string lLine;

    std::vector<std::string> lKnowledgeVect;

    //Loop over file lines
    for (int i = 0; i < 4; i++)
    {
        std::getline(aFile, lLine);
        
        //Parse clauses into vector
        if (i == 1)
        {
            std::istringstream lStream(lLine);

            std::string lSubString;

            while (std::getline(lStream, lSubString, ';')) 
            {
                lKnowledgeVect.push_back(lSubString);
            }
        }
        //Set query member variable
        else if (i == 3)
        {
            fQuery = lLine;
        }
    }
    
    return lKnowledgeVect;
}

void KnowledgeBase::InitKnowledgeBase(std::vector<std::string>& aKnowledgeVect)
{
    //Loop over clause strings
    for (size_t i = 0; i < aKnowledgeVect.size(); i++)
    {
        //Check for entailment
        if (aKnowledgeVect[i].find("=>") != std::string::npos)
        {
            //Strip string of non-symbols
            aKnowledgeVect[i] = std::regex_replace(aKnowledgeVect[i], std::regex("[^a-zA-Z0-9 :]"), " ");
            
            std::vector<std::string> lPrecedents;

            std::string lSubString;

            //Iterate through string appending precedents and subsequents
            for (std::istringstream lStream(aKnowledgeVect[i]); lStream >> lSubString; )
            {
                lSubString.erase(std::remove_if(lSubString.begin(), lSubString.end(), isspace), lSubString.end());

                if (!lStream.eof())
                {
                    lPrecedents.push_back(lSubString);
                }
                
                //Insert unique symbol (ignores duplicates)
                fSymbols.insert(lSubString);
                //Insert Unique symbol and bool into Inferred (ignores Duplicates)
                fInferred.insert({ lSubString, false });
              
            }
            //Insert new premises with count
            //fCount.insert({ lPrecedents, lPrecedents.size() });

            //Append horn clause to knowledge base
            fKnowledgeBase.push_back(HornClause(lPrecedents, lSubString, lPrecedents.size()));
        }
        else 
        {

            //Remove spaces
            aKnowledgeVect[i].erase(aKnowledgeVect[i].find(' '), 1);

            //Otherwise add symbol fact as clause with no subsequent
            fKnowledgeBase.push_back(HornClause({ aKnowledgeVect[i] }, std::string(), 0));

            //Add initial fact to agenda for FC and BC
            fAgenda.push_back(aKnowledgeVect[i]);

            //Insert unique symbol (ignores duplicates
            fSymbols.insert(aKnowledgeVect[i]);
        }
    }

}

std::vector<HornClause>& KnowledgeBase::GetKnowledgeBase() 
{
    return fKnowledgeBase;
}

void KnowledgeBase::SetKnowledgeBase(std::string aInput)
{
    //Used for scaled algorithm to test. Sets subsequent to new input
    fKnowledgeBase[fKnowledgeBase.size() - 1].SetSubsequent(aInput);
    //Creates new horn clause with query as entailed
    fKnowledgeBase.push_back(HornClause({ aInput }, fQuery, 1));
}

const std::set<std::string>& KnowledgeBase::GetSymbols() const
{
    return fSymbols;
}

const std::string& KnowledgeBase::GetQuery() const
{
    return fQuery;
}

std::unordered_map<std::string, bool>& KnowledgeBase::GetInferred()
{
    return fInferred;
}

std::vector<std::string>& KnowledgeBase::GetAgenda() 
{
    return fAgenda;
}




