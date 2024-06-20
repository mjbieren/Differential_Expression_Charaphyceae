
#include "GlobalHelper.h"

long ParseKEGGSetObjects(CTable* pTableKEGGDescription, std::vector<CKEGGSet*>* pvecKeggSets, size_t sizeDEMatrix)
{
	long lReturn = ERR_NOERROR;
	
	CKEGGSet * pKeggSet = nullptr;
	size_t sizeKEGGDescriptionRows = pTableKEGGDescription->GetAmountOfTableRows();

	for (size_t idx = 0; idx < sizeKEGGDescriptionRows; idx++)
	{
		pKeggSet = new CKEGGSet(sizeDEMatrix);
		lReturn = pKeggSet->SetKeggRow(pTableKEGGDescription->GetRow(idx));
		if (lReturn != ERR_NOERROR)
		{
			delete pKeggSet;
			return lReturn;
		}
		pvecKeggSets->push_back(pKeggSet);

	}

	SortKeggVectorAlphabeticallyKEGGID(pvecKeggSets); //we want to have it alphabetically ordered.


	return lReturn;
}

long InputTableFiles(CTable* pTableKEGGMatrix, CTable* pTableKEGGDescription)
{
	long lReturn = ERR_NOERROR;

	//Parse teh KEGG Matrix file
	printf_s("Parsing the KEGG Matrix file %s", EOL);
	std::string strKeggMatrixFilePath;
	lReturn = glb.propertyBag.GetKEGGMatrixPath(&strKeggMatrixFilePath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_KEGGMATRIX_KEGGCOUNTER;
	lReturn = pTableKEGGMatrix->ParseTableWithPath(strKeggMatrixFilePath, 9, true); //9 = ASCII TAB
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done parsing the KEGG Matrix file %s", EOL);


	printf_s("Parsing the KEGG Description file %s", EOL);
	std::string strKEGGDescriptionPath;
	lReturn = glb.propertyBag.GetKEGGDescriptionPath(&strKEGGDescriptionPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_KEGGDESCRIPTION_KEGGCOUNTER;
	lReturn = pTableKEGGDescription->ParseTableWithPath(strKEGGDescriptionPath, 9, true); //9 = ASCII TAB
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done parsing the KEGG Description file %s", EOL);



	return lReturn;
}

long ParseInputFiles(CTable* pTableKEGGMatrix, CTable* pTableKEGGDescription, std::vector<CKEGGSet*>* pvecKEGGSet)
{
	long lReturn = ERR_NOERROR;
	/*
	This function parses the input files which are the Table Kegg matrix (output from DEMC), the Kegg Description file and then fill the pKEGGSet vector
	*/

	//Parses the KEGGMAtrix and the KEGG Description


	printf_s("Parsing the KEGG Matrix file and the KEGG Description file %s", EOL);
	lReturn = InputTableFiles(pTableKEGGMatrix, pTableKEGGDescription);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with Parsing the two files.%s", EOL);


	std::vector<char*> *pFirstRow = pTableKEGGMatrix->GetRow(0); //We need to know how many sets

	//Parsing the KEGG Set objects
	printf_s("Creating the KEGGSet Objects based on the KEGG Description file and the amount of sets from the KEGG Matrix file.%s", EOL);
	lReturn = ParseKEGGSetObjects(pTableKEGGDescription, pvecKEGGSet, (pFirstRow->size() - 3)); //-3 because first 3 columns are ISOForm ID, Protein ID, KEGG ID
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with creating the KEGGSet Objects %s", EOL);


	return lReturn;

}