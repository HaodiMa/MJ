#pragma once
#include "IMJRoom.h"
#include "CommonDefine.h"
#include "MJCard.h"
#include "HHMJPlayerCard.h"
class HHMJRoom
	:public IMJRoom
{
	struct stSettle
	{
		std::map<uint8_t, uint16_t> vWinIdxs;
		std::map<uint8_t, uint16_t> vLoseIdx;
		eMJActType eSettleReason;
		void addWin(uint8_t nIdx, uint16_t nWinCoin)
		{
			vWinIdxs[nIdx] = nWinCoin;
		}

		void addLose(uint8_t nIdx, uint16_t nLoseCoin)
		{
			vLoseIdx[nIdx] = nLoseCoin;
		}
	};
	struct stFightLandLord
	{
		uint8_t nIdx;
		uint8_t nCard;
		bool isLargeLandLord;
	};
public:
	bool init(IGameRoomManager* pRoomMgr, stBaseRoomConfig* pConfig, uint32_t nSeialNum, uint32_t nRoomID, Json::Value& vJsValue) override;
	void willStartGame()override;
	void startGame()override;
	void onGameDidEnd()override;
	void onGameEnd()override;
	IMJPlayer* doCreateMJPlayer()override;
	IMJPoker* getMJPoker()override;
	bool isGameOver()override;
	void onPlayerHu(std::vector<uint8_t>& vHuIdx, uint8_t nCard, uint8_t nInvokeIdx)override;
	bool onPlayerApplyLeave(uint32_t nPlayerUID)override;
	uint8_t getRoomType()override { return eRoom_MJ_HongHe; }
	void sendPlayersCardInfo(uint32_t nSessionID)override;
	void onPlayerChu(uint8_t nIdx, uint8_t nCard)override;
	void onPlayerPeng(uint8_t nIdx, uint8_t nCard, uint8_t nInvokeIdx)override;
	void onPlayerMingGang(uint8_t nIdx, uint8_t nCard, uint8_t nInvokeIdx)override;
	void onPlayerAnGang(uint8_t nIdx, uint8_t nCard)override;
	void onPlayerBuGang(uint8_t nIdx, uint8_t nCard)override;
	std::shared_ptr<IGameRoomRecorder> createRoomRecorder()override;
	void onPlayerMo(uint8_t nIdx)override;
	void onWaitPlayerAct(uint8_t nIdx, bool& isCanPass)override;

	uint8_t getGangCard1() { return m_nGangCard1; }
	uint8_t getGangCard2() { return m_nGangCard2; }
	void setGangCard(uint8_t nCard) { m_nGangCard = nCard; }
	bool getContinueFight() { return m_isContinueFight; }
	void clearContinueFight() { m_isContinueFight = false; }
	void setLandLordCard(uint8_t nIdx, uint8_t nCard);

	void fightLandLord();
	bool canGang(uint8_t nIdx);
	void onAskForRobotGang(uint8_t nInvokeIdx, uint8_t nCard, std::vector<uint8_t>& vOutCandinates)override;

	bool checkTangZhi();
	void onPlayerTangZhiHu(uint8_t nIdx);

	bool isAnyPlayerPengOrHuThisCard(uint8_t nInvokeIdx, uint8_t nCard);

protected:
	void calculateGangCoin(uint8_t nHuIdx, uint8_t nInvokeIdx, Json::Value& jsMsg, std::vector<uint32_t>& vGangCoinGet, std::vector<uint32_t>& vGangCoinOut);
	void removeInvalidGang(uint8_t nHuIdx, uint8_t nInvokeIdx, std::vector<uint8_t>& vAnGang, std::vector<HHMJPlayerCard::tSongGangIdx>& vMingGang);
	void calculateFightLandLordCoin(Json::Value& jsMsg, std::vector<uint32_t>& vFightLandLordGet, std::vector<uint32_t>& vFightLandLordOut);

	void getSubRoomInfo(Json::Value& jsSubInfo)override;
	void onPlayerZiMo(uint8_t nHuIdx, uint8_t nInvokeIdx, uint8_t nCard, Json::Value& jsDetail, std::vector<uint32_t> vLoseCoin, 
		std::vector<uint32_t> vWinCoin, std::vector<uint32_t> vGangCoinGet, std::vector<uint32_t> vGangCoinOut, 
		std::vector<uint32_t> vFightLandLordGet, std::vector<uint32_t> vFightLandLordOut);

	void changeGangCard();
protected:
	bool m_isBankerHu;
	CMJCard m_tPoker;

	uint8_t m_nGangCard1;
	uint8_t m_nGangCard2;
	uint8_t m_nGangCard;
	uint8_t m_nGangCount;

	bool m_isFightLandLord; // 1:��������0:��������
	bool m_bZiPaiLandLord; // 1:�����Ʒ�����0:�����Ʋ�����
	bool m_bBigLandLord; // 1:���������0:���������
	bool m_isContinueFight;
	std::vector<stFightLandLord> m_vLandLord;
	uint8_t m_LandLordCard[MAX_SEAT_CNT];

	uint8_t m_nZhuangType; // 0:4ׯ�룻1:8ׯ�룻2:��ׯ
	//bool m_bLanPai; // 1:�����ã�0:����
	uint8_t m_nTangZhiType; // 0:û�����ӣ�1:����һ����2:����ƽ��
	
	bool m_bZhuangFan; // 1:ׯ�ҷ�����0:������
	bool m_haveYiTiaoLong; //1:һ������0:û��һ������
	bool m_haveLuoDiLong; //1:�������0:û��
	bool m_haveShouDaiLong; //1:�ִ�����0:û��
	bool m_bShouDaiLong; // 1:�ִ����ӷ���0:���ӷ�
	bool m_b7Pair; // 1:7�Լӷ���0:���ӷ�
};