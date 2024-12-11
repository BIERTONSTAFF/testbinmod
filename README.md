# Interface
![image](https://github.com/user-attachments/assets/a254ba06-c1b0-47ea-85c7-58d03727e0d2)
# Test
## Input
- InputMask = *.bin
- DeleteInputFiles = 0
- OutputDir = ./output
- OverwriteOutputFiles = CreateUniqueName(1)
- Mode = Timer(0)
- CheckInterval = 5
- XOR key = 1101 → 1101000000000000

![image](https://github.com/user-attachments/assets/a7e95046-6489-492b-ba31-1a0810d5f2e7)
### Input file content
"abc" → 61 62 63

## Output
### Files content
70 63 63 → "pcc"

![image](https://github.com/user-attachments/assets/6b65c173-3cf6-42f0-a440-ded1655b31c8)
