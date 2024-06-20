#!/bin/bash
#SBATCH -p medium
#SBATCH -t 48:00:00
#SBATCH -o %J_ZygnemaTrinity.out
#SBATCH -c 24
#SBATCH -C scratch
#SBATCH --exclusive
#SBATCH --mem 300G

SINGULARITY_HOME_PATH=${PWD} #Generally don't change or know what you're doing ;)
CPU=24 #change
RAM=300G #Change
STRAIN=${PWD##**/} #Name of the output file, generally I use the strain name but you can also do whatever you want here. Just that the files will be named like that :)
TRINITY_OUTPUT=Trinity_Output #Don't touch
IN1=/home/RawData/ #FullPath_x1_1.fg.qz,FullPath_x2_1fq.gz //Change Pair Left
IN2=/home/RawData/ #x1_2.fg.qz,x2_2fq.gz //Change Pair Right
#SINGLE=/home/RawData/ERR3005824_1.fastq,/home/RawData/ERR3005825_1.fastq #Single one line FullPath_x1_1.fg.qz,FullPath_x2_1fq.gz

SINGULARITY_TRINITY_IMAGE=/home/Singularity_Objects/Trinity/trinityrnaseq.v2.15.1.simg

module load singularity/3.8.5

#Novogene adapter Pair
singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --left ${IN1} --right ${IN2} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/novogene_adapter_sequences.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"

#Novogene Adapter Single
#singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --single ${SINGLE} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/novogene_adapter_sequences.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"

# TRUSEQ3 adapters (HiSeq and MiSeq) PAIR
#singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --left ${IN1} --right ${IN2} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/TruSeq3-PE.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"

# TRUSEQ3 adapters (HiSeq and MiSeq) Single
#singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --single ${SINGLE} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/TruSeq3-PE.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"

#TRUSEQ2 adapters (GAII machines)
#singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --left ${IN1} --right ${IN2} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/TruSeq2-PE.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"

#TRUSEQ2 adapters (GAII machines) Single
#singularity exec --home ${SINGULARITY_HOME_PATH}:/home -e ${SINGULARITY_TRINITY_IMAGE} Trinity --seqType fq --single ${SINGLE} --output /home/${TRINITY_OUTPUT} --CPU ${CPU} --trimmomatic --full_cleanup --max_memory ${RAM} --quality_trimming_params "ILLUMINACLIP:/mnt/TruSeq2-PE.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"


#Rename the last output files :)
mv ${SINGULARITY_HOME_PATH}/Trinity_Output.Trinity.fasta ${SINGULARITY_HOME_PATH}/${STRAIN}.Trinity.fasta
mv ${SINGULARITY_HOME_PATH}/Trinity_Output.Trinity.fasta.gene_trans_map ${SINGULARITY_HOME_PATH}/${STRAIN}.Trinity.gene_maps

module purge

#Remove the Trinity output folder in case it isn't deleted (sometimes happens.) but ignore if it already happens.
rm -r ${SINGULARITY_HOME_PATH}/${TRINITY_OUTPUT} || true


