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
    originalImage = io.imread(imageLoc)

    targetNumColors = target

    array = originalImage.reshape((-1,3))
    kmeans = KMeans(n_clusters=round(targetNumColors/4), tol=1e-4, random_state=4).fit(array) #targetNumColors/4 seems to make it more accurate to intended number
    labels = kmeans.labels_
    centers = kmeans.cluster_centers_
    colorReduced = centers[labels].reshape(originalImage.shape).astype('uint8')

    io.imsave(reducedImageLoc, colorReduced)

    reducedNumColors = countColors(reducedImageLoc)
    print("After reduction, number of colors =", reducedNumColors)
    
    return reducedNumColors

#########################################################################################################

def writeHeaderData(binFile):
    fileHeader = [0x0, 0x1, 0xC0, 0x0]
    fileHeaderBytes = bytes(fileHeader)
    binFile.write(fileHeaderBytes)

#########################################################################################################

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
    tempList = []
    unique = True

    for x in range(0, width): #iterate through every pixel in image, column to column, left to right
        for y in range (0, height):
            tempList = list(pixels[x, y])
            tempList[3] = 255 #set alpha to 255 regardless, since it was fluctuating slightly
            pixels[x, y] = tuple(tempList)

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
    del RGBList[3] #remove alpha element, leaving RGB

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


#########################################################################################################

def writePixelData(binFile, imageLoc, colorList):
    im = image.open(imageLoc)
    pixels = im.load()

    width = im.size[0]
    height = im.size[1]

    startWidth = 0 #the coordinates to start iterating at for each tile
    startHeight = 0

    currentPixel = ()
    tempList = []
    hexString = ''
    
    tilesPerRow = width / 8

    for tiles in range(0, round(width*height/64)): #768 tiles total in 256 by 192 pixel image, 32 by 24 tiles
        startWidth = (tiles % tilesPerRow) * 8 #32 tiles per row, each tile is 8 pixels wide
        startHeight = ((tiles - (tiles % tilesPerRow))/tilesPerRow)*8 #lower to nearest start of row, then multiply by tile height
        
        for y in range (0, 8):
            for x in range (0, 8): #iterate through each tile row to row, top to bottom
                currentPixel = pixels[startWidth+x, startHeight+y]
                tempList = list(currentPixel)
                tempList[3] = 255 #set alpha to 255
                currentPixel = tuple(tempList)

                for element in range (0, len(colorList)):
                    if (currentPixel == colorList[element]):
                        hexString = hex(element)
                        hexString = hexString[2 : len(hexString)]

                        if len(hexString) == 1:
                            hexString = '0' + hexString #won't be read as hex if only one digit
                        
                        binFile.write(bytes.fromhex(hexString))
                        break
    
    print("Finished.")
    return 0
    

#########################################################################################################

imageLocation = 'trucy1.png'
reducedImageLocation = 'reducedImage.png'

targetNumColors = 16
reducedNumColors = 0 #initialize variable

numColors = countColors(imageLocation)
print("Number of colors =", numColors)

if (numColors > 256) & (targetNumColors < numColors):
    reducedNumColors = reduceColors(imageLocation, reducedImageLocation, targetNumColors)
else:
    print("No color reduction happened.")
    reducedImageLocation = imageLocation #so reducedImageLocation and reducedNumColors can be used regardless
    reducedNumColors = numColors

#######################################################################################

#random note: image needs to be 4:3 to be properly resized
#file should be 0xC204 bytes long
#confirm the header is correct
#header is followed by 0x200 palette bytes representing 0x100 different colors, at most
#but it probably won't be completely filled
#then there are 0xC000 pixel bytes, each byte containing a palette index from 0x0 to 0xFF
#the main issue here is the ordering of the pixels, it's in the order of the 768 8x8 tiles

if reducedNumColors > 256: #if there are still more than 256 colors after reduction
    print("error: more than 256 colors even after reduction")

else: #if the number of colors is in a good range (1-256)
    binFileName = 'convertedImage.bin'

    binFile = open(binFileName, "wb")

    writeHeaderData(binFile)
    colorList = writePaletteData(binFile, reducedImageLocation)
    writePixelData(binFile, reducedImageLocation, colorList)

    binFile.close()

