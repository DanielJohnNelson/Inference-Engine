// BackwardChaining.h
// Daniel Nelson (102578897)

#pragma once

#include "HornClause.h"
#include "LogicAlgorithm.h"
#include <vector>
#include <unordered_map>
#include <string>



class BackwardChaining : public LogicAlgorithm
{
    private:
        //Used to manage entailable clauses in recursion
        std::vector<HornClause> fQueryClauses;

    public:

        //Constructor
        BackwardChaining();

        //Entailment Method (Backward Chaining)
        virtual bool Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery);
};