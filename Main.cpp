// Main.cpp
// Daniel Nelson (102578897)

#include "KnowledgeBase.h"
#include "ForwardChaining.h"
#include "BackwardChaining.h"
#include "LogicAlgorithm.h"
#include "TruthTable.h"
#include <iostream>
#include <chrono>




int main(int argc, char* argv[])
{
    //Check for invalid input
    if (argc < 3 || argc > 3)
    {
        std::cout << "Invalid Amount of command arguments. Specify (exe method filename)" << std::endl;

        return 2;
    }
    else 
    {
        //Declare and open file
        std::ifstream lFile;
        lFile.open(std::string(argv[2]));
        //Handle open error
        if (!lFile)
        {
            std::cout << "File not found" << std::endl;
            return -1;
        }
        //Check for valid method input
        else if (std::string(argv[1]) != "TT" && std::string(argv[1]) != "FC" && std::string(argv[1]) != "BC")
        {
            std::cout << "Invalid Method." << std::endl;

            return -1;
        }
        //Initialize knowledge base
        KnowledgeBase lKB(lFile);

        if (lKB.GetKnowledgeBase().empty())
        {
            std::cout << "No knowledge base statements were given" << std::endl;

            return -1;
        }
        else if (lKB.GetQuery().empty())
        {
            std::cout << "No query was given" << std::endl;

            return -1;
        }

        //Close file after initializing
        lFile.close();

        //Declare base logic algorithm class
        LogicAlgorithm* lLogicAlg;
        //Declare map of declared sub algorithms to be used on base
        std::unordered_map<std::string, LogicAlgorithm*> lInit;
        //Append each sub-algorithm
        lInit["TT"] = new TruthTable(lKB.GetSymbols());
        lInit["FC"] = new ForwardChaining(lKB.GetInferred(), lKB.GetAgenda());
        lInit["BC"] = new BackwardChaining();

        //Initialize base class with sub class
        lLogicAlg = lInit[std::string(argv[1])];

        //Begin compute time clock
        auto lStartTime = std::chrono::high_resolution_clock::now();
        //Compute desired algorithm
        bool lEntails = lLogicAlg->Entail(lKB.GetKnowledgeBase(), lKB.GetQuery());
        //End compute time clock
        auto lEndTime = std::chrono::high_resolution_clock::now();
        //Convert time to microseconds
        auto lCompTime = std::chrono::duration_cast<std::chrono::microseconds>(lEndTime - lStartTime).count();


        //Code for testing time and space complexity of algorithm over infinite loop
        /*
        bool lTesting = true;

        if (lTesting)
        {
            for (size_t i = 0; i < 1000; i++)
            {
                lKB.SetKnowledgeBase("X" + std::to_string(i));

                lLogicAlg = new BackwardChaining();

                auto lStartTime = std::chrono::high_resolution_clock::now();

                lLogicAlg->Entail(lKB.GetKnowledgeBase(), lKB.GetQuery());

                auto lEndTime = std::chrono::high_resolution_clock::now();

                auto lCompTime = std::chrono::duration_cast<std::chrono::microseconds>(lEndTime - lStartTime).count();

                std::cout << lLogicAlg->GetAlgType() << ":       KB Size: " << lKB.GetKnowledgeBase().size() << "         CompTime: " << lCompTime << "       Max Mem: " << lLogicAlg->GetMemoryUsed() << std::endl;
            }
        }

        */


        //Output type of algorithm used
        std::cout << "Algorithm: " << lLogicAlg->GetAlgType() << std::endl;

        //Output size of KB
        std::cout << "Knowledge Base Size: " << lKB.GetKnowledgeBase().size() << std::endl;

        //Call virtual entail method depending on algorithm sub-class
        if (lEntails)
        {
            //Call virtual valid models method
            std::cout << "Entaled: YES: " << lLogicAlg->GetValidModels() << std::endl;
        }
        else
        {
            std::cout << "Entailed: NO" << std::endl;
        }

        //Output algorithm time
        std::cout << "Computation Time: " << lCompTime << " Microseconds" << std::endl;
        //Output max memory used in bytes
        std::cout << "Maximum memory used: " << lLogicAlg->GetMemoryUsed() << " Kilobytes" << std::endl;


        
    }

    return 0;
}


