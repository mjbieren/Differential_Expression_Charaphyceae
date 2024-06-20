# BUSCO I
The 3rd step is running BUSCO to determine how complete the alignments are (which is a good indication of whether we can use the dataset or not)

In my case BUSCO was a module already installed on our High Performance Cluster system. But you can also run it through a conda environment.

```
conda create -n busco -c conda-forge -c bioconda busco
```

Afterward simply edit the [Busco.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/03_BUSCO/Busco.sh) script and run it.


For more information on BUSCO please go to their website [BUSCO](https://busco.ezlab.org/)
