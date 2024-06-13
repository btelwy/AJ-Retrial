using System.Data;
using System.Runtime;
using System.Security.Cryptography.X509Certificates;

namespace GifProcessor;

public static class GifProcessor
{
    public static class Globals
    {
        //the background color of the .gif
        //as defined by top-left pixel
        public static UInt16 bgColor;

        //OBJs will start as 8 by 8 squares
        //before later being coalesced into larger squares/rectangles
        public static int objSize = 8;

        //cropped frame width divided by 8
        public static int numObjsWidth;

        //cropped frame height divided by 8
        public static int numObjsHeight;
    }
    
    public struct objInfo
    {
        public Rectangle cell;
        public List<UInt16> colors;
    }
    
    public struct frameInfo
    {
        public int duration;
        public List<objInfo> objs;
    }

    public static (List<Image>, frameInfo[]) getFrames(Image gif)
    {
        int numberOfFrames = gif.GetFrameCount(FrameDimension.Time);

        List<Image> frames = new List<Image>(numberOfFrames);
        frameInfo[] parameters = new frameInfo[numberOfFrames];

        for (int i = 0; i < numberOfFrames; i++)
        {
            gif.SelectActiveFrame(FrameDimension.Time, i);
            frames.Add((Image) gif.Clone());
        }

        //crop frames all to the same size, cutting down blank space
        frames = cropFrames(frames);

        //get how many 8 by 8 OBJs fit horizontally and vertically
        //inside one frame
        Globals.numObjsWidth = frames[0].Width / Globals.objSize;
        Globals.numObjsHeight = frames[0].Height / Globals.objSize;

        List<int> durations = getDurations(gif, numberOfFrames);

        for (int i = 0; i < numberOfFrames; i++)
        {
            parameters[i].duration = durations[i];
            parameters[i].objs = getObjInfo(frames[i]);
        }

        int count = 0;
        foreach (objInfo info in parameters[0].objs)
        {
            Console.Write(count + ": " + info.cell.X + "," + info.cell.Y + " -- ");
            Console.WriteLine(info.cell.Width + "," + info.cell.Height);
            count++;
        }
        Console.WriteLine("Number of OBJs: " + parameters[0].objs.Count);

        return (frames, parameters);
    }

    private static List<Image> cropFrames(List<Image> frames)
    {
        int maxArea = int.MinValue;
        Rectangle maxBounded = new Rectangle(0, 0, 1, 1);

        foreach (Image frame in frames)
        {
            Rectangle bBox = getBoundingBox(frame);

            int boundedArea = bBox.Width * bBox.Height;
            if (boundedArea > maxArea)
            {
                maxArea = boundedArea;
                maxBounded = bBox;
            }
        }

        //now adjust boundary box so that it's dimensions
        //are multiples of 8, if not already
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        if (maxBounded.Width % Globals.objSize != 0)
        {
            x = maxBounded.Left - (Globals.objSize - maxBounded.Width % Globals.objSize);
            width = maxBounded.Width + (Globals.objSize - maxBounded.Width % Globals.objSize);
        }
        if (maxBounded.Height % Globals.objSize != 0)
        {
            y = maxBounded.Top - (Globals.objSize - maxBounded.Height % Globals.objSize);
            height = maxBounded.Height + (Globals.objSize - maxBounded.Height % Globals.objSize);
        }

        Rectangle cropRect = new Rectangle(x, y, width, height);

        //guarantee the width and height are multiples of 8
        Debug.Assert(cropRect.Width % Globals.objSize == 0);
        Debug.Assert(cropRect.Height % Globals.objSize == 0);

        //at this point, maxBounded is the rectangle to crop to
        for (int i = 0; i < frames.Count; i++)
            frames[i] = ((Bitmap) frames[i]).Clone(cropRect, 
                PixelFormat.Format16bppArgb1555);

        return frames;
    }


    private static Rectangle getBoundingBox(Image frame)
    {
        Rectangle frameRect = new Rectangle(0, 0, frame.Width,
            frame.Height);
        
        //a complete, non-unique list of all colors in the image
        List<UInt16> colors = getColors(frame, frameRect, false);
        
        //the background color is considered the first color,
        //the color of the pixel at the top left corner
        Globals.bgColor = colors[0];

        int xMin = int.MaxValue;
        int xMax = 0;
        int yMin = int.MaxValue;
        int yMax = 0;
            
        for (int y = 0; y < frame.Height; y++)
        {
            for (int x = 0; x < frame.Width; x++)
            {
                //colors is a list ordered from left to right,
                //up to down
                //so the current color can be found through multiplying

                UInt16 currentColor = colors[y * frame.Width + x];
                if (currentColor != Globals.bgColor)
                {
                    if (x < xMin) xMin = x;
                    if (x > xMax) xMax = x;
                    if (y < yMin) yMin = y;
                    if (y > yMax) yMax = y;
                }
            }
        }

        if (xMax < xMin || yMax < yMin)
        {
            //If image is empty, return null rectangle
            return new Rectangle(0, 0, 1, 1);
        }

        //the boundary box for this frame
        return Rectangle.FromLTRB(xMin, yMin, xMax, yMax);
    }


    private static List<int> getDurations(Image gif, int frameCount)
    {
        List<int> durations = new List<int>();

        for (int byteOffset = 0; byteOffset < frameCount; byteOffset++)
        {
            //delay is labeled in centiseconds
            Int32 duration = BitConverter.ToInt32(
                gif.GetPropertyItem(0x5100).Value, 4 * byteOffset);

            //minimum delay allowed in .gif format is 10 cs
            //duration = (duration < 10 ? 10 : duration);

            durations.Add(duration);
        }

        return durations;
    }


    private static List<objInfo> getObjInfo(Image frame)
    {
        List<Rectangle> objCells = splitFrame(frame);
        objCells = optimizeCells(objCells, frame);

        //get the unique colors in each OBJ; though a little inefficient
        List<List<UInt16>> objColors = new List<List<UInt16>>();
        foreach (Rectangle cell in objCells)
            objColors.Add(getColors(frame, cell, true));

        //create list of objInfo struct with acquired data
        //and return that list
        List<objInfo> objs = new List<objInfo>();

        for (int i = 0; i < objCells.Count; i++)
            objs.Add(new objInfo{
                cell = objCells[i], colors = objColors[i]});

        return objs;
    }


    private static List<Rectangle> splitFrame(Image frame)
    {
        Bitmap bmp = (Bitmap) frame;
                
        //a list of tuples of (rectangle and color)
        //where the colors are the unique colors within the cell
        List<(Rectangle, List<UInt16>)> cellData = new List<(Rectangle, List<UInt16>)>();

        int startX;
        int startY;
        int objOffset;

        //first, divide frame into 8 by 8 cells
        for (int obj = 0; obj < Globals.numObjsWidth * Globals.numObjsHeight; obj++)
        {
            //leftmost pixel
            startX = (obj % Globals.numObjsWidth) * Globals.objSize;
            //OBJ index at beginning of current row
            objOffset = obj - (startX / Globals.objSize);
            //topmost pixel
            startY = objOffset / Globals.numObjsWidth * Globals.objSize;

            Rectangle cell = new Rectangle(startX, startY, Globals.objSize, Globals.objSize);
            
            //get a list of all unique colors in the cell
            List<UInt16> colors = getColors(frame, cell, true);

            cellData.Add((cell, colors));
        }

        //now there are 8 by 8 tiles
        //and each tile has associated with it a list of colors of each pixel
        //in other words, cellData is a list of (rectangle, colors) tuples
        List<Rectangle> coalescedObjs = coalesceObjs(cellData);
        return coalescedObjs;
    }


    private static List<UInt16> getColors(Image frame, Rectangle obj, bool unique)
    {
        Bitmap bmp = (Bitmap) frame;
        BitmapData bmpData = bmp.LockBits(obj, ImageLockMode.ReadOnly,
            PixelFormat.Format16bppArgb1555);

        List<UInt16> colors = new List<UInt16>();

        try
        {
            //copy all data within rectangle to buffer
            byte[] buffer = new byte[bmpData.Height * bmpData.Stride];
            Marshal.Copy(bmpData.Scan0, buffer, 0, buffer.Length);

            UInt16 color = 0;

            for (int y = 0; y < bmpData.Height; y++)
            {
                for (int x = 0; x < bmpData.Width; x++)
                {
                    //if color is not already in list,
                    //or if "unique" is set to false,
                    //add the current color
                    color = buffer[y * bmpData.Stride + 2 * x];
                    if (!colors.Contains(color) || !unique)
                        colors.Add(color);
                }
            }
        }
        finally
        {
            //free memory
            if (bmpData != null)
                bmp.UnlockBits(bmpData);
        }

        return colors;
    }


    private static List<Rectangle> coalesceObjs(List<(Rectangle, List<UInt16>)> cellData)
    {
        //holds the indices of OBJs that are completely blank
        List<int> blankObjs = new List<int>();

        //first, identify blank OBJs
        for (int obj = 0; obj < cellData.Count; obj++)
        {
            //a list of the unique colors in the 8 by 8 OBJ
            List<UInt16> cellColors = cellData[obj].Item2;

            //if the OBJ is entirely background color, no sprite
            //(i.e., bgColor is only unique color),
            //there shouldn't be an OBJ there, since it's blank
            if (cellColors.Count == 1 && cellColors[0] == Globals.bgColor)
                blankObjs.Add(obj);
        }
        
        //Now, do another pass through the OBJs to coalesce them
        //under these conditions:
        //That the resulting OBJ is as large as possible
        //That the resulting OBJ contains no cells already coalesced
        //That the resulting OBJ has fewer than 15 colors

        //dictionary with top left OBJ as key
        //and the OBJ indices of the OBJs coalesced together as value
        Dictionary<int, List<int>> alreadyCoalesced = new Dictionary<int, List<int>>();

        for (int obj = 0; obj < cellData.Count; obj++)
        {
            //if this cell hasn't already been coalesced + isn't blank
            List<int> temp = new List<int>(); //a temp list with one item
            temp.Add(obj);

            //skip this OBJ if it's blank
            if (blankObjs.Contains(obj))
                continue;
            
            //else,
            bool possible;

            //"scale" is the amount to multiply OBJ size by;
            //specifically, by 1 shifted left by the scale
            //starts at 64 by 64 and works downward
            //finding the biggest square or rectangle possible
            //in DS terminology, it is called "size"
            for (int scale = 3; scale >= 0; scale--)
            {
                var tuple = checkAdjacent(blankObjs,
                    alreadyCoalesced, obj, scale, cellData);
                alreadyCoalesced = tuple.Item1;
                possible = tuple.Item2;

                //exit loop early if possible, since work is done
                if (possible)
                    break;

                //if not possible and at the end of the loop
                //this OBJ will not be coalesced
                //so the only OBJ associated with it is itself
                if (scale == 0)
                    alreadyCoalesced.Add(obj, temp);
            }
        }

        //now alreadyCoalesced contains each non-blank OBJ once in its lists
        //and from this data Rectangle instances must be created
        List<Rectangle> objs = new List<Rectangle>();

        int corner;
        int startX;
        int startY;
        int totalObjs;
        int rectWidth = 0;
        int rectHeight = 0;

        foreach (KeyValuePair<int, List<int>> kvp in alreadyCoalesced)
        {
            corner = kvp.Key;
            startX = (corner % Globals.numObjsWidth) * Globals.objSize;
            startY = (corner - (startX / Globals.objSize)) / Globals.numObjsWidth * Globals.objSize;

            totalObjs = kvp.Value.Count;

            if (totalObjs == 1)
            {
                rectWidth = 8;
                rectHeight = 8;
            }
            else
            {
                for (int i = 1; i < totalObjs; i++)
                {
                    if (kvp.Value[i] - kvp.Value[i - 1] != 1)
                    {
                        rectWidth = 8 * i;
                        rectHeight = totalObjs / (rectWidth / 8) * 8;
                        break;
                    }
                }
            }

            objs.Add(Rectangle.FromLTRB(startX, startY,
                startX + rectWidth, startY + rectHeight));
        }

        return objs;
    }


    private static (Dictionary<int, List<int>>, bool)
    checkAdjacent(List<int> blankObjs,
        Dictionary<int, List<int>> alreadyCoalesced, int obj, int scale,
        List<(Rectangle, List<UInt16>)> cellData)
    {
        //first try a square with the given scale
        //then try the two possible rectangles
        
        //get current position in grid, in 8 by 8 squares
        int horizontalPos = obj % Globals.numObjsWidth;
        int verticalPos = (obj - horizontalPos) / Globals.numObjsWidth;

        List<int> involvedObjs = new List<int>();
        bool possible = false;

        //and use that information to see if the square will fit
        //given that coalescing only happens from top left corner
        while (horizontalPos + (1 << scale) < Globals.numObjsWidth &&
            verticalPos + (1 << scale) < Globals.numObjsHeight)
        {
            possible = true;

            //try a square, equal scale along both dimensions
            involvedObjs = tryRectangle(obj, scale, "square");
            if (isPossible(obj, involvedObjs, blankObjs,
                alreadyCoalesced, cellData))
                break;
            
            //for scale == 0 and scale == 1, horizontal mode uses
            //width * 2, so check if that will fit
            if (scale > 1 ||
                horizontalPos + 2 * (1 << scale) < Globals.numObjsWidth)
            {
                //try a horizontal rectangle
                involvedObjs = tryRectangle(obj, scale, "horizontal");
                if (isPossible(obj, involvedObjs, blankObjs,
                    alreadyCoalesced, cellData))
                    break;
            }
            //for scale == 0 and scale == 1, vertical mode uses
            //height * 2, so check if that will fit
            if (scale > 1 ||
                verticalPos + 2 * (1 << scale) < Globals.numObjsHeight)
            {
                //try a vertical rectangle
                involvedObjs = tryRectangle(obj, scale, "vertical");
                if (isPossible(obj, involvedObjs, blankObjs,
                    alreadyCoalesced, cellData))
                    break;
            }

            //at this point, nothing at this scale worked
            possible = false;
            break;
        }

        Dictionary<int, List<int>> coalescedObjs = alreadyCoalesced;

        if (possible) //if one of the shapes worked out
        {
            //add an entry to the dictionary
            //with key "obj" and value the OBJs coalesced with it
            coalescedObjs.Add(obj, involvedObjs);
        }

        //if not possible, leave dictionary unchanged

        return (coalescedObjs, possible);
    }


    private static bool containsAlreadyCoalesced(List<int> targets, Dictionary<int, List<int>> dict)
    {
        bool contains = false;

        //checks if the target index is contained within any of the
        //lists that are the values in the dictionary
        foreach (KeyValuePair<int, List<int>> kvp in dict)
        {
            foreach (int target in targets)
            {
                if (kvp.Value.Contains(target))
                    contains = true;
            }
        }

        return contains;
    }

    
    private static List<int> tryRectangle(int obj, int scale, string mode)
    {
        List<int> involvedObjs = new List<int>();

        int bitShiftedScale = 1 << scale;
        int bitShiftedScaleX = 0;
        int bitShiftedScaleY = 0;

        if (mode.Equals("square"))
        {
            //same proportions regardless of scale
            //scale == 0: 8 by 8
            //scale == 1: 16 by 16
            //scale == 2: 32 by 32
            //scale == 3: 64 by 64
            bitShiftedScaleX = bitShiftedScale;
            bitShiftedScaleY = bitShiftedScale;
        }

        else if (mode.Equals("horizontal"))
        {
            switch(scale)
            {
                case 0: //16 by 8
                bitShiftedScaleX = 2 * bitShiftedScale;
                bitShiftedScaleY = bitShiftedScale;
                break;

                case 1: //32 by 8
                bitShiftedScaleX = 2 * bitShiftedScale;
                bitShiftedScaleY = bitShiftedScale / 2;
                break;

                case 2: //32 by 16
                bitShiftedScaleX = bitShiftedScale;
                bitShiftedScaleY = bitShiftedScale / 2;
                break;

                case 3: //64 by 32
                bitShiftedScaleX = bitShiftedScale;
                bitShiftedScaleY = bitShiftedScale / 2;
                break;
            }
        }

        else if (mode.Equals("vertical"))
        {
            switch(scale)
            {
                case 0: //8 by 16
                bitShiftedScaleX = bitShiftedScale;
                bitShiftedScaleY = 2 * bitShiftedScale;
                break;

                case 1: //8 by 32
                bitShiftedScaleX = bitShiftedScale / 2;
                bitShiftedScaleY = 2 * bitShiftedScale;
                break;

                case 2: //16 by 32
                bitShiftedScaleX = bitShiftedScale / 2;
                bitShiftedScaleY = bitShiftedScale;
                break;

                case 3: //32 by 64
                bitShiftedScaleX = bitShiftedScale / 2;
                bitShiftedScaleY = bitShiftedScale;
                break;
            }
        }

        else
            Debug.Assert(0 == 1, "Mode must be \"square\", \"vertical\", or \"horizontal\"");

        int currentObj;

        //if "square" or "horizontal"
        for (int i = 0; i < bitShiftedScaleY; i++)
        {
            //move down i squares
            currentObj = obj + (i * Globals.numObjsWidth);
            involvedObjs.Add(currentObj);

            //move right j squares
            for (int j = 1; j < bitShiftedScaleX; j++)
                involvedObjs.Add(currentObj + j);
        }

        return involvedObjs;
    }


    private static bool isPossible(int obj, List<int> involvedObjs, List<int> blankObjs,
        Dictionary<int, List<int>> alreadyCoalesced,
        List<(Rectangle, List<UInt16>)> cellData)
    {
        //at this point, all the OBJs in the square
        //are listed in involvedObjs
        //so check if any of them are blank

        //if (Enumerable.Intersect(involvedObjs, blankObjs).Sum() != 0)
        //    return false;

        //and check if any of them are already coalesced
        
        /*if (containsAlreadyCoalesced(involvedObjs, alreadyCoalesced))
            return false;*/

        //first get the unique colors in the current OBJ
        //then add unique colors from all involvedObjs
        List<UInt16> uniqueColors = cellData[obj].Item2;
        foreach (int involvedObj in involvedObjs)
        {
            List<UInt16> newUniqueColors = cellData[involvedObj].Item2;
            uniqueColors = Enumerable.Union(uniqueColors, newUniqueColors).ToList();
        }
        
        //check that resulting OBJ would use fewer than
        //15 unique colors
        if (uniqueColors.Count > 15)
            return false;

        //if this point is reached, the square / rectangle is possible
        return true;
    }


    private static List<Rectangle> optimizeCells(List<Rectangle> cells, Image frame)
    {
        //takes the excessive list of overlapping OBJs produced
        //and finds the optimal ones to keep

        //int threshold = 50;

        List<int> removeList = removeCells(cells);

        //sort removeList so it goes from highest to lowest
        //avoiding index problems with removeAt()
        removeList.Sort();
        removeList.Reverse();

        foreach (int index in removeList)
            cells.RemoveAt(index);

        return cells;
    }

    private static List<int> removeCells(List<Rectangle> cells)
    {
        List<int> overlappedIndices = new();
        List<List<int>> overlappingLists = new();

        for (int index = 0; index < cells.Count; index++)
        {   
            var tuple = isEntirelyOverlapped(index, cells, new List<int>());
            bool overlapped = tuple.Item1;
            List<int> overlappingIndices = tuple.Item2;

            if (overlapped)
            {
                overlappedIndices.Add(index);
                overlappingLists.Add(overlappingIndices);
            }
        }

        List<int> shouldRemove = new();
        List<int> exclude = new();

        for (int i = 0; i < overlappedIndices.Count; i++)
        {
            foreach (int overlap in overlappingLists[i])
            {
                shouldRemove.Add(overlap);
                foreach (int remove in shouldRemove)
                    exclude.Add(remove);
                if (!isEntirelyOverlapped(overlappedIndices[i], cells, exclude).Item1)
                    shouldRemove.Remove(overlap);
            }
        }

        for (int i = 0; i < cells.Count; i++)
        {
            if (shouldRemove.Contains(i))
                continue;
            Console.WriteLine(i);
        }

        return shouldRemove;
    }

    private static (bool, List<int>) isEntirelyOverlapped(int index, List<Rectangle> cells, List<int> exclude)
    {
        bool isOverlapped = false;
        List<int> overlappingList = new List<int>();
        Region remaining = new Region(cells[index]);

        using Graphics g = Graphics.FromImage(Image.FromFile("C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-gif-converter\\test2.gif"));

        for (int i = 0; i < cells.Count && i != index; i++)
        {   
            if (exclude.Contains(i))
                continue;

            if (cells[i].Contains(cells[index]))
            {
                isOverlapped = true;
                overlappingList.Clear();
                overlappingList.Add(i);
                break;
            }

            else if (cells[index].IntersectsWith(cells[i]))
            {
                remaining.Exclude(cells[i]);
                overlappingList.Add(i);
                if (remaining.IsEmpty(g))
                {
                    isOverlapped = true;
                    break;
                }
            }
        }

        return (isOverlapped, overlappingList);
    }
}