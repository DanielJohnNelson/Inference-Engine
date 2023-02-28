// KnowledgeBase.h
// Daniel Nelson (102578897)

#pragma once

#include "HornClause.h"
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>

class KnowledgeBase
{
    private:
        //Knowledge base of clauses
        std::vector<HornClause> fKnowledgeBase;
        //Set of unique symbols
        std::set<std::string> fSymbols;
        //User inputted query
        std::string fQuery;
        //Table indexed by symbol and according bool value
        std::unordered_map<std::string, bool> fInferred;
        //List of initially true symbols
        std::vector<std::string> fAgenda;


    public:
        //Knowledge Base Constructor
        KnowledgeBase(std::ifstream& aFile);
        
        //Load data from file
        std::vector<std::string> LoadKnowledgeBase(std::ifstream &aFile);

        //Initialize member variables
        void InitKnowledgeBase(std::vector<std::string>& aKnowledgeVect);

        //Return vector of clauses
        std::vector<HornClause>& GetKnowledgeBase();

        //For testing
        void SetKnowledgeBase(std::string aInput);

        //Return set of unique symbols
        const std::set<std::string>& GetSymbols() const;

        //Return query string
        const std::string& GetQuery() const;

        //Return Inferred map for FC and BC
        std::unordered_map<std::string, bool>& GetInferred();

        //Return Agenda map for FC and BC
        std::vector<std::string>& GetAgenda();


};