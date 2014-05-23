/*
 * Copyright 2014 (c) Daniel Rosser, danoli3.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */


#include "ofxZipUtils.h"

ofxZipUtils::ofxZipUtils() {
    // ctor
    dezip = NULL;
    comzip = NULL;
}

ofxZipUtils::~ofxZipUtils() {
    // dtor
    if(dezip) {
        delete dezip;
        dezip = NULL;
    }
    
    if(comzip) {
        delete comzip;
        comzip = NULL;
    }
}



bool ofxZipUtils::unzip(string zipFilePath, string destination)
{
    //-------------------------------------- Work out oF related file locations.
    zipFilePath = ofToDataPath(zipFilePath);
    destination = ofToDataPath(destination);
    ofLog(logLevel, "ofxZipUtils::Unzipping: " + zipFilePath + " to " + destination);
    
    ifstream *infile = new ifstream();
    infile->open(zipFilePath.c_str());
    ofxZipUtilsHandler handler;
    handler.logLevel = logLevel;
    
    dezip = new Poco::Zip::Decompress (*infile, *(new Poco::Path(destination)));
    dezip->EError += Poco::Delegate<ofxZipUtilsHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(&handler, &ofxZipUtilsHandler::onError);
    dezip->EOk +=Poco::Delegate<ofxZipUtilsHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const Poco::Path> >(&handler, &ofxZipUtilsHandler::onOk);
    dezip->decompressAllFiles();
    dezip->EError -= Poco::Delegate<ofxZipUtilsHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string> >(&handler, &ofxZipUtilsHandler::onError);
    dezip->EOk -=Poco::Delegate<ofxZipUtilsHandler, std::pair<const Poco::Zip::ZipLocalFileHeader, const Poco::Path> >(&handler, &ofxZipUtilsHandler::onOk);
    
    if(handler.isSuccessful) {
        return true;
    } else {
        return false;
    }
}

#warning *** ofxZipUtils zipping to archive not working yet!
bool ofxZipUtils::zipDirectory(string folderPath, string zipPath, bool recursive, bool excludeRoot, ofxZipUtilsCompression compression) {
    //-------------------------------------- Work out oF related file locations.
    folderPath = ofToDataPath(folderPath);
    zipPath = ofToDataPath(zipPath);

    ofLog(logLevel, "ofxZipUtils::Zipping: " + folderPath + " to " + zipPath);
   
    Poco::Path pathIn(folderPath);
    Poco::Path pathOut(zipPath);
    Poco::FileInputStream in(folderPath);
	Poco::FileOutputStream out(zipPath);

    ofxZipUtilsHandler handler;
    handler.logLevel = logLevel;
    
//    comzip = new Poco::Zip::Compress(out, true); // true for local files
////    comzip->EDone += Poco::Delegate<ofxZipUtilsHandler, const Poco::Zip::ZipLocalFileHeader>(&handler, &ofxZipUtilsHandler::onDone); // delegate not working yet
//    comzip->addRecursive(pathIn,((Poco::Zip::ZipCommon::CompressionLevel)((int)compression)), excludeRoot, pathOut);
//    comzip->close();
////    comzip->EDone -= Poco::Delegate<ofxZipUtilsHandler, const Poco::Zip::ZipLocalFileHeader>(&handler, &ofxZipUtilsHandler::onDone); // delegate not working yet
//    
    return false;
//    if(handler.isSuccessful) {
//        return true;
//    } else {
//        return false;
//    }
    
    
}



