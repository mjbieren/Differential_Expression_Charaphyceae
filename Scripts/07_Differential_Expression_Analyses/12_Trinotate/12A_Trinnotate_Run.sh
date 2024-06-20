#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD} #Generally don't change or know what you're doing ;)

SINGULARITY_TRINNOTATE_IMAGE=/home/Singularity_Images/Trinnotate/trinotate.v4.0.2.simg
DB_NAME=/home/Trinotate_100.sqlite #Pre created database see trinotate documentation
TRINOTATE_DIR= #Location of the trinotate storage directory (aka when you create a trinotate database, where is that folder).
TRINOTATE_GENE_MAP_FILE= #Trinity Gene map file
TRINOTATE_TRINITY_FILE= #Trinity Assembly file
TRINOTATE_PEPTIDE_FILE= #Transdecoder pep file.
THREADS=30

export LC_ALL=C


###TRINOTATE###
#init Trinotate
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted ${SINGULARITY_TRINNOTATE_IMAGE} /usr/local/src/Trinotate/Trinotate --db ${DB_NAME} --trinotate_data_dir ${TRINOTATE_DIR} --init --gene_trans_map ${TRINOTATE_GENE_MAP_FILE} --transcript_fasta ${TRINOTATE_TRINITY_FILE} --transdecoder_pep ${TRINOTATE_PEPTIDE_FILE}

#Running the analysis
#Run Infernal separately
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db ${DB_NAME} --trinotate_data_dir ${TRINOTATE_DIR} --CPU ${THREADS} --transcript_fasta ${TRINOTATE_TRINITY_FILE} --transdecoder_pep ${TRINOTATE_PEPTIDE_FILE} --run "swissprot_blastp swissprot_blastx pfam EggnogMapper" --use_diamond
