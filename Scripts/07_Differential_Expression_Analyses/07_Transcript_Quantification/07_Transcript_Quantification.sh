#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mnt as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mnt/

SINGULARITY_HOME_PATH=${PWD}

SAMPLE_FILES=/home/Sample_file.txt #create the sample file according to the trinity documentation
TRANSCRIPT_FILE=/home/Balt_Filter_Transcript_TPM_1.fa
GENE_TRANS_MAP=/home/Balt_Filter_Transcript_TPM_1.fa.gene-trans-map
EST_METHOD=kallisto #Alignment based: RSEM, Alignment_Free:kallisto|salmon
THREAD_COUNT=20
OUT=OUT=/home/07_Quantification/
SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1_Duplicate.simg #Change this


#Testing
#singularity exec --bind /data:/mnt $SINGULARITY_TRINITY_IMAGE ls /mnt

#To remove the local error for perl
export LC_ALL=C

singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/align_and_estimate_abundance.pl --transcripts $TRANSCRIPT_FILE --gene_trans_map $GENE_TRANS_MAP --seqType fq --samples_file $SAMPLE_FILES --est_method $EST_METHOD --thread_count $THREAD_COUNT --output_dir $OUT --prep_reference --trinity_mode
