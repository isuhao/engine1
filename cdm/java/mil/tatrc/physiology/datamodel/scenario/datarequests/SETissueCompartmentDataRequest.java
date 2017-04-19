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

package mil.tatrc.physiology.datamodel.scenario.datarequests;

import mil.tatrc.physiology.datamodel.CDMSerializer;
import mil.tatrc.physiology.datamodel.bind.TissueCompartmentDataRequestData;

public class SETissueCompartmentDataRequest extends SECompartmentDataRequest
{
  public SETissueCompartmentDataRequest()
  {

  }

  public void reset()
  {
    super.reset();
  }

  public boolean load(TissueCompartmentDataRequestData in)
  {
    super.load(in);    
    return true;
  }  
  public TissueCompartmentDataRequestData unload()
  {
    TissueCompartmentDataRequestData data = CDMSerializer.objFactory.createTissueCompartmentDataRequestData();
    unload(data);
    return data;
  }
  protected void unload(TissueCompartmentDataRequestData data)
  {
    super.unload(data);    
  }
}
