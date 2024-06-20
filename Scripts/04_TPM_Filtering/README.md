# TPM Filtering
The fourth step of this project is to filter the reads based on the TPM values:
For this, we do the following:

- Estimate Transcript Abundance
- Build Transcript and Gene Expression Matrices
- Count the number of expressed Transcripts or Genes
- Filtering Transcripts Based on Expression Values
- Create New Trinity Gene Maps

For more detailed documentation about all the options, go to [Trinity Documentation](https://github.com/trinityrnaseq/trinityrnaseq/wiki/Trinity-Transcript-Quantification)

For all the steps, we use the Trinity Singularity image.

## Estimate Transcript Abundance
For establishing the Quantitative transcript abundance we use the trinity script "align_and_estimate_abundance.pl" shown in [02_TranscriptQuantitification_Trinity_Combined_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/04_TPM_Filtering/02_TranscriptQuantitification_Trinity_Combined_ALL.sh). </br>

As an estimation method, we use Kallisto's alignment-free abundance estimation method.

## Build Transcript and Gene Expression Matrices
To build the Transcript and Gene Expression matrices we use the Trinity script "abundance_estimates_to_matrix.pl" shown in [03_BuildTranscript_And_Gene_Expression_Matrix_Trinity_Combined_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/04_TPM_Filtering/03_BuildTranscript_And_Gene_Expression_Matrix_Trinity_Combined_ALL.sh)


## Count the number of expressed transcript or genes
We then create a list of how many different transcripts per matched TPM value with the trinity script "count_matrix_features_given_MIN_TPM_threshold.pl" for the genes and transcripts shown under [04_Count_Numbers_Expressed_Transcripts_And_Genes_Trinity_Combined_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/04_TPM_Filtering/04_Count_Numbers_Expressed_Transcripts_And_Genes_Trinity_Combined_ALL.sh)

## Filtering the Transcript based on Expression Values
Now that we have the list of transcripts/genes per TPM value, we can create new assembly files. By filtering out the lower TPM values (We use the TPM values of 1, 3, and 8). </br>
To filter, we use the Trinity Script filter_low_expr_transcripts.pl look at [05_Filter_Transcript_Based_on_Expression_Trinity_Combined_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/04_TPM_Filtering/05_Filter_Transcript_Based_on_Expression_Trinity_Combined_ALL.sh)

## Create new Trinity Gene Maps
The created trinity "assembly" files are based on the filtered TPM values. However, we still need the Gene map files. We create them with the trinity file "filter_low_expr_transcripts.pl" shown in [05_Filter_Transcript_Based_on_Expression_Trinity_Combined_ALL.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/04_TPM_Filtering/05_Filter_Transcript_Based_on_Expression_Trinity_Combined_ALL.sh)



