using EPaperPHD.Model;
using EPaperPHD.Model.EpaperPHDQueryModel;
using EPaperPHD.Model.EpaperPHDUpdateDataModel;
using EPaperPHD.Service.Intention;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Logging;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
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
                EpaperPHDUpdateNameModel model = new EpaperPHDUpdateNameModel()
                {
                    Name = queryModel.Name,
                    IdDevice = queryModel.IdDevice,
                };
                result = await mqttServerService.PublishToMqttServer(model, "EpaperPHD/UpdateName");
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
                EpaperPHDUpdateDateOfBirthModel model = new EpaperPHDUpdateDateOfBirthModel()
                {
                    DateOfBirth = queryModel.DateOfBirth,
                    IdDevice = queryModel.IdDevice
                };
                result = await mqttServerService.PublishToMqttServer(model, "EpaperPHD/UpdateDateOfBirth");
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
                EpaperPHDUpdateMajorModel model = new EpaperPHDUpdateMajorModel()
                {
                    Major = queryModel.Major,
                    IdDevice = queryModel.IdDevice
                };
                result = await mqttServerService.PublishToMqttServer(model, "EpaperPHD/UpdateMajor");
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
                EpaperPHDUpdateClassModel model = new EpaperPHDUpdateClassModel()
                {
                    Class = queryModel.Class,
                    IdDevice = queryModel.IdDevice
                };
                result = await mqttServerService.PublishToMqttServer(model, "EpaperPHD/UpdateClass");
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
                if(queryModel.Image == null || queryModel.Image.Length == 0)
                {
                    return false;
                }
                if (queryModel.Image == null || queryModel.Image.Length == 0) return false;
                var image = await ImageToByteArrayAsync(queryModel.Image);
                EpaperPHDUpdateImageModel model = new EpaperPHDUpdateImageModel()
                {
                    IdDevice = queryModel.IdDevice,
                    ImageLength = image.Length,
                };
                result = await mqttServerService.PublishImageToMqttServer(image,model, "EpaperPHD/UpdateImage");
            }
            catch (Exception ex)
            {
                logger.LogError(ex.ToString());
            }
            return result;
        }
        private async Task<byte[]> ImageToByteArrayAsync(IFormFile imageFile)
        {
            using (MemoryStream memoryStream = new MemoryStream())
            {
                // Đọc dữ liệu từ IFormFile vào MemoryStream
                await imageFile.CopyToAsync(memoryStream);

                // Load hình ảnh từ MemoryStream bằng System.Drawing.Common
                using (Bitmap bitmap = new Bitmap(memoryStream))
                {
                    int width = bitmap.Width;
                    int height = bitmap.Height;

                    int arraySize = width * height / 8;
                    byte[] imageBytes = new byte[arraySize];
                    int index = 0;
                    for (int y = 0; y < height; y++)
                    {
                        for (int x = 0; x < width; x++)
                        {
                            Color pixel = bitmap.GetPixel(x, y);
                            if (pixel.GetBrightness() > 0.5)
                            {
                                imageBytes[index / 8] |= (byte)(1 << (7 - (index % 8)));
                            }
                            index++;
                        }
                    }
                    return imageBytes;
                }
            }
        }
    }
}
