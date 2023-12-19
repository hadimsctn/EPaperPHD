using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model
{
    public sealed class IdentificationModel<T>
    {
        public string IdDevice { get; set; } = string.Empty;
        public IEnumerable<T> Data { get; set; } = null!;
    }
}
