/*************************************************************************** 
**                                                                        **
** Copyright (C) 2006-2010 neuroinformatics group (vision)                **
**                         University of Bielefeld                        **
**                         nivision@techfak.uni-bielefeld.de              **
**                                                                        **
** This file is part of the ICLIO module of ICL                           **
**                                                                        **
** Commercial License                                                     **
** Commercial usage of ICL is possible and must be negotiated with us.    **
** See our website www.iclcv.org for more details                         **
**                                                                        **
** GNU General Public License Usage                                       **
** Alternatively, this file may be used under the terms of the GNU        **
** General Public License version 3.0 as published by the Free Software   **
** Foundation and appearing in the file LICENSE.GPL included in the       **
** packaging of this file.  Please review the following information to    **
** ensure the GNU General Public License version 3.0 requirements will be **
** met: http://www.gnu.org/copyleft/gpl.html.                             **
**                                                                        **
***************************************************************************/ 

#ifdef HAVE_XCF
#ifndef ICL_XCF_MEMORY_GRABBER_H
#define ICL_XCF_MEMORY_GRABBER_H

#include <ICLIO/Grabber.h>
#include <ICLUtils/SmartPtr.h>

namespace icl{
  
  /** \cond */
  class XCFMemoryGrabberImpl;
  struct XCFMemoryGrabberImplDelOp{ 
    static void delete_func(XCFMemoryGrabberImpl *impl);
  };
  /** \endcond */
  
  
  /// Grabber implementation to acquire images from an ActiveMemory Server application
  class XCFMemoryGrabber : public Grabber{
    public:
    /// Create a new instance
    XCFMemoryGrabber(const std::string &memoryName,const std::string &imageXPath="//IMAGE");

    /// get next image
    virtual const ImgBase *grabUD(ImgBase **ppoDst=0);
   
    // TODO setIgnoreDesiredParams(bool) 
    // TODO const xmltio::TIODocment *getLastDocument() const;
    SmartPtrBase<XCFMemoryGrabberImpl,XCFMemoryGrabberImplDelOp> impl;
  };
  
}


#endif // ICL_XCF_MEMORY_GRABBER_H

#endif // HAVE_XCF
