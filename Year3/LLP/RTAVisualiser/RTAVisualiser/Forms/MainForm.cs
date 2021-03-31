using System;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

using RTAVisualiser.Interfaces;

using Unity.Attributes;

using RTAVisualiser.Debugging;

namespace RTAVisualiser.Forms
{
    public partial class MainForm : Form
    {
        private string CurrentPreview { get; set; } = null;
        private string CurrentLastRender { get; set; } = null;
        public ITerminalInstruction Magick { get; set; } = null;
        public ITerminalInstruction Raytracer { get; set; } = null;

        private IAppSettings AppSettings { get; set; } = null;
        private IReportMapper CoreMapper { get; set; } = null;
        private IConfigDomain ConfigDomain { get; set; } = null;

        public MainForm(IAppSettings settings, IReportMapper mapper, IConfigDomain configDomain, [Dependency("Raytracer")] ITerminalInstruction raytracer, [Dependency("Magick")] ITerminalInstruction magick)
        {
            Magick = magick;
            Raytracer = raytracer;
            Magick.Task.Exited += Magick_Exited;

            AppSettings = settings;
            CurrentLastRender = AppSettings.RepositoryLastAccess;

            CoreMapper = mapper;
            ConfigDomain = configDomain;

            InitializeComponent();
            InitialiseConfigGUI();
            
            DurationAllCartesian.Series = CoreMapper.InitialiseFrameTimeCollection();
            TimingsCartesian2.Series = CoreMapper.InitialiseFrameTimeCollection();
            ThreadingCartesian.Series = CoreMapper.InitialiseThreadTimeCollection();

            RenderPreview.Image = Image.FromFile("Config\\Image.jpg");
            RenderPreview.SizeMode = PictureBoxSizeMode.StretchImage;

            Console.SetOut(new MultiTextWriter(new RichTextBoxWriter(ConsoleOutputTB), Console.Out));
        }
        
        private void InitialiseConfigGUI()
        {
            PhysicsTickBox.Checked = ConfigDomain.GetPhysics();
            ConcurrentTickBox.Checked = ConfigDomain.GetParallel();

            ThreadCountNUD.Value = ConfigDomain.GetThreads();

            FramesTB.Text = $"{ConfigDomain.GetMaxFrames()}";
            FPSCBox.Text = $"{ConfigDomain.GetFramesPerSecond()}";
            ResCBox.Text = $"{ConfigDomain.GetResolutionWidth()}x{ConfigDomain.GetResolutionHeight()}";
        }
        private void UpdatePreview()
        {
            RenderPreview.Image = Image.FromFile($"Config\\Image_{CurrentPreview}.jpg");
            RenderPreview.SizeMode = PictureBoxSizeMode.StretchImage;
            Raytracer.SetArguments("");
        }

        private void MagickTask(object sender, EventArgs e)
        {
            CurrentPreview = DateTime.Now.Millisecond.ToString();
            if (this.InvokeRequired)
            {
                try
                {
                    Magick.SetArguments(CurrentPreview);
                    this.Invoke(new MethodInvoker(() => Magick.Launch()));
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"MainForm.cs:78:- EXCEPTION CAUGHT: {ex.Message}");
                    return;
                }
            }
            else
            {
                Magick.SetArguments(CurrentPreview);
                Magick.Launch();
            }
        }
        private void RaytracerTask(object sender, EventArgs e)
        {
            CoreMapper.Update();
        }
        private void Magick_Exited(object sender, EventArgs e)
        {
            Thread.Sleep(2000);
            this.Invoke(new MethodInvoker(() => UpdatePreview()));
            Raytracer.Task.Exited -= MagickTask;
        }

        private void RenderButton_Click(object sender, EventArgs e)
        {
            CurrentLastRender = DateTime.Now.ToString("yyyy-MM-dd_HH-mm-ss");
            ConfigDomain.SetMP4OutputPath($"Output\\{CurrentLastRender}\\MP4\\");
            ConfigDomain.SetPPMOutputPath($"Output\\{CurrentLastRender}\\PPM\\");
            ConfigDomain.SetReportPath($"Output\\{CurrentLastRender}\\Reports\\");

            Raytracer.Task.Exited += RaytracerTask;
            Raytracer.Launch();
        }
        private void FramesTB_TextChanged(object sender, EventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text != "")
                ConfigDomain.SetMaxFrames(Convert.ToInt32(tb.Text));
        }
        private void PhysicsBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            ConfigDomain.SetPhysics(cb.Checked);
        }
        private void ThreadCountNUD_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown nud = (NumericUpDown)sender;
            ConfigDomain.SetThreads(Convert.ToInt32(nud.Value));
        }
        private void ResCBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ConfigDomain.SetMP4OutputPath($"Output\\PreviewRender\\MP4\\");
            ConfigDomain.SetPPMOutputPath($"Output\\PreviewRender\\PPM\\");
            ConfigDomain.SetReportPath($"Output\\PreviewRender\\Reports\\");

            ComboBox cb = (ComboBox)sender;
            string[] res = cb.Text.Split('x');
            string dtMilliseconds = DateTime.Now.Millisecond.ToString();

            ConfigDomain.SetResolutionWidth(Convert.ToInt32(res[0]));
            ConfigDomain.SetResolutionHeight(Convert.ToInt32(res[1]));

            Raytracer.Task.Exited += MagickTask;
            Raytracer.SetArguments("preview");
            Raytracer.Launch();
        }
        private void FPSCBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = (ComboBox)sender;
            ConfigDomain.SetFramesPerSecond(Convert.ToInt32(cb.Text));
        }
        private void ConcurrentTickBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            ConfigDomain.SetParallel(cb.Checked);

            ThreadCountNUD.Enabled = cb.Checked;
        }

        private void MethodProfiling_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;
            ConfigDomain.SetMethodProfiling(cb.Checked);
        }

        private void CompilerOptimisationCB_SelectedIndexChanged(object sender, EventArgs e)
        {
            string optimisation = ((ComboBox)sender).Text;
            if (optimisation == "None")
            {
                Raytracer.SetArguments("");
            }
            else if(optimisation =="/O2: Maximum Running Speed")
            {
                Raytracer.SetArguments("O2");
            }
            else if (optimisation == "/Ox: Full Optimisation")
            {
                Raytracer.SetArguments("Ox");
            }
            else if (optimisation == "/Oy: Omit Frame Pointers")
            {
                Raytracer.SetArguments("Oy");
            }
            else
            {
                Raytracer.SetArguments(optimisation);
            }

        }

        private void BaselineCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = (CheckBox)sender;

            ConcurrentTickBox.Enabled = !cb.Checked;
            ThreadCountNUD.Enabled = !cb.Checked;
            ResCBox.Enabled = !cb.Checked;
            PhysicsTickBox.Enabled = !cb.Checked;
            FramesTB.Enabled = !cb.Checked;
            FPSCBox.Enabled = !cb.Checked;

            if (cb.Checked) Raytracer.SetArguments("baseline");
            else
            {
                if (CompilerOptimisationCB.Text == "None")
                {
                    Raytracer.SetArguments("");
                }
                else
                {
                    string s = CompilerOptimisationCB.Text;
                    Raytracer.SetArguments(CompilerOptimisationCB.Text);
                }
            }
        }


        private void DataGridView1_DataMemberChanged(object sender, System.EventArgs e)
        {
            DataGridView dgvSender = (DataGridView)sender;

            Console.WriteLine($"Data inputted = {dgvSender.DataMember}");
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }
    }
}
