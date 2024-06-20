#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

SAMPLE_FILES=/home/Quant_Files_ALL.txt #FullPath_x1_1.fg.qz,FullPath_x2_1fq.gz
GENE_TRANS_MAP=/home/TRINITY_BALT.Trinity.fasta.gene_trans_map
EST_METHOD=kallisto #Alignment based: RSEM, Alignment_Free:kallisto|salmon
OUT=/home/Filtered_00_Only_abundance_estimates_matrix #OutputPathFull
SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg



#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the local error for perl
export LC_ALL=C

singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/abundance_estimates_to_matrix.pl --est_method $EST_METHOD --gene_trans_map $GENE_TRANS_MAP --out_prefix $OUT --quant_files $SAMPLE_FILES --name_sample_by_basedir 
