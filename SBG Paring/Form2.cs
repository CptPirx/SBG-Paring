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

namespace SBG_Paring
{
    public partial class Form2 : Form
    {
        // Inicjalizacja połączenia z bazą graczy
        private OleDbConnection conn;
        private OleDbConnectionStringBuilder sb;

        //Czy wywołanie tego okna skończyło się wybraniem graczy
        public static bool dataChosen = false;

        Form1 f1;

        public Form2(Form1 form1)
        {
            InitializeComponent();
            this.f1 = form1;

            sb = new OleDbConnectionStringBuilder();
            sb.Provider = "Microsoft.ACE.OLEDB.12.0";
            sb.DataSource = @"D:\Dropbox\LOTR SBG\Sędziówka pomorze\Gracze.accdb";
            conn = new OleDbConnection(sb.ConnectionString);
            dataGridView1.DataSource = FillTable("SELECT * FROM Tabela1");
        }

        private DataTable FillTable(String sql)
        {
            DataTable table = new DataTable();
            using (OleDbDataAdapter da = new OleDbDataAdapter(sql, conn))
            {
                da.Fill(table);
            }
            return table;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                bool value;
                string teamName;

                foreach (DataGridViewRow row in dataGridView1.Rows)
                {
                    if (row.Cells[7].Value.Equals(true))
                    {
                        Player player = new Player(row.Cells[2].Value.ToString(), row.Cells[3].Value.ToString(), row.Cells[4].Value.ToString(), row.Cells[1].Value.ToString(), row.Cells[5].Value.ToString());
                        player.team = row.Cells[2].Value.ToString() + " " + row.Cells[3].Value.ToString();

                        Team team = new Team(player.team);
                        team.teamPlayers.Add(player);

                        //Dodaj gracz do listy graczy
                        Utility.teamList.Add(team);

                        //Dodaj gracza do tabelki pokazującej zapisanych graczy
                        ListViewItem item = new ListViewItem(player.name.ToString());
                        item.SubItems.Add(player.surname.ToString());
                        item.SubItems.Add(player.nick.ToString());
                        item.SubItems.Add(player.id.ToString());
                        item.SubItems.Add(player.region.ToString());
                        item.SubItems.Add(player.team.ToString());
                        f1.listView1.Items.Add(item);
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
