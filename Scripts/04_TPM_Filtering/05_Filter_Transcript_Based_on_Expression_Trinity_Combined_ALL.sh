#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

MATRIX=[PATH]/Balt_Only_abundance_estimates_matrix.isoform.TMM.EXPR.matrix #replace the first folder with "mounted"
TRINITY_OUTPUT_FILE=[PATH]/TRINITY_BALT.Trinity.fasta #replace the first folder with "mounted"
SINGULARITY_TRINITY_IMAGE=[PATH]/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg #You've to download it from the Trinity website. get latest from: https://data.broadinstitute.org/Trinity/TRINITY_SINGULARITY/


#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#Filter Based on TPM 1
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/filter_low_expr_transcripts.pl --matrix $MATRIX --transcripts $TRINITY_OUTPUT_FILE --trinity_mode --min_expr_any 1 > Balt_Filter_Transcript_TPM_1.fa

#Filter Based on TPM 3
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/filter_low_expr_transcripts.pl --matrix $MATRIX --transcripts $TRINITY_OUTPUT_FILE --trinity_mode --min_expr_any 3  > Balt_Filter_Transcript_TPM_3.fa

#Filter Based on TPM 8
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/filter_low_expr_transcripts.pl --matrix $MATRIX --transcripts $TRINITY_OUTPUT_FILE --trinity_mode --min_expr_any 8 > Balt_Filter_Transcript_TPM_8.fa
