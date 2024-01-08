using EPaperPHD.Model.Configuration;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using MQTTnet;
using MQTTnet.Client;
using Newtonsoft.Json;
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
        private readonly MqttConfiguration mqttConfiguration;
        public MqttServerService(ILogger<MqttServerService> logger, IOptionsMonitor<MqttConfiguration> mqttConfiguration)
        {
            this.logger = logger;
            this.mqttConfiguration = mqttConfiguration.CurrentValue;
        }
        public async Task<bool> PublishToMqttServer(object data,string topic)
        {
            try
            {
                logger.LogInformation("Start publish data to Mqtt Server");
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                .WithClientId(Guid.NewGuid().ToString())
                .WithTcpServer(mqttConfiguration.Broker, mqttConfiguration.Port)
                .WithCredentials("nguyenha","12345678")
                    .WithCleanSession()
                    .Build();
                var connectResult = await client.ConnectAsync(options);

                // Chuyển đối tượng thành JSON
                var jsonData = JsonConvert.SerializeObject(data);             
                var applicationMessage = new MqttApplicationMessageBuilder()
                .WithTopic(topic)
                .WithPayload(Encoding.UTF8.GetBytes(jsonData))
                .Build();
                await client.PublishAsync(applicationMessage, CancellationToken.None);
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return true;
        }
        public async Task<bool> PublishImageToMqttServer(byte[] image,object data, string topic)
        {
            try
            {
                logger.LogInformation("Start publish data to Mqtt Server");
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                .WithClientId(Guid.NewGuid().ToString())
                .WithTcpServer(mqttConfiguration.Broker, mqttConfiguration.Port)
                .WithCredentials("nguyenha", "12345678")
                    .WithCleanSession()
                    .Build();
                var connectResult = await client.ConnectAsync(options);
                // Chuyển đối tượng thành JSON
                var jsonData = JsonConvert.SerializeObject(data);
                var applicationMessage = new MqttApplicationMessageBuilder()
                .WithTopic(topic)
                .WithPayload(Encoding.UTF8.GetBytes(jsonData).Concat(image))
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
