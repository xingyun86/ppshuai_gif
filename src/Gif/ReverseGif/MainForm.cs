using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Gif.Components;
using System.IO;

namespace ReverseGif
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void buttonSelectGif_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.InitialDirectory = ".\\";//注意这里写路径时要用c:\\而不是c:\
            ofd.Filter = "GIF文件|*.gif|所有文件|*.*";
            ofd.RestoreDirectory = true;
            ofd.FilterIndex = 1;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                this.textBox1.Text = ofd.FileName;
            }
        }

        private void buttonReverseGif_Click(object sender, EventArgs e)
        {
            string strFileName = this.textBox1.Text;
            if (strFileName.Length <= 0)
            {
                MessageBox.Show("未选择要反序的文件!");
                return;
            }
            /* extract Gif */
            
            string outputPath = Path.GetTempPath();
            List<string> strList = GetFrames(strFileName, outputPath);
            GifDecoder gifDecoder = new GifDecoder();
            gifDecoder.Read(strFileName);
//             int count = gifDecoder.GetFrameCount();
//             List<string> strList = new List<string>();
//             for (int i = 0; i < count; i++)
//             {
//                 Image frame = gifDecoder.GetFrame(i);  // frame i
//                 strList[i] = outputPath + Guid.NewGuid().ToString() + ".png";
//                 frame.Save(strList[i], ImageFormat.Png);
//                 frame.Dispose();
//             }
            strList.Reverse();
            String outputFilePath = strFileName + ".gif";
            AnimatedGifEncoder age = new AnimatedGifEncoder();
            age.Start(outputFilePath);
            age.SetDelay(gifDecoder.GetDelay(0));
            //-1:no repeat,0:always repeat
            age.SetRepeat(0);
            for (int i = 0; i < strList.Count; i++)
            {
                age.AddFrame(Image.FromFile(strList[i]));
            }
            age.Finish();

            MessageBox.Show("反序完成,文件保存在" + outputFilePath);
        }


        //解码GIF图片
        public List<string> GetFrames(string pPath, string pSavedPath)
        {
            string path = null;
            Image gif = Image.FromFile(pPath);
            FrameDimension fd = new FrameDimension(gif.FrameDimensionsList[0]);

            //获取帧数(gif图片可能包含多帧，其它格式图片一般仅一帧)
            int count = gif.GetFrameCount(fd);
            List<string> gifList = new List<string>();
            //以Jpeg格式保存各帧

            for (int i = 0; i < count; i++)
            {
                path = pSavedPath + "\\frame_" + i + ".png";
                gif.SelectActiveFrame(fd, i);
                gif.Save(path, ImageFormat.Png);
                gifList.Add(path);
            }
            return gifList;
        }
    }
}
