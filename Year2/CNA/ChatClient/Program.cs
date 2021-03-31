/**
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1 26/11/2015
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    static class Program
    {

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {            
             string _hostString = "127.0.0.1";
             int _portNo = 4444;

             Application.EnableVisualStyles();
             Application.SetCompatibleTextRenderingDefault(false);

            SimpleClient sClient = new SimpleClient();
            Form1 form = new Form1(sClient);

            sClient.Connect(_hostString, _portNo);

            Application.Run(form);
        }
    }
}
