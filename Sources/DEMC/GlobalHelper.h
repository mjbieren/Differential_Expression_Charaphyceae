#pragma once
#include "stdafx.h"
#include "Table.h"
#include "Fasta.h"
#include "DifferentialExpression.h"
#include "Management.h"
#include "ProcessFile.h"
#include "DEMC_PropertyBag.h"

class CGlobal
{
public:
	CGlobal() {};
	~CGlobal() {};

	CDEMCPropertyBag propertyBag;
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

long SetFileBuffer(char** ppPos, std::string strFileName);