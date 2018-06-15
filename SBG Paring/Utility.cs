using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SBG_Paring
{
    public static class Utility
    {
        public static List<Player> playerList = new List<Player>();
        public static List<Team> teamList = new List<Team>();
        public static List<Team> sortedList = new List<Team>();
        public static List<int> oldOpponentNumbers = new List<int>();

        public static Random rnd = new Random();

        public static int battleCounter = 0;
        public static int playerCounter = 0;
        public static int tableNumber = 1;

        //Pierwsze losowanie paringów
        public static void FirstDraw()
        {
            int opponentNumber = 0;

            tableNumber = 1;
            //Losowe sortowanie listy
            sortedList = teamList;
            Shuffle(sortedList);

            //Pierwszy gracz zawsze gra na pierwszym stole
            sortedList[0].table = tableNumber;

            //Sprawdzenie, czy jest nieparzysta ilość graczy, i pauza dla ostatniego możliwego
            if (sortedList.Count % 2 != 0)
            {
                for (int k = sortedList.Count - 1; k >= 0; --k)
                {
                    if (sortedList[k].hasPaused == false && sortedList[k].pastOpponents.Count < battleCounter)
                    {
                        sortedList[k].pauseNow = true;
                        sortedList[k].hasPaused = true;
                        var fakeOpponent = new Team("0987");
                        sortedList[k].pastOpponents.Add(fakeOpponent);
                        sortedList.SingleOrDefault(x => x.pauseNow == true).table = 1000;
                        sortedList.SingleOrDefault(x => x.pauseNow == true).pauseNow = false;
                        break;
                    }
                }
            }

            //Tworzenie par
            for (int i = 0; i < sortedList.Count; i++)
            {
                //Sprawdzenie, czy gracz nie ma już pary
                if (sortedList[i].pastOpponents.Count < battleCounter)
                {
                    //Losowanie numeru przeciwnika, dopóki nie będzie unikalny, i dopóki wylosowany gracz nie ma pauzy
                    do
                    {
                        opponentNumber = rnd.Next(1, sortedList.Count);
                    } while (oldOpponentNumbers.Any(x => x == opponentNumber) || i == opponentNumber || sortedList[opponentNumber].hasPaused == true);


                    sortedList[i].table = tableNumber;
                    sortedList[opponentNumber].table = tableNumber;
                    //Dodanie przeciwnika do historii
                    sortedList[i].pastOpponents.Add(sortedList[opponentNumber]);
                    sortedList[opponentNumber].pastOpponents.Add(sortedList[i]);

                    tableNumber++;
                    oldOpponentNumbers.Add(opponentNumber);
                }
            }

            sortedList = sortedList.OrderBy(a => a.table).ThenByDescending(a => a.VP).ToList();
        }

        //Kolejne losowania paringów
        public static void Draw()
        {
            tableNumber = 1;
            //Sortowanie listy graczy po VP, potem GP
            sortedList = teamList.OrderByDescending(a => a.VP).ThenByDescending(a => a.GP).ToList();

            //Pierwszy gracz zawsze gra na pierwszym stole
            sortedList[0].table = tableNumber;

            //Tworzenie par
            for (int i = 0; i < sortedList.Count; i++)
            {
                //Sprawdzenie, czy gracz nie ma już pary
                if (sortedList[i].pastOpponents.Count < battleCounter)
                {
                    //Sprawdzamy po kolei kolejnych graczy
                    for (int j = 0; j < sortedList.Count; j++)
                    {
                        //Kolejny gracz grał z aktualnie rozpatrywanym graczem, lub już ma parę
                        if (sortedList[j].pastOpponents.Any(x => x.name == sortedList[i].name) || sortedList[j].name == sortedList[i].name || sortedList[j].pastOpponents.Count >= battleCounter)
                        {

                        }
                        else
                        {
                            sortedList[i].table = tableNumber;
                            sortedList[j].table = tableNumber;
                            //Dodanie przeciwnika do historii
                            sortedList[i].pastOpponents.Add(sortedList[j]);
                            sortedList[j].pastOpponents.Add(sortedList[i]);

                            tableNumber++;
                            break;
                        }
                    }
                }
            }

            //Sprawdzenie, czy jest nieparzysta ilość graczy, i pauza dla ostatniego możliwego
            if (sortedList.Count % 2 != 0)
            {
                for (int k = sortedList.Count - 1; k >= 0; --k)
                {
                    if (sortedList[k].hasPaused == false && sortedList[k].pastOpponents.Count < battleCounter)
                    {
                        sortedList[k].pauseNow = true;
                        sortedList[k].hasPaused = true;
                        var fakeOpponent = new Team("0987");
                        sortedList[k].pastOpponents.Add(fakeOpponent);
                        sortedList.SingleOrDefault(x => x.pauseNow == true).table = 1000;
                        sortedList.SingleOrDefault(x => x.pauseNow == true).pauseNow = false;
                        break;
                    }
                }
            }


            sortedList = sortedList.OrderBy(a => a.table).ThenByDescending(a => a.VP).ToList();
        }

        //Wyczyść dane
        public static void ClearData()
        {
            //Czyszczenie przeciwników
            foreach (var item in playerList)
                item.pastOpponents.Clear();

            foreach (var item in teamList)
            {
                item.pastOpponents.Clear();
                item.GP = 0;
                item.VP = 0;
            }

            battleCounter = 0;
            playerCounter = 0;
            tableNumber = 1;
        }

        //Losowe ułożenie listy
        public static void Shuffle<T>(this IList<T> list)
        {
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = rnd.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }

    }
}
