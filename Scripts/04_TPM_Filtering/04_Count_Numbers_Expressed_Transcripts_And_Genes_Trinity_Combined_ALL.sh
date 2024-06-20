#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/
SINGULARITY_HOME_PATH=${PWD}
GENE_COUNTS_INPUT=Balt_Only_abundance_estimates_matrix.gene.TPM.not_cross_norm
GENE_COUNTS_OUTPUT=Balt_Only_abundance_estimates_matrix.gene.TPM.not_cross_norm.counts_by_min_TPM
TRANSCRIPT_COUNTS_INPUT=Balt_Only_abundance_estimates_matrix.isoform.TPM.not_cross_norm
TRANSCRIPT_COUNTS_OUTPUT=Balt_Only_abundance_estimates_matrix.isoform.TPM.not_cross_norm.counts_by_min_TPM
SINGULARITY_TRINITY_IMAGE=[PATH]/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg #You've to download it from the Trinity website. get latest from: https://data.broadinstitute.org/Trinity/TRINITY_SINGULARITY/


#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#counting number of expressed genes
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/misc/count_matrix_features_given_MIN_TPM_threshold.pl $GENE_COUNTS_INPUT | tee $GENE_COUNTS_OUTPUT


#counting number of expressed Transcripts
singularity exec --home $SINGULARITY_HOME_PATH:/home --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/misc/count_matrix_features_given_MIN_TPM_threshold.pl $TRANSCRIPT_COUNTS_INPUT | tee $TRANSCRIPT_COUNTS_OUTPUT
