using EPaperPHD.Service;
using EPaperPHD.Service.Intention;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.StartUp.BuilderExtensions
{
    internal static class ServicesExtension
    {
        internal static WebApplicationBuilder AddServices(this WebApplicationBuilder builder) => builder.AddLogicServices();
        private static WebApplicationBuilder AddLogicServices(this WebApplicationBuilder builder)
        {
            builder.Services.AddHostedService<ListeningService>();
            builder.Services.AddScoped<IMqttServerService, MqttServerService>();
            builder.Services.AddScoped<IUpdateDataService, UpdateDataService>();
            return builder;
        }
    }
}
