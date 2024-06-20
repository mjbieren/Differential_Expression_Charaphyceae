#include "GlobalHelper.h"

#define TOTALREQUIREMENTS 3

long ParseCommandLine(int argc, char* argv[], char* envp[])
{
	long lRet = ERR_NOERROR;
	char* pEnd = nullptr;
	int aiRequirements[TOTALREQUIREMENTS] = { 0,0,0 };
	for (int i = 1; i < argc; i++)
	{

		printf_s("arg %i, %s %s", i, argv[i], EOL);

		

		if (*argv[i] == '-') //switch detected
		{
			switch (argv[i][1])
			{
			case 'k': //Input KEGG Matrix
				lRet = glb.propertyBag.SetKEGGMatrixPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_KEGGMATRIX_KEGGCOUNTER;
				aiRequirements[0] = 1;
				break;
			case 'd': //Input Kegg Description File
				lRet = glb.propertyBag.SetKEGGDescriptionPath(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return 	PARSECOMMANDLINE_KEGGDESCRIPTION_KEGGCOUNTER;
				aiRequirements[1] = 1;
				break;
			case 'r': //Output Folder
				lRet = glb.propertyBag.SetOutputFolder(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return 	PARSECOMMANDLINE_OUTPUT_FOLDER_KEGGCOUNTER;
				aiRequirements[2] = 1;
				break;
			case 'p': //Prefix Tag
				lRet = glb.propertyBag.SetBoolPrefix();
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_BOOL_PREFIXTAG_KEGGCOUNTER;
				lRet = glb.propertyBag.SetPrefix(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_PREFIXTAG_KEGGCOUNTER;
				break;
			case 'x':
				lRet = glb.propertyBag.SetOutputPrefix(&argv[i][3]);
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_OUTPUT_PREFIX_KEGGCOUNTER;
				break;
			case 'c': //Threshold KEGG DE value		
				lRet = glb.propertyBag.SetThresholdDE(strtof(&argv[i][3],&pEnd));
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_THRESHOLD_DE_KEGGCOUNTER;
				break;
			case 'h': //Threshold Minimum hits
				lRet = glb.propertyBag.SetThresholdMinimumCounter(atol(&argv[i][3]));
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_THRESHOLD_HITS;
				break;
			case 's': //Treshold minimum sets
				lRet = glb.propertyBag.SetThresholdMinimumSets(atol(&argv[i][3]));
				if (lRet != ERR_NOERROR)
					return PARSECOMMANDLINE_THRESHOLD_SETSAVAILABLE;
				break;		
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
				"-k <Kegg Matrix Path>\t\t Set the Path to the Kegg Matrix file: REQUIRED %s"
				"-d <Kegg Description Path>\t\t Set the Path to the Kegg Description file: REQUIRED %s"
				"-r <Output Folder> \t\t Set the path for the output folder: REQUIRED%s"
				"-x <Output_Prefix> \t\t Set the output prefix for the output file: NOT REQUIRED %s"
				"-p <Prefix>\t\t Set the Prefix of the KEGG Matrix, KEGG IDs: NOT REQUIRED %s"
				"-c <Threshold DE Hit> \t\t Set the treshold of the Log2Fold values for the DE levels. e.g. 1.0 = values below -1.0 and above 1.0 are counted. This is a decimal number so you can also say 0.1, 0.3 etc: NOT REQUIRED (But recommended) %s"
				"-h <Threshold KEGG hits> \t\t minimum amount of hits every set has to get in order to pass into the output file: NOT REQUIRED but recommended %s"					
				"-s <Threshold minimum amount of sets> \t\t Add a prefix to the output files: NOT REQUIRED. Not setting this will result in files having the names like _DE_Matrix. Instead of <PREFIX>_%s"
				"%s"
				, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL);
			return PARSE_COMMAND_LINE_MAN;
		}
		if (lRet != ERR_NOERROR)
			return lRet;
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
			"-k <Kegg Matrix Path>\t\t Set the Path to the Kegg Matrix file: REQUIRED %s"
			"-d <Kegg Description Path>\t\t Set the Path to the Kegg Description file: REQUIRED %s"
			"-r <Output Folder> \t\t Set the path for the output folder: REQUIRED%s"
			"-x <Output_Prefix> \t\t Set the output prefix for the output file: NOT REQUIRED %s"
			"-p <Prefix>\t\t Set the Prefix of the KEGG Matrix, KEGG IDs: NOT REQUIRED %s"
			"-c <Threshold DE Hit> \t\t Set the treshold of the Log2Fold values for the DE levels. e.g. 1.0 = values below -1.0 and above 1.0 are counted. This is a decimal number so you can also say 0.1, 0.3 etc: NOT REQUIRED (But recommended) %s"
			"-h <Threshold KEGG hits> \t\t minimum amount of hits every set has to get in order to pass into the output file: NOT REQUIRED but recommended %s"					
			"-s <Threshold minimum amount of sets> \t\t Add a prefix to the output files: NOT REQUIRED. Not setting this will result in files having the names like _DE_Matrix. Instead of <PREFIX>_%s"
			"%s"
			, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL, EOL);
		return PARSE_COMMAND_LINE_MAN;
	}

	return lRet;
}