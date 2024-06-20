#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg
OUTPUT_SEQ_LENGTH= #00_Filtered.TRINITY.fasta.seq_lens
OUTPUT_GENE_LENGTH= #00_Filtered.TRINITY.gene_lengths.txt
TRINOTATE_GENE_MAP_FILE= #GeneMap File
MATRIX_ISOFORM_NORMALISED= # Matrix isoform file. e.g. Balt_Only_abundance_estimates_matrix.isoform.TMM.EXPR.matrix

#To remove the localisation error for perl
export LC_ALL=C

#Create the actual gene length file
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/misc/TPM_weighted_gene_length.py --gene_trans_map $TRINOTATE_GENE_MAP_FILE --trans_lengths $OUTPUT_SEQ_LENGTH --TPM_matrix $MATRIX_ISOFORM_NORMALISED > $OUTPUT_GENE_LENGTH


