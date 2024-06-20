#include "GlobalHelper.h"


long WriteOutputFile(CTable* pKEGGMatrix, std::vector<CKEGGSet*>* pvecKEGGSet)
{
	long lReturn = ERR_NOERROR;

	size_t sizeRowColumns = pKEGGMatrix->GetRow(0)->size();

	char* pFileBuffer = new char[SIZE_BUFFER_ONE_GIG];
	CSmartPtr<char> pAutoDelete = pFileBuffer;
	memset(pFileBuffer, '\0', SIZE_BUFFER_ONE_GIG);

	size_t sizeBufferLeft = SIZE_BUFFER_ONE_GIG;
	char* pPos = pFileBuffer;

	//GEt Threshold values

	long lThresholdSet = 0;
	lReturn = glb.propertyBag.GetThresholdMinimumSets(&lThresholdSet);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_THRESHOLD_SETSAVAILABLE_KEGGCOUNTER;

	long lThresholdHitsMinimum = 0;
	lReturn = glb.propertyBag.GetThresholdMinimumCounter(&lThresholdHitsMinimum);
	if(lReturn != ERR_NOERROR)
		return PROPERTYBAG_THRESHOLD_HITS_KEGGCOUNTER;

	CTableRowHeader* pHeader = nullptr;
	lReturn = pKEGGMatrix->GetHeaderRowTable(&pHeader);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	CTableColumnHeader* pColumn = nullptr;

	
	
	size_t sizeVectorOfAKeggSet = pvecKEGGSet->at(0)->GetVectorsize();
	



	//Write header
	//KEGG DESCRIPTION -> GOR_UP -> GOR_DOWN, RED_UP, RED_DOWN

	sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
	pPos += sprintf_s(pPos, sizeBufferLeft, "KEGG_ID\tKEGG_Description\t");
	sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);

	for (size_t idx = 3; idx < sizeRowColumns; idx++)
	{
		pColumn = pHeader->GetVectorItem(idx);
		sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
		pPos += sprintf_s(pPos, sizeBufferLeft, "%s_UP\t%s_DOWN\t", pColumn->GetHeaderName(),pColumn->GetHeaderName());
		sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
	}



	//Remove last TAB and replace it for EOL
	pPos--;
	sizeBufferLeft++;
	//Add an EOL
	pPos += sprintf_s(pPos, sizeBufferLeft, "%s", EOL);
	sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);




	bool bAddRow = false;
	//Now we fill the rest.
	CKEGGSet* pKeggSet = nullptr;
	size_t sizeVector = pvecKEGGSet->size();

	for (size_t idx = 0; idx < sizeVector; idx++)
	{
		pKeggSet = pvecKEGGSet->at(idx);
		lReturn = pKeggSet->CheckCombinedThreshold(&bAddRow, (size_t)lThresholdSet, (size_t)lThresholdHitsMinimum);
		if (lReturn != ERR_NOERROR)
			return lReturn;

		if (bAddRow == true)
		{
#ifdef _DEBUG
			printf_s("Working on row %zu / %zu, which will be added into the output file %s", idx + 1, sizeVector, EOL);
#endif
			sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
			pPos += sprintf_s(pPos, sizeBufferLeft, "%s\t%s\t", pKeggSet->GetKEGGID(), pKeggSet->GetKEGGRowDescription());
			sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);


			for (size_t idx2 = 0; idx2 < sizeVectorOfAKeggSet; idx2++)
			{
				sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
				pPos += sprintf_s(pPos, sizeBufferLeft, "%lu\t", pKeggSet->GetVectorItem(idx2));
				sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
			}

			//Remove last TAB and replace it for EOL
			pPos--;
			sizeBufferLeft++;
			//Add an EOL
			pPos += sprintf_s(pPos, sizeBufferLeft, "%s", EOL);
			sizeBufferLeft = sizeBufferLeft - (pPos - pFileBuffer);
			

		}

	}

	//Remove last EOL
	pPos--;
	*pPos = '\0';


	//Time to get the output path

	std::string strFileOutputPath;
	lReturn = glb.propertyBag.GetOutputFolder(&strFileOutputPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_OUTPUT_FOLDER_KEGGCOUNTER;

	std::string strOutPrefix;
	lReturn = glb.propertyBag.GetOutputPrefix(&strOutPrefix); //Should not be cuz it has a default value.
	if (lReturn != ERR_NOERROR)
		return lReturn;

	float fDEThreshold = 0.0;
	lReturn = glb.propertyBag.GetThresholdDE(&fDEThreshold);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_THRESHOLD_DE_KEGGCOUNTER;

	char* pFileNameBuffer = new char[SIZE_BUFFER_MEDIUM];
	CSmartPtr<char> pAutoDeleteFileNameBuffer = pFileNameBuffer;
	memset(pFileNameBuffer, '\0', SIZE_BUFFER_MEDIUM);

	sprintf_s(pFileNameBuffer, SIZE_BUFFER_MEDIUM, "%s_DE_FilterValue_%.1f_HitTreshold_%ld_SetThreshold_%ld_KEGG_Pathway_Matrix.tsv", strOutPrefix.c_str(), fDEThreshold, lThresholdHitsMinimum, lThresholdSet);

	std::string strFullPath = strFileOutputPath + pFileNameBuffer;

	lReturn = WriteOutputFile(pFileBuffer, strFullPath);
	if (lReturn != ERR_NOERROR)
		return lReturn;


	return lReturn;
}