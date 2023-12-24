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
        public List<string> IdDevice { get; set; } = new List<string>();
        public IFormFile? Image { get; set; }
    }
}
