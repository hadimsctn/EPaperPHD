using EPaperPHD.Model;
using EPaperPHD.Model.EpaperPHDQueryModel;
using EPaperPHD.Model.EpaperPHDUpdateDataModel;
using EPaperPHD.Service.Intention;
using EPaperPHD.Service.MqttServer;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service
{
    public class UpdateDataService : IUpdateDataService
    {
        private readonly ILogger<UpdateDataService> logger;
        private readonly IMqttServerService mqttServerService;
        public UpdateDataService(ILogger<UpdateDataService> logger, IMqttServerService mqttServerService)
        {
            this.logger = logger;
            this.mqttServerService = mqttServerService;
        }
        public async Task<bool> UpdateDataName(EpaperPHDUpdateNameQueryModel queryModel)
        {
            bool result = false;
            try
            {
                logger.LogInformation("Start update Name");
                IdentificationModel<EpaperPHDUpdateNameModel> response = new();
                EpaperPHDUpdateNameModel model = new EpaperPHDUpdateNameModel()
                {
                    Name = queryModel.Name,
                };
                IEnumerable<EpaperPHDUpdateNameModel> enumerableCollection = new List<EpaperPHDUpdateNameModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateName");
            }
            catch(Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        public async Task<bool> UpdateDateOfBirth(EpaperPHDUpdateDateOfBirthQueryModel queryModel)
        {
            bool result = false;
            try
            {
                logger.LogInformation("Start update Name");
                IdentificationModel<EpaperPHDUpdateNameModel> response = new();
                EpaperPHDUpdateNameModel model = new EpaperPHDUpdateNameModel()
                {
                    Name = queryModel.Name,
                };
                IEnumerable<EpaperPHDUpdateNameModel> enumerableCollection = new List<EpaperPHDUpdateNameModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateName");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        public async Task<bool> UpdateMajor(EpaperPHDUpdateMajorQueryModel queryModel)
        {
            bool result = false;
            try
            {
                logger.LogInformation("Start update Name");
                IdentificationModel<EpaperPHDUpdateNameModel> response = new();
                EpaperPHDUpdateNameModel model = new EpaperPHDUpdateNameModel()
                {
                    Name = queryModel.Name,
                };
                IEnumerable<EpaperPHDUpdateNameModel> enumerableCollection = new List<EpaperPHDUpdateNameModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateName");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        public async Task<bool> UpdateClass(EpaperPHDUpdateClassQueryModel queryModel)
        {
            bool result = false;
            try
            {
                logger.LogInformation("Start update Name");
                IdentificationModel<EpaperPHDUpdateNameModel> response = new();
                EpaperPHDUpdateNameModel model = new EpaperPHDUpdateNameModel()
                {
                    Name = queryModel.Name,
                };
                IEnumerable<EpaperPHDUpdateNameModel> enumerableCollection = new List<EpaperPHDUpdateNameModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateName");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
    }
}
