#pragma once
#include "stdafx.h"
#include "Management.h"
#include "ClearVector.h"


class CKEGGSet
{
private:
	char* m_pKEGGID = nullptr; //The ID of the KEGG
	std::vector<char*>* m_pvecKeggRowTable = nullptr; //The linked Row Table from the KEGG Table
	std::vector<unsigned long> m_vecCounters; //Vector that keeps track of the amount of values
	size_t m_sizeKeggCounterVector = 0; //How big the Vector is (should always be able to divide by 1)
	bool m_bDeleteKeggRowTable = false; //Depends on how the user deletes it or not. Most of the time the Kegg Row is only a pointer (meaning this object and another object are looking at the same piece of memory)
	bool m_bHasInfo = false; //In case the KEGG set was increased it will be true

public:
	CKEGGSet();
	CKEGGSet(size_t sizeCounterSets);
	~CKEGGSet();

	size_t GetVectorsize();

	void InitVectorCounters(size_t sizeCounters);


	long SetKEGGID(const char* pKEGGID);
	long GetKEGGID(char** ppKEGGID);
	char* GetKEGGID();

	void SetBoolKeggRowTable(bool bSetDelete = true);
	bool GetBoolKeggRowtable();
	void SetBoolObjectIsFilled(bool bSetInfo = true);
	bool GetBoolObjectIsFilled();

	long IncreaseCounter(size_t idxIncrease);

	long CheckSetThreshold(bool* bpSetThreshold, size_t sizeSetThreshold);


	long CheckSumThreshold(bool* bpSumThreshold, size_t sizeSumThreshold);

	unsigned long GetVectorItem(size_t idx);

	char* GetKEGGRowDescription();


	long SetKeggRow(std::vector<char*>* pvecKeggRowTable, bool bSetRowDelete = false);

	long CheckCombinedThreshold(bool* bpCombinedThreshold, size_t sizeSetThreshold, size_t sizeSumThreshold);

};


long SortKeggVectorAlphabeticallyKEGGID(std::vector<CKEGGSet*>* pvecKeggSet);

long FindMatchingKeggSet(std::vector<CKEGGSet*>* pvecKeggSet, const char* szToMatch, CKEGGSet** ppKEGGSet);