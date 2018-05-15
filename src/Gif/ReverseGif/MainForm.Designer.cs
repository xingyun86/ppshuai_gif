namespace ReverseGif
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
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonSelectGif = new System.Windows.Forms.Button();
            this.buttonReverseGif = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(12, 12);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(302, 21);
            this.textBox1.TabIndex = 0;
            // 
            // buttonSelectGif
            // 
            this.buttonSelectGif.Location = new System.Drawing.Point(12, 50);
            this.buttonSelectGif.Name = "buttonSelectGif";
            this.buttonSelectGif.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectGif.TabIndex = 1;
            this.buttonSelectGif.Text = "选择GIF";
            this.buttonSelectGif.UseVisualStyleBackColor = true;
            this.buttonSelectGif.Click += new System.EventHandler(this.buttonSelectGif_Click);
            // 
            // buttonReverseGif
            // 
            this.buttonReverseGif.Location = new System.Drawing.Point(239, 50);
            this.buttonReverseGif.Name = "buttonReverseGif";
            this.buttonReverseGif.Size = new System.Drawing.Size(75, 23);
            this.buttonReverseGif.TabIndex = 2;
            this.buttonReverseGif.Text = "反转GIF";
            this.buttonReverseGif.UseVisualStyleBackColor = true;
            this.buttonReverseGif.Click += new System.EventHandler(this.buttonReverseGif_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(326, 92);
            this.Controls.Add(this.buttonReverseGif);
            this.Controls.Add(this.buttonSelectGif);
            this.Controls.Add(this.textBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.Text = "Gif倒序";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonSelectGif;
        private System.Windows.Forms.Button buttonReverseGif;
    }
}

