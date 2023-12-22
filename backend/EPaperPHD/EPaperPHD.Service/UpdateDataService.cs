using EPaperPHD.Model;
using EPaperPHD.Model.EpaperPHDQueryModel;
using EPaperPHD.Model.EpaperPHDUpdateDataModel;
using EPaperPHD.Service.Intention;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Http;
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
                logger.LogInformation("Start update Date Of Birth");
                IdentificationModel<EpaperPHDUpdateDateOfBirthModel> response = new();
                EpaperPHDUpdateDateOfBirthModel model = new EpaperPHDUpdateDateOfBirthModel()
                {
                    DateOfBirth = queryModel.DateOfBirth,
                };
                IEnumerable<EpaperPHDUpdateDateOfBirthModel> enumerableCollection = new List<EpaperPHDUpdateDateOfBirthModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateDateOfBirth");
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
                logger.LogInformation("Start update Major");
                IdentificationModel<EpaperPHDUpdateMajorModel> response = new();
                EpaperPHDUpdateMajorModel model = new EpaperPHDUpdateMajorModel()
                {
                    Major = queryModel.Major,
                };
                IEnumerable<EpaperPHDUpdateMajorModel> enumerableCollection = new List<EpaperPHDUpdateMajorModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateMajor");
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
                IdentificationModel<EpaperPHDUpdateClassModel> response = new();
                EpaperPHDUpdateClassModel model = new EpaperPHDUpdateClassModel()
                {
                    Class = queryModel.Class,
                };
                IEnumerable<EpaperPHDUpdateClassModel> enumerableCollection = new List<EpaperPHDUpdateClassModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateClass");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        public async Task<bool> UpdateImage(EpaperPHDUpdateImageQueryModel queryModel)
        {
            bool result = false;
            try
            {
                logger.LogInformation("Start update Image");
                IdentificationModel<EpaperPHDUpdateImageModel> response = new();
                if(queryModel.Image == null || queryModel.Image.Length == 0)
                {
                    return false;
                }
                if (queryModel.Image == null || queryModel.Image.Length == 0) return false;
                var image = await ConvertImageToByte(queryModel.Image);
                EpaperPHDUpdateImageModel model = new EpaperPHDUpdateImageModel()
                {
                    Image = image,
                };
                IEnumerable<EpaperPHDUpdateImageModel> enumerableCollection = new List<EpaperPHDUpdateImageModel> { model };
                response.IdDevice = queryModel.IdDevice;
                response.Data = enumerableCollection;
                result = await mqttServerService.PublishToMqttServer(response, "EpaperPHD/UpdateImage");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        private async Task<byte[]> ConvertImageToByte(IFormFile imageData)
        {
            using (MemoryStream memoryStream = new MemoryStream())
            {
                // Copy the contents of the uploaded file to the memory stream
                imageData.CopyTo(memoryStream);

                // Get the byte array from the memory stream
                byte[] byteArray = memoryStream.ToArray();

                return await Task.FromResult(byteArray);
            }
        }
    }
}
