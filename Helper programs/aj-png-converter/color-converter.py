def convertBGRA5551ToRGB(colorString):
    colorString = colorString[2:] + colorString[:-2] #reverse endianness of the two-byte groups
    colorString = bin(int(colorString, 16))[2:] #convert to binary

    while len(colorString) < 15: #make sure each item in the list is 15 digits long
        colorString = "0" + colorString

    RGBList = [0, 0, 0]

    for color in range(0, 3): #cycle through blue, green, red
        RGBList[color] = colorString[15-5*(color+1):(15-5*(color+1))+5] #divide it into groups of five bits in reverse
        RGBList[color] = int(RGBList[color], 2)
        RGBList[color] = round(RGBList[color]*255/31) #change the values to out of 255 instead of out of 31

    return RGBList
#-------------------------------------------------------------------
def convertRGBToBGRA5551(RGBATuple):
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
#--------------------------------------------------------------------------
#true if the inputted color(s) is RGB and should be converted to BGRA5551
#false if the inputted color(s) is BGRA5551 and should be converted to RGB
isRGB = False

colors = ["FF7F", "0000"]

if (isRGB):
    #alpha is assumed to be 0, could be changed if needed though
    for color in colors:
        print(f'{color} converts to {convertRGBToBGRA5551(color)}')
else:
    #the two-byte string should be little endian, as in the ROM
    for color in colors:
        print(f'{color} converts to {convertBGRA5551ToRGB(color)}')