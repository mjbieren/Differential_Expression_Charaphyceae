#include "DifferentialExpression.h"

//CInfernal
long CInfernal::SetInfernalIsoformID(char* pInfernalIsoformID, bool bSetNew) //default is true
{
	long lReturn = ERR_NOERROR;

	if (bSetNew == false) //If the item was already based on a "new char"
	{
		if (!pInfernalIsoformID)
			return INFERNAL_SET_ISOFORMID_SZ;

		if (m_szIsoformID)
			delete m_szIsoformID;

		m_szIsoformID = pInfernalIsoformID;
	}
	else //When it's based on a reusable file buffer
	{
		size_t sizeIsoformID = strlen(pInfernalIsoformID);
		if (sizeIsoformID == 0)
			return INFERNAL_SET_ISOFORMID_SIZE;

		if (m_szIsoformID)
			delete m_szIsoformID;
		m_szIsoformID = new char[sizeIsoformID + 10];
		memset(m_szIsoformID, '\0', sizeIsoformID + 10);
		memcpy(m_szIsoformID, pInfernalIsoformID, sizeIsoformID);
	}

	return lReturn;
}

long CInfernal::SetInfernalIsoformID(char* pStart, char* pEnd)
{
	long lReturn = ERR_NOERROR;

	long lSizeDifference = pEnd - pStart;
	if (lSizeDifference <= 0 || lSizeDifference > SIZE_BUFFER_ONE_GIG)
		return INFERNAL_SETISOFORMID_POINTERDIFFERENCE;

	if (m_szIsoformID)
		delete m_szIsoformID;

	m_szIsoformID = new char[lSizeDifference + 10];
	memset(m_szIsoformID, '\0', lSizeDifference + 10); //Zero Terminating everything.
	memcpy(m_szIsoformID, pStart, lSizeDifference);
	
	return lReturn;
}

long CInfernal::SetInfernalAccession(char* pInfernalAccession, bool bSetNew)
{
	long lReturn = ERR_NOERROR;

	if (bSetNew == false) //If the item was already based on a "new char"
	{
		if (!pInfernalAccession)
			return INFERNAL_SET_ACCESSION_SZ;

		if (m_szInfernalAccession)
			delete m_szInfernalAccession;

		m_szInfernalAccession = pInfernalAccession;
	}
	else //When it's based on a reusable file buffer
	{
		size_t sizeAccession = strlen(pInfernalAccession);
		if (sizeAccession == 0)
			return INFERNAL_SET_ACCESSION_SIZE;

		if (m_szInfernalAccession)
			delete m_szInfernalAccession;
		m_szInfernalAccession = new char[sizeAccession + 10];
		memset(m_szInfernalAccession, '\0', sizeAccession + 10);
		memcpy(m_szInfernalAccession, pInfernalAccession, sizeAccession);
	}

	return lReturn;
}

long CInfernal::SetInfernalAccession(char* pStart, char* pEnd)
{
	long lReturn = ERR_NOERROR;

	long lSizeDifference = pEnd - pStart;
	if (lSizeDifference <= 0 || lSizeDifference > SIZE_BUFFER_ONE_GIG)
		return INFERNAL_SETACCESSION_POINTERDIFFERENCE;

	if (m_szInfernalAccession)
		delete m_szInfernalAccession;

	m_szInfernalAccession = new char[lSizeDifference + 10];
	memset(m_szInfernalAccession, '\0', lSizeDifference + 10); //Zero Terminating everything.
	memcpy(m_szInfernalAccession, pStart, lSizeDifference);

	return lReturn;
}

long CInfernal::SetInfernalDescription(char* pInfernalDescription, bool bSetNew)
{
	long lReturn = ERR_NOERROR;

	if (bSetNew == false) //If the item was already based on a "new char"
	{
		if (!pInfernalDescription)
			return INFERNAL_SET_DESCRIPTION_SZ;

		if (m_szInfernalDescription)
			delete m_szInfernalDescription;

		m_szInfernalDescription = pInfernalDescription;
	}
	else //When it's based on a reusable file buffer
	{
		size_t sizeAccession = strlen(pInfernalDescription);
		if (sizeAccession == 0)
			return INFERNAL_SET_DESCRIPTION_SIZE;

		if (m_szInfernalDescription)
			delete m_szInfernalDescription;
		m_szInfernalDescription = new char[sizeAccession + 10];
		memset(m_szInfernalDescription, '\0', sizeAccession + 10);
		memcpy(m_szInfernalDescription, pInfernalDescription, sizeAccession);
	}

	return lReturn;
}

long CInfernal::SetInfernalDescription(char* pStart, char* pEnd)
{
	long lReturn = ERR_NOERROR;

	long lSizeDifference = pEnd - pStart;
	if (lSizeDifference <= 0 || lSizeDifference > SIZE_BUFFER_ONE_GIG)
		return INFERNAL_SETDESCRIPTION_POINTERDIFFERENCE;

	if (m_szInfernalDescription)
		delete m_szInfernalDescription;

	m_szInfernalDescription = new char[lSizeDifference + 10];
	memset(m_szInfernalDescription, '\0', lSizeDifference + 10); //Zero Terminating everything.
	memcpy(m_szInfernalDescription, pStart, lSizeDifference);

	return lReturn;
}

long CInfernal::GetInfernalIsoformID(char** ppInfernalIsoformID)
{
	long lReturn = ERR_NOERROR;

	if (!m_szIsoformID)
		return INFERNAL_GETISOFORMID;

	*ppInfernalIsoformID = m_szIsoformID;

	return lReturn;
}

char* CInfernal::GetInfernalIsoformID()
{
	return m_szIsoformID;
}


long CInfernal::GetInfernalAccession(char** ppInfernalAccession)
{
	long lReturn = ERR_NOERROR;

	if (!m_szInfernalAccession)
		return INFERNAL_GETACCESSION;

	*ppInfernalAccession = m_szInfernalAccession;

	return lReturn;
}

char* CInfernal::GetInfernalAccession()
{
	return m_szInfernalAccession;
}

long CInfernal::GetInfernalDescription(char** ppInfernalDescription)
{
	long lReturn = ERR_NOERROR;

	if (!m_szInfernalDescription)
		return INFERNAL_GETDESCRIPTION;

	*ppInfernalDescription = m_szInfernalDescription;

	return lReturn;
}

char* CInfernal::GetInfernalDescription()
{
	return m_szInfernalDescription;
}

//CDifferentialMatrixBlock
long CDifferentialMatrixBlock::SetDEMatrixRow(std::vector<char*>* pvecDEMatrixRow) //This one is never filled from a file but linked from other objects!
{
	long lReturn = ERR_NOERROR;
	//Just check if it's empty or not

	if (!pvecDEMatrixRow)
		return DIFFERENTIALMATRIX_SET_ROW_DEMATRIX_EMPTY;

	m_pvecDEMatrixRow = pvecDEMatrixRow;

	return lReturn;
}

long CDifferentialMatrixBlock::SetTrinotateRow(std::vector<char*>* pvecTrinotate)//This one is never filled from a file but linked from other objects!
{
	long lReturn = ERR_NOERROR;

	if (!pvecTrinotate)
		return DIFFERENTIALMATRIX_SET_ROW_TRINOTATE_EMPTY;

	m_pvecTrinotate = pvecTrinotate;

	return lReturn;
}

long CDifferentialMatrixBlock::SetFastaTrinityBlock(CFastaBlock* pFastaTrinityBlock)//This one is never filled from a file but linked from other objects!
{
	long lReturn = ERR_NOERROR;
	if (!pFastaTrinityBlock)
		return DIFFERENTIALMATRIX_SET_TRINITY_EMPTY;

	m_pFastaTrinityBlock = pFastaTrinityBlock;

	return lReturn;
}

long CDifferentialMatrixBlock::SetFastaTrinityProtein(CFastaBlock* pFastaProteinBlock)//This one is never filled from a file but linked from other objects!
{
	long lReturn = ERR_NOERROR;

	if (!pFastaProteinBlock)
		return DIFFERENTIALMATRIX_SET_PROTEIN_EMPTY;

	m_pFastaProteinBlock = pFastaProteinBlock;

	SetBoolProteinBlock();

	return lReturn;
}

long CDifferentialMatrixBlock::SetInfernal(CInfernal* pInfernal)//This one is never filled from a file but linked from other objects!
{
	long lReturn = ERR_NOERROR;
	if (!pInfernal)
		return DIFFERENTIALMATRIX_SET_INFERNAL_EMPTY;

	m_pInfernal = pInfernal;

	SetBoolInfernal();//If we sset it then we also set the boolean (to avoid crashes).

	return lReturn;
}

void CDifferentialMatrixBlock::SetBoolInfernal(bool bInfernal) //Has a default so it's always set.
{
	m_bInfernal = bInfernal;
}

void CDifferentialMatrixBlock::SetBoolProteinBlock(bool bProteinBlock)
{
	m_bProteinBlock = bProteinBlock;
}

long CDifferentialMatrixBlock::GetDEMatrixRow(std::vector<char*>** ppvecDEMatrixRow)
{
	long lReturn = ERR_NOERROR;

	if (!m_pvecDEMatrixRow)
		return DIFFERENTIALMATRIX_GET_ROW_DEMATRIX_EMPTY;

	*ppvecDEMatrixRow = m_pvecDEMatrixRow;

	return lReturn;
}

std::vector<char*>* CDifferentialMatrixBlock::GetDEMatrixRow()
{
	return m_pvecDEMatrixRow;
}

long CDifferentialMatrixBlock::GetTrinotateRow(std::vector<char*>** ppvecTrinotate)
{
	long lReturn = ERR_NOERROR;

	if (!m_pvecTrinotate)
		return DIFFERENTIALMATRIX_GET_ROW_TRINOTATE_EMPTY;

	*ppvecTrinotate = m_pvecTrinotate;

	return lReturn;
}

std::vector<char*>* CDifferentialMatrixBlock::GetTrinotateRow()
{
	return m_pvecTrinotate;
}

long CDifferentialMatrixBlock::GetFastaTrinityBlock(CFastaBlock** ppFastaTrinityBlock)
{
	long lReturn = ERR_NOERROR;

	if (!m_pFastaTrinityBlock)
		return DIFFERENTIALMATRIX_GET_TRINITY_EMPTY;


	*ppFastaTrinityBlock = m_pFastaTrinityBlock;

	return lReturn;
}

CFastaBlock* CDifferentialMatrixBlock::GetFastaTrinityBlock()
{
	return m_pFastaTrinityBlock;
}

long CDifferentialMatrixBlock::GetFastaProteinBlock(CFastaBlock** ppFastaProteinBlock)
{
	long lReturn = ERR_NOERROR;

	if (!m_pFastaProteinBlock)
		return DIFFERENTIALMATRIX_GET_PROTEIN_EMPTY;

	*ppFastaProteinBlock = m_pFastaProteinBlock;

	return lReturn;
}

CFastaBlock* CDifferentialMatrixBlock::GetFastaProteinBlock()
{
	return m_pFastaProteinBlock;
}

long CDifferentialMatrixBlock::GetInfernal(CInfernal** ppInfernal)
{
	long lReturn = ERR_NOERROR;

	if (!m_pInfernal)
		return DIFFERENTIALMATRIX_GET_INFERNAL_EMPTY;

	*ppInfernal = m_pInfernal;

	return lReturn;
}

CInfernal* CDifferentialMatrixBlock::GetInfernal()
{
	return m_pInfernal;
}

bool CDifferentialMatrixBlock::GetInfernalBool() { return m_bInfernal; }
bool CDifferentialMatrixBlock::GetBoolProtein() { return m_bProteinBlock; }


//Sort Infernal Vector
long SortInfernalVectorAlphabetically(std::vector<CInfernal*> *pvecInfernal)
{
	long lReturn = ERR_NOERROR;

	std::sort(pvecInfernal->begin(), pvecInfernal->end(), [](CInfernal* a, CInfernal* b)
		{
			int iRes = strcasecmp(a->GetInfernalIsoformID(), b->GetInfernalIsoformID());
			return iRes < 0;
		});



	return lReturn;
}

long FindMatchingInfernal(std::vector<CInfernal*>* pvecInfernal, char* szToMatch, CInfernal** ppInfernalMatched)
{
	long lReturn = ERR_NOERROR;

	size_t sizeToMatch = strlen(szToMatch);

	std::vector<CInfernal*>::iterator iterLowPos;
	std::vector<CInfernal*>::iterator iterHighPos;
	std::vector<CInfernal*>::iterator iterBegin = pvecInfernal->begin();
	std::vector<CInfernal*>::iterator iterEnd = pvecInfernal->end() - 1;

#ifdef _DEBUG //WE have this to determine if the iterator worked or not
	CInfernal* pBeginInfernalBegin = *iterBegin;
	pBeginInfernalBegin = pBeginInfernalBegin;
	CInfernal* pBeginFastaFileEnd = *iterEnd;
	pBeginFastaFileEnd = pBeginFastaFileEnd;
#endif

	bool bFoundInfernal = false;
	std::string strInfernalNameToFind;

	CInfernal Infernal;

	Infernal.SetInfernalIsoformID(szToMatch);
	iterLowPos = std::lower_bound(iterBegin, iterEnd, &Infernal, [](CInfernal* a, CInfernal* b)
		{
			int iRes = strcasecmp(a->GetInfernalIsoformID(), b->GetInfernalIsoformID()); // Sort numbers as string (just in case).	
			return iRes < 0;
		});
	iterHighPos = std::upper_bound(iterBegin, iterEnd, &Infernal, [](CInfernal* a, CInfernal* b)
		{
			int iRes = strcasecmp(a->GetInfernalIsoformID(), b->GetInfernalIsoformID());// Sort numbers as string (just in case).
			return iRes < 0;
		});

	CInfernal* pInfernalToTest = nullptr;
	if (*iterLowPos)
	{
		sizeToMatch = strlen(szToMatch);
		if (iterLowPos != iterHighPos)
		{
			while (iterLowPos <= iterHighPos)
			{
				pInfernalToTest = *iterLowPos;

				if (memcmp(szToMatch, pInfernalToTest->GetInfernalIsoformID(), sizeToMatch) == 0)
				{
					*ppInfernalMatched = pInfernalToTest;
					bFoundInfernal = true;
					break;
				}
				iterLowPos++;
			}
		}
		else
		{
			pInfernalToTest = *iterLowPos; //Fasta File import goes wrong, iterEnd is empty!!
						
			if (memcmp(szToMatch, pInfernalToTest->GetInfernalIsoformID(), sizeToMatch) == 0)
			{
				*ppInfernalMatched = pInfernalToTest;
				bFoundInfernal = true;			
			}
			
		}
	}

	if (bFoundInfernal == false)
		return DEMC_MATCHING_INFERNAL_NOT_FOUND;

	return lReturn;
}