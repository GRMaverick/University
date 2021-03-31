using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RTAVisualiser.Threading
{
    public class WorkerClass
    {
        public delegate void WorkToCompleteHandler();
        public delegate void WorkCompleteHandler();

        public event WorkCompleteHandler OnWorkComplete;
        public event WorkToCompleteHandler WorkToComplete;
        public int ID { get; set; }

        public WorkerClass(int id)
        {
            ID = id;
        }
        public void Start()
        {
            ThreadPool.QueueUserWorkItem(new WaitCallback(ThisWork));
        }
        private void ThisWork(object stateInformation)
        {
            this.WorkToComplete?.Invoke();
            this.OnWorkComplete?.Invoke();
        }
    }
}
