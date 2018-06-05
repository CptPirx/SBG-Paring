using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SBG_Paring
{
    public class Player
    {
        public String name, surname, nick, id, region, team;

        public List<Player> pastOpponents = new List<Player>();

        public Player(String name, String surname, String nick, String id, String region)
        {
            this.name = name;
            this.surname = surname;
            this.nick = nick;
            this.id = id;
            this.region = region;
        }
    }
}
