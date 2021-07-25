/***************************************************************************************************
 * MIT License
 *
 * Copyright (c) 2021 antmuse@live.cn/antmuse@qq.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
***************************************************************************************************/


#ifndef APP_CONNECTOR_H
#define	APP_CONNECTOR_H

#include "Loop.h"
#include "Net/HandleTCP.h"

namespace app {
namespace net {


class TcpProxy {
public:
    TcpProxy(Loop& loop);

    ~TcpProxy();


    static void funcOnLink(net::RequestTCP* it) {
        TcpProxy* con = new TcpProxy(*it->mHandle->getLoop());
        con->onLink(it); //TcpProxy�Իٶ���
    }


private:

    s32 onTimeout(HandleTime& it);
    s32 onTimeout2(HandleTime& it);

    void onClose(Handle* it);
    void onClose2(Handle* it);

    void onWrite(net::RequestTCP* it);
    void onWrite2(net::RequestTCP* it);

    void onRead(net::RequestTCP* it);
    void onRead2(net::RequestTCP* it);

    void onConnect(net::RequestTCP* it);
    void onLink(net::RequestTCP* it);

    static s32 funcOnTime(HandleTime* it) {
        TcpProxy& nd = *(TcpProxy*)it->getUser();
        return nd.onTimeout(*it);
    }

    static void funcOnWrite(net::RequestTCP* it) {
        TcpProxy& nd = *(TcpProxy*)it->mUser;
        nd.onWrite(it);
    }

    static void funcOnRead(net::RequestTCP* it) {
        TcpProxy& nd = *(TcpProxy*)it->mUser;
        nd.onRead(it);
    }

    static void funcOnClose(Handle* it) {
        TcpProxy& nd = *(TcpProxy*)it->getUser();
        nd.onClose(it);
    }


    static s32 funcOnTime2(HandleTime* it) {
        TcpProxy& nd = *(TcpProxy*)it->getUser();
        return nd.onTimeout2(*it);
    }

    static void funcOnWrite2(net::RequestTCP* it) {
        TcpProxy& nd = *(TcpProxy*)it->mUser;
        nd.onWrite2(it);
    }

    static void funcOnRead2(net::RequestTCP* it) {
        TcpProxy& nd = *(TcpProxy*)it->mUser;
        nd.onRead2(it);
    }

    static void funcOnClose2(Handle* it) {
        TcpProxy& nd = *(TcpProxy*)it->getUser();
        nd.onClose2(it);
    }

    static void funcOnConnect(net::RequestTCP* it) {
        TcpProxy& nd = *(TcpProxy*)it->mUser;
        nd.onConnect(it);
    }

    s32 open();

    Loop& mLoop;
    net::HandleTCP mTCP;
    net::HandleTCP mTcpBackend;
};


} //namespace net
} //namespace app


#endif //APP_CONNECTOR_H