/**
 * Copyright (c) 2017 QNibbles, LLC.
 * West Fargo ND, 58078
 * All rights reserved.
 */

//#include <Python.h>
#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#include <malloc.h>
#include <iostream>
#include <fstream>

VL53L0X_Dev_t   _MyDevice;
int32_t         _init_done;
float           _lastLaserMeasurement;
double          _millivoltsPerMillimeter;
double          _zeroedLaserValueInMillimeteres;

void print_pal_error(VL53L0X_Error Status){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    VL53L0X_GetPalErrorString(Status, buf);
    printf("API Status: %i : %s\n", Status, buf);
}

void print_range_status(VL53L0X_RangingMeasurementData_t* pRangingMeasurementData){
    char buf[VL53L0X_MAX_STRING_LENGTH];
    uint8_t RangeStatus;

    /*
     * New Range Status: data is valid when pRangingMeasurementData->RangeStatus = 0
     */

    RangeStatus = pRangingMeasurementData->RangeStatus;

    VL53L0X_GetRangeStatusString(RangeStatus, buf);
    printf("Range Status: %i : %s\n", RangeStatus, buf);

}


VL53L0X_Error configureDevice(VL53L0X_Dev_t *pMyDevice)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    int i;
    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_StaticInit\n");
        Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
        print_pal_error(Status);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_PerformRefSpadManagement\n");
        Status = VL53L0X_PerformRefSpadManagement(pMyDevice,
                &refSpadCount, &isApertureSpads); // Device Initialization
        printf ("refSpadCount = %d, isApertureSpads = %d\n", refSpadCount, isApertureSpads);
        print_pal_error(Status);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_PerformRefCalibration\n");
        Status = VL53L0X_PerformRefCalibration(pMyDevice,
                &VhvSettings, &PhaseCal); // Device Initialization
        printf ("VhvSettings = %d, PhaseCal = %d\n", VhvSettings, PhaseCal);
        print_pal_error(Status);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        // no need to do this when we use VL53L0X_PerformSingleRangingMeasurement
        printf ("Call of VL53L0X_SetDeviceMode\n");
        Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
        print_pal_error(Status);
    }

    // Enable/Disable Sigma and Signal check

 /*   if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetSequenceStepEnable(pMyDevice,VL53L0X_SEQUENCESTEP_DSS, 1);
    }*/

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                (FixPoint1616_t)(0.25*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                (FixPoint1616_t)(18*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice,
                30000);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetVcselPulsePeriod(pMyDevice,
                VL53L0X_VCSEL_PERIOD_PRE_RANGE, 18);
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetVcselPulsePeriod(pMyDevice,
                VL53L0X_VCSEL_PERIOD_FINAL_RANGE, 14);
    }

    return Status;
}

float getMeasurement()
{
    float rangeInmm = -1;
    if (_init_done)
    {
        VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
        VL53L0X_Error Status = VL53L0X_PerformSingleRangingMeasurement(&_MyDevice,
            &RangingMeasurementData);

        print_pal_error(Status);
        print_range_status(&RangingMeasurementData);

        if ((Status == VL53L0X_ERROR_NONE) && (RangingMeasurementData.RangeStatus == 0))
        {
            rangeInmm = RangingMeasurementData.RangeMilliMeter;
        }
    }
    return rangeInmm;
}

int init()
{
    _init_done = false;
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_Dev_t *pMyDevice = &_MyDevice;
    VL53L0X_Version_t                   Version;
    VL53L0X_Version_t                  *pVersion   = &Version;
    VL53L0X_DeviceInfo_t                DeviceInfo;

    int32_t status_int;
    int NecleoComStatus = 0;
    int NecleoAutoCom = 1;

    memset(pMyDevice, 0, sizeof(VL53L0X_Dev_t));

    // Initialize Comms
    pMyDevice->I2cDevAddr      = 0x29;
    pMyDevice->comms_type      =  1;
    pMyDevice->comms_speed_khz =  400;

    Status = VL53L0X_comms_initialise(0, 400);
    if (Status != VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    } else
        printf ("Init Comms\n");

    _init_done = 1;

    /*
     * Disable VL53L0X API logging if you want to run at full speed
     */
#ifdef VL53L0X_LOG_ENABLE
    VL53L0X_trace_config("test.log", TRACE_MODULE_ALL, TRACE_LEVEL_ALL, TRACE_FUNCTION_ALL);
#endif

    /*
     *  Get the version of the VL53L0X API running in the firmware
     */

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf("Calling VL53L0X_GetVersion\n");
        status_int = VL53L0X_GetVersion(pVersion);
        if (status_int != 0)
            Status = VL53L0X_ERROR_CONTROL_INTERFACE;
    }
    print_pal_error(Status);

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf ("Call of VL53L0X_DataInit\n");
        Status = VL53L0X_DataInit(&_MyDevice); // Data initialization
        print_pal_error(Status);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        printf("Calling VL53L0X_GetDeviceInfo\n");
        Status = VL53L0X_GetDeviceInfo(&_MyDevice, &DeviceInfo);
        print_pal_error(Status);
        if(Status == VL53L0X_ERROR_NONE)
        {
            printf("VL53L0X_GetDeviceInfo:\n");
            printf("Device Name : %s\n", DeviceInfo.Name);
            printf("Device Type : %s\n", DeviceInfo.Type);
            printf("Device ID : %s\n", DeviceInfo.ProductId);
            printf("ProductRevisionMajor : %d\n", DeviceInfo.ProductRevisionMajor);
            printf("ProductRevisionMinor : %d\n", DeviceInfo.ProductRevisionMinor);

            if ((DeviceInfo.ProductRevisionMinor != 1) && (DeviceInfo.ProductRevisionMinor != 1))
            {
                printf("Error expected cut 1.1 but found cut %d.%d\n",
                       DeviceInfo.ProductRevisionMajor, DeviceInfo.ProductRevisionMinor);
                Status = VL53L0X_ERROR_NOT_SUPPORTED;
            }
        }
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = configureDevice(pMyDevice);
    }

    print_pal_error(Status);

    // Implementation specific

    return (Status);
}

void disconnect()
{
    /*
     *  Disconnect comms - part of VL53L0X_platform.c
     */
    if(_init_done == 0)
    {
        printf ("Close Comms\n");
        VL53L0X_comms_close();
    }
}

#if 0
/**
* Python bindings below
*/
static PyObject *LaserError;

static PyObject *
laser_system(PyObject *self, PyObject *args)
{
    const char *command;

    if (!PyArg_ParseTuple(args, "", &command))
    {
        return NULL;
    }

    init();
    float measurement = getMeasurement();

    return PyFloat_FromDouble((double)measurement);
}

static PyObject *
laser_getMeasurement(PyObject *self, PyObject *args)
{
    const char *command;

    if (!PyArg_ParseTuple(args, "", &command))
    {
        return NULL;
    }

    return PyFloat_FromDouble((double)_lastLaserMeasurement);
}

static PyObject *
laser_set_mv_per_mm(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "d", &_millivoltsPerMillimeter))
    {
        return NULL;
    }

    return PyFloat_FromDouble((double)_millivoltsPerMillimeter);
}

static PyObject *
laser_zeroOffset(PyObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, "", NULL))
    {
        return NULL;
    }

    _zeroedLaserValueInMillimeteres = _lastLaserMeasurement;

    return PyFloat_FromDouble((double)_lastLaserMeasurement);
}

static PyMethodDef LaserMethods[] =
{
    {"init", laser_system, METH_VARARGS, "Initialize the laser system"},
    {"getMeasurement", laser_getMeasurement, METH_VARARGS, "Get a measurement"},
    {"set_mv_per_mm", laser_set_mv_per_mm, METH_VARARGS, "Sets the offset of millivolts per millimeter of displacement"},
    {"zeroOffset", laser_zeroOffset, METH_VARARGS, "Zeros the offset of the laser rangefinder"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef lasermodule =
{
    PyModuleDef_HEAD_INIT,
    "laser",
    NULL,
    -1,
    LaserMethods
};


PyMODINIT_FUNC
PyInit_laser(void)
{
    PyObject *m;

    m = PyModule_Create(&lasermodule);
    if (m == NULL)
        return NULL;

    // LaserError = PyErr_NewException("laser.error", NULL, NULL);
    // Py_INCREF(LaserError);
    // PyModule_AddObject(m, "error", LaserError);
    return m;
}
#endif