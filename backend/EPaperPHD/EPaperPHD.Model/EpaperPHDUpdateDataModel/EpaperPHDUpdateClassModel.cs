using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model.EpaperPHDUpdateDataModel
{
    public class EpaperPHDUpdateClassModel
    {
        public string Class { get; set; } = string.Empty;
        public List<string> IdDevice { get; set; } = new List<string>();
    }
}
