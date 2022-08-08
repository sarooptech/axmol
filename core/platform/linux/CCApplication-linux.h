/****************************************************************************
Copyright (c) 2011      Laschweinski
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

https://axys1.github.io/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once

#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>
#include <chrono>

NS_AX_BEGIN
class Rect;

class Application : public ApplicationProtocol
{
public:
    /**
     * @js ctor
     */
    Application();
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Application();

    /**
     @brief Callback by Director for limit FPS.
     @param interval    The time, which expressed in second in second, between current frame and next.
     */
    virtual void setAnimationInterval(float interval) override;

    /**
     @brief Run the message loop.
     */
    int run();

    /**
     @brief Get current application instance.
     @return Current application instance pointer.
     */
    static Application* getInstance();

    /** @deprecated Use getInstance() instead */
    AX_DEPRECATED_ATTRIBUTE static Application* sharedApplication();

    /* override functions */
    virtual LanguageType getCurrentLanguage() override;

    /**
    @brief Get current language iso 639-1 code
    @return Current language iso 639-1 code
    */
    virtual const char* getCurrentLanguageCode() override;

    /**
    @brief Get application version
    */
    virtual std::string getVersion() override;

    /**
     @brief Open url in default browser
     @param String with url to open.
     @return true if the resource located by the URL was successfully opened; otherwise false.
     */
    virtual bool openURL(std::string_view url) override;

    /**
     *  Sets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->setSearchPaths() instead.
     */
    AX_DEPRECATED_ATTRIBUTE void setResourceRootPath(std::string_view rootResDir);

    /**
     *  Gets the Resource root path.
     *  @deprecated Please use FileUtils::getInstance()->getSearchPaths() instead.
     */
    AX_DEPRECATED_ATTRIBUTE std::string_view getResourceRootPath();

    /**
     @brief Get target platform
     */
    virtual Platform getTargetPlatform() override;

protected:
    std::chrono::nanoseconds _animationInterval;  // nano seconds
    std::string _resourceRootPath;

    static Application* sm_pSharedApplication;
};

NS_AX_END
