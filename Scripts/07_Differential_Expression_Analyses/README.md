# Differential Expression Charaphyceae
The 7th step of this project is the actual Differential Expression analysis. For this, we do the following:

- Transcript Quantification
- Build Transcript and Gene Matrices
- Count Number Expressed for Transcript and Genes
- Compare the different Replicates for each Sample
- Differential Expression Analyses
- Trinotate
- Rename Matrix
- Extract Differential Expressed Transcript
- DEMC
- KEGG Counter

For more detailed documentation about all the options, go to [Trinity-Differential-Expression](https://github.com/trinityrnaseq/trinityrnaseq/wiki/Trinity-Differential-Expression) [Trinotate](https://github.com/trinityrnaseq/trinityrnaseq/wiki/Functional-Annotation-of-Transcripts)

## Transcript Quantification
After we have filtered the transcript per TPM levels, we again have to quantify the transcript with the Trinity script "align_and_estimate_abundance.pl" which is included in [07_Transcript_Quantification.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/07_Transcript_Quantification/07_Transcript_Quantification.sh)

## Build Transcript and Gene Matrices
We again build the Transcript and Gene Expression matrices with the Trinity script "abundance_estimates_to_matrix.pl" shown in [08_BuildTranscript_And_Gene_Expression_Matrix.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/08_Build_Transcript_and_Gene_Matrices/08_BuildTranscript_And_Gene_Expression_Matrix.sh)

## Counter Number Expressed for Transcript and Genes
Again create a count matrix (for 1, 3, and 8 TPM). These are not used further but can be used as a qualifying check. Since fewer Isoforms are present, more reads could have been matched per Isoform. Again the trinity script "count_matrix_features_given_MIN_TPM_threshold.pl" was used. And can be seen under [09_Count_Number_Expressed_Transcripts_And_Genes.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/09_Count_Numbers_Expressed_Transcript_And_Genes_Trinity/09_Count_Number_Expressed_Transcripts_And_Genes.sh)

## Compare the different Replicates for each Sample
Here, we check the Quality Control of the samples and the biological Replicates. For more information and all the details, read the documentation of Trinity [here](https://github.com/trinityrnaseq/trinityrnaseq/wiki/QC-Samples-and-Biological-Replicates)
</br></br>
This step is separated into 3 steps
-PtR Compare each replicate for each sample under [10A_Compare_Replicates_For_Each_Sample.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/10_Compare_Replicates_For_Each_Sample_Trinity/10A_Compare_Replicates_For_Each_Sample.sh)
-PtR Compare Replicates Across Samples under [10B_Compare_Replicates_For_Each_Sample.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/10_Compare_Replicates_For_Each_Sample_Trinity/10B_Compare_Replicates_For_Each_Sample.sh)
-PCA under [10C_Compare_Replicates_For_Each_Sample.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/10_Compare_Replicates_For_Each_Sample_Trinity/10C_Compare_Replicates_For_Each_Sample.sh)

## Differential Expression Analyses
The differential analysis uses the DeSEQ2 method for both the genes and isoforms. This is done with the [Trinity](https://github.com/trinityrnaseq/trinityrnaseq/wiki/Trinity-Differential-Expression) script "run_DE_analysis.pl", which is included in [11_DeSEQ_Differential_Expression_Analysis.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/new/main/Scripts/07_Differential_Expression_Analyses/11_Differential_Expression_Analyses)

## Trinotate
We use Trinotate for functional annotation of the data. This is split into 6 different steps and uses the trinitrate singularity image. We also ran Infernal separately and included this into the load and Write step (2nd script).
- Run Trinotate (initialize the trinnotate database and run the files) [12A_Trinnotate_Run.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12A_Trinnotate_Run.sh)
- Load the analysis into the trinnotate database and write the report [12B_Trinnotate_Load_And_Write.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12B_Trinnotate_Load_And_Write.sh)
- Partition Genes into Expression Clusters [112C_Trinnotate_PostWrite.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12C_Trinnotate_PostWrite.sh)
- Get the Go Terms [12D_Get_GO_Terms.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12D_Get_GO_Terms.sh)
- Get Gene Lengths A [12E_Get_Gene_Lengths_From_Trinity_Files.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12E_Get_Gene_Lengths_From_Trinity_Files.sh)
- Get Gene Lengths B [12F_Get_Actual_Gene_Lengths_File.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/12_Trinotate/12F_Get_Actual_Gene_Length_File.sh)

## Rename Matrix
To redo the expression matrix with the features from Trinnotate, we used the Trinity Script "rename_matrix_feature_identifiers.pl" which is included in [13_Trinity_Rename_Matrix_Feature.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/13_Rename_Matrix/13_Trinity_Rename_Matrix_Feature.sh)

## Extract and cluster the Expressed transcripts
We run this script with the Trinity script "analyze_diff_expr.pl," but we include the Go annotations and gene lengths.
This step is split into two scripts [14A_Extract_And_Cluster_Expressed_Transcripts.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/14_Extract_Differential_Expressed_Transcript/14A_Extract_And_Cluster_Expressed_Transcripts.sh) and [14B_Extract_Genes_Into_Expression_Clusters_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/07_Differential_Expression_Analyses/14_Extract_Differential_Expressed_Transcript/14B_Extract_Genes_Into_Expression_Clusters_All.sh)

## DEMC
DEMC automatically 


