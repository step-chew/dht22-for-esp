#include "esphome.h"
#include "DHTesp.h"

DHTesp dht;

int dhtPin;

class DHT22CustomSensor : public PollingComponent
{
  public:
    Sensor *temperature_sensor = new Sensor();
    Sensor *humidity_sensor = new Sensor();
    Sensor *heat_index_sensor = new Sensor();
    Sensor *dew_point_sensor = new Sensor();

    DHT22CustomSensor(int pin, uint32_t update_interval) : PollingComponent(update_interval) {
      dhtPin = pin;
    }

  void setup() override
  {
    dht.setup(dhtPin, DHTesp::DHT22);
  }

  void update() override
  {
    TempAndHumidity values = dht.getTempAndHumidity();

    float temperature = values.temperature;
    float humidity = values.humidity;
    float heatIndex = dht.computeHeatIndex(temperature, humidity);
    float dewPoint = dht.computeDewPoint(temperature, humidity);

    temperature_sensor->publish_state(temperature);
    humidity_sensor->publish_state(humidity);
    heat_index_sensor->publish_state(heatIndex);
    dew_point_sensor->publish_state(dewPoint);
  }
};
