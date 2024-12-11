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
- XOR key = DE AD BE EF CA FE BA BE

![image](https://github.com/user-attachments/assets/a7e95046-6489-492b-ba31-1a0810d5f2e7)
### Input file content
"DEAD BEEF CAFE BABE" → 44 45 41 44 20 42 45 45 46 20 43 41 46 45 20 42 41 42 45

## Output
### Files content
9A E8 FF AB EA BC FF FB 98 8D FD AE 8C BB 9A FC 9F EF FB

![image](https://github.com/user-attachments/assets/6b65c173-3cf6-42f0-a440-ded1655b31c8)
