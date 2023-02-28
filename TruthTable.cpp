// TruthTable.cpp
// Daniel Nelson (102578897)

#include "TruthTable.h"
#include <string>
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <Psapi.h>

TruthTable::TruthTable(const std::set<std::string>& aSymbols)
{
    //Initialize variables
    fSymbols = aSymbols;

    fAlgType = "TT";
}

bool TruthTable::Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery)
{
    //Combine unique symbols of both KB and Query
    std::set<std::string> lSymbols(fSymbols);
    //Add query symbol
    lSymbols.insert(aQuery);
    //Initialize empty model
    std::unordered_map<std::string, bool> lModel;
    //Call recursive truth table algorithm
    return TT_Check_All(aKnowledgeBase, aQuery, lSymbols, lModel);
}

bool TruthTable::TT_Check_All(const std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery, const std::set<std::string>& aSymbols, std::unordered_map<std::string, bool>& aModel)
{
    //Calculates memory use of current process
    LogicAlgorithm::CalcMemoryUse();

   if (aSymbols.empty())
   {
       //Check if model is true against knowledge base
       if (ModelTrue(aKnowledgeBase, aModel))
       {
           //Check if query valid in model
           if (aModel.at(aQuery))
           {
               LogicAlgorithm::fValidNum += 1;

               return true;
           }
           else 
           {
               return false;
           }
       }
       else
       {
           return true;
       }
   }
   else
   {
       
       //Take symbol from end of symbol set
       std::string lFirst = *std::prev(aSymbols.end());
       //Create copy of symbol set
       std::set<std::string> lRest(aSymbols);
       //Remove last element of symbol set
       lRest.erase(std::prev(lRest.end()));
       //Recurse into all possible models depth first
       return ((TT_Check_All(aKnowledgeBase, aQuery, lRest, Extend(lFirst, true, aModel))) && (TT_Check_All(aKnowledgeBase, aQuery, lRest, Extend(lFirst, false, aModel))));

   }
}

bool TruthTable::ModelTrue(const std::vector<HornClause>& aKnowledgeBase, std::unordered_map<std::string, bool>& aModel)
{
    //Loop over knowledge base
    for (size_t i = 0; i < aKnowledgeBase.size(); i++)
    {
        //Check if individual model is true against knowledge base
        if (ClauseTrue(aKnowledgeBase[i], aModel) == false)
        {
            return false;
        }
    }

    return true;
}

bool TruthTable::ClauseTrue(const HornClause& aClause, std::unordered_map<std::string, bool>& aModel)
{
    //Check if no entailment, implying just one symbol
    if (aClause.GetSubsequent().empty())
    {
        //Checks if fact in clause is true in model
        size_t lStart = 0;
        return aModel.at(aClause.GetPrecedents()[lStart]);
    }
    else
    {
        
        bool lResult = true;
        //For each precedent in clause, check if not true with model
        for (size_t i = 0; i < aClause.GetPreSize(); i++)
        {
            //Check if clause is not true in model
            if (!aModel.at(aClause.GetPrecedents()[i]))
            {
                lResult = false;
            }
        }
        //If all precedents are true
        if (lResult)
        {
            //Return subsequent
            return aModel.at(aClause.GetSubsequent());
        }

    }

    //If precedents turn out false, return true
    return true;
}

std::unordered_map<std::string, bool>& TruthTable::Extend(std::string& aSymbol, bool aBool, std::unordered_map<std::string, bool>& aModel)
{
    //Append model with new potential DFS branch (Replacing if full)
    aModel[aSymbol] = aBool;
    //Return updated model
    return aModel;
}
