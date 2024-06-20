#pragma once
#include "stdafx.h"
#include "Management.h"

class CDEMCPropertyBag : CPropertyBag
{
protected:
	char m_szGetDifferentialExpressionMatricesCombineErrMessage[255];
public:
	CDEMCPropertyBag() {};
	~CDEMCPropertyBag() {};
	const char* GetLastDifferentialExpressionMatricesCombineErrorMessage() { return m_szGetDifferentialExpressionMatricesCombineErrMessage; }

	/*
	Fasta File Trinity Assembly
	Fasta File Peptide Transdecoder
	Trinotate Report
	Differential.Matrix
	Infernal
	ColumnsToParse
	OutputFolder
	prefix
	*/

	long SetFastaTrinityPath(const char* szFastaFilePath)
	{
		return SetValueString("Paths", "FastaTrinity", szFastaFilePath);
	}

	long GetFastaTrinityPath(std::string* pstrFastaFilePath)
	{
		return GetValueString("Paths", "FastaTrinity", pstrFastaFilePath);
	}

	long SetFastaProteinPath(const char* szFastaFilePath)
	{
		return SetValueString("Paths", "FastaProtein", szFastaFilePath);
	}

	long GetFastaProteinPath(std::string* pstrFastaFilePath)
	{
		return GetValueString("Paths", "FastaProtein", pstrFastaFilePath);
	}

	long SetTrinotatePath(const char* szTrinotateFilePath)
	{
		return SetValueString("Paths", "Trinotate", szTrinotateFilePath);
	}

	long GetTrinotatePath(std::string* pstrTrinotateFilePath)
	{
		return GetValueString("Paths", "Trinotate", pstrTrinotateFilePath);
	}

	long SetDEMatrixPath(const char* szDEMatrixFilePath)
	{
		return SetValueString("Paths", "DEMatrix", szDEMatrixFilePath);
	}

	long GetDEMatrixPath(std::string* pstrDEMatrixFilePath)
	{
		return GetValueString("Paths", "DEMatrix", pstrDEMatrixFilePath);
	}

	long SetInfernalPath(const char* szInfernalFilePath)
	{
		return SetValueString("Paths", "Infernal", szInfernalFilePath);
	}

	long GetInfernalPath(std::string* pstrInfernalFilePath)
	{
		return GetValueString("Paths", "Infernal", pstrInfernalFilePath);
	}

	long SetTrinotateColumns(const char* szTrinotateColumns)
	{
		return SetValueString("Table", "Trinotate", szTrinotateColumns);
	}

	long GetTrinotateColumns(std::string* pstrTrinotateColumns)
	{
		return GetValueString("Table", "Trinotate", pstrTrinotateColumns);
	}

	long SetBoolDEFilterColumns(bool bSetFilterColumns = true)
	{
		return SetValueBool("Bool", "FilterColumns", bSetFilterColumns);
	}

	long GetBoolDeFilterColumns(bool* pbGetFilterColumns)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "FilterColumns", pbGetFilterColumns, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s", "pbGetFilterColumns Bool Not Found: Default used", EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

	long SetBoolFilterOnFastaFile(bool bSetFilterOnFastaFile = true)
	{
		return SetValueBool("Bool", "FilterOnFastaFile", bSetFilterOnFastaFile);
	}

	long GetBoolFilterOnFastaFile(bool* pbGetBoolFilterOnFastaFile)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "FilterOnFastaFile", pbGetBoolFilterOnFastaFile, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s", "pbGetBoolFilterOnFastaFile Bool Not Found: Default used", EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}



	long SetPrefixValue(const char* szPrefixValue)
	{
		return SetValueString("Output", "Prefix", szPrefixValue);
	}

	long GetPrefixValue(std::string* pstrPrefixValue)
	{
		return GetValueString("Output", "Prefix", pstrPrefixValue);
	}


	long SetOutputDir(const char* szOutputDir)
	{
		std::string strOutputDir = szOutputDir;
		AppendSlash(&strOutputDir); //This is to make sure the path ends with a /
		return SetValueString("Paths", "Output", strOutputDir.c_str());
	}

	long GetOutputDir(std::string* pstrOutputDir)
	{
		return GetValueString("Paths", "Output", pstrOutputDir);
	}

};
