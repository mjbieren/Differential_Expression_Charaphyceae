#!/bin/bash
#If you use a singularity command, change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

#TRINITY
SINGULARITY_TRINITY_IMAGE=/home/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg
TRINOTATE_TRINITY_FILE= #Trinity file (ending with .fa)
OUTPUT_SEQ_LENGTH= #00_Filtered.TRINITY.fasta.seq_lens


#To remove the localisation error for perl
export LC_ALL=C


###Get the gene length file###
#Create a transcript lengths
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/misc/fasta_seq_length.pl $TRINOTATE_TRINITY_FILE > $OUTPUT_SEQ_LENGTH




