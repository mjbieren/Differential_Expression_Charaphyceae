#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg
SINGULARITY_HOME_PATH=${PWD}

#HOME_FOLDER=$(pwd)

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#TRINOTATE
RDATA=diffExpr.P0.01_C2.matrix.RData

#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/run_DE_analysis.pl --matrix $MATRIX --method $METHOD --samples_file $SAMPLE_LIST --output $OUTPUT_PREFIX --contrast $CONTRAST_FILE

#Extracting and clustering differentially expressed transcripts
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/Analysis/DifferentialExpression/define_clusters_by_cutting_tree.pl -R $RDATA --Ptree 60


