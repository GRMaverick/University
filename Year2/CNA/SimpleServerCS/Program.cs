/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SimpleServer.Program.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SimpleServerCS
{
    
    class Program
    {
        /// <summary>
        ///  Entry point to Server
        /// </summary>
        static void Main(string[] args)
        {
            SimpleServer _simpleServer = new SimpleServer("127.0.0.1", 4444);

            _simpleServer.Start();

            _simpleServer.Stop();
        }
    }
}
