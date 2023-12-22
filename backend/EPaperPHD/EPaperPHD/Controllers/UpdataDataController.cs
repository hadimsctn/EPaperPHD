using EPaperPHD.Model;
using EPaperPHD.Model.EpaperPHDQueryModel;
using EPaperPHD.Model.EpaperPHDUpdateDataModel;
using EPaperPHD.Service.Intention;
using Microsoft.AspNetCore.Mvc;

namespace EPaperPHD.Web.Controllers
{
    [ApiController, Route("api/Update")]
    public class UpdataDataController : ControllerBase
    {
        private readonly IUpdateDataService updateDataService;

        public UpdataDataController(IUpdateDataService updateDataService)
        {
            this.updateDataService = updateDataService;
        }
        [HttpPut,Route("UpdateName")]
        public async Task<bool> UpdateName(EpaperPHDUpdateNameQueryModel queryModel)
        {
            return await updateDataService.UpdateDataName(queryModel);
        }
        [HttpPut, Route("UpdateDateOfBirth")]
        public async Task<bool> UpdateDateOfBirth(EpaperPHDUpdateDateOfBirthQueryModel queryModel)
        {
            return await updateDataService.UpdateDateOfBirth(queryModel);
        }
        [HttpPut, Route("UpdateMajor")]
        public async Task<bool> UpdateMajor(EpaperPHDUpdateMajorQueryModel queryModel)
        {
            return await updateDataService.UpdateMajor(queryModel);
        }
        [HttpPut, Route("UpdateClass")]
        public async Task<bool> UpdateClass(EpaperPHDUpdateClassQueryModel queryModel)
        {
            return await updateDataService.UpdateClass(queryModel);
        }
        [HttpPost, Route("UpdateImage")]
        public async Task<bool> UpdateImage([FromForm]EpaperPHDUpdateImageQueryModel queryModel)
        {
            return await updateDataService.UpdateImage(queryModel);
        }
    }
}
