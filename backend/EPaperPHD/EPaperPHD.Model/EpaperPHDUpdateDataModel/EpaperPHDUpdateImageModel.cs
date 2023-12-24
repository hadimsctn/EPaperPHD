using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model.EpaperPHDUpdateDataModel
{
    public class EpaperPHDUpdateImageModel
    {
        public List<string> IdDevice { get; set; } = new List<string>();
        public int ImageLength { get; set; }
    }
}
