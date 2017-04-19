/**************************************************************************************
Copyright 2015 Applied Research Associates, Inc.
Licensed under the Apache License, Version 2.0 (the "License"); you may not use
this file except in compliance with the License. You may obtain a copy of the License
at:
http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.
**************************************************************************************/

package mil.tatrc.physiology.datamodel.system.equipment.anesthesia.actions;

import mil.tatrc.physiology.datamodel.CDMSerializer;
import mil.tatrc.physiology.datamodel.bind.EnumOnOff;
import mil.tatrc.physiology.datamodel.bind.TubeCuffLeakData;
import mil.tatrc.physiology.datamodel.properties.SEScalar0To1;

public class SETubeCuffLeak extends SEAnesthesiaMachineAction
{
  protected SEScalar0To1 severity;
  
  public SETubeCuffLeak()
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
  
  public boolean load(TubeCuffLeakData in)
  {
    super.load(in);
    getSeverity().load(in.getSeverity());
    return isValid();
  }
  
  public TubeCuffLeakData unload()
  {
    TubeCuffLeakData data = CDMSerializer.objFactory.createTubeCuffLeakData();
    unload(data);
    return data;
  }
  
  protected void unload(TubeCuffLeakData data)
  {
    super.unload(data);
    if (hasSeverity())
      data.setSeverity(severity.unload());
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
      return "Tube Cuff Leak"
          + "\n\tSeverity: " + getSeverity();
    else
      return "Action not specified properly";
  }
}
