namespace EPaperPHD.Service.MqttServer
{
    public interface IMqttServerService
    {
        Task<bool> PublishToMqttServer(object data, string topic, string broker, double port);
    }
}