global using System;
global using System.Drawing;
global using System.Drawing.Imaging;
global using System.Runtime.InteropServices;
global using System.Collections.Generic;

global using System.Diagnostics;

using System.IO;

class Program
{
    static void Main(string[] args)
    {
        string path = "C:\\Users\\ben\\Desktop\\AJ-Retrial\\Helper programs\\aj-gif-converter\\";
        Directory.SetCurrentDirectory(path);

        Image gif = Image.FromFile("test.gif");
        var returnVals = GifProcessor.getFrames(gif);

        //maybe include a check for whether the .gif is looped:
        //info.IsLooped = BitConverter.ToInt16(image.GetPropertyItem(0x5101).Value, 0) != 1;



        List<Image> frames = returnVals.Item1;
        GifProcessor.frameInfo[] parameters = returnVals.Item2;
        
        for (int i = 0; i < frames.Count; i++)
        {
            frames[i].Save(i + ".png");
        }
    }
}