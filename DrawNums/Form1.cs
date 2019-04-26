
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace DrawNums
{
    public partial class Form1 : Form
    {
        double[] o;
        [DllImport("E:\\CNN_ITMM\\x64\\Debug\\DeepNetworkLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Neyroset(double[] ooo);
        [DllImport("E:\\CNN_ITMM\\x64\\Debug\\DeepNetworkLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void startNeyroset();
        [DllImport("E:\\CNN_ITMM\\x64\\Debug\\DeepNetworkLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Set(int i, int j);

        public Form1()
        {
            o = new double[15];
            for(int i = 0; i < 10; i++)
            {
                o[i] = -1;
            }
            InitializeComponent();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            ((PictureBox)sender).BackColor = Color.FromArgb(255, 255, 255);
            int i = (((PictureBox)sender).Location.X - 230)/46;
            i += (((PictureBox)sender).Location.Y - 38) / 46 * 3;
            o[i] = 1;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Neyroset(o);
        }
    }
}
