/* Distributed under the Apache License, Version 2.0.
   See accompanying NOTICE file for details.*/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;

import com.kitware.physiology.cdm.AnesthesiaMachineActions.ExpiratoryValveLeakData;

import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SEExpiratoryValveLeak extends SEAnesthesiaMachineAction
{
  protected SEScalar0To1 severity;
  
  public SEExpiratoryValveLeak()
  {
    severity = null;
  }
  
  public void reset()
  {
    super.reset();
    if (severity != null)
      severity.invalidate();
  }
  
  public boolean isValid()
  {
    return hasSeverity();
  }
  
  public static void load(ExpiratoryValveLeakData src, SEExpiratoryValveLeak dst)
  {
    SEAnesthesiaMachineAction.load(src.getAnesthesiaMachineAction(),dst);
    if(src.hasSeverity())
      SEScalar0To1.load(src.getSeverity(),dst.getSeverity());
  }
  public static ExpiratoryValveLeakData unload(SEExpiratoryValveLeak src)
  {
    ExpiratoryValveLeakData.Builder dst = ExpiratoryValveLeakData.newBuilder();
    unload(src,dst);
    return dst.build();
  }
  protected static void unload(SEExpiratoryValveLeak src, ExpiratoryValveLeakData.Builder dst)
  {
    SEAnesthesiaMachineAction.unload(src, dst.getAnesthesiaMachineActionBuilder());
    if (src.hasSeverity())
      dst.setSeverity(SEScalar0To1.unload(src.severity));
  }
  
  /*
   * Severity
   */
  public boolean hasSeverity()
  {
    return severity == null ? false : severity.isValid();
  }
  public SEScalar0To1 getSeverity()
  {
    if (severity == null)
      severity = new SEScalar0To1();
    return severity;
  }
  
  public String toString()
  {
    if (severity != null)
      return "Expiratory Valve Leak"
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
