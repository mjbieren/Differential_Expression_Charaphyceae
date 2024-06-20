# Phylogenetic Analysis
For the final step of this project, we did a phylogenetic analysis.

We first aligned our file with mafft L-INS-I
```
mafft-linsi input > output
```

To find the best model for proteins we used ModelFinder
```
$IQ_TREEPATH -nt $THREADS -m $AUTOMATIC_MODEL_SELECTION -madd LG+C60 -msub $MSUB -s $FILE_INPUT 
```

We then computed our maximum likelihood trees using IQ-Tree v. 1.5.5  with 1000 ultrafast bootstrap pseudo-replicates
```
$IQ_TREEPATH -nt $THREADS -m $AUTOMATIC_MODEL_SELECTION -msub $MSUB -s $FILE_INPUT -bb $BRANCH_TEST_REPLICATES -alrt $BRANCH_TEST_REPLICATES -pre $OUTPUT_PREFIX
```

Where Autmatic_Model selection was replaced with the model determined by ModelFinder.
