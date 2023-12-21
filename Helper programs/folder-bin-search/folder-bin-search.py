import os

#search through a folder of binary files to find the one with a specific sequence of bytes

#the desired sequence of bytes to be searched for
sequence = b'\x23\x52\x66\x66\x66\x64'

#choose the folder of binary files
workingDir = os.chdir(path="C:\\Users\\ben\\Desktop\\AJ-Retrial\\Extracted materials\\cpac2d.bin\\subarc01")

#list for the files that have the sequence
matches = []

#iterate through each file in the folder
for file in os.listdir(workingDir):
    with open(file, 'rb') as f:
        #read the entire file into a string of bytes
        s = f.read()
        
        #and check that string of bytes for the byte sequence
        if (s.find(sequence) != -1):
            matches.append(f.name)

print(matches)