using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model.EpaperPHDQueryModel
{
    public class EpaperPHDUpdateImageQueryModel
    {
        public string IdDevice { get; set; } = string.Empty;
        public IFormFile? Image { get; set; }
    }
}
