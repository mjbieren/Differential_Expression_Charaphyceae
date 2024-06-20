#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}


MATRIX_GENE=/home/Filtered_1_ALL_Only_abundance_estimates_matrix.gene.counts.matrix
MATRIX_ISOFORM=/home/Filtered_1_ALL_Only_abundance_estimates_matrix.isoform.counts.matrix
SAMPLE_LIST=/home/Biological_Replicates.txt
OUTPUT_PREFIX=/home/11B_Differential_Expression_Analysis_Sample_Trinity_Combined_ALL
METHOD=DESeq2 #edgeR|DESeq2|voom
CONTRAST_FILE=/home/Contrast_File.txt

SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#Compare replicates for each of your samples
#Gene
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/run_DE_analysis.pl --matrix $MATRIX_GENE --method $METHOD --samples_file $SAMPLE_LIST --output ${OUTPUT_PREFIX}_GENE/ --contrast $CONTRAST_FILE

#Isoform
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/run_DE_analysis.pl --matrix $MATRIX_ISOFORM --method $METHOD --samples_file $SAMPLE_LIST --output ${OUTPUT_PREFIX}_Isoform/ --contrast $CONTRAST_FILE
