#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SINGULARITY_HOME_PATH=${PWD} #Generally don't change or know what you're doing ;)

SINGULARITY_TRINNOTATE_IMAGE=/home/Singularity_Images/Trinnotate/trinotate.v4.0.2.simg
OUTPUT_TRINOTATE_REPORT= #Report name e.g. 00_Filtered.Trinotate.xls
OUTPUT_TRINOTATE_REPORT_NAME_MAPPING=${OUTPUT_TRINOTATE_REPORT}.name_mapping

THREADS=50


export LC_ALL=C


###Automatically Partitioning Genes into Expression Clusters###
singularity exec --home ${SINGULARITY_HOME_PATH}:/home --bind /data:/mounted $SINGULARITY_TRINNOTATE_IMAGE /usr/local/src/Trinotate/util/Trinotate_get_feature_name_encoding_attributes.pl $OUTPUT_TRINOTATE_REPORT > $OUTPUT_TRINOTATE_REPORT_NAME_MAPPING

