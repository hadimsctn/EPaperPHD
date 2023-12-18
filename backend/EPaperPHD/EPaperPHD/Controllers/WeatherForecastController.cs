using EPaperPHD.Model.Test;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Mvc;
using System.Text;

namespace EPaperPHD.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class WeatherForecastController : ControllerBase
    {
        private static readonly string[] Summaries = new[]
        {
            "Freezing", "Bracing", "Chilly", "Cool", "Mild", "Warm", "Balmy", "Hot", "Sweltering", "Scorching"
        };

        private readonly ILogger<WeatherForecastController> _logger;
        private readonly IMqttServerService mqttServerService;

        public WeatherForecastController(ILogger<WeatherForecastController> logger,IMqttServerService mqttServerService)
        {
            _logger = logger;
            this.mqttServerService = mqttServerService;
        }

        [HttpGet(Name = "GetWeatherForecast")]
        public IEnumerable<WeatherForecast> Get()
        { 
            return Enumerable.Range(1, 5).Select(index => new WeatherForecast
            {
                Date = DateTime.Now.AddDays(index),
                TemperatureC = Random.Shared.Next(-20, 55),
                Summary = Summaries[Random.Shared.Next(Summaries.Length)]
            })
            .ToArray();

        }
        [HttpPost(Name = "GetWeather")]
        public IActionResult GetFolders()
        {
            // Tạo cấu trúc thư mục
            Folder rootFolder = new Folder("Root");

            for (int i = 1; i <= 3; i++)
            {
                Folder subfolder = new Folder($"Subfolder {i}");

                for (int j = 1; j <= 3; j++)
                {
                    Folder nestedSubfolder = new Folder($"Nested Subfolder {i}.{j}");
                    subfolder.Subfolders.Add(nestedSubfolder);
                }

                rootFolder.Subfolders.Add(subfolder);
            }
            var result = mqttServerService.PublishToMqttServer(UTF8Encoding.UTF8.GetBytes(DateTime.Now.ToString("yyyyMMdd")), "esp32/test/hello/vietnamhaha/dateofbirth", "broker.hivemq.com", 1883);
            // Trả về dữ liệu JSON
            return Ok(rootFolder);
        }
    }
}
