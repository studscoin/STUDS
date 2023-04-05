// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2019-2020 The MasterWin developers
// Copyright (c) 2021-2021 The Studscoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[0];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x00000080047121d8857fd183fddf47a9cd0c5b4d5f0a5e1d04704f03e91e95c1"))
    (339934, uint256("0xcf13592e307c073a99029e04172f6e51399f7376550810528bdc4a04b518fdbd"))
    (344460, uint256("0x7c7f9e83edb7155a2af266ca91b29b6ca58d2138a1a38ead4533c3994f61e779"))
    (350562, uint256("0x71ff2f4ede2da1e69ccac8e97f73ba4aa4ac75952b1c541faa189c65edd7d96b"))
    (355000, uint256("0x3a9d46b8a133251d3b50829a27f817fbcf8d58a4a44b9e5c0079d65723bce92e"))
    (360000, uint256("0xea9759fa5401dd1db8b0a311cc2f9ef145c684edd5efb6838f0dc40e184a943a"))  
    (370000, uint256("0xfcc0a71cbf81ffefb0173000e37019a4f08deb66695e95729af8cd76c5e2220a"))  
    (378000, uint256("0x39195c08ac0fd275e4bda01e261c620f3454cbe36dffd613ffc5a76003757b0e"))  
    (378900, uint256("0x28d3777b1fd08ab9dd2ec85f80cce1b04bd4434429c538fb9d91e72c9b5d983a"))
    (564186, uint256("0x3438902ba013e8fdbb031d06712b72702d5477c9300c9101b17335da63312697"))
    (695000, uint256("0x14e5144a7bbf38cb2ef90a5abcdae492c0fcdcec564590b23596b24692551011"));
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1680706723, // * UNIX timestamp of last checkpoint block
    1426391,		// * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1622407662,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1622407663,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x5e;
        pchMessageStart[2] = 0xca;
        pchMessageStart[3] = 0x1d;
		vAlertPubKey = ParseHex("04e857989347e0a56ce010833255f6d2c4d274a24bd9e1e67951957b3317f2b386e15e022b44252560ca641012b78719aeccf3c00fba5176f5523b96edfc7e5936");
		nDefaultPort = 11220;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Studscoin starting difficulty is 1 / 2^12
        //nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // STUDS: 1 day
        nTargetSpacing = 1 * 60;  // STUDS: 1 minute
        nMaturity = 100;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 75000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        //nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 1622407658;
        nZerocoinStartTime = 1622407658;
        nBlockEnforceSerialRange = 253; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 999999999; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0 * COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 9999999; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        nEnforceNewSporkKey = 1574428163; //!> Sporks signed after (GMT):  Wednesday, June 12, 2019 5:00:00 AM GMT must use the new spork key

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "Studscoin Created by MasterWin Developer!!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		txNew.vout[0].SetEmpty();
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04060cddf8a7eb70085ddab5ff90ea821de0375c56e881c54cd8c1144ec030ca48ddb150f9d0c5f02937ae6dcf201a05efed40746ca3e2dd6330a8b07c9e4888a1") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1622407658;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 14109257;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00000080047121d8857fd183fddf47a9cd0c5b4d5f0a5e1d04704f03e91e95c1"));
        assert(genesis.hashMerkleRoot == uint256("0xad4b627711cc14c63cd1264bba794186735173ecabf6a84612e4f0ba95e17e720"));

        vSeeds.push_back(CDNSSeedData("seed1", "seed1.studentscoin.net"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.studentscoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed3", "seed3.studentscoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed4", "seed4.studentscoin.net"));
	    vSeeds.push_back(CDNSSeedData("seed5", "seed5.studentscoin.net"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 242);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x22)(0x2e)(0x35)(0x13).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x52)(0xf1)(0xe1)(0x1B).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x60)(0x70)(0x80)(0x97).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "045fb8afbad285b73641e7164fa988bcff1b509abc9a65a6a7d82546f9cb93acaff8f4182450f58efc773bcf80674c69592e3b9c5086cd4bfb6bfda5db7d2c8002";
        strObfuscationPoolDummyAddress = "SF9HoKzH14Y4wu7v9ucEe5d4FxCSg5zBVT";
        nStartMasternodePayments = 1622407659; 

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zstuds to be stakable
        
    vMasternodePhasen.push_back ({
      100,
      {
        {  25000 * COIN, 95 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      50000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 95 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      200000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 95 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      525000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 95 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      1000000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 95 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      1525000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 95 },
        {  200000 * COIN, 0 }
      }
    });
    vMasternodePhasen.push_back ({
      2000000,
      {
        {  25000 * COIN, 0 },
        {  30000 * COIN, 0 },
        {  40000 * COIN, 0 },
        {  50000 * COIN, 0 },
        {  100000 * COIN, 0 },
        {  150000 * COIN, 0 },
        {  200000 * COIN, 95 }
      }
    });
  }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x43;
        pchMessageStart[1] = 0x76;
        pchMessageStart[2] = 0x65;
        pchMessageStart[3] = 0xba;
	vAlertPubKey = ParseHex("04ac4a0017a91f21be5ea4d22adbc007815044f74813ff842ec4ea46072b727440baa610751900c25e57a610f2d03c74320cb7a25ec7587b812a3c4c80c62b9f65");
	nDefaultPort = 32822;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Studscoin: 1 day
        nTargetSpacing = 1 * 60;  // Studscoin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;
        nZerocoinStartTime = 1621704682;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = 9902850; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = 444020; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1622407664;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0x0000041e482b9b9691d98eefb48473405c0b8ec31b76df3797c74a78680ef818"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("", ""));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38); // Testnet mwx addresses start with 'g' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet mwx script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet mwx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet mwx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet mwx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

		convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 2;
        strSporkKey = "045fb8afbad285b73641e7164fa988bcff1b509abc9a65a6a7d82546f9cb93acaff8f4182450f58efc773bcf80674c69592e3b9c5086cd4bfb6bfda5db7d2c8002";
        strObfuscationPoolDummyAddress = "SF9HoKzH14Y4wu7v9ucEe5d4FxCSg5zBVT";
        nStartMasternodePayments = 1615728986; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        //nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Studscoin: 1 day
        nTargetSpacing = 1 * 60;        // Studscoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1622407666;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2402015;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 32824;
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 32825;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    //virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
