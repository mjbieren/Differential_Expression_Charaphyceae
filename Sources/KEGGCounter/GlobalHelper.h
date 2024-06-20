#pragma once
#include "stdafx.h"
#include "Table.h"
#include "KEGGSet.h"
#include "Management.h"
#include "ProcessFile.h"
#include "KEGGCounter_PropertyBag.h"


class CGlobal
{
public:
	CGlobal() {};
	~CGlobal() {};

	CKEGGCounterPropertyBag propertyBag;
	CManagement management;

};

extern CGlobal glb;


#define CHECK_RETURNVALUE(value)        \
if(value!=ERR_NOERROR)                  \
{                                       \
   glb.management.ErrorChecker(value);  \
   return (int) value;                        \
}                              

#define CHECK_RETURNVALUE_REL_PTR(value, ptr)        \
if(value!=ERR_NOERROR)                  \
{                                       \
    delete ptr;                         \
     glb.management.ErrorChecker(value); \
   return (int) value;                  \
}

long ParseCommandLine(int argc, char* argv[], char* envp[]);
long CheckReturnValue(long lReturn, std::vector<CKEGGSet*>* pvecKEGGSet);
long ParseInputFiles(CTable* pTableKEGGMatrix, CTable* pTableKEGGDescription, std::vector<CKEGGSet*>* pvecKEGGSet);
long MatchAndCountKEGGHits(CTable* pTableKEGGMatrix, std::vector<CKEGGSet*>* pvecKEGGSet);
long WriteOutputFile(CTable* pKEGGMatrix, std::vector<CKEGGSet*>* pvecKEGGSet);
