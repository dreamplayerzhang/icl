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

#include <ICLIO/UnicapConvertEngine.h>
#include <ICLIO/UnicapFormat.h>
#include <ICLIO/UnicapDevice.h>
#include <ICLCore/CoreFunctions.h>

namespace icl{

  void UnicapConvertEngine::cvtNative(const icl8u *rawData, ImgBase **ppoDst){
    depth d = depth8u; // maybe we can try to estimate depth from m_poDevice
    UnicapFormat f = m_poDevice->getCurrentUnicapFormat();
    ImgParams p(f.getSize(),formatRGB); // here we use RGB as default
    ensureCompatible(ppoDst,d,p);
    cvt(rawData,p,d,ppoDst);
  }

}
