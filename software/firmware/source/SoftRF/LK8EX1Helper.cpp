/*
 * D1090Helper.cpp
 * Copyright (C) 2016-2019 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//#include <adsb_encoder.h>
//#include <TimeLib.h>
#include <TinyGPS++.h>

#include "LK8EX1Helper.h"
#include "NMEAHelper.h"
#include "EEPROMHelper.h"
#include "SoCHelper.h"
//#include "TrafficHelper.h"
#include "SoftRF.h"

char LK8EX1Buffer[LK8EX1_BUFFER_SIZE]; //buffer for NMEA data

static void LK8EX1_Out(byte *buf, size_t size)
{
//  switch(LK8EX1_BLUETOOTH)
  switch(settings->nmea_out)
  {
  case NMEA_UART:
    {
      Serial.write(buf, size);
    }
    break;
  case NMEA_BLUETOOTH:
    {
      if (SoC->Bluetooth) {
        SoC->Bluetooth->write(buf, size);
      }
    }
    break;
  case NMEA_UDP:
  case NMEA_TCP:
  case NMEA_OFF:
  default:
    break;
  }
}

void LK8EX1_Export()
{
  // ADAHRS AHRS               
                                   
  //if (settings->LK8EX1 != LK8EX1_OFF) {

  long mypreasure = 999999;

  int myaltitude = 245;
  /* If the aircraft's data has standard pressure altitude - make use it */
  if (ThisAircraft.pressure_altitude != 0.0) {
    myaltitude = (int) ThisAircraft.pressure_altitude;
	}
	
	int myvoltage = 1090;
	if (SoC->Battery_voltage() != 0.0 ) {
	  myvoltage = 1000 + ( (int)(SoC->Battery_voltage()*10) - 32) * 10;
	}
  int myvario = 0;
  if (ThisAircraft.vs != 0.0) {
    myvario = (int) (ThisAircraft.vs*100/60.0/_GPS_FEET_PER_METER);
  }
  int mytemperature = (int) (ThisAircraft.temperature + 0.5f);
  
  // https://github.com/LK8000/LK8000/blob/master/Docs/LK8EX1.txt              
	// $LK8EX1,pressure,altitude,vario,temperature,battery,*checksum\r\n
  // $LK8EX1,98000,245,95,25,1090*23F
  //        hPa*100 m cm/s C  1000+%   
  snprintf_P(LK8EX1Buffer, sizeof(LK8EX1Buffer), PSTR("$LK8EX1,%.1f,%i,%i,%i,%i,*"), ThisAircraft.pressure, myaltitude, myvario, mytemperature, myvoltage);
  NMEA_add_checksum(LK8EX1Buffer, sizeof(LK8EX1Buffer) - strlen(LK8EX1Buffer));
  LK8EX1_Out((byte *) LK8EX1Buffer, strlen(LK8EX1Buffer));

  // FLYMASTER format
  // $VARIO,fPressure,fVario,Bat1Volts,Bat2Volts,BatBank,TempSensor1,TempSensor2*CS
  // fVario = the variometer in decimeters per second
  // Bat1Volts = the voltage of the battery in bank 1
  // Bat2Volts = the voltage of the battery in bank 2
  // BatBank = the battery bank in use.
  // TempSensor1 = temperature in ºC of external wireless sensor 1
  // TempSensor2 = temperature in ºC of external wireless sensor 2
  
  //snprintf_P(LK8EX1Buffer, sizeof(LK8EX1Buffer), PSTR("$VARIO,%.2f,%i,%.2f,,,%i,*"), ThisAircraft.pressure/100, (int) (myvario/10), SoC->Battery_voltage(), mytemperature);
  //NMEA_add_checksum(LK8EX1Buffer, sizeof(LK8EX1Buffer) - strlen(LK8EX1Buffer));
  //LK8EX1_Out((byte *) LK8EX1Buffer, strlen(LK8EX1Buffer));

  /* LXNAV
  $LXWP0,Y,222.3,1665.5,1.71,,,,,,239,174,10.1
   0 loger_stored (Y/N)
   1 IAS (kph) ----> Condor uses TAS!
   2 baroaltitude (m)
   3-8 vario (m/s) (last 6 measurements in last second)
   9 heading of plane
  10 windcourse (deg)
  11 windspeed (kph)
  */

  //snprintf_P(LK8EX1Buffer, sizeof(LK8EX1Buffer), PSTR("$LXWP0,N,,%i,%.2f,,,,,,,,*"), myaltitude, (float)myvario/100);
  //NMEA_add_checksum(LK8EX1Buffer, sizeof(LK8EX1Buffer) - strlen(LK8EX1Buffer));
  //LK8EX1_Out((byte *) LK8EX1Buffer, strlen(LK8EX1Buffer));
  
  //}
}
