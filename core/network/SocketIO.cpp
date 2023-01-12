/****************************************************************************
 Copyright (c) 2015 Chris Hannon http://www.channon.us
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2023 Bytedance Inc.

 https://axmolengine.github.io/

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

*based on the SocketIO library created by LearnBoost at http://socket.io
*using spec version 1 found at https://github.com/LearnBoost/socket.io-spec

 ****************************************************************************/

#include "network/SocketIO.h"
#include "network/Uri.h"
#include <algorithm>
#include <sstream>
#include <memory>
#include <iterator>
#include "base/ccUTF8.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "network/WebSocket.h"
#include "network/HttpClient.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document-wrapper.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

NS_AX_BEGIN

namespace network
{

// class declarations

class SocketIOPacketV10x;

class SocketIOPacket
{
public:
    enum class SocketIOVersion
    {
        V09x,
        V10x
    };

    SocketIOPacket();
    virtual ~SocketIOPacket();
    void initWithType(std::string_view packetType);
    void initWithTypeIndex(int index);

    std::string toString() const;
    virtual int typeAsNumber() const;
    std::string_view typeForIndex(int index) const;

    void setEndpoint(const std::string_view& endpoint) { _endpoint = endpoint; };
    std::string_view getEndpoint() const { return _endpoint; };
    void setEvent(std::string_view event) { _name = event; };
    std::string_view getEvent() const { return _name; };

    void addData(std::string_view data);
    std::vector<std::string> getData() const { return _args; };
    virtual std::string stringify() const;

    static std::shared_ptr<SocketIOPacket> createPacketWithType(std::string_view type, SocketIOVersion version);
    static std::shared_ptr<SocketIOPacket> createPacketWithTypeIndex(int type, SocketIOVersion version);

protected:
    std::string _pId;                 // id message
    std::string _ack;                 //
    std::string _name;                // event name
    std::vector<std::string> _args;   // we will be using a vector of strings to store multiple data
    std::string _endpoint;            //
    std::string _endpointseparator;   // socket.io 1.x requires a ',' between endpoint and payload
    std::string _type;                // message type
    std::string _separator;           // for stringify the object
    std::vector<std::string> _types;  // types of messages
};

class SocketIOPacketV10x : public SocketIOPacket
{
public:
    SocketIOPacketV10x();
    virtual ~SocketIOPacketV10x();
    int typeAsNumber() const override;
    std::string stringify() const override;

private:
    std::vector<std::string> _typesMessage;
};

SocketIOPacket::SocketIOPacket() : _endpointseparator(""), _separator(":")
{
    _types.push_back("disconnect");
    _types.push_back("connect");
    _types.push_back("heartbeat");
    _types.push_back("message");
    _types.push_back("json");
    _types.push_back("event");
    _types.push_back("ack");
    _types.push_back("error");
    _types.push_back("noop");
}

SocketIOPacket::~SocketIOPacket()
{
    _types.clear();
}

void SocketIOPacket::initWithType(std::string_view packetType)
{
    _type = packetType;
}
void SocketIOPacket::initWithTypeIndex(int index)
{
    _type = _types.at(index);
}

std::string SocketIOPacket::toString() const
{
    std::stringstream encoded;
    encoded << this->typeAsNumber();
    encoded << this->_separator;

    std::string pIdL = _pId;
    if (_ack == "data")
    {
        pIdL += "+";
    }

    // Do not write pid for acknowledgements
    if (_type != "ack")
    {
        encoded << pIdL;
    }
    encoded << this->_separator;

    // Add the endpoint for the namespace to be used if not the default namespace "" or "/", and as long as it is not an
    // ACK, heartbeat, or disconnect packet
    if (_endpoint != "/" && _endpoint != "" && _type != "ack" && _type != "heartbeat" && _type != "disconnect")
    {
        encoded << _endpoint << _endpointseparator;
    }
    encoded << this->_separator;

    if (!_args.empty())
    {
        std::string ackpId = "";
        // This is an acknowledgement packet, so, prepend the ack pid to the data
        if (_type == "ack")
        {
            ackpId += pIdL + "+";
        }

        encoded << ackpId << this->stringify();
    }

    return encoded.str();
}
int SocketIOPacket::typeAsNumber() const
{
    std::string::size_type num = 0;
    auto item                  = std::find(_types.begin(), _types.end(), _type);
    if (item != _types.end())
    {
        num = item - _types.begin();
    }
    return (int)num;
}
std::string_view SocketIOPacket::typeForIndex(int index) const
{
    return _types.at(index);
}

void SocketIOPacket::addData(std::string_view data)
{

    this->_args.emplace_back(std::string{data});
}

std::string SocketIOPacket::stringify() const
{

    std::string outS;
    if (_type == "message")
    {
        outS = _args[0];
    }
    else
    {

        rapidjson::StringBuffer s;
        rapidjson::Writer<rapidjson::StringBuffer> writer(s);

        writer.StartObject();
        writer.String("name");
        writer.String(_name.c_str());

        writer.String("args");

        writer.StartArray();

        for (auto& item : _args)
        {
            writer.String(item.c_str());
        }

        writer.EndArray();
        writer.EndObject();

        outS = s.GetString();

        AXLOGINFO("create args object: %s:", outS.c_str());
    }

    return outS;
}

SocketIOPacketV10x::SocketIOPacketV10x()
{
    _separator         = "";
    _endpointseparator = ",";
    _types.push_back("disconnected");
    _types.push_back("connected");
    _types.push_back("heartbeat");
    _types.push_back("pong");
    _types.push_back("message");
    _types.push_back("upgrade");
    _types.push_back("noop");
    _typesMessage.push_back("connect");
    _typesMessage.push_back("disconnect");
    _typesMessage.push_back("event");
    _typesMessage.push_back("ack");
    _typesMessage.push_back("error");
    _typesMessage.push_back("binarevent");
    _typesMessage.push_back("binaryack");
}

int SocketIOPacketV10x::typeAsNumber() const
{
    std::vector<std::string>::size_type num = 0;
    auto item                               = std::find(_typesMessage.begin(), _typesMessage.end(), _type);
    if (item != _typesMessage.end())
    {  // it's a message
        num = item - _typesMessage.begin();
        num += 40;
    }
    else
    {
        item = std::find(_types.begin(), _types.end(), _type);
        num += item - _types.begin();
    }
    return (int)num;
}

std::string SocketIOPacketV10x::stringify() const
{

    std::string outS;

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);

    writer.StartArray();
    writer.String(_name.c_str());

    for (auto& item : _args)
    {
        writer.String(item.c_str());
    }

    writer.EndArray();

    outS = s.GetString();

    AXLOGINFO("create args object: %s:", outS.c_str());

    return outS;
}

SocketIOPacketV10x::~SocketIOPacketV10x()
{
    _types.clear();
    _typesMessage.clear();
    _type     = "";
    _pId      = "";
    _name     = "";
    _ack      = "";
    _endpoint = "";
}

std::shared_ptr<SocketIOPacket> SocketIOPacket::createPacketWithType(std::string_view type,
                                                                     SocketIOPacket::SocketIOVersion version)
{
    if (version == SocketIOPacket::SocketIOVersion::V09x)
    {
        auto ret = std::make_shared<SocketIOPacket>();
        ret->initWithType(type);
        return ret;
    }
    else if (version == SocketIOPacket::SocketIOVersion::V10x)
    {
        auto ret = std::make_shared<SocketIOPacketV10x>();
        ret->initWithType(type);
        return ret;
    }
    return nullptr;
}

std::shared_ptr<SocketIOPacket> SocketIOPacket::createPacketWithTypeIndex(int type,
                                                                          SocketIOPacket::SocketIOVersion version)
{
    if (version == SocketIOPacket::SocketIOVersion::V09x)
    {
        auto ret = std::make_shared<SocketIOPacket>();
        ret->initWithTypeIndex(type);
        return ret;
    }
    else if (version == SocketIOPacket::SocketIOVersion::V10x)
    {
        auto ret = std::make_shared<SocketIOPacketV10x>();
        ret->initWithTypeIndex(type);
        return ret;
    }
    return nullptr;
}

/**
 *  @brief The implementation of the socket.io connection
 *         Clients/endpoints may share the same impl to accomplish multiplexing on the same websocket
 */
class SIOClientImpl : public WebSocket::Delegate, public std::enable_shared_from_this<SIOClientImpl>
{
private:
    int _heartbeat, _timeout;
    std::string _sid;
    Uri _uri;
    std::string _caFilePath;
    bool _connected;
    SocketIOPacket::SocketIOVersion _version;

    WebSocket* _ws;

    StringMap<SIOClient*> _clients;

public:
    SIOClientImpl(const Uri& uri, std::string_view caFilePath);
    virtual ~SIOClientImpl();

    static std::shared_ptr<SIOClientImpl> create(const Uri& uri, std::string_view caFilePath);

    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    void connect();
    void disconnect();
    bool init();
    void handshake();
    void handshakeResponse(HttpClient* sender, HttpResponse* response);
    void openSocket();
    void heartbeat(float dt);

    SIOClient* getClient(const std::string_view& endpoint);
    void addClient(const std::string_view& endpoint, SIOClient* client);

    void connectToEndpoint(const std::string_view& endpoint);
    void disconnectFromEndpoint(const std::string_view& endpoint);

    void send(std::string_view endpoint, std::string_view s);
    void send(std::string_view endpoint, const std::vector<std::string_view>& s);
    void send(std::shared_ptr<SocketIOPacket>& packet);
    void emit(std::string_view endpoint, std::string_view eventname, std::string_view args);
    void emit(std::string_view endpoint, std::string_view eventname, const std::vector<std::string_view>& args);

    friend class SIOClient;
};

// method implementations

// begin SIOClientImpl methods
SIOClientImpl::SIOClientImpl(const Uri& uri, std::string_view caFilePath)
    : _heartbeat(0)
    , _timeout(0)
    , _uri(uri)
    , _caFilePath(caFilePath)
    , _connected(false)
    , _version(SocketIOPacket::SocketIOVersion::V09x)
    , _ws(nullptr)
{}

SIOClientImpl::~SIOClientImpl()
{
    if (_connected)
        disconnect();

    AX_SAFE_DELETE(_ws);
}

void SIOClientImpl::handshake()
{
    AXLOGINFO("SIOClientImpl::handshake() called");

    std::stringstream pre;

    if (_uri.isSecure())
        pre << "https://";
    else
        pre << "http://";

    pre << _uri.getAuthority() << "/socket.io/1/?EIO=2&transport=polling&b64=true";

    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl(pre.str());
    request->setRequestType(HttpRequest::Type::GET);

    std::weak_ptr<SIOClientImpl> self = shared_from_this();
    auto callback                     = [self](HttpClient* client, HttpResponse* resp) {
        auto conn = self.lock();
        if (conn)
        {
            conn->handshakeResponse(client, resp);
        }
    };
    request->setResponseCallback(callback);
    request->setTag("handshake");

    AXLOGINFO("SIOClientImpl::handshake() waiting");

    if (_uri.isSecure() && !_caFilePath.empty())
    {
        HttpClient::getInstance()->setSSLVerification(_caFilePath);
    }
    HttpClient::getInstance()->send(request);

    request->release();

    return;
}

void SIOClientImpl::handshakeResponse(HttpClient* /*sender*/, HttpResponse* response)
{
    AXLOGINFO("SIOClientImpl::handshakeResponse() called");

    auto tag = response->getHttpRequest()->getTag();
    if (!tag.empty())
    {
        AXLOGINFO("%s completed", tag.data());
    }

    int statusCode        = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, tag.data());
    AXLOGINFO("response code: %ld", statusCode);

    if (!response->isSucceed())
    {
        AXLOGERROR("SIOClientImpl::handshake() failed");
        // AXLOGERROR("error buffer: %s", response->getErrorBuffer());

        for (auto& client : _clients)
        {
            client.second->getDelegate()->onError(client.second, std::to_string(response->getResponseCode()));
        }

        return;
    }

    AXLOGINFO("SIOClientImpl::handshake() succeeded");

    auto buffer = response->getResponseData();
    std::stringstream s;
    s.str("");

    for (const auto& iter : *buffer)
    {
        s << iter;
    }

    AXLOGINFO("SIOClientImpl::handshake() dump data: %s", s.str().c_str());

    std::string res = s.str();
    std::string sid = "";
    int heartbeat = 0, timeout = 0;

    if (res.find('}') != std::string::npos)
    {

        AXLOGINFO("SIOClientImpl::handshake() Socket.IO 1.x detected");
        _version = SocketIOPacket::SocketIOVersion::V10x;
        // sample: 97:0{"sid":"GMkL6lzCmgMvMs9bAAAA","upgrades":["websocket"],"pingInterval":25000,"pingTimeout":60000}

        std::string::size_type a, b;
        a                = res.find('{');
        std::string temp = res.substr(a, res.size() - a);

        // find the sid
        a = temp.find(':');
        b = temp.find(',');

        sid = temp.substr(a + 2, b - (a + 3));

        temp = temp.erase(0, b + 1);

        // chomp past the upgrades
        b = temp.find(',');

        temp = temp.erase(0, b + 1);

        // get the pingInterval / heartbeat
        a = temp.find(':');
        b = temp.find(',');

        std::string heartbeat_str = temp.substr(a + 1, b - a);
        heartbeat                 = atoi(heartbeat_str.c_str()) / 1000;
        temp                      = temp.erase(0, b + 1);

        // get the timeout
        a = temp.find(':');
        b = temp.find('}');

        std::string timeout_str = temp.substr(a + 1, b - a);
        timeout                 = atoi(timeout_str.c_str()) / 1000;
        AXLOGINFO("done parsing 1.x");
    }
    else
    {

        AXLOGINFO("SIOClientImpl::handshake() Socket.IO 0.9.x detected");
        _version = SocketIOPacket::SocketIOVersion::V09x;
        // sample: 3GYzE9md2Ig-lm3cf8Rv:60:60:websocket,htmlfile,xhr-polling,jsonp-polling
        size_t pos = 0;

        pos = res.find(':');
        if (pos != std::string::npos)
        {
            sid = res.substr(0, pos);
            res.erase(0, pos + 1);
        }

        pos = res.find(':');
        if (pos != std::string::npos)
        {
            heartbeat = atoi(res.substr(pos + 1, res.size()).c_str());
        }

        pos = res.find(':');
        if (pos != std::string::npos)
        {
            timeout = atoi(res.substr(pos + 1, res.size()).c_str());
        }
    }

    _sid       = sid;
    _heartbeat = heartbeat;
    _timeout   = timeout;

    openSocket();

    return;
}

void SIOClientImpl::openSocket()
{
    AXLOGINFO("SIOClientImpl::openSocket() called");

    std::stringstream s;

    if (_uri.isSecure())
        s << "wss://";
    else
        s << "ws://";

    switch (_version)
    {
    case SocketIOPacket::SocketIOVersion::V09x:
        s << _uri.getAuthority() << "/socket.io/1/websocket/" << _sid;
        break;
    case SocketIOPacket::SocketIOVersion::V10x:
        s << _uri.getAuthority() << "/socket.io/1/websocket/?EIO=2&transport=websocket&sid=" << _sid;
        break;
    }

    _ws = new (std::nothrow) WebSocket();
    if (!_ws->init(*this, s.str(), nullptr, _caFilePath))
    {
        AX_SAFE_DELETE(_ws);
    }

    return;
}

bool SIOClientImpl::init()
{
    AXLOGINFO("SIOClientImpl::init() successful");
    return true;
}

void SIOClientImpl::connect()
{
    this->handshake();
}

void SIOClientImpl::disconnect()
{
    if (_ws->getReadyState() == WebSocket::State::OPEN)
    {
        std::string s, endpoint;

        if (_version == SocketIOPacket::SocketIOVersion::V09x)
            s = "0::" + endpoint;
        else
            s = "41" + endpoint;
        _ws->send(s);
    }

    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

    _connected = false;

    SocketIO::getInstance()->removeSocket(_uri.getAuthority());

    // Close websocket connection should be at last.
    _ws->close();
}

std::shared_ptr<SIOClientImpl> SIOClientImpl::create(const Uri& uri, std::string_view caFilePath)
{
    SIOClientImpl* s = new (std::nothrow) SIOClientImpl(uri, caFilePath);

    if (s && s->init())
    {
        return std::shared_ptr<SIOClientImpl>(s);
    }

    return nullptr;
}

SIOClient* SIOClientImpl::getClient(const std::string_view& endpoint)
{
    return _clients.at(endpoint);
}

void SIOClientImpl::addClient(const std::string_view& endpoint, SIOClient* client)
{
    _clients.insert(endpoint, client);
}

void SIOClientImpl::connectToEndpoint(const std::string_view& endpoint)
{
    auto packet = SocketIOPacket::createPacketWithType("connect", _version);
    packet->setEndpoint(endpoint);
    this->send(packet);
}

void SIOClientImpl::disconnectFromEndpoint(const std::string_view& endpoint)
{
    _clients.erase(endpoint);

    if (_clients.empty() || endpoint == "/")
    {
        AXLOGINFO("SIOClientImpl::disconnectFromEndpoint out of endpoints, checking for disconnect");

        if (_connected)
            this->disconnect();
    }
    else
    {
        auto path = endpoint == "/" ? "" : endpoint;

        std::string s("0::");
        s += path;

        _ws->send(s);
    }
}

void SIOClientImpl::heartbeat(float /*dt*/)
{
    auto packet = SocketIOPacket::createPacketWithType("heartbeat", _version);

    this->send(packet);

    AXLOGINFO("Heartbeat sent");
}

void SIOClientImpl::send(std::string_view endpoint, const std::vector<std::string_view>& s)
{
    switch (_version)
    {
    case SocketIOPacket::SocketIOVersion::V09x:
    {
        auto packet = SocketIOPacket::createPacketWithType("message", _version);
        packet->setEndpoint(endpoint);
        for (auto& i : s)
        {
            packet->addData(i);
        }
        this->send(packet);
        break;
    }
    case SocketIOPacket::SocketIOVersion::V10x:
    {
        this->emit(endpoint, "message", s);
        break;
    }
    }
}

void SIOClientImpl::send(std::string_view endpoint, std::string_view s)
{
    std::vector<std::string_view> t{s};
    send(endpoint, t);
}

void SIOClientImpl::send(std::shared_ptr<SocketIOPacket>& packet)
{
    std::string req = packet->toString();
    if (_connected)
    {
        AXLOGINFO("-->SEND:%s", req.data());
        _ws->send(req.data());
    }
    else
        AXLOGINFO("Cant send the message (%s) because disconnected", req.c_str());
}

void SIOClientImpl::emit(std::string_view endpoint, std::string_view eventname, std::string_view args)
{
    AXLOGINFO("Emitting event \"%s\"", eventname.c_str());
    auto packet = SocketIOPacket::createPacketWithType("event", _version);
    packet->setEndpoint(endpoint == "/" ? "" : endpoint);
    packet->setEvent(eventname);
    packet->addData(args);
    this->send(packet);
}

void SIOClientImpl::emit(std::string_view endpoint,
                         std::string_view eventname,
                         const std::vector<std::string_view>& args)
{
    AXLOGINFO("Emitting event \"%s\"", eventname.c_str());
    auto packet = SocketIOPacket::createPacketWithType("event", _version);
    packet->setEndpoint(endpoint == "/" ? "" : endpoint);
    packet->setEvent(eventname);
    for (auto& arg : args)
    {
        packet->addData(arg);
    }
    this->send(packet);
}

void SIOClientImpl::onOpen(WebSocket* /*ws*/)
{
    _connected = true;

    auto self = shared_from_this();

    SocketIO::getInstance()->addSocket(_uri.getAuthority(), self);

    if (_version == SocketIOPacket::SocketIOVersion::V10x)
    {
        std::string s =
            "5";  // That's a ping
                  // https://github.com/Automattic/engine.io-parser/blob/1b8e077b2218f4947a69f5ad18be2a512ed54e93/lib/index.js#L21
        _ws->send(s.data());
    }

    std::weak_ptr<SIOClientImpl> selfWeak = shared_from_this();
    auto f                                = [selfWeak](float dt) {
        auto conn = selfWeak.lock();
        if (conn)
            conn->heartbeat(dt);
    };

    Director::getInstance()->getScheduler()->schedule(f, this, (_heartbeat * .9f), false, "heart_beat");

    for (auto& client : _clients)
    {
        client.second->onOpen();
    }
}

void SIOClientImpl::onMessage(WebSocket* /*ws*/, const WebSocket::Data& data)
{
    AXLOGINFO("SIOClientImpl::onMessage received: %s", data.bytes);

    std::string payload = data.bytes;
    int control         = atoi(payload.substr(0, 1).c_str());
    payload             = payload.substr(1, payload.size() - 1);

    SIOClient* c = nullptr;

    switch (_version)
    {
    case SocketIOPacket::SocketIOVersion::V09x:
    {
        std::string msgid, endpoint, s_data, eventname;

        std::string::size_type pos, pos2;

        pos = payload.find(':');
        if (pos != std::string::npos)
        {
            payload.erase(0, pos + 1);
        }

        pos = payload.find(':');
        if (pos != std::string::npos)
        {
            msgid = atoi(payload.substr(0, pos + 1).c_str());
        }
        payload.erase(0, pos + 1);

        pos = payload.find(':');
        if (pos != std::string::npos)
        {
            endpoint = payload.substr(0, pos);
            payload.erase(0, pos + 1);
        }
        else
        {
            endpoint = payload;
        }

        if (endpoint == "")
            endpoint = "/";

        c = getClient(endpoint);

        s_data = payload;

        if (c == nullptr)
            AXLOGINFO("SIOClientImpl::onMessage client lookup returned nullptr");

        switch (control)
        {
        case 0:
            AXLOGINFO("Received Disconnect Signal for Endpoint: %s\n", endpoint.c_str());
            disconnectFromEndpoint(endpoint);
            c->fireEvent("disconnect", payload);
            break;
        case 1:
            AXLOGINFO("Connected to endpoint: %s \n", endpoint.c_str());
            if (c)
            {
                c->onConnect();
                c->fireEvent("connect", payload);
            }
            break;
        case 2:
            AXLOGINFO("Heartbeat received\n");
            break;
        case 3:
            AXLOGINFO("Message received: %s \n", s_data.c_str());
            if (c)
                c->getDelegate()->onMessage(c, s_data);
            if (c)
                c->fireEvent("message", s_data);
            break;
        case 4:
            AXLOGINFO("JSON Message Received: %s \n", s_data.c_str());
            if (c)
                c->getDelegate()->onMessage(c, s_data);
            if (c)
                c->fireEvent("json", s_data);
            break;
        case 5:
            AXLOGINFO("Event Received with data: %s \n", s_data.c_str());

            if (c)
            {
                eventname = "";
                pos       = s_data.find(':');
                pos2      = s_data.find(',');
                if (pos2 > pos)
                {
                    eventname = s_data.substr(pos + 2, pos2 - (pos + 3));
                    s_data    = s_data.substr(pos2 + 9, s_data.size() - (pos2 + 11));
                }

                c->fireEvent(eventname, s_data);
            }

            break;
        case 6:
            AXLOGINFO("Message Ack\n");
            break;
        case 7:
            AXLOGERROR("Error\n");
            // if (c) c->getDelegate()->onError(c, s_data);
            if (c)
                c->fireEvent("error", s_data);
            break;
        case 8:
            AXLOGINFO("Noop\n");
            break;
        }
    }
    break;
    case SocketIOPacket::SocketIOVersion::V10x:
    {
        switch (control)
        {
        case 0:
            AXLOGINFO("Not supposed to receive control 0 for websocket");
            AXLOGINFO("That's not good");
            break;
        case 1:
            AXLOGINFO("Not supposed to receive control 1 for websocket");
            break;
        case 2:
            AXLOGINFO("Ping received, send pong");
            payload = "3" + payload;
            _ws->send(payload);
            break;
        case 3:
            AXLOGINFO("Pong received");
            if (payload == "probe")
            {
                AXLOGINFO("Request Update");
                _ws->send("5");
            }
            break;
        case 4:
        {
            int control2 = payload.at(0) - '0';
            AXLOGINFO("Message code: [%i]", control2);

            std::string endpoint = "";

            std::string::size_type a = payload.find('/');
            std::string::size_type b = payload.find('[');

            if (b != std::string::npos)
            {
                if (a != std::string::npos && a < b)
                {
                    // we have an endpoint and a payload
                    endpoint = payload.substr(a, b - (a + 1));
                }
            }
            else if (a != std::string::npos)
            {
                // we have an endpoint with no payload
                endpoint = payload.substr(a, payload.size() - a);
            }

            // we didn't find and endpoint and we are in the default namespace
            if (endpoint == "")
                endpoint = "/";

            c = getClient(endpoint);

            payload = payload.substr(1);

            if (endpoint != "/")
                payload = payload.substr(endpoint.size());
            if (endpoint != "/" && payload != "")
                payload = payload.substr(1);

            switch (control2)
            {
            case 0:
                AXLOGINFO("Socket Connected");
                if (c)
                {
                    c->onConnect();
                    c->fireEvent("connect", payload);
                }
                break;
            case 1:
                AXLOGINFO("Socket Disconnected");
                disconnectFromEndpoint(endpoint);
                c->fireEvent("disconnect", payload);
                break;
            case 2:
            {
                AXLOGINFO("Event Received (%s)", payload.c_str());

                std::string::size_type payloadFirstSlashPos  = payload.find('\"');
                std::string::size_type payloadSecondSlashPos = payload.substr(payloadFirstSlashPos + 1).find('\"');

                std::string eventname =
                    payload.substr(payloadFirstSlashPos + 1, payloadSecondSlashPos - payloadFirstSlashPos + 1);

                AXLOGINFO("event name %s between %i and %i", eventname.c_str(), payloadFirstSlashPos,
                          payloadSecondSlashPos);

                payload = payload.substr(payloadSecondSlashPos + 4, payload.size() - (payloadSecondSlashPos + 5));

                if (c)
                    c->fireEvent(eventname, payload);
                if (c)
                    c->getDelegate()->onMessage(c, payload);
            }
            break;
            case 3:
                AXLOGINFO("Message Ack");
                break;
            case 4:
                AXLOGERROR("Error");
                if (c)
                    c->fireEvent("error", payload);
                break;
            case 5:
                AXLOGINFO("Binary Event");
                break;
            case 6:
                AXLOGINFO("Binary Ack");
                break;
            }
        }
        break;
        case 5:
            AXLOGINFO("Upgrade required");
            break;
        case 6:
            AXLOGINFO("Noop\n");
            break;
        }
    }
    break;
    }

    return;
}

void SIOClientImpl::onClose(WebSocket* /*ws*/)
{
    if (!_clients.empty())
    {
        for (auto& client : _clients)
        {
            client.second->socketClosed();
        }
        // discard this client
        _connected = false;
        if (Director::getInstance())
            Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);

        SocketIO::getInstance()->removeSocket(_uri.getAuthority());
    }
}

void SIOClientImpl::onError(WebSocket* /*ws*/, const WebSocket::ErrorCode& error)
{
    AXLOGERROR("Websocket error received: %d", static_cast<int>(error));
}

// begin SIOClient methods
SIOClient::SIOClient(const std::string_view& path,
                     std::shared_ptr<SIOClientImpl>& impl,
                     SocketIO::SIODelegate& delegate)
    : _path(path), _connected(false), _socket(impl), _delegate(&delegate)
{}

SIOClient::~SIOClient()
{
    if (isConnected())
    {
        _socket->disconnectFromEndpoint(_path);
    }
}

void SIOClient::onOpen()
{
    if (_path != "/")
    {
        _socket->connectToEndpoint(_path);
    }

    setConnected(true);
}

void SIOClient::onConnect()
{
    setConnected(true);
}

void SIOClient::send(std::string_view s)
{
    std::vector<std::string_view> t{s};
    send(t);
}

void SIOClient::send(const std::vector<std::string_view>& s)
{
    if (isConnected())
    {
        _socket->send(_path, s);
    }
    else
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::emit(std::string_view eventname, std::string_view args)
{
    if (isConnected())
    {
        _socket->emit(_path, eventname, args);
    }
    else
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::emit(std::string_view eventname, const std::vector<std::string_view>& args)
{
    if (isConnected())
    {
        _socket->emit(_path, eventname, args);
    }
    else
    {
        _delegate->onError(this, "Client not yet connected");
    }
}

void SIOClient::disconnect()
{
    setConnected(false);
    _socket->disconnectFromEndpoint(_path);
    this->release();
}

void SIOClient::socketClosed()
{
    setConnected(false);
    _delegate->onClose(this);
    this->release();
}

bool SIOClient::isConnected() const
{
    return _socket && _socket->_connected && _connected;
}

void SIOClient::setConnected(bool connected)
{
    _connected = connected;
}

void SIOClient::on(std::string_view eventName, SIOEvent e)
{
    _eventRegistry[eventName] = e;
}

void SIOClient::fireEvent(std::string_view eventName, std::string_view data)
{
    AXLOGINFO("SIOClient::fireEvent called with event name: %s and data: %s", eventName.c_str(), data.c_str());

    _delegate->fireEventToScript(this, eventName, data);

    if (_eventRegistry[eventName])
    {
        SIOEvent e = _eventRegistry[eventName];

        e(this, data);

        return;
    }

    AXLOGINFO("SIOClient::fireEvent no native event with name %s found", eventName.c_str());
}

void SIOClient::setTag(std::string_view tag)
{
    _tag = tag;
}

// begin SocketIO methods
SocketIO* SocketIO::_inst = nullptr;

SocketIO::SocketIO() {}

SocketIO::~SocketIO() {}

SocketIO* SocketIO::getInstance()
{
    if (nullptr == _inst)
        _inst = new (std::nothrow) SocketIO();

    return _inst;
}

void SocketIO::destroyInstance()
{
    AX_SAFE_DELETE(_inst);
}

SIOClient* SocketIO::connect(std::string_view uri, SocketIO::SIODelegate& delegate)
{
    return SocketIO::connect(uri, delegate, "");
}

SIOClient* SocketIO::connect(std::string_view uri, SocketIO::SIODelegate& delegate, std::string_view caFilePath)
{
    Uri uriObj = Uri::parse(uri);

    std::shared_ptr<SIOClientImpl> socket = SocketIO::getInstance()->getSocket(uriObj.getAuthority());
    SIOClient* c                          = nullptr;

    auto path = uriObj.getPath();
    if (path == "")
        path = "/";

    if (socket == nullptr)
    {
        // create a new socket, new client, connect
        socket = SIOClientImpl::create(uriObj, caFilePath);

        c = new (std::nothrow) SIOClient(path, socket, delegate);

        socket->addClient(path, c);

        socket->connect();
    }
    else
    {
        // check if already connected to endpoint, handle
        c = socket->getClient(path);

        if (c == nullptr)
        {
            c = new (std::nothrow) SIOClient(path, socket, delegate);

            socket->addClient(path, c);

            socket->connectToEndpoint(path);
        }
        else
        {
            AXLOG("SocketIO: disconnect previous client");
            c->disconnect();

            AXLOG("SocketIO: recreate a new socket, new client, connect");
            std::shared_ptr<SIOClientImpl> newSocket = SIOClientImpl::create(uriObj, caFilePath);
            SIOClient* newC                          = new (std::nothrow) SIOClient(path, newSocket, delegate);

            newSocket->addClient(path, newC);
            newSocket->connect();

            return newC;
        }
    }

    return c;
}

std::shared_ptr<SIOClientImpl> SocketIO::getSocket(const std::string_view& uri)
{
    auto p = _sockets.find(uri);
    if (p == _sockets.end())
        return nullptr;
    return p->second.lock();
}

void SocketIO::addSocket(const std::string_view& uri, std::shared_ptr<SIOClientImpl>& socket)
{
    _sockets.emplace(uri, socket);
}

void SocketIO::removeSocket(const std::string_view& uri)
{
    _sockets.erase(uri);
}

}  // namespace network

NS_AX_END
