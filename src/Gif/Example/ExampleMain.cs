using System;
using System.Drawing;
using System.Drawing.Imaging;
using Gif.Components;

namespace Example
{
	class ExampleMain
	{
		[STAThread]
		static void Main(string[] args)
		{
			/* create Gif */
			//you should replace filepath
//			String [] imageFilePaths = new String[]{"D:\\0.bmp","D:\\2.bmp","D:\\3.bmp","D:\\4.bmp","D:\\5.bmp","D:\\6.bmp","D:\\7.bmp","D:\\8.bmp","D:\\9.bmp","D:\\10.bmp","D:\\11.bmp","D:\\12.bmp","D:\\13.bmp","D:\\14.bmp","D:\\15.bmp","D:\\16.bmp","D:\\17.bmp","D:\\18.bmp","D:\\19.bmp","D:\\20.bmp","D:\\21.bmp","D:\\22.bmp","D:\\23.bmp","D:\\24.bmp","D:\\25.bmp","D:\\26.bmp","D:\\27.bmp","D:\\28.bmp","D:\\29.bmp","D:\\30.bmp","D:\\31.bmp","D:\\32.bmp","D:\\33.bmp","D:\\34.bmp","D:\\35.bmp","D:\\36.bmp","D:\\37.bmp","D:\\38.bmp"};
            String[] imageFilePaths = new String[] { "D:\\0.bmp", "D:\\1.bmp", "D:\\2.bmp", "D:\\3.bmp", "D:\\4.bmp", "D:\\5.bmp" };
            String outputFilePath = "D:\\test.gif";
			AnimatedGifEncoder e = new AnimatedGifEncoder();
			e.Start( outputFilePath );
			e.SetDelay(200);
			//-1:no repeat,0:always repeat
			e.SetRepeat(0);
			for (int i = 0, count = imageFilePaths.Length; i < count; i++ ) 
			{
				e.AddFrame( Image.FromFile( imageFilePaths[i] ) );
			}
			e.Finish();
			/* extract Gif */
			string outputPath = "D:\\";
			GifDecoder gifDecoder = new GifDecoder();
			gifDecoder.Read( "C:\\test.gif" );
			for ( int i = 0, count = gifDecoder.GetFrameCount(); i < count; i++ ) 
			{
				Image frame = gifDecoder.GetFrame( i );  // frame i
				frame.Save( outputPath + Guid.NewGuid().ToString() + ".png", ImageFormat.Png );
			}
		}
	}
}
