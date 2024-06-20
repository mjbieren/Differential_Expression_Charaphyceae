#!/bin/bash

source activate transdecoder

#Supertranscript fasta file
IN1=$PWD/trinity_genes.fasta #Change this
OUT=$IN1.transdecoder_dir #Change this
IN2=$OUT/longest_orfs.pep #Change this
OUT2=$OUT/.outfmt6 #Change this
REFERENCE_GENOME= #Change this

#Keep in mind you have to make a blast database first. E.g. below for creating a protein database from a reference fasta file
#makeblastdb -in Chara_braunii_COMBINED.Protein.faa -parse_seqids -title "Chara_DB" -dbtype prot -blastdb_version 4 #We work with version 4

#Create output folder so that the work dir isn't overcrowded. the "exit -1" is to make sure that the script doesn't continue if the directory creation fails. The -p options is to make sure that no error occurs when a directory already exist.
mkdir -p "$OUT" || exit -1

echo "Step 1 Extract the long open reading frames"
TransDecoder.LongOrfs -t $IN1 -O $OUT || exit -1  

echo "Step 2 predict the likely coding regions, but retain only the blastp hits"
TransDecoder.Predict -t $IN1 -O $OUT || exit -1
