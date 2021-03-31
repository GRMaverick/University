/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SharedLibrary.PACKET_TYPE_ENUM.cs
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
    /// <summary>
    /// Enum to check which type of packet is being transmitted across the server
    /// </summary>
    public enum PACKET_TYPE_ENUM
    {
        EMPTY,
        NICKNAME,
        CHAT_MESSAGE,
        USER_LIST,
    }
}
