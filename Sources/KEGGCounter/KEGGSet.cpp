#include "KEGGSet.h"

CKEGGSet::CKEGGSet() {}

CKEGGSet::CKEGGSet(size_t sizeCounterSets)
{
	for (size_t idx = 0; idx < sizeCounterSets *2; idx++)
	{
		m_vecCounters.push_back(0);
	}

	m_sizeKeggCounterVector = sizeCounterSets*2;
}
CKEGGSet::~CKEGGSet()
{
	if (m_pKEGGID)
		delete m_pKEGGID;

	if (m_pvecKeggRowTable && m_bDeleteKeggRowTable == true)
	{
		ClearVector<char>(m_pvecKeggRowTable);

	}

	m_vecCounters.clear();
}

size_t CKEGGSet::GetVectorsize() { return m_vecCounters.size(); }

void CKEGGSet::InitVectorCounters(size_t sizeCounters)
{
	//Just to be sure
	m_vecCounters.clear();
	for (size_t idx = 0; idx < sizeCounters*2; idx++)
	{
		m_vecCounters.push_back(0);
	}

	m_sizeKeggCounterVector = m_vecCounters.size();
}

long CKEGGSet::SetKEGGID(const char* pKEGGID)
{
	if (!pKEGGID)
		return 1; //ToDO Error KEGGSET_KEGGID_DOES_NOT_EXIST

	size_t sizeKEGGID = strlen(pKEGGID);

	if (sizeKEGGID == 0)
		return 1; //ToDO Error KEGGSET_KEGGID_NOT_FILLED


	if (m_pKEGGID)
		delete m_pKEGGID;

	m_pKEGGID = new char[sizeKEGGID + 10];
	memset(m_pKEGGID, '\0', sizeKEGGID + 10);
	memcpy(m_pKEGGID, pKEGGID, sizeKEGGID);

	return ERR_NOERROR;

}
long CKEGGSet::GetKEGGID(char** ppKEGGID)
{
	if (!m_pKEGGID)
		return 1; //ToDo KEGGSET_KEGGID_GET_FAIL

	*ppKEGGID = m_pKEGGID;

	return ERR_NOERROR;
}
char* CKEGGSet::GetKEGGID() { return m_pKEGGID; }

void CKEGGSet::SetBoolKeggRowTable(bool bSetDelete) { m_bDeleteKeggRowTable = bSetDelete; }
bool CKEGGSet::GetBoolKeggRowtable() { return m_bDeleteKeggRowTable; }
void CKEGGSet::SetBoolObjectIsFilled(bool bSetInfo) { m_bHasInfo = bSetInfo; }
bool CKEGGSet::GetBoolObjectIsFilled() { return m_bHasInfo; }

long CKEGGSet::IncreaseCounter(size_t idxIncrease)
{
	long lReturn = ERR_NOERROR;

	if (idxIncrease >= m_sizeKeggCounterVector)
		return KEGGSET_COUNTERINCREASE_NOT_VALID; //ToDO Error KEGGSET_COUNTERINCREASE_NOT_VALID

	m_vecCounters.at(idxIncrease) = m_vecCounters.at(idxIncrease) + 1;

	m_bHasInfo = true; //Yes it looks a bit stupid that it will be set every time, but this way you know 100% sure it will be set and otherwise the user needs to have previous knowledge and that's counter productive. (How would you know?)

	return lReturn;
}

long CKEGGSet::CheckSetThreshold(bool* bpSetThreshold, size_t sizeSetThreshold)
{
	long lReturn = ERR_NOERROR;

	//Check if it's divisible by two and if not error
	if (m_sizeKeggCounterVector % 2 != 0)
		return KEGGSET_KEGGSETTHRESHOLD_NOT_VALID; //ToDO KEGGSET_KEGGSETTHRESHOLD_NOT_VALID

	//Check if Threshold makes sense if not automatically set the threshold to being all present.
	size_t sizeCheckThreshold = sizeSetThreshold;

	if (sizeSetThreshold > (m_sizeKeggCounterVector / 2))
		sizeCheckThreshold = m_sizeKeggCounterVector / 2;



	size_t sizeSum = 0;
	unsigned int iPos = 0;
	for (size_t idx = 0; idx < m_sizeKeggCounterVector; idx++)
	{
		//even number = new set
		if (idx % 2 == 0)
		{
			iPos = 0;

			if (m_vecCounters.at(idx) > 0)
				iPos++;

			continue; //We don't want to continue the rest, ODD number has to follow
		}
		else //It's an odd number
		{
			if (m_vecCounters.at(idx) > 0)
				iPos++;
		}

		if (iPos > 0) //If the set has an increase
			sizeSum++;
	}

	//If sizeSum is lower than sizeCheckThreshold return false otherwise return true;
	if (sizeSum < sizeCheckThreshold)
		*bpSetThreshold = false;
	else
		*bpSetThreshold = true;

	return lReturn;
}


long CKEGGSet::CheckSumThreshold(bool* bpSumThreshold, size_t sizeSumThreshold)
{
	long lReturn = ERR_NOERROR;

	//Just loop over till we determine all values are at least equal or above the threshold value.

	bool bThreshold = true;

	for (size_t idx = 0; idx < m_sizeKeggCounterVector; idx++)
	{
		if (m_vecCounters.at(idx) < sizeSumThreshold)
		{
			bThreshold = false;
			break;
		}
	}

	*bpSumThreshold = bThreshold;

	return lReturn;

}

unsigned long CKEGGSet::GetVectorItem(size_t idx)
{
	return m_vecCounters.at(idx);
}

char* CKEGGSet::GetKEGGRowDescription() { return m_pvecKeggRowTable->at(1); }

long CKEGGSet::CheckCombinedThreshold(bool* bpCombinedThreshold, size_t sizeSetThreshold, size_t sizeSumThreshold)
{
	long lReturn = ERR_NOERROR;
	
	//Check if it's divisible by two and if not error
	if (m_sizeKeggCounterVector % 2 != 0)
		return KEGGSET_KEGGSETTHRESHOLD_NOT_VALID; //ToDO KEGGSET_KEGGSETTHRESHOLD_NOT_VALID

	//Check if Threshold makes sense if not automatically set the threshold to being all present.
	size_t sizeCheckThreshold = sizeSetThreshold;
	sizeCheckThreshold = sizeCheckThreshold;

	if (sizeSetThreshold > (m_sizeKeggCounterVector / 2))
		sizeCheckThreshold = m_sizeKeggCounterVector / 2;

	std::vector<unsigned long> vecCombinedSets;

	for (size_t idx = 0; idx < (m_sizeKeggCounterVector/2); idx++)
	{
		vecCombinedSets.push_back(0);
	}


	for (size_t idx = 0; idx < m_sizeKeggCounterVector; idx++)
	{
		if (idx % 2 == 0)
		{
			vecCombinedSets.at(idx/2) = vecCombinedSets.at(idx/2) + m_vecCounters.at(idx);
		}
		else
		{
			vecCombinedSets.at(idx/2) = vecCombinedSets.at(idx/2) + m_vecCounters.at(idx);
		}
	}

	size_t sizeActivateSetChecker = 0;

	for (size_t idx = 0; idx < vecCombinedSets.size(); idx++)
	{
		if (vecCombinedSets.at(idx) >= sizeSumThreshold)
			sizeActivateSetChecker++;
	}

	if (sizeActivateSetChecker >= sizeSetThreshold)
		*bpCombinedThreshold = true;
	else
		*bpCombinedThreshold = false;

	return lReturn;


}

long CKEGGSet::SetKeggRow(std::vector<char*>* pvecKeggRowTable, bool bSetRowDelete)
{
	long lReturn = ERR_NOERROR;

	if (!pvecKeggRowTable)
		return 1; //ToDo KEGGSET_SETKEGGROW_KEGGROW_NOT_VALID

	m_pvecKeggRowTable = pvecKeggRowTable;
	m_bDeleteKeggRowTable = bSetRowDelete;

	lReturn = SetKEGGID(pvecKeggRowTable->at(0));
	if (lReturn != ERR_NOERROR)
		return lReturn;

	return lReturn;
}



long SortKeggVectorAlphabeticallyKEGGID(std::vector<CKEGGSet*>* pvecKeggSet)
{
	long lReturn = ERR_NOERROR;
	std::sort(pvecKeggSet->begin(), pvecKeggSet->end(), [](CKEGGSet* a, CKEGGSet* b)
		{
			int iRes = strcasecmp(a->GetKEGGID(), b->GetKEGGID());
			return iRes < 0;
		});

	return lReturn;
}

long FindMatchingKeggSet(std::vector<CKEGGSet*>* pvecKeggSet, const char* szToMatch, CKEGGSet** ppKEGGSet)
{
	long lReturn = ERR_NOERROR;

	size_t sizeToMatch = strlen(szToMatch);

	std::vector<CKEGGSet*>::iterator iterLowPos;
	std::vector<CKEGGSet*>::iterator iterHighPos;
	std::vector<CKEGGSet*>::iterator iterBegin = pvecKeggSet->begin();
	std::vector<CKEGGSet*>::iterator iterEnd = pvecKeggSet->end()-1;

#ifdef _DEBUG
	CKEGGSet* pBeginKEGGSetBegin = *iterBegin;
	pBeginKEGGSetBegin = pBeginKEGGSetBegin;
	CKEGGSet* pBeginKEGGSetEnd =  *iterEnd;
	pBeginKEGGSetEnd = pBeginKEGGSetEnd;
#endif

	bool bFoundKeggSet = false;
	std::string strKeggSetToFind;

	CKEGGSet KEGGSetToSearch;
	KEGGSetToSearch.SetKEGGID(szToMatch);

	iterLowPos = std::lower_bound(iterBegin, iterEnd, &KEGGSetToSearch, [](CKEGGSet* a, CKEGGSet* b)
		{
			int iRes = strcasecmp(a->GetKEGGID(), b->GetKEGGID());
			return iRes < 0;
		});
	iterHighPos = std::lower_bound(iterBegin, iterEnd, &KEGGSetToSearch, [](CKEGGSet* a, CKEGGSet* b)
		{
			int iRes = strcasecmp(a->GetKEGGID(), b->GetKEGGID());
			return iRes < 0;
		});

	CKEGGSet* pKeggSetToTest = nullptr;

	if (*iterLowPos)
	{
		if (iterLowPos != iterHighPos)
		{
			while (iterLowPos <= iterHighPos)
			{
				pKeggSetToTest = *iterLowPos;

				if (memcmp(szToMatch, pKeggSetToTest->GetKEGGID(), sizeToMatch) == 0)
				{
					*ppKEGGSet = pKeggSetToTest;
					bFoundKeggSet = true;
					break;
				}

			}
		}
		else
		{
				pKeggSetToTest = *iterLowPos;

				if (memcmp(szToMatch, pKeggSetToTest->GetKEGGID(), sizeToMatch) == 0)
				{
					*ppKEGGSet = pKeggSetToTest;
					bFoundKeggSet = true;
				}
		}
	}

	if (bFoundKeggSet == false)
	{
		printf_s("Could not find %s in the KEGG Description File, Is it there?%s", szToMatch, EOL);
		return KEGGSET_KEGGSET_NOT_FOUND_VECTOR;
	}

	return lReturn;

}