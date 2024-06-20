#include "GlobalHelper.h"

#define TOTALREQUIREMENTS 8

long ParseCommandLine(int argc, char* argv[], char* envp[])
{
	long lRet = ERR_NOERROR;

	int aiRequirements[TOTALREQUIREMENTS] = { 0,0,0,0,0,0,0,0 };
	for (int i = 1; i < argc; i++)
	{

		printf_s("arg %i, %s %s", i, argv[i], EOL);



		if (*argv[i] == '-') //switch detected
		{
			switch (argv[i][1])
			{
			case 'f': //Input fasta trinity file
				lRet = glb.propertyBag.SetFastaTrinityPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_FASTA_TRINITY_DEMC;
				aiRequirements[0] = 1;
				break;
			case 'p': //Input fasta protein file
				lRet = glb.propertyBag.SetFastaProteinPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return 	PARSECOMMANDLINE_FASTA_PROTEIN_DEMC;
				aiRequirements[1] = 1;
				break;
			case 't': //Trinotate report file
				lRet = glb.propertyBag.SetTrinotatePath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_TRINOTATE_REPORT_DEMC;
				aiRequirements[2] = 1;
				break;
			case 'd': //Differental Expression matrix path
				lRet = glb.propertyBag.SetDEMatrixPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_DIFFERENTIAL_MATRIX_DEMC;
				aiRequirements[3] = 1;
				break;
			case 'i': //Infernal output file
				lRet = glb.propertyBag.SetInfernalPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_INFERNAL_DEMC;
				aiRequirements[4] = 1;
				break;
			case 'r': //Output Folder path
				lRet = glb.propertyBag.SetOutputDir(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_OUTPUT_FOLDER_DEMC;
				aiRequirements[5] = 1;
				break;
			case 'a':
				lRet = glb.propertyBag.SetPrefixValue(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_PREFIX_DEMC;
				aiRequirements[6] = 1;
				break;
			case 'c': //Columns To Parse;
				lRet = glb.propertyBag.SetBoolDEFilterColumns();
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_BOOL_COLUMNS_DEMC;
				lRet = glb.propertyBag.SetTrinotateColumns(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_COLUMNS_TO_PARSE_DEMC;
				aiRequirements[7] = 1;
				break;
			case 'v': //Filter based on fasta peptide file bool
				lRet = glb.propertyBag.SetBoolFilterOnFastaFile();
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_BOOL_FASTA_FILTER_DEMC;
				break; //Not a requirement so not added.
			default:
			{
				printf_s("Invalid command line parameter no %i detected: %s %s", i, argv[i], EOL);
				return PARSE_COMMAND_LINE;
			}
			}

			/*

E-value

*/

		}
		else if (*argv[i] == '?')
		{
			//print arguments: ToDO change it
			printf_s(
				"%s"
				"-f <Trinity_Assembly>\t\t Set the Path to the trinity assembly file: REQUIRED %s"
				"-p <Protein_file>\t\t Set the Path to the path to the Protein file: REQUIRED %s"
				"-t <Trinotate>\t\t Set the Path to the Trinotate xls file: REQUIRED %s"
				"-d <Differential_Matrix> \t\t Set the path to the DE matrix, be sure the header has the same amount of columns as the rest. in TSV format: REQUIRED%s"
				"-i <Infernal_Output_File> \t\t Set the Path to the Infernal Output File: REQUIRED%s"
				"-r <Output Folder> \t\t Set the path for the output folder: REQUIRED%s"
				"-a <OUTPUT PREFIX> \t\t Add a prefix to the output files: NOT REQUIRED. Not setting this will result in files having the names like _DE_Matrix. Instead of <PREFIX>_%s"
				"-p <ColumsYouWantInOutput> \t\t Setting this will only show these colums and nothing else. e.g. '#gene_id,transcript_id,prot_id,Kegg,gene_ontology_Pfam,EggNM.Description,EggNM.PFAMs' NOT REQUIRED. Not setting it will result in only the columns transcript_id, #gene_id, prot_id, Kegg in the output file.%s"
				"-v \t\t Setting this variable will cause the program to filter based on the fasta peptide file (transdecoder output). %s"
				"%s"
				, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL);
			return PARSE_COMMAND_LINE_MAN;
		}
		if (lRet != ERR_NOERROR)
			return lRet;
	}

	//Check if -t, -n and -p are set if not give a messsage to the user

	if (aiRequirements[6] == 0)
	{
		printf_s("The Prefix for the output files is not added. Output files will not have a prefix %s", EOL);
		aiRequirements[6] = 1;
	}


	if (aiRequirements[7] == 0)
	{
		printf_s("The column filter is not set, only columns transcript_id, #gene_id, prot_id and Kegg will be used %s", EOL);
		aiRequirements[7] = 1;
	}

	//Check if the other requiprements are met, if not sent a message to the user like if they would use ?. And sent back an error message.
	int iSum = 0;
	size_t idx = 0;
	while (idx < TOTALREQUIREMENTS)
	{
		iSum += aiRequirements[idx];
		idx++;
	}

	if (iSum == TOTALREQUIREMENTS)
		return lRet;
	else
	{
		//print arguments
		printf_s(
			"%s"
			"-f <Trinity_Assembly>\t\t Set the Path to the trinity assembly file: REQUIRED %s"
			"-p <Protein_file>\t\t Set the Path to the path to the Protein file: REQUIRED %s"
			"-t <Trinotate>\t\t Set the Path to the Trinotate xls file: REQUIRED %s"
			"-d <Differential_Matrix> \t\t Set the path to the DE matrix, be sure the header has the same amount of columns as the rest. in TSV format: REQUIRED%s"
			"-i <Infernal_Output_File> \t\t Set the Path to the Infernal Output File: REQUIRED%s"
			"-r <Output Folder> \t\t Set the path for the output folder: REQUIRED%s"
			"-a <OUTPUT PREFIX> \t\t Add a prefix to the output files: NOT REQUIRED. Not setting this will result in files having the names like _DE_Matrix. Instead of <PREFIX>_%s"
			"-p <ColumsYouWantInOutput> \t\t Setting this will only show these colums and nothing else. e.g. '#gene_id,transcript_id,prot_id,Kegg,gene_ontology_Pfam,EggNM.Description,EggNM.PFAMs' NOT REQUIRED. Not setting it will result in only the columns transcript_id, #gene_id, prot_id, Kegg in the output file.%s"
			"-v \t\t Setting this variable will cause the program to filter based on the fasta peptide file (transdecoder output). %s"
			"%s"
			, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL);
		return PARSE_COMMAND_LINE_MAN;
	}

	return lRet;
}