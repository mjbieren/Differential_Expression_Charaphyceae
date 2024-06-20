#include "GlobalHelper.h"


long IncreaseKEGGPathways(std::vector<char*>* pvecKeggRow, std::vector<CKEGGSet*>* pvecKEGGSet, bool bPrefix, std::string strPrefix, double dThresholdUpregulated, double dThresholdDownRegulated)
{
	long lReturn = ERR_NOERROR;


	std::string strKeggColumn = pvecKeggRow->at(2);
	std::vector<char*> vecPathwayColumn;

	
	lReturn = SplitColumnInObjects(strKeggColumn, &vecPathwayColumn, ',');
	if (lReturn != ERR_NOERROR)
		return lReturn;


	CKEGGSet* pKEGGSet = nullptr;

	std::string strStringToSearch;

	float fKeggValue = 0.0;

	size_t idxPosition = 0;

	char* pEnd = nullptr;
	for (size_t idx = 0; idx < vecPathwayColumn.size(); idx++)
	{
		strStringToSearch = vecPathwayColumn.at(idx);
		idxPosition = 0;

		if (memcmp(strStringToSearch.c_str(), strPrefix.c_str(), strPrefix.size()) == 0)
		{
			//we found you

			lReturn = FindMatchingKeggSet(pvecKEGGSet, strStringToSearch.c_str() + strPrefix.size(), &pKEGGSet);
			if (lReturn != ERR_NOERROR)
			{
				ClearVector(&vecPathwayColumn);
				return lReturn;
			}

			for (size_t idx2 = 3; idx2 < pvecKeggRow->size(); idx2++)
			{
				fKeggValue = strtof(pvecKeggRow->at(idx2),&pEnd);
				if (fKeggValue > dThresholdUpregulated)
				{
					pKEGGSet->IncreaseCounter(idx2 - 3 +idxPosition);
				}
				else if (fKeggValue < dThresholdDownRegulated)
				{
					pKEGGSet->IncreaseCounter(idx2 - 3 +idxPosition + 1);
				}
				idxPosition++;

			}
		}
		else if (isdigit(strStringToSearch[0]) == true)
		{
			lReturn = FindMatchingKeggSet(pvecKEGGSet, strStringToSearch.c_str(), &pKEGGSet);
			if (lReturn != ERR_NOERROR)
			{
				if (lReturn == KEGGSET_KEGGSET_NOT_FOUND_VECTOR)
				{
					continue;
				}
				ClearVector(&vecPathwayColumn);
				return lReturn;
			}

			for (size_t idx2 = 3; idx2 < pvecKeggRow->size(); idx2++)
			{
				fKeggValue = strtof(pvecKeggRow->at(idx2),&pEnd);
				if (fKeggValue > dThresholdUpregulated)
				{
					pKEGGSet->IncreaseCounter(idx2 - 3 +idxPosition);
				}
				else if (fKeggValue < dThresholdDownRegulated)
				{
					pKEGGSet->IncreaseCounter(idx2 - 3 +idxPosition + 1);
				}
				idxPosition++;

			}
		}

	}

	ClearVector(&vecPathwayColumn);
	return lReturn;
}



long MatchAndCountKEGGHits(CTable* pTableKEGGMatrix, std::vector<CKEGGSet*>* pvecKEGGSet)
{
	long lReturn = ERR_NOERROR;

	/*
	1) This function loops over the KEGG Matrix and checks if the DE values (Log2Folds) passes the threshold set
	2) If it matches the Threshold set go over the KEGG Pathway column. Extract all the objects and increase it in the right column

	
	*/

	size_t sizeColumnsInKeggMatrix = pTableKEGGMatrix->GetRow(0)->size(); //And we know we start

	float fThresholdUpregulated = 0.0;
	float fThresholdDownregulated = 0.0;

	lReturn = glb.propertyBag.GetThresholdDE(&fThresholdUpregulated);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_THRESHOLD_DE_KEGGCOUNTER;

	fThresholdDownregulated = -fThresholdUpregulated;

	//we now have the borders. Time to get the prefix

	bool bPrefix = false;

	lReturn = glb.propertyBag.GetBoolPrefix(&bPrefix);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_BOOL_PREFIXTAG_KEGGCOUNTER;

	std::string strPrefix;
	if (bPrefix == true)
	{
		lReturn = glb.propertyBag.GetPrefix(&strPrefix);
		if (lReturn != ERR_NOERROR)
			return PROPERTYBAG_PREFIXTAG_KEGGCOUNTER;
	}

	size_t sizeKeggMatrix = pTableKEGGMatrix->GetAmountOfTableRows();


	double dDEValue = 0.0;

	//Check the first. because we can't do a negative of a size_t datatype.

	char* pEnd = nullptr;
	for (size_t idx3 = 3; idx3 < sizeColumnsInKeggMatrix; idx3++)
	{
		dDEValue = strtof(pTableKEGGMatrix->GetRow(0)->at(idx3),&pEnd);
		if (dDEValue >= fThresholdUpregulated || dDEValue <= fThresholdDownregulated)
		{
			lReturn = IncreaseKEGGPathways(pTableKEGGMatrix->GetRow(0), pvecKEGGSet, bPrefix, strPrefix, fThresholdUpregulated, fThresholdDownregulated);
			if (lReturn != ERR_NOERROR)
				return lReturn;
			break;
		}
	}

	for (size_t idx = 1; idx < sizeKeggMatrix; idx++)
	{
		printf_s("Working on Kegg Matrix Row %zu/%zu %s", idx + 1, sizeKeggMatrix, EOL);
		for (size_t idx2 = 3; idx2 < sizeColumnsInKeggMatrix; idx2++)
		{
			dDEValue = strtof(pTableKEGGMatrix->GetRow(idx)->at(idx2),&pEnd);
			if (dDEValue >= fThresholdUpregulated || dDEValue <= fThresholdDownregulated)
			{
				lReturn = IncreaseKEGGPathways(pTableKEGGMatrix->GetRow(idx), pvecKEGGSet, bPrefix, strPrefix, fThresholdUpregulated, fThresholdDownregulated);
				if (lReturn != ERR_NOERROR)
					return lReturn;
				break;
			}
		}

	}



	return lReturn;
}