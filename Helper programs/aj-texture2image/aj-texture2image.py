from PIL import Image as im
from PIL import ImageDraw as imDraw

fileName = "369" #or whatever the name of the .bin file is
fileLoc = fileName + ".bin"
bpp4 = True
#whether it's 4 or 8bpp

#adjust this as needed to get the right size for the resulting .png
#may require some experimentation
#so check likely factors of the image size, as shown in the header
width = 128
height = 32

file = open(fileLoc, "rb") #open binary file
headerLength = 20
header = list(bytearray(file.read(20))) #read the first 0x14 bytes, the header, converting to decimal

#offset where the image data itself starts
imageOffset = header[4]

#number of bytes of image data; read bytes 9 and 8 together as hex and flip endianness
#0 added to string because it reads "00" as "0"
imageLength = int(hex(header[9])[2:] + hex(header[8])[2:] + "0", base = 16)

#offset where palette starts; read bytes 13 and 12 together as hex and flip endianness
paletteOffset = int(hex(header[13])[2:] + hex(header[12])[2:], base = 16)

file.seek(paletteOffset, 0)

paletteData = []

if bpp4:
    paletteData = file.read(32).hex() #read the first palette
else:
    paletteData = file.read(512).hex() #read the entire palette

palette = []
RGB = [0, 0, 0]

for i in range(0, len(paletteData), 4): #step is 4 to read two bytes at a time
    palette.append(paletteData[i:i+4])

for i in range(0, len(palette)): #step through each two-byte group of the palette
    palette[i] = palette[i][2:] + palette[i][:-2] #reverse endianness of the two-byte groups
    palette[i] = bin(int(palette[i], 16))[2:] #convert to binary

    while len(palette[i]) < 15: #make sure each item in the list is 15 digits long
        palette[i] = "0" + palette[i]

    for color in range(0, 3): #cycle through blue, green, red
        RGB[color] = palette[i][15-5*(color+1):(15-5*(color+1))+5] #divide it into groups of five bits in reverse
        RGB[color] = int(RGB[color], 2)
        RGB[color] = round(RGB[color]*255/31) #change the values to out of 255 instead of out of 31

    palette[i] = tuple(RGB)

if bpp4:
    pixelNybbles = [(paletteOffset - headerLength) * 2] #set size to number of nybbles of pixel data
else:
    pixelNybbles = [paletteOffset - headerLength] #half as many pixels in 8bpp as compared to 4bpp


for i in range(headerLength, paletteOffset - 1): #iterate through the pixel data
    file.seek(i, 0) #set cursor to current byte

    if bpp4:
        pixelNybbles.append(int(file.read(1).hex()[:-1], 16)) #take the higher nybble and convert to decimal
        pixelNybbles.append(int(file.read(1).hex()[1:], 16)) #take the lower nybble and convert to decimal
    else:
        pixelNybbles.append(int(file.read(1).hex(), 16)) #take one byte, not a nybble

pixelNybbles[0] = 0

print(len(pixelNybbles))

file.close()


#create image
image = im.new(size=[width, height], mode="RGB")
draw = imDraw.Draw(image)

pixelCount = 0

#draw image
for y in range (0, image.height):
    for x in range (0, image.width):
        if (pixelCount < len(pixelNybbles) and pixelNybbles[pixelCount] < len(palette)):
            draw.point((x, y), palette[pixelNybbles[pixelCount]]) #each pixel corresponds to a nybble
        
            pixelCount += 1
        

image.show()
image.save(fp=fileName + ".png", format="png")

#the process:
#read data from header into variables
#read (first) palette into a tuple
#use Pillow's ImageDraw.point function to draw pixels corresponding to each nybble
#the issues are whether to draw from left to right or in tiles,
#and also what the first four bytes of the header represent