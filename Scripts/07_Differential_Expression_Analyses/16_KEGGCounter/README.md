# KEGGCounter
To run this step, edit lines 3 to 12 in file [16_KEGGCounter.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/16_KEGGCounter/16_KEGGCounter.sh).

This tool runs with 1 CPU, and the amount of RAM depends on the input file. But it will never exceed 1.2x the size of all the input files combined.

Basically, this tool creates a KEGG tsv file that can instantly be used to create a bar plot in Excel and/or R.
It imports a KEGG description file (also tsv format), creates CKEGGSet objects out of that, and fills the counters in this CKEGGSet object based on the DE KEGG Matrix the user provides.

## KEGG Counter development notes
This tool is created with the boost library (v1.85). Development took place in Visual Studio 2019 community version with the GCC compiler (For remote Linux development). I've compiled 2 different (static) executables under Debian 10 (and tested under 11 and 12) [KEGGCounter_Debian.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/KEGGCounter/KEGGCounter_Debian.out), and Scientific Linux 7.9 which is based on Red Hat [KEGGCounter_HPC.out](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Executables/KEGGCounter/KEGGCounter_HPC.out)
