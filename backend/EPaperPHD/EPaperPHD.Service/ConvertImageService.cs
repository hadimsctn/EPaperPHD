using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Service
{
    public class ConvertImageService
    {
        public readonly ILogger<ConvertImageService> logger;
        public ConvertImageService(ILogger<ConvertImageService> logger)
        {
            this.logger = logger;
        }
        //public byte[] ConvertImageToMonochrome(byte[] image)
        //{
        //    using (var imageCv = CvInvoke.Imdecode(image, ImreadModes.Color))
        //    {
        //        // Chuyển đổi ảnh thành ảnh đơn sắc
        //        CvInvoke.CvtColor(imageCv, imageCv, ColorConversion.Bgr2Gray);

        //        // Chuyển đổi lại thành byte[]
        //        return imageCv.ToImage<Bgr, byte>().ToJpegData();
        //    }
        //}
    }
}
