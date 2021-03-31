/** -----------------------------------------------------------------
 * Concurrent Network Applications
 * Year 2, Semester 1, Assignment 1
 * Purpose: To Create a game with integrated Chat Server
 * 
 * Solution: ChatClient - SharedLibrary.USER_LIST.cs
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
    public class USER_LIST : PACKET
    {
        public List<String> userList = new List<String>();

        /**
         * Constructs the USER_LIST Packet Class
         * 
         * @param List of strings which is a list of usernames
         */
        public USER_LIST(List<String> userList)
        {
            this.userList = userList;
            this.PACKET_TYPE = PACKET_TYPE_ENUM.USER_LIST;
        }
    }
}
