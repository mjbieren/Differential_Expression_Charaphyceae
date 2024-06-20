#include "GlobalHelper.h"

long InputInfernal(std::vector<CInfernal*>* pvecInfernal)
{
	/*
	This file is a bit complicated since it is issued as a table, but the column dividers are based on the character spaces instanced on the 2nd line of the file.
	However due to the some column texts being larger than the initial character spacing on the 2nd line, it often does not following this spacing.

	For the Infernal objects (each row = one object). We want the:
	Isoform ID (4th column)
	Acession (3rd Column)
	Description (Last Column) = EOL - 22 (Starting).

	#idx target name          accession query name            accession clan name mdl mdl from   mdl to seq from   seq to strand trunc pass   gc  bias  score   E-value inc olp anyidx afrct1 afrct2 winidx wfrct1 wfrct2 description of target
	#--- -------------------- --------- --------------------- --------- --------- --- -------- -------- -------- -------- ------ ----- ---- ---- ----- ------ --------- --- --- ------ ------ ------ ------ ------ ------ ---------------------


	Steps:
	1) Parse file into file buffer
	2) Loop over the file row by row and parses each row accordingly
	3) Fill the Infernal objects
	4) Clean up the file buffer
	5) Sort the objects
	6) Done




	*/

	long lReturn = ERR_NOERROR;

	//STEP ONE
	//Get the path to the Infernal
	std::string strInfernalPath;
	lReturn = glb.propertyBag.GetInfernalPath(&strInfernalPath);
	if (lReturn != ERR_NOERROR)
		return PROPTERYBAG_INFERNAL_DEMC;

	//Get the file buffer for the Infernal file
	char* pFileBuffer = nullptr;
	lReturn = SetFileBuffer(&pFileBuffer, strInfernalPath);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	//create a smart poitner so that we do not have to keep track of the file buffer, it will get auto deleted as soon as we leave the function.
	CSmartPtr<char> pAutoDeleteFileBuffer = pFileBuffer;


	//STEP TWO AND THREE
	char* pStart = pFileBuffer;
	char* pPos = pFileBuffer;
	char* pEnd = pFileBuffer;

	CInfernal* pInfernal = nullptr;

	size_t sizePositionColumn = 0;

	//First move the pStart of the actual file the 3rd line (or when there are no commands anymore (indicated by a #)
	while (*pStart == '#')
	{
		MOVE_PTR_TO_BOL(pStart);
	}

	//Count how big the last column is based on the characters which looks like *------------ (where the * is a space)
	//Move the pPos to the EOL of the 2nd line.
	
	//Move to BOL of line 2
	MOVE_PTR_TO_BOL(pPos);
	MOVE_PTR_TO_BOL(pEnd)
	//Move to EOL of line 2
	MOVE_PTR_TO_EOL(pEnd);
	//Now count how big the last column is (based on characters).
	while (*pEnd && *pEnd != ' ')
		pEnd--;

	sizePositionColumn = pEnd - pPos; //Start Position
	
	pEnd = pStart;
	pPos = pStart;

	//We are now looking at the actual data 
	while (*pStart)
	{
		if (*pStart == '#')
			break; //We are done

		//FILLING THE INFERNAL DESCRIPTION ITEM
		//Move the pEnd to the EOL
		MOVE_PTR_TO_EOL_REAL(pEnd);
		if (!pEnd)
			break; //we are done
		//Move pPos to the start of the Last Column
		pPos = pPos + sizePositionColumn;
		//Move Ptr to first alpha character (a-z/A-Z)
		MOVE_PTR_TO_ALPHA2(pPos);
		//Now move back to the first space (in case the there are numbers in the description (start)
		MOVE_PTR_TO_PREVIOUS_SPACE(pPos);
		if (pPos < pStart)
			return lReturn; //We are done
		//Now increase it by 1 since we don't want the pStart to be filled.
		pPos++;

		pInfernal = new CInfernal;

		lReturn = pInfernal->SetInfernalDescription(pPos, pEnd);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}

		//Now the other two columns

		//Accession
		MOVE_PTR_TO_SPACE(pStart);//Looking after the first column
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 2nd Column)
		MOVE_PTR_TO_SPACE(pStart); //Looking after the 2nd column
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 3rd column (the one we need :D )

		pPos = pStart;
		MOVE_PTR_TO_SPACE(pPos); //Looking at the start of the 4th column (the end of the 3rd column).
		lReturn = pInfernal->SetInfernalAccession(pStart, pPos);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}

		//Isoform ID.
		pStart = pPos;
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 4th column (the other one we need ;D )
		pPos = pStart;
		MOVE_PTR_TO_SPACE(pPos); //Looking after the 4th column
		lReturn = pInfernal->SetInfernalIsoformID(pStart, pPos);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}

		//Move the pointers to the start again :D
		MOVE_PTR_TO_BOL(pStart);
		pEnd = pStart;
		pPos = pStart;
		pvecInfernal->push_back(pInfernal);
	}

	if (*pStart != '#') // In case there is no Hash at the end (Program info)
	{
		//Now the last one
		pPos = pPos + sizePositionColumn;
		//Move Ptr to first alpha character (a-z/A-Z)
		MOVE_PTR_TO_ALPHA2(pPos);
		//Now move back to the first space (in case the there are numbers in the description (start)
		MOVE_PTR_TO_PREVIOUS_SPACE(pPos);
		if (pPos < pStart)
			return lReturn; //We are done
		//Now increase it by 1 since we don't want the pStart to be filled.
		pPos++;

		pInfernal = new CInfernal;

		lReturn = pInfernal->SetInfernalDescription(pPos, pEnd);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}

		//Now the other two columns

		//Accession
		MOVE_PTR_TO_SPACE(pStart);//Looking after the first column
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 2nd Column)
		MOVE_PTR_TO_SPACE(pStart); //Looking after the 2nd column
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 3rd column (the one we need :D )

		pPos = pStart;
		MOVE_PTR_TO_SPACE(pPos); //Looking at the start of the 4th column (the end of the 3rd column).
		lReturn = pInfernal->SetInfernalAccession(pStart, pPos);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}

		//Isoform ID.
		pStart = pPos;
		MOVE_PTR_TO_NON_SPACE(pStart); //Looking at the start of the 4th column (the other one we need ;D )
		pPos = pStart;
		MOVE_PTR_TO_SPACE(pPos); //Looking after the 4th column
		lReturn = pInfernal->SetInfernalIsoformID(pStart, pPos);
		if (lReturn != ERR_NOERROR)
		{
			delete pInfernal;
			return lReturn;
		}
		pvecInfernal->push_back(pInfernal);
	}

	//STEP SIX
	lReturn = SortInfernalVectorAlphabetically(pvecInfernal);
	if (lReturn != ERR_NOERROR)
		return lReturn;

	printf_s("We parsed %zu Infernal Objects %s", pvecInfernal->size(), EOL);

	//We are done :)
	return lReturn;
}

long InputTableFiles(CTable* pTableTrinotate, CTable* pTableDifferentialMatrix)
{
	long lReturn = ERR_NOERROR;

	//Parse Trinotate file
	printf_s("Parsing the Trinotate file %s", EOL);
	std::string strTablePathTrinotate;
	lReturn = glb.propertyBag.GetTrinotatePath(&strTablePathTrinotate);
	if (lReturn != ERR_NOERROR)
		return PROTERTYBAG_TRINOTATE_REPORT_DEMC;//
	lReturn = pTableTrinotate->ParseTableWithPath(strTablePathTrinotate, 9, true); //9 = ASCII TAB
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done parsing the Trinotate file %s", EOL);

	pTableTrinotate->SortTableRowsAlphabetically(1);


	printf_s("Parsing the Differential Matrix file %s", EOL);
	std::string strTablePathDifferentialMatrix;
	lReturn = glb.propertyBag.GetDEMatrixPath(&strTablePathDifferentialMatrix);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_DIFFERENTIAL_MATRIX_DEMC;
	lReturn = pTableDifferentialMatrix->ParseTableWithPath(strTablePathDifferentialMatrix);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with Parsing the Differential Matrix file %s", EOL);

	pTableDifferentialMatrix->SortTableRowsAlphabetically(0);


	return lReturn;
}

long InputFastaFiles(CFastaFile* pFastaFileTrinity, CFastaFile* pFastaFileProtein)
{
	long lReturn = ERR_NOERROR;

	std::string strFastaFileTrinityPath;
	lReturn = glb.propertyBag.GetFastaTrinityPath(&strFastaFileTrinityPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_FASTA_TRINITY_DEMC;

	std::string strFastaFileProteinPath;
	lReturn = glb.propertyBag.GetFastaProteinPath(&strFastaFileProteinPath);
	if (lReturn != ERR_NOERROR)
		return PROPERTYBAG_FASTA_PROTEIN_DEMC;

	lReturn = pFastaFileTrinity->ParseFastaFile(strFastaFileTrinityPath.c_str());
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = pFastaFileTrinity->SortFastaFileAlphabetically();
	if (lReturn != ERR_NOERROR)
		return lReturn;


	lReturn = pFastaFileProtein->ParseFastaFile(strFastaFileProteinPath.c_str());
	if (lReturn != ERR_NOERROR)
		return lReturn;
	lReturn = pFastaFileProtein->SortFastaFileAlphabetically();
	if (lReturn != ERR_NOERROR)
		return lReturn;


	return lReturn;
}

long ParseInputFiles(CFastaFile* pFastaFileTrinity, CFastaFile* pFastaFileProtein, CTable* pTableTrinotate, CTable* pTableDEMatrix, std::vector<CInfernal*>* pvecInfernal)
{
	long lReturn = ERR_NOERROR;
	/*
	This function parses all the input files into their respective object.
	1) FastaFile Trinity
	2) FastaFile Protein
	3) Table of Trinotate output
	4) Table of Differential Matrix
	5) Infernal File

	*/

	//STEP ONE AND TWO
	printf_s("Parsing the Trinity Assembly file and the Transdecoder output protein file into Fasta Objects. %s", EOL);
	lReturn = InputFastaFiles(pFastaFileTrinity, pFastaFileProtein);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with parsing the two fasta files (Trinity and Protein) into the fasta file objects. %s", EOL);

	//STEP THREE AND FOUR
	printf_s("Parsing the Trinotate report file and the Differential Matrix file into the table objects. %s", EOL);
	lReturn = InputTableFiles(pTableTrinotate, pTableDEMatrix);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with the parsing of the two tables (Trinotate Report & Differential Matrix) into the table objects. %s", EOL);

	//STEP FIVE
	printf_s("Parsing the Infernal file into the Infernal object. %s", EOL);
	lReturn = InputInfernal(pvecInfernal);
	if (lReturn != ERR_NOERROR)
		return lReturn;
	printf_s("Done with the parsing of the Infernal output file into the Infernal objects %s", EOL);

	return lReturn;
}

