/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SimpleServer.Client.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using SharedLibrary;

namespace SimpleServerCS
{
    public class Client
    {
        public Socket socket;
        public string ID;

        private string nickname;
        public NetworkStream  NET_STREAM;
        public BinaryReader BIN_READER;
        public BinaryWriter BIN_WRITER;
        private Thread _threadSocketMethod;
        
        /**
         *  Constructs the Client Class
         *  
         * @param Socket which is the TCP Server Listener
         */
        public Client(Socket socket)
        {
            ID = Guid.NewGuid().ToString();
            this.socket = socket as Socket;
            NET_STREAM = new NetworkStream(socket);
            BIN_READER = new BinaryReader(NET_STREAM, Encoding.UTF8);
            BIN_WRITER = new BinaryWriter(NET_STREAM, Encoding.UTF8);
        }
    
        /**
         * Sets the Nickname from NICKNAME_PACKET
         * 
         * @param Nickname string which is sent from NICKNAME_PACKET
         */
        public void SetNickname(string nickname)
        {
            this.nickname = nickname;
        }

        /**
         * Returns the nickname
         * 
         * @return nickname which is a string
         */
        public string GetNickname()
        {
            return nickname;
        }

        /**
         * Initiates the Socket Thread
         */
        public void Start()
        {
            _threadSocketMethod = new Thread(new ThreadStart(SocketMethod));
            _threadSocketMethod.Start();
        }

        /**
         * Kills the Socket Thread
         */
        public void Stop()
        {
            socket.Close();
            if (_threadSocketMethod.IsAlive)
                _threadSocketMethod.Abort();
        }

        /**
         * The Socket Method that will be executed on the thread
         */
        private void SocketMethod()
        {
            SimpleServer.SocketMethod(this);
        }

        /**
         * Sends text as a packet
         * 
         * @param Message which is a string sent to server
         */
        public void SendText(string text)
        {
            if (!socket.Connected)
                return;

            CHAT_MESSAGE CHAT_MESSAGE_PACKET = new CHAT_MESSAGE(text);
            SendPacket(CHAT_MESSAGE_PACKET);
        }

        /**
         * Sends List as a packet
         * 
         * @param UserList which is a list sent to server
         */
        public void SendList(List<string> uList)
        {
            if (!socket.Connected)
                return;

            USER_LIST USER_LIST_PACKET = new USER_LIST(uList);
            SendPacket(USER_LIST_PACKET);
        }

        /**
         * Serialises the Packet for transmission across the network
         */
        public void SendPacket(PACKET PACKET_DATA)
        {
            MemoryStream MEMORY_STREAM = new MemoryStream();
            BinaryFormatter BINARY_FORMATTER = new BinaryFormatter();
            BINARY_FORMATTER.Serialize(MEMORY_STREAM, PACKET_DATA);
            byte[] BUFFER = MEMORY_STREAM.GetBuffer();

            BIN_WRITER.Write(BUFFER.Length);
            BIN_WRITER.Write(BUFFER);
            BIN_WRITER.Flush();
        }
    }
}
