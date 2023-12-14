using EPaperPHD.Model.Configuration;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.StartUp.BuilderExtensions
{
    internal static class ConfigurationExtension
    {
        public static WebApplicationBuilder AddConfigurationService(this WebApplicationBuilder builder)
        {
            builder.Services.Configure<MqttConfiguration>(builder.Configuration.GetSection("MqttServer"));
            return builder;
        }
    }
}
