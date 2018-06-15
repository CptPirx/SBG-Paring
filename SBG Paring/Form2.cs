using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Data.SqlClient;

namespace SBG_Paring
{
    public partial class Form2 : Form
    {
        // Inicjalizacja połączenia z bazą graczy
        //private OleDbConnection conn;
        //private OleDbConnectionStringBuilder sb;

        //Czy wywołanie tego okna skończyło się wybraniem graczy
        public static bool dataChosen = false;

        Form1 f1;

        public Form2(Form1 form1)
        {
            InitializeComponent();
            this.f1 = form1;

            String DATA = Application.StartupPath + @"\Gracze.mdf";
            string constring = @"Data Source=(LocalDB)\mssqllocaldb;AttachDbFilename=" + DATA + ";Integrated Security=True";

            SqlConnection conDataBase = new SqlConnection(constring);
            SqlCommand cmdDataBase = new SqlCommand("Select * From [Table]", conDataBase);
            try
            {
                SqlDataAdapter sda = new SqlDataAdapter();
                sda.SelectCommand = cmdDataBase;
                DataTable dbdataset = new DataTable();
                sda.Fill(dbdataset);
                BindingSource bSource = new BindingSource();

                bSource.DataSource = dbdataset;
                dataGridView1.DataSource = bSource;
                sda.Update(dbdataset);
            }
            catch (Exception uu)
            {
                MessageBox.Show(uu.Message);
            }

            //sb = new OleDbConnectionStringBuilder();
            //sb.Provider = "Microsoft.ACE.OLEDB.12.0";
            //sb.DataSource = Application.StartupPath + @"\Resources\Gracze.accdb";
            //conn = new OleDbConnection(sb.ConnectionString);
            //dataGridView1.DataSource = FillTable("SELECT * FROM Tabela1");
        }
        //Wypełnianie tabeli danymi z bazy danych
        //private DataTable FillTable(String sql)
        //{
        //    DataTable table = new DataTable();
        //    using (OleDbDataAdapter da = new OleDbDataAdapter(sql, conn))
        //    {
        //        da.Fill(table);
        //    }
        //    return table;
        //}

        //Kliknięcie guzika "ok"
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    if (row.Cells[7].Value.Equals(true))
                    {
                        Player player = new Player(row.Cells[2].Value.ToString(), row.Cells[3].Value.ToString(), row.Cells[4].Value.ToString(), row.Cells[1].Value.ToString(), row.Cells[5].Value.ToString());
                        player.team = row.Cells[2].Value.ToString() + " " + row.Cells[3].Value.ToString();

                        Team team = new Team(player.team);
                        team.teamPlayers.Add(player);

                        bool alreadyExists = Utility.playerList.Any(x => x.name == player.name && x.surname == player.surname && x.nick == player.nick);

                        if (alreadyExists == false)
                        {
                            //Dodaj gracz do listy graczy
                            Utility.playerList.Add(player);
                            Utility.teamList.Add(team);

                            //Dodaj gracza do tabelki pokazującej zapisanych graczy
                            ListViewItem item = new ListViewItem(player.name.ToString());
                            item.SubItems.Add(player.surname.ToString());
                            item.SubItems.Add(player.nick.ToString());
                            item.SubItems.Add(player.id.ToString());
                            item.SubItems.Add(player.region.ToString());
                            item.SubItems.Add(player.team.ToString());
                            f1.listView1.Items.Add(item);

                            //Zaktualizuj liczbę graczy na turnieju
                            f1.textBox5.Text = Utility.playerList.Count.ToString();
                            f1.textBox6.Text = Utility.teamList.Count.ToString();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine();
                Console.WriteLine("Press any key to continue");
                Console.ReadLine();
            }

            dataChosen = true;
            this.Close();
        }
    }
}
