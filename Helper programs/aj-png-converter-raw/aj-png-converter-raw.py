from PIL import Image
import math

#converts a .png into AJ's raw image format, found in cpac2d.bin/subarc-01
#in this format, there is no palette in the file, and no header
#this program assumes that the raw image format was converted to a .png for editing
#and so the .png is already compatible with the format, not a random .png

#if true, draws pixels in order of tiles; if false, draws linearly, left to right
drawTilewise = False

#put name of file to be converted in here
fileName = "trucy1Reduced"
source = Image.open(fileName + ".png")

#always use palette from subarc-00 at offset 0x1000 (in original subarc-00 file),
#at least for 4bpp images
#this is a 4bpp palette, so has 16 colors
#first color is transparent, so the original last color, '2308', was removed
#always set transparency to 1 when decoding the raw image files to .png
subarc00Palette = ['0000', '1042', '9456', '586B', 'CE10', 'F214', '3519', '4504', 'CA10', '0E19', 'B521',\
           'F825', '5A2E', '9D36', 'FE42', 'C15E']

#alternatively, for option buttons, this is the palette to use:
optionPalette = ['E003', '1863', 'DE7B', 'FF7F', '9D73', '5C6B', '3B63', 'FA5A', 'B84E', '5742', '1532',\
                 'B425', '9321', '3111', 'F008', 'AF00']

#or,
trucyPalette = ['E720', 'A610', '2835', 'EF39', '0D56', 'AB49', '6F62', 'FF7B' '356B', 'D32D', '5736', 'EC14', 'FC4A', '9A3E', 'B220', 'DD24']

palette = subarc00Palette

paletteRGB = []

for color in palette:
    flippedColor = bytearray.fromhex(color)[::-1] #change endianness of two-byte color
    flippedColor = int(flippedColor.hex(), base=16) #convert it to decimal

    #separate the number into R, G, B
    #each color is then between 0 and 31, so convert to a 0-255 scale
    red = round(((flippedColor & 0b11111) << 0) * (255/31))
    green = round(((flippedColor & 0b1111100000) >> 5) * (255/31))
    blue = round(((flippedColor & 0b111110000000000) >> 10) * (255/31))

    paletteRGB.append((red, green, blue))

width, height = source.size #image dimensions
startWidth, startHeight = 0, 0 #the coordinates to start iterating at for each tile
tilesPerRow = width / 8

pixels = source.load() #get a view object of the pixel color values
currentPixel = ()

tempList = []

buffer = []

with open(fileName + "Converted.bin", "wb") as convertedImage: #create .bin file
    #if drawing tile by tile
    if drawTilewise:
        for tiles in range(0, round(width*height/64)):
            startWidth = (tiles % tilesPerRow) * 8
            startHeight = ((tiles - (tiles % tilesPerRow))/tilesPerRow)*8 #lower to nearest start of row, then multiply by tile height
                
            for y in range (0, 8):
                for x in range (0, 8): #iterate through each tile row to row, top to bottom
                    currentPixel = pixels[startWidth+x, startHeight+y]

                    tempList = list(currentPixel)
                    
                    currentPixel = tuple(tempList)

                    #due to rounding and stuff the current pixel won't exactly match anything in the palette
                    #so use a similarity metric to find the closest match: distance in a 3D plane
                    similarity = math.inf
                    match = 0

                    for index, item in enumerate(paletteRGB):
                        distance = (item[0]-currentPixel[0])**2 + (item[1]-currentPixel[1])**2 + \
                            (item[2]-currentPixel[2])**2
                        distance = math.sqrt(distance)

                        if (distance < similarity):
                            similarity = distance

                            match = index

                            #don't know what bug requires this, but each nybble is one greater than should be
                            if (match > 1):
                                match -= 1

                    buffer.append(match)

                    #write one nybble per pixel by waiting until you have two nybbles to write both at once
                    if (len(buffer) == 2):
                        pixel = hex(buffer[1])[2:] + hex(buffer[0])[2:] #concatenate the two nybbles
                        pixel = int.to_bytes(int(pixel, base=16)) #convert into a bytes object
                        
                        convertedImage.write(pixel)

                        buffer = [] #empty buffer

    #if drawing linearly
    else:
        for y in range(height):
            for x in range(width):
                #really should use a function here to increase readability, but too lazy

                currentPixel = pixels[x, y]
                

                #due to rounding and stuff the current pixel won't exactly match anything in the palette
                #so use a similarity metric to find the closest match: distance in a 3D plane
                similarity = math.inf
                match = 0

                for index, item in enumerate(paletteRGB):
                    distance = (item[0]-currentPixel[0])**2 + (item[1]-currentPixel[1])**2 + \
                        (item[2]-currentPixel[2])**2
                    distance = math.sqrt(distance)

                    if (distance < similarity):
                        similarity = distance

                        match = index

                        #don't know what bug requires this, but each nybble is one greater than should be
                        if (match > 1):
                            match -= 1

                buffer.append(match)

                #write one nybble per pixel by waiting until you have two nybbles to write both at once
                if (len(buffer) == 2):
                    pixel = hex(buffer[1])[2:] + hex(buffer[0])[2:] #concatenate the two nybbles
                    pixel = int.to_bytes(int(pixel, base=16)) #convert into a bytes object
                        
                    convertedImage.write(pixel)

                    buffer = [] #empty buffer back to length 0


    print("Finished.")