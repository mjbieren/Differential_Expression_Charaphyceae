# Decontamination
Basically, this step requires MMseqs2, a decontamination database, and a conversion of your protein file to an MMseqs2 database.

## MMseqs2
MMSeqs2 is an ultra-fast and sensitive sequence search and clustering suite. It's a lot faster (100-10k times faster) than BLAST, and since we are looking at removing all decontaminants in a very strict matter, the slight loss in sensitivity can be ignored. Since performance is more important here, especially when comparing against a huge dataset (Against the whole: Archeae, Bacteria, Fungi, Viral, and Plastid dataset) we use MMseqs2 instead of BLAST.

MMSeqs2 is developed at the Söding's at the Max-Planck-Institute for Multidisciplinary Sciences, Göttingen.
To install MMseqs2 please follow the link https://github.com/soedinglab/MMseqs2


## Decontamination database
As a decontamination database, we downloaded the full RefSeq database for Archaea, Bacteria, Fungi, Invertebrates, mitochondria, Mitochondiroon, Parasite, Parasite, Protozoa, and all available virus genomes on 30 December 2024. For the Positive set, we used _Chara braunii_ S276

To make it easier to define what is a decontaminant and what is not I've reformatted all fasta headers with the script [simplify_headers_for_blastdb.py](https://github.com/mjbieren/Phylogenomics_klebsormidiophyceae/blob/main/Scripts/07_Decontamination/simplify_headers_for_blastdb.py) made by Dr. Iker Irrisari.
simply use the script by the command:

```
python [script] [inputFile] [RenameHeaders]>>[FileOutput]
```
where the FileOutput is the concatenated file for all sub-databases (e.g., RefSeq Bacteria, RefSeq Archeae, etc).
I used the following combinations:
```
"arch_neg" for the Archea set
"bact_neg" for the Bacteria set
"virus_neg" for the Viridae se"
"fungi_neg" for te Fungi set
"invert_neg for the Invertebrates"
"plast_neg" for the Plastid set
"pasm_neg" for the Plasmid set
"mito_neg" for the Mitochondrion set
"proto_neg" for the Protozoa 
"Cbraunii" for the Chara positive set
```
This means, for example, that for every fasta header for bacteria, we now have bact_neg-n, where n is the number. This is important since the step after the decontamination uses these as a reference (you can decide on your own what the names are, but they have to be consistent and preferable without spaces since many programs can not interpret a space properly).

Then simply use the commands:
```
mmseqs createdb Decontamination_Chara_DB.fa Decontamination_Chara_DB.db
mmseqs createindex Decontamination_Chara_DB.db tmp
```
Your decontamination database is ready to use

## Conversion of your protein file.
Similar to creating a database for decontamination, you have the same commands for creating an MMseqs2 database for your protein file.
```
mmseqs createdb trinity_genes.fasta.transdecoder.pep StrainName_Chara_db.db || module purge && exit -1
mmseqs createindex StrainName_Chara_db.db tmp || module purge && exit -1
```
You can also use the script [ConvertToMMseqsDatabase.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/06_Decontamination/ConvertToMMseqsDatabase.sh) and run it in the same folder as the TransDecoder output .pep file.


## Running the script
Now simply run the script [Decontamination_MMSEQS_Memmode.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/06_Decontamination/Decontamination_MMSEQS_Memmode.sh)
Don't forget to change the variables on lines: 8,9,10,11.

The output will be a simple outfmt6 output, identical to a blast output file with outfmt6 format.

## GPDS
As described previously in my other repository, Phylogenomics_Klebsormidiophyceae, we use a tool to obtain the positive set out of the .outfmt file with "Get Positive Data set" or [GPDS](https://github.com/mjbieren/Phylogenomics_klebsormidiophyceae/tree/main/Scripts/08_GetPositiveDataSet_GPDS).

### Command Line commands
To run GPDS, follow this command guideline
```
GPDS.out -i <HeaderFile> -f <Fasta> -b <Blast> -c <EvalueColumn> -s <StrainName> -r <OutputPath>
```

Program options:
```

-i	<HeaderFile>	Basically an overview that the program uses to interpret if a header is a contaminant or not. E.g.
				HeaderName	+-	Full Name
				
				plast_neg	-	Plastid
				Cbraunii  +	Klebsormidiophyceae
```					
This means that everything with plast_neg is interpreted as a contaminant, and the fasta file name will be StrainName_Plastid.fa . 
The 2nd will be interpreted as a non-contaminant, and the fasta file name will be StrainName_Chara.fa.

```
-f	<FastaFile>		The Transdecoder Output File (.pep)
-b	<Blast>			The output file of MMseqs2 in blast .outfmt6 format.
-c	<ColumnNumber>		The column of the e-value. (Normally, this is 11, but can change due to settings)
-s	<StrainName>		The Strain Name of the sample
-r	<OutputPath>		The full path to the output folder.
-t				Unset the strict decontamination, ignore the positive set if the result is weaker (default is strict is on, best
				e-value is the one taken)
```
Alternatively you can edit [GPDS.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/06_Decontamination/GPDS.sh) and run the script
