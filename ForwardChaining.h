// ForwardChaining.h
// Daniel Nelson (102578897)

#pragma once

#include "HornClause.h"
#include "LogicAlgorithm.h"
#include <vector>
#include <unordered_map>
#include <string>


class ForwardChaining : public LogicAlgorithm
{
    //Symbol indexed mapped to bool value
    std::unordered_map<std::string, bool> fInferred;
    //List of symbols which are factual
    std::vector<std::string> fAgenda;

    public:

        //Constructor
        ForwardChaining(std::unordered_map<std::string, bool>& aInferred, std::vector<std::string>& aAgenda);
        
        //Entailment Method (Forward chaining algorithm)
        virtual bool Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery);

        //Check if premises contain desired premise
        bool Contains(const std::vector<std::string> aPremises, const std::string aPremise) const;
};