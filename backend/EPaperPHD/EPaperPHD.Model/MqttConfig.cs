using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EPaperPHD.Model
{
    public class MqttConfig
    {
        public string Uri { get; set; } = "broker.hivemq.com";
        public int Port { get; set; } = 2002;
    }
}
