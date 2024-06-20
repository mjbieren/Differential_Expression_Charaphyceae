#pragma once
#include "ClearVector.h"
#include "Management.h"
#include "Fasta.h"
#include "GlobalHelper.h"


class CInfernal
{
private:
	char* m_szIsoformID = nullptr;
	char* m_szInfernalAccession = nullptr;
	char* m_szInfernalDescription = nullptr;
public:
	CInfernal() {};
	~CInfernal() 
	{
		if (m_szIsoformID)
			delete m_szIsoformID;
		if (m_szInfernalAccession)
			delete m_szInfernalAccession;
		if (m_szInfernalDescription)
			delete m_szInfernalDescription;

	};

	long SetInfernalIsoformID(char* pInfernalIsoformID,bool bSetNew = true);
	long SetInfernalIsoformID(char* pStart, char* pEnd);
	long SetInfernalAccession(char* pInfernalAccession, bool bSetNew = true);
	long SetInfernalAccession(char* pStart, char* pEnd);
	long SetInfernalDescription(char* pInfernalDescription, bool bSetNew = true);
	long SetInfernalDescription(char* pStart, char* pEnd);

	long GetInfernalIsoformID(char** ppInfernalIsoformID);
	char* GetInfernalIsoformID();

	long GetInfernalAccession(char** ppInfernalAccession);
	char* GetInfernalAccession();
	long GetInfernalDescription(char** ppInfernalDescription);
	char* GetInfernalDescription();

};

class CFastaBlock;

class CDifferentialMatrixBlock
{
private:
	std::vector<char*>* m_pvecDEMatrixRow = nullptr;
	std::vector<char*>* m_pvecTrinotate = nullptr;
	CFastaBlock* m_pFastaTrinityBlock = nullptr;
	CFastaBlock* m_pFastaProteinBlock = nullptr;
	CInfernal* m_pInfernal = nullptr;
	bool m_bInfernal = false;
	bool m_bProteinBlock = false;
public:
	CDifferentialMatrixBlock() {};
	~CDifferentialMatrixBlock() {}; //We do not have to delete something since they exist in other places

	long SetDEMatrixRow(std::vector<char*>* pvecDEMatrixRow);
	long SetTrinotateRow(std::vector<char*>* pvecTrinotate);
	long SetFastaTrinityBlock(CFastaBlock* pFastaTrinityBlock);
	long SetFastaTrinityProtein(CFastaBlock* pFastaProteinBlock);
	long SetInfernal(CInfernal* pInfernal);
	void SetBoolInfernal(bool bInfernal = true);
	void SetBoolProteinBlock(bool bProtein = true);

	long GetDEMatrixRow(std::vector<char*>** ppvecDEMatrixRow);
	std::vector<char*>* GetDEMatrixRow();
	long GetTrinotateRow(std::vector<char*>** ppvecTrinotate);
	std::vector<char*>* GetTrinotateRow();
	long GetFastaTrinityBlock(CFastaBlock** ppFastaTrinityBlock);
	CFastaBlock* GetFastaTrinityBlock();
	long GetFastaProteinBlock(CFastaBlock** ppFastaProteinBlock);
	CFastaBlock* GetFastaProteinBlock();
	long GetInfernal(CInfernal** ppInfernal);
	CInfernal* GetInfernal();
	bool GetInfernalBool();
	bool GetBoolProtein();
	

};

long SortInfernalVectorAlphabetically(std::vector<CInfernal*>* pvecInfernal);
long FindMatchingInfernal(std::vector<CInfernal*>* pvecInfernal, char* szToMatch, CInfernal** ppInfernalMatched);