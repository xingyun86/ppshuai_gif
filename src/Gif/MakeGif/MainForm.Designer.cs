namespace MakeGif
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonMakeGif = new System.Windows.Forms.Button();
            this.buttonSelectGifPath = new System.Windows.Forms.Button();
            this.textBox_SelectGifPath = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // buttonMakeGif
            // 
            this.buttonMakeGif.Location = new System.Drawing.Point(232, 50);
            this.buttonMakeGif.Name = "buttonMakeGif";
            this.buttonMakeGif.Size = new System.Drawing.Size(82, 23);
            this.buttonMakeGif.TabIndex = 5;
            this.buttonMakeGif.Text = "生成GIF动画";
            this.buttonMakeGif.UseVisualStyleBackColor = true;
            this.buttonMakeGif.Click += new System.EventHandler(this.buttonMakeGif_Click);
            // 
            // buttonSelectGifPath
            // 
            this.buttonSelectGifPath.Location = new System.Drawing.Point(12, 50);
            this.buttonSelectGifPath.Name = "buttonSelectGifPath";
            this.buttonSelectGifPath.Size = new System.Drawing.Size(83, 23);
            this.buttonSelectGifPath.TabIndex = 4;
            this.buttonSelectGifPath.Text = "选择GIF路径";
            this.buttonSelectGifPath.UseVisualStyleBackColor = true;
            this.buttonSelectGifPath.Click += new System.EventHandler(this.buttonSelectGifPath_Click);
            // 
            // textBox_SelectGifPath
            // 
            this.textBox_SelectGifPath.Location = new System.Drawing.Point(12, 12);
            this.textBox_SelectGifPath.Name = "textBox_SelectGifPath";
            this.textBox_SelectGifPath.ReadOnly = true;
            this.textBox_SelectGifPath.Size = new System.Drawing.Size(302, 21);
            this.textBox_SelectGifPath.TabIndex = 3;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(329, 84);
            this.Controls.Add(this.buttonMakeGif);
            this.Controls.Add(this.buttonSelectGifPath);
            this.Controls.Add(this.textBox_SelectGifPath);
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "制作GIF";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonMakeGif;
        private System.Windows.Forms.Button buttonSelectGifPath;
        private System.Windows.Forms.TextBox textBox_SelectGifPath;
    }
}

