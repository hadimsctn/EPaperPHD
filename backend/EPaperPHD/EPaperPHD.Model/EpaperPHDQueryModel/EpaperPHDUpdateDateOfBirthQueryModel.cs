﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model.EpaperPHDQueryModel
{
    public class EpaperPHDUpdateDateOfBirthQueryModel
    {
        public string DateOfBirth { get; set; } = string.Empty;
        public List<string> IdDevice { get; set; } = new List<string>();
    }
}
