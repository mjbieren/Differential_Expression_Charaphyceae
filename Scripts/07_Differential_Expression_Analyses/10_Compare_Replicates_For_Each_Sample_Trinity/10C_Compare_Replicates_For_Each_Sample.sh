#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

MATRIX=/home/Filtered_1_ALL_Only_abundance_estimates_matrix.isoform.counts.matrix
SAMPLE_LIST=/home/Biological_Replicates.txt
OUTPUT_PREFIX=Filtered_01_ALL_Only_C_
SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#Compare Replicates PCA
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE  /usr/local/bin/Analysis/DifferentialExpression/PtR --matrix $MATRIX --samples $SAMPLE_LIST --min_rowSums 10 --log2 --CPM --center_rows --prin_comp 3 --heatmap_colorscheme "red,blue" --save --output $OUTPUT_PREFIX

