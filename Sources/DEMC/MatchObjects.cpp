#include "GlobalHelper.h"


long MatchObjects(CFastaFile* pFastaTrinity, CFastaFile* pFastaProtein, CTable* pTableTrinotate, CTable* pTableDEMatrix, std::vector<CInfernal*>* pvecInfernalInput, std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocksOutput, std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutput)
{
	long lReturn = ERR_NOERROR;

	/*
	This function matches the different objects to one another
	
	pvecDifferentialMatrixBlocksOutput
	1) Loop over the Table of pTableDEMatrix
	2) Match the First Column to pFastaTrinity
	3) Match the First column to pTableTrinotate 2nd column
	4) Match the fifth column of pTableTrinotate rows to pFastaProtein
	5) If 4th column of pTableTrinotate row is not .  Match the First Column of ptableDEMatrix to a pInfernal object.



	pvecInfernalOutput
	1) Loop over pvecInfernal
	2) Match pInfernalIsoformID to pFastaTrnity pFastaBlock item
	*/

	bool bFilterFasta = false;
	lReturn = glb.propertyBag.GetBoolFilterOnFastaFile(&bFilterFasta);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_BOOL_FASTA_FILTER_DEMC;


	//pvecDifferentialMatrixBlocksOutput
	size_t sizeDEMatrixvector = pTableDEMatrix->GetAmountOfTableRows();

	CDifferentialMatrixBlock* pDifferentialMatrixBlock = nullptr;
	CDifferentialMatrixBlock* pInfernalCombinedBlock = nullptr;
	std::vector<char*>* pRowDEMatrix = nullptr;
	std::vector<char*>* pRowTrinotate = nullptr;
	CFastaBlock* pFastaBlockTrinity = nullptr;
	CFastaBlock* pFastaBlockProtein = nullptr;
	CInfernal* pInfernal = nullptr;

	char* pMatchingIsoformName = nullptr;
	char* pMatchingProteinsName = nullptr;
	char* pMatchingInfernalName = nullptr;
	//pvecDifferentialMatrixBlocksOutput
	//STEP ONE
	for (size_t idx = 0; idx < sizeDEMatrixvector; idx++)
	{
		pDifferentialMatrixBlock = new CDifferentialMatrixBlock;
		pRowDEMatrix = pTableDEMatrix->GetRow(idx);
		lReturn = pDifferentialMatrixBlock->SetDEMatrixRow(pRowDEMatrix);
		pMatchingIsoformName = pRowDEMatrix->at(0);

		//STEP TWO
		lReturn = pFastaTrinity->GetMatchingFastaBlock(pMatchingIsoformName, &pFastaBlockTrinity);
		if (lReturn != ERR_NOERROR)
		{
			delete pDifferentialMatrixBlock;
			if(bFilterFasta == false)
				return lReturn;

			if (lReturn == FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND)
				lReturn = ERR_NOERROR;

			continue;
		}
		lReturn = pDifferentialMatrixBlock->SetFastaTrinityBlock(pFastaBlockTrinity);
		if (lReturn != ERR_NOERROR)
		{
			delete pDifferentialMatrixBlock;
			return lReturn;
		}

		//STEP THREE
		lReturn = pTableTrinotate->FindMatchingRow(pMatchingIsoformName, &pRowTrinotate, 2); //We are looking for the 2nd column
		if (lReturn != ERR_NOERROR)
		{
			delete pDifferentialMatrixBlock;
			return  lReturn;
		}
		lReturn = pDifferentialMatrixBlock->SetTrinotateRow(pRowTrinotate);
		if (lReturn != ERR_NOERROR)
		{
			delete pDifferentialMatrixBlock;
			return lReturn;
		}

		//STEP FOUR
		pMatchingProteinsName = pRowTrinotate->at(4); //Get the protein Name
		if (*pMatchingProteinsName != '.') //There is no protein matching
		{
			lReturn = pFastaProtein->GetMatchingFastaBlock(pMatchingProteinsName, &pFastaBlockProtein);
			if (lReturn != FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND)
			{
				if (lReturn != ERR_NOERROR)
				{
					delete pDifferentialMatrixBlock;
					return lReturn;
				}
				lReturn = pDifferentialMatrixBlock->SetFastaTrinityProtein(pFastaBlockProtein);
				if (lReturn != ERR_NOERROR)
				{
					delete pDifferentialMatrixBlock;
					return lReturn;
				}
			}
		}
		//STEP FIVE
		pMatchingInfernalName = pRowTrinotate->at(3); //Check if the infernal row is filled or not.
		if (pMatchingInfernalName[0] != '.') //. is not filled so if it's not . it's filled and we can find it. RNA molecules are rare so we don't do them all here.
		{
			//There is a match to an Infernal object.
			lReturn = FindMatchingInfernal(pvecInfernalInput, pRowTrinotate->at(1), &pInfernal); //Compare the transcripts. since the Infernal text does nto match anyway
			if (lReturn != ERR_NOERROR)
			{
				delete pDifferentialMatrixBlock;
				return lReturn;
			}
			lReturn = pDifferentialMatrixBlock->SetInfernal(pInfernal);
			if (lReturn != ERR_NOERROR)
			{
				delete pDifferentialMatrixBlock;
				return lReturn;
			}
		}

		pvecDifferentialMatrixBlocksOutput->push_back(pDifferentialMatrixBlock);

	}

	printf_s("We found %zu different Differential Matrix blocks %s", pvecDifferentialMatrixBlocksOutput->size(), EOL);

	//pvecInfernalOutput
	size_t sizeInfernalVector = pvecInfernalInput->size();
	//STEP ONE
	for (size_t idx = 0; idx < sizeInfernalVector; idx++)
	{
		pInfernalCombinedBlock = new CDifferentialMatrixBlock;
		pInfernal = pvecInfernalInput->at(idx);
		lReturn = pInfernalCombinedBlock->SetInfernal(pInfernal);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernalCombinedBlock;
			return lReturn;
		}

		//STEP TWO
		lReturn = pInfernal->GetInfernalIsoformID(&pMatchingIsoformName);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernalCombinedBlock;
			return lReturn;
		}
		lReturn = pFastaTrinity->GetMatchingFastaBlock(pMatchingIsoformName, &pFastaBlockTrinity);
		if (lReturn != ERR_NOERROR)
		{
			
			delete pInfernalCombinedBlock;
			if(bFilterFasta == false)
				return lReturn;
			
			if (lReturn == FASTAFILE_MATCHING_FASTABLOCK_NOT_FOUND)
				lReturn = ERR_NOERROR;
			continue;
		}
		lReturn = pInfernalCombinedBlock->SetFastaTrinityBlock(pFastaBlockTrinity);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernalCombinedBlock;
			return lReturn;
		}

		pvecInfernalOutput->push_back(pInfernalCombinedBlock);
	
	}

	printf_s("We found %zu different Infernal Objects %s", pvecInfernalOutput->size(), EOL);

	return lReturn;
}

long FindSets(std::vector<char*>* pvecSetNames, std::vector<size_t>* pvecColumnPositions, CTable* pTableDEMatrix)
{
	long lReturn = ERR_NOERROR;

	CTableRowHeader* pTableHeaderRow = nullptr;
	lReturn = pTableDEMatrix->GetHeaderRowTable(&pTableHeaderRow);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	size_t sizeColumns = pTableHeaderRow->GetVectorSize();

	for (size_t idx = 0; idx < sizeColumns - 1; idx++) //-1 since the first column is the Isoform ID
	{
		pvecColumnPositions->push_back(0);
	}

	//Fill the 2 vectors for real
	
	//Start with the first one
	
	char * pColumnObject = pTableHeaderRow->GetVectorItem(1)->GetHeaderName();
	size_t sizeColumnObject = strlen(pColumnObject);
	
	char* pPos = pColumnObject + sizeColumnObject-1; //We want it to look at the last character otherwise it will run in a non readable memory
	MOVE_PTR_TO_PREVIOUS_ALPHA2(pPos);
	pPos++;

	char* pColumnName = nullptr;
	size_t sizeColumnName = pPos - pColumnObject;
	pColumnName = new char[sizeColumnName+10];
	memset(pColumnName, '\0', sizeColumnName+10);
	memcpy(pColumnName, pColumnObject, sizeColumnName);

	size_t index = 0;
	pvecSetNames->push_back(pColumnName);
	pvecColumnPositions->at(0) = index;
	
	//Fill The rest
	for (size_t idx = 2; idx < sizeColumns; idx++)
	{
		pColumnObject = pTableHeaderRow->GetVectorItem(idx)->GetHeaderName();
		if (memcmp(pColumnName, pColumnObject, strlen(pColumnName)) == 0)
		{
			//It's the same
			pvecColumnPositions->at(idx - 1) = index;
		}
		else
		{
			//It's not the same we have to add a new one to the pvecSetNames
			sizeColumnObject = strlen(pColumnObject);
			pPos = pColumnObject + sizeColumnObject-1;
			MOVE_PTR_TO_PREVIOUS_ALPHA2(pPos);
			pPos++;

			sizeColumnName = pPos - pColumnObject;
			pColumnName = new char[sizeColumnName + 10];
			memset(pColumnName, '\0', sizeColumnName + 10);
			memcpy(pColumnName, pColumnObject, sizeColumnName);
			index++;
			pvecSetNames->push_back(pColumnName);
			pvecColumnPositions->at(idx - 1) = index;
		}

	}


	return lReturn;
}