using EPaperPHD.Model.EpaperPHDQueryModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service.Intention
{
    public interface IUpdateDataService
    {
        Task<bool> UpdateDataName(EpaperPHDUpdateNameQueryModel queryModel);
        Task<bool> UpdateDateOfBirth(EpaperPHDUpdateDateOfBirthQueryModel queryModel);
        Task<bool> UpdateMajor(EpaperPHDUpdateMajorQueryModel queryModel);
        Task<bool> UpdateClass(EpaperPHDUpdateClassQueryModel queryModel);
    }
}
