// HornClause.cpp
// Daniel Nelson (102578897)

#include "HornClause.h"


HornClause::HornClause(const std::vector<std::string>& aPrecedents, const std::string& aSubsequent, const int aCount)
{
    //Initialize variables
    fPrecedents = aPrecedents;
    fSubsequent = aSubsequent;
    fCount = aCount;
}

std::vector<std::string> HornClause::GetPrecedents() const
{
    return fPrecedents;
}

const std::string& HornClause::GetSubsequent() const
{
    return fSubsequent;
}

void HornClause::SetSubsequent(std::string aSub)
{
    fSubsequent = aSub;
}

const size_t& HornClause::GetPreSize() const
{
    return fPrecedents.size();
}

const int& HornClause::GetCount() const
{
    return fCount;
}

void HornClause::operator--(int)
{
    fCount--;
}

