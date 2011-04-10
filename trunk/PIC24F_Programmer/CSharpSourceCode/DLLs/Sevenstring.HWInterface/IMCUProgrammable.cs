using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace Sevenstring.HWInterface
{
    public interface IMCUProgrammable
    {
        ulong ? ReadDeviceID();
        bool Erase();
        bool Program(string FileName, TextBox textBox);

    }
}
