using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace QuestCreator
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();

            if (dialog.ShowDialog(this) != DialogResult.Cancel)
            {
                string fileName = dialog.FileName;

                FileStream fs = new FileStream(fileName, FileMode.Create);
                StreamWriter sw = new StreamWriter(fs);

                string s = 
"<plist version=\"1.0\">\n" +
"<dict>\n";
                sw.Write(s);

                for (int i = 1; i <= 1000; ++i )
                {
                    s =
    "\t<key>" + i +"</key>\n" +
    "\t<dict>\n" +
        "\t\t<key>quest</key>\n" +
        "\t\t<string>" + "Câu hỏi số " + i + "</string>\n" +
        "\t\t<key>a</key>\n" +
        "\t\t<string>Đáp án a</string>\n" +
        "\t\t<key>b</key>\n" +
        "\t\t<string>Đán án b</string>\n" +
        "\t\t<key>c</key>\n" +
        "\t\t<string>Đáp án c</string>\n" +
        "\t\t<key>d</key>\n" +
        "\t\t<string>Đáp án e</string>\n" +
        "\t\t<key>answer</key>\n" +
        "\t\t<string>" + ( i % 4) + "</string>\n" +
    "\t</dict>\n";

                    sw.Write(s);
                }

                s =
"</dict>\n" +
"</plist>";
                sw.Write(s);

                sw.Flush();
                sw.Close();
                MessageBox.Show("OK");
            }            
        }
    }
}
