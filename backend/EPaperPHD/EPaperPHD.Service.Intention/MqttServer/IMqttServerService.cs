namespace EPaperPHD.Service.MqttServer
{
    public interface IMqttServerService
    {
        Task<bool> PublishToMqttServer(byte[] bytes, string topic, string broker, double port);
    }
}