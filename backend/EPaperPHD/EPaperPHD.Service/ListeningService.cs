using EPaperPHD.Model.Configuration;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using MQTTnet.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service
{
    public class ListeningService : BackgroundService
    {
        private readonly MqttClient mqttClient;
        private readonly ILogger<ListeningService> logger;
        private readonly IConfiguration configuration;
        private readonly MqttConfiguration mqttConfiguration;
        
        public ListeningService(MqttClient mqttClient, ILogger<ListeningService> logger, IConfiguration configuration,IOptionsMonitor<MqttConfiguration> mqttConfiguration)
        {
            this.mqttClient = mqttClient;
            this.logger = logger;
            this.configuration = configuration;
            this.mqttConfiguration = mqttConfiguration.CurrentValue;
        }
        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                var broker = mqttConfiguration.Broker;
                var port = mqttConfiguration.Port;
                logger.LogInformation("Connect Start" + broker + "/" + port);
                var mqttClientOptions = new MqttClientOptionsBuilder()
                .WithTcpServer(broker, port)
                .Build();
                var a = await mqttClient.ConnectAsync(mqttClientOptions, CancellationToken.None);
                Console.WriteLine(a.ToString());
                await Task.Delay(1000, stoppingToken);
            }
        }   
    }
}
