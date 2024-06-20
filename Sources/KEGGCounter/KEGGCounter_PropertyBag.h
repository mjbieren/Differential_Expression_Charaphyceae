#pragma once
#include "stdafx.h"
#include "Management.h"


class CKEGGCounterPropertyBag : CPropertyBag
{
protected:
	char m_szKEGGCounterErrMessage[255];
public:
	CKEGGCounterPropertyBag() {};
	~CKEGGCounterPropertyBag() {};
	const char* GetLastKEGGCounterErrormessage() { return m_szKEGGCounterErrMessage; }

	/*
	KEGG Matrix
	KEGG Description
	Outputfolder
	Bool Prefix
	Prefix
	Threshold DE Value
	Threshold minimum counter
	Threshold How many sets present

	*/




	long SetKEGGMatrixPath(const char* szKEGGMatrixPath)
	{
		return SetValueString("Paths", "KEGGMatrix", szKEGGMatrixPath);
	}
	long GetKEGGMatrixPath(std::string* pstrKEGGMatrixPath)
	{
		return GetValueString("Paths", "KEGGMatrix", pstrKEGGMatrixPath);
	}

	long SetKEGGDescriptionPath(const char* szKEGGDescriptionPath)
	{
		return SetValueString("Paths", "KEGGDescription", szKEGGDescriptionPath);
	}
	long GetKEGGDescriptionPath(std::string* pstrKEGGDescriptionPath)
	{
		return GetValueString("Paths", "KEGGDescription", pstrKEGGDescriptionPath);
	}

	long SetOutputFolder(const char* szOutputPath)
	{
		return SetValueString("Paths", "Output", szOutputPath);
	}

	long GetOutputFolder(std::string* pstrOutputPath)
	{
		return GetValueString("Paths", "Output", pstrOutputPath);
	}

	long SetOutputPrefix(const char* szOutputPrefix)
	{
		return SetValueString("Output", "Prefix", szOutputPrefix);
	}

	long GetOutputPrefix(std::string* pstrOutputPrefix)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueString("Output", "Prefix", pstrOutputPrefix);
		if (lReturn != ERR_NOERROR)
		{
			printf_s("Output Prefix not set, default is used, which means it's empty %s", EOL);
			*pstrOutputPrefix = ""; //We are going to have a default
			return ERR_NOERROR;
		}
		return lReturn;
	}


	long SetBoolPrefix(bool bSetPrefix = true)
	{
		return SetValueBool("Bool", "Prefix", bSetPrefix);
	}

	long GetBoolPrefix(bool* pbPrefix)
	{
		long lReturn = ERR_NOERROR;
		lReturn = GetValueBool("Bool", "Prefix", pbPrefix, false);
		if (lReturn == PROP_ERR_SECTION_NOT_FOUND_DEFAULT_USED || lReturn == PROP_ERR_KEY_NOT_FOUND_DEFAULT_USED)
		{
			printf_s("%s %s", "pbPrefix Bool Not Found: Default used", EOL);
			return ERR_NOERROR;
		}
		return lReturn;
	}

	long SetPrefix(const char* szPrefix)
	{
		return SetValueString("KEGG", "Prefix", szPrefix);
	}

	long GetPrefix(std::string* pstrPrefix)
	{
		return GetValueString("KEGG", "Prefix", pstrPrefix);
	}

	long SetThresholdDE(float fDEThreshold)
	{
		return SetValueFloat("DEMatrix", "Threshold", fDEThreshold);
	}

	long GetThresholdDE(float* fDEThreshold)
	{
		return GetValueFloat("DEMatrix", "Threshold", fDEThreshold, 0.0);
	}

	long SetThresholdMinimumCounter(long lMinimumCounter)
	{
		return SetValueLong("KEGG", "MinimumCounter", lMinimumCounter);
	}

	long GetThresholdMinimumCounter(long* plMinimumCounter)
	{
		return GetValueLong("KEGG", "MinimumCounter", plMinimumCounter, 0);
	}

	long SetThresholdMinimumSets(long lMinimumSets)
	{
		return SetValueLong("KEGG", "MinimumSets", lMinimumSets);
	}

	long GetThresholdMinimumSets(long* plMinimumSets)
	{
		return GetValueLong("KEGG", "MinimumSets", plMinimumSets, 0);
	}

};