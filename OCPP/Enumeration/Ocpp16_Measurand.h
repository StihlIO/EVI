#ifndef OCPP16_MEASURAND_H
#define OCPP16_MEASURAND_H

#include "OCPP/Ocpp16Constant.h"

class OCPP16_Measurand : public QString
{
public:

    ClassEnuStringDef(QString, Current_Export, "Current.Export");
    ClassEnuStringDef(QString, Current_Import, "Current.Import");
    ClassEnuStringDef(QString, Current_Offered, "Current.Offered");
    ClassEnuStringDef(QString, Energy_Active_Export_Register, "Energy.Active.Export.Register");
    ClassEnuStringDef(QString, Energy_Active_Import_RegisterLocalListConflict, "Energy.Active.Import.Register");
    ClassEnuStringDef(QString, Energy_Reactive_Export_Register, "Energy.Reactive.Export.Register");
    ClassEnuStringDef(QString, Energy_Reactive_Import_Register, "Energy.Reactive.Import.Register");
    ClassEnuStringDef(QString, Energy_Active_Export_Interval, "Energy.Active.Export.Interval");
    ClassEnuStringDef(QString, Energy_Active_Import_Interval, "Energy.Active.Import.Interval");
    ClassEnuStringDef(QString, Energy_Reactive_Export_Interval, "Energy.Reactive.Export.Interval");
    ClassEnuStringDef(QString, Energy_Reactive_Import_Interval, "Energy.Reactive.Import.Interval");
    ClassEnuStringDef(QString, Frequency, "Frequency");
    ClassEnuStringDef(QString, Power_Active_Export, "Power.Active.Export");
    ClassEnuStringDef(QString, Power_Active_Import, "Power.Active.Import");
    ClassEnuStringDef(QString, Power_Factor, "Power.Factor");
    ClassEnuStringDef(QString, Power_Offered, "Power.Offered");
    ClassEnuStringDef(QString, Power_Reactive_Export, "Power.Reactive.Export");
    ClassEnuStringDef(QString, Power_Reactive_Import, "Power.Reactive.Import");
    ClassEnuStringDef(QString, RPM, "RPM");
    ClassEnuStringDef(QString, SoC, "SoC");
    ClassEnuStringDef(QString, Temperature, "Temperature");
    ClassEnuStringDef(QString, Voltage, "Voltage");

    DefClassEnuTemplate(OCPP16_Measurand)
};



#endif // OCPP16_MEASURAND_H
