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
        public readonly MqttFactory mqttFactory;
        public readonly MqttClient mqttClient;
        public MqttServerService(MqttFactory mqttFactory, MqttClient mqttClient)
        {
            this.mqttFactory = mqttFactory;
            this.mqttClient = mqttClient;
        }
        public async Task<bool> PublishToMqttServer(byte[] bytes, string topic, string broker, double port)
        {
            try
            {
                var applicationMessage = new MqttApplicationMessageBuilder()
                .WithTopic(topic)
                .WithPayload(bytes)
                .Build();
                await mqttClient.PublishAsync(applicationMessage, CancellationToken.None);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            return true;
        }
    }
}
