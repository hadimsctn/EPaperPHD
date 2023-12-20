using EPaperPHD.Model;
using EPaperPHD.Model.EpaperPHDQueryModel;
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

    }
}
