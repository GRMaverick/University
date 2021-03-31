/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SimpleServer.SimpleServer.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using System;
using SharedLibrary;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;

namespace SimpleServerCS
{
    class SimpleServer
    {
        TcpListener _tcpListener;

        private static List<Client> _clients = new List<Client>();
        private static List<string> _userList = new List<string>();

        private static NetworkStream NET_STREAM;
        private static BinaryReader BIN_READER;
        private static BinaryWriter BIN_WRITER;

        /**
         * Constructs the SimpleServer class
         * 
         * @param IP Address which is a string and Port Number sent from Program.cs
         */
        public SimpleServer(string ipAddress, int port)
        {
            IPAddress ip = IPAddress.Parse(ipAddress);
            _tcpListener = new TcpListener(ip, port);
        }

        /**
         * Starts the server
         */
        public void Start()
        {
            _tcpListener.Start();
            
            Console.WriteLine("Listening...");
            while(true)
            {
                Socket socket = _tcpListener.AcceptSocket();
                Client client = new Client(socket);
                _clients.Add(client);
                _userList.Add(client.GetNickname());
                client.Start();
            }
        }

        /**
         * Kills the Server
         */
        public void Stop()
        {
            _tcpListener.Stop();
            foreach (Client c in _clients)
            {
                c.Stop();
                _userList.Remove(c.GetNickname());
            }
        }

        /**
         * Deserialises the Packets received from clients and operates on them
         * 
         * @param Client which is sent from Client.cs
         */
        public static void SocketMethod(Client client)
        {
            try
            {
                client.SendText("Welcome User: Enter '/clientend' to terminate Chatroom \n");
                int INCOMING_BYTES;

                while ((INCOMING_BYTES = client.BIN_READER.ReadInt32()) != 0)
                {
                    byte[] bytes = client.BIN_READER.ReadBytes(INCOMING_BYTES);
                    MemoryStream MEMORY_STREAM = new MemoryStream(bytes);
                    BinaryFormatter formatter = new BinaryFormatter();

                    PACKET RECEIVED_PACKET = formatter.Deserialize(MEMORY_STREAM) as PACKET;

                    switch (RECEIVED_PACKET.PACKET_TYPE)
                    {
                        case PACKET_TYPE_ENUM.NICKNAME:
                            string nickname = ((NICKNAME_PACKET)RECEIVED_PACKET).nickname;
                            client.SetNickname(nickname);
                            break;
                        case PACKET_TYPE_ENUM.CHAT_MESSAGE:
                            string message = client.GetNickname() + ((CHAT_MESSAGE)RECEIVED_PACKET).message;
                            foreach (Client c in _clients)
                            {
                                if (message != "/clientend")
                                    c.SendText(message);
                                else if (message == "/clientend")
                                    c.Stop();
                            }
                            break;
                        case PACKET_TYPE_ENUM.USER_LIST:
                            List<string> uList = ((USER_LIST)RECEIVED_PACKET).userList;
                            client.SendList(uList);
                            break;
                        default:
                            break;
                    }
                }
             }
            catch (Exception e)
            {
                Console.WriteLine("Error occured: " + e.Message);
            }
            finally
            {
                client.Stop();
            }
        }
    }
}