using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RTAVisualiser.Debugging
{
    public class MultiTextWriter : System.IO.TextWriter
    {
        private IEnumerable<System.IO.TextWriter> writers { get; set; } = null;

        public MultiTextWriter(IEnumerable<System.IO.TextWriter> writers)
        {
            this.writers = writers.ToList();
        }
        public MultiTextWriter(params System.IO.TextWriter[] writers)
        {
            this.writers = writers;
        }

        public override void Write(char value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        public override void Write(string value)
        {
            foreach (var writer in writers)
                writer.Write(value);
        }

        public override void Flush()
        {
            foreach (var writer in writers)
                writer.Flush();
        }

        public override void Close()
        {
            foreach (var writer in writers)
                writer.Close();
        }

        public override Encoding Encoding
        {
            get { return Encoding.ASCII; }
        }
    }
}
