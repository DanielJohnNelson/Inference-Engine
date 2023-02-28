// BackwardChaining.cpp
// Daniel Nelson (102578897)

#include "BackwardChaining.h"

BackwardChaining::BackwardChaining()
{
    //Initialize variables
    fAlgType = "BC";
}

bool BackwardChaining::Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery)
{
    LogicAlgorithm::CalcMemoryUse();
    //Initialize bool to check if there is a rule with the given query as subsequent
    bool lSubQuery = false;

    //Loop over knowledge base
    for (size_t i = 0; i < aKnowledgeBase.size(); i++)
    {
        //Check if given query is a fact in individual clause
        if (aKnowledgeBase[i].GetSubsequent().empty() && aKnowledgeBase[i].GetPrecedents()[0] == aQuery)
        {
            //Append it to valid model string
            fValidModels.append(aQuery + ", ");
            
            return true;
        }

        //Check if query is subsequent in individual clause
        if (aKnowledgeBase[i].GetSubsequent() == aQuery)
        {
            //Set available query true
            lSubQuery = true;
            //Append vector of potential models with clause
            fQueryClauses.insert(fQueryClauses.begin(), aKnowledgeBase[i]);
        }
        
    }

    //If there is no clauses with query subsequent return back
    if (!lSubQuery)
    {
        return false;
    }

    //Loop over potential query clauses
    for (size_t k = 0; k < fQueryClauses.size(); k++)
    {
        //Bool to check if all precedents are true
        bool lValidPrecedents = true;

        //Loop over individual clause precedents
        for (size_t j = 0; j < fQueryClauses[j].GetPreSize(); j++)
        {
            //Check if precedent is true
            if (!Entail(aKnowledgeBase, fQueryClauses[k].GetPrecedents()[j]))
            {
                //If not set bool false
                lValidPrecedents = false;
            }

            //Otherwise append valid model string
            else
            {
                fValidModels.append(aQuery + ", ");
            }
        }

        //Return true if all precedents are valid
        if (lValidPrecedents)
        {
            return true;
        }
    }

    //If nothing, return false
    return false;
}
