#!/bin/bash
#If you use a singularity command be sure to change all your full paths to mounted as a start path since you have to mount your directory. Change the path accordingly. In this case /data/ is turned into /mounted/

SAMPLE_FILES=[PATH]/Quant_Files_ALL.txt #FullPath_x1_1.fg.qz,FullPath_x2_1fq.gz #replace the first folder with "mounted"
GENE_TRANS_MAP=[PATH]/TRINITY_BALT.Trinity.fasta.gene_trans_map #replace the first folder with "mounted"
EST_METHOD=kallisto #Alignment based: RSEM, Alignment_Free:kallisto|salmon 
OUT=[PATH]/Balt_Only_abundance_estimates_matrix #OutputPathFull #replace the first folder with "mounted"
SINGULARITY_TRINITY_IMAGE=[PATH]/Singularity_Images/Trinity/trinityrnaseq.v2.15.1.simg #You've to download it from the Trinity website. get latest from: https://data.broadinstitute.org/Trinity/TRINITY_SINGULARITY/



#Testing
#singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE ls /mounted

#To remove the local error for perl
export LC_ALL=C

singularity exec --bind /data:/mounted $SINGULARITY_TRINITY_IMAGE /usr/local/bin/util/abundance_estimates_to_matrix.pl --est_method $EST_METHOD --gene_trans_map $GENE_TRANS_MAP --out_prefix $OUT --quant_files $SAMPLE_FILES --name_sample_by_basedir 