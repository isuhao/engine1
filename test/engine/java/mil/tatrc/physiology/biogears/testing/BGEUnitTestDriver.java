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
package mil.tatrc.physiology.biogears.testing;

import java.util.ArrayList;
import java.util.List;

import mil.tatrc.physiology.utilities.FileUtils;
import mil.tatrc.physiology.utilities.Log;
import mil.tatrc.physiology.utilities.UnitConverter;
import mil.tatrc.physiology.utilities.testing.TestDriver;
import mil.tatrc.physiology.utilities.testing.TestDriver.TestJob;

public class BGEUnitTestDriver implements TestDriver.Executor
{
  
  static
  {
    UnitConverter.initialize(System.getProperty("user.dir"));
    List<String> libs = new ArrayList<String>();
    libs.add("BioGearsEngine");
    libs.add("BioGearsEngineTest");
    libs.add("BioGearsEngineJNI");         
    FileUtils.loadLibraries(libs);
  }
  
  protected long nativeObj;
  protected native long nativeAllocate();
  protected native void nativeDelete(long nativeObj);
  protected native void nativeExecute(long nativeObj, String testName, String outputDir);
  
  public BGEUnitTestDriver()
  {
    this.nativeObj = nativeAllocate();
  }
  
  protected void finalize()
  {
    nativeDelete(this.nativeObj);
  }
  
  public boolean ExecuteTest(TestJob job)
  {
    nativeExecute(this.nativeObj,job.name,job.computedDirectory);
    Log.info("Completed running "+job.name);
    return true;
  }
  
  public static void main(String[] args)
  {
    TestDriver.main(args);
  }

}

