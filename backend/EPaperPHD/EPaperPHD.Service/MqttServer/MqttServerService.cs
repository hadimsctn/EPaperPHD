using EPaperPHD.Model.Configuration;
using Microsoft.Extensions.Logging;
using MQTTnet;
using MQTTnet.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service.MqttServer
{
    public class MqttServerService : IMqttServerService
    {
        private readonly ILogger<MqttServerService> logger;
        public MqttServerService(ILogger<MqttServerService> logger)
        {
            this.logger = logger;
        }
        public async Task<bool> PublishToMqttServer(byte[] bytes, string topic, string broker, double port)
        {
            try
            {
                logger.LogInformation("Start publish data to Mqtt Server");
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                .WithClientId(Guid.NewGuid().ToString())
                .WithTcpServer(broker, (int)port)
                    .WithCleanSession()
                    .Build();
                var connectResult = await client.ConnectAsync(options);
                var applicationMessage = new MqttApplicationMessageBuilder()
                .WithTopic(topic)
                .WithPayload(bytes)
                .Build();
                await client.PublishAsync(applicationMessage, CancellationToken.None);
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return true;
        }
    }
}
