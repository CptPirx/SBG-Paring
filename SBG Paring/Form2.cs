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

        public Form2()
        {
            InitializeComponent();

            sb = new OleDbConnectionStringBuilder();
            sb.Provider = "Microsoft.ACE.OLEDB.12.0";
            sb.DataSource = @"C:\Users\Błażej\Dropbox\LOTR SBG\Sędziówka pomorze\Gracze.accdb";
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
    }
}
