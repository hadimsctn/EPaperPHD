using Microsoft.AspNetCore.Builder;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.StartUp.BuilderExtensions
{
    public static class BuilderSetupExtension
    {
        public static WebApplicationBuilder SetupBuilder(this WebApplicationBuilder builder)
        {
            builder
                .AddConfigurationService()
                .AddServices();
            return builder;
        }
    }
}
