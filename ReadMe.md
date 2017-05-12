BioGears Engine 
===============

The BioGears engine is a C++ library for human physiology simulation.
It is intended to provide accurate and consistent physiology data to medical education, research, and training technologies. 
The libraries built (*.dll/*.so) can be integrated with standalone applications, hardware simulators and sensor interfaces, and other physiology models of all fidelities.

The BioGears engine high-level objectives include:
-   Create a publicly available physiology research platform that
    enables accurate and consistent simulated physiology across training
    applications
-   Lower the barrier to create medical training content
-   Engage the community to develop and extend physiology models
-   Meet the training needs of the military
-   Expand the body of knowledge regarding the use of simulated
    physiology for medical education


## Build Environment

BioGears utilizes C++11, here is a list of popular compilers and their initial version to implement all of C++11 :
- GCC 4.8.1 and later
- Clang 3.3 and later
- MSVC 2015 and later

If you have any questions\comments, don't hesitate to email aaron.bray@kitware.com

While BioGears automatically pulls many libraries it needs to compile, 
you will still need to have the following tools installed (along with your choice of C++ compiler) :

### CMake
Go to the cmake website, `https://cmake.org/download`, and download the appropriate distribution.
Ensure that cmake bin is on your PATH and available in your cmd/bash shell.

### Java JDK

The test suite and data generate tools used by BioGears is written in Java.
While there is no dependency on Java when integrating BioGears with your application, it is currently required to build/develop BioGears.
You can get the </a> 

Add a JAVA_HOME environment variable to point to the Java installation and add it to the system PATH.<br>
There are many ways to do this, here is a simple walk through to get you going with a JDK.

#### Windows
- Download the Windows x64 JDK <a href="http://www.oracle.com/technetwork/java/javase/downloads/index.html">here.
- Run the installer.
- Goto your Control Panel->System and click Advanced system settings on the left. <br>
- Click the 'Environment Variables' button and add JAVA_HOME as a new 'System variables'.<br>
- Set the Value to something like: C:\Program Files\Java\jdk1.8.0_121<br>
    - It's a good idea to add the JDK to the system PATH by adding this to the beginning: %JAVA_HOME%/bin;
- Make sure to start a new cmd window.<br>

#### Linux
- You can find where java is by running `update-alternatives --list java <br>
 - If you don't have a Java SDK, I recommend using an installer like Synaptic
 - Search for 'jdk' by name and install the 'openjdk-8-jdk' 
- You can then add the JAVA_HOME variable to a bash shell by typing
    - export JAVA_HOME=(a path listed by a call to updata-alternatives --list java)
    - For example : export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
- You can also add it to your ~/.bash_profile, or related file (.bashrc, .zshrc, .cshrc, setenv.sh), to get the path in all shells

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
JAVA_HOME='/usr/lib/jvm/java-8-openjdk-amd64'
export JAVA_HOME
PATH="$JAVA_HOME/bin:$PATH"
export PATH
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Building BioGears

The BioGears build is directed by CMake to ensure it can be build on various platforms. 
The code is build by a CMake 'superbuild', meaning as part of the build, CMake will download any
dependent libraries and compile those before it builds BioGears. 
The build is also out of source, meaning the code base is seperated from the build files.
This means you will need two folders for BioGears, one for the source code and one for the build files.
Generally, I create a single directory to house these two folders.
Here is the quickest way to pull and build BioGears via a cmd/bash shell:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
mkdir BioGears
cd BioGears
mkdir src
cd src
git clone https://gitlab.kitware.com/bioGears/biogears
cd ..
mkdir builds
cd builds
# Feel free to make subfolders here, like msvc2017x64 or something
# Generate a make file/msvc solution for the external dependencies
# Note you need to provide cmake the source directory at the end (relative or absolute)
# Run CMake (it will use the system default compiler if you don't provide options or use the CMake GUI)
cmake -DCMAKE_BUILD_TYPE:STRING=Release ../src
# Build the install target/project
# On Linux/OSX/MinGW 
make install 
# For MSVC
# Open the OuterBuild.sln and build the INSTALL project (It will build everything!)
# When the build is complete, MSVC users can close the OuterBuild solution, and open the BioGears.sln located in the InnerBuild directory.
# Unix based systems can also change to this directory for building as well to build specific BioGears components
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Running and Testing

BioGears provides a few driver programs to execute the physiology libraries built.

<b> !! NOTE : The 'bin' directory being refered to below is the bin directory in your <build directory>/install/bin NOT the src/bin directory !! </b>

### BioGears Scenario Driver

The BioGears Scenario Driver is a simple C++ driver that reads a scenario XML file and creates a CSV file with results.
See <a href="https://biogearsengine.com/documentation/_scenario_x_m_l_file.html">here</a> for more info.

You will need to download the latest scenario/verification zip <a href="https://github.com/BioGearsEngine/Engine/releases/download/6.1.1-beta/BioGears_6.1.1-beta-verification-all.zip">here</a> and put the verification directory at the root of your source tree.
In the near future, we will link the verification data to this repository, so it will be downloaded automatically.

To run the driver, change directory in your cmd/bash shell to the build/install/bin directory and execute the following :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
# First ensure the release directory (or debug if that is what you are running) is on your path
PATH=%PATH%;./release # for windows
PATH=$PATH:./release # for linux
BioGearsScenarioDriver ../verification/Scenarios/Patient/BasicStandard.xml 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
<b> .csv and .log files will be placed in the bin directory </b>

If you are going to run the BioGearsSceanrioDriver through visual studio follow these steps
- Right-click the BioGearsScenarioDriver project and select 'Set as Startup Project'
- Right-click the Project and select settings
- Make sure you are on the appropriate configuration in the Configuration drop down. The one you intend to run
  - You probably want to do this for all configuration in the solution
- Click on 'Configuration Options->Debugging' on the left tree in the properties dialog
- Put the directory to your bin directory as the 'Working Directory'
- Enter the relative path to the associated directory containing the dlls for your selected configuration into the 'Envirionment' field.
  - For example, this is what you would enter to run against the 64bit release dll's: PATH=PATH;./release
  - and this is what you would enter to run against the 32bit release dll's : PATH=PATH;./release32
  
<b> You will also want to do this for the UnitTestDriver if you want to run that through visual studio as well </b>

### Java Based Testing Suite

BioGears provides a test harnes, written in Java, that will process a ./test/config/*.config file in the source tree by doing the following :
- For each line in the config file :
    - Run the BioGearsScenarioDriver or UnitTestDriver (depends on the line)
    - Compare the generated csv results to a baseline csv file and report any differences
    - Generate an plot image file for each data column of the csv file over the time of the scenario

To run the test driver change directory in your cmd/bash shell to the build/install/bin directory and execute the run.cmake in the following way :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~bash
cmake -DTYPE:STRING=<option> -P run.cmake 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Where <option> can be one of the following :
- genData - Generate xml files from data in the ../data/BioGears.xlxs file (Patients, Substances, etc.)
- genStates - Generate BioGears state file for every patient at the point where the patient completed stabilization (Simulation time 0s)
- Any of the testing configurations found in ../test/config without the suffix
  - For Example : DebugRun, CDMUnitTests, ValidationSystems, VerificationScenarios, etc.
  - With exception of the Characterize.config, this is a legacy testing configuration that will not work  
- SystemValidation - Will run the ../test/config/ValidationSystems configuration plus create validation tables from comparing results to ../test/validation
- PatientValidation - Will run the ../test/config/ValidationPatients configuration plus create validation tables from comparing results to ../test/validation

<b>Results will be place in the build/install/bin/test_results directory </b>

#### Configuration Files

The configuration files, referenced above, provied the testing suite direction on how to execute BioGears and what to do with the results.


## Creating the Sofware Developmenet Kit (SDK)

In the BioGears source code tree is an sdk folder.
This folder provides examples of how to use BioGears.
During the build and install, all the header and library files needed to integrate BioGears into your application are placed into the build/install folder
External applications only need to reference this directory for headers and libraries for their build.

Note, your application will still need to execute within the build/install/bin directory as it has the binaries and data files in it.

There is a CMakeLists.txt in the sdk folder that you can also run to build and run any of the provided howto examples.
You can edit the BioGearsEngineHowTo.cpp to run a particular example, and even code in the HowToSandbox.cpp to run your own engine!


There is also an example of using a Java based BioGears interface with an eclipse project you can explore as well.

## Programmatics

BioGears began at Applied Research Associates, Inc. (ARA) with oversight from 
the Telemedicine and Advanced Technology Research Center (TATRC) under award W81XWH-13-2-0068

All files are released under the Apache 2.0 license
