#include "GlobalHelper.h"

long CheckReturnValue(long lReturn, std::vector<CKEGGSet*>* pvecKEGGSet)
{
	if (lReturn != ERR_NOERROR)
	{
		ClearVector(pvecKEGGSet);
	}
	return lReturn;
}