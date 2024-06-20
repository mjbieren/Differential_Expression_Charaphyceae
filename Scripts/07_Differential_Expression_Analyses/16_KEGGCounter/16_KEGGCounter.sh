#!/bin/bash

KEGG_MATRIX= #One of DEMC KEGG Matrix output files e.g. CHARA_1_Decontaminated_Filtered_DE_KEGG_Pathway_Matrix.tsv
KEGG_DESCRIPTION= #List of all the KEGG pathway/module/etc in a tsv manner e.g.  KEGG_Pathway_List_2024Feb15_2.txt Format is ID\tDescription 00010\tGlycolysis / Gluconeogenesis
OUTPUT_FOLDER= #Output folder path
OUTPUT_PREFIX= #output prefix e.g. CHARA_1_TPM_
THRESHOLD_DE=1.0 #Set the treshold of the Log2Fold values for the DE levels. e.g. 1.0 = values below -1.0 and above 1.0 are counted. This is a decimal number so you can also say 0.1, 0.3
THRESHOLD_KEGG_HITS=10 #minimum amount of hits every KEGG ID has to get in order to pass into the output file e.g. here 00010 has to have at least 10 hits to be shown in the output file.
THRESHOLD_MINIMUM_SETS=1 #Minimum amount of hits every sample (they are paired per two as they have up and down regulation hits) has to have to make the KEGG ID be parsed into the output file.
PREFIX=ko #Prefix of the kegg IDS in trinotate e.g. ko00010.

PROGRAMPATH=/home/maaike/Programs/KEGGCounter/KEGGCounter_Debian.out

$PROGRAMPATH -k $KEGG_MATRIX -d $KEGG_DESCRIPTION -p $PREFIX -r $OUTPUT_FOLDER -x $OUTPUT_PREFIX -c $THRESHOLD_DE -h $THRESHOLD_KEGG_HITS -s $THRESHOLD_MINIMUM_SETS
