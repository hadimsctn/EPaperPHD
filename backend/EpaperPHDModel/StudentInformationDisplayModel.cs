namespace EpaperPHDModel
{
    public class StudentInformationDisplayModel
    {
        public byte[]? imageBytes { get; set; } 
        public string studentName { get; set; } = string.Empty;
        public string dateOfBirth { get; set; } = string.Empty;
        public string major { get; set; } = string.Empty;
        public string majorCode { get; set; } = string.Empty;
    }
}