#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

#TRINITY
MATRIX_ISOFORM_NORMALISED= #Filtered_1_ALL_Only_abundance_estimates_matrix.isoform.TMM.EXPR.matrix
SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#TRINOTATE
OUTPUT_TRINOTATE_REPORT_NAME_MAPPING= #1_Filtered.Trinotate.xls
OUTPUT_RENAME_MATRIX= #Renamed_Filtered_1_ALL_Only_abundance_estimates_matrix.isoform.TMM.EXPR.matrix


#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C


###RENAME_MATRIX_FEATURE
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/rename_matrix_feature_identifiers.pl $MATRIX_ISOFORM_NORMALISED $OUTPUT_TRINOTATE_REPORT_NAME_MAPPING > $OUTPUT_RENAME_MATRIX








