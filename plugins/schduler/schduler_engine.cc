//  Copyright (c) 2015-2015 The quotations Authors. All rights reserved.
//  Created on: 2017年1月8日 Author: kerry

#include"schduler/schduler_engine.h"
#include "net/comm_head.h"
#include "logic/logic_comm.h"
#include "logic/logic_unit.h"
#include "basic/template.h"

quotations_schduler::SchdulerEngine *GetConnectionSchdulerEngine(void) {
  return new quotations_schduler::SchdulerEngineImpl();
}

namespace quotations_schduler {

bool SchdulerEngineImpl::SetConnectionSchduler(
    const int32 id, quotations_logic::ConnectionSchduler* schduler) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SetConnectionSchduler(id, schduler);
}

bool SchdulerEngineImpl::GetConnectionSchduler(
    const int32 id, quotations_logic::ConnectionSchduler* schduler) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->GetConnectionSchduler(id, schduler);
}

bool SchdulerEngineImpl::DelConnectionSchduler(int32 id) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->DelConnectionSchduler(id);
}

bool SchdulerEngineImpl::FindConnectionSchduler(
    const int socket, quotations_logic::ConnectionSchduler* schduler) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->FindConnectionSchduler(socket, schduler);
}

bool SchdulerEngineImpl::CloseConnectionSchduler(const int socket) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->CloseConnectionSchduler(socket);
}

bool SchdulerEngineImpl::SetRecvTime(const int socket) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SetRecvTime(socket);
}

bool SchdulerEngineImpl::SetSendTime(const int socket) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SetSendTime(socket);
}

bool SchdulerEngineImpl::CheckHeartPacket() {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->CheckHeartPacket();
}

bool SchdulerEngineImpl::SetSendErrorCount(const int socket) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SetSendErrorCount(socket);
}

bool SchdulerEngineImpl::SetRecvErrorCount(const int socket) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SetRecvErrorCount(socket);
}

int32 SchdulerEngineImpl::SendAllQuotations(const void* data, const int32 len,
                                            const int32 type) {
  ConnectionSchdulerManager* schduler_mgr =
       ConnectionSchdulerEngine::GetSchdulerManager();
   return schduler_mgr->SendAllQuotations(data, len, type);
}

int32 SchdulerEngineImpl::SendAllQuotations(const void* data, const int32 len) {
  ConnectionSchdulerManager* schduler_mgr =
      ConnectionSchdulerEngine::GetSchdulerManager();
  return schduler_mgr->SendAllQuotations(data, len);
}

ConnectionSchdulerManager* ConnectionSchdulerEngine::schduler_mgr_ = NULL;
ConnectionSchdulerEngine* ConnectionSchdulerEngine::schduler_engine_ = NULL;

ConnectionSchdulerManager::ConnectionSchdulerManager() {
  schduler_cache_ = new SchdulerCache();
  Init();
}

void ConnectionSchdulerManager::Init() {
  InitThreadrw(&lock_);
}

ConnectionSchdulerManager::~ConnectionSchdulerManager() {
  DeinitThreadrw(lock_);
  schduler_cache_->schduler_map_.clear();
  schduler_cache_->socket_map_.clear();
  if (schduler_cache_) {
    delete schduler_cache_;
    schduler_cache_ = NULL;
  }
}

bool ConnectionSchdulerManager::SetConnectionSchduler(
    const int32 id, quotations_logic::ConnectionSchduler* schduler) {
  base_logic::WLockGd lk(lock_);
  int socket = schduler->socket();
  SOCKET_MAP::iterator it = schduler_cache_->socket_map_.find(socket);
  if (schduler_cache_->socket_map_.end() != it) {
    LOG_ERROR2("find old socket reconnected, socket=%d", socket);
    return false;
  }
  base::MapAdd<SOCKET_MAP, int, quotations_logic::ConnectionSchduler>(
      schduler_cache_->socket_map_, schduler->socket(), (*schduler));
  return base::MapAdd<SCHDULER_MAP, int32, quotations_logic::ConnectionSchduler>(
      schduler_cache_->schduler_map_, id, (*schduler));
}

bool ConnectionSchdulerManager::GetConnectionSchduler(
    const int32 id, quotations_logic::ConnectionSchduler* schduler) {
  base_logic::RLockGd lk(lock_);
  return base::MapGet<SCHDULER_MAP, SCHDULER_MAP::iterator, int32,
      quotations_logic::ConnectionSchduler>(schduler_cache_->schduler_map_, id,
                                            (*schduler));
}

bool ConnectionSchdulerManager::DelConnectionSchduler(const int32 id) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler schduler;
  base::MapGet<SCHDULER_MAP, SCHDULER_MAP::iterator, int32,
      quotations_logic::ConnectionSchduler>(schduler_cache_->schduler_map_, id,
                                            schduler);
  schduler.set_is_effective(false);

  base::MapDel<SOCKET_MAP, SOCKET_MAP::iterator, int>(
      schduler_cache_->socket_map_, schduler.socket());
  return base::MapDel<SCHDULER_MAP, SCHDULER_MAP::iterator, int32>(
      schduler_cache_->schduler_map_, id);
}

bool ConnectionSchdulerManager::FindConnectionSchduler(
    const int socket, quotations_logic::ConnectionSchduler* schduler) {
  base_logic::RLockGd lk(lock_);
  return base::MapGet<SOCKET_MAP, SOCKET_MAP::iterator, int32,
      quotations_logic::ConnectionSchduler>(schduler_cache_->socket_map_,
                                            socket, (*schduler));
}

bool ConnectionSchdulerManager::CloseConnectionSchduler(int socket) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler schduler;
  base::MapGet<SOCKET_MAP, SOCKET_MAP::iterator, int32,
      quotations_logic::ConnectionSchduler>(schduler_cache_->socket_map_,
                                            socket, schduler);
  schduler.set_is_effective(false);
  base::MapDel<SOCKET_MAP, SOCKET_MAP::iterator, int>(
      schduler_cache_->socket_map_, socket);
  return base::MapDel<SCHDULER_MAP, SCHDULER_MAP::iterator, int32>(
      schduler_cache_->schduler_map_, schduler.id());
}

bool ConnectionSchdulerManager::SetSendTime(int socket) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler& schduler =
      schduler_cache_->socket_map_[socket];
  schduler.set_send_last_time(time(NULL));
  return true;
}

bool ConnectionSchdulerManager::SetRecvTime(int socket) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler& schduler =
      schduler_cache_->socket_map_[socket];
  schduler.set_recv_last_time(time(NULL));
  return true;
}

bool ConnectionSchdulerManager::SetSendErrorCount(int socket) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler& schduler =
      schduler_cache_->socket_map_[socket];
  schduler.add_send_error_count();
  return true;
}

bool ConnectionSchdulerManager::SetRecvErrorCount(int socket) {
  base_logic::WLockGd lk(lock_);
  quotations_logic::ConnectionSchduler& schduler =
      schduler_cache_->socket_map_[socket];
  schduler.add_recv_error_count();
  return true;
}

int32 ConnectionSchdulerManager::SendAllQuotations(const void* data,
                                                   const int32 len,
                                                   const int32 type) {
  base_logic::WLockGd lk(lock_);

  SCHDULER_MAP::iterator it = schduler_cache_->schduler_map_.begin();
  for (; it != schduler_cache_->schduler_map_.end(); it++) {
    quotations_logic::ConnectionSchduler& schduler = it->second;
    if (!schduler.is_effective())
      continue;
    if (schduler.id() == 0
        || (type != schduler.type() && (type != quotations_logic::NO_TYPE)))
      continue;
    struct PacketHead* packet = (struct PacketHead*) data;
    if (!send_message(schduler.socket(), packet)) {
      schduler.add_send_error_count();
      schduler.set_is_effective(false);
      LOG_MSG2("schduler.socket()=%d,error msg=%s", (int) schduler.socket(),
          strerror(errno));
      continue;
    }
  }
  return 0;
}

int32 ConnectionSchdulerManager::SendAllQuotations(const void* data,
                                                   const int32 len) {
  return SendAllQuotations(data, len, quotations_logic::NO_TYPE);
}

bool ConnectionSchdulerManager::CheckHeartPacket() {
  time_t current_time = time(NULL);
  bool r = false;
  base_logic::WLockGd lk(lock_);

  SCHDULER_MAP::iterator it = schduler_cache_->schduler_map_.begin();
  for (; it != schduler_cache_->schduler_map_.end(); it++) {
    quotations_logic::ConnectionSchduler& schduler = it->second;
    if ((current_time - schduler.recv_last_time() > 300)) {
      schduler.add_send_error_count();
      //LOG_DEBUG2("location of schduler=%p current_time=%d crawler_schduler out of time %d socket=%d send_error_count=%d",
      //&schduler, (int)current_time, (int)schduler.recv_last_time(), schduler.socket(), schduler.send_error_count());
    }

    if (schduler.send_error_count() > 3) {
      LOG_MSG("close connection");
      schduler.set_is_effective(false);
      base::MapDel<SOCKET_MAP, SOCKET_MAP::iterator, int>(
          schduler_cache_->schduler_map_, schduler.socket());
      base::MapDel<SCHDULER_MAP, SCHDULER_MAP::iterator, int32>(
          schduler_cache_->schduler_map_, schduler.id());
      //closelockconnect(schduler.socket());
      continue;
    }
  }
  return true;
}

}
