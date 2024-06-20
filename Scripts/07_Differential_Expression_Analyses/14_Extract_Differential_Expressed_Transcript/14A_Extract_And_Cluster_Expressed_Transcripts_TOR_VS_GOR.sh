#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_TRINITY_IMAGE=/home/maaike/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg
SINGULARITY_HOME_PATH=${PWD}

#TRINOTATE
MATRIX= #ALL_Only_abundance_estimates_matrix.isoform.counts.matrix
SAMPLE_LIST= #Biological_Replicates.txt
OUTPUT_GO_TERMS= #00_Filtered.go_annotations_Transcripts.txt
OUTPUT_GENE_LENGTH= #00_Filtered.TRINITY.gene_lengths.txt

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#Extracting and clustering differentially expressed transcripts
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/analyze_diff_expr.pl --matrix $MATRIX -P 0.01 --samples $SAMPLE_LIST --examine_GO_enrichment --GO_annots $OUTPUT_GO_TERMS --gene_lengths $OUTPUT_GENE_LENGTH

