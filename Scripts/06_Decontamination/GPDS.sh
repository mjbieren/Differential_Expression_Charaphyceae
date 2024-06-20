#!/bin/bash

#$PROGRAM_PATH -i <Header> -f <Fasta> -b <Blast> -c <EvalueColumn> -s <StrainName> -r <OutputPath>

STRAIN=${PWD##**/} #Or just enter your strain name, my folders automatically were created with the strain name I wanted prior.
IN=*.outfmt6 #Match File MMseqs2 Output
HEADER= #HeaderFile
FASTA=*.pep #Fasta File source (Transdecoder Output)
PROGRAM_PATH= #The path to GPDS_[OS].out You have to compile this yourself or use on of the Executables /Executables/GPDS/
WORKINGDIR= #Output Path
#Run the program
$PROGRAM_PATH -i $HEADER -f $FASTA -b $IN -c 11 -s $STRAIN -r $WORKINGDIR
