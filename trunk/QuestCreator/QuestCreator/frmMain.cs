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

                string s = "[\n";

                for (int i = 1; i <= 1000; ++i )
                {
                    s +=        "\t{\n" +
		                            "\t\t\"quest\": \"Đây éo phải là câu hỏi số " + i + "?\",\n" +
                                    "\t\t\"answers\":\n" +
                                    "\t\t[\n" +
                                        "\t\t\t\"Câu trả lời số " + i + "-0\",\n" +
                                        "\t\t\t\"Câu trả lời số " + i + "-1\",\n" +
                                        "\t\t\t\"Câu trả lời số " + i + "-2\",\n" +
                                        "\t\t\t\"Câu trả lời số " + i + "-3\"\n" +
                                    "\t\t],\n" +
                                    "\t\t\"right\": " + (i%4) + "\n" + 
	                            "\t}";
                    if (i != 1000)
                    {
                        s += ",\n";
                    }
                    else
                    {
                        s += "\n";
                    }
                }

                s += "]";
                sw.Write(s);

                sw.Flush();
                sw.Close();
                MessageBox.Show("OK");
            }            
        }
    }
}
