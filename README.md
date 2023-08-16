# Arduino_PowerManagement

This library abstracts the functionality of the PF1550 Power Management IC and MAX17162 LiPo Fuel Gauge found in the Portenta C33, Portenta H7 and Nicla Vision boards. 
It allows you to monitor the battery usage of your board, control and monitor charging parameters, enable or disable specific power rails on each board to save power, as well as change voltages on some of these rails. 

## Examples 
* **/examples/battery** - 
* **/examples/charger** -
* **/examples/external_voltage** -
* **/examples/power_shell** -
* **/examples/toggle_nicla_cameras** - 

## Features

* Monitor current and average battery metrics (viltage, current, percentage, time-to-full, time-to-empty)
* Monitor battery health metrics (power cycles, temperature, reported capacity)
* Monitor and control charging
* Toggle and set voltages on different power rails of the board
    * On Nicla Vision 
        * Enable and disable the external power rail
        * Enable and disable the camera power rail      
        * Change voltage on external power rail
    * On Portenta C33 
        * Enable and disable the external power rail
        * Enable and disable the communication (ESP32, secure element) power rail 
        * Change voltage on the external power rail 
        * Change Reference and analog voltage
    * On Portenta H7
        * Enable and disable the external power rail
        * Change voltage on external power rail


### Usage 

```cpp
#include "PowerManagement.h"
#include <vector>
#include <string>

PowerManagement manager = PowerManagement();
Battery battery; 
Board board; 
Charger charger;

void setup(){
    manager.begin();
    battery = manager.getBattery();
    board = manager.getBoard();
    charger = manager.getCharger();

    /* Rest of your setup() code */
}
```

#### Battery
The battery object contains methods to read battery usage and health metrics. You can get current and average values for voltage, percentage, current and time as well as an estimated of the time left to charge completely and time left to discharge. 

```
Serial.print("* Voltage: ");
Serial.println(String(battery.readVoltageAvg()) + "mV");

Serial.print("* Current: ");
Serial.println(String(battery.readCurrent()) + "mA");

Serial.print("* Percentage: ");
Serial.println(String(battery.readPercentage()) + "%");

Serial.print("* Remaining Capacity: ");
Serial.println(String(battery.readRemainingCapacity()) + "mAh");

Serial.print("* Temperature: ");
Serial.println(String(battery.readTempAvg()));

Serial.print("* Time-to-full: ");
Serial.println(String(battery.readTimeToFull()) + "s");

Serial.print("* Time-to-empty: ");
Serial.println(String(battery.readTimeToEmpty()) + "s");

```

#### Charger 
Charging a LiPo battery is done in three stages. This library allows you to monitor what charging stage we are in as well as control some of the chagring parameters. 

* **Pre-charge** - First phase of the charging process where the battery is charged at a low constant current and is slowly increased until it reaches the full **charge current**
* **Constant Current** - Second phase of the charging process where the battery is charging in constant current mode until it reaches the voltage where the it's considered fully charged (4.2V normally)
* **Constant Voltage** - Third phase of the charging process where the battery is kept at the fully charged voltage and current is slowly decreased to the ending **end of charge current**

#### Get charger status 
You can find out what stage the charger is in by calling the `getChargeStatus()` method.
It will return a value of `ChargeStatus` which can be one of the above:
* `PRECHARGE` - First stage of the charging process
* `FAST_CHARGE_CC` - Second stage of the charging process
* `FAST_CHARGE_CV` - Last stage of the charging process
* `END_OF_CHARGE` - If the battery is still connected, the charger will ensure it's kept at 4.2V by topping up the voltage to avoid self discharge. 
* `DONE` - Battery is fully charged
* `TIMER_FAULT` - The timer that is monitoring the charge status has encountered an error. 
* `THERMISTOR_SUSPEND` - Charging was suspended due to overheating
* `OFF` - Charger is disabled 
* `BATTERY_OVERVOLTAGE` - Charging was suspended due to an overvoltage fault
* `LINEAR_ONLY` - in this state, the charger is bypassed completely and the USB voltage is powering the board

#### Set charging parameters
This library allows you to change the following charging parameters of the charging process. Please be careful with these and make sure they are supported by the battery you are using as the wrong values might damage your board or the battery. 

##### Charge Voltage
This is the voltage that your battery is charged with:
`charger.setChargeVoltage(ChargeVoltage::V_3_80);`

`ChargeVoltage` is an enum with values ranging from `ChargeVoltage::V_3_50` to `ChargeVoltage::V_4_44` in steps of 0.02V, (`V_3_50`, `V_3_52`, ..., `V_3_42`, `V_4_44`)

##### Charge Current
This is the current used in the constant charging phase. 
`charger.setChargeCurrent(ChargeCurrent::I_500_mA);`

`ChargeCurrent` is an enum with value ranging from `ChargeCurrent::I_100_mA` to `ChargeCurrent::I_100_mA` in steps of 50mA (`I_100_mA`, `I_150_mA`, ... `I_950_mA`, `I_1000_mA`).

##### End of Charge Current
This is the current used in the end-of-charge phase where the voltage is kept at 4.2V. 
`charger.setEndOfChargeCurrent(EndOfChargeCurrent::I_5_mA);`
`EndOfChargeCurrent` is an enum with the following values (`I_5_mA`, `I_10_mA`, `I_20_mA`, `I_30_mA`, `I_50_mA`. )

```

#### Board
##### Nicla vision
##### Portenta C33
##### Portenta H7