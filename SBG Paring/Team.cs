using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SBG_Paring
{
    public class Team
    {
        public String name;
        public int VP = 0, GP = 0, tempVP = 0, tempGP = 0, table;
        public bool pauseNow, hasPaused;

        public List<Team> pastOpponents = new List<Team>();
        public List<Player> teamPlayers = new List<Player>();

        public Team(String name)
        {
            this.name = name;
        }
    }
}
