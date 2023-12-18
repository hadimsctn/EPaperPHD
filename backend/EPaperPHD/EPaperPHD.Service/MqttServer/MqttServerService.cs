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
        public MqttServerService()
        {
            
        }
        public async Task<bool> PublishToMqttServer(byte[] bytes, string topic, string broker, double port)
        {
            try
            {
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                .WithClientId("2023")
                .WithTcpServer(broker, ((int)port))
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
                Console.WriteLine(ex.ToString());
            }
            return true;
        }
        public async Task<string> SubcribeMqttServer()
        {
            var mqttFactory = new MqttFactory();
            IMqttClient client = mqttFactory.CreateMqttClient();
            var options = new MqttClientOptionsBuilder()
            .WithClientId("2023")
            .WithTcpServer("broker.hivemq.com", 1883)
                .WithCleanSession()
                .Build();
            var connectResult = await client.ConnectAsync(options);
            if (connectResult.ResultCode == MqttClientConnectResultCode.Success) { }
        }
    }
}
