/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - ChatClient.SimpleClient.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using SharedLibrary;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading;


namespace ChatClient
{
    class NotConnectedException : Exception
    {
        public NotConnectedException() : base("TcpClient not connected.")
        {}

        public NotConnectedException(string message) : base(message)
        {}
    }

    public class SimpleClient
    {
        private Form1 form;
        private Random rand = new Random();
        private string nickname;
        private TcpClient _tcpClient;
        private NetworkStream _stream;
        private BinaryWriter _writer;
        private BinaryReader _reader;

        /**
         * Constructs the SimpleClient Class
         */
        public SimpleClient()
        {
            _tcpClient = new TcpClient();
        }

        /**
         * Sets the form 
         * 
         * @param Form which is the Game-Server Interface
         */
        public void SetForm(Form1 form)
        {
            this.form = form;
            this.nickname = form.GetUsername();
        }

        /**
         * Sets the user's alias
         * 
         * @param nickname which is passed from the UI
         */
        public void SetNickname(string nickname)
        {
            this.nickname = nickname;
            NICKNAME_PACKET NICKNAME_PACKET = new NICKNAME_PACKET(this.nickname);
            SendPacket(NICKNAME_PACKET);
        }
        
        /**
         * Returns user's alias
         * 
         * @return A string which is the user's alias
         */
        public string GetNickname()
        {
            return this.nickname;
        }

        /**
         * Connects to the server
         * 
         * @param the hostname and port number from Program.cs
         * @return whether the connection is true or false
         */
        public bool Connect(string hostname, int port)
        {
            try
            {
                _tcpClient.Connect(hostname, port);
                _stream = _tcpClient.GetStream();
                _writer = new BinaryWriter(_stream, Encoding.UTF8);
                _reader = new BinaryReader(_stream, Encoding.UTF8);

                Thread thread = new Thread(new ThreadStart(ProcessServerResponse));
                thread.Start();
            }
            catch (Exception e)
            {
                OutputString("Exception: " + e.Message);
                return false;
            }
            return true;
        }       

        /**
         * Constantly running function which process incoming transmission and outputs it to the server
         */
        private void ProcessServerResponse()
        {
            int INCOMING_BYTES;

                while ((INCOMING_BYTES = _reader.ReadInt32()) != 0)
                {
                    byte[] bytes = _reader.ReadBytes(INCOMING_BYTES);
                    MemoryStream MEMORY_STREAM = new MemoryStream(bytes);
                    BinaryFormatter formatter = new BinaryFormatter();

                    PACKET RECEIVED_PACKET = formatter.Deserialize(MEMORY_STREAM) as PACKET;

                    switch (RECEIVED_PACKET.PACKET_TYPE)
                    {
                        case PACKET_TYPE_ENUM.CHAT_MESSAGE:
                            string message = ((CHAT_MESSAGE)RECEIVED_PACKET).message;
                            try
                            {
                                OutputString(message);
                            }
                            catch (Exception e)
                            {
                                OutputString("Exception:" + e.Message);
                            }
                            break;
                        case PACKET_TYPE_ENUM.USER_LIST:
                            List<string> userList = ((USER_LIST)RECEIVED_PACKET).userList;
                            OutputUserList(userList);
                            break;
                        default:
                            break;
                    }
                }
        }

        /**
         * Message is passed in and outputs the string using the form's invoke method
         *
         * @param message sent to the server from the client
         */
        private void OutputString(string x)
        {
            form.Invoke(new AppendStringDelegate(form.AppendString), new object[] { x });
        }

        /**
         * List of users is passed in and outputted to the form through the invoke method
         * 
         * @param List of users
         */
        private void OutputUserList(List<string> uList)
        {
            form.Invoke(new AppendListDelegate(form.AppendList), new object[] { uList });
        }

        /**
         * Sends text the server for clients to read
         * 
         * @param Message sent from Clients
         */
        public void SendText(string text)
        {
            if (!_tcpClient.Connected)
                return;

            CHAT_MESSAGE CHAT_MESSAGE_PACKET = new CHAT_MESSAGE(text);
            SendPacket(CHAT_MESSAGE_PACKET);
        }

        /**
         * Sends UserList from the server for clients to read
         * 
         * @param UserList formed from Clients
         */
        public void SendList(List<string> uList)
        {
            if (!_tcpClient.Connected)
                return;

            USER_LIST USER_LIST_PACKET = new USER_LIST(uList);
            SendPacket(USER_LIST_PACKET);
        }

        /**
         * Transmits a packet through the server
         * 
         * @param Packet being transmitted
         */
        public void SendPacket(PACKET PACKET_DATA)
        {
            MemoryStream MEMORY_STREAM = new MemoryStream();
            BinaryFormatter BINARY_FORMATTER = new BinaryFormatter();
            BINARY_FORMATTER.Serialize(MEMORY_STREAM, PACKET_DATA);
            byte[] BUFFER = MEMORY_STREAM.GetBuffer();

            _writer.Write(BUFFER.Length);
            _writer.Write(BUFFER);
            _writer.Flush();
        }

        /**
         * Delegate for Form Invoke method
         * 
         * @param Text to be displayed on the Form
         */
        private delegate void AppendStringDelegate(string text);

        /**
         * Delegate for Form Invoke method
         * 
         * @param UserList to be displayed on the Form
         */
        private delegate void AppendListDelegate(List<string> uList);
    }
}
