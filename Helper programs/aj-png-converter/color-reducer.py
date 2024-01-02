import numpy as np
import skimage.io as io
from sklearn.cluster import KMeans
from PIL import Image as image

def countColors(imageLoc):
    originalImage = image.open(imageLoc).convert("RGB")
    colorArray = np.array(originalImage)
    dotProduct = np.dot(colorArray.astype(np.uint32),[1,256,65536]) #creates one 24-bit value for each pixel

    numColors = len(np.unique(dotProduct))
    return numColors


def reduceColors(imageLoc, reducedImageLoc, target):
    originalImage = image.open(imageLoc).convert("RGB")

    #array length needs to be divisible by three
    #since converting to RGB gives red, green, and blue values
    array = np.array(originalImage).reshape((-1,3))

    #targetNumColors/4 seems to make it more accurate to intended number
    kmeans = KMeans(n_clusters=round(target), tol=1e-4, random_state=4).fit(array)
    labels = kmeans.labels_
    centers = kmeans.cluster_centers_

    colorReduced = centers[labels].reshape(np.array(originalImage).shape).astype('uint8')

    io.imsave(reducedImageLoc, colorReduced)

    reducedNumColors = countColors(reducedImageLoc)
    print("After reduction, number of colors =", reducedNumColors)
    
    return reducedNumColors

def writePaletteData(binFile, imageLoc):
    #write 0x200 palette bytes, taking into account there may be less than 256 colors

    colorList = getUniqueColorsList(imageLoc)
    colorDict = createColorDict(colorList)
    

    for element in range (0, len(colorList)):
        binFile.write(colorDict.get(colorList[element]))
    
    for element in range(len(colorList)*2, 512, 2): #if less than 256 colors, fill the rest of the bytes with duplicates
        binFile.write(colorDict.get(colorList[0])) #step is 2, since each color is two bytes

    return colorList


def getUniqueColorsList(imageLoc):
    im = image.open(imageLoc)
    pixels = im.load()
    width = im.size[0]
    height = im.size[1]

    uniqueColorsList = []
    unique = True

    for x in range(0, width): #iterate through every pixel in image, column to column, left to right
        for y in range (0, height):
            for element in range (0, len(uniqueColorsList)): #check that the color isn't already in the list
                if (uniqueColorsList[element] == pixels[x, y]):
                    unique = False

            if unique:
                uniqueColorsList.append(pixels[x, y])
            unique = True #resets boolean for next check

    return uniqueColorsList


def createColorDict(colorList):
    #colorList is a list of tuples representing RGBA

    colorDict = {}
    colorBytes = bytes(0)

    for element in range (0, len(colorList)):
        colorBytes = convertRGBToAJ(colorList[element]) #convert one tuple in the list at a time to four bytes
        colorDict[colorList[element]] = colorBytes #add bytes to dict with RGBA tuple as key

    return colorDict


def convertRGBToAJ(RGBATuple):
    RGBList = list(RGBATuple)

    for element in range(0, 3):
        RGBList[element] = round((RGBList[element]*31)/255) #make RGB value in range 0, 31
        RGBList[element] = bin(RGBList[element]) #convert it to binary represented by string starting with "0b"
        RGBList[element] = RGBList[element][2 : len(RGBList[element])] #cut off the "0b"
        
        while (len(RGBList[element]) < 5):
            RGBList[element] = '0' + str(RGBList[element]) #ensures each string is five digits long
    
    binString = '0b0' + str(RGBList[2]) + str(RGBList[1]) + str(RGBList[0]) #0 for alpha, then five digits for B, G, and R
    hexString = hex(int(binString, base=2)) #convert to decimal int to convert to hex string
    hexString = hexString[2 : len(hexString)] #remove "0x"

    while (len(hexString) < 4): #hex string must be four bytes
        hexString = '0' + hexString
    
    hexString = hexString[2 : 4] + hexString[0 : 2] #flip endianness

    colorBytes = bytes.fromhex(hexString)

    return colorBytes


fileName = "trucy11"
fileLoc = fileName + ".png"
reducedFileLoc = fileName + "Reduced.png"

targetNumColors = 16
reducedNumColors = 0 #initialize variable

numColors = countColors(fileLoc)
print("Number of colors =", numColors)

if (targetNumColors < numColors):
    reducedNumColors = reduceColors(fileLoc, reducedFileLoc, targetNumColors)
else:
    print("No color reduction happened.")
    reducedFileLoc = fileLoc #so reducedImageLocation and reducedNumColors can be used regardless
    reducedNumColors = numColors


binFileName = fileName + "Palette.bin"

binFile = open(binFileName, "wb")
writePaletteData(binFile, reducedFileLoc)
binFile.close()