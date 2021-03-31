/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SharedLibrary.NICKNAME_PACKET.cs
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
    public class NICKNAME_PACKET : PACKET
    {
        public string nickname = String.Empty;

        /**
         * Constructs the NICKNAME_PACKET Packet Class
         * 
         * @param string which is the nickname
         */
        public NICKNAME_PACKET(string nickname)
        {
            this.nickname = nickname;
            this.PACKET_TYPE = PACKET_TYPE_ENUM.NICKNAME;
        }
    }
}
