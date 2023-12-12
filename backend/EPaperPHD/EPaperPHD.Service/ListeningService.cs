using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using MQTTnet;

namespace EPaperPHD.Service
{
    public class ListeningService : BackgroundService
    {
        private readonly MqttFactory mqttFactory;
        private readonly IConfiguration configuration;
        public ListeningService(IConfiguration configuration)
    }
}
