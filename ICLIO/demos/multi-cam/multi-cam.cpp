/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2013 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : ICLIO/demos/multi-cam/multi-cam.cpp                    **
** Module : ICLIO                                                  **
** Authors: Christof Elbrechter                                    **
**                                                                 **
**                                                                 **
** GNU LESSER GENERAL PUBLIC LICENSE                               **
** This file may be used under the terms of the GNU Lesser General **
** Public License version 3.0 as published by the                  **
**                                                                 **
** Free Software Foundation and appearing in the file LICENSE.LGPL **
** included in the packaging of this file.  Please review the      **
** following information to ensure the license requirements will   **
** be met: http://www.gnu.org/licenses/lgpl-3.0.txt                **
**                                                                 **
** The development of this software was supported by the           **
** Excellence Cluster EXC 277 Cognitive Interaction Technology.    **
** The Excellence Cluster EXC 277 is a grant of the Deutsche       **
** Forschungsgemeinschaft (DFG) in the context of the German       **
** Excellence Initiative.                                          **
**                                                                 **
********************************************************************/

#include <ICLQt/Common.h>
#include <ICLIO/FileWriter.h>

VSplit gui;

std::vector<SmartPtr<GenericGrabber> > gs;

void init(){
  for(int i=1;i<=4;++i){
    std::string arg=str("-input")+str(i);
    if(pa(arg)){
      try{
        SmartPtr<GenericGrabber> gr = SmartPtr<GenericGrabber>(new GenericGrabber());
        gr -> init(pa(arg));
        gr -> useDesired<Size>(pa("-size"));
        if(pa("-t")){
          gr -> setPropertyValue("trigger-power","on"); // or off?
        }
        gs.push_back(gr);
      }catch(const ICLException &ex){
        WARNING_LOG("unable to instantiate grabber from argument " << arg << "(skipping)");
      }
    }
  }
  if(!gs.size()){
    ERROR_LOG("program was unable to instantiate at least one input device (aborting)");
    exit(-1);
  }
  
  for(unsigned int i=0;i<gs.size();++i){
    gui << Image().handle("image"+str(i)).minSize(12,8);
  }
  gui << ( HBox()
           << Fps(10).handle("fps").label("FPS")
           << CamCfg()
           )
      << Show();
}


void run(){
  FPSHandle fps = gui["fps"];
  
  while(1){
    for(unsigned int i=0;i<gs.size();i++){
      gui["image"+str(i)] = gs[i]->grab();
    }
    fps.render();
  }
}


int main(int n, char **ppc){
  pa_explain
  ("-size","grabbing size")
  ("-t","use external trigger (only for devices that support this)")
  ("-r","reset dc-bus before instantiating grabbers")
  ("-input1","first possible input device and params")
  ("-input2","second possible input device and params")
  ("-input3","third possible input device and params")
  ("-input4","fourth possible input device and params");
  
  return ICLApp(n,ppc,"-size|-s(Size=QVGA) "
                "-external-trigger|-t [m]-input1|-1(device,device-params) -reset-bus|-r "
                "-input2|-2(device,device-params) -input3|-3(device,device-params) "
                "-input4|-4(device,device-params)",init,run).exec();
  
}
