#include "GlobalHelper.h"

long CheckReturnValue(long lReturn, std::vector<CInfernal*>* pvecInfernal, std::vector<CDifferentialMatrixBlock*>* pvecDifferentialMatrixBlocks, std::vector<CDifferentialMatrixBlock*>* pvecInfernalOutputBlocks,std::vector<char*> * pvecSetNames, std::vector<size_t> * pvecColumnPositions)
{
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pvecDifferentialMatrixBlocks);
		ClearVector(pvecInfernalOutputBlocks);
		ClearVector(pvecInfernal);
		ClearVector(pvecSetNames);
		pvecColumnPositions->clear();
	}

	return lReturn;
}