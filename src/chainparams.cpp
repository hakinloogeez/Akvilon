// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

#define SHOW_LOG true

class CMainParams : public CChainParams {
public:
    CMainParams() {
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0xc5;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xde;
        vAlertPubKey = ParseHex("78340397288b1e4264789957oyd4ldc63ae4a1a2523b24300a3de1c5c8f4ec1e13eece09ebb0e9514f7b2b7e65f35f3a6ef6279d512f755078347bdcdf4ac378704");
        nDefaultPort = 49085;
        nRPCPort = 49086;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "Volume of the Scottish economy returned to the pre-crisis level earlier than experts expected, and faster than the British economy as a whole July 17, 2014";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1526313900, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1526313900;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 2125083;

        hashGenesisBlock = genesis.GetHash();
#ifdef SHOW_LOG
        LogPrintf("genesis.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("genesis.nBits == %d\n", genesis.nBits);
        LogPrintf("genesis.nNonce == %d\n", genesis.nNonce);
#endif
        assert(hashGenesisBlock == uint256("669edc268b641e9dce1848afbdaed8b8ea006b4fa8e454e9f594dff52ab1686e"));
        assert(genesis.hashMerkleRoot == uint256("02fd74dbcb2ed7efe5ecc9e52f353d432d6be4a1558af48090a8c047adc0d3d8"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("185.246.152.210","185.246.152.210"));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;

        strDarksendPoolDummyAddress = "";
        nLastPOWBlock = 130316;
        nPOSStartBlock = 7467;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xd3;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xb1;
        pchMessageStart[3] = 0xdf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("044c0f17b03507d43fa568e5aa7845e5d4398708bdccc0f658d67029224ad170babc8492d73bbc95ffca8f73eab12d9bb2d87ea6671b0ec023e2fdf1a141ac4624");
        nDefaultPort = 47445;
        nRPCPort = 47446;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1516063067;
        genesis.nNonce = 44;
#ifdef SHOW_LOG
        LogPrintf("CTestNetParams.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("CTestNetParams.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("CTestNetParams.nBits == %d\n", genesis.nBits);
        LogPrintf("CTestNetParams.nNonce == %d\n", genesis.nNonce);
#endif
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,115);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,21);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,28);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
