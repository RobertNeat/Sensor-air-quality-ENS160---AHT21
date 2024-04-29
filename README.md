# ENS160 + AHT21 sensor package on ESP_32

This project is the barebone for the projects using this sensor package (the readouts are on serial and to variables so they can be used on displays etc.). I2C address 0x52, 0x53.

The measurement are made through two sensors hooked to I2C line:
1. ENS160 (air quality) - Indoor Air Quality:
     - TVOC (Total Volatile Organic Compunds),
     - eCO2 (equvalent CO2),
     - AQI (Air Quality Index),
     - additionally it detects: toluene, hydrogen, ethanol, NO2 and ozone. (cannot be measured but can be detected as quality decrease), 
3. AHT21 (air temperature and humidity:
    - room temperature,
    - relative humidity,

### Tables with metric reference:  
![AQ_output_characteristic](https://github.com/RobertNeat/Sensor-air-quality-ENS160---AHT21/assets/47086490/87f38750-e519-4ae5-9a89-295a61460a9b)
 
![AQI_index_table](https://github.com/RobertNeat/Sensor-air-quality-ENS160---AHT21/assets/47086490/6e4fc663-ea0d-4533-bf13-ee79a424bc00)
