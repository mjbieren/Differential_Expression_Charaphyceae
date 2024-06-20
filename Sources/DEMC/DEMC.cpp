#include "GlobalHelper.h"
CGlobal glb;


long CheckReturnValue(long lReturn, std::vector<CInfernal*>* pvecInfernal, std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocks, std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutputBlocks, std::vector<char*>* pvecSetNames, std::vector<size_t>* pvecColumnPositions);
long ParseCommandLine(int argc, char* argv[], char* envp[]);
long ParseInputFiles(CFastaFile* pFastaFileTrinity, CFastaFile* pFastaFileProtein, CTable* pTableTrinotate, CTable* pTableDEMatrix, std::vector<CInfernal*>* pvecInfernal);
long MatchObjects(CFastaFile* pFastaTrinity, CFastaFile* pFastaProtein, CTable* pTableTrinotate, CTable* pTableDEMatrix, std::vector<CInfernal*>* pvecInfernalInput, std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocksOutput, std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutput);
long FindSets(std::vector<char*>* pvecSetNames, std::vector<size_t>* pvecColumnPositions, CTable* pTableDEMatrix);
long WriteOutputFiles(const std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocks, const std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutputBlocks, std::vector<char*>* pvecBiologicalSetNames, std::vector<size_t>* pvecSamplesVsBiologicalSetPositions, CTableRowHeader* pTrinotateTableHeaders);

/*
This program filters out the Differential Expression genes and based on the columns the user wants to add (or not if the user doesn't use this parameter).
It will match the DE isoforms to the Trinotate output format, and based on the previous line. Either shows the whole row, or only a select few columns.
The DE matrix values will be combined based on condition (rather than sample). Which we can use later for creating a tsv file based on KEGG Numbers

1) Parse Command Line
2) Parse Input Files
3) Matching:
    Loop over DE matrix.
    3a match DE Script to Trinotate output
    3b Check if tere is an infernal output in teh Trinotate Output, if not skip. If yes, Match to Infernal
    3c Match Trinity Fasta (Isoform)
    3d Match Protein Fasta (Proteins
4) Determine How many sets and how they are named.
5) Write Output:
    Loop over CDifferentialMatrixBlock Vector and fill in file buffers:
        Filtered_DE_Matrix
        KEGG_DE_MATRIX
        INFERNAL_DE_MATRIX
        RNA_Infernal_ (Fasta File)
        Trinity_Protein_File_With_Protein_Description_InHeader (Trinity Protein ID + Description)
        Trinity_Protein_File_Clean (Trinity Protein ID)
        Trinity_Gene_File (Trinity Isoform ID Only).
5) Clean UP

*/


int main(int argc, char* argv[], char* envp[])
{
    long lReturn = ERR_NOERROR;

    //STEP ONE
    printf_s("Parsing the command line %s", EOL);
    lReturn = ParseCommandLine(argc, argv, envp);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with parsing the command line %s", EOL);

    //init variables.
    CFastaFile* pFastaFileTrinity = new CFastaFile;
    CSmartPtr<CFastaFile> pAutoDeleteTrinity = pFastaFileTrinity;
    CFastaFile* pFastaFileProtein = new CFastaFile;
    CSmartPtr<CFastaFile> pAutoDeleteProtein = pFastaFileProtein;
    CTable* pTableTrinotate = new CTable;
    CSmartPtr<CTable> pAutoDeleteTrinotate = pTableTrinotate;
    CTable* pTableDEMatrix = new CTable;
    CSmartPtr<CTable> pAutoDeleteDEMatrix = pTableDEMatrix;

    std::vector<CInfernal*> vecInfernal;
    std::vector<CDifferentialMatrixBlock*> vecDifferentialMatrixBlocks;
    std::vector<CDifferentialMatrixBlock*> vecInfernalOutputBlocks;
    std::vector<char*> vecSetNames; //as in biologically sample sets
    std::vector<size_t> vecColumnPositions; //As the DE columns matching

 
    //STEP TWO
    //ParseInputFiles
    printf_s("Parsing the Input Files %s", EOL);
    lReturn = ParseInputFiles(pFastaFileTrinity, pFastaFileProtein,pTableTrinotate, pTableDEMatrix, &vecInfernal);
    CheckReturnValue(lReturn, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks, &vecSetNames, &vecColumnPositions);
    CHECK_RETURNVALUE(lReturn); 
    printf_s("Done with parsing the input files %s", EOL);

    //STEP THREE
    //MATCHING
    printf_s("Matching the different objects to another %s", EOL);
    lReturn = MatchObjects(pFastaFileTrinity, pFastaFileProtein, pTableTrinotate, pTableDEMatrix, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks);
    CheckReturnValue(lReturn, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks, &vecSetNames, &vecColumnPositions);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with matching the objects to one another %s", EOL);

    //STEP FOUR
    printf_s("Determine the amount of Biological replicate sets %s", EOL);
    lReturn = FindSets(&vecSetNames, &vecColumnPositions, pTableDEMatrix);
    CheckReturnValue(lReturn, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks, &vecSetNames, &vecColumnPositions);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with determining the amount of Biological replicate sets %s",EOL);

    //STEP FIVE
    //WriteOutputFiles
    printf_s("Write the output files %s", EOL);
    CTableRowHeader* pTableRowHeader = nullptr;
    lReturn = pTableTrinotate->GetHeaderRowTable(&pTableRowHeader);
    CheckReturnValue(lReturn, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks, &vecSetNames, &vecColumnPositions);
    CHECK_RETURNVALUE(lReturn);
    lReturn = WriteOutputFiles(&vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks, &vecSetNames, &vecColumnPositions, pTableRowHeader);
    CheckReturnValue(lReturn, &vecInfernal, &vecDifferentialMatrixBlocks, &vecInfernalOutputBlocks,&vecSetNames, &vecColumnPositions);
    CHECK_RETURNVALUE(lReturn);
    printf_s("Done with writing the output files %s", EOL);

    //STEP FIVE
    //Clean up
    ClearVector(&vecDifferentialMatrixBlocks);
    ClearVector(&vecInfernalOutputBlocks);
    ClearVector(&vecInfernal);
    ClearVector(&vecSetNames);


    //Done :)
    return 0;
}