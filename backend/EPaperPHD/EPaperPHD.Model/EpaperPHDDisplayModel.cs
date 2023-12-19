using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model
{
    public class EpaperPHDDisplayModel
    {
        public string Name { get; set; } = string.Empty;
        public string DateOfBirth { get; set; } = string.Empty;
        public string Major { get; set; } = string.Empty;
        public string Class { get; set; } = string.Empty;
        public byte[]? ImageData { get; set; }
    }
}
