/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_nfcd_NfcManager_h
#define mozilla_nfcd_NfcManager_h

#include "DeviceHost.h"
#include "INfcManager.h"

class P2pDevice;
class NfcTagManager;
class ILlcpServerSocket;
class ILlcpSocket;

class NfcManager
  : public DeviceHost
  , public INfcManager
{
public:
  static const int DEFAULT_LLCP_MIU = 1980;
  static const int DEFAULT_LLCP_RWSIZE = 2;

  NfcManager();
  virtual ~NfcManager();

  /**
   * To get a specific interface from NfcManager
   *
   * @param  name Interface name
   * @return      Return specific interface if exist, null if cannot find.
   */
  void* queryInterface(const char* name);

  /**
   * Turn on NFC.
   *
   * @return True if ok.
   */
  bool initialize();

  /**
   * Turn off NFC.
   *
   * @return True if ok.
   */
  bool deinitialize();

  /**
   * Start polling and listening for devices.
   *
   * @return True if ok.
   */
  bool enableDiscovery();

  /**
   * Stop polling and listening for devices.
   *
   * @return True if ok.
   */
  bool disableDiscovery();

  /**
   * Start polling for devices.
   *
   * @return True if ok.
   */
  bool enablePolling();

  /**
   * Stop polling for devices.
   *
   * @return True if ok.
   */
  bool disablePolling();

  /**
   * Start peer-to-peer listening for devices.
   *
   * @return True if ok.
   */
  bool enableP2pListening();

  /**
   * Stop peer-to-peer listening for devices.
   *
   * @return True if ok.
   */
  bool disableP2pListening();

  /**
   * Check Llcp connection.
   * Not used in NCI case.
   *
   * @return True if ok.
   */
  bool checkLlcp();

  /**
   * Activate Llcp connection.
   * Not used in NCI case.
   *
   * @return True if ok.
   */
  bool activateLlcp();

  /**
   * Create a LLCP connection-oriented socket.
   *
   * @param  sap                Service access point.
   * @param  miu                Maximum information unit.
   * @param  rw                 Receive window size.
   * @param  linearBufferLength Max buffer size.
   * @return                    ILlcpSocket interface.
   */
  ILlcpSocket* createLlcpSocket(int sap, int miu, int rw, int linearBufferLength);

  /**
   * Create a new LLCP server socket.
   *
   * @param  nSap               Service access point.
   * @param  sn                 Service name.
   * @param  miu                Maximum information unit.
   * @param  rw                 Receive window size.
   * @param  linearBufferLength Max buffer size.
   * @return                    ILlcpServerSocket interface.
   */
  ILlcpServerSocket* createLlcpServerSocket(int nSap, const char* sn, int miu, int rw, int linearBufferLength);

  /**
   * Set P2P initiator's activation modes.
   *
   * @param  modes Active and/or passive modes.
   * @return       None.
   */
  void setP2pInitiatorModes(int modes);

  /**
   * Set P2P target's activation modes.
   *
   * @param  modes Active and/or passive modes.
   * @return       None.
   */
  void setP2pTargetModes(int modes);

  /**
   * Get default Llcp connection maxumum information unit
   *
   * @return Default MIU.
   */
  int getDefaultLlcpMiu() const { return NfcManager::DEFAULT_LLCP_MIU; };

  /**
   * Get default Llcp connection receive window size
   *
   * @return Default receive window size
   */
  int getDefaultLlcpRwSize() const { return NfcManager::DEFAULT_LLCP_RWSIZE; };

  void resetRFField();

  /**
   * NFC controller starts routing data in listen mode.
   *
   * @return True if ok.
   */
  bool doSelectSecureElement();

  /**
   * NFC controller stops routing data in listen mode.
   *
   * @return True if ok.
   */
  bool doDeselectSecureElement();

private:
  P2pDevice* mP2pDevice;
  NfcTagManager* mNfcTagManager;
};

#endif 
