#!/bin/bash

#$PROGRAMPATH -f IsoForm.fa -p Peptide.fa -t Trinotate_Output_File -d MatrixOutput.dat -i Infernal_Output -r OutputFolder -a [Strain] -c Trinotate_columns

PROGRAMPATH=DEMC.out #Path to the program
TRINITY_OUTPUT= #Trinity output file e.g. Filter_Transcript_TPM_1.fa
TRANSDECODER_OUTPUT= #Transdecoder output e.g. Chara_TPM_1_Chara.fa
TRINITATE_OUTPUT= #Trinotate report file e.g. 1_Filtered.Trinotate.xls
MATRIX_OUTPUT= #Matrix output from step 14 e.g. 1_diffExpr.P0.001_C2.matrix.log2.centered.dat
INFERNAL_OUTPUT= #Output of infernal e.g. infernal.out
OUTPUT_FOLDER= #Output folder path
STRAIN= #Strain name (Ouput prefix) 
TRINOTATE_COLUMNS=transcript_id,#gene_id,prot_id,Kegg,infernal,gene_ontology_Pfam,EggNM.Description,EggNM.PFAMs Which columns you want basically from the trinotate report output (should be exact copy). Seperated by , no spaces

$PROGRAMPATH -f $TRINITY_OUTPUT -p $TRANSDECODER_OUTPUT -t $TRINITATE_OUTPUT -d $MATRIX_OUTPUT -i $INFERNAL_OUTPUT -r $OUTPUT_FOLDER -a $STRAIN -c $TRINOTATE_COLUMNS -v
