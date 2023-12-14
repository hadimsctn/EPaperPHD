using MQTTnet;
using MQTTnet.Client;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model
{
    public class ClientBase
    {
        public readonly IMqttClient client;
        public readonly MqttConfig config;
        public IMqttClient Client => client;
        public ClientBase(IMqttClient client, MqttConfig config)
        {
            this.client = client;
            this.config = config;
        }
        public ClientBase(MqttConfig config)
        {
            config = config;
            client = new MqttFactory().CreateMqttClient();
        }
        public async Task ConnectAsync()
        {
            var options = new MqttClientOptionsBuilder().WithClientId("").WithTcpServer(config.Uri, config.Port).WithCleanSession().Build();
            await client.ConnectAsync(options);
        }

    }
}
