/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SharedLibrary.CHAT_MESSAGE.cs
 * 
 * @author: Ryan A. Buxton (b020612e)
 * @version: 0.1.1.0 26/11/2015
 ------------------------------------------------------------------ */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SharedLibrary
{
    [Serializable]
    public class CHAT_MESSAGE : PACKET
    {
        public string message = String.Empty;

        /**
         * Constructs the CHAT_MESSAGE Packet Class
         * 
         * @param string which is the chat message
         */
        public CHAT_MESSAGE(string message)
        {
            this.message = message;
            this.PACKET_TYPE = PACKET_TYPE_ENUM.CHAT_MESSAGE;
        }
    }
}
