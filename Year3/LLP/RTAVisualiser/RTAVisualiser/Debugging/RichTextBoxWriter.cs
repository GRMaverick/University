using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RTAVisualiser.Debugging
{
    public class RichTextBoxWriter : System.IO.TextWriter
    {
        private RichTextBox TextBox { get; set; } = null;
        private StringBuilder Content { get; set; } = new StringBuilder();

        public RichTextBoxWriter(RichTextBox textbox)
        {
            this.TextBox = textbox;
        }

        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }

        public override void Write(char value)
        {
            base.Write(value);
            Content.Append(value);

            if (value != '\n')
                return;

            if(TextBox.InvokeRequired)
            {
                try
                {
                    TextBox.Invoke(new MethodInvoker(() => TextBox.AppendText(Content.ToString())));
                    TextBox.Invoke(new MethodInvoker(() => TextBox.ScrollToCaret()));
                }
                catch(Exception ex)
                {
                    Console.WriteLine($"RichTextBoxWriter.cs:42:- EXCEPTION CAUGHT: {ex.Message}");
                    return;
                }
            }
            else
            {
                // TextBox.Clear();
                TextBox.AppendText(Content.ToString());
            }
            Content.Clear();
        }

        public override void Write(string value)
        {
            base.Write(value);
            Content.Append(value);

            if (value.EndsWith("\n")) 
                return;

            if (TextBox.InvokeRequired)
            {
                try
                {
                    TextBox.Invoke(new MethodInvoker(() => TextBox.AppendText(Content.ToString())));
                    TextBox.Invoke(new MethodInvoker(() => TextBox.ScrollToCaret()));
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"ReportMapper.cs:179:- EXCEPTION CAUGHT: {ex.Message}");
                    return;
                }
            }
            else
            {
                TextBox.Clear();
                TextBox.AppendText(Content.ToString());
            }
            Content.Clear();
        }
    }
}
