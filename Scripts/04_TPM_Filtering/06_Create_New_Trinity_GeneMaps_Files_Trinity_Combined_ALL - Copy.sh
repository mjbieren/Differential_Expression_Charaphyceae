#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

FILTERED_FILE_100=[PATH]/Balt_Filter_Transcript_TPM_1.fa #replace the first folder with "mounted"
FILTERED_FILE_300=[PATH]/Balt_Filter_Transcript_TPM_3.fa #replace the first folder with "mounted"
FILTERED_FILE_800=[PATH]/Balt_Filter_Transcript_TPM_8.fa #replace the first folder with "mounted"

SINGULARITY_TRINITY_IMAGE=[PATH]/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg #You've to download it from the Trinity website. get latest from: https://data.broadinstitute.org/Trinity/TRINITY_SINGULARITY/


#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the localisation error for perl
export LC_ALL=C

#Filter Based on TPM 1
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/support_scripts/get_Trinity_gene_to_trans_map.pl $FILTERED_FILE_100 > Balt_Filter_Transcript_TPM_1.fa.gene-trans-map

#Filter Based on TPM 3
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/support_scripts/get_Trinity_gene_to_trans_map.pl $FILTERED_FILE_300 > Balt_Filter_Transcript_TPM_3.fa.gene-trans-map

#Filter Based on TPM 8
singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/support_scripts/get_Trinity_gene_to_trans_map.pl $FILTERED_FILE_800 > Balt_Filter_Transcript_TPM_8.fa.gene-trans-map
