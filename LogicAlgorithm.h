// LogicAlgorithm.h
// Daniel Nelson (102578897)

#pragma once

#include "HornClause.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <Windows.h>

class LogicAlgorithm
{

    protected:

        //String of valid models, used in FC AN BC
        std::string fValidModels;
        //Number of valid models used in TT
        int fValidNum = 0;
        //Type of sub-algorithm
        std::string fAlgType;

        size_t fMemoryUsed = 0;

    public:

        //Virtual entail method overrided by sub algorithms
        virtual bool Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery);

        void CalcMemoryUse();

        //Returns valid models (either number or models)
        const std::string& GetValidModels();

        //Returns algorithm type
        const std::string& GetAlgType() const;
        //Returns max memory used
        const size_t& GetMemoryUsed() const;

         
};