/********************************************************************
**                Image Component Library (ICL)                    **
**                                                                 **
** Copyright (C) 2006-2012 CITEC, University of Bielefeld          **
**                         Neuroinformatics Group                  **
** Website: www.iclcv.org and                                      **
**          http://opensource.cit-ec.de/projects/icl               **
**                                                                 **
** File   : include/ICLIO/FileGrabberPlugin.h                      **
** Module : ICLIO                                                  **
** Authors: Christof Elbrechter                                    **
**                                                                 **
**                                                                 **
** Commercial License                                              **
** ICL can be used commercially, please refer to our website       **
** www.iclcv.org for more details.                                 **
**                                                                 **
** GNU General Public License Usage                                **
** Alternatively, this file may be used under the terms of the     **
** GNU General Public License version 3.0 as published by the      **
** Free Software Foundation and appearing in the file LICENSE.GPL  **
** included in the packaging of this file.  Please review the      **
** following information to ensure the GNU General Public License  **
** version 3.0 requirements will be met:                           **
** http://www.gnu.org/copyleft/gpl.html.                           **
**                                                                 **
** The development of this software was supported by the           **
** Excellence Cluster EXC 277 Cognitive Interaction Technology.    **
** The Excellence Cluster EXC 277 is a grant of the Deutsche       **
** Forschungsgemeinschaft (DFG) in the context of the German       **
** Excellence Initiative.                                          **
**                                                                 **
*********************************************************************/

#pragma once

#include <ICLUtils/File.h>
#include <ICLCore/Img.h>

namespace icl{
  namespace io{
    /// interface for ImageGrabber Plugins for reading different file types \ingroup FILEIO_G
    class FileGrabberPlugin{
      public:
  #ifdef HAVE_LIBJPEG
      friend class JPEGDecoder;
  #endif
  
      virtual ~FileGrabberPlugin() {}
      /// pure virtual grab function
      virtual void grab(utils::File &file, core::ImgBase **dest)=0;
  
      protected:
      /// Internally used collection of image parameters
      struct HeaderInfo{
        core::format imageFormat; ///!< format
        core::depth imageDepth;   ///!< depth
        utils::Rect roi;           ///!< roi rect
        utils::Time time;          ///!< time stamp
        utils::Size size;          ///!< image size
        int channelCount;   ///!< image channel count
        int imageCount;     ///!< image count (e.g. when writing color images as .pgm gray-scale images)
      };
    };  
  } // namespace io
}

