# KEGGCounter
To run this step, edit lines 3 to 12 in file [16_KEGGCounter.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/16_KEGGCounter/16_KEGGCounter.sh).

This tool runs with 1 CPU, and the amount of RAM depends on the input file. But it will never exceed 1.2x the size of all the input files combined.

Basically, this tool creates a KEGG tsv file that can instantly be used to create a bar plot in Excel and/or R.
It imports a KEGG description file (also tsv format), creates CKEGGSet objects out of that, and fills the counters in this CKEGGSet object based on the DE KEGG Matrix the user provides.

## KEGG Counter development notes
This tool is created with the boost library (v1.85). Development took place in Visual Studio 2019 community version with the GCC compiler (For remote Linux development). I've compiled 2 different (static) executables under Debian 10 (and tested under 11 and 12) [KEGGCounter_Debian.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/KEGGCounter/KEGGCounter_Debian.out), and Scientific Linux 7.9 which is based on Red Hat [KEGGCounter_HPC.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/KEGGCounter/KEGGCounter_HPC.out)

Either make your own executable with the corresponding source files or use one existing executable.

### Command line
Program format:
```
KEGGCounter.out -k <KEGG_Matrix> -d <KEGG_DESCRIPTION_FILE> -r <OUTPUT_FOLDER_PATH> -x <OUTPUT_PREFIX> -p <PREFIX_OF_KEGG_IDS> -c <THRESHOLD_DE_HIT> -h <THRESHOLD_KEGG_HITS> -s <THRESHOLD_MINIMUM_FOR_PAIR>
```

Program options:
```
-k <Kegg Matrix Path> Set the Path to the Kegg Matrix file: REQUIRED
-d <Kegg Description Path> Set the Path to the Kegg Description file, Aka list of ids\tDescription of all Kegs. See example:KEGG_Pathway_List_2024Feb15_2.txt REQUIRED
-r <Output Folder> Set the path for the output folder: REQUIRED
-x <Output_Prefix> Set the output prefix for the output file: NOT REQUIRED
-p <Prefix> Set the Prefix of the KEGG Matrix, KEGG IDs. e.g. of KEGG ID prefix is ko in ko00010: NOT REQUIRED
-c <Threshold DE Hit> Set the threshold of the Log2Fold values for the DE levels. e.g., 1.0 = values below -1.0 and above 1.0 are counted. This is a decimal number, so you can also say 0.1, 0.3, etc: NOT REQUIRED (But recommended)
-h <Threshold KEGG hits> minimum amount of hits every set has to get to pass into the output file: NOT REQUIRED but recommended 
-s <Threshold minimum amount for sample pair> Minimum amount of hits every sample (they are paired per two as they have up and down-regulation hits) has to have to make the KEGG ID be parsed into the output file
```
