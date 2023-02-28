// TruthTable.h
// Daniel Nelson (102578897)

#pragma once

#include "HornClause.h"
#include "LogicAlgorithm.h"
#include <vector>
#include <set>
#include <unordered_map>


class TruthTable : public LogicAlgorithm
{
    private:
        std::set<std::string> fSymbols;

    public:

        //Constructor
        TruthTable(const std::set<std::string>& aSymbols);

        //Entailment Method (Truth Table)
        virtual bool Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery);

        //Recursive Truth table algorithm method
        bool TT_Check_All(const std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery, const std::set<std::string>& aSymbols, std::unordered_map<std::string, bool>& aModel);

        //Check model against knowledge base
        bool ModelTrue(const std::vector<HornClause>& aKnowledgeBase, std::unordered_map<std::string, bool>& aModel);

        //Check model against individual clause in knowledge base
        bool ClauseTrue(const HornClause& aClause, std::unordered_map<std::string, bool>& aModel);

        //Extend model with new potential clause
        std::unordered_map<std::string, bool>& Extend(std::string& aSymbol, bool aBool, std::unordered_map<std::string, bool>& aModel);

};