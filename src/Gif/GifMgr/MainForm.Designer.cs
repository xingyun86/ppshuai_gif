namespace GifMgr
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
            this.textBox_SelectPNGPath = new System.Windows.Forms.TextBox();
            this.buttonSelectPNGPath = new System.Windows.Forms.Button();
            this.buttonMakeGIF = new System.Windows.Forms.Button();
            this.textBox_SelectGIFPath = new System.Windows.Forms.TextBox();
            this.buttonSelectGIFPath = new System.Windows.Forms.Button();
            this.buttonReverseGIF = new System.Windows.Forms.Button();
            this.textBox_SelectPNGSavePath = new System.Windows.Forms.TextBox();
            this.buttonSelectPNGSavePath = new System.Windows.Forms.Button();
            this.buttonUnpackGIF = new System.Windows.Forms.Button();
            this.pictureBox_Sepertor = new System.Windows.Forms.PictureBox();
            this.numericUpDown_DelayTimes = new System.Windows.Forms.NumericUpDown();
            this.label_DelayTimes = new System.Windows.Forms.Label();
            this.buttonHelpInstrument = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Sepertor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_DelayTimes)).BeginInit();
            this.SuspendLayout();
            // 
            // textBox_SelectPNGPath
            // 
            this.textBox_SelectPNGPath.Location = new System.Drawing.Point(12, 18);
            this.textBox_SelectPNGPath.Name = "textBox_SelectPNGPath";
            this.textBox_SelectPNGPath.ReadOnly = true;
            this.textBox_SelectPNGPath.Size = new System.Drawing.Size(299, 21);
            this.textBox_SelectPNGPath.TabIndex = 1;
            // 
            // buttonSelectPNGPath
            // 
            this.buttonSelectPNGPath.Location = new System.Drawing.Point(312, 18);
            this.buttonSelectPNGPath.Name = "buttonSelectPNGPath";
            this.buttonSelectPNGPath.Size = new System.Drawing.Size(83, 23);
            this.buttonSelectPNGPath.TabIndex = 2;
            this.buttonSelectPNGPath.Text = "选择PNG路径";
            this.buttonSelectPNGPath.UseVisualStyleBackColor = true;
            this.buttonSelectPNGPath.Click += new System.EventHandler(this.buttonSelectPNGPath_Click);
            // 
            // buttonMakeGIF
            // 
            this.buttonMakeGIF.Location = new System.Drawing.Point(211, 119);
            this.buttonMakeGIF.Name = "buttonMakeGIF";
            this.buttonMakeGIF.Size = new System.Drawing.Size(64, 23);
            this.buttonMakeGIF.TabIndex = 3;
            this.buttonMakeGIF.Text = "生成GIF";
            this.buttonMakeGIF.UseVisualStyleBackColor = true;
            this.buttonMakeGIF.Click += new System.EventHandler(this.buttonMakeGIF_Click);
            // 
            // textBox_SelectGIFPath
            // 
            this.textBox_SelectGIFPath.Location = new System.Drawing.Point(12, 45);
            this.textBox_SelectGIFPath.Name = "textBox_SelectGIFPath";
            this.textBox_SelectGIFPath.ReadOnly = true;
            this.textBox_SelectGIFPath.Size = new System.Drawing.Size(299, 21);
            this.textBox_SelectGIFPath.TabIndex = 4;
            // 
            // buttonSelectGIFPath
            // 
            this.buttonSelectGIFPath.Location = new System.Drawing.Point(312, 45);
            this.buttonSelectGIFPath.Name = "buttonSelectGIFPath";
            this.buttonSelectGIFPath.Size = new System.Drawing.Size(83, 21);
            this.buttonSelectGIFPath.TabIndex = 5;
            this.buttonSelectGIFPath.Text = "选择GIF路径";
            this.buttonSelectGIFPath.UseVisualStyleBackColor = true;
            this.buttonSelectGIFPath.Click += new System.EventHandler(this.buttonSelectGIFPath_Click);
            // 
            // buttonReverseGIF
            // 
            this.buttonReverseGIF.Location = new System.Drawing.Point(277, 119);
            this.buttonReverseGIF.Name = "buttonReverseGIF";
            this.buttonReverseGIF.Size = new System.Drawing.Size(55, 23);
            this.buttonReverseGIF.TabIndex = 6;
            this.buttonReverseGIF.Text = "反转GIF";
            this.buttonReverseGIF.UseVisualStyleBackColor = true;
            this.buttonReverseGIF.Click += new System.EventHandler(this.buttonReverseGIF_Click);
            // 
            // textBox_SelectPNGSavePath
            // 
            this.textBox_SelectPNGSavePath.Location = new System.Drawing.Point(12, 73);
            this.textBox_SelectPNGSavePath.Name = "textBox_SelectPNGSavePath";
            this.textBox_SelectPNGSavePath.ReadOnly = true;
            this.textBox_SelectPNGSavePath.Size = new System.Drawing.Size(299, 21);
            this.textBox_SelectPNGSavePath.TabIndex = 7;
            // 
            // buttonSelectPNGSavePath
            // 
            this.buttonSelectPNGSavePath.Location = new System.Drawing.Point(312, 73);
            this.buttonSelectPNGSavePath.Name = "buttonSelectPNGSavePath";
            this.buttonSelectPNGSavePath.Size = new System.Drawing.Size(83, 21);
            this.buttonSelectPNGSavePath.TabIndex = 8;
            this.buttonSelectPNGSavePath.Text = "保存PNG路径";
            this.buttonSelectPNGSavePath.UseVisualStyleBackColor = true;
            this.buttonSelectPNGSavePath.Click += new System.EventHandler(this.buttonSelectUnpackPNGPath_Click);
            // 
            // buttonUnpackGIF
            // 
            this.buttonUnpackGIF.Location = new System.Drawing.Point(145, 119);
            this.buttonUnpackGIF.Name = "buttonUnpackGIF";
            this.buttonUnpackGIF.Size = new System.Drawing.Size(64, 23);
            this.buttonUnpackGIF.TabIndex = 9;
            this.buttonUnpackGIF.Text = "解压GIF";
            this.buttonUnpackGIF.UseVisualStyleBackColor = true;
            this.buttonUnpackGIF.Click += new System.EventHandler(this.buttonUnpackGIF_Click);
            // 
            // pictureBox_Sepertor
            // 
            this.pictureBox_Sepertor.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.pictureBox_Sepertor.Location = new System.Drawing.Point(12, 107);
            this.pictureBox_Sepertor.Name = "pictureBox_Sepertor";
            this.pictureBox_Sepertor.Size = new System.Drawing.Size(383, 1);
            this.pictureBox_Sepertor.TabIndex = 10;
            this.pictureBox_Sepertor.TabStop = false;
            // 
            // numericUpDown_DelayTimes
            // 
            this.numericUpDown_DelayTimes.Location = new System.Drawing.Point(88, 121);
            this.numericUpDown_DelayTimes.Maximum = new decimal(new int[] {
            -1,
            0,
            0,
            0});
            this.numericUpDown_DelayTimes.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown_DelayTimes.Name = "numericUpDown_DelayTimes";
            this.numericUpDown_DelayTimes.Size = new System.Drawing.Size(54, 21);
            this.numericUpDown_DelayTimes.TabIndex = 11;
            this.numericUpDown_DelayTimes.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numericUpDown_DelayTimes.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label_DelayTimes
            // 
            this.label_DelayTimes.AutoSize = true;
            this.label_DelayTimes.Location = new System.Drawing.Point(11, 124);
            this.label_DelayTimes.Name = "label_DelayTimes";
            this.label_DelayTimes.Size = new System.Drawing.Size(77, 12);
            this.label_DelayTimes.TabIndex = 12;
            this.label_DelayTimes.Text = "延迟间隔(ms)";
            // 
            // buttonHelpInstrument
            // 
            this.buttonHelpInstrument.Location = new System.Drawing.Point(333, 119);
            this.buttonHelpInstrument.Name = "buttonHelpInstrument";
            this.buttonHelpInstrument.Size = new System.Drawing.Size(62, 23);
            this.buttonHelpInstrument.TabIndex = 6;
            this.buttonHelpInstrument.Text = "帮助说明";
            this.buttonHelpInstrument.UseVisualStyleBackColor = true;
            this.buttonHelpInstrument.Click += new System.EventHandler(this.buttonHelpInstrument_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(407, 154);
            this.Controls.Add(this.label_DelayTimes);
            this.Controls.Add(this.numericUpDown_DelayTimes);
            this.Controls.Add(this.pictureBox_Sepertor);
            this.Controls.Add(this.textBox_SelectPNGPath);
            this.Controls.Add(this.buttonSelectPNGPath);
            this.Controls.Add(this.buttonMakeGIF);
            this.Controls.Add(this.textBox_SelectGIFPath);
            this.Controls.Add(this.buttonSelectGIFPath);
            this.Controls.Add(this.buttonHelpInstrument);
            this.Controls.Add(this.buttonReverseGIF);
            this.Controls.Add(this.textBox_SelectPNGSavePath);
            this.Controls.Add(this.buttonSelectPNGSavePath);
            this.Controls.Add(this.buttonUnpackGIF);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GIF管理工具";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_Sepertor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_DelayTimes)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox_SelectPNGPath;
        private System.Windows.Forms.Button buttonSelectPNGPath;
        private System.Windows.Forms.Button buttonMakeGIF;
        private System.Windows.Forms.TextBox textBox_SelectGIFPath;
        private System.Windows.Forms.Button buttonSelectGIFPath;
        private System.Windows.Forms.Button buttonReverseGIF;       
        private System.Windows.Forms.TextBox textBox_SelectPNGSavePath;
        private System.Windows.Forms.Button buttonSelectPNGSavePath;        
        private System.Windows.Forms.Button buttonUnpackGIF;
        private System.Windows.Forms.PictureBox pictureBox_Sepertor;
        private System.Windows.Forms.NumericUpDown numericUpDown_DelayTimes;
        private System.Windows.Forms.Label label_DelayTimes;
        private System.Windows.Forms.Button buttonHelpInstrument;
    }
}

