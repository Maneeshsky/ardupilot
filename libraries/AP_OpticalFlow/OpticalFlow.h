#ifndef __OpticalFlow_H__
#define __OpticalFlow_H__
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 *       OpticalFlow.h - OpticalFlow Base Class for Ardupilot
 *       Code by Randy Mackay. DIYDrones.com
 *
 *       Methods:
 *               init() : initializate sensor and library.
 *               read   : reads latest value from OpticalFlow and
 *                        stores values in x,y, surface_quality parameter
 *               read_register()  : reads a value from the sensor (will be
 *                                  sensor specific)
 *               write_register() : writes a value to one of the sensor's
 *                                  register (will be sensor specific)
 */

#include <AP_Math.h>
#include <AP_AHRS.h>

class OpticalFlow
{
public:
    // constructor
    OpticalFlow(const AP_AHRS &ahrs);

    // init - initialise sensor
    virtual void init() {}

    // enabled - returns true if optical flow is enabled
    bool enabled() const { return _enabled; }

    // healthy - return true if the sensor is healthy
    bool healthy() const { return _flags.healthy; }

    // read latest values from sensor and fill in x,y and totals.
    virtual void update() {}

    // quality - returns the surface quality as a measure from 0 ~ 255
    uint8_t quality() const { return _surface_quality; }

    // raw - returns the raw movement from the sensor
    const Vector2f& flowRate() const { return _flowRate; }

    // velocity - returns the velocity in m/s
    const Vector2f& bodyRate() const { return _bodyRate; }

    // device_id - returns device id
    uint8_t device_id() const { return _device_id; }

    // last_update() - returns system time of last sensor update
    uint32_t last_update() const { return _last_update; }

    // parameter var info table
    static const struct AP_Param::GroupInfo var_info[];

protected:

    struct AP_OpticalFlow_Flags {
        uint8_t healthy     : 1;    // true if sensor is healthy
    } _flags;

    // external references
    const AP_AHRS &_ahrs;           // ahrs object

    // parameters
    AP_Int8  _enabled;              // enabled/disabled flag
    AP_Int16 _flowScalerX;          // X axis flow scale factor correction - parts per thousand
    AP_Int16 _flowScalerY;          // Y axis flow scale factor correction - parts per thousand

    // internal variables
    uint8_t _device_id;             // device id
    uint8_t  _surface_quality;      // image quality (below TBD you can't trust the dx,dy values returned)
    Vector2f _flowRate;             // optical flow angular rate in rad/sec measured about the X and Y body axis. A RH rotation about a sensor axis produces a positive rate.
    Vector2f _bodyRate;             // body inertial angular rate in rad/sec measured about the X and Y body axis. A RH rotation about a sensor axis produces a positive rate.
    uint32_t _last_update;          // millis() time of last update
};

#endif
