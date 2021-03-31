/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - ChatClient.Form1.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChatClient
{
    public partial class Form1 : Form
    {
        SimpleClient _client;

        /**
         * Constructs the Form and Initialises data
         */
        public Form1(SimpleClient sClient)
        {
            InitializeComponent();
            _client = sClient;
            _client.SetForm(this);
        }

        /**
         *  Returns the Username
         *  
         * @return username as a string
         */
        public string GetUsername()
        {
            return tb_User.Text;
        }

        /**
         * Appends string which is called by its Delegate in the Invoke method call
         * 
         * @param string which is a message sent from a client to the server
        */
        public void AppendString(string text)
        {
            chatText.Text += text + "\n";
            chatText.SelectionStart = chatText.Text.Length;
            chatText.ScrollToCaret();
        }

        /**
         * Appends List of strings which is called by its Delegate in the Invoke method call
         * 
         * @param List of strings which is a Username list sent generated and sent from the server
        */
        public void AppendList(List<string> userList)
        {
            clientList.Text += Convert.ToString(userList);
            clientList.SelectionStart = clientList.Text.Length;
            clientList.ScrollToCaret();

        }

        /**
         * Checks for Button presses for sending a message
         * 
         * @param object which is a button and Event Argument
        */
        private void btnEnter_Click(object sender, EventArgs e)
        {
            _client.SendText(this.GetUsername() +": "+ textToSend.Text);
            textToSend.Clear();
        }
    }
}
