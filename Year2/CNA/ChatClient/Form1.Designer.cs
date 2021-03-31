namespace ChatClient
{
    partial class Form1
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
            this.textToSend = new System.Windows.Forms.TextBox();
            this.chatText = new System.Windows.Forms.RichTextBox();
            this.clientList = new System.Windows.Forms.RichTextBox();
            this.lbl_User = new System.Windows.Forms.Label();
            this.tb_User = new System.Windows.Forms.TextBox();
            this.btnEnter = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textToSend
            // 
            this.textToSend.Location = new System.Drawing.Point(27, 446);
            this.textToSend.Multiline = true;
            this.textToSend.Name = "textToSend";
            this.textToSend.Size = new System.Drawing.Size(493, 59);
            this.textToSend.TabIndex = 1;
            // 
            // chatText
            // 
            this.chatText.Location = new System.Drawing.Point(27, 34);
            this.chatText.Name = "chatText";
            this.chatText.ReadOnly = true;
            this.chatText.Size = new System.Drawing.Size(419, 397);
            this.chatText.TabIndex = 2;
            this.chatText.Text = "";
            // 
            // clientList
            // 
            this.clientList.Location = new System.Drawing.Point(461, 34);
            this.clientList.Name = "clientList";
            this.clientList.ReadOnly = true;
            this.clientList.Size = new System.Drawing.Size(140, 397);
            this.clientList.TabIndex = 3;
            this.clientList.Text = "";
            // 
            // lbl_User
            // 
            this.lbl_User.AutoSize = true;
            this.lbl_User.Location = new System.Drawing.Point(24, 8);
            this.lbl_User.Name = "lbl_User";
            this.lbl_User.Size = new System.Drawing.Size(77, 17);
            this.lbl_User.TabIndex = 4;
            this.lbl_User.Text = "Username:";
            // 
            // tb_User
            // 
            this.tb_User.Location = new System.Drawing.Point(107, 6);
            this.tb_User.Name = "tb_User";
            this.tb_User.Size = new System.Drawing.Size(339, 22);
            this.tb_User.TabIndex = 5;
            // 
            // btnEnter
            // 
            this.btnEnter.Location = new System.Drawing.Point(526, 446);
            this.btnEnter.Name = "btnEnter";
            this.btnEnter.Size = new System.Drawing.Size(75, 59);
            this.btnEnter.TabIndex = 6;
            this.btnEnter.Text = "Enter";
            this.btnEnter.UseVisualStyleBackColor = true;
            this.btnEnter.Click += new System.EventHandler(this.btnEnter_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1091, 517);
            this.Controls.Add(this.btnEnter);
            this.Controls.Add(this.tb_User);
            this.Controls.Add(this.lbl_User);
            this.Controls.Add(this.clientList);
            this.Controls.Add(this.chatText);
            this.Controls.Add(this.textToSend);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textToSend;
        private System.Windows.Forms.RichTextBox chatText;
        private System.Windows.Forms.RichTextBox clientList;
        private System.Windows.Forms.Label lbl_User;
        private System.Windows.Forms.TextBox tb_User;
        private System.Windows.Forms.Button btnEnter;
    }
}

