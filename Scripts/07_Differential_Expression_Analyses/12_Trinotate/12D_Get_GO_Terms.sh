#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD}

#TRINOTATE
SINGULARITY_TRINNOTATE_IMAGE=/home/Singularity_Images/Trinnotate/trinotate.v4.0.2.simg
DB_NAME= #Trinotate_100.sqlite
OUTPUT_TRINOTATE_REPORT_NAME_MAPPING= #00_Filtered.Trinotate.xls.name_mapping

OUTPUT_TRINOTATE_REPORT= #00_Filtered.Trinotate.xls
OUTPUT_GO_TERMS_GENES= #00_Filtered.go_annotations_GENES.txt
OUTPUT_GO_TERMS_TRANSCRIPTS= #00_Filtered.go_annotations_Transcripts.txt


#To remove the localisation error for perl
export LC_ALL=C


###RENAME_MATRIX_FEATURE
#GENES
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/util/extract_GO_assignments_from_Trinotate_xls.pl --Trinotate_xls $OUTPUT_TRINOTATE_REPORT -G --include_ancestral_terms > $OUTPUT_GO_TERMS_GENES

#TRANSCRIPTS
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/util/extract_GO_assignments_from_Trinotate_xls.pl --Trinotate_xls $OUTPUT_TRINOTATE_REPORT -T --include_ancestral_terms > $OUTPUT_GO_TERMS_TRANSCRIPTS













