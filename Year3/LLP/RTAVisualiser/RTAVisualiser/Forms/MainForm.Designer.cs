namespace RTAVisualiser.Forms
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
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.cartesianChart1 = new LiveCharts.WinForms.CartesianChart();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.DurationAllCartesian = new LiveCharts.WinForms.CartesianChart();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.RenderPreview = new System.Windows.Forms.PictureBox();
            this.ResCBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.CompilerOptimisationCB = new System.Windows.Forms.ComboBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.Sphere = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Radius = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Position = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SurfaceColour = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Reflection = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Transparency = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.EmissionColour = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.BaselineCheckBox = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.ThreadCountNUD = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.PhysicsTickBox = new System.Windows.Forms.CheckBox();
            this.ConcurrentTickBox = new System.Windows.Forms.CheckBox();
            this.FramesTB = new System.Windows.Forms.TextBox();
            this.FPSCBox = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.RenderButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.ConsoleOutputTB = new System.Windows.Forms.RichTextBox();
            this.tabControl3 = new System.Windows.Forms.TabControl();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.tabControl4 = new System.Windows.Forms.TabControl();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.TimingsCartesian2 = new LiveCharts.WinForms.CartesianChart();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.ThreadingCartesian = new LiveCharts.WinForms.CartesianChart();
            this.tabPage8 = new System.Windows.Forms.TabPage();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.tabControl2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.RenderPreview)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ThreadCountNUD)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabControl3.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.tabControl4.SuspendLayout();
            this.tabPage7.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPage3);
            this.tabControl2.Controls.Add(this.tabPage4);
            this.tabControl2.Location = new System.Drawing.Point(823, 7);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(1064, 1006);
            this.tabControl2.TabIndex = 0;
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.groupBox5);
            this.tabPage3.Controls.Add(this.groupBox4);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage3.Size = new System.Drawing.Size(1056, 980);
            this.tabPage3.TabIndex = 0;
            this.tabPage3.Text = "General";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.cartesianChart1);
            this.groupBox5.Location = new System.Drawing.Point(6, 6);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(1044, 437);
            this.groupBox5.TabIndex = 3;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Memory Report";
            // 
            // cartesianChart1
            // 
            this.cartesianChart1.Location = new System.Drawing.Point(7, 16);
            this.cartesianChart1.Name = "cartesianChart1";
            this.cartesianChart1.Size = new System.Drawing.Size(1031, 415);
            this.cartesianChart1.TabIndex = 0;
            this.cartesianChart1.Text = "DurationCartesian";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.DurationAllCartesian);
            this.groupBox4.Location = new System.Drawing.Point(6, 449);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(1044, 525);
            this.groupBox4.TabIndex = 2;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Duration Report";
            // 
            // DurationAllCartesian
            // 
            this.DurationAllCartesian.Location = new System.Drawing.Point(7, 19);
            this.DurationAllCartesian.Name = "DurationAllCartesian";
            this.DurationAllCartesian.Size = new System.Drawing.Size(1031, 500);
            this.DurationAllCartesian.TabIndex = 0;
            this.DurationAllCartesian.Text = "DurationCartesian";
            // 
            // tabPage4
            // 
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage4.Size = new System.Drawing.Size(1056, 980);
            this.tabPage4.TabIndex = 1;
            this.tabPage4.Text = "Methods";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // RenderPreview
            // 
            this.RenderPreview.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.RenderPreview.Location = new System.Drawing.Point(0, 0);
            this.RenderPreview.Name = "RenderPreview";
            this.RenderPreview.Size = new System.Drawing.Size(814, 491);
            this.RenderPreview.TabIndex = 1;
            this.RenderPreview.TabStop = false;
            // 
            // ResCBox
            // 
            this.ResCBox.FormattingEnabled = true;
            this.ResCBox.Items.AddRange(new object[] {
            "3820x2160",
            "1920x1080",
            "640x480"});
            this.ResCBox.Location = new System.Drawing.Point(70, 19);
            this.ResCBox.Name = "ResCBox";
            this.ResCBox.Size = new System.Drawing.Size(121, 21);
            this.ResCBox.TabIndex = 2;
            this.ResCBox.SelectedIndexChanged += new System.EventHandler(this.ResCBox_SelectedIndexChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Resolution:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox8);
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.Location = new System.Drawing.Point(6, 9);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(814, 454);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Configuration";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.label5);
            this.groupBox8.Controls.Add(this.CompilerOptimisationCB);
            this.groupBox8.Location = new System.Drawing.Point(428, 20);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(379, 152);
            this.groupBox8.TabIndex = 2;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Optimisation";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(22, 68);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(110, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Compiler Optimisation:";
            // 
            // CompilerOptimisationCB
            // 
            this.CompilerOptimisationCB.FormattingEnabled = true;
            this.CompilerOptimisationCB.Items.AddRange(new object[] {
            "None",
            "/O2: Maximum Running Speed",
            "/Ox: Full Optimisation",
            "/Oy: Omit Frame Pointers"});
            this.CompilerOptimisationCB.Location = new System.Drawing.Point(138, 65);
            this.CompilerOptimisationCB.Name = "CompilerOptimisationCB";
            this.CompilerOptimisationCB.Size = new System.Drawing.Size(207, 21);
            this.CompilerOptimisationCB.TabIndex = 0;
            this.CompilerOptimisationCB.SelectedIndexChanged += new System.EventHandler(this.CompilerOptimisationCB_SelectedIndexChanged);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.dataGridView1);
            this.groupBox3.Location = new System.Drawing.Point(6, 179);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(802, 269);
            this.groupBox3.TabIndex = 1;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Scene Objects";
            // 
            // dataGridView1
            // 
            this.dataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridView1.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.DisplayedCells;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Sphere,
            this.Radius,
            this.Position,
            this.SurfaceColour,
            this.Reflection,
            this.Transparency,
            this.EmissionColour});
            this.dataGridView1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dataGridView1.Location = new System.Drawing.Point(3, 16);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.Size = new System.Drawing.Size(796, 250);
            this.dataGridView1.TabIndex = 0;
            this.dataGridView1.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            // 
            // Sphere
            // 
            this.Sphere.HeaderText = "Name";
            this.Sphere.Name = "Sphere";
            // 
            // Radius
            // 
            this.Radius.HeaderText = "Radius";
            this.Radius.Name = "Radius";
            // 
            // Position
            // 
            this.Position.HeaderText = "Position";
            this.Position.Name = "Position";
            // 
            // SurfaceColour
            // 
            this.SurfaceColour.HeaderText = "Surface Colour";
            this.SurfaceColour.Name = "SurfaceColour";
            // 
            // Reflection
            // 
            this.Reflection.HeaderText = "Reflection";
            this.Reflection.Name = "Reflection";
            // 
            // Transparency
            // 
            this.Transparency.HeaderText = "Transparency";
            this.Transparency.Name = "Transparency";
            // 
            // EmissionColour
            // 
            this.EmissionColour.HeaderText = "EmissionColour";
            this.EmissionColour.Name = "EmissionColour";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.BaselineCheckBox);
            this.groupBox2.Controls.Add(this.checkBox1);
            this.groupBox2.Controls.Add(this.ThreadCountNUD);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.PhysicsTickBox);
            this.groupBox2.Controls.Add(this.ConcurrentTickBox);
            this.groupBox2.Controls.Add(this.FramesTB);
            this.groupBox2.Controls.Add(this.FPSCBox);
            this.groupBox2.Controls.Add(this.ResCBox);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(6, 19);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(416, 154);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Renderer";
            // 
            // BaselineCheckBox
            // 
            this.BaselineCheckBox.AutoSize = true;
            this.BaselineCheckBox.Location = new System.Drawing.Point(214, 23);
            this.BaselineCheckBox.Name = "BaselineCheckBox";
            this.BaselineCheckBox.Size = new System.Drawing.Size(113, 17);
            this.BaselineCheckBox.TabIndex = 13;
            this.BaselineCheckBox.Text = "Baseline Renderer";
            this.BaselineCheckBox.UseVisualStyleBackColor = true;
            this.BaselineCheckBox.CheckedChanged += new System.EventHandler(this.BaselineCheckBox_CheckedChanged);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(214, 49);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(102, 17);
            this.checkBox1.TabIndex = 12;
            this.checkBox1.Text = "Method Profiling";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.MethodProfiling_CheckedChanged);
            // 
            // ThreadCountNUD
            // 
            this.ThreadCountNUD.Location = new System.Drawing.Point(285, 98);
            this.ThreadCountNUD.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.ThreadCountNUD.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ThreadCountNUD.Name = "ThreadCountNUD";
            this.ThreadCountNUD.Size = new System.Drawing.Size(120, 20);
            this.ThreadCountNUD.TabIndex = 11;
            this.ThreadCountNUD.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.ThreadCountNUD.ValueChanged += new System.EventHandler(this.ThreadCountNUD_ValueChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(211, 101);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 13);
            this.label4.TabIndex = 10;
            this.label4.Text = "Max Threads:";
            // 
            // PhysicsTickBox
            // 
            this.PhysicsTickBox.AutoSize = true;
            this.PhysicsTickBox.Location = new System.Drawing.Point(11, 122);
            this.PhysicsTickBox.Name = "PhysicsTickBox";
            this.PhysicsTickBox.Size = new System.Drawing.Size(91, 17);
            this.PhysicsTickBox.TabIndex = 9;
            this.PhysicsTickBox.Text = "Apply Physics";
            this.PhysicsTickBox.UseVisualStyleBackColor = true;
            this.PhysicsTickBox.CheckedChanged += new System.EventHandler(this.PhysicsBox_CheckedChanged);
            // 
            // ConcurrentTickBox
            // 
            this.ConcurrentTickBox.AutoSize = true;
            this.ConcurrentTickBox.Location = new System.Drawing.Point(11, 99);
            this.ConcurrentTickBox.Name = "ConcurrentTickBox";
            this.ConcurrentTickBox.Size = new System.Drawing.Size(130, 17);
            this.ConcurrentTickBox.TabIndex = 5;
            this.ConcurrentTickBox.Text = "Concurrent Rendering";
            this.ConcurrentTickBox.UseVisualStyleBackColor = true;
            this.ConcurrentTickBox.CheckedChanged += new System.EventHandler(this.ConcurrentTickBox_CheckedChanged);
            // 
            // FramesTB
            // 
            this.FramesTB.Location = new System.Drawing.Point(70, 46);
            this.FramesTB.Name = "FramesTB";
            this.FramesTB.Size = new System.Drawing.Size(120, 20);
            this.FramesTB.TabIndex = 8;
            this.FramesTB.Text = "Enter Framecount";
            this.FramesTB.TextChanged += new System.EventHandler(this.FramesTB_TextChanged);
            // 
            // FPSCBox
            // 
            this.FPSCBox.FormattingEnabled = true;
            this.FPSCBox.Items.AddRange(new object[] {
            "24",
            "30",
            "60",
            "90",
            "120"});
            this.FPSCBox.Location = new System.Drawing.Point(70, 72);
            this.FPSCBox.Name = "FPSCBox";
            this.FPSCBox.Size = new System.Drawing.Size(121, 21);
            this.FPSCBox.TabIndex = 4;
            this.FPSCBox.SelectedIndexChanged += new System.EventHandler(this.FPSCBox_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(23, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 13);
            this.label3.TabIndex = 7;
            this.label3.Text = "Frames:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(40, 75);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "FPS:";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(3, 469);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(709, 23);
            this.progressBar1.TabIndex = 2;
            // 
            // RenderButton
            // 
            this.RenderButton.Location = new System.Drawing.Point(718, 469);
            this.RenderButton.Name = "RenderButton";
            this.RenderButton.Size = new System.Drawing.Size(102, 23);
            this.RenderButton.TabIndex = 3;
            this.RenderButton.Text = "Render";
            this.RenderButton.UseVisualStyleBackColor = true;
            this.RenderButton.Click += new System.EventHandler(this.RenderButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Location = new System.Drawing.Point(3, 497);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(824, 517);
            this.tabControl1.TabIndex = 5;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.RenderPreview);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(816, 491);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Render Preview";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.ConsoleOutputTB);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(816, 491);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Console Output";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // ConsoleOutputTB
            // 
            this.ConsoleOutputTB.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConsoleOutputTB.Location = new System.Drawing.Point(6, 6);
            this.ConsoleOutputTB.Name = "ConsoleOutputTB";
            this.ConsoleOutputTB.ReadOnly = true;
            this.ConsoleOutputTB.Size = new System.Drawing.Size(812, 482);
            this.ConsoleOutputTB.TabIndex = 0;
            this.ConsoleOutputTB.Text = "";
            // 
            // tabControl3
            // 
            this.tabControl3.Controls.Add(this.tabPage5);
            this.tabControl3.Controls.Add(this.tabPage6);
            this.tabControl3.Location = new System.Drawing.Point(2, 0);
            this.tabControl3.Name = "tabControl3";
            this.tabControl3.SelectedIndex = 0;
            this.tabControl3.Size = new System.Drawing.Size(1901, 1042);
            this.tabControl3.TabIndex = 6;
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.groupBox1);
            this.tabPage5.Controls.Add(this.tabControl2);
            this.tabPage5.Controls.Add(this.tabControl1);
            this.tabPage5.Controls.Add(this.progressBar1);
            this.tabPage5.Controls.Add(this.RenderButton);
            this.tabPage5.Location = new System.Drawing.Point(4, 22);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage5.Size = new System.Drawing.Size(1893, 1016);
            this.tabPage5.TabIndex = 0;
            this.tabPage5.Text = "Overview";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.tabControl4);
            this.tabPage6.Location = new System.Drawing.Point(4, 22);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage6.Size = new System.Drawing.Size(1893, 1016);
            this.tabPage6.TabIndex = 1;
            this.tabPage6.Text = "Reporting";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // tabControl4
            // 
            this.tabControl4.Controls.Add(this.tabPage7);
            this.tabControl4.Controls.Add(this.tabPage8);
            this.tabControl4.Controls.Add(this.tabPage9);
            this.tabControl4.Location = new System.Drawing.Point(8, 6);
            this.tabControl4.Name = "tabControl4";
            this.tabControl4.SelectedIndex = 0;
            this.tabControl4.Size = new System.Drawing.Size(1882, 1007);
            this.tabControl4.TabIndex = 0;
            // 
            // tabPage7
            // 
            this.tabPage7.Controls.Add(this.splitContainer1);
            this.tabPage7.Location = new System.Drawing.Point(4, 22);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage7.Size = new System.Drawing.Size(1874, 981);
            this.tabPage7.TabIndex = 0;
            this.tabPage7.Text = "Timings";
            this.tabPage7.UseVisualStyleBackColor = true;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(3, 3);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.groupBox6);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.groupBox7);
            this.splitContainer1.Size = new System.Drawing.Size(1868, 975);
            this.splitContainer1.SplitterDistance = 463;
            this.splitContainer1.TabIndex = 0;
            // 
            // groupBox6
            // 
            this.groupBox6.AutoSize = true;
            this.groupBox6.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.groupBox6.Controls.Add(this.TimingsCartesian2);
            this.groupBox6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox6.Location = new System.Drawing.Point(0, 0);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(1868, 463);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Frame Time";
            // 
            // TimingsCartesian2
            // 
            this.TimingsCartesian2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TimingsCartesian2.Location = new System.Drawing.Point(3, 16);
            this.TimingsCartesian2.Name = "TimingsCartesian2";
            this.TimingsCartesian2.Size = new System.Drawing.Size(1862, 444);
            this.TimingsCartesian2.TabIndex = 0;
            this.TimingsCartesian2.Text = "TimingsCartesian2";
            // 
            // groupBox7
            // 
            this.groupBox7.AutoSize = true;
            this.groupBox7.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowAndShrink;
            this.groupBox7.Controls.Add(this.ThreadingCartesian);
            this.groupBox7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox7.Location = new System.Drawing.Point(0, 0);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(1868, 508);
            this.groupBox7.TabIndex = 0;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Threading";
            // 
            // ThreadingCartesian
            // 
            this.ThreadingCartesian.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ThreadingCartesian.Location = new System.Drawing.Point(3, 16);
            this.ThreadingCartesian.Name = "ThreadingCartesian";
            this.ThreadingCartesian.Size = new System.Drawing.Size(1862, 489);
            this.ThreadingCartesian.TabIndex = 0;
            this.ThreadingCartesian.Text = "cartesianChart3";
            // 
            // tabPage8
            // 
            this.tabPage8.Location = new System.Drawing.Point(4, 22);
            this.tabPage8.Name = "tabPage8";
            this.tabPage8.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage8.Size = new System.Drawing.Size(1874, 981);
            this.tabPage8.TabIndex = 1;
            this.tabPage8.Text = "Memory";
            this.tabPage8.UseVisualStyleBackColor = true;
            // 
            // tabPage9
            // 
            this.tabPage9.Location = new System.Drawing.Point(4, 22);
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.Size = new System.Drawing.Size(1874, 981);
            this.tabPage9.TabIndex = 2;
            this.tabPage9.Text = "Method Calling";
            this.tabPage9.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.ClientSize = new System.Drawing.Size(1904, 1041);
            this.Controls.Add(this.tabControl3);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "RTA Visualiser";
            this.tabControl2.ResumeLayout(false);
            this.tabPage3.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.RenderPreview)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.ThreadCountNUD)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabControl3.ResumeLayout(false);
            this.tabPage5.ResumeLayout(false);
            this.tabPage6.ResumeLayout(false);
            this.tabControl4.ResumeLayout(false);
            this.tabPage7.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.groupBox7.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.TabPage tabPage4;
        private LiveCharts.WinForms.CartesianChart DurationAllCartesian;
        private System.Windows.Forms.PictureBox RenderPreview;
        private System.Windows.Forms.ComboBox ResCBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox FramesTB;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox FPSCBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.GroupBox groupBox5;
        private LiveCharts.WinForms.CartesianChart cartesianChart1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button RenderButton;
        private System.Windows.Forms.CheckBox ConcurrentTickBox;
        private System.Windows.Forms.NumericUpDown ThreadCountNUD;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox PhysicsTickBox;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.RichTextBox ConsoleOutputTB;
        private System.Windows.Forms.TabControl tabControl3;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.TabControl tabControl4;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.TabPage tabPage8;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.GroupBox groupBox6;
        private LiveCharts.WinForms.CartesianChart TimingsCartesian2;
        private System.Windows.Forms.GroupBox groupBox7;
        private LiveCharts.WinForms.CartesianChart ThreadingCartesian;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox CompilerOptimisationCB;
        private System.Windows.Forms.CheckBox BaselineCheckBox;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn Sphere;
        private System.Windows.Forms.DataGridViewTextBoxColumn Radius;
        private System.Windows.Forms.DataGridViewTextBoxColumn Position;
        private System.Windows.Forms.DataGridViewTextBoxColumn SurfaceColour;
        private System.Windows.Forms.DataGridViewTextBoxColumn Reflection;
        private System.Windows.Forms.DataGridViewTextBoxColumn Transparency;
        private System.Windows.Forms.DataGridViewTextBoxColumn EmissionColour;
    }
}