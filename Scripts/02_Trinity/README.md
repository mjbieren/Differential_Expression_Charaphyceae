# Trinity
This is the second step within the pipeline. Generally, you have to edit [Trinity_HPC.sh](https://github.com/mjbieren/Differential_Expression_Charaphyceae/blob/main/Scripts/02_Trinity/02_Trinity_HPC.sh) if you run Trinity in a slurm system. <br/>
You can also run the script on a dedicated machine but change the script accordingly :) 
Alternatively, you can install Trinity within a conda environment, but I don't recommend this.

We decided to run Trinity through it's singularity image, since it causes the least of problems to get Trinity to work (Really recommended to use instead).


For more information, go to the [Trinity Github](https://github.com/trinityrnaseq/trinityrnaseq) <br/>
I highly recommend reading their [Wiki site](https://github.com/trinityrnaseq/trinityrnaseq/wiki), which explains everything pretty well.

