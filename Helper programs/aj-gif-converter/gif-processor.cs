using System.Security.Cryptography.X509Certificates;

public static class GifProcessor
{
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

        List<int> durations = getDurations(gif, numberOfFrames);

        for (int i = 0; i < numberOfFrames; i++)
        {
            parameters[i].duration = durations[i];
            parameters[i].objs = getObjInfo(frames[i]);
        }

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
        //are multiples of 16, if not already
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        if (maxBounded.Width % 16 != 0)
        {
            x = maxBounded.Left - (16 - maxBounded.Width % 16);
            width = maxBounded.Width + (16 - maxBounded.Width % 16);
        }
        if (maxBounded.Height % 16 != 0)
        {
            y = maxBounded.Top - (16 - maxBounded.Height % 16);
            height = maxBounded.Height + (16 - maxBounded.Height % 16);
        }

        Rectangle cropRect = new Rectangle(x, y, width, height);

        //guarantee the width and height are multiples of 16
        Debug.Assert(cropRect.Width % 16 == 0);
        Debug.Assert(cropRect.Height % 16 == 0);

        //at this point, maxBounded is the rectangle to crop to
        for (int i = 0; i < frames.Count; i++)
        {
            frames[i] = ((Bitmap) frames[i]).Clone(cropRect, 
                PixelFormat.Format16bppArgb1555);
        }

        return frames;
    }


    private static Rectangle getBoundingBox(Image frame)
    {
        BitmapData data = ((Bitmap) frame).LockBits(new Rectangle(0, 0,
            frame.Width, frame.Height), ImageLockMode.ReadOnly,
            PixelFormat.Format16bppArgb1555);

        try
        {
            byte[] buffer = new byte[data.Height * data.Stride];
            Marshal.Copy(data.Scan0, buffer, 0, buffer.Length);
            
            short bgColor = Marshal.ReadInt16(data.Scan0);

            int xMin = int.MaxValue;
            int xMax = 0;
            int yMin = int.MaxValue;
            int yMax = 0;
            
            for (int y = 0; y < data.Height; y++)
            {
                for (int x = 0; x < data.Width; x++)
                {
                    short currentColor = buffer[y * data.Stride + 2 * x];
                    if (currentColor != bgColor)
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
        finally
        {
            //free memory
            if (data != null)
                ((Bitmap) frame).UnlockBits(data);
        }
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
        List<List<UInt16>> objColors = getUniqueColors(objCells);

        List<objInfo> objs = new List<objInfo>();
        
        for (int i = 0; i < objCells.Count; i++)
            objs.Add(new objInfo{
                cell = objCells[i], colors = objColors[i]});

        return objs;
    }


    private static List<Rectangle> splitFrame(Image frame)
    {
        List<Rectangle> cells = new List<Rectangle>();



        /*
        for obj in range(numObjs[0] * numObjs[1]):
        #topmost pixel
        startX = (obj % numObjs[0]) * objSize
        #leftmost pixel
        startY = (obj - (startX // objSize)) // numObjs[0] * objSize
        
        #leftmost, topmost, rightmost, bottommost positions for crop
        cellCoords = (startX, startY, startX + objSize, startY + objSize)

        cell = anim.crop(cellCoords)
        cell.save(f'{path}\\obj{obj},x{startX},y{startY}.png')
        */

        return cells;
    }


    private static List<List<UInt16>> getUniqueColors(List<Rectangle> cells)
    {
        List<List<UInt16>> colorsList = new List<List<UInt16>>();


        return colorsList;
    }
}



