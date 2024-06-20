# Differential Expression Matrices Combined
To run this step, edit line 5 to 13 in file [15_DEMC.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/15_DEMC/15_DEMC.sh)

This tool runs with 1 CPU. The memory size depends on the input files (roughly combined size x 1,2). It runs on a 64-bit machine and is fast (it only takes a couple of seconds to run).

Basically, this tool combines the differentially expressed matrices from the trinitrate output and verifies this with the decontamination output file. This way, you only get the differential expression result of the proteins/genes that are decontaminated, not potential contaminants. 

## DEMC (Differential Expression Matrices Combined)
This tool is created with the boost library (v1.85). Development took place in Visual Studio 2019 community version with the GCC compiler (For remote Linux development). I've compiled 2 different (static) executables under Debian 10 (and tested under 11 and 12) [DEMC_Debian.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/DEMC/DEMC_Debian.out), and Scientific Linux 7.9 which is based on Red Hat [DEMC_HPC.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/DEMC/DEMC_HPC.out)

Either make your own executable with the corresponding source files or use one existing executable.

### Command line
Program format:
```
DEMC.out -f <Trinity_Assembly> -p <Protein_file> -t <Trinotate_Report> -d <Differential_Matrix> -i <Infernal_Ouput_file> -r <Output_Folder> -a <Output_prefix> -p <Columns_You_Want_In_Output_From_Trinitate_TSV_File> -v
```

Program Options:
```
-f <Trinity_Assembly> Set the Path to the trinity assembly file: REQUIRED
-p <Protein_file> Set the Path to the path to the Protein file: REQUIRED
-t <Trinotate> Set the Path to the Trinotate xls file: REQUIRED
-d <Differential_Matrix> Set the path to the DE matrix; be sure the header has the same amount of columns as the rest. in TSV format: REQUIRED
-i <Infernal_Output_File> Set the Path to the Infernal Output File: REQUIRED
-r <Output Folder> Set the path for the output folder: REQUIRED
-a <OUTPUT PREFIX> Add a prefix to the output files: NOT REQUIRED. Not setting this will result in files with names like _DE_Matrix. Instead of <PREFIX>_%s"
-p <ColumsYouWantInOutput> Setting this will only show these colums and nothing else. e.g. '#gene_id,transcript_id,prot_id,Kegg,gene_ontology_Pfam,EggNM.Description,EggNM.PFAMs' NOT REQUIRED. Not setting it will result in only the columns transcript_id, #gene_id, prot_id, Kegg in the output file.%s"
-v Setting this variable will cause the program to filter based on the fasta peptide file (transdecoder output).
```
