using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Hosting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.StartUp.AppExtensions
{
    public static class AppSetupExtention
    {
        public static WebApplication SetupApp(this WebApplication app)
        {
            app.UseCors();
            if (app.Environment.IsDevelopment())
            {
                app.UseSwagger();
                app.UseSwaggerUI();
            }
            app.UseHttpsRedirection();

            app.UseAuthorization();
            app.MapControllers();
            return app;
        }
    }
}
