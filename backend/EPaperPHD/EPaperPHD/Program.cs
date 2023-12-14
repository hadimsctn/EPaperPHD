using EPaperPHD.StartUp.BuilderExtensions;
using EPaperPHD.Service;
using MQTTnet.Client;

var builder = WebApplication.CreateBuilder(args).SetupBuilder();

// Add services to the container.

builder.Services.AddControllers();
builder.Services.AddHostedService<ListeningService>();
builder.Services.AddSingleton<IMqttClient, MqttClient>();

// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseHttpsRedirection();

app.UseAuthorization();

app.MapControllers();

app.Run();
