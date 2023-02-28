// HornClause.h
// Daniel Nelson (102578897)

#pragma once

#include <vector>
#include <string>

class HornClause
{
    private:
        
        //Symbols preceeding the operator
        std::vector<std::string> fPrecedents;

        //Symbol succeeding the operator (if any)
        std::string fSubsequent;
        
        //Count used for forward chaining
        int fCount;

    public:
    
        //Horn Clause Constructor
        HornClause(const std::vector<std::string>& aPrecedents, const std::string& aSubsequent, const int aCount);

        //Get symbols preceeding operator
        std::vector<std::string> GetPrecedents() const;

        //Get symbol succeeding operator
        const std::string &GetSubsequent() const;

        //Set subsequent used in testing algorithm
        void SetSubsequent(std::string aSub);

        //Get amount of symbols preceeding operator
        const size_t& GetPreSize() const;

        //Return count for FC/BC methods
        const int& GetCount() const;
        
        //Decrement count for FC/BC methods
        void operator--(int);

};