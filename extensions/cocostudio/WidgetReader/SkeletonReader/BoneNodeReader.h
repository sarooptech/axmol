/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.

https://axis-project.github.io/

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

#ifndef __BONENODEREADER_H_
#define __BONENODEREADER_H_

#include "WidgetReader/NodeReaderProtocol.h"
#include "WidgetReader/NodeReaderDefine.h"

class BoneNodeReader : public axis::Ref, public cocostudio::NodeReaderProtocol
{
    DECLARE_CLASS_NODE_READER_INFO

public:
    BoneNodeReader();
    ~BoneNodeReader();

    static BoneNodeReader* getInstance();
    /** @deprecated Use method destroyInstance() instead */
    CC_DEPRECATED_ATTRIBUTE static void purge();
    static void destroyInstance();

    flatbuffers::Offset<flatbuffers::Table> createOptionsWithFlatBuffers(
        pugi::xml_node objectData,
        flatbuffers::FlatBufferBuilder* builder) override;
    void setPropsWithFlatBuffers(axis::Node* node, const flatbuffers::Table* boneOptions) override;

    axis::Node* createNodeWithFlatBuffers(const flatbuffers::Table* boneOptions) override;
};

#endif /* defined(__BONENODEREADER_H_) */
