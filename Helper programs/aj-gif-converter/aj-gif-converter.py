from PIL import Image, ImageChops
import os

#crop .gif to minimize blank space
def trim(gif):
    #bg is an image with the color of the top leftmost pixel of .gif
    bg = Image.new(gif.mode, gif.size, gif.getpixel((0,0)))
    diff = ImageChops.difference(gif, bg)
    #2 is scale, -100 offset; (diff + diff) / 2 - 100
    #subtracting 100 saturates colors under (100, 100, 100) to 0
    #removing noise in detecting blank space
    diff = ImageChops.add(diff, diff, 2.0, -100)
    bbox = diff.getbbox()
    if bbox is not None: #if boundary box exists, return it
        return bbox
    return (0, 0, 0, 0) #an empty boundary box

#Procedure:
#Iterate through each frame in the .gif
#Make the smallest possible rectangle that contains the whole .gif
#Expand the rectangle so its dimensions are multiples of 16
#For each frame:
#Divide the rectangle into 16 by 16 cells
#Collect information to enable calculating optimal palettes
#Since the whole animation will use the same palettes
#And cells will be divided up regardless of the colors inside
#Try to have at most four palettes

anim = Image.open("./test.gif")
#length of one side of the square, all OBJs will be square
objSize = 32 #32 by 32 pixel OBJs seems a good choice

#crop each frame of the .gif
#then crop entire .gif by the largest boundary box of the frames
largestBbox = (0, 0, 0, 0)
largestBboxArea = 0

#find largest boundary box by area among the frames
for frame in range(0, anim.n_frames):
    anim.seek(frame)
    bbox = trim(anim)

    bboxArea = (bbox[2] - bbox[0]) * (bbox[3] - bbox[1]) #area of rectangle

    if (bboxArea > largestBboxArea):
        largestBbox = list(bbox)

dims = [0, 0] #initialize list for width, height with size 2
#all frames have same size now
dims[0], dims[1] = largestBbox[2] - largestBbox[0], \
    largestBbox[3] - largestBbox[1]

numObjs = [0, 0] #initialize list with size 2, width number, height number

for dim in range(2): #dims[0], dims[1]
    if dims[dim] % objSize != 0: #if dimension is not a multiple of 16 pixels
        #make it the next multiple of 16
        dims[dim] = dims[dim] + (objSize - dims[dim] % objSize)
    
    assert(dims[dim] % objSize == 0)

    #round just to cast to int, not actually to round
    numObjs[dim] = round(dims[dim] / objSize) #number of objs that fit in this dim

#adjust boundary box with this updated width and height
#it won't be centered around sprite anymore, but it shouldn't matter
largestBbox[2] = largestBbox[0] + dims[0]
largestBbox[3] = largestBbox[1] + dims[1]

#and use this new boundary box to crop each frame of the .gif
frameList = [] #initialize empty list to hold the frames

for frame in range(0, anim.n_frames):
    anim.seek(frame) #go to relevant frame in .gif
    croppedFrame = anim.crop(largestBbox)
    frameList.append(croppedFrame)

#main action of code, iterating through each static frame
for n, frame in enumerate(frameList):
    path = f'{os.getcwd()}\\frame{n}' #make folder for frame
    if not (os.path.exists(path)): #if it doesn't exist yet
        os.mkdir(path)

    #now divide into numObjs[0] * numObjs[1] 16 by 16 cells
    for obj in range(numObjs[0] * numObjs[1]):
        #topmost pixel
        startX = (obj % numObjs[0]) * objSize
        #leftmost pixel
        startY = (obj - (startX // objSize)) // numObjs[0] * objSize
        
        #leftmost, topmost, rightmost, bottommost positions for crop
        cellCoords = (startX, startY, startX + objSize, startY + objSize)

        cell = anim.crop(cellCoords)
        cell.save(f'{path}\\obj{obj},x{startX},y{startY}.png')