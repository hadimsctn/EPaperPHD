using EPaperPHD.Model;
using EPaperPHD.Model.Test;
using EPaperPHD.Service.MqttServer;
using Microsoft.AspNetCore.Components.Forms;
using Microsoft.AspNetCore.Mvc;
using System.Drawing;
using System.Drawing.Imaging;
using static System.Net.Mime.MediaTypeNames;

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
            WeatherForecast weatherForecast = new WeatherForecast
            {
                TemperatureC = 25,
                Summary = "dsfs",
            };
            return await mqttServerService.PublishToMqttServer(weatherForecast, "EpaperPHD/UpdateAll");
        }
        [HttpPost, Route("TestController/testData")]
        public async Task<IdentificationModel<EpaperPHDDisplayModel>> PublishDataDefault()
        {
            IdentificationModel<EpaperPHDDisplayModel> Response = new();
            EpaperPHDDisplayModel model = new EpaperPHDDisplayModel()
            {
                DateOfBirth = "12/08/2002",
                Name = "Name",
                Class = "Class",
                Major = "dsd",
            };
            IEnumerable<EpaperPHDDisplayModel> enumerableCollection = new List<EpaperPHDDisplayModel> { model };
            Response.IdDevice = "adsdfsaf";
            Response.Data = enumerableCollection;
            return Response;
        }
        [HttpPost, Route("TestController/testConvertImage")]
        public async Task<bool> ConvertImageToMonochrome(string SourceImage)
        {
            string inputImagePath = SourceImage;
            string outputImagePath = "output_dither_manual_detail.bmp";

            // Load the input image
            Bitmap inputImage = new Bitmap(inputImagePath);

            // Convert the image to monochrome using manual error diffusion dithering with enhanced detail
            Bitmap outputImage = ConvertToMonochromeErrorDiffusion(inputImage);

            // Save the result
            outputImage.Save(outputImagePath, System.Drawing.Imaging.ImageFormat.Bmp);

            Console.WriteLine("Image converted successfully using manual error diffusion dithering with enhanced detail.");
            return true;
        }
        static Bitmap ConvertToMonochromeErrorDiffusion(Bitmap inputImage)
        {
            // Create a new Bitmap with the same dimensions as the input image
            Bitmap outputImage = new Bitmap(inputImage.Width, inputImage.Height);

            // Loop through each pixel in the input image
            for (int y = 0; y < inputImage.Height; y++)
            {
                for (int x = 0; x < inputImage.Width; x++)
                {
                    // Get the color of the current pixel
                    Color oldColor = inputImage.GetPixel(x, y);

                    // Convert the color to monochrome using Floyd-Steinberg error diffusion with enhanced detail
                    int newColorValue = oldColor.R > 128 ? 255 : 0;
                    Color newColor = Color.FromArgb(newColorValue, newColorValue, newColorValue);
                    outputImage.SetPixel(x, y, newColor);

                    // Calculate error
                    int error = oldColor.R - newColorValue;

                    // Distribute the error to neighboring pixels with enhanced detail
                    PropagateError(inputImage, x, y, error, 7.0 / 16.0);
                    PropagateError(inputImage, x, y, error, 1.0 / 16.0, 1, -1);
                    PropagateError(inputImage, x, y, error, 5.0 / 16.0, 1, 0);
                    PropagateError(inputImage, x, y, error, 3.0 / 16.0, 1, 1);
                }
            }

            return outputImage;
        }

        static void PropagateError(Bitmap image, int x, int y, int error, double factor, int offsetX = 0, int offsetY = 0)
        {
            if (x + offsetX >= 0 && x + offsetX < image.Width && y + offsetY >= 0 && y + offsetY < image.Height)
            {
                Color currentColor = image.GetPixel(x + offsetX, y + offsetY);
                int newColorValue = Math.Max(0, Math.Min(255, currentColor.R + (int)(error * factor)));
                Color newColor = Color.FromArgb(newColorValue, newColorValue, newColorValue);
                image.SetPixel(x + offsetX, y + offsetY, newColor);
            }
        }
    }
}
