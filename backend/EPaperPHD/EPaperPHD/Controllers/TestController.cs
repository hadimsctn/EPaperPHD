using EPaperPHD.Controllers;
using EPaperPHD.Model;
using EPaperPHD.Model.Test;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Text;

namespace EPaperPHD.Web.Controllers
{
    [ApiController, Route("api/Test")]
    public class TestController : ControllerBase
    {
        private readonly IMqttServerService mqttServerService;

        public TestController(IMqttServerService mqttServerService)
        {
            this.mqttServerService = mqttServerService;
        }
        [HttpPost, Route("TestController/publisher")]
        public async Task<bool> PublishDatatoMQTTServer()
        {
            WeatherForecast weatherForecast = new WeatherForecast
            {
                TemperatureC = 25,
                Summary = "dsfs",
            };
            return await mqttServerService.PublishToMqttServer(weatherForecast,"EpaperPHD/UpdateAll", "broker.hivemq.com", 1883);
        }
        [HttpPost,Route("TestController/testData")]
        public async Task<IdentificationModel<EpaperPHDDisplayModel>> PublishDataDefault()
        {
            IdentificationModel<EpaperPHDDisplayModel> Response = new();
            EpaperPHDDisplayModel model = new EpaperPHDDisplayModel()
            {
                DateOfBirth = "12/08/2002",
                Name = "Name",
                Class = "Class",
                Major = "dsd",
            };
            IEnumerable<EpaperPHDDisplayModel> enumerableCollection = new List<EpaperPHDDisplayModel> { model };
            Response.IdDevice = "adsdfsaf";
            Response.Data = enumerableCollection;
            return Response;
        }
    }
}
