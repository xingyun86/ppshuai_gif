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

namespace GifMgr
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
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

        //选择PNG图片路径
        private void buttonSelectPNGPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "请选择文件路径";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                this.textBox_SelectPNGPath.Text = dialog.SelectedPath;
            }
        }
        //生成GIF动画
        private void buttonMakeGIF_Click(object sender, EventArgs e)
        {
            decimal decDelayTimes = numericUpDown_DelayTimes.Value;
            /* create Gif */
            //you should replace filepath
            List<String> imageFileList = new List<String>();
            if (this.textBox_SelectPNGPath.Text.Length <= 0)
            {
                MessageBox.Show("未选择用于生成GIF的PNG图片原路径!请选择【选择PNG路径】");
                return;
            }
            DirectoryInfo TheFolder = new DirectoryInfo(this.textBox_SelectPNGPath.Text);
            //遍历文件夹
            //foreach (DirectoryInfo NextFolder in TheFolder.GetDirectories())
            //    this.listBox1.Items.Add(NextFolder.Name);
            //遍历文件
            foreach (FileInfo NextFile in TheFolder.GetFiles())
            {
                if (NextFile.Name.ToLower().EndsWith(".bmp") ||
                    NextFile.Name.ToLower().EndsWith(".jpg") ||
                    NextFile.Name.ToLower().EndsWith(".jpeg") ||
                    NextFile.Name.ToLower().EndsWith(".png") ||
                    NextFile.Name.ToLower().EndsWith(".ico") ||
                    NextFile.Name.ToLower().EndsWith(".icon") ||
                    NextFile.Name.ToLower().EndsWith(".tiff") ||
                    NextFile.Name.ToLower().EndsWith(".svg"))
                {
                    imageFileList.Add(NextFile.FullName);
                }
            }

            String outputFilePath = this.textBox_SelectPNGPath.Text + "\\output.gif";
            AnimatedGifEncoder age = new AnimatedGifEncoder();
            age.Start(outputFilePath);

            age.SetDelay(Decimal.ToInt32(decDelayTimes));
            //-1:no repeat,0:always repeat
            age.SetRepeat(0);
            
            for (int i = 0, count = imageFileList.Count; i < count; i++)
            {
                age.SetSize(Image.FromFile(imageFileList[i]).Size.Width,Image.FromFile(imageFileList[i]).Size.Height);
                age.AddFrame(Image.FromFile(imageFileList[i]));
            }
            age.Finish();

            MessageBox.Show("完成,文件保存在" + outputFilePath + "!");
        }
        //选择GIF路径
        private void buttonSelectGIFPath_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.InitialDirectory = ".\\";//注意这里写路径时要用c:\\而不是c:\
            ofd.Filter = "GIF文件|*.gif|所有文件|*.*";
            ofd.RestoreDirectory = true;
            ofd.FilterIndex = 1;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                this.textBox_SelectGIFPath.Text = ofd.FileName;
            }
        }
        //反转GIF动画
        private void buttonReverseGIF_Click(object sender, EventArgs e)
        {
            decimal decDelayTimes = numericUpDown_DelayTimes.Value;
            string strFileName = this.textBox_SelectGIFPath.Text;
            if (strFileName.Length <= 0)
            {
                MessageBox.Show("未选择要反序的文件!请选择【选择GIF文件】");
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

            MessageBox.Show("反序完成,文件保存在" + outputFilePath + "目录!");
        }

        //选择解压GIF为PNG的保存路径
        private void buttonSelectUnpackPNGPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "请选择文件路径";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                this.textBox_SelectPNGSavePath.Text = dialog.SelectedPath;
            }
        }

        //解压GIF为PNG
        private void buttonUnpackGIF_Click(object sender, EventArgs e)
        {
            string strFileName = this.textBox_SelectGIFPath.Text;
            if (strFileName.Length <= 0)
            {
                MessageBox.Show("未选择要解压PNG的GIF文件!请选择【选择GIF路径】");
                return;
            }
            string strFilePath = this.textBox_SelectPNGSavePath.Text;
            if (strFilePath.Length <= 0)
            {
                MessageBox.Show("未选择要保存PNG的文件路径!请选择【保存PNG路径】");
                return;
            }
            /* extract Gif */

            List<string> strList = GetFrames(strFileName, strFilePath);

            MessageBox.Show("解压GIF完成,文件保存在" + strFilePath + "目录!");
        }
        //帮助说明
        private void buttonHelpInstrument_Click(object sender, EventArgs e)
        {
            MessageBox.Show(this, "\t\t\t【使用说明】\r\n" +
                "(1).生成 【选择PNG路径】->生成GIF=【PNG路径\\output.gif】\r\n" +
                "(2).解压 【选择GIF路径】->【保存PNG路径】->解压PNG=【保存PNG路径】\r\n" +
                "(3).反转 【选择GIF路径】->生成GIF=【选择GIF路径.GIF】\r\n" +
                "延迟间隔范围=【1,4294967295】");
        }
    }
}
