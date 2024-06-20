# Differential Expression Charaphyceae
This overviews all (novel) tools and scripts we used in the Differential Expression Charaphyceae Project.
This GitHub does not contain the raw data we used and obtained (with some minor exceptions) during our Differential Expression Charaphyceae Project. For that, we would like to refer you to our Zenodo Link: [https://zenodo.org/records/10058795](https://zenodo.org/doi/10.5281/zenodo.10822046)


# Workflow
xx

# Introduction
Above. I've portrayed the Workflow in which the Differential Expression Charaphyceae Project was executed.

## 1. RNA Seq Data
All the RNA Seq Data was obtained "in-house". The SRA dataset can be obtained through the following project ID on SRA: [PRJNA1088485](https://www.ncbi.nlm.nih.gov/bioproject/PRJNA1088485)

Plant material of _C. tomentosa_ and _C. baltica_ from Michaelsdorf (54.371306 °N, 12.569778 °E), a lagoon in the Bodstedter bodden of the Darss-Zingst bodden chain, was used for this study. This site is characterized by a high proportion of organic suspended matter, which strongly affects the light climate and underwater vegetation. The sheltered part of the lagoon has soft muddy bottom up to 1m and is covered with charophytes of _C. tomentosa, C. baltica, Chara aspera_ and _Chara baltica var. liljebladii_.

The plants of both species were collected by hand in the year 2023 at a depth of 50-75 cm. Male plants of _C. tomentosa_ had developed antheridia. Harvested plants of _C. baltica_ exhibits antheridia and oogonia but no oospores. For all following analyses VT or top parts, also called RED in the samples (antheridia+swollen end cells at the top of the plant) for _C. tomentosa_ were used and whole plant samples (VT + antheridia and oogonia) for _C. baltica_ were used. Physico-chemical parameter was measured during sampling as followed: temperature 16°C, salinity 4.2 ‰, conductivity 11520 μS/cm (measured with a commercial device for home aquaculture). Plants were transported in their native water medium

Further Extraction was then done with the RNA from the Spectrum™ Plant Total RNA Kit (Sigma-Aldrich Chemie GmbH, Germany) according to the manufacturer’s instructions. DNAse I treatment (Thermo Fisher, Waltham, MA, USA) was applied to the RNA samples, and their quality and quantity were assessed using a 1% agarose gel with an SDS stain, and nanodrop (Thermo Fisher), respectively. The RNA samples were shipped on dry ice to Novogene (Cambridge, UK).

At Novogene (Cambridge, UK), the samples underwent quality checks using a Bionanalyzer (Agilent Technologies Inc., Santa Clara, CA, USA), and library preparation was performed based on polyA enrichment and using directional mRNA library preparation. The libraries were quality checked and sequenced using the NovaSeq 6000 platform (Illumina) with Novogene dual adapters: <br/>5’- AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGTAGATCTCGGTGGTCGCCGTATCATT-3’ <br/>for read 1 and <br/>5’- GATCGGAAGAGCACACGTCTGAACTCCAGTCACGGATGACTATCTCGTATGCCGTCTTCTGCTTG-3’

## 2. FastQC
[FastQC](https://github.com/s-andrews/FastQC) ([Simon Andrews](https://www.bioinformatics.babraham.ac.uk/projects/fastqc/)) was used as a quality control, as very bad samples (Either from our in-house or downloaded from the SRA set) were then identified to be removed. Even if we removed the bad reads, some of them had such a low read count after trimming that we decided not to include them in our sample list and, therefore not included within the project. <br/>For more information on how FastQC was used within the project, go to [FASTQC](Scripts/01_FastQC).</br></br> For more information on FastQC please go to their site http://www.bioinformatics.babraham.ac.uk/projects/fastqc/


## 3. Trinity *de novo* Assembly
After FastQC quality control, all samples were then assembled with the Trinity pipeline. <br/>First, the adapters were trimmed with [Trimmomatic](https://github.com/usadellab/Trimmomatic) ([A. M Bolger et al_2014](https://academic.oup.com/bioinformatics/article/30/15/2114/2390096)) with the settings:
```
-trimmomatic “novogene_adapter_sequences.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36”
```

Followed by running [Trinity](https://github.com/trinityrnaseq/trinityrnaseq) ([Haas *et al* 2013](https://www.nature.com/articles/nprot.2013.084)) with the command 
```
Trinity --seqType fq --left [LEFT_READS] --right [RIGHT_READS] --output [OUTPUT_FOLDER] --SS_lib_type RF --CPU 48 --trimmomatic --full_cleanup --max_memory 350G --quality_trimming_params  "ILLUMINACLIP:novogene_adapter_sequences.fa:2:30:10:2:keepBothReads LEADING:3 TRAILING:3 MINLEN:36"
```
I highly recommend reading Trinity's [Wiki site](https://github.com/trinityrnaseq/trinityrnaseq/wiki), which explains everything pretty well.<br/><br/>

See [TRINITY](Scripts/02_Trinity) for a more in-depth overview of what we did.
