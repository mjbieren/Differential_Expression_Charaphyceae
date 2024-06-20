#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD} #Generally don't change or know what you're doing ;)

SINGULARITY_TRINNOTATE_IMAGE=/home/Singularity_Images/Trinnotate/trinotate.v4.0.2.simg
DB_NAME= #trinotate database e.g. Trinotate_100.sqlite
TRINOTATE_DIR= #Trinotate data directory
THREADS=50

SWISS_BLASTP= #Blast output file for blastP
SWISS_BLASTX= #Blast output file for blastx
PFAM_OUTPUT= #TrinotatePFAM.out
EGGNOG_OUTPUT= #eggnog_mapper.emapper.annotations
INFERNAL_OUTPUT= #infernal.out

export LC_ALL=C

###TRINOTATE###
#Loading the data
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db $DB_NAME --LOAD_swissprot_blastp $SWISS_BLASTP

singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db $DB_NAME --LOAD_swissprot_blastx $SWISS_BLASTX

singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db $DB_NAME --LOAD_pfam $PFAM_OUTPUT

singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db $DB_NAME --LOAD_EggnogMapper $EGGNOG_OUTPUT

singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --db $DB_NAME --LOAD_infernal $INFERNAL_OUTPUT

#Writing the report
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/Trinotate --report --db $DB_NAME --incl_pep --incl_trans>00_Filtered.Trinotate.xls
