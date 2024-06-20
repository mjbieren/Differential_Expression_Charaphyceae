#include "GlobalHelper.h"
//Other function locations
long DetermineFilebufferSize(size_t* psizeBuffer, std::string strFileName);

//WriteOutput OF Set One




//Own Functions
long FindTrinotateColumnNamesPosition(std::vector<char*>* pvecTrinotateColumnNames, std::vector<size_t>* pvecTrinotateColumnPositions, std::vector<size_t>* pvecKEGGMatrixPositions, CTableRowHeader* pTrinotateTableHeader)
{
	long lReturn = ERR_NOERROR;
	char* pTrinotateColumnName = nullptr;
	char* pDETableColumnName = nullptr;

	size_t sizeTrinotateColumnNames = pvecTrinotateColumnNames->size();
	size_t sizeTrinotateTableHeadersColumns = pTrinotateTableHeader->GetVectorSize();

	bool bColumnFound = false;
	for (size_t idx = 0; idx < sizeTrinotateColumnNames; idx++)
	{
		bColumnFound = false;
		pTrinotateColumnName = pvecTrinotateColumnNames->at(idx);

		for (size_t idx2 = 0; idx2 < sizeTrinotateTableHeadersColumns; idx2++)
		{
			pDETableColumnName = pTrinotateTableHeader->GetVectorItem(idx2)->GetHeaderName();
			if (memcmp(pTrinotateColumnName, pDETableColumnName, strlen(pTrinotateColumnName)) == 0) //Found it;
			{
				pvecTrinotateColumnPositions->push_back(idx2);
				bColumnFound = true;
				break;
			}
		}
		
		if (bColumnFound == false)
			return 0; //ToDo DEMC_SPLIT_DE_NAMES_COLUMN_NOT_FOUND
	}

	//Fill in the KEGG_MATRIX, Kegg, transcript_id,prot_id
	//Find transcript_id

	//KEGG = Transcript_ID, Protein_ID, KEGG
	pvecKEGGMatrixPositions->push_back(0); //Transcript_ID
	pvecKEGGMatrixPositions->push_back(0); //Protein_ID
	pvecKEGGMatrixPositions->push_back(0); //KEGG_KO
	pvecKEGGMatrixPositions->push_back(0); //KEGG_Pathway


	char* pColumnName = nullptr;

	for (size_t idx = 0; idx < sizeTrinotateColumnNames; idx++)
	{
		pColumnName = pvecTrinotateColumnNames->at(idx);
		if (memcmp(pColumnName, "transcript_id", strlen(pColumnName)) == 0)
		{
			pvecKEGGMatrixPositions->at(0) = pvecTrinotateColumnPositions->at(idx);
			continue;

		}
		else if (memcmp(pColumnName, "prot_id", strlen(pColumnName)) == 0)
		{
			pvecKEGGMatrixPositions->at(1) = pvecTrinotateColumnPositions->at(idx);
			continue;

		}
		else if (memcmp(pColumnName, "Kegg", strlen(pColumnName)) == 0)
		{
			pvecKEGGMatrixPositions->at(2) = pvecTrinotateColumnPositions->at(idx);
			continue;
		}
		else if (memcmp(pColumnName, "EggNM.KEGG_Module", strlen(pColumnName)) == 0)
		{
			pvecKEGGMatrixPositions->at(3) = pvecTrinotateColumnPositions->at(idx);
			continue;
		}
	}





	return lReturn;
}

long SplitTrinotateColumnsNames(std::string strColumnSet, std::vector<char*>* pvecTrinotateColumnNames)
{
	long lReturn = ERR_NOERROR;

	//Count how many "," there are.

	size_t sizeColumns = 0;

	for (size_t idx = 0; idx < strColumnSet.size(); idx++)
	{
		if (strColumnSet[idx] == ',')
			sizeColumns++;
	}

	const char* pStart = strColumnSet.c_str();
	const char* pEnd = strColumnSet.c_str();

	char* pDEColumnName = nullptr;

	//Start with the defaults
	//Transcript_ID
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "transcript_id", strlen("transcript_id"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	//Gene_ID
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "#gene_id", strlen("#gene_id"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	//Protein ID
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "prot_id", strlen("prot_id"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	//KEGG_KO
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "Kegg", strlen("Kegg"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	//KEGG_MODULE
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "EggNM.KEGG_Module", strlen("EggNM.KEGG_Module"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	//KEGG_PATHWAY
	pDEColumnName = new char[SIZE_BUFFER_TINY];
	memset(pDEColumnName, '\0', SIZE_BUFFER_TINY);
	memcpy(pDEColumnName, "EggNM.KEGG_Pathwayo", strlen("EggNM.KEGG_Pathway"));
	pvecTrinotateColumnNames->push_back(pDEColumnName);

	size_t sizeColumn = 0;
	for (size_t idx = 0; idx < sizeColumns; idx++)
	{
		MOVE_PTR_TO_COMMA(pEnd); //since it's comma delimited ;)
		sizeColumn = pEnd - pStart;
		if (sizeColumn == 0)
			return DEMC_SPLIT_DE_NAMES_EMPTY_COLUMN_NAME;
		pDEColumnName = new char[sizeColumn +10];
		memset(pDEColumnName, '\0', sizeColumn + 10);
		memcpy(pDEColumnName, pStart, sizeColumn);

		//To Avoid duplicates
		if (memcmp(pDEColumnName, "transcript_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "#gene_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "prot_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "Kegg", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "EggNM.KEGG_Module", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "EggNM.KEGG_Pathway", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else
		{
			pvecTrinotateColumnNames->push_back(pDEColumnName);
		}


		
		//Increase to beyond the ,
		pEnd++;
		pStart = pEnd;

	}

	//Add the the last one (or if the user ended it with the , skip this step

	if (*pEnd && *pEnd != '\0') //Meaning we have still data in our memory
	{
		while (*pEnd) //Move it to the end
			pEnd++;

		sizeColumn = pEnd - pStart;
		if (sizeColumn == 0)
			return 0; //ToDO DEMC_SPLIT_DE_NAMES_EMPTY_COLUMN_NAME
		pDEColumnName = new char[sizeColumn + 10];
		memset(pDEColumnName, '\0', sizeColumn + 10);
		memcpy(pDEColumnName, pStart, sizeColumn);

		if (memcmp(pDEColumnName, "transcript_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "#gene_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "prot_id", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "Kegg", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "EggNM.KEGG_Module", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else if (memcmp(pDEColumnName, "EggNM.KEGG_Pathway", strlen(pDEColumnName)) == 0)
		{
			delete pDEColumnName;
		}
		else
		{
			pvecTrinotateColumnNames->push_back(pDEColumnName);
		}

	}

	//Done
	return lReturn;

}

long FindProteinDescription(size_t * psizePositionProteinDescription, CTableRowHeader* pTrinotateHeaders)
{
	long lReturn = ERR_NOERROR;

	size_t sizeTableRow = pTrinotateHeaders->GetVectorSize();

	char* pColumnName = nullptr;

	bool bFoundHeader = false;

	for (size_t idx = 0; idx < sizeTableRow; idx++)
	{
		pColumnName = pTrinotateHeaders->GetVectorItem(idx)->GetHeaderName();
		if (memcmp(pColumnName, "EggNM.Description", strlen(pColumnName)) == 0)
		{
			//Found it :)
			*psizePositionProteinDescription = idx;
			bFoundHeader = true;
		}
	}

	if (bFoundHeader == false)
		return 0; //ToDo DEMC_PROTEIN_DESCRIPTION_NOT_FOUND

	return lReturn;
}

long GetTrinotateColumnNamesAndPosition(std::vector<char*>* pvecTrinotateColumnNames, std::vector<size_t>* pvecTrinotateColumnPositions, std::vector<size_t>* pvecKEGGMatrixPositions, size_t *psizeProteinDescriptionPosition, CTableRowHeader * pTrinotateTableHeader)
{
	long lReturn = ERR_NOERROR;

	//First get the column Set by the user. The order of the columns provided by the user determines how it will be shown in the output file.
	std::string strColumnSet;
	lReturn = glb.propertyBag.GetTrinotateColumns(&strColumnSet);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_COLUMNS_TO_PARSE_DEMC;

	//Split the Columns up.
	lReturn = SplitTrinotateColumnsNames(strColumnSet, pvecTrinotateColumnNames);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//Find the column names and place the indexes in there
	lReturn = FindTrinotateColumnNamesPosition(pvecTrinotateColumnNames, pvecTrinotateColumnPositions, pvecKEGGMatrixPositions, pTrinotateTableHeader);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	//Find the position for the protein description for the Protein Fasta + Description File.
	lReturn = FindProteinDescription(psizeProteinDescriptionPosition, pTrinotateTableHeader);
	if (lReturn != ERR_NOERROR)
		return lReturn;


	return lReturn;
}

long ParsingRowsInFileBuffersFirstSet(char** ppPosBufferOne, char* pBufferFileOne, size_t* psizeBufferLeftOne, char** ppPosBufferTwo, char* pBufferFileTwo, size_t* psizeBufferLeftTwo, char** ppPosBufferThree, char* pBufferFileThree, size_t* psizeBufferLeftThree, char** ppPosBufferFour, char* pBufferFileFour, size_t* psizeBufferLeftFour, char* pBufferFileFive, size_t* psizeBufferLeftFive, char** ppPosBufferFive, char* pBufferFileSix, size_t* psizeBufferLeftSix, char** ppPosBufferSix, CDifferentialMatrixBlock* pDEMatrixBlock, std::vector<size_t>* pvecIDXPositionsDEMatrix, std::vector<double>* pvecNumberOfSamplesPerSet, std::vector<double> *pvecCombinedLog2Folds, std::vector<size_t>* pvecTrinotateColumnPositions)
{

	char* pPosBufferOne = *ppPosBufferOne;
	char* pPosBufferTwo = *ppPosBufferTwo;
	char* pPosBufferThree = *ppPosBufferThree;
	char* pPosBufferFour = *ppPosBufferFour;
	char* pPosBufferFive = *ppPosBufferFive;
	char* pPosBufferSix = *ppPosBufferSix;

	long lReturn = ERR_NOERROR;
	size_t sizeVectorSet = pvecCombinedLog2Folds->size();
	size_t sizeVectorSamples = pvecIDXPositionsDEMatrix->size();
	size_t sizeVectorTrinotate = pvecTrinotateColumnPositions->size();

	//Ressetting the values (JTBS)
	for (size_t idx = 0; idx < sizeVectorSet; idx++)
	{
		pvecCombinedLog2Folds->at(idx) = 0.0;
	}

	size_t sizeBufferLeftOne = *psizeBufferLeftOne;
	size_t sizeBufferLeftTwo = *psizeBufferLeftTwo;
	size_t sizeBufferLeftThree = *psizeBufferLeftThree;
	size_t sizeBufferLeftFour = *psizeBufferLeftFour;
	size_t sizeBufferLeftFive = *psizeBufferLeftFive;
	size_t sizeBufferLeftSix = *psizeBufferLeftSix;


	//We are first going to set the values for the DE Columns
	//Get the DE ROW
	std::vector<char*>* pRowDE = nullptr;
	lReturn = pDEMatrixBlock->GetDEMatrixRow(&pRowDE);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	char* pColumn = nullptr;
	double dColumn = 0.0;
	double dIncreasingColumn = 0.0;
#ifdef _DEBUG
	std::vector<size_t> vecIDXPositionsDEMatrix = *pvecIDXPositionsDEMatrix;
	vecIDXPositionsDEMatrix = vecIDXPositionsDEMatrix;
#endif

	for (size_t idx = 0; idx < sizeVectorSamples-1; idx++)
	{
		pColumn = pRowDE->at(idx + 1); //since we have also the Transcript_ID that we skip.
		dColumn = atof(pColumn);
		dIncreasingColumn = pvecCombinedLog2Folds->at(pvecIDXPositionsDEMatrix->at(idx));
		pvecCombinedLog2Folds->at(pvecIDXPositionsDEMatrix->at(idx)) = dIncreasingColumn + dColumn;
	}

	//Add the last one
	pColumn = pRowDE->at(sizeVectorSamples); //since we have also the Transcript_ID that we skip.
	dColumn = atof(pColumn);
	dIncreasingColumn = pvecCombinedLog2Folds->at(pvecIDXPositionsDEMatrix->at(sizeVectorSamples-1));
	pvecCombinedLog2Folds->at(pvecIDXPositionsDEMatrix->at(sizeVectorSamples-1)) = dIncreasingColumn + dColumn;

	//Now we have the summed up values for each set. Now we have to divide them based on the number of samples (Creating the MEANS).
	for (size_t idx = 0; idx < sizeVectorSet; idx++)
	{
		pvecCombinedLog2Folds->at(idx) = pvecCombinedLog2Folds->at(idx) / pvecNumberOfSamplesPerSet->at(idx);
	}

	//Now we have the log2Fold means per Set and can fill the rows %0.14f
	std::vector<char*>* pRowTrinotate = nullptr;
	lReturn = pDEMatrixBlock->GetTrinotateRow(&pRowTrinotate);
	double dLog2Fold = 0.0;
	dLog2Fold = dLog2Fold;

	//Filling the first file
	for (size_t idx = 0; idx < sizeVectorTrinotate; idx++)
	{
		pColumn = pRowTrinotate->at(pvecTrinotateColumnPositions->at(idx));
		sizeBufferLeftOne = sizeBufferLeftOne - (pPosBufferOne - pBufferFileOne);
		pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftOne, "%s\t", pColumn);
		sizeBufferLeftOne = sizeBufferLeftOne - (pPosBufferOne - pBufferFileOne);
	}
	//Filling the DE Matrix
	for (size_t idx = 0; idx < sizeVectorSet; idx++)
	{
		dLog2Fold = pvecCombinedLog2Folds->at(idx);
		*psizeBufferLeftOne = *psizeBufferLeftOne - (pPosBufferOne - pBufferFileOne);
		pPosBufferOne += sprintf_s(pPosBufferOne, *psizeBufferLeftOne, "%0.10f\t", dLog2Fold);
		*psizeBufferLeftOne = *psizeBufferLeftOne - (pPosBufferOne - pBufferFileOne);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferOne--;
	sizeBufferLeftOne++;
	//Add an EOL
	pPosBufferOne += sprintf_s(pPosBufferOne, *psizeBufferLeftOne, "%s", EOL);
	sizeBufferLeftOne = sizeBufferLeftOne - (pPosBufferOne - pBufferFileOne);


	//FILE TWO KEGG_MATRIX
	//Filling the Trinotate Part 0,2,3 //Only if there is a protein
	char* pKeggMatch = nullptr;
	if (pDEMatrixBlock->GetBoolProtein() == true)
	{
		sizeBufferLeftTwo = sizeBufferLeftTwo - (pPosBufferTwo - pBufferFileTwo);
		//Check if KEGG is filled or not
		pKeggMatch = pRowTrinotate->at(11);
		//File Two
		if (*pKeggMatch != '.')
		{
			pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftTwo, "%s\t%s\t%s\t", pRowTrinotate->at(1), pRowTrinotate->at(4), pRowTrinotate->at(11));
			sizeBufferLeftTwo = sizeBufferLeftTwo - (pPosBufferTwo - pBufferFileTwo);
			//Filling the DE Matrix
			for (size_t idx = 0; idx < sizeVectorSet; idx++)
			{
				dLog2Fold = pvecCombinedLog2Folds->at(idx);
				sizeBufferLeftTwo = sizeBufferLeftTwo - (pPosBufferTwo - pBufferFileTwo);
				pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftTwo, "%0.10f\t", dLog2Fold);
				sizeBufferLeftTwo = sizeBufferLeftTwo - (pPosBufferTwo - pBufferFileTwo);
			}
			//Remove pPosBufferTwo TAB and replace it for EOL
			pPosBufferTwo--;
			sizeBufferLeftTwo++;
			//Add an EOL
			pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftTwo, "%s", EOL);
			sizeBufferLeftTwo = sizeBufferLeftTwo - (pPosBufferTwo - pBufferFileTwo);
		}
		//File FIVE // KEGG MODULE
		pKeggMatch = pRowTrinotate->at(27); 
		if (*pKeggMatch != '.')
		{
			pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftFive, "%s\t%s\t%s\t", pRowTrinotate->at(1), pRowTrinotate->at(4), pRowTrinotate->at(27));
			sizeBufferLeftFive = sizeBufferLeftFive - (pPosBufferFive - pBufferFileFive);
			//Filling the DE Matrix
			for (size_t idx = 0; idx < sizeVectorSet; idx++)
			{
				dLog2Fold = pvecCombinedLog2Folds->at(idx);
				sizeBufferLeftFive = sizeBufferLeftFive - (pPosBufferFive - pBufferFileFive);
				pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftFive, "%0.10f\t", dLog2Fold);
				sizeBufferLeftFive = sizeBufferLeftFive - (pPosBufferFive - pBufferFileFive);
			}
			//Remove pPosBufferTwo TAB and replace it for EOL
			pPosBufferFive--;
			sizeBufferLeftFive++;
			//Add an EOL
			pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftFive, "%s", EOL);
			sizeBufferLeftFive = sizeBufferLeftFive - (pPosBufferFive - pBufferFileFive);
		}

		//File Six //KEGG Pathway
		pKeggMatch = pRowTrinotate->at(26); 
		if (*pKeggMatch != '.')
		{
			pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftSix, "%s\t%s\t%s\t", pRowTrinotate->at(1), pRowTrinotate->at(4), pRowTrinotate->at(26));
			sizeBufferLeftSix = sizeBufferLeftSix - (pPosBufferSix - pBufferFileSix);
			//Filling the DE Matrix
			for (size_t idx = 0; idx < sizeVectorSet; idx++)
			{
				dLog2Fold = pvecCombinedLog2Folds->at(idx);
				sizeBufferLeftSix = sizeBufferLeftSix - (pPosBufferSix - pBufferFileSix);
				pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftSix, "%0.10f\t", dLog2Fold);
				sizeBufferLeftSix = sizeBufferLeftSix - (pPosBufferSix - pBufferFileSix);
			}
			//Remove pPosBufferTwo TAB and replace it for EOL
			pPosBufferSix--;
			sizeBufferLeftSix++;
			//Add an EOL
			pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftSix, "%s", EOL);
			sizeBufferLeftSix = sizeBufferLeftSix - (pPosBufferSix - pBufferFileSix);
		}


	}

	//FILE THREE AND FILE FOUR INFERNAL MATRIX & INFERNAL FASTA FILTERED and File Five.
	if (pDEMatrixBlock->GetInfernalBool() == true)
	{
		CInfernal* pInfernal = nullptr;

		lReturn = pDEMatrixBlock->GetInfernal(&pInfernal);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		CFastaBlock* pFastaTrinity = nullptr;
		lReturn = pDEMatrixBlock->GetFastaTrinityBlock(&pFastaTrinity);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		char* pTranscriptID = nullptr;
		char* pAccession = nullptr;
		char* pDescription = nullptr;
		char* pFastaSequence = nullptr;

		lReturn = pInfernal->GetInfernalIsoformID(&pTranscriptID);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pInfernal->GetInfernalAccession(&pAccession);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pInfernal->GetInfernalDescription(&pDescription);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pFastaTrinity->GetFastaSequence(&pFastaSequence);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		//INFERNAL MATRIX
		sizeBufferLeftThree = sizeBufferLeftThree - (pPosBufferThree - pBufferFileThree);
		pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftThree, "%s\t%s\t%s\t", pTranscriptID, pAccession, pDescription);
		sizeBufferLeftThree = sizeBufferLeftThree - (pPosBufferThree - pBufferFileThree);
		//Filling the DE Matrix
		for (size_t idx = 0; idx < sizeVectorSet; idx++)
		{
			dLog2Fold = pvecCombinedLog2Folds->at(idx);
			sizeBufferLeftThree = sizeBufferLeftThree - (pPosBufferThree - pBufferFileThree);
			pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftThree, "%0.10f\t", dLog2Fold);
			sizeBufferLeftThree = sizeBufferLeftThree - (pPosBufferThree - pBufferFileThree);
		}
		//Remove pPosBufferTwo TAB and replace it for EOL
		pPosBufferThree--;
		sizeBufferLeftThree++;
		//Add an EOL
		pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftThree, "%s", EOL);
		sizeBufferLeftThree = sizeBufferLeftThree - (pPosBufferThree - pBufferFileThree);

		//INFERNAL FASTA FILE
		sizeBufferLeftFour = sizeBufferLeftFour - (pPosBufferFour - pBufferFileFour);
		pPosBufferFour += sprintf_s(pPosBufferFour, sizeBufferLeftFour, ">%s %s %s%s%s%s", pTranscriptID, pAccession, pDescription,EOL,pFastaSequence,EOL);
		sizeBufferLeftFour = sizeBufferLeftFour - (pPosBufferFour - pBufferFileFour);

	

	}

	*psizeBufferLeftOne = sizeBufferLeftOne;
	*psizeBufferLeftTwo = sizeBufferLeftTwo;
	*psizeBufferLeftThree = sizeBufferLeftThree;
	*psizeBufferLeftFour = sizeBufferLeftFour;
	*psizeBufferLeftFive = sizeBufferLeftFive;
	*psizeBufferLeftSix = sizeBufferLeftSix;

	*ppPosBufferOne = pPosBufferOne;
	*ppPosBufferTwo = pPosBufferTwo;
	*ppPosBufferThree = pPosBufferThree;
	*ppPosBufferFour = pPosBufferFour;
	*ppPosBufferFive = pPosBufferFive;
	*ppPosBufferSix = pPosBufferSix;


	return lReturn;
}



long SetDetermineColumnsPositions(size_t sizeVecSetNames, std::vector<double> *pvecHitsPerSetname, std::vector<double>* pvecCombinedLog2Folds, std::vector<size_t>* pvecColumnPositions)
{
	long lReturn = ERR_NOERROR;

	for (size_t idx = 0; idx < sizeVecSetNames; idx++)
	{
		pvecHitsPerSetname->push_back(0.0);
		pvecCombinedLog2Folds->push_back(0.0);
	}

	//Now we determine how much samples we have per set.
	size_t sizeColumnsPosistion = pvecColumnPositions->size();

	size_t sizeNumberPosition = 0;

	double dNumberSetValue = 0;

	for (size_t idx = 0; idx < sizeColumnsPosistion; idx++)
	{
		//Determine which set it is
		sizeNumberPosition = pvecColumnPositions->at(idx);

		//Get the Set and increase it by 1
		dNumberSetValue = (double)pvecHitsPerSetname->at(sizeNumberPosition);
		dNumberSetValue++;

		//Replace the Set value with the increased value
		pvecHitsPerSetname->at(sizeNumberPosition) = dNumberSetValue;

	}


	return lReturn;
}

long SetFileBuffers(char** ppFileBufferOne, char** ppFileBufferTwo, char** ppFileBufferThree, char** ppFileBufferFour, char** ppFileBufferFive, char** ppFileBufferSix, size_t * psizeFileBuffer)
{
	long lReturn = ERR_NOERROR;
	//Setting the file buffers. We Base these file buffers on the biggest file, which is the trinotate file.
	std::string strTrinotateFilePath;
	lReturn = glb.propertyBag.GetTrinotatePath(&strTrinotateFilePath);
	if (lReturn != ERR_NOERROR)
		return PROTERTYBAG_TRINOTATE_REPORT_DEMC;

	size_t sizeFileBuffers = 0;
	lReturn = DetermineFilebufferSize(&sizeFileBuffers, strTrinotateFilePath);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	*psizeFileBuffer = sizeFileBuffers;

	//We need 6 file buffers simulteanously :)
	char* pFileBufferOne = new char[sizeFileBuffers + 10];
	memset(pFileBufferOne, '\0', sizeFileBuffers + 10);

	char* pFileBufferTwo = new char[sizeFileBuffers + 10];
	memset(pFileBufferTwo, '\0', sizeFileBuffers + 10);

	char* pFileBufferThree = new char[sizeFileBuffers + 10];
	memset(pFileBufferThree, '\0', sizeFileBuffers + 10);

	char* pFileBufferFour = new char[sizeFileBuffers + 10];
	memset(pFileBufferFour, '\0', sizeFileBuffers + 10);

	char* pFileBufferFive = new char[sizeFileBuffers + 10];
	memset(pFileBufferFive, '\0', sizeFileBuffers + 10);

	char* pFileBufferSix = new char[sizeFileBuffers + 10];
	memset(pFileBufferSix, '\0', sizeFileBuffers + 10);

	*ppFileBufferOne = pFileBufferOne;
	*ppFileBufferTwo = pFileBufferTwo;
	*ppFileBufferThree = pFileBufferThree;
	*ppFileBufferFour = pFileBufferFour;
	*ppFileBufferFive = pFileBufferFive;
	*ppFileBufferSix = pFileBufferSix;


	return lReturn;
}

long WriteOutputFiles(const std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocks, const std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutputBlocks, std::vector<char*> *pvecBiologicalSetNames, std::vector<size_t>* pvecSamplesVsBiologicalSetPositions, CTableRowHeader * pTrinotateTableHeaders)
{
	long lReturn = ERR_NOERROR;


	//We are now going to write the different output files
	// 3 different matrix (Tables)
	// 5 Different Fasta files
	//We start with 3 Matrixes simulteanously (Filtered_DE_Matrix, and the KEGG_MATRIX, Infernal Matrix) + the Infernal filtered fasta file (4 Files)
	//Again go over the pvecDifferentialMatrixBlocks and fill the Protein Fasta file + Description, Protein Fasta File and the IsoForm Fasta File
	//Followed by looping over the pvecInfernalOutput vector to fill the unfiltered Infernal fasta file based on the vecInfernal.
	
	//Get Prefix
	std::string strPrefix;
	lReturn = glb.propertyBag.GetPrefixValue(&strPrefix);
	if (lReturn != ERR_NOERROR)
	{
		strPrefix = ""; //Empty
	}


	//Get Output Folder
	std::string strOutputFolderPath;
	lReturn = glb.propertyBag.GetOutputDir(&strOutputFolderPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_OUTPUTFOLDER_DEMC;

	std::vector<char*> vecTrinotateColumnNames;
	std::vector<size_t> vecTrinotateColumnPositions;
	std::vector<size_t> vecKEGGMatrixPositions;
	
	size_t sizeProteinDescriptionPosition = 0;

	lReturn = GetTrinotateColumnNamesAndPosition(&vecTrinotateColumnNames, &vecTrinotateColumnPositions,&vecKEGGMatrixPositions,&sizeProteinDescriptionPosition, pTrinotateTableHeaders);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(&vecTrinotateColumnNames);
		vecTrinotateColumnPositions.clear();
		return lReturn;
	}

	size_t sizeTrinotateColumns = vecTrinotateColumnNames.size();
	size_t sizeBiologicalSetNames = pvecBiologicalSetNames->size();
	

	char* pFileBufferOne = nullptr;
	char* pFileBufferTwo = nullptr;
	char* pFileBufferThree = nullptr;
	char* pFileBufferFour = nullptr;
	char* pFileBufferFive = nullptr;
	char* pFileBufferSix = nullptr;

	size_t sizeFileBuffers = 0;

	lReturn = SetFileBuffers(&pFileBufferOne, &pFileBufferTwo, &pFileBufferThree, &pFileBufferFour, &pFileBufferFive, &pFileBufferSix, &sizeFileBuffers);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(&vecTrinotateColumnNames);
		vecTrinotateColumnPositions.clear();
		return lReturn;
	}

	CSmartPtr<char> pAutoDeleteBufferOne = pFileBufferOne;
	CSmartPtr<char> pAutoDeleteBufferTwo = pFileBufferTwo;
	CSmartPtr<char> pAutoDeleteBufferThree = pFileBufferThree;
	CSmartPtr<char> pAutoDeleteBufferFour = pFileBufferFour;
	CSmartPtr<char> pAutoDeleteBufferFive = pFileBufferFive;
	CSmartPtr<char> pAutoDeleteBufferSix = pFileBufferSix;

	//Time to determine how many columns we have for the DE. We need 2 arrays One for summing up during the sets
	size_t sizeColumnVectors = pvecBiologicalSetNames->size();
	std::vector<double> vecNumberOfSamplesPerSet;
	std::vector<double> vecCombinedLog2Folds;
	

	lReturn = SetDetermineColumnsPositions(sizeColumnVectors, &vecNumberOfSamplesPerSet, &vecCombinedLog2Folds, pvecSamplesVsBiologicalSetPositions);
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(&vecTrinotateColumnNames);
		vecTrinotateColumnPositions.clear();
		vecNumberOfSamplesPerSet.clear();
		return lReturn;
	}

	//Set the file buffer lefts and the position pointers in the buffer.
	//SizeBuffer lefts
	size_t sizeBufferLeftBufferOne = sizeFileBuffers;
	size_t sizeBufferLeftBufferTwo = sizeFileBuffers;
	size_t sizeBufferLeftBufferThree = sizeFileBuffers;
	size_t sizeBufferLeftBufferFour = sizeFileBuffers;
	size_t sizeBufferLeftBufferFive = sizeFileBuffers;
	size_t sizeBufferLeftBufferSix = sizeFileBuffers;
	
	//Position Buffers
	char* pPosBufferOne = pFileBufferOne;
	char* pPosBufferTwo = pFileBufferTwo;
	char* pPosBufferThree = pFileBufferThree;
	char* pPosBufferFour = pFileBufferFour;
	char* pPosBufferFive = pFileBufferFive;
	char* pPosBufferSix = pFileBufferSix;

	//Time to fill the file buffers of the first 4 files.
	//1) Filtered_DE_Matrix
	//2) KEGG_KO_MATRIX
	//3) Infernal Matrix
	//4) Infernal_Fasta_Filtered
	//5) KEGG_Pathway_Matrix

	//Filtered_TRINOTATE_MATRIX		BUFFER_ONE
	//KEGG_Matrix					BUFFER_TWO
	//Infernal_Matrix_Filtered		BUFFER_THREE
	//Filtered_Infernal_Fasta_File	BUFFER_FOUR

	//Start with the header of BUFFER_ONE




	char* pColumnFiller = nullptr;
	///////////////////
	//HEADERS FIRSSST//
	//////////////////
	
	
	//FILTERED_TRINOTATE_MATRIX - FILE ONE
	//TrinotateColumns
	for (size_t idx = 0; idx < sizeTrinotateColumns; idx++)
	{
		pColumnFiller = vecTrinotateColumnNames.at(idx);
		sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);
		pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftBufferOne, "%s\t", pColumnFiller);
	}
	//DE Columns
	for (size_t idx = 0; idx < sizeBiologicalSetNames; idx++)
	{
		pColumnFiller = pvecBiologicalSetNames->at(idx);
		sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);
		pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftBufferOne, "%s\t", pColumnFiller);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferOne--;
	sizeBufferLeftBufferOne++;
	//Add an EOL
	pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftBufferOne, "%s", EOL);
	sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);




	//KEGG_MATRIX_KO - FILE TWO
	//Fill the first 3.
	sizeBufferLeftBufferTwo = sizeBufferLeftBufferTwo - (pPosBufferTwo - pFileBufferTwo);
	pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftBufferTwo, "Transcript_ID\tProtein_ID\tKEGG_KO\t");
	//DE Columns
	for (size_t idx = 0; idx < sizeBiologicalSetNames; idx++)
	{
		pColumnFiller = pvecBiologicalSetNames->at(idx);
		sizeBufferLeftBufferTwo = sizeBufferLeftBufferTwo - (pPosBufferTwo - pFileBufferTwo);
		pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftBufferTwo, "%s\t", pColumnFiller);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferTwo--;
	sizeBufferLeftBufferTwo++;
	//Add an EOL
	pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftBufferTwo, "%s", EOL);
	sizeBufferLeftBufferTwo = sizeBufferLeftBufferTwo - (pPosBufferTwo - pFileBufferTwo);


	//KEGG_MATRIX_PATHWAY - FILE FIVE
	//Fill the first 3.
	sizeBufferLeftBufferFive = sizeBufferLeftBufferFive - (pPosBufferFive - pFileBufferFive);
	pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftBufferFive, "Transcript_ID\tProtein_ID\tKEGG_Module\t");
	//DE Columns
	for (size_t idx = 0; idx < sizeBiologicalSetNames; idx++)
	{
		pColumnFiller = pvecBiologicalSetNames->at(idx);
		sizeBufferLeftBufferFive = sizeBufferLeftBufferFive - (pPosBufferFive - pFileBufferFive);
		pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftBufferFive, "%s\t", pColumnFiller);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferFive--;
	sizeBufferLeftBufferFive++;
	//Add an EOL
	pPosBufferFive += sprintf_s(pPosBufferFive, sizeBufferLeftBufferFive, "%s", EOL);
	sizeBufferLeftBufferFive = sizeBufferLeftBufferFive - (pPosBufferFive - pFileBufferFive);

	//KEGG_MATRIX_PATHWAY - FILE Six
	//Fill the first 3.
	sizeBufferLeftBufferSix = sizeBufferLeftBufferSix - (pPosBufferSix - pFileBufferSix);
	pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftBufferSix, "Transcript_ID\tProtein_ID\tKEGG_Pathway\t");
	//DE Columns
	for (size_t idx = 0; idx < sizeBiologicalSetNames; idx++)
	{
		pColumnFiller = pvecBiologicalSetNames->at(idx);
		sizeBufferLeftBufferSix = sizeBufferLeftBufferSix - (pPosBufferSix - pFileBufferSix);
		pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftBufferSix, "%s\t", pColumnFiller);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferSix--;
	sizeBufferLeftBufferSix++;
	//Add an EOL
	pPosBufferSix += sprintf_s(pPosBufferSix, sizeBufferLeftBufferSix, "%s", EOL);
	sizeBufferLeftBufferSix = sizeBufferLeftBufferSix - (pPosBufferSix - pFileBufferSix);




	//INFERNAL_MATRIX_FILTERED - FILE THREE
	//Fill the first 3.
	sizeBufferLeftBufferThree = sizeBufferLeftBufferThree - (pPosBufferThree - pFileBufferThree);
	pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftBufferThree, "Transcript_ID\tAccession\tDescription\t");
	//DE Columns
	for (size_t idx = 0; idx < sizeBiologicalSetNames; idx++)
	{
		pColumnFiller = pvecBiologicalSetNames->at(idx);
		sizeBufferLeftBufferThree = sizeBufferLeftBufferThree - (pPosBufferThree - pFileBufferThree);
		pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftBufferThree, "%s\t", pColumnFiller);
	}
	//Remove last TAB and replace it for EOL
	pPosBufferThree--;
	sizeBufferLeftBufferThree++;
	//Add an EOL
	pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftBufferThree, "%s", EOL);
	sizeBufferLeftBufferThree = sizeBufferLeftBufferThree - (pPosBufferThree - pFileBufferThree);

	//INFERNAL FASTA FILE - FILE FOUR DOES NOT HAVE A HEADER
	//SKIP




	/////////////////////
	///FILL THE DATA////
	///////////////////

	//Looping over the DE Matrix blocks vector

	size_t sizeDEMatrixBlocks = pvecDifferentialMatrixBlocks->size();
	CDifferentialMatrixBlock* pDEMatrixBlock = nullptr;
	

	for (size_t idx = 0; idx < sizeDEMatrixBlocks; idx++)
	{
		pDEMatrixBlock = pvecDifferentialMatrixBlocks->at(idx);
		lReturn = ParsingRowsInFileBuffersFirstSet(&pPosBufferOne, pFileBufferOne, &sizeBufferLeftBufferOne, &pPosBufferTwo, pFileBufferTwo, &sizeBufferLeftBufferTwo, &pPosBufferThree, pFileBufferThree, &sizeBufferLeftBufferThree, &pPosBufferFour, pFileBufferFour, &sizeBufferLeftBufferFour, pFileBufferFive, &sizeBufferLeftBufferFive, &pPosBufferFive, pFileBufferSix, &sizeBufferLeftBufferSix, &pPosBufferSix, pDEMatrixBlock, pvecSamplesVsBiologicalSetPositions, &vecNumberOfSamplesPerSet, &vecCombinedLog2Folds, &vecTrinotateColumnPositions);
		if (lReturn != ERR_NOERROR)
			return lReturn;

	}


	//We have to remove the last EOL for every File Buffer
	pPosBufferOne--;
	*pPosBufferOne = '\0';

	pPosBufferTwo--;
	*pPosBufferTwo = '\0';

	pPosBufferThree--;
	*pPosBufferThree = '\0';

	pPosBufferFour--;
	*pPosBufferFour = '\0';

	pPosBufferFive--;
	*pPosBufferFive = '\0';

	pPosBufferSix--;
	*pPosBufferSix = '\0';

	//Write the output files for the first set.
	std::string strFilePathFilteredTrinotateMatrix = strOutputFolderPath + strPrefix + "_Filtered_Trinotate_DE_Matrix.tsv";
	std::string strFilePathKeggKOMatrix = strOutputFolderPath + strPrefix + "_Filtered_DE_KEGG_KO_Matrix.tsv";
	std::string strFilePathInfernalMatrix = strOutputFolderPath + strPrefix +  "_Filtered_DE_Infernal_Matrix.tsv";
	std::string strFilePathInfernalFastaFile = strOutputFolderPath + strPrefix + "_Filtered_Infernal.fa";
	std::string strFilePathKEGGModule =  strOutputFolderPath + strPrefix + "_Filtered_DE_KEGG_Module_Matrix.tsv";
	std::string strFilePathKEGGPathway =  strOutputFolderPath + strPrefix + "_Filtered_DE_KEGG_Pathway_Matrix.tsv";


	lReturn = WriteOutputFile(pFileBufferOne, strFilePathFilteredTrinotateMatrix);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferTwo, strFilePathKeggKOMatrix);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferThree, strFilePathInfernalMatrix);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferFour, strFilePathInfernalFastaFile);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferFive, strFilePathKEGGModule);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	lReturn = WriteOutputFile(pFileBufferSix, strFilePathKEGGPathway);
	if (lReturn != ERR_NOERROR)
		return lReturn;




	//MEMSET THE FILE BUFFERS!
	memset(pFileBufferOne, '\0', sizeFileBuffers);
	memset(pFileBufferTwo, '\0', sizeFileBuffers);
	memset(pFileBufferThree, '\0', sizeFileBuffers);
	memset(pFileBufferFour, '\0', sizeFileBuffers);
	memset(pFileBufferFive, '\0', sizeFileBuffers);
	memset(pFileBufferSix, '\0', sizeFileBuffers);

	//Reset the positions of the pPos and the sizeBuffers left
	pPosBufferOne = pFileBufferOne;
	sizeBufferLeftBufferOne = sizeFileBuffers;
	pPosBufferTwo = pFileBufferTwo;
	sizeBufferLeftBufferTwo = sizeFileBuffers;
	pPosBufferThree = pFileBufferThree;
	sizeBufferLeftBufferThree = sizeFileBuffers;
	pPosBufferFour = pFileBufferFour;
	sizeBufferLeftBufferFour = sizeFileBuffers;
	pPosBufferFive = pFileBufferFive;
	sizeBufferLeftBufferFive = sizeFileBuffers;
	pPosBufferSix = pFileBufferSix;
	sizeBufferLeftBufferSix = sizeFileBuffers;


	//3 Fasta Files
	//1) Protein Fasta File + Description
	//2) Protein Fasta File
	//3) Isoform Fasta File

	std::vector<char*>* pRowTrinotate = nullptr;
	CFastaBlock* pTrinity = nullptr;
	CFastaBlock* pProtein = nullptr;
	char* pTrinitySequence = nullptr;
	char* pProteinSequence = nullptr;
	char* pProteinDescription = nullptr;

	char* pProteinID = nullptr;
	char* pTranscriptID = nullptr;
	bool bProtein = false;

	for (size_t idx = 0; idx < sizeDEMatrixBlocks; idx++)
	{
		pDEMatrixBlock = pvecDifferentialMatrixBlocks->at(idx);
		lReturn = pDEMatrixBlock->GetTrinotateRow(&pRowTrinotate);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		pTranscriptID = pRowTrinotate->at(0); //Transcript ID
		
		bProtein = pDEMatrixBlock->GetBoolProtein();

		lReturn = pDEMatrixBlock->GetFastaTrinityBlock(&pTrinity);
		if (lReturn != ERR_NOERROR)
			return lReturn;
		lReturn = pTrinity->GetFastaSequence(&pTrinitySequence);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		
		if (bProtein == true)
		{
			pProteinID = pRowTrinotate->at(4); //Protein ID
			pProteinDescription = pRowTrinotate->at(sizeProteinDescriptionPosition); //Protein Description

			lReturn = pDEMatrixBlock->GetFastaProteinBlock(&pProtein);
			if (lReturn != ERR_NOERROR)
				return lReturn;
			lReturn = pProtein->GetFastaSequence(&pProteinSequence);
			if (lReturn != ERR_NOERROR)
				return lReturn;


			//File Buffer one
			sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);
			pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftBufferOne, ">%s %s%s%s%s", pProteinID, pProteinDescription, EOL, pProteinSequence, EOL);
			sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);

			//File Buffer two
			sizeBufferLeftBufferTwo = sizeBufferLeftBufferTwo - (pPosBufferTwo - pFileBufferTwo);
			pPosBufferTwo += sprintf_s(pPosBufferTwo, sizeBufferLeftBufferTwo, ">%s%s%s%s", pProteinID, EOL, pProteinSequence, EOL);
			sizeBufferLeftBufferTwo = sizeBufferLeftBufferTwo - (pPosBufferTwo - pFileBufferTwo);
		}
		//File Buffer Three
		sizeBufferLeftBufferThree = sizeBufferLeftBufferThree - (pPosBufferThree - pFileBufferThree);
		pPosBufferThree += sprintf_s(pPosBufferThree, sizeBufferLeftBufferThree, ">%s%s%s%s", pTranscriptID, EOL, pTrinitySequence, EOL);
		sizeBufferLeftBufferThree = sizeBufferLeftBufferThree - (pPosBufferThree - pFileBufferThree);


	}

	//We have to remove the last EOL for every File Buffer
	pPosBufferOne--;
	*pPosBufferOne = '\0';

	pPosBufferTwo--;
	*pPosBufferTwo = '\0';

	pPosBufferThree--;
	*pPosBufferThree = '\0';

	//Write Output file for the 2nd set
	std::string strFilePathProteinDescriptionFasta = strOutputFolderPath + strPrefix + "_DE_Protein_With_Description.faa";
	std::string strFilePathProteinFasta = strOutputFolderPath + strPrefix + "_DE_Protein_Without_Description.faa";
	std::string strFilePathTranscriptFasta = strOutputFolderPath + strPrefix + "_DE_Transcripts.fa";

	lReturn = WriteOutputFile(pFileBufferOne, strFilePathProteinDescriptionFasta);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferTwo, strFilePathProteinFasta);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = WriteOutputFile(pFileBufferThree, strFilePathTranscriptFasta);
	if (lReturn != ERR_NOERROR)
		return lReturn;


	//MEMSET THE FILE BUFFERS!
	memset(pFileBufferOne, '\0', sizeFileBuffers);
	memset(pFileBufferTwo, '\0', sizeFileBuffers);
	memset(pFileBufferThree, '\0', sizeFileBuffers);
	memset(pFileBufferFour, '\0', sizeFileBuffers);

	//Reset the positions of the pPos and the sizeBuffers left
	pPosBufferOne = pFileBufferOne;
	sizeBufferLeftBufferOne = sizeFileBuffers;
	pPosBufferTwo = pFileBufferTwo;
	sizeBufferLeftBufferTwo = sizeFileBuffers;
	pPosBufferThree = pFileBufferThree;
	sizeBufferLeftBufferThree = sizeFileBuffers;
	pPosBufferFour = pFileBufferFour;
	sizeBufferLeftBufferFour = sizeFileBuffers;


	//Last but not least the Infernal Fasta File
	size_t sizeInfernal = pvecInfernalOutputBlocks->size();
	CInfernal* pInfernal = nullptr;
	char* pInfernalTranscriptionID = nullptr;
	char* pInfernalAccession = nullptr;
	char* pInfernalDescription = nullptr;

	

	for (size_t idx = 0; idx < sizeInfernal; idx++)
	{
		pDEMatrixBlock = pvecInfernalOutputBlocks->at(idx);
		lReturn = pDEMatrixBlock->GetInfernal(&pInfernal);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pDEMatrixBlock->GetFastaTrinityBlock(&pTrinity);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pInfernal->GetInfernalAccession(&pInfernalAccession);
		if (lReturn != ERR_NOERROR)
			return lReturn;
		lReturn = pInfernal->GetInfernalDescription(&pInfernalDescription);
		if (lReturn != ERR_NOERROR)
			return lReturn;
		lReturn = pInfernal->GetInfernalIsoformID(&pInfernalTranscriptionID);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		lReturn = pTrinity->GetFastaSequence(&pTrinitySequence);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);
		pPosBufferOne += sprintf_s(pPosBufferOne, sizeBufferLeftBufferOne, ">%s %s %s%s%s%s", pInfernalTranscriptionID, pInfernalAccession, pInfernalDescription,EOL,pTrinitySequence,EOL);
		sizeBufferLeftBufferOne = sizeBufferLeftBufferOne - (pPosBufferOne - pFileBufferOne);

	}


	//We have to remove the last EOL
	pPosBufferOne--;
	*pPosBufferOne = '\0';

	std::string strFilePathInfernalFull = strOutputFolderPath + strPrefix + "_Infernal_Unfiltered.fa";

	lReturn = WriteOutputFile(pFileBufferOne, strFilePathInfernalFull);
	if (lReturn != ERR_NOERROR)
		return lReturn;



	//Done with all clean up

	/*
	std::vector<char*> vecTrinotateColumnNames;
	std::vector<size_t> vecTrinotateColumnPositions;
	std::vector<size_t> vecKEGGMatrixPositions;
	std::vector<double> vecNumberOfSamplesPerSet;
	std::vector<double> vecCombinedLog2Folds;
	
	*/
	ClearVector(&vecTrinotateColumnNames);
	vecTrinotateColumnPositions.clear();
	vecKEGGMatrixPositions.clear();
	vecNumberOfSamplesPerSet.clear();
	vecCombinedLog2Folds.clear();


	return lReturn;
}