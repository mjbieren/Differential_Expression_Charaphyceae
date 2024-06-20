
# TransDecoder
Our 5th step is to obtain proteins from our Trinity files since we will use these proteins files for the trinotate step.

In our case, TransDecoder was already installed on our High-Performance Cluster, so we could run this on the system there without installing it.

But you can install it with a conda environment:
```
conda create -n transdecoder -c conda-forge -c bioconda transdecoder
```

Then simply edit the [TransDecoder.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/05_Transdecoder/Transdecoder.sh) script and run it.

For more information on TransDecoder, go to their website: [Transdecoder](https://github.com/TransDecoder/TransDecoder/wiki)
