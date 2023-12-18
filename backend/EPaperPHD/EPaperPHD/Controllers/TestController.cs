﻿using EPaperPHD.Controllers;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Mvc;
using System.Text;

namespace EPaperPHD.Web.Controllers
{
    [ApiController, Route("api/Test")]
    public class TestController : ControllerBase
    {
        private readonly IMqttServerService mqttServerService;

        public TestController(IMqttServerService mqttServerService)
        {
            this.mqttServerService = mqttServerService;
        }
        [HttpPost, Route("TestController/publisher")]
        public async Task<bool> PublishDatatoMQTTServer()
        {
            return await mqttServerService.PublishToMqttServer(UTF8Encoding.UTF8.GetBytes("Quang Thanh Dat"), "EpaperPHD/UpdateName", "broker.hivemq.com", 1883);
        }
    }
}
