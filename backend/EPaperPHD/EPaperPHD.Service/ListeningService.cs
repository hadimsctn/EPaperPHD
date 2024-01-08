using EPaperPHD.Model.Configuration;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Server;

namespace EPaperPHD.Service
{
    public class ListeningService : BackgroundService
    {
        private readonly ILogger<ListeningService> logger;
        private readonly MqttConfiguration mqttConfiguration;

        public ListeningService(ILogger<ListeningService> logger, IOptionsMonitor<MqttConfiguration> mqttConfiguration)
        {
            this.logger = logger;
            this.mqttConfiguration = mqttConfiguration.CurrentValue;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            try
            {
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                    .WithClientId(Guid.NewGuid().ToString())
                    .WithTcpServer(mqttConfiguration.Broker, mqttConfiguration.Port)
                    .WithCredentials("nguyenha", "12345678")
                    .WithCleanSession()
                    .Build();
                var connectResult = await client.ConnectAsync(options);
                if (connectResult.ResultCode == MqttClientConnectResultCode.Success)
                {
                    logger.LogInformation("Connected mqtt Server");
                    await client.SubscribeAsync("EpaperPHD");

                    // Callback function when a message is received
                    client.ApplicationMessageReceivedAsync += e =>
                    {
                        logger.LogInformation($"Received message: {System.Text.Encoding.UTF8.GetString(e.ApplicationMessage.PayloadSegment)}");
                        return Task.CompletedTask;
                    };
                }
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }


        }
    }
}
