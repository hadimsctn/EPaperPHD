using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model.Configuration
{
    public class MqttConfiguration
    {
        public string? Broker {  get; set; }
        public int Port { get; set; }
    }
}
