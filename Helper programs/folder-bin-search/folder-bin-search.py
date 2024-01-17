import os
import pathlib
from pprint import pprint as pprint

#search through a folder of binary files,
#recursively searching any folders within,
#to find the one(s) with a specific sequence of bytes

#the desired sequence of bytes to be searched for
sequence = b'\x10\x86\x01\x00\x00\x18\x00\x1F\x00\x23\x00\x27'

#choose the folder of binary files
folder = "C:\\Users\\ben\\Desktop\\AJ-Retrial\\Extracted materials"

#the list that will contain the matching files
matches = []

#iterate through each file in the folder recursively
for (root, dirs, files) in os.walk(folder):
    for item in files:
        path = pathlib.Path(f'{root}/{item}') #get path of selected file
        absolutePath = pathlib.Path.absolute(path)

        with open(absolutePath, 'rb') as f:
            #read the entire file into a string of bytes
            string = f.read() 
            offset = string.find(sequence) #byte offset of match in file, or -1 if none
            
            #and check that string of bytes for the byte sequence
            if (offset != -1):
                matches.append((f.name, offset))


if (len(matches) == 0): #if matches is empty
    print("No matches found.")
else:
    pprint(matches)