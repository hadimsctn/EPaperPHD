﻿using EPaperPHD.Model.Configuration;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using MQTTnet;
using MQTTnet.Client;
using MQTTnet.Server;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service
{
    public class ListeningService : BackgroundService
    {
        private readonly ILogger<ListeningService> logger;
        private readonly IConfiguration configuration;
        private readonly MqttConfiguration mqttConfiguration;
        
        public ListeningService(ILogger<ListeningService> logger, IConfiguration configuration,IOptionsMonitor<MqttConfiguration> mqttConfiguration)
        {
            this.logger = logger;
            this.configuration = configuration;
            this.mqttConfiguration = mqttConfiguration.CurrentValue;  
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while(!stoppingToken.IsCancellationRequested)
            {
                var mqttFactory = new MqttFactory();
                IMqttClient client = mqttFactory.CreateMqttClient();
                var options = new MqttClientOptionsBuilder()
                    .WithClientId("2023")
                    .WithTcpServer(mqttConfiguration.Broker, mqttConfiguration.Port)
                    .WithCleanSession()
                    .Build();
                var connectResult = await client.ConnectAsync(options);
                if (connectResult.ResultCode == MqttClientConnectResultCode.Success)
                {
                    logger.LogInformation("Connected mqtt Server");
                }
                await Task.Delay(1000, stoppingToken);
            }
        }
    }
}
