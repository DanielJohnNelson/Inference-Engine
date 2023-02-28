// LogicAlgorithm.cpp
// Daniel Nelson (102578897)

#include "LogicAlgorithm.h"
#include <Windows.h>
#include <Psapi.h>

const std::string& LogicAlgorithm::GetValidModels() 
{
    //Return different output based on sub-class type
    if (fAlgType == "TT")
    {
        //Return number of valid models
        
        fValidModels = std::to_string(fValidNum);
    }
    //Return string of valid models (or int to string)
    return fValidModels;
}

bool LogicAlgorithm::Entail(std::vector<HornClause>& aKnowledgeBase, const std::string& aQuery)
{
    return false;
}

void LogicAlgorithm::CalcMemoryUse()
{
    //Calculate memory used by current process
    PROCESS_MEMORY_COUNTERS_EX lMem;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&lMem, sizeof(lMem));

    //Put into size_t
    SIZE_T lMemUsed = lMem.WorkingSetSize;
    
    //Convert from bytes to KB
    lMemUsed /= 1000;
    
    //Set max if current max <= current memory usage
    if (fMemoryUsed <= lMemUsed)
    {
        //std::cout << lMemUsed << std::endl;
        fMemoryUsed = lMemUsed;
    }
}

const std::string& LogicAlgorithm::GetAlgType() const
{
    return fAlgType;
}

const size_t& LogicAlgorithm::GetMemoryUsed() const
{
    return fMemoryUsed;
}
