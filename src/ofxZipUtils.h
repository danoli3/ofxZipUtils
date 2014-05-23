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

#pragma once
#include "ofMain.h"

#ifdef OF_USING_POCO
#include <Poco/Zip/ZipArchive.h>
#include <Poco/Zip/Compress.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Path.h>
#include "Poco/Delegate.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"

#include <istream>
#include <ostream>

enum ofxZipUtilsCompression {
    NORMAL_COMPRESSION    = 0,
    MAXIMUM_COMPRESSION   = 1,
    FAST_COMPRESSION      = 2,
    SUPERFAST_COMPRESSION = 3
};

//-------------------------------------------
class ofxZipUtils
{
public:
    ofxZipUtils();
    ~ofxZipUtils();
    
    
    bool unzip(string zipFilePath, string destination);
    bool zipDirectory(string folderPath, string zipPath, bool recursive=true, bool excludeRoot=true, ofxZipUtilsCompression compression=NORMAL_COMPRESSION);

    ofLogLevel logLevel;
    
private:
    Poco::Zip::Decompress *dezip;
    Poco::Zip::Compress *comzip;
};


//--------------------------------------------
class ofxZipUtilsHandler
{
public:
	ofxZipUtilsHandler() {
        isSuccessful = false;
        logLevel = OF_LOG_VERBOSE;
	}
	~ofxZipUtilsHandler(){
	}
    
	void onError(const void*, std::pair<const Poco::Zip::ZipLocalFileHeader, const std::string>& info){
		ofLog(OF_LOG_ERROR, "ofxZipUtils: Failed to Unzip: " + info.second);
        isSuccessful = false;
    }
    
	void onOk(const void*, std::pair<const Poco::Zip::ZipLocalFileHeader, const Poco::Path>& info){
		ofLog(logLevel, "ofxZipUtils: Unzipped: " + info.second.toString());
        isSuccessful = true;
	}
    
    void onDone(const void*, const Poco::Zip::ZipLocalFileHeader){
        ofLog(logLevel, "ofxZipUtils: Zipped");
        isSuccessful = true;
    }
    
    bool isSuccessful;
    ofLogLevel logLevel;
};

#else
    #warning *** ofxZipUtils Requires Poco Library
#endif
