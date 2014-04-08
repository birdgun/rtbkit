/* nexage_exchange_connector.h                                    -*- C++ -*-
   Copyright (c) 2014 Datacratic Inc.  All rights reserved.

*/

#pragma once

#include "rtbkit/plugins/exchange/openrtb_exchange_connector.h"

namespace RTBKIT {


/*****************************************************************************/
/* BIDSWITCH EXCHANGE CONNECTOR                                                */
/*****************************************************************************/

/** Exchange connector for Nexage.  This speaks their flavour of the
    OpenRTB 2.1 protocol.
*/

struct NexageExchangeConnector: public OpenRTBExchangeConnector {
    NexageExchangeConnector(ServiceBase & owner, const std::string & name);
    NexageExchangeConnector(const std::string & name,
                               std::shared_ptr<ServiceProxies> proxies);

    static std::string exchangeNameString() {
        return "nexage";
    }

    virtual std::string exchangeName() const {
        return exchangeNameString();
    }

    virtual std::shared_ptr<BidRequest>
    parseBidRequest(HttpAuctionHandler & connection,
                    const HttpHeader & header,
                    const std::string & payload);

#if 0
    virtual HttpResponse
    getResponse(const HttpAuctionHandler & connection,
                const HttpHeader & requestHeader,
                const Auction & auction) const;
#endif

    /** This is the information that the Nexage exchange needs to keep
        for each campaign (agent).
    */
    struct CampaignInfo {
        Id seat;          ///< ID of the Nexage exchange seat
        std::string iurl; ///< Image URL for content checking
    };

    virtual ExchangeCompatibility
    getCampaignCompatibility(const AgentConfig & config,
                             bool includeReasons) const;

    /** This is the information that Nexage needs in order to properly
        filter and serve a creative.
    */
    struct CreativeInfo {
        Id adid;                ///< ID for ad to be service if bid wins
        std::string nurl;       ///< Win notice URL
        std::vector<std::string> adomain;    ///< Advertiser Domain
    };

    virtual ExchangeCompatibility
    getCreativeCompatibility(const Creative & creative,
                             bool includeReasons) const;

    // Nexage win price decoding function.
    static float decodeWinPrice(const std::string & sharedSecret,
                                const std::string & winPriceStr);

  private:
    virtual void setSeatBid(Auction const & auction,
                            int spotNum,
                            OpenRTB::BidResponse & response) const;
};



} // namespace RTBKIT
