namespace EPaperPHD.Service.MqttServer
{
    public interface IMqttServerService
    {
        Task<bool> PublishToMqttServer(object data, string topic);
        Task<bool> PublishImageToMqttServer(byte[] image,object data, string topic);
    }
}