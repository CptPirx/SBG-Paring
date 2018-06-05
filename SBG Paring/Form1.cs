using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SBG_Paring
{
    public partial class Form1 : Form
    {
        private ListViewColumnSorter lvwColumnSorter;

        DataGridView newGridView0 = new DataGridView();

        public Form1()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;

            lvwColumnSorter = new ListViewColumnSorter();
            this.listView1.ListViewItemSorter = lvwColumnSorter;
        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem.ToString() == "Solowy")
            {
                p2NameBox.Enabled = false;
                p2SurnameBox.Enabled = false;
                p2NickBox.Enabled = false;
                p2IdBox.Enabled = false;
                p2RegionBox.Enabled = false;

                p3NameBox.Enabled = false;
                p3SurnameBox.Enabled = false;
                p3NickBox.Enabled = false;
                p3IdBox.Enabled = false;
                p3RegionBox.Enabled = false;

                p4NameBox.Enabled = false;
                p4SurnameBox.Enabled = false;
                p4NickBox.Enabled = false;
                p4IdBox.Enabled = false;
                p4RegionBox.Enabled = false;

                TeamNameBox.Enabled = false;
                checkBox1.Enabled = false;
                checkBox2.Enabled = false;
            }
            if (comboBox1.SelectedItem.ToString() == "Parowy")
            {
                p2NameBox.Enabled = true;
                p2SurnameBox.Enabled = true;
                p2NickBox.Enabled = true;
                p2IdBox.Enabled = true;
                p2RegionBox.Enabled = true;

                p3NameBox.Enabled = false;
                p3SurnameBox.Enabled = false;
                p3NickBox.Enabled = false;
                p3IdBox.Enabled = false;
                p3RegionBox.Enabled = false;

                p4NameBox.Enabled = false;
                p4SurnameBox.Enabled = false;
                p4NickBox.Enabled = false;
                p4IdBox.Enabled = false;
                p4RegionBox.Enabled = false;

                TeamNameBox.Enabled = true;
                checkBox1.Enabled = true;
                checkBox2.Enabled = true;
            }
            if (comboBox1.SelectedItem.ToString() == "Drużyny 4 osobowe")
            {
                p2NameBox.Enabled = true;
                p2SurnameBox.Enabled = true;
                p2NickBox.Enabled = true;
                p2IdBox.Enabled = true;
                p2RegionBox.Enabled = true;

                p3NameBox.Enabled = true;
                p3SurnameBox.Enabled = true;
                p3NickBox.Enabled = true;
                p3IdBox.Enabled = true;
                p3RegionBox.Enabled = true;

                p4NameBox.Enabled = true;
                p4SurnameBox.Enabled = true;
                p4NickBox.Enabled = true;
                p4IdBox.Enabled = true;
                p4RegionBox.Enabled = true;

                TeamNameBox.Enabled = true;
                checkBox1.Enabled = true;
                checkBox2.Enabled = true;
            }
        }

        private void AddPlayer_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem.ToString() == "Solowy" && (p1NameBox.Text.Length > 0 || p1NickBox.Text.Length > 0))
            {
                Player player = new Player(p1NameBox.Text, p1SurnameBox.Text, p1NickBox.Text, p1IdBox.Text, p1RegionBox.Text);
                player.team = p1NameBox.Text + " " + p1SurnameBox.Text;

                Team team = new Team(player.team);
                team.teamPlayers.Add(player);

                bool alreadyExists = Utility.playerList.Any(x => x.name == p1NameBox.Text && x.surname == p1SurnameBox.Text && x.nick == p1NickBox.Text);

                if (alreadyExists == false)
                {
                    Utility.playerList.Add(player);
                    Utility.teamList.Add(team);

                    ListViewItem item = new ListViewItem(player.name.ToString());
                    item.SubItems.Add(player.surname.ToString());
                    item.SubItems.Add(player.nick.ToString());
                    item.SubItems.Add(player.id.ToString());
                    item.SubItems.Add(player.region.ToString());
                    item.SubItems.Add(player.team.ToString());
                    listView1.Items.Add(item);
                }
            }
            else if (comboBox1.SelectedItem.ToString() == "Parowy" && (p1NameBox.Text.Length > 0 || p1NickBox.Text.Length > 0) && (p2NameBox.Text.Length > 0 || p2NickBox.Text.Length > 0))
            {
                Player player1 = new Player(p1NameBox.Text, p1SurnameBox.Text, p1NickBox.Text, p1IdBox.Text, p1RegionBox.Text);
                player1.team = TeamNameBox.Text;
                Player player2 = new Player(p2NameBox.Text, p2SurnameBox.Text, p2NickBox.Text, p2IdBox.Text, p2RegionBox.Text);
                player2.team = TeamNameBox.Text;

                Team team = new Team(TeamNameBox.Text);
                team.teamPlayers.Add(player1);
                team.teamPlayers.Add(player2);

                bool alreadyExists = Utility.playerList.Any(x => x.team == TeamNameBox.Text);

                if (alreadyExists == false)
                {

                    Utility.playerList.Add(player1);
                    Utility.playerList.Add(player2);

                    Utility.teamList.Add(team);

                    ListViewItem item = new ListViewItem(player1.name.ToString());
                    item.SubItems.Add(player1.surname.ToString());
                    item.SubItems.Add(player1.nick.ToString());
                    item.SubItems.Add(player1.id.ToString());
                    item.SubItems.Add(player1.region.ToString());
                    item.SubItems.Add(player1.team.ToString());
                    listView1.Items.Add(item);

                    item = new ListViewItem(player2.name.ToString());
                    item.SubItems.Add(player2.surname.ToString());
                    item.SubItems.Add(player2.nick.ToString());
                    item.SubItems.Add(player2.id.ToString());
                    item.SubItems.Add(player2.region.ToString());
                    item.SubItems.Add(player2.team.ToString());
                    listView1.Items.Add(item);
                }
            }
            else if (comboBox1.SelectedItem.ToString() == "Drużyny 4 osobowe" && (p1NameBox.Text.Length > 0 || p1NickBox.Text.Length > 0) && (p2NameBox.Text.Length > 0 || p2NickBox.Text.Length > 0) && (p3NameBox.Text.Length > 0 || p3NickBox.Text.Length > 0) && (p4NameBox.Text.Length > 0 || p4NickBox.Text.Length > 0))
            {
                Player player1 = new Player(p1NameBox.Text, p1SurnameBox.Text, p1NickBox.Text, p1IdBox.Text, p1RegionBox.Text);
                player1.team = TeamNameBox.Text;
                Player player2 = new Player(p2NameBox.Text, p2SurnameBox.Text, p2NickBox.Text, p2IdBox.Text, p2RegionBox.Text);
                player2.team = TeamNameBox.Text;
                Player player3 = new Player(p3NameBox.Text, p3SurnameBox.Text, p3NickBox.Text, p3IdBox.Text, p3RegionBox.Text);
                player2.team = TeamNameBox.Text;
                Player player4 = new Player(p4NameBox.Text, p4SurnameBox.Text, p4NickBox.Text, p4IdBox.Text, p4RegionBox.Text);
                player2.team = TeamNameBox.Text;

                Team team = new Team(TeamNameBox.Text);
                team.teamPlayers.Add(player1);
                team.teamPlayers.Add(player2);
                team.teamPlayers.Add(player3);
                team.teamPlayers.Add(player4);


                bool alreadyExists = Utility.playerList.Any(x => x.team == TeamNameBox.Text);

                if (alreadyExists == false)
                {
                    Utility.playerList.Add(player1);
                    Utility.playerList.Add(player2);
                    Utility.playerList.Add(player3);
                    Utility.playerList.Add(player4);

                    Utility.teamList.Add(team);

                    ListViewItem item = new ListViewItem(player1.name.ToString());
                    item.SubItems.Add(player1.surname.ToString());
                    item.SubItems.Add(player1.nick.ToString());
                    item.SubItems.Add(player1.id.ToString());
                    item.SubItems.Add(player1.region.ToString());
                    item.SubItems.Add(player1.team.ToString());
                    listView1.Items.Add(item);

                    item = new ListViewItem(player2.name.ToString());
                    item.SubItems.Add(player2.surname.ToString());
                    item.SubItems.Add(player2.nick.ToString());
                    item.SubItems.Add(player2.id.ToString());
                    item.SubItems.Add(player2.region.ToString());
                    item.SubItems.Add(player2.team.ToString());
                    listView1.Items.Add(item);

                    item = new ListViewItem(player3.name.ToString());
                    item.SubItems.Add(player3.surname.ToString());
                    item.SubItems.Add(player3.nick.ToString());
                    item.SubItems.Add(player3.id.ToString());
                    item.SubItems.Add(player3.region.ToString());
                    item.SubItems.Add(player3.team.ToString());
                    listView1.Items.Add(item);

                    item = new ListViewItem(player4.name.ToString());
                    item.SubItems.Add(player4.surname.ToString());
                    item.SubItems.Add(player4.nick.ToString());
                    item.SubItems.Add(player4.id.ToString());
                    item.SubItems.Add(player4.region.ToString());
                    item.SubItems.Add(player4.team.ToString());
                    listView1.Items.Add(item);
                }
            }
            else
            {
                MessageBox.Show("Każdy gracz musi mieć imię lub pseudonim!", "Błąd",
                MessageBoxButtons.OK, MessageBoxIcon.Error,
                MessageBoxDefaultButton.Button1);
            }


            checkBox1.Checked = false;
            checkBox2.Checked = false;

            textBox5.Text = Utility.playerList.Count.ToString();
            textBox6.Text = Utility.teamList.Count.ToString();
        }

        //Sortowanie
        private void ListView1_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            // Determine if clicked column is already the column that is being sorted.
            if (e.Column == lvwColumnSorter.SortColumn)
            {
                // Reverse the current sort direction for this column.
                if (lvwColumnSorter.Order == SortOrder.Ascending)
                {
                    lvwColumnSorter.Order = SortOrder.Descending;
                }
                else
                {
                    lvwColumnSorter.Order = SortOrder.Ascending;
                }
            }
            else
            {
                // Set the column number that is to be sorted; default to ascending.
                lvwColumnSorter.SortColumn = e.Column;
                lvwColumnSorter.Order = SortOrder.Ascending;
            }

            // Perform the sort with these new sort options.
            this.listView1.Sort();
        }

        //Usuwanie
        private void ListView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (Keys.Delete == e.KeyCode)
            {
                foreach (ListViewItem listViewItem in ((ListView)sender).SelectedItems)
                {
                    listViewItem.Remove();
                    //Wyszukiwanie odpowiednich graczy i drużyn do usunięcia
                    var playerToDelete = Utility.playerList.SingleOrDefault(x => x.name == listViewItem.Text);
                    int index = Utility.teamList.FindIndex(f => f.name == playerToDelete.team);
                    Utility.playerList.Remove(playerToDelete);
                    Utility.teamList.RemoveAt(index);
                }

                textBox5.Text = Utility.playerList.Count.ToString();
                textBox6.Text = Utility.teamList.Count.ToString();
            }
        }

        private void CheckBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox1.Checked == true)
                TeamNameBox.Text = p1NickBox.Text + " + " + p2NickBox.Text;
            else
                TeamNameBox.Clear();
        }

        private void CheckBox2_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox2.Checked == true)
                TeamNameBox.Text = p1NameBox.Text + " " + p1SurnameBox.Text + " + " + p2NameBox.Text + " " + p2SurnameBox.Text;
            else
                TeamNameBox.Clear();
        }

        //Pierwsze losowanie = pierwsza bitwa
        private void AcceptButton_Click(object sender, EventArgs e)
        {
            //Okienko czy jesteś pewien
            if (MessageBox.Show("Czy jesteś pewien?", "Generacja paringów",
                MessageBoxButtons.YesNo, MessageBoxIcon.Question,
                MessageBoxDefaultButton.Button1) == DialogResult.Yes)
            {
                //Czyszczenie kart
                for (int i = 0; i < tabControl1.TabCount; i++)
                {
                    string tabToRemove = "Bitwa " + (i + 1).ToString();
                    tabControl1.TabPages.RemoveByKey(tabToRemove);
                }

                Utility.ClearData();

                //Tworzenie nowej bitwy
                Utility.battleCounter++;

                //Create a new TabPage
                var newTabPage = new TabPage()
                {
                    Text = "Bitwa 1",
                    Name = "Bitwa 1"
                };

                //Create a new Button

                var buttonDraw = new Button()
                {
                    Text = "Generuj paringi",
                    Left = 1060,
                    Top = 610,
                    Width = 124
                };

                if (Utility.battleCounter == numericUpDown1.Value)
                {
                    buttonDraw.Text = "Podsumowanie turnieju";
                    buttonDraw.Click += new EventHandler(ButtonFinish_click);
                }
                else
                {
                    //Assign dynamic handler for the Button's click event
                    buttonDraw.Click += new EventHandler(ButtonDraw_click);
                }

                //Add the Button to the tab page
                newTabPage.Controls.Add(buttonDraw);

                //Create a new Data Grid View
                newGridView0 = new DataGridView()
                {
                    Location = new Point(20, 20),
                    Height = 580,
                    Width = 1175,
                };

                newGridView0.CellEndEdit += new DataGridViewCellEventHandler(CellEdit_finished);

                var col0 = new DataGridViewTextBoxColumn();
                var col1 = new DataGridViewTextBoxColumn();
                var col2 = new DataGridViewTextBoxColumn();
                var col3 = new DataGridViewTextBoxColumn();
                var col4 = new DataGridViewTextBoxColumn();
                var col5 = new DataGridViewTextBoxColumn();

                col0.HeaderText = "Stół";
                col0.Name = "Column0";

                col1.HeaderText = "Gracz / Drużyna";
                col1.Name = "Column1";

                col2.HeaderText = "Suma VP";
                col2.Name = "Column2";

                col3.HeaderText = "Suma GP";
                col3.Name = "Column3";

                col4.HeaderText = "VP";
                col4.Name = "Column4";

                col5.HeaderText = "GP";
                col5.Name = "Column5";

                newGridView0.Columns.AddRange(new DataGridViewColumn[] { col0, col1, col2, col3, col4, col5 });

                //Add the DataGridView to the tab page
                newTabPage.Controls.Add(newGridView0);

                //Add the TabPage to the TabControl
                tabControl1.TabPages.Add(newTabPage);

                if (checkBoxFirstRandom.Checked == true)
                {
                    Utility.FirstDraw();

                    //Dodawanie graczy z listy
                    foreach (var item in Utility.sortedList)
                    {
                        String[] addRow = { item.table.ToString(), item.name, item.VP.ToString(), item.GP.ToString() };
                        newGridView0.Rows.Add(addRow);
                    }
                }
                else
                {

                    //Dodawanie graczy z listy
                    foreach (var item in Utility.teamList)
                    {
                        Utility.playerCounter++;
                        if (Utility.playerCounter > Utility.tableNumber * 2)
                            Utility.tableNumber++;
                        item.table = Utility.tableNumber;
                        String[] addRow = { item.table.ToString(), item.name, item.VP.ToString(), item.GP.ToString() };
                        newGridView0.Rows.Add(addRow);
                    }

                    //Dodanie przeciwników do historii 
                    foreach (var item in Utility.teamList)
                    {
                        var opponent = Utility.teamList.SingleOrDefault(x => x.table == item.table && item.name != x.name);
                        if (opponent != null)
                            item.pastOpponents.Add(opponent);
                    }

                    //Dodawanie pauzy
                    if (Utility.teamList.Count % 2 != 0)
                    {
                        var lastTeam = Utility.teamList.LastOrDefault();
                        var fakeOpponent = new Team("0987");
                        lastTeam.hasPaused = true;
                        lastTeam.pastOpponents.Add(fakeOpponent);
                    }
                }
            }
        }

        //Kliknięcie guzika losującego ponownie
        public void ButtonDraw_click(object sender, EventArgs e)
        {
            if ((Utility.teamList.Any(x => x.tempGP == -1 || x.tempVP == -1)))
            {
                List<Team> blankTeams = new List<Team>();
                blankTeams = Utility.teamList.Where(x => x.tempGP == -1 || x.tempVP == -1).ToList();
                foreach (var item in blankTeams)
                    MessageBox.Show(item.name + "posiada nieuzupełnione wartości GP i VP!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                Button buttonClicked = (Button)sender;

                //Sumowanie punktów
                foreach (var item in Utility.teamList)
                {
                    item.VP += item.tempVP;
                    item.tempVP = -1;
                    item.GP += item.tempGP;
                    item.tempGP = -1;
                }

                //Tworzenie nowej bitwy
                Utility.battleCounter++;
                Utility.playerCounter = 0;
                Utility.tableNumber = 1;

                //Create a new TabPage
                var newTabPage = new TabPage()
                {
                    Text = "Bitwa " + Utility.battleCounter,
                    Name = "Bitwa " + Utility.battleCounter
                };

                //Create a new Button

                var buttonDraw = new Button()
                {
                    Text = "Generuj paringi",
                    Left = 1060,
                    Top = 610,
                    Width = 124
                };

                if (Utility.battleCounter == numericUpDown1.Value)
                {
                    buttonDraw.Text = "Podsumowanie turnieju";
                    buttonDraw.Click += new EventHandler(ButtonFinish_click);
                }
                else
                {
                    //Assign dynamic handler for the Button's click event
                    buttonDraw.Click += new EventHandler(ButtonDraw_click);
                }

                //Add the Button to the tab page
                newTabPage.Controls.Add(buttonDraw);

                //Create a new Data Grid View
                newGridView0 = new DataGridView()
                {
                    Location = new Point(20, 20),
                    Height = 580,
                    Width = 1175
                };

                newGridView0.CellEndEdit += new DataGridViewCellEventHandler(CellEdit_finished);

                var col0 = new DataGridViewTextBoxColumn();
                var col1 = new DataGridViewTextBoxColumn();
                var col2 = new DataGridViewTextBoxColumn();
                var col3 = new DataGridViewTextBoxColumn();
                var col4 = new DataGridViewTextBoxColumn();
                var col5 = new DataGridViewTextBoxColumn();

                col0.HeaderText = "Stół";
                col0.Name = "Column0";

                col1.HeaderText = "Gracz / Drużyna";
                col1.Name = "Column1";

                col2.HeaderText = "Suma VP";
                col2.Name = "Column2";

                col3.HeaderText = "Suma GP";
                col3.Name = "Column3";

                col4.HeaderText = "VP";
                col4.Name = "Column4";

                col5.HeaderText = "GP";
                col5.Name = "Column5";

                newGridView0.Columns.AddRange(new DataGridViewColumn[] { col0, col1, col2, col3, col4, col5 });

                //Add the DataGridView to the tab page
                newTabPage.Controls.Add(newGridView0);

                //Add the TabPage to the TabControl
                tabControl1.TabPages.Add(newTabPage);

                Utility.Draw();

                //Dodawanie graczy z listy
                foreach (var item in Utility.sortedList)
                {
                    String[] addRow = { item.table.ToString(), item.name, item.VP.ToString(), item.GP.ToString() };
                    newGridView0.Rows.Add(addRow);
                }
            }

        }

        //Kliknięcie guzika posumowującego
        public void ButtonFinish_click(object sender, EventArgs e)
        {
            int spot = 1;

            if ((Utility.teamList.Any(x => x.tempGP == -1 || x.tempVP == -1)))
            {
                List<Team> blankTeams = new List<Team>();
                blankTeams = Utility.teamList.Where(x => x.tempGP == -1 || x.tempVP == -1).ToList();
                foreach (var item in blankTeams)
                    MessageBox.Show(item.name + "posiada nieuzupełnione wartości GP i VP!", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                //Sumowanie punktów
                foreach (var item in Utility.teamList)
                {
                    item.VP += item.tempVP;
                    item.tempVP = -1;
                    item.GP += item.tempGP;
                    item.tempGP = -1;
                }

                //Tworzenie nowej bitwy
                Utility.battleCounter++;

                //Create a new TabPage
                var newTabPage = new TabPage()
                {
                    Text = "Podsumowanie turnieju",
                };

                //Create a new Button

                var buttonSumUp = new Button()
                {
                    Text = "Generuj Excela",
                    Left = 1060,
                    Top = 610,
                    Width = 124
                };

                //Assign dynamic handler for the Button's click event
                //buttonDraw.Click += new EventHandler(buttonDraw_click);

                //Add the Button to the tab page
                newTabPage.Controls.Add(buttonSumUp);

                //Create a new Data Grid View
                var newGridView0 = new DataGridView()
                {
                    Location = new Point(20, 20),
                    Height = 580,
                    Width = 1175
                };

                var col0 = new DataGridViewTextBoxColumn();
                var col1 = new DataGridViewTextBoxColumn();
                var col2 = new DataGridViewTextBoxColumn();
                var col3 = new DataGridViewTextBoxColumn();
                var col4 = new DataGridViewTextBoxColumn();
                var col5 = new DataGridViewTextBoxColumn();

                col0.HeaderText = "Miejsce";
                col0.Name = "Column0";

                col1.HeaderText = "Gracz / Drużyna";
                col1.Name = "Column1";

                col2.HeaderText = "Suma VP";
                col2.Name = "Column2";

                col3.HeaderText = "Suma GP";
                col3.Name = "Column3";

                newGridView0.Columns.AddRange(new DataGridViewColumn[] { col0, col1, col2, col3 });

                //Add the DataGridView to the tab page
                newTabPage.Controls.Add(newGridView0);

                //Add the TabPage to the TabControl
                tabControl1.TabPages.Add(newTabPage);

                Utility.sortedList = Utility.teamList.OrderByDescending(a => a.VP).ThenByDescending(a => a.GP).ToList();

                //Dodawanie graczy z listy
                foreach (var item in Utility.sortedList)
                {
                    String[] addRow = { spot.ToString(), item.name, item.VP.ToString(), item.GP.ToString() };
                    newGridView0.Rows.Add(addRow);
                    spot++;
                }
            }

        }

        //Koniec edycji pola w datagridview
        public void CellEdit_finished(object sender, DataGridViewCellEventArgs e)
        {
            //foreach (var item in Utility.teamList)
            //{
            try
            {
                string value = newGridView0.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString();
                string teamName = newGridView0.Rows[e.RowIndex].Cells[1].Value.ToString();

                if (e.ColumnIndex == 4)
                {
                    Utility.teamList.SingleOrDefault(x => x.name == teamName).tempVP = Convert.ToInt32(value);
                }
                else if (e.ColumnIndex == 5)
                {
                    Utility.teamList.SingleOrDefault(x => x.name == teamName).tempGP = Convert.ToInt32(value);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine();
                Console.WriteLine("Press any key to continue");
                Console.ReadLine();
            }
            //}

        }

        //Zmiana ilości gier na turnieju
        private void NumericUpDown1_ValueChanged(object sender, EventArgs e)
        {
            if (numericUpDown1.Value > 0)
                acceptButton.Enabled = true;
            else
                acceptButton.Enabled = false;
        }
    }
}
