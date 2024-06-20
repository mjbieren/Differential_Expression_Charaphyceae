#include "GlobalHelper.h"
CGlobal glb;


/*
This programs basically creates a KEGG tsv file that can instantly be used to create a bar plot in Excel and/or R.
It imports a KEGG description file (also tsv format), create CKEGGSet objects out of that and fill the counters in this CKEGGSet objects based on the DE KEGG Matrix the user provides.


1) Parse Command Line
2) Parse Input Files
3) Match and increase (if threshold is match) the corresponding IDX of the KEGG object.
4) Write output file
    Loop over the vector of CKEGGSets and determine first if the threshold for the minimum amount of sets and minimum amount of hits (per set) are matched before being included in the output file
5) Clean up.

*/



int main(int argc, char* argv[], char* envp[])
{
    long lReturn = ERR_NOERROR;

    //STEP ONE
    printf_s("Parsing the command line %s", EOL);
    lReturn = ParseCommandLine(argc, argv, envp);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the command line %s", EOL);


    //init variables
    CTable* pKEGGMatrix = new CTable;
    CSmartPtr<CTable> pAutoDeleteKeggMatrix = pKEGGMatrix;
    CTable* pKEGGDescription = new CTable;
    CSmartPtr<CTable> pAutoDeleteKeggDescription = pKEGGDescription;
    std::vector<CKEGGSet*> vecKEGGSet;



    //STEP TWO
    printf_s("Parsing the input files %s", EOL);
    lReturn = ParseInputFiles(pKEGGMatrix, pKEGGDescription, &vecKEGGSet);
    CheckReturnValue(lReturn, &vecKEGGSet);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the input files%s", EOL);

    //STEP THREE
    printf_s("Matching the KEGG hits against the pathways%s", EOL);
    lReturn = MatchAndCountKEGGHits(pKEGGMatrix, &vecKEGGSet);
	CheckReturnValue(lReturn, &vecKEGGSet);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with Matching the Input files %s", EOL);

    //STEP FOUR
    printf_s("Writing the output file %s", EOL);
    lReturn = WriteOutputFile(pKEGGMatrix, &vecKEGGSet);
    CheckReturnValue(lReturn, &vecKEGGSet);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with Writing the output file%s", EOL);


    //STEP FIVE
    ClearVector(&vecKEGGSet);

    return 0;
}