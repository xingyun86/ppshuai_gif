using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Gif.Components;
using System.IO;

namespace MakeGif
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void buttonSelectGifPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            dialog.Description = "请选择文件路径";
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                this.textBox_SelectGifPath.Text = dialog.SelectedPath;
            }
        }

        private void buttonMakeGif_Click(object sender, EventArgs e)
        {
            /* create Gif */
            //you should replace filepath
            List<String> imageFileList = new List<String>();
            if (this.textBox_SelectGifPath.Text.Length <= 0)
            {
                MessageBox.Show("未选择用于生成GIF的图片原路径!");
                return;
            }
            DirectoryInfo TheFolder = new DirectoryInfo(this.textBox_SelectGifPath.Text);
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

            String outputFilePath = this.textBox_SelectGifPath.Text + "\\output.gif";
            AnimatedGifEncoder age = new AnimatedGifEncoder();
            age.Start(outputFilePath);
            age.SetDelay(200);
            //-1:no repeat,0:always repeat
            age.SetRepeat(0);
            for (int i = 0, count = imageFileList.Count; i < count; i++)
            {
                age.AddFrame(Image.FromFile(imageFileList[i]));
            }
            age.Finish();

            MessageBox.Show("完成,文件保存在" + outputFilePath);
        }
    }
}
