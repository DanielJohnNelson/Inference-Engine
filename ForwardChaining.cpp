// ForwardChaining.cpp
// Daniel Nelson (102578897)

#include "ForwardChaining.h"
#include <Windows.h>
#include <Psapi.h>

ForwardChaining::ForwardChaining(std::unordered_map<std::string, bool>& aInferred, std::vector<std::string>& aAgenda)
{
    //Initialize variables
    fInferred = aInferred;

    fAgenda = aAgenda;

    fAlgType = "FC";
}

bool ForwardChaining::Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery)
{
    //Loop until no more elements in agenda
    while (fAgenda.empty() == false)
    {
        //Calculates memory use of current process
        LogicAlgorithm::CalcMemoryUse();
        //Take next clause off agenda
        std::string lNext = fAgenda[0];
        //Remove clause from agenda
        fAgenda.erase(fAgenda.begin());
        //Append valid models with next agenda
        LogicAlgorithm::fValidModels.append(lNext + ", ");
        //Append inferred with next clause
        fInferred.insert({ lNext, false });

        if (fInferred.at(lNext) == false)
        {
            fInferred[lNext] = true;

            for (size_t i = 0; i < aKnowledgeBase.size(); i++)
            {
                if (Contains(aKnowledgeBase[i].GetPrecedents(), lNext))
                {
                    //Decrement the count of premises left in clause
                    aKnowledgeBase[i]--;

                    if (aKnowledgeBase[i].GetCount() == 0)
                    {
                        //Check if query found
                        if (aKnowledgeBase[i].GetSubsequent() == aQuery)
                        {
                            //Append query with valid model
                            LogicAlgorithm::fValidModels.append(aQuery + ", ");

                            return true;
                        }
                        else
                        {
                            //Append agenda with new fact
                            fAgenda.push_back(aKnowledgeBase[i].GetSubsequent());
                        }
                    }
                }
            }
            
        }
    }

    return false;
}

bool ForwardChaining::Contains(const std::vector<std::string> aPremises, std::string aPremise) const
{
    //Loop over each premise to determine if they contain given premise
    for (size_t i = 0; i < aPremises.size(); i++)
    {
        if (aPremises[i] == aPremise)
        {
            //Return if found
            return true;
        }
    }
    //Else return false for not found
    return false;
}

