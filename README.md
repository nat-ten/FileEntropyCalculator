# FileEntropyCalculator
Calculates the entropy of files to find encrypted or packed malware.

Utilizing the method from this paper, https://ieeexplore.ieee.org/document/4140989, this program calculates the entropy of files from the command line and compares them to the threshold from the paper, 6.677. Any files whose entropy score is higher than this threshold is flagged as likely to be encrypted or packed.
